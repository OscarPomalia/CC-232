### PC3 - CC232

#### Estudiante

- **Nombre:** Oscar Alberto Pomalia Suyo

- **Código:** 20240385I

- **Problema asignado:** Codeforces 817F - MEX Queries

- **Enlace oficial:** [https://codeforces.com/problemset/problem/817/F](https://codeforces.com/problemset/problem/817/F)

#### Referencia oficial

- **CSV oficial:** [https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv](https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv)

#### Relación con Semanas 4-6

- **Semana principal:** Semanas 5 y 6

- **Estructura usada:** Treap de Intervalos Disjuntos (Lazy Concept)

- **Estructura de la librería `cc232` relacionada:** `Treap.h` (Heap/Prioridades) y lógica de `BST` (Búsqueda ordenada)

#### Resumen de la solución

El problema exige actualizar y consultar rangos masivos de datos (hasta $10^{18}$). Una solución ingenua iterando punto por punto causaría TLE y MLE inmediatos. Para superarlo, se comprimió la información en un Treap donde cada nodo representa un intervalo contiguo y disjunto `[l, r]` de números cubiertos (con valor 1). Al insertar, remover o invertir, el algoritmo usa búsqueda binaria para recolectar los nodos solapados, los extrae temporalmente, recalcula los límites y reinserta los nuevos intervalos fusionados o particionados. El MEX corresponde al primer hueco no cubierto a la derecha del límite superior del primer bloque, o 1 si la estructura está vacía o no empieza en 1.

#### Invariante principal

**Invariante de Disyunción y Orden:** No existen dos intervalos en el árbol que se toquen o se solapen. Para cualquier par de intervalos `[a, b]` y `[c, d]`, se cumple que `max(a,c) > min(b,d) + 1`. Esto asegura que el árbol mantenga estrictamente rangos disjuntos y ordenados por su límite inferior, lo cual permite búsquedas seguras y evita duplicidades.

#### Complejidad

- **Tiempo por operación:** $O(\log N + K \log N)$ amortizado, donde $K$ es el número de nodos solapados afectados en una consulta.

- **Tiempo total:** $O(N \log N)$ amortizado en el peor de los casos para procesar $N$ consultas.

- **Espacio:** $O(M)$ donde $M$ es la cantidad de intervalos vivos generados (acotado superiormente por $O(N)$).

#### Archivos relevantes

- `include/IntervalTreap.h`: Lógica central del Treap y operaciones de intervalos.

- `src/main.cpp`: Lectura de operaciones y ejecución para Codeforces.

- `docs/respuestas_obligatorias.md`: Cuestionario técnico de la PC3.

- `docs/bitacora.md`: Proceso e historial de desarrollo diario.

- `resultados/`: Evidencias reproducibles de las pruebas y la compilación limpia.

#### Limpieza del repositorio

El repositorio no versiona builds, ejecutables ni archivos generados, cumpliendo estrictamente con la Regla 3.6 de la PC3. No existen archivos residuales en el repositorio como `build/`, `cmake-build-*`, `.exe`, `.out`, `.o`, `.obj`, `CMakeCache.txt`, `CMakeFiles/` ni `__pycache__/`.

Para verificar la limpieza de archivos generados, se utilizó el siguiente comando, el cual devuelve una salida limpia demostrando que el `.gitignore` cumple su función:

```bash
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
```

#### Compilación

El proyecto debe compilar desde una copia limpia del repositorio utilizando CMake:

```bash
cmake -S . -B build
cmake --build build
```

#### Ejecución

Indica el comando exacto para ejecutar el programa principal:

```bash
./build/pc3_main.exe
```

#### Pruebas

**Justificación sobre ctest:** Tal como permite explícitamente la rúbrica, se optó por no usar `ctest` automatizado y, en su lugar, ofrecer pruebas interactivas manuales y documentadas de forma reproducible en la carpeta `resultados/`. Esta decisión se tomó para poder visualizar el estado interno de los nodos del Treap y la evolución del MEX paso a paso durante la modificación grabada en la sustentación en video.

Se diseñaron e integraron al menos 5 pruebas detalladas (documentadas en `resultados/`) para validar de manera estricta la correctitud y los invariantes:

1. **Caso mínimo:**
   * **entrada usada:** Operación `1 1 1` (Añadir el rango `[1, 1]`).
   * **salida esperada:** `2`
   * **salida obtenida:** `2`
   * **qué aspecto valida:** Inserción elemental en el Treap y actualización inmediata del MEX.

2. **Caso con estructura vacía, frontera o ausencia de respuesta:**
   * **entrada usada:** Consultar el MEX sin haber realizado ninguna operación de inserción.
   * **salida esperada:** `1`
   * **salida obtenida:** `1`
   * **qué aspecto valida:** Correctitud de la estructura en su estado base y prevención de errores por punteros nulos (`root_ == nullptr`).

3. **Caso con duplicados o empates:**
   * **entrada usada:** Añadir `[1, 5]` y subsecuentemente añadir `[3, 7]`.
   * **salida esperada:** `6` y luego `8`.
   * **salida obtenida:** `6` y `8`.
   * **qué aspecto valida:** La lógica de fusión dinámica de intervalos solapados, absorbiendo los nodos redundantes y consolidando un único nodo disjunto `[1, 7]`.

4. **Caso extremo pequeño verificable manualmente:**
   * **entrada usada:** Añadir `[1, 10]`, seguido de Invertir `[5, 15]`.
   * **salida esperada:** `11` y luego `5`.
   * **salida obtenida:** `11` y `5`.
   * **qué aspecto valida:** La operación de partición (split). El nodo se divide y acota correctamente, reinsertando los nuevos intervalos invertidos sin romper el árbol.

5. **Caso comparado contra una solución ingenua (Invariante principal):**
   * **entrada usada:** Operación masiva en el límite de Codeforces añadiendo el rango `[1, 1000000000000000000]`.
   * **salida esperada:** `1000000000000000001`
   * **salida obtenida:** `1000000000000000001`
   * **qué aspecto valida:** El Treap procesa un rango masivo en tiempo $O(1)$ amortizado creando un solo nodo, previniendo el Time Limit Exceeded (TLE) y Memory Limit Exceeded (MLE) que sufriría irremediablemente una solución ingenua.

#### Evidencia Git

El video inicia mostrando el historial de commits, fechas, archivos modificados y explicación del proceso real de desarrollo a lo largo de 5 días.

Comandos obligatorios verificables en el video:

```bash
git status
git log --date=short --pretty=format:"%ad - %h - %an - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
git log --graph --oneline --decorate --all
git log --date=short --name-status --pretty=format:"%ad - %h - %s" -- Semana4 Semana5 Semana6 Practicas practica-calificada3
git log --date=short --stat --pretty=format:"%ad - %h - %s"
```

El estudiante explica en el video:

- Qué commits corresponden a actividades de clase y cuáles a la práctica calificada.

- Los archivos que cambiaron, las pruebas que se agregaron y los errores que se corrigieron.

- Por qué el historial demuestra un trabajo progresivo durante 5 días, descartando un historial prefabricado al final.

#### Preguntas obligatorias

Se responde de forma explícita a las preguntas comunes, a las preguntas específicas del problema Codeforces 817F, a la relación con Semanas 4-6, el invariante, la complejidad, los casos borde y la modificación grabada. Toda esta información se encuentra detallada exhaustivamente en el archivo de respuestas obligatorias.

#### Bitácora obligatoria

El resumen del proceso real de desarrollo día por día se encuentra en el archivo:

`docs/bitacora.md`

La bitácora resume el día de avance, problema trabajado, estructura implementada, errores encontrados, pruebas agregadas, cambios importantes y la relación con los commits.

#### Respuestas obligatorias

El archivo con el cuestionario técnico resuelto (preguntas comunes y específicas del problema asignado), con respuestas claras y numeradas, se encuentra en:

`docs/respuestas_obligatorias.md`

#### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación. También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.