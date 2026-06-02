### Práctica Calificada 3 CC232

**Curso:** CC232  
**Modalidad:** Individual  
**Formato de evaluación:** video + repositorio + evidencia de compilación, ejecución, pruebas, historial Git y modificación grabada  
**Nota:** sobre 20  
**Entrega:** **12 de Junio del 2026 hasta las 8:00 a.m**  
**Archivo oficial de asignación:**  
`https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv`

La entrega debe incluir la dirección del repositorio personal donde se encuentre esta evaluación.

### 1. Enfoque de la práctica

Esta práctica no evalúa solamente si el programa obtiene una respuesta correcta en un juez en línea. Evalúa si el estudiante comprende, implementa, adapta, prueba y defiende una estructura de datos vinculada con las Semanas 4, 5 y 6 de la librería `cc232`.

El estudiante debe demostrar cómo su solución se apoya en una estructura estudiada o extendida desde la librería del curso.

#### Relación con las semanas evaluadas

| Semana | Estructuras y conceptos evaluables |
|---|---|
| Semana 4 | `Stack`, `Queue`, deques, pilas monotónicas, colas monotónicas, simulación, estados e invariantes de estructuras lineales |
| Semana 5 | árboles binarios, BST, búsqueda ordenada, predecessor/successor, rotaciones, árboles aumentados, intervalos |
| Semana 6 | `BinaryHeap`, `PQ`, heaps mínimo/máximo, `heapify`, heaps mezclables, Huffman, Treap, orden estadístico, lazy deletion |

Si un problema requiere una técnica adicional, esta debe explicarse como una extensión natural de esas semanas. Por ejemplo, un problema de intervalos debe conectarse con BST/Treap, un problema de mediana dinámica debe conectarse con heaps o Treap, un problema de ranking dinámico debe conectarse con árboles ordenados, un problema de frontera mínima debe conectarse con priority queue.

### 2. Estructura sugerida del trabajo

```text
Practica_Calificada3-CC232/
├── README.md
├── CMakeLists.txt
├── include/
├── src/
├── demos/
├── tests/
├── resultados/
├── benchmark/
├── docs/
└── video/
```

También debe observarse evidencia de trabajo previo de clase:

```text
Repositorio-personal/
├── Semana4/
│   └── Actividad4-CC232/
├── Semana5/
│   └── Actividad5-CC232/
├── Semana6/
│   └── Actividad6-CC232/
└── Practicas/
    └── practica-calificada3/
```
>Indica en tu entrega la ubicación de tu trabajo.

### 3. Reglas centrales de autoría

#### 3.1 Trabajo individual

La práctica es estrictamente individual. Cada estudiante debe resolver el problema asignado en el CSV oficial y debe verificar que el problema, el enlace, el README, el video y el repositorio coincidan.

#### 3.2 Uso de la librería del curso

El estudiante debe reutilizar o extender al menos una estructura o idea de `Libreria_cc232/Semana4`, `Semana5` o `Semana6`.

Se permite usar estructuras estándar solo como apoyo secundario. No se acepta que la estructura central del problema sea una caja negra no explicada.

No se acepta como solución suficiente:

- usar `std::set`, `std::multiset`, `std::map`, `std::priority_queue` o PBDS sin explicar la estructura equivalente,
- copiar una solución de juez online y solo cambiar nombres,
- presentar código generado automáticamente sin comprensión verificable,
- usar una biblioteca externa que oculte la estructura central.

Si usa una estructura estándar, debes explicar cómo implementaría la parte central con la librería `cc232` o con una extensión propia.

#### 3.3 Cabeceras permitidas

Solo se permite el uso de archivos de cabecera `.h`.

**El uso de `.hpp`, `.hh`, `.hxx` u otras variantes implica nota 01, salvo que el docente indique explícitamente una excepción antes de la entrega.**

#### 3.4 Entrega fuera de plazo

No se permiten entregas tardías.

- Entrega después de **12 de Junio del 2026 a las 8:30 am** -> **NP**.
- No se revisará el repositorio ni el video.

#### 3.5 Repositorio accesible y URL válida

El enlace del repositorio entregado debe funcionar al momento de la revisión. El repositorio debe estar público o debe haber sido compartido con los permisos necesarios antes de la fecha y hora de entrega.

Se considera URL inválida o entrega no verificable cualquiera de estos casos:

- enlace que no abre,
- repositorio privado sin acceso para revisión,
- repositorio vacío,
- rama principal inexistente o sin el trabajo de la práctica,
- enlace a una carpeta, commit, release o archivo que no contiene la práctica,
- repositorio eliminado, renombrado o movido después de entregar,
- URL que no coincide con el README, el video o el problema asignado.

**Si el repositorio no puede verse o clonarse desde el enlace entregado, la práctica se considera no verificable. En ese caso la calificación será NP o 01, según el criterio administrativo del curso, porque no existe evidencia revisable del trabajo. No se aceptarán correcciones posteriores del enlace.**

#### 3.6 Repositorio limpio: prohibido subir builds, ejecutables y archivos generados

El repositorio debe contener código fuente, pruebas, documentación y evidencias textuales reproducibles. No debe usarse el repositorio como carpeta de compilación ni como depósito de binarios.

No se permite versionar como parte de la entrega:

- carpetas `build/`, `cmake-build-*`, `Debug/`, `Release/`, `x64/`, `bin/` generadas automáticamente,
- ejecutables `.exe`, `.out`, `.app`, binarios sin extensión o programas compilados,
- archivos objeto o bibliotecas compiladas: `.o`, `.obj`, `.a`, `.so`, `.dll`, `.dylib`, `.lib`,
- archivos generados por CMake o compiladores: `CMakeFiles/`, `CMakeCache.txt`, `cmake_install.cmake`, `Makefile` generado dentro de `build/`,
- carpetas y basura de ejecución: `__pycache__/`, `.pytest_cache/`, `.vscode/`, `.idea/`, `.DS_Store`, temporales y logs masivos,
- capturas o archivos pesados que intenten reemplazar la compilación reproducible.

El repositorio debe incluir un `.gitignore` coherente para evitar estos archivos.

**Si se suben builds, ejecutables o binarios generados, la nota máxima total será 08. Si el repositorio depende de esos binarios para funcionar, no puede compilar desde una copia limpia o no permite verificar el código fuente real, la calificación será 01.**

#### 3.7 Obligación de responder lo pedido, no lo que el estudiante desea explicar

Las preguntas comunes, preguntas específicas y retos grabados son obligatorios. No basta con describir el código de forma general, leer el README o narrar lo que hace cada archivo.

El estudiante debe responder además explícitamente lo solicitado:

- estructura usada,
- invariante,
- complejidad por operación y total,
- casos borde,
- relación con Semanas 4, 5 y 6,
- operaciones críticas del código,
- pruebas realizadas,
- reto específico de su problema.

**Si el estudiante evita las preguntas obligatorias, responde algo distinto, se limita a describir código o no conecta sus respuestas con funciones concretas del repositorio, la nota máxima total será 08. Si además hay indicios de generación automática o copia, la calificación será 01.**

#### 3.8 Reiteración de conductas ya advertidas

Las siguientes conductas se consideran reiteradas y no serán tratadas como errores menores:

- entregar repositorios con builds, ejecutables o basura de compilación,
- no responder las preguntas obligatorias,
- entregar repositorios cuyo enlace no funciona,
- no realizar actividades previas de clase,
- presentar código que parece generado o copiado y no demostrar comprensión en el video,
- trabajar casi todo al final sin historial técnico real.

**Cuando aparezcan dos o más de estas conductas en una misma entrega, se aplicará el tope más severo correspondiente. Si la combinación impide verificar autoría, comprensión o reproducibilidad, la calificación será 01.**

### 4. Video obligatorio

El video debe durar entre **25 y 35 minutos**.

| Bloque | Duración sugerida | Contenido |
|---|---:|---|
| 1. Evidencia Git y proceso real | 4-5 min | Debe aparecer al inicio |
| 2. Problema y repositorio | 2-3 min | Problema asignado, enlace oficial, estructura del repo |
| 3. Explicación conceptual | 7-8 min | estructura, invariante, complejidad, casos borde |
| 4. Recorrido técnico del código | 5-6 min | funciones críticas, estado interno, operaciones |
| 5. Compilación, ejecución y pruebas | 3-4 min | build limpio, ejecución, casos propios |
| 6. Modificación/codificación sin cortes | 5-6 min | cambio real, recompilación y validación |

El video debe empezar obligatoriamente con el bloque de evidencia Git. No debe dejarse para el final.

#### 4.1 Regla clave: no habrá evaluación oral posterior

La evaluación se realizará únicamente con base en:

- el video entregado,
- el repositorio entregado,
- el historial Git,
- el `README.md`,
- `docs/respuestas_obligatorias.md`,
- `docs/bitacora.md`,
- los tests, resultados y evidencias reproducibles.

No se tomará una evaluación oral posterior. Por lo tanto, todo lo que el estudiante no explique, no compile, no ejecute, no pruebe o no modifique dentro del video y del repositorio se considerará evidencia ausente.

#### 4.2 Archivo obligatorio de respuestas

El repositorio debe incluir:

```text
docs/respuestas_obligatorias.md
```

Este archivo debe responder, con texto propio y vinculado al código, las preguntas comunes y las preguntas específicas del problema asignado. No se aceptan respuestas genéricas, copiadas del enunciado o desconectadas de funciones concretas del repositorio.

**Si el archivo no existe, está incompleto o no coincide con el video y el código, la nota máxima total será 08.**

#### 4.3 Bitácora obligatoria de desarrollo

El repositorio debe incluir:

```text
docs/bitacora.md
```

La bitácora debe describir el avance por días: lectura del problema, solución inicial, elección de estructura, operaciones implementadas, errores encontrados, pruebas agregadas, refactorizaciones y preparación del bloque de modificación grabada.

**Si la bitácora no existe, no coincide con los commits o parece generada al final sin relación con el código, la nota máxima total será 12. Si además el historial Git es débil o artificial, se aplicará el tope de autoría correspondiente.**

#### 4.4 Evidencia reproducible mínima

Además del video, el repositorio debe contener:

```text
resultados/ejecucion_pc3.txt
resultados/tests_pc3.txt
resultados/casos_borde.txt
```

Estos archivos deben registrar comandos ejecutados, salidas relevantes, pruebas propias y casos borde. La evidencia debe poder reproducirse desde el repositorio.

#### 4.5 Respuestas obligatorias dentro del video y documentos

El video debe mostrar que el estudiante responde las preguntas exigidas. No se aceptará que el estudiante reemplace las preguntas por una exposición libre o por una descripción superficial del código.

La respuesta debe ser verificable en tres lugares:

1. video,
2. `README.md`,
3. `docs/respuestas_obligatorias.md`.

**Si el video no responde las preguntas comunes y específicas, aunque el código compile, la nota máxima total será 08. Si el estudiante solo describe archivos o funciones sin explicar estructura, invariante y complejidad, la nota máxima total será 08. Si además el código muestra indicios de copia o generación automática, la calificación será 01.**

#### 4.6 Evidencia de repositorio limpio en el video

Durante el bloque inicial, el estudiante debe mostrar brevemente que el repositorio no contiene builds ni ejecutables versionados. Puede hacerlo ejecutando, por ejemplo:

```bash
git status
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
cat .gitignore
```

Si el segundo comando no devuelve archivos prohibidos, debe indicarlo. Si devuelve archivos prohibidos, debe explicarlo, sin embargo, la explicación no elimina la penalización si esos archivos forman parte de la entrega.

**La presencia de builds, ejecutables o archivos generados en el historial final se penaliza aunque el programa funcione.**


### 5. Bloque inicial obligatorio de evidencia Git

El estudiante debe ejecutar y explicar desde la raíz del repositorio:

```bash
git status
git log --date=short --pretty=format:"%ad - %h - %an - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
git log --graph --oneline --decorate --all
git log --date=short --name-status --pretty=format:"%ad - %h - %s" -- Semana4 Semana5 Semana6 Practicas practica-calificada3
git log --date=short --stat --pretty=format:"%ad - %h - %s"
```

Debe explicar:

- qué commits corresponden a actividades de clase,
- qué commits corresponden a la práctica calificada,
- en qué fechas hubo avances técnicos reales,
- qué archivos cambiaron,
- qué pruebas, casos borde o refactorizaciones se agregaron,
- por qué el historial no muestra trabajo concentrado artificialmente al final,
- cómo se justifican commits grandes.

#### Requisito mínimo de commits

El repositorio debe mostrar:

- al menos **5 commits**,
- en al menos **5 días diferentes**,
- con mensajes coherentes con el avance técnico.

No son válidos commits vacíos, repetitivos, artificiales o concentrados solo para aparentar trabajo.

#### Tope por falta de evidencia Git

**Si el video no inicia con este bloque, no ejecuta los comandos o no explica el proceso real, la nota máxima total será 05, aunque el programa compile.**

### 6. Actividades previas obligatorias

En el repositorio deben verse completas las actividades de:

- Semana 4,
- Semana 5,
- Semana 6.

**Si no están completas o no se puede verificar su existencia, la nota máxima total será 05.Eso incluye hacerlo fuera de fecha o a última hora**

### 7. Requisitos técnicos mínimos

El repositorio debe permitir:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Si no usa `ctest`, debe justificarlo y ofrecer una forma reproducible de ejecutar pruebas.

#### 7.1 Compilación desde copia limpia

La revisión puede realizarse desde una copia limpia del repositorio. Por tanto, el proyecto debe compilar sin depender de archivos generados previamente.

Comandos esperados:

```bash
git clone <url-del-repositorio>
cd <repositorio>
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

**Si el proyecto solo funciona porque el estudiante subió un ejecutable, una carpeta `build/` o archivos generados, la nota máxima total será 08. Si no puede reconstruirse desde código fuente, la calificación será 01.**

#### 7.2 README no sustituye respuestas obligatorias

El README organiza la entrega, pero no sustituye el archivo `docs/respuestas_obligatorias.md` ni la explicación del video.

**Si el README solo describe el código y no responde lo pedido por la práctica, la nota máxima total será 08.**

El README debe indicar:

- problema asignado,
- enlace oficial,
- estructura usada,
- relación con Semanas 4-6,
- compilación,
- ejecución,
- pruebas,
- complejidad,
- invariante,
- casos borde,
- declaración de autoría.

### 8. Pruebas obligatorias

El estudiante debe incluir al menos:

1. un caso mínimo,
2. un caso con estructura vacía, frontera o ausencia de respuesta,
3. un caso con duplicados o empates, si aplica,
4. un caso extremo pequeño verificable manualmente,
5. una comparación contra solución ingenua para entradas pequeñas, cuando sea razonable,
6. una prueba específica del invariante principal.

**La falta de pruebas limita la nota máxima total a 10.**

### 9. Bloque obligatorio de modificación grabada sin cortes

El estudiante debe hacer una modificación real en el código durante el video, sin cortes visibles.

Debe:

1. modificar código,
2. explicar el cambio,
3. recompilar,
4. ejecutar,
5. mostrar que el cambio funciona,
6. relacionar el cambio con el invariante o la estructura usada.

#### Retos transversales posibles

El estudiante debe resolver al menos **2 retos transversales** y **1 reto específico** de su problema:

1. agregar un caso borde y probarlo,
2. agregar una verificación explícita de invariante,
3. imprimir estado interno útil para depuración,
4. comparar contra una versión ingenua,
5. agregar una prueba aleatoria pequeña,
6. corregir un bug preparado,
7. refactorizar una función grande,
8. agregar un `assert`,
9. cambiar el criterio de desempate,
10. instrumentar una operación crítica: `push`, `pop`, `merge`, `split`, `rotate`, `pull`, `rebalance`, `percolateUp`, `percolateDown` o lazy deletion.

Si no realiza este bloque, la evaluación se considera incompleta y puede recibir **01**.

### 10. Conceptos mínimos que debe poder explicar

El estudiante debe explicar los conceptos que correspondan a su problema. Como mínimo debe cubrir **12 conceptos**, entre ellos obligatoriamente estructura, invariante, complejidad y casos borde.

1. ADT vs implementación concreta  
2. Invariante de estructura  
3. Complejidad por operación  
4. Complejidad total  
5. Complejidad espacial  
6. Peor caso vs costo amortizado  
7. Stack, Queue o deque  
8. Pila o cola monotónica  
9. Heap binario y arreglo implícito  
10. Priority queue y criterio de comparación  
11. `percolateUp`, `percolateDown`, `heapify`  
12. Lazy deletion  
13. BST y propiedad de orden  
14. Predecessor y successor  
15. Rotación izquierda y derecha  
16. Treap como BST por clave y heap por prioridad  
17. Prioridades aleatorias y altura esperada  
18. Árbol aumentado con `size`, `sum`, `max`, `min` o frecuencia  
19. Order statistic tree  
20. Intervalos disjuntos  
21. Barrido de eventos  
22. Estructura de ranking dinámico  
23. Casos borde  
24. Correctitud observable  
25. Separación entre API pública y representación interna  
26. Pruebas contra fuerza bruta

### 11. Preguntas comunes obligatorias

Estas preguntas deben estar respondidas explícitamente en el video, en el `README.md` o en `docs/respuestas_obligatorias.md`. No habrá evaluación oral posterior, por eso, toda la evidencia debe quedar registrada en el video y en el repositorio.

1. ¿Cuál es el problema exacto asignado?  
2. ¿Qué recibe la entrada y qué produce la salida?  
3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?  
4. ¿Cuál sería la solución ingenua y cuál es su complejidad?  
5. ¿Qué estructura de datos elegiste?  
6. ¿Qué estructura de la librería `cc232` se parece más?  
7. ¿Qué operación domina el tiempo?  
8. ¿Qué invariante mantiene tu estructura?  
9. ¿Dónde se actualiza ese invariante en el código?  
10. ¿Qué caso borde puede romper una solución superficial?  
11. ¿Cómo manejas duplicados, empates o elementos obsoletos?  
12. ¿Cuál es la complejidad temporal por operación?  
13. ¿Cuál es la complejidad total?  
14. ¿Cuál es la complejidad espacial?  
15. ¿Qué parte del código sería más fácil de romper?  
16. ¿Qué alternativa de estructura existe y qué perderías con ella?  
17. ¿Qué prueba propia escribiste?  
18. ¿Qué cambiaste durante el bloque sin cortes?  
19. ¿Cómo sabes que el cambio no rompió la solución?  
20. ¿Qué demuestra que no es una solución de caja negra?

**Si el estudiante no puede responder al menos **12 de estas 20 preguntas** y al menos **2 de las 3 preguntas específicas** de su problema, la **nota máxima total será 05**.**

### 12. Preguntas y retos específicos por problema

#### 1. Kattis - Galactic Collegiate Programming Contest

**Enlace oficial:** https://open.kattis.com/problems/gcpc  
**Relación principal:** ranking dinámico, BST/Treap ordenado por tupla  
**Semana de apoyo:** Semana 5

**Debe responder:**

1. ¿Cuál es el criterio exacto de orden entre equipos?
2. ¿Cómo se actualiza el ranking sin reordenar todos los equipos?
3. ¿Qué estructura de la librería se aproxima más a tu solución?

**Reto grabado obligatorio:**  
Agregar una traza que muestre el cambio de posición de tres equipos después de varias actualizaciones.

#### 2. Codeforces 702F - T-Shirts

**Enlace oficial:** https://codeforces.com/problemset/problem/702/F  
**Relación principal:** estructuras ordenadas, procesamiento offline, BST/Treap aumentado  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué se ordena primero y por qué ese orden evita recomputar desde cero?
2. ¿Qué información debe mantener la estructura ordenada?
3. ¿Qué parte de la solución depende de búsquedas, particiones o rangos?

**Reto grabado obligatorio:**  
Agregar una ejecución pequeña con compradores y camisetas ordenados, mostrando el estado de la estructura después de cada grupo.

#### 3. LeetCode 407 - Trapping Rain Water II

**Enlace oficial:** https://leetcode.com/problems/trapping-rain-water-ii/  
**Relación principal:** priority queue, BFS con frontera mínima  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Por qué se usa un min-heap en lugar de una cola simple?
2. ¿Qué representa la frontera actual de celdas procesadas?
3. ¿Qué caso falla si se procesa una celda antes de conocer la menor barrera posible?

**Reto grabado obligatorio:**  
Agregar una matriz pequeña e imprimir el orden de extracción del heap y el agua acumulada por celda.

#### 4. CSES - Sliding Window Cost

**Enlace oficial:** https://cses.fi/problemset/task/1077  
**Relación principal:** mediana dinámica, Treap con suma acumulada o dos estructuras ordenadas  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Por qué la mediana minimiza la suma de distancias absolutas?
2. ¿Dónde se actualiza la suma acumulada de cada lado?
3. ¿Cómo se eliminan correctamente duplicados al mover la ventana?

**Reto grabado obligatorio:**  
Agregar un caso con muchos duplicados y comparar contra una solución lenta O(nk).

#### 5. AtCoder AGC001 F - Wide Swap

**Enlace oficial:** https://atcoder.jp/contests/agc001/tasks/agc001_f  
**Relación principal:** orden dinámico, posiciones, estructura ordenada avanzada  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué relación existe entre el orden de los elementos y la operación permitida?
2. ¿Qué consulta ordenada domina la complejidad?
3. ¿Cómo se puede justificar la solución usando BST/Treap o una estructura aumentada?

**Reto grabado obligatorio:**  
Agregar una entrada pequeña y mostrar paso a paso cómo cambian las posiciones relevantes.

#### 6. AtCoder ABC241 D - Sequence Query

**Enlace oficial:** https://atcoder.jp/contests/abc241/tasks/abc241_d  
**Relación principal:** Treap con duplicados, predecessor, successor, kth  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Cómo manejas valores repetidos?
2. ¿Cómo respondes el k-ésimo menor o mayor relativo a x?
3. ¿Qué operación se rompe si no actualizas size o frecuencia?

**Reto grabado obligatorio:**  
Agregar una prueba con duplicados y consultas que mezclen menor, mayor y ausencia de respuesta.

#### 7. LeetCode 715 - Range Module

**Enlace oficial:** https://leetcode.com/problems/range-module/  
**Relación principal:** BST/Treap de intervalos disjuntos  
**Semana de apoyo:** Semana 5

**Debe responder:**

1. ¿Cómo representas intervalos semiabiertos?
2. ¿Cuándo fusionas dos intervalos?
3. ¿Cómo partes un intervalo durante removeRange?

**Reto grabado obligatorio:**  
Agregar una secuencia add-remove-query que obligue a fusionar y partir intervalos.

#### 8. ICPC World Finals 2025 - A-Skew-ed Reasoning

**Enlace oficial:** https://worldfinals.icpc.global/problems/2025/finals/problems/problemset.pdf  
**Relación principal:** skew heap, heap mezclable, razonamiento sobre merge  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Qué diferencia hay entre skew heap, leftist heap y heap binario completo?
2. ¿Cuál es la operación dominante en un heap mezclable?
3. ¿Qué invariante se conserva durante merge?

**Reto grabado obligatorio:**  
Mostrar una fusión pequeña de heaps e indicar qué nodos cambian de lado.

#### 9. LeetCode 480 - Sliding Window Median

**Enlace oficial:** https://leetcode.com/problems/sliding-window-median/  
**Relación principal:** dos heaps con lazy deletion o Treap con duplicados  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Por qué una eliminación directa en heap es difícil?
2. ¿Qué significa lazy deletion?
3. ¿Cómo se mantiene balanceado el tamaño de ambos lados?

**Reto grabado obligatorio:**  
Agregar un caso con repetidos y valores negativos, imprimiendo el estado lógico de ambos heaps.

#### 10. AtCoder ABC281 E - Least Elements

**Enlace oficial:** https://atcoder.jp/contests/abc281/tasks/abc281_e  
**Relación principal:** suma dinámica de K menores, dos Treaps o dos conjuntos ordenados propios  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué conjunto contiene los K menores?
2. ¿Cuándo se debe mover un elemento entre conjuntos?
3. ¿Dónde se actualiza la suma de los K menores?

**Reto grabado obligatorio:**  
Agregar trazas de inserción y eliminación en una ventana donde cambie el elemento frontera.

#### 11. LeetCode 895 - Maximum Frequency Stack

**Enlace oficial:** https://leetcode.com/problems/maximum-frequency-stack/  
**Relación principal:** pila de frecuencias, prioridad por frecuencia y recencia  
**Semana de apoyo:** Semana 4

**Debe responder:**

1. ¿Qué estructura representa la frecuencia actual?
2. ¿Cómo se resuelve el empate por elemento más reciente?
3. ¿Por qué una priority queue simple puede dejar elementos obsoletos?

**Reto grabado obligatorio:**  
Agregar una operación o prueba que fuerce empates de frecuencia y explique la elección.

#### 12. SPOJ ORDERSET - Order statistic set

**Enlace oficial:** https://www.spoj.com/problems/ORDERSET/  
**Relación principal:** order statistic tree, Treap con rank y kth  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué significa rank(x)?
2. ¿Cómo se implementa kth sin recorrer todo el árbol?
3. ¿Qué cambia si hay elementos repetidos?

**Reto grabado obligatorio:**  
Agregar validación contra un vector ordenado para entradas pequeñas aleatorias.

#### 13. CSES - Salary Queries

**Enlace oficial:** https://cses.fi/problemset/task/1144  
**Relación principal:** conteo dinámico en rango, árbol balanceado aumentado  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué representa una frecuencia almacenada?
2. ¿Cómo actualizas un salario anterior y uno nuevo?
3. ¿Cómo adaptarías la solución a Treap en lugar de Fenwick?

**Reto grabado obligatorio:**  
Agregar un caso con salarios repetidos y actualizar solo uno de ellos.

#### 15. LeetCode 218 - The Skyline Problem

**Enlace oficial:** https://leetcode.com/problems/the-skyline-problem/  
**Relación principal:** sweep line, heap de alturas activas, lazy deletion  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Cómo ordenas eventos que ocurren en la misma coordenada?
2. ¿Por qué el heap puede contener edificios vencidos?
3. ¿Qué invariante mantiene la altura activa máxima?

**Reto grabado obligatorio:**  
Agregar edificios que empiezan y terminan en la misma coordenada y mostrar los puntos críticos.

#### 16. AtCoder ABC308 G - Minimum Xor Pair

**Enlace oficial:** https://atcoder.jp/contests/abc308/tasks/abc308_g  
**Relación principal:** conjunto ordenado, vecinos en orden, mínimo XOR dinámico  
**Semana de apoyo:** Semana 5

**Debe responder:**

1. ¿Por qué el par de XOR mínimo aparece entre vecinos ordenados?
2. ¿Qué cambia al insertar o eliminar un valor?
3. ¿Cómo mantienes candidatos sin recomputar todos los pares?

**Reto grabado obligatorio:**  
Agregar una traza de inserción/eliminación mostrando qué pares vecinos se agregan y retiran.

#### 17. LeetCode 862 - Shortest Subarray with Sum at Least K

**Enlace oficial:** https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/  
**Relación principal:** deque monotónica sobre prefijos  
**Semana de apoyo:** Semana 4

**Debe responder:**

1. ¿Qué representa cada prefijo guardado en la deque?
2. ¿Por qué se eliminan prefijos dominados?
3. ¿Qué caso rompe una solución de ventana clásica con números negativos?

**Reto grabado obligatorio:**  
Agregar una entrada con negativos y mostrar cómo cambia la deque.

#### 18. CSES - List Removals

**Enlace oficial:** https://cses.fi/problemset/task/1749  
**Relación principal:** Treap implícito u order statistic tree  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué significa remover el k-ésimo vivo?
2. ¿Dónde se actualiza size?
3. ¿Por qué una lista o vector directo no basta?

**Reto grabado obligatorio:**  
Agregar una verificación contra vector para n pequeño.

#### 19. LeetCode 871 - Minimum Number of Refueling Stops

**Enlace oficial:** https://leetcode.com/problems/minimum-number-of-refueling-stops/  
**Relación principal:** greedy con max-heap  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Por qué se elige el combustible máximo entre estaciones alcanzables?
2. ¿Qué representa el heap en cada momento?
3. ¿Qué caso falla si se toma combustible en orden de llegada sin prioridad?

**Reto grabado obligatorio:**  
Agregar una traza donde se vean estaciones candidatas y extracciones del heap.

#### 20. CSES - Sliding Window Median

**Enlace oficial:** https://cses.fi/problemset/task/1076  
**Relación principal:** mediana dinámica, dos heaps o Treap  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Cómo se mantiene el elemento medio al mover la ventana?
2. ¿Qué ocurre con duplicados?
3. ¿Qué operación domina el tiempo por ventana?

**Reto grabado obligatorio:**  
Agregar una prueba con k par e impar y explicar qué mediana se usa.

#### 21. Codeforces 19D - Points

**Enlace oficial:** https://codeforces.com/problemset/problem/19/D  
**Relación principal:** estructura ordenada bidimensional, sets/Treaps anidados  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué consulta bidimensional resuelve el problema?
2. ¿Qué estructura se usa por coordenada o por segmento?
3. ¿Cómo se elimina un punto sin dejar estado obsoleto?

**Reto grabado obligatorio:**  
Agregar una entrada pequeña y mostrar la búsqueda del punto candidato paso a paso.

#### 22. Codeforces 817F - MEX Queries

**Enlace oficial:** https://codeforces.com/problemset/problem/817/F  
**Relación principal:** intervalos dinámicos, BST/Treap de rangos, lazy conceptual  
**Semana de apoyo:** Semana 5

**Debe responder:**

1. ¿Cómo representas rangos cubiertos o invertidos?
2. ¿Cómo se obtiene el menor entero positivo ausente?
3. ¿Qué caso rompe una solución que actualiza punto por punto?

**Reto grabado obligatorio:**  
Agregar operaciones que fusionen, partan e inviertan intervalos y mostrar el MEX después de cada una.

#### 23. AtCoder ARC033 C - Data Structure

**Enlace oficial:** https://atcoder.jp/contests/arc033/tasks/arc033_3  
**Relación principal:** Treap con insert, erase y kth  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Cómo se encuentra el k-ésimo usando tamaños de subárbol?
2. ¿Dónde se actualiza size?
3. ¿Qué pasa si el árbol se vuelve degenerado?

**Reto grabado obligatorio:**  
Agregar una función que imprima inorder con size de cada nodo.

#### 24. AtCoder ABC170 E - Smart Infants

**Enlace oficial:** https://atcoder.jp/contests/abc170/tasks/abc170_e  
**Relación principal:** conjuntos por grupo y estructura global de máximos  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué guarda cada grupo?
2. ¿Qué guarda la estructura global?
3. ¿Qué se actualiza cuando un niño cambia de grupo?

**Reto grabado obligatorio:**  
Agregar una traza donde un grupo queda vacío y otro recibe un nuevo máximo.

#### 25. Codeforces 455D - Serega and Fun

**Enlace oficial:** https://codeforces.com/problemset/problem/455/D  
**Relación principal:** deques por bloque, consultas dinámicas, conteos por bloque  
**Semana de apoyo:** Semana 4

**Debe responder:**

1. ¿Por qué una secuencia plana sería lenta?
2. ¿Qué información guarda cada bloque?
3. ¿Cómo se actualizan conteos al mover elementos entre bloques?

**Reto grabado obligatorio:**  
Agregar una prueba pequeña e imprimir bloques antes y después de una operación de rotación.

#### 27. Kattis - Cookie Selection

**Enlace oficial:** https://open.kattis.com/problems/cookieselection  
**Relación principal:** mediana dinámica con dos heaps o Treap  
**Semana de apoyo:** Semana 6

**Debe responder:**

1. ¿Qué heap contiene la mitad inferior?
2. ¿Qué heap contiene la mitad superior?
3. ¿Cómo se reequilibra después de insertar o extraer?

**Reto grabado obligatorio:**  
Agregar una secuencia con extracciones consecutivas de mediana y mostrar ambos heaps.

#### 28. AtCoder ABC287 G - Balance Update Query

**Enlace oficial:** https://atcoder.jp/contests/abc287/tasks/abc287_g  
**Relación principal:** Treap con frecuencias, suma y consulta top-k  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué información aumentada guarda cada nodo?
2. ¿Cómo se actualiza el valor de una carta?
3. ¿Cómo se obtiene la suma de los k mayores?

**Reto grabado obligatorio:**  
Agregar una consulta pequeña y mostrar la ruta tomada para sumar los k mayores.

#### 29. AtCoder ABC306 E - Best Performances

**Enlace oficial:** https://atcoder.jp/contests/abc306/tasks/abc306_e  
**Relación principal:** mantenimiento dinámico de suma de K mayores  
**Semana de apoyo:** Semanas 5-6

**Debe responder:**

1. ¿Qué estructura contiene los K mejores valores?
2. ¿Cuándo se intercambian elementos entre estructuras?
3. ¿Dónde se actualiza la suma final?

**Reto grabado obligatorio:**  
Agregar una actualización que saque un valor del top K y otra que lo vuelva a insertar.


### **13. Rúbrica sobre 20 puntos**

| Criterio | Puntaje |
|---|---:|
| Dominio conceptual: estructura, invariante, complejidad, correctitud | 6 |
| Implementación y adaptación a Semanas 4-6 | 5 |
| Pruebas, casos borde y validación | 3 |
| Modificación/codificación grabada sin cortes | 3 |
| Evidencia Git, proceso real y autoría | 2 |
| README, organización y coherencia con CSV/video/repositorio | 1 |
| **Total** | **20** |

#### **Topes y sanciones**

- **Repositorio inaccesible, URL inválida, repositorio privado sin permiso o enlace que no permite revisar la práctica: NP o 01.**
- **Repositorio vacío, rama incorrecta, carpeta de práctica ausente o problema distinto al CSV oficial: nota máxima 05, si no hay evidencia revisable, NP o 01.**
- **Subir `build/`, ejecutables `.exe`, binarios, objetos, bibliotecas compiladas o archivos generados como parte de la entrega: nota máxima 08.**
- **Proyecto que depende de binarios subidos o no puede reconstruirse desde código fuente en una copia limpia: 01.**
- **No responder las preguntas obligatorias y limitarse a describir el código: nota máxima 08.**
- **Omitir `docs/respuestas_obligatorias.md` o entregarlo con respuestas genéricas/desconectadas del código: nota máxima 08.**
- **Responder lo que el estudiante desea explicar, pero no lo que la práctica pregunta explícitamente: nota máxima 08.**
- **Sin bloque inicial de evidencia Git: nota máxima 05.**
- **Sin actividades 4, 5 y 6 verificables: nota máxima 05.**
- **Sin pruebas propias: nota máxima 10.**
- **Sin modificación grabada: posible 01.**
- **Sin compilación y ejecución visibles: posible 01.**
- **Uso de `.hpp`, `.hh`, `.hxx`: 01.**
- **Inconsistencia grave entre CSV, repositorio, README y video: posible 01.**
- **Código que parece copiado o generado y no puede ser explicado, probado o modificado dentro del video: 01.**
- **Solución aceptada en juez, pero sin conexión con la estructura del curso: nota máxima 08.**
- **Uso de STL/PBDS como caja negra central sin explicación ni alternativa propia: nota máxima 08.**
- **Trabajo concentrado al final, commits artificiales y ausencia de proceso real: nota máxima 05.**
- **Dos o más conductas reiteradas en una misma entrega: se aplica el tope más severo, si impiden verificar autoría o reproducibilidad, 01.**

### 14. Plantilla mínima de README.md

### PC3 - CC232

#### Estudiante

- Nombre:
- Código:
- Problema asignado:
- Enlace oficial:

#### Referencia oficial

- CSV oficial:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6

- Semana principal:
- Estructura usada:
- Estructura de la librería `cc232` relacionada:

#### Resumen de la solución

Explica la idea central de la solución sin copiar el enunciado del juez.  
Debe quedar claro qué problema se resuelve, qué estrategia se usa y por qué la estructura elegida es adecuada.

#### Invariante principal

Describe qué propiedad se mantiene después de cada operación importante.

Ejemplos:

- balance entre dos heaps;
- propiedad de BST;
- propiedad heap;
- tamaño de subárbol actualizado;
- suma acumulada correcta;
- intervalos disjuntos;
- orden estadístico correcto;
- eliminación diferida sin elementos obsoletos visibles.

#### Complejidad

- Tiempo por operación:
- Tiempo total:
- Espacio:

#### Archivos relevantes

Indica qué contiene cada carpeta o archivo importante.

- `include/`
- `src/`
- `tests/`
- `demos/`
- `docs/respuestas_obligatorias.md`
- `docs/bitacora.md`
- `resultados/`

#### Limpieza del repositorio

El repositorio no debe versionar builds, ejecutables ni archivos generados.

No deben aparecer archivos como:

- `build/`
- `cmake-build-*`
- `.exe`
- `.out`
- `.o`
- `.obj`
- `CMakeCache.txt`
- `CMakeFiles/`
- `__pycache__/`

Comando sugerido para verificar archivos generados versionados:

```bash
git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"
```

Si el comando muestra resultados, el estudiante debe explicar por qué existen.  
En general, estos archivos deben eliminarse del repositorio y agregarse al `.gitignore`.

#### Compilación

El proyecto debe compilar desde una copia limpia del repositorio.

```bash
cmake -S . -B build
cmake --build build
```

#### Ejecución

Indica el comando exacto para ejecutar el programa principal.

```bash
./build/nombre_del_programa
```

#### Pruebas

Describe al menos 5 pruebas, incluyendo casos borde.

Cada prueba debe indicar:

- entrada usada;
- salida esperada;
- salida obtenida;
- qué aspecto valida.

Ejemplo de lista mínima:

1. Caso mínimo.
2. Caso con estructura vacía, frontera o ausencia de respuesta.
3. Caso con duplicados o empates.
4. Caso extremo pequeño verificable manualmente.
5. Caso comparado contra una solución ingenua, si aplica.

#### Evidencia Git

El video debe iniciar mostrando el historial de commits, fechas, archivos modificados y explicación del proceso real de desarrollo.

Comandos obligatorios:

```bash
git status
git log --date=short --pretty=format:"%ad - %h - %an - %s"
git log --date=short --pretty=format:"%ad" | sort | uniq -c
git log --graph --oneline --decorate --all
git log --date=short --name-status --pretty=format:"%ad - %h - %s" -- Semana4 Semana5 Semana6 Practicas practica-calificada3
git log --date=short --stat --pretty=format:"%ad - %h - %s"
```

El estudiante debe explicar:

- qué commits corresponden a actividades de clase;
- qué commits corresponden a la práctica calificada;
- qué archivos cambiaron;
- qué pruebas se agregaron;
- qué errores se corrigieron;
- por qué el historial demuestra trabajo progresivo.

#### Preguntas obligatorias

El estudiante debe responder lo que se pide en las preguntas obligatorias.  
No basta con describir el código de forma libre.

Debe responder explícitamente:

- las preguntas comunes;
- las preguntas específicas de su problema;
- la relación con Semanas 4-6;
- el invariante;
- la complejidad;
- los casos borde;
- la modificación grabada.

Si el estudiante omite estas preguntas y solo describe código, la evidencia se considera incompleta.

#### Bitácora obligatoria

Debe existir el archivo:

```text
docs/bitacora.md
```

La bitácora debe resumir el proceso real de desarrollo:

- día de avance;
- problema trabajado;
- estructura implementada;
- errores encontrados;
- pruebas agregadas;
- cambios importantes;
- relación con commits.

#### Respuestas obligatorias

Debe existir el archivo:

```text
docs/respuestas_obligatorias.md
```

Este archivo debe contener respuestas claras y numeradas a las preguntas comunes y específicas del problema asignado.

#### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.  
También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.

### 15. Observación final

La Práctica Calificada 3 está diseñada para reducir respuestas superficiales o copiadas. La evidencia principal no es solo el resultado aceptado por el juez, sino la capacidad de explicar el diseño, sustentar el invariante, justificar la complejidad, mostrar pruebas propias, conectar la solución con Semanas 4-6 y realizar una modificación funcional sin cortes.

*La reiteración de entregas con builds, ejecutables, enlaces inválidos, respuestas omitidas o repositorios no verificables será penalizada de forma estricta. Estas reglas han sido incorporadas porque la práctica evalúa autoría, reproducibilidad y comprensión, no solo la presencia de archivos o una solución aparentemente funcional.*
