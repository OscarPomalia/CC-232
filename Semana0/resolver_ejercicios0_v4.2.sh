#!/usr/bin/env bash
set -euo pipefail

# Resuelve/automatiza los experimentos propuestos en Ejercicios0.md
# usando el archivo stl_optimizacion_demostracion.cpp subido para el curso.
# Version 4.2
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BASE_CPP_DEFAULT="$ROOT_DIR/stl_optimizacion_demostracion.cpp"
BASE_CPP="$BASE_CPP_DEFAULT"
TARGET="all"
WORKDIR="${WORKDIR:-$ROOT_DIR/ejercicios0_out}"
REPORT="$WORKDIR/reporte_ejercicios0.md"
CXX="${CXX:-g++}"
LIGHT_ARGS=(--scale=10)

mkdir -p "$WORKDIR"

have() {
    command -v "$1" >/dev/null 2>&1
}

log() {
    echo -e "$*" | tee -a "$REPORT"
}

section() {
    echo | tee -a "$REPORT" >/dev/null
    log "## $1"
}

list_exercises() {
    cat <<'USAGE'
Uso:
  ./resolver_ejercicios0_v4.2.sh
  ./resolver_ejercicios0_v4.2.sh [ejercicio]
  ./resolver_ejercicios0_v4.2.sh [archivo.cpp] [ejercicio]

Ejercicios disponibles:
  all     -> ejecuta todo
  1       -> escalera de optimizacion
  2       -> demo STL
  3       -> LTO
  4       -> PGO
  5       -> sanitizers
  6       -> cobertura con gcov
  7       -> cobertura de condiciones y caminos
  8       -> warnings dependientes de optimizacion
  9       -> profiling con gprof
  10      -> resumen/checklist

Alias validos:
  opt, stl, lto, pgo, san, cov, cond, warn, gprof, resumen

Ejemplos:
  ./resolver_ejercicios0_v4.2.sh 1
  ./resolver_ejercicios0_v4.2.sh 5
  ./resolver_ejercicios0_v4.2.sh ./stl_optimizacion_demostracion.cpp 2
  ./resolver_ejercicios0_v4.2.sh all
USAGE
}

normalize_target() {
    case "$1" in
        all) echo "all" ;;
        1|opt|optim|optimizacion) echo "1" ;;
        2|stl) echo "2" ;;
        3|lto) echo "3" ;;
        4|pgo) echo "4" ;;
        5|san|sanitizers) echo "5" ;;
        6|cov|coverage|gcov) echo "6" ;;
        7|cond|path|conditions) echo "7" ;;
        8|warn|warnings) echo "8" ;;
        9|gprof|profile|profiling) echo "9" ;;
        10|resumen|summary) echo "10" ;;
        -h|--help|help|list) echo "help" ;;
        *) echo "invalid" ;;
    esac
}

parse_args() {
    if [[ $# -eq 0 ]]; then
        return 0
    fi

    local first_norm
    first_norm="$(normalize_target "$1")"

    if [[ "$first_norm" != "invalid" ]]; then
        TARGET="$first_norm"
        return 0
    fi

    BASE_CPP="$1"
    shift || true

    if [[ $# -ge 1 ]]; then
        local second_norm
        second_norm="$(normalize_target "$1")"
        if [[ "$second_norm" == "invalid" ]]; then
            echo "Ejercicio no valido: $1" >&2
            echo >&2
            list_exercises
            exit 1
        fi
        TARGET="$second_norm"
    fi
}

needs_base_cpp() {
    case "$TARGET" in
        all|1|2|4) return 0 ;;
        *) return 1 ;;
    esac
}

validate_inputs() {
    if [[ "$TARGET" == "help" ]]; then
        list_exercises
        exit 0
    fi

    if [[ "$TARGET" == "invalid" ]]; then
        echo "Ejercicio no valido." >&2
        echo >&2
        list_exercises
        exit 1
    fi

    if needs_base_cpp && [[ ! -f "$BASE_CPP" ]]; then
        echo "No encuentro el archivo base: $BASE_CPP" >&2
        echo >&2
        list_exercises >&2
        exit 1
    fi
}

write_header() {
    {
        echo "# Reporte automatico de la lista de ejercicios 0"
        echo
        echo "Archivo base usado: $BASE_CPP"
        echo
        echo "Ejercicio seleccionado: $TARGET"
        echo
        echo "Directorio de trabajo: $WORKDIR"
        echo
        echo "Compilador detectado:"
        echo
        echo '```'
        "$CXX" --version | head -n 1
        echo '```'
        echo
        if [[ -n "${MSYSTEM:-}" ]]; then
            echo "MSYSTEM detectado: $MSYSTEM"
            echo
        fi
    } > "$REPORT"
}

resolve_exe() {
    local base="$1"
    if [[ -f "$base" ]]; then
        printf '%s\n' "$base"
    elif [[ -f "${base}.exe" ]]; then
        printf '%s\n' "${base}.exe"
    else
        printf '%s\n' "$base"
    fi
}

measure_run() {
    local exe
    exe="$(resolve_exe "$1")"
    local stdout_file="$2"
    local stderr_file="$3"
    shift 3

    local time_file="$WORKDIR/.time.tmp"
    set +e
    if have /usr/bin/time; then
        /usr/bin/time -f '%e' -o "$time_file" "$exe" "$@" >"$stdout_file" 2>"$stderr_file"
    elif have time; then
        time "$exe" "$@" >"$stdout_file" 2>"$stderr_file"
        printf 'N/A\n' > "$time_file"
    else
        "$exe" "$@" >"$stdout_file" 2>"$stderr_file"
        printf 'N/A\n' > "$time_file"
    fi
    local status=$?
    set -e

    local elapsed="N/A"
    if [[ -f "$time_file" ]]; then
        elapsed="$(cat "$time_file")"
    fi
    rm -f "$time_file"
    printf '%s;%s\n' "$status" "$elapsed"
}

binary_size() {
    local f
    f="$(resolve_exe "$1")"
    if [[ ! -f "$f" ]]; then
        echo "N/A"
        return
    fi
    if stat -c '%s' "$f" >/dev/null 2>&1; then
        stat -c '%s' "$f"
    else
        wc -c < "$f" | tr -d ' '
    fi
}

compile_capture() {
    local out="$1"
    local logf="$2"
    shift 2
    set +e
    "$CXX" "$@" -o "$out" > /dev/null 2> "$logf"
    local status=$?
    set -e
    return "$status"
}

count_warnings() {
    local f="$1"
    if [[ ! -s "$f" ]]; then
        echo 0
    else
        grep -ci 'warning:' "$f" || true
    fi
}

print_table_header() {
    printf '%-12s | %-10s | %-12s | %-10s\n' "Build" "Estado" "Tiempo(s)" "Bytes" | tee -a "$REPORT"
    printf '%-12s-+-%-10s-+-%-12s-+-%-10s\n' '------------' '----------' '------------' '----------' | tee -a "$REPORT"
}

show_compile_error_excerpt() {
    local f="$1"
    if [[ -s "$f" ]]; then
        log '```text'
        head -n 20 "$f" | tee -a "$REPORT" >/dev/null
        log '```'
    fi
}

experiment_1_optimization_ladder() {
    section "1. Escalera de optimizacion"
    log "Compila el mismo programa con distintos niveles y mide tiempo, tamaño y warnings."
    echo >> "$REPORT"
    printf '```text\n' | tee -a "$REPORT" >/dev/null
    print_table_header

    local builds=(
        "O0|-std=c++17 -O0 -g -Wall -Wextra -pedantic"
        "Og|-std=c++17 -Og -g -Wall -Wextra -pedantic"
        "O1|-std=c++17 -O1 -DNDEBUG -Wall -Wextra -pedantic"
        "O2|-std=c++17 -O2 -DNDEBUG -Wall -Wextra -pedantic"
        "O3|-std=c++17 -O3 -DNDEBUG -Wall -Wextra -pedantic"
        "Os|-std=c++17 -Os -DNDEBUG -Wall -Wextra -pedantic"
    )

    for entry in "${builds[@]}"; do
        IFS='|' read -r name flags <<< "$entry"
        local exe_base="$WORKDIR/demo_${name}"
        local clog="$WORKDIR/${name}.compile.log"
        if compile_capture "$exe_base" "$clog" $flags "$BASE_CPP"; then
            local exe
            exe="$(resolve_exe "$exe_base")"
            local run_out="$WORKDIR/${name}.stdout.txt"
            local run_err="$WORKDIR/${name}.stderr.txt"
            IFS=';' read -r status elapsed < <(measure_run "$exe" "$run_out" "$run_err" "${LIGHT_ARGS[@]}")
            printf '%-12s | %-10s | %-12s | %-10s\n' "$name" "ok($status)" "$elapsed" "$(binary_size "$exe")" | tee -a "$REPORT"
            log "Warnings en $name: $(count_warnings "$clog")"
        else
            printf '%-12s | %-10s | %-12s | %-10s\n' "$name" "falla" "N/A" "N/A" | tee -a "$REPORT"
            log "Error de compilacion en $name. Revisa: $clog"
        fi
    done
    printf '```\n' | tee -a "$REPORT" >/dev/null

    log "\nComandos extra utiles:"
    log '\n```bash'
    log "$CXX -Q -O2 --help=optimizers"
    log "$CXX -Q -O3 --help=optimizers"
    log "$CXX -Q -Os --help=optimizers"
    log '```'
}

experiment_2_stl_demo() {
    section "2. STL: algoritmo correcto vs microajuste"
    local exe_base="$WORKDIR/stl_demo"
    local clog="$WORKDIR/stl_demo.compile.log"
    if compile_capture "$exe_base" "$clog" -std=c++17 -O2 -Wall -Wextra -pedantic "$BASE_CPP"; then
        local exe
        exe="$(resolve_exe "$exe_base")"
        local run_out="$WORKDIR/stl_demo.stdout.txt"
        local run_err="$WORKDIR/stl_demo.stderr.txt"
        IFS=';' read -r status elapsed < <(measure_run "$exe" "$run_out" "$run_err" "${LIGHT_ARGS[@]}")
        log "Compilacion: OK"
        log "Tiempo de ejecucion (${LIGHT_ARGS[*]}): ${elapsed}s"
        log "Codigo de salida: $status"
        log "Salida completa guardada en: \`$run_out\`"
        log "\nPrimeras lineas de la salida:"
        log '```text'
        head -n 30 "$run_out" | tee -a "$REPORT" >/dev/null
        log '```'
    else
        log "Fallo la compilacion del experimento STL. Revisa \`$clog\`."
        show_compile_error_excerpt "$clog"
    fi
}

create_lto_files() {
    cat > "$WORKDIR/a.cpp" <<'CPP'
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

std::uint64_t hot_transform(const std::vector<int>& v);

int main() {
    std::vector<int> data(800000);
    for (std::size_t i = 0; i < data.size(); ++i) data[i] = static_cast<int>(i % 997);
    std::uint64_t acc = 0;
    for (int rep = 0; rep < 40; ++rep) acc ^= hot_transform(data);
    std::cout << acc << "\n";
    return 0;
}
CPP

    cat > "$WORKDIR/b.cpp" <<'CPP'
#include <cstdint>
#include <vector>

static inline std::uint64_t mix(std::uint64_t x) {
    x ^= (x << 13);
    x ^= (x >> 7);
    x ^= (x << 17);
    return x;
}

std::uint64_t hot_transform(const std::vector<int>& v) {
    std::uint64_t acc = 0;
    for (int x : v) {
        acc += mix(static_cast<std::uint64_t>(x * 1315423911u + 12345u));
    }
    return acc;
}
CPP
}

experiment_3_lto() {
    section "3. LTO: optimizacion entre archivos"
    create_lto_files

    local fail=0

    if ! compile_capture "$WORKDIR/a.o" "$WORKDIR/lto_a.compile.log" -std=c++17 -O2 -c "$WORKDIR/a.cpp"; then fail=1; fi
    if ! compile_capture "$WORKDIR/b.o" "$WORKDIR/lto_b.compile.log" -std=c++17 -O2 -c "$WORKDIR/b.cpp"; then fail=1; fi
    if [[ $fail -eq 0 ]]; then
        set +e
        "$CXX" -std=c++17 -O2 "$WORKDIR/a.o" "$WORKDIR/b.o" -o "$WORKDIR/app_no_lto" > /dev/null 2> "$WORKDIR/lto_link_plain.log"
        local plain_link=$?
        set -e
        [[ $plain_link -ne 0 ]] && fail=1
    fi

    if ! compile_capture "$WORKDIR/a_lto.o" "$WORKDIR/lto_a_lto.compile.log" -std=c++17 -O2 -flto -c "$WORKDIR/a.cpp"; then fail=1; fi
    if ! compile_capture "$WORKDIR/b_lto.o" "$WORKDIR/lto_b_lto.compile.log" -std=c++17 -O2 -flto -c "$WORKDIR/b.cpp"; then fail=1; fi
    if [[ $fail -eq 0 ]]; then
        set +e
        "$CXX" -std=c++17 -O2 -flto "$WORKDIR/a_lto.o" "$WORKDIR/b_lto.o" -o "$WORKDIR/app_lto" > /dev/null 2> "$WORKDIR/lto_link_lto.log"
        local lto_link=$?
        set -e
        [[ $lto_link -ne 0 ]] && fail=1
    fi

    if [[ $fail -ne 0 ]]; then
        log "No se pudo completar el experimento LTO en este entorno."
        log "Revisa estos logs si quieres el detalle:"
        log "- \`$WORKDIR/lto_a.compile.log\`"
        log "- \`$WORKDIR/lto_b.compile.log\`"
        log "- \`$WORKDIR/lto_link_plain.log\`"
        log "- \`$WORKDIR/lto_a_lto.compile.log\`"
        log "- \`$WORKDIR/lto_b_lto.compile.log\`"
        log "- \`$WORKDIR/lto_link_lto.log\`"
        return
    fi

    IFS=';' read -r s1 t1 < <(measure_run "$WORKDIR/app_no_lto" "$WORKDIR/no_lto.out" "$WORKDIR/no_lto.err")
    IFS=';' read -r s2 t2 < <(measure_run "$WORKDIR/app_lto" "$WORKDIR/lto.out" "$WORKDIR/lto.err")

    log '| Variante | Estado | Tiempo(s) | Bytes |'
    log '|---|---:|---:|---:|'
    log "| sin LTO | $s1 | $t1 | $(binary_size "$WORKDIR/app_no_lto") |"
    log "| con LTO | $s2 | $t2 | $(binary_size "$WORKDIR/app_lto") |"
    log "\nNota: para LTO se uso \`-flto\` tanto al compilar como al enlazar."
}

experiment_4_pgo() {
    section "4. PGO: optimizacion guiada por perfil"
    local pgo_dir="$WORKDIR/pgo-data"
    rm -rf "$pgo_dir"
    mkdir -p "$pgo_dir"

    local plain_log="$WORKDIR/pgo_plain.compile.log"
    local gen_log="$WORKDIR/pgo_gen.compile.log"
    local use_log="$WORKDIR/pgo_use.compile.log"

    if ! compile_capture "$WORKDIR/demo_o2_plain" "$plain_log" -std=c++17 -O2 "$BASE_CPP"; then
        log "Fallo la compilacion O2 base para PGO. Revisa \`$plain_log\`."
        show_compile_error_excerpt "$plain_log"
        return
    fi

    if ! compile_capture "$WORKDIR/demo_pgo_gen" "$gen_log" -std=c++17 -O2 -fprofile-generate="$pgo_dir" "$BASE_CPP"; then
        log "Este entorno no acepto la fase de generacion de perfiles de PGO. Revisa \`$gen_log\`."
        show_compile_error_excerpt "$gen_log"
        return
    fi

    measure_run "$WORKDIR/demo_pgo_gen" "$WORKDIR/pgo_gen.out" "$WORKDIR/pgo_gen.err" "${LIGHT_ARGS[@]}" >/dev/null || true

    if ! compile_capture "$WORKDIR/demo_pgo_use" "$use_log" -std=c++17 -O2 -fprofile-use="$pgo_dir" -Wno-error=coverage-mismatch "$BASE_CPP"; then
        log "Este entorno no acepto la fase de uso de perfiles de PGO. Revisa \`$use_log\`."
        show_compile_error_excerpt "$use_log"
        return
    fi

    IFS=';' read -r s1 t1 < <(measure_run "$WORKDIR/demo_o2_plain" "$WORKDIR/pgo_plain.out" "$WORKDIR/pgo_plain.err" "${LIGHT_ARGS[@]}")
    IFS=';' read -r s2 t2 < <(measure_run "$WORKDIR/demo_pgo_use" "$WORKDIR/pgo_use.out" "$WORKDIR/pgo_use.err" "${LIGHT_ARGS[@]}")

    log '| Variante | Estado | Tiempo(s) | Bytes |'
    log '|---|---:|---:|---:|'
    log "| O2 normal | $s1 | $t1 | $(binary_size "$WORKDIR/demo_o2_plain") |"
    log "| O2 + PGO | $s2 | $t2 | $(binary_size "$WORKDIR/demo_pgo_use") |"
    log "\nEntrenamiento realizado con el mismo programa usando \`--scale=10\`."
}

create_sanitizer_sources() {
    cat > "$WORKDIR/demo_ub.cpp" <<'CPP'
#include <climits>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(4, 7);
    int overflow = INT_MAX;
    overflow += 1; // UB: signed overflow
    std::cout << "overflow=" << overflow << "\n";
    std::cout << v[10] << "\n"; // acceso fuera de rango para ASan
    return 0;
}
CPP

    cat > "$WORKDIR/demo_threads.cpp" <<'CPP'
#include <iostream>
#include <thread>

int counter = 0;

void work() {
    for (int i = 0; i < 100000; ++i) {
        counter++;
    }
}

int main() {
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
    std::cout << counter << "\n";
    return 0;
}
CPP
}

experiment_5_sanitizers() {
    section "5. Sanitizers: memoria, UB y data races"
    create_sanitizer_sources

    local asan_bin="$WORKDIR/demo_asan_ubsan"
    local asan_log="$WORKDIR/demo_asan_ubsan.compile.log"
    if compile_capture "$asan_bin" "$asan_log" -std=c++17 -O1 -g -fsanitize=address,undefined "$WORKDIR/demo_ub.cpp"; then
        set +e
        "$(resolve_exe "$asan_bin")" > "$WORKDIR/asan.stdout.txt" 2> "$WORKDIR/asan.stderr.txt"
        local rs=$?
        set -e
        log "ASan/UBSan compila bien. Codigo de salida al ejecutar: $rs"
        log '```text'
        head -n 20 "$WORKDIR/asan.stderr.txt" | tee -a "$REPORT" >/dev/null
        log '```'
    else
        log "No se pudo compilar ASan/UBSan en este entorno."
        show_compile_error_excerpt "$asan_log"
    fi

    local rec_bin="$WORKDIR/demo_recover"
    local stop_bin="$WORKDIR/demo_stop"
    local rec_log="$WORKDIR/demo_recover.compile.log"
    local stop_log="$WORKDIR/demo_stop.compile.log"

    if compile_capture "$rec_bin" "$rec_log" -std=c++17 -O1 -g -fsanitize=undefined -fsanitize-recover=undefined "$WORKDIR/demo_ub.cpp"; then
        set +e
        "$(resolve_exe "$rec_bin")" > "$WORKDIR/recover.stdout.txt" 2> "$WORKDIR/recover.stderr.txt"
        local rrec=$?
        set -e
        log "Recover exit code: $rrec"
    else
        log "No se pudo compilar la variante recover de UBSan."
        show_compile_error_excerpt "$rec_log"
    fi

    if compile_capture "$stop_bin" "$stop_log" -std=c++17 -O1 -g -fsanitize=undefined -fno-sanitize-recover=undefined "$WORKDIR/demo_ub.cpp"; then
        set +e
        "$(resolve_exe "$stop_bin")" > "$WORKDIR/stop.stdout.txt" 2> "$WORKDIR/stop.stderr.txt"
        local rstop=$?
        set -e
        log "Stop-at-first exit code: $rstop"
    else
        log "No se pudo compilar la variante stop-at-first de UBSan."
        show_compile_error_excerpt "$stop_log"
    fi

    local tsan_bin="$WORKDIR/demo_tsan"
    local tsan_log="$WORKDIR/demo_tsan.compile.log"
    if compile_capture "$tsan_bin" "$tsan_log" -std=c++17 -O1 -g -fsanitize=thread "$WORKDIR/demo_threads.cpp"; then
        set +e
        "$(resolve_exe "$tsan_bin")" > "$WORKDIR/tsan.stdout.txt" 2> "$WORKDIR/tsan.stderr.txt"
        local ts=$?
        set -e
        log "TSan compilo bien. Codigo de salida: $ts"
        log '```text'
        head -n 20 "$WORKDIR/tsan.stderr.txt" | tee -a "$REPORT" >/dev/null
        log '```'
    else
        log "No se pudo compilar ThreadSanitizer en este entorno."
        show_compile_error_excerpt "$tsan_log"
    fi
}

create_coverage_sources() {
    cat > "$WORKDIR/modulo.cpp" <<'CPP'
int clasificar(int x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    if (x % 2 == 0) return 2;
    if (x % 3 == 0) return 3;
    return 1;
}
CPP

    cat > "$WORKDIR/tests.cpp" <<'CPP'
#include <cassert>

int clasificar(int x);

int main() {
    assert(clasificar(-5) == -1);
    assert(clasificar(0) == 0);
    assert(clasificar(8) == 2);
    // Faltan casos para multiplos de 3 y para impares no multiplos de 3.
    return 0;
}
CPP
}

experiment_6_coverage() {
    section "6. Cobertura: tests que pasan no implican tests buenos"
    create_coverage_sources

    if ! have gcov; then
        log "gcov no esta disponible en este entorno."
        return
    fi

    pushd "$WORKDIR" >/dev/null

    set +e
    "$CXX" -std=c++17 --coverage -O0 -c tests.cpp -o tests.o > /dev/null 2> tests.compile.log
    local c_tests=$?
    "$CXX" -std=c++17 --coverage -O0 -c modulo.cpp -o modulo.o > /dev/null 2> modulo.compile.log
    local c_mod=$?
    set -e

    if [[ $c_tests -ne 0 || $c_mod -ne 0 ]]; then
        popd >/dev/null
        log "No se pudo compilar el experimento de cobertura."
        log "Revisa \`$WORKDIR/tests.compile.log\` y \`$WORKDIR/modulo.compile.log\`."
        show_compile_error_excerpt "$WORKDIR/tests.compile.log"
        show_compile_error_excerpt "$WORKDIR/modulo.compile.log"
        return
    fi

    set +e
    "$CXX" --coverage tests.o modulo.o -o tests_cov > /dev/null 2> tests_cov.link.log
    local lstatus=$?
    set -e
    if [[ $lstatus -ne 0 ]]; then
        popd >/dev/null
        log "No se pudo enlazar el ejecutable de cobertura. Revisa \`$WORKDIR/tests_cov.link.log\`."
        show_compile_error_excerpt "$WORKDIR/tests_cov.link.log"
        return
    fi

    set +e
    "$(resolve_exe "$WORKDIR/tests_cov")" > tests_cov.out 2> tests_cov.err
    local rstatus=$?
    gcov -o . tests.cpp modulo.cpp > gcov_summary.txt 2>&1
    local gcov_status=$?
    if [[ $gcov_status -ne 0 ]]; then
        echo >> gcov_summary.txt
        echo "--- intento alternativo: gcov -o $WORKDIR tests.cpp modulo.cpp ---" >> gcov_summary.txt
        gcov -o "$WORKDIR" tests.cpp modulo.cpp >> gcov_summary.txt 2>&1
        gcov_status=$?
    fi
    set -e
    popd >/dev/null

    log "Ejecucion tests_cov: $rstatus"
    if [[ $gcov_status -ne 0 ]]; then
        log "gcov fallo. Revisa \`$WORKDIR/gcov_summary.txt\`."
        show_compile_error_excerpt "$WORKDIR/gcov_summary.txt"
        return
    fi

    log "Resumen de gcov:"
    log '```text'
    grep -E 'Lines executed|Creating' "$WORKDIR/gcov_summary.txt" | tee -a "$REPORT" >/dev/null || true
    log '```'
    log "Archivos generados: \`$WORKDIR/modulo.cpp.gcov\` y \`$WORKDIR/tests.cpp.gcov\`."
}

create_condition_source() {
    cat > "$WORKDIR/demo_cond.cpp" <<'CPP'
#include <cassert>

bool decision(int a, int b, int c) {
    return (a > 0 && b > 0) || c == 0;
}

int main() {
    assert(decision(1, 1, 9) == true);
    assert(decision(-1, 1, 0) == true);
    assert(decision(-1, 1, 5) == false);
    return 0;
}
CPP
}

experiment_7_condition_path() {
    section "7. Cobertura de condiciones y caminos"
    create_condition_source

    pushd "$WORKDIR" >/dev/null
    set +e
    "$CXX" -std=c++17 -O0 -fcondition-coverage demo_cond.cpp -o demo_cond > /dev/null 2> demo_cond.compile.log
    local cond_ok=$?
    set -e

    if [[ $cond_ok -eq 0 ]]; then
        "$(resolve_exe "$WORKDIR/demo_cond")" > demo_cond.out 2> demo_cond.err || true
        gcov --conditions demo_cond.cpp > gcov_conditions.txt 2>&1 || true
        log "Cobertura de condiciones: disponible en este compilador."
        log '```text'
        head -n 20 gcov_conditions.txt | tee -a "$REPORT" >/dev/null
        log '```'
    else
        log "Este compilador no acepta -fcondition-coverage."
    fi

    set +e
    "$CXX" -std=c++17 -O0 -fpath-coverage demo_cond.cpp -o demo_path > /dev/null 2> demo_path.compile.log
    local path_ok=$?
    set -e
    if [[ $path_ok -eq 0 ]]; then
        log "-fpath-coverage si esta disponible aqui."
    else
        log "-fpath-coverage no esta disponible en este GCC, el script lo detecta automaticamente."
    fi
    popd >/dev/null
}

create_warning_source() {
    cat > "$WORKDIR/demo_warn.cpp" <<'CPP'
#include <cstdlib>

int f(bool cond) {
    int x;
    if (cond) x = 10;
    return x + 1; // potencialmente no inicializada
}

int main() {
    return f(std::rand() % 2 == 0);
}
CPP
}

experiment_8_opt_warnings() {
    section "8. Warnings dependientes de optimizacion"
    create_warning_source

    set +e
    "$CXX" -std=c++17 -O0 -Wall -Wextra -Wpedantic -Wmaybe-uninitialized "$WORKDIR/demo_warn.cpp" -o "$WORKDIR/demo_w0" 2> "$WORKDIR/demo_w0.log"
    local s0=$?
    "$CXX" -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wmaybe-uninitialized "$WORKDIR/demo_warn.cpp" -o "$WORKDIR/demo_w2" 2> "$WORKDIR/demo_w2.log"
    local s2=$?
    set -e

    log "Estado O0: $s0 | warnings: $(count_warnings "$WORKDIR/demo_w0.log")"
    log "Estado O2: $s2 | warnings: $(count_warnings "$WORKDIR/demo_w2.log")"
    log "\nFragmento O2:"
    log '```text'
    if [[ -s "$WORKDIR/demo_w2.log" ]]; then
        cat "$WORKDIR/demo_w2.log" | tee -a "$REPORT" >/dev/null
    else
        echo "Sin warnings en O2" | tee -a "$REPORT" >/dev/null
    fi
    log '```'
}

create_gprof_source() {
    cat > "$WORKDIR/demo_gprof.cpp" <<'CPP'
#include <cstdint>
#include <iostream>
#include <vector>

std::uint64_t hot(const std::vector<int>& data) {
    std::uint64_t s = 0;
    for (int rep = 0; rep < 180; ++rep) {
        for (int x : data) {
            s += static_cast<std::uint64_t>((x * 37) ^ (x >> 3));
        }
    }
    return s;
}

std::uint64_t cold(const std::vector<int>& data) {
    std::uint64_t s = 0;
    for (int x : data) s += static_cast<std::uint64_t>(x);
    return s;
}

int main() {
    std::vector<int> data(50000);
    for (int i = 0; i < 50000; ++i) data[i] = i;
    std::cout << hot(data) + cold(data) << "\n";
    return 0;
}
CPP
}

experiment_9_gprof() {
    section "9. Profiling clasico con gprof"
    create_gprof_source

    if ! have gprof; then
        log "gprof no esta disponible en este entorno."
        return
    fi

    pushd "$WORKDIR" >/dev/null

    local out_name="demo_gprof"
    case "${OS:-}" in
        Windows_NT) out_name="demo_gprof.exe" ;;
    esac
    case "${MSYSTEM:-}" in
        MINGW*|UCRT*|CLANG*) out_name="demo_gprof.exe" ;;
    esac

    set +e
    "$CXX" -std=c++17 -O2 -pg demo_gprof.cpp -o "$out_name" > demo_gprof.compile.log 2>&1
    local cstatus=$?
    set -e
    if [[ $cstatus -ne 0 ]]; then
        popd >/dev/null
        log "Falla la compilacion de gprof. Revisa \`$WORKDIR/demo_gprof.compile.log\`."
        show_compile_error_excerpt "$WORKDIR/demo_gprof.compile.log"
        return
    fi

    local exe="./$out_name"
    if [[ ! -f "$exe" ]]; then
        popd >/dev/null
        log "No se encuentra el ejecutable esperado: \`$WORKDIR/$out_name\`."
        return
    fi

    set +e
    "$exe" > demo_gprof.out 2> demo_gprof.err
    local rstatus=$?
    set -e
    if [[ $rstatus -ne 0 ]]; then
        popd >/dev/null
        log "La ejecucion del binario gprof falla. Revisa \`$WORKDIR/demo_gprof.err\`."
        return
    fi

    if [[ ! -f gmon.out ]]; then
        popd >/dev/null
        log "No se genera \`gmon.out\`. Este entorno probablemente no soporta \`gprof\` correctamente."
        return
    fi

    set +e
    gprof "$exe" gmon.out > gprof.txt 2> gprof.stderr.txt
    local gpstatus=$?
    set -e
    popd >/dev/null

    if [[ $gpstatus -ne 0 ]]; then
        log "gprof falla. Revisa \`$WORKDIR/gprof.stderr.txt\`."
        show_compile_error_excerpt "$WORKDIR/gprof.stderr.txt"
        return
    fi

    log "Primeras lineas relevantes de gprof:"
    log '```text'
    grep -n -m 20 -E 'flat profile|hot|cold|time' "$WORKDIR/gprof.txt" | tee -a "$REPORT" >/dev/null || true
    log '```'
}

experiment_10_summary() {
    section "10. Que medir siempre"
    log "Checklist sugerido para todos los experimentos:"
    log "- tiempo total"
    log "- tamaño del ejecutable"
    log "- correctitud del resultado"
    log "- estabilidad entre corridas"
    log "- uso de memoria, cuando aplique"
    log "\nY mantener constantes: input, maquina, compilador y numero de repeticiones."
}

run_selected_exercise() {
    case "$TARGET" in
        all)
            experiment_1_optimization_ladder
            experiment_2_stl_demo
            experiment_3_lto
            experiment_4_pgo
            experiment_5_sanitizers
            experiment_6_coverage
            experiment_7_condition_path
            experiment_8_opt_warnings
            experiment_9_gprof
            experiment_10_summary
            ;;
        1) experiment_1_optimization_ladder ;;
        2) experiment_2_stl_demo ;;
        3) experiment_3_lto ;;
        4) experiment_4_pgo ;;
        5) experiment_5_sanitizers ;;
        6) experiment_6_coverage ;;
        7) experiment_7_condition_path ;;
        8) experiment_8_opt_warnings ;;
        9) experiment_9_gprof ;;
        10) experiment_10_summary ;;
        *)
            echo "Ejercicio no valido: $TARGET" >&2
            echo >&2
            list_exercises
            exit 1
            ;;
    esac
}

main() {
    parse_args "$@"
    validate_inputs
    write_header
    section "Preparacion"
    log "Se usara el archivo base: \`$BASE_CPP\`"
    log "Ejercicio seleccionado: \`$TARGET\`"
    log "Todos los binarios, logs y reportes se guardaran en: \`$WORKDIR\`"
    log ""

    run_selected_exercise

    section "Fin"
    log "Listo. Revisa el reporte en: \`$REPORT\`"
}

main "$@"
