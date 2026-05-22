### Semana 1

Esta semana refuerza los fundamentos del análisis y diseño de algoritmos con ejemplos pequeños, correctos y fáciles de inspeccionar. El foco está en distinguir especificación, implementación y comportamiento observable, además de introducir criterios básicos de eficiencia y robustez.

#### Temas trabajados

- Modelo RAM
- Costo temporal y espacial básico
- Correctitud básica
- Recursión vs iteración
- ADT, interfaz e implementación
- Bubble sort: orden local/global, invariante, monotonicidad y finitud
- Eficiencia y robustez con ejemplos pequeños

#### Cabeceras principales

- `include/sum.h`
- `include/power.h`
- `include/Fib.h`
- `include/count_ones.h`
- `include/max_algorithms.h`
- `include/bubble_sort.h`
- `include/reverse_utils.h`
- `include/gcd.h`
- `include/hanoi.h`
- `include/Semana1.h`

#### Fuentes

- `src/sum.cpp`
- `src/power.cpp`
- `src/fibonacci.cpp`
- `src/count_ones.cpp`
- `src/max_algorithms.cpp`
- `src/bubble_sort.cpp`
- `src/reverse_utils.cpp`
- `src/gcd.cpp`
- `src/hanoi.cpp`

### Build

Desde la raíz del repositorio:

#### Linux/macOS o generadores single-config

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
````

#### Windows con Visual Studio o generadores multi-config

En Windows, cuando el proyecto se genera con Visual Studio u otro generador multi-config, `ctest` necesita que se indique explícitamente la configuración (`Debug` o `Release`).

```bash
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Si deseas compilar en `Release`:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

#### Ejecución manual en Windows (Debug)

Si compilaste con:

```bash
cmake --build build --config Debug
```

entonces los ejecutables quedan dentro de `build/Semana1/Debug/`.

#### PowerShell o CMD

```powershell
.\build\Semana1\Debug\sem1_demo_sum.exe
.\build\Semana1\Debug\sem1_demo_sum_explicado.exe
.\build\Semana1\Debug\sem1_demo_power.exe
.\build\Semana1\Debug\sem1_demo_fibonacci.exe
.\build\Semana1\Debug\sem1_demo_adt_secuencia.exe
.\build\Semana1\Debug\sem1_demo_bubblesort.exe
.\build\Semana1\Debug\sem1_demo_maximos.exe
.\build\Semana1\Debug\sem1_demo_countones.exe
.\build\Semana1\Debug\sem1_demo_reverse_shift.exe
.\build\Semana1\Debug\sem1_demo_gcd.exe
.\build\Semana1\Debug\sem1_demo_hanoi.exe
.\build\Semana1\Debug\sem1_test_public.exe
.\build\Semana1\Debug\sem1_test_public_extra.exe
.\build\Semana1\Debug\sem1_test_internal.exe
.\build\Semana1\Debug\sem1_test_internal_extra.exe
.\build\Semana1\Debug\sem1_edge_cases.exe
```

#### Git Bash

```bash
./build/Semana1/Debug/sem1_demo_sum.exe
./build/Semana1/Debug/sem1_demo_sum_explicado.exe
./build/Semana1/Debug/sem1_demo_power.exe
./build/Semana1/Debug/sem1_demo_fibonacci.exe
./build/Semana1/Debug/sem1_demo_adt_secuencia.exe
./build/Semana1/Debug/sem1_demo_bubblesort.exe
./build/Semana1/Debug/sem1_demo_maximos.exe
./build/Semana1/Debug/sem1_demo_countones.exe
./build/Semana1/Debug/sem1_demo_reverse_shift.exe
./build/Semana1/Debug/sem1_demo_gcd.exe
./build/Semana1/Debug/sem1_demo_hanoi.exe
./build/Semana1/Debug/sem1_test_public.exe
./build/Semana1/Debug/sem1_test_public_extra.exe
./build/Semana1/Debug/sem1_test_internal.exe
./build/Semana1/Debug/sem1_test_internal_extra.exe
./build/Semana1/Debug/sem1_edge_cases.exe
```

#### Nota sobre `ctest` en Windows

Si aparece un mensaje como el siguiente:

```text
Test not available without configuration. (Missing "-C <config>"?)
```

eso no significa que los tests hayan fallado. Significa que `ctest` no sabe si debe buscar los ejecutables de prueba en `Debug` o en `Release`.

Usa:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

o, si compilaste en `Release`:

```bash
ctest --test-dir build -C Release --output-on-failure
```

#### Cobertura conceptual

Con estas piezas, la semana 1 queda preparada para explicar:

* Algoritmo, entrada/salida y correctitud
* Recursión lineal y recursión con múltiples ramas
* Disminuir y conquistar
* Orden local vs orden global
* Mejor caso, peor caso e intuición asintótica.
* Robustez mediante casos borde y reutilización básica.

