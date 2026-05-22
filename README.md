### CC232 - Algoritmos y Estructuras de Datos

Repositorio público del curso **CC232 - Algoritmos y Estructuras de Datos**.

Este curso introduce y desarrolla, con un enfoque riguroso de Ciencia de la Computación, las estructuras de datos fundamentales y modernas que permiten diseñar software eficiente, correcto y mantenible. El énfasis del curso no está solo en "usar" estructuras, sino en **modelarlas, implementarlas, analizarlas y defender técnicamente por qué una representación es adecuada para un problema dado**.

> **Lenguaje principal del curso:** C++17  
> **Lenguaje auxiliar:** Python (solo para prototipos cortos, trazas o validaciones puntuales)

#### Descripción del curso

Asignatura teórico-práctica orientada al diseño, análisis, implementación y evaluación rigurosa de estructuras de datos fundamentales para la Ciencia de la Computación. El curso cubre complejidad asintótica, tipos abstractos de datos, análisis amortizado, estructuras lineales, árboles, colas de prioridad, diccionarios, hashing, grafos, estructuras probabilísticas y estructuras avanzadas para consultas eficientes.

A lo largo del curso se enfatiza la relación entre:

- representación de datos
- complejidad temporal y espacial
- localidad de memoria
- calidad de implementación
- correctitud e invariantes
- defensa oral de decisiones de diseño.

#### Competencia del curso

Diseñar, implementar, analizar y sustentar estructuras de datos adecuadas para resolver problemas computacionales no triviales, justificando formalmente su correctitud, complejidad y pertinencia práctica.

#### Resultados de aprendizaje

Al finalizar el curso, el estudiante deberá ser capaz de:

1. Modelar problemas mediante **tipos abstractos de datos (ADT)** y elegir representaciones adecuadas.
2. Implementar en **C++17** estructuras fundamentales sin depender ciegamente de bibliotecas de alto nivel.
3. Explicar invariantes, precondiciones, postcondiciones y argumentos básicos de correctitud.
4. Analizar complejidad temporal y espacial en peor caso, caso amortizado y caso esperado.
5. Comparar estructuras considerando tiempo, espacio, localidad de memoria y mantenibilidad.
6. Sustentar oralmente decisiones de diseño e implementación.
7. Llegar con base sólida para cursos posteriores, especialmente en análisis de algoritmos y sistemas.

#### Prerrequisitos esperados

Se asume que el estudiante llega con bases razonables en:

- programación previa
- programación orientada a objetos
- matemática discreta
- razonamiento lógico
- nociones básicas de memoria y arquitectura de computadores.

#### Enfoque metodológico

El curso se desarrolla con una combinación de:

- teoría rigurosa
- implementación disciplinada
- laboratorios y experimentación
- análisis de correctitud y complejidad
- defensas orales breves
- lectura previa obligatoria.

La intención es que el estudiante no solo logre que el código "funcione", sino que pueda **explicar por qué funciona, cuánto cuesta, qué compromisos de diseño tomó y cuándo conviene usar una estructura frente a otra**.


#### Contenido general

##### Unidad I - Fundamentos, secuencias y estructuras lineales
- Complejidad asintótica
- Modelo de costo
- Tipos abstractos de datos
- Análisis amortizado
- Arreglos dinámicos
- Listas enlazadas
- Pilas, colas y deques

##### Unidad II - Árboles, diccionarios y prioridades
- Recursión
- Árboles binarios
- Recorridos y serialización
- Colas de prioridad
- Heaps
- Árboles binarios de búsqueda
- Hashing
- Árboles AVL

#### Unidad III - Grafos y estructuras avanzadas
- Representación de grafos
- BFS y DFS
- Orden topológico
- Disjoint Set Union
- Skiplist
- Sorting y benchmarking

#### Unidad IV - Estructuras modernas, memoria externa e integración
- Trie
- Fenwick Tree
- Segment Tree
- B-Tree
- Selección de estructuras
- Benchmarking final
- Integración del curso

#### Programación semanal

## Cronograma del curso

| Semana | Tema central | Resultado esperado |
|---|---|---|
| 1 | Presentación del curso, prueba de entrada, modelo RAM, notación asintótica, ADT, correctitud básica e invariantes | Distingue problema, ADT, estructura de datos e implementación, y comprende el estándar de trabajo del curso. |
| 2 | Arreglos dinámicos, memoria contigua, vectores, *resizing* y análisis amortizado | Explica el funcionamiento del arreglo dinámico y justifica su eficiencia amortizada. |
| 3 | Listas enlazadas, pilas, colas y deques | Implementa estructuras lineales y compara representaciones enlazadas y contiguas. |
| 4 | Recursión, árboles binarios, recorridos, serialización y árboles de expresión | Domina recorridos de árboles y explica su correctitud recursiva. |
| 5 | Colas de prioridad, *heaps* y árboles binarios de búsqueda | Distingue estructuras orientadas a prioridad de estructuras orientadas a búsqueda ordenada. |
| 6 | *Hashing*, *chaining*, *open addressing*, factor de carga y *rehashing* | Analiza el rendimiento esperado y la degradación causada por colisiones. |
| 7 | Árboles AVL, rotaciones, rebalanceo y repaso | Justifica la necesidad de mantener altura logarítmica en estructuras de búsqueda. |
| 8 | Examen parcial | Integra y evalúa los contenidos del primer bloque del curso. |
| 9 | Representación de grafos, BFS, DFS y orden topológico | Selecciona representaciones adecuadas según densidad, operaciones y costo. |
| 10 | Disjoint Set Union y *skiplist* | Compara enfoques de balanceo probabilístico y determinista. |
| 11 | *Sorting*, cotas inferiores y *benchmarking* | Relaciona teoría, estabilidad y rendimiento empírico de los algoritmos de ordenamiento. |
| 12 | Trie y Fenwick Tree | Distingue diccionarios generales de estructuras especializadas para consultas eficientes. |
| 13 | Segment Tree y B-Tree | Diferencia estructuras diseñadas para memoria principal y memoria externa. |
| 14 | Selección de estructuras, *benchmarking* final e integración | Justifica decisiones de diseño según operaciones, memoria y mantenibilidad. |
| 15 | Integración final y cierre conceptual | Sintetiza los contenidos del curso y los conecta con asignaturas posteriores. |
| 16 | Examen final | Integra y evalúa todos los contenidos del curso. |
| 17 | Examen sustitutorio | Se desarrolla según la normativa institucional vigente. |

#### Sistema de evaluación

El curso considera:

- **5 prácticas calificadas**
- **1 examen parcial**
- **1 examen final**

Fórmula general:

```text
PP = promedio(C1, C2, C3, C4, C5), se elimina la menor nota.
PF = (PP + EP + EF)/3
```

Criterios sugeridos para una práctica calificable:

- Sustentación oral individual: **40%**
- Implementación y calidad técnica: **30%**
- Correctitud, invariantes y análisis: **20%**
- Pruebas y casos borde: **10%**

> En un entorno académico contemporáneo, con uso amplio de herramientas automáticas, el curso prioriza la comprensión real, la autoría verificable y la capacidad de argumentar decisiones técnicas.

#### Bibliografía principal

##### Base del curso
- **Deng Junhui** - *Data Structure (C++ Language Edition), 3rd Edition*  
  https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/
- **Pat Morin** - *Open Data Structures (in C++)*  
  https://opendatastructures.org/
- **Dasgupta, Papadimitriou, Vazirani (DPV)** - *Algorithms*  
  https://cs170.org/
- **Daniel Zingaro** - *Algorithmic Thinking, A Problem-Based Introduction*  
  https://www.danielzingaro.com/alg2/

##### Referencias complementarias
- **CLRS** - *Introduction to Algorithms*  
- **Kleinberg & Tardos** - *Algorithm Design*  
- **MIT OCW 6.006** - *Introduction to Algorithms*  
  https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/
- **Princeton Algorithms / algs4**  
  https://algs4.cs.princeton.edu/
- **cp-algorithms**  
  https://cp-algorithms.com/
- **USACO Guide**  
  https://usaco.guide/
- **CSES Problem Set**  
  https://cses.fi/problemset/

#### Recomendaciones de uso para estudiantes

1. Revisar primero el `README.md` general.
2. Leer la carpeta de la semana correspondiente antes de la sesión.
3. Compilar y ejecutar ejemplos base antes del laboratorio.
4. Resolver ejercicios con atención a invariantes, casos borde y costo asintótico.
5. Usar las pruebas públicas como validación mínima, no como criterio único de correctitud.
6. Prepararse para explicar oralmente decisiones de implementación.

#### Estándar esperado de implementación

En este curso se espera que el código:

- tenga nombres claros
- mantenga invariantes explícitos
- contemple casos borde
- se acompañe de pruebas mínimas
- justifique costos temporales y espaciales
- diferencie interfaz, representación y operaciones.

La meta no es solo escribir código funcional, sino producir implementaciones que puedan ser **explicadas, defendidas y mantenidas**.

#### Integridad académica

Este repositorio puede contener material público, esqueletos y pruebas visibles, pero eso no reemplaza el trabajo individual del estudiante. El curso prioriza la comprensión real del contenido y la capacidad de sustentar decisiones técnicas con claridad.

Toda reutilización de código, ideas o material externo debe hacerse con criterio académico, honestidad intelectual y comprensión efectiva de lo entregado.

#### Relación con cursos posteriores

CC232 sirve como base rigurosa para cursos posteriores del eje teórico y de sistemas, en particular aquellos relacionados con:

- análisis y diseño de algoritmos
- teoría de la computación
- sistemas de software
- optimización de implementaciones
- programación competitiva con criterio formal
- ingeniería de software con énfasis en eficiencia y correctitud.


**CC232** es un curso de estructuras de datos con enfoque serio en modelado, implementación, análisis, benchmarking y defensa técnica. Este rreflejar ese estándar en una forma pública, ordenada y reutilizable para docencia, estudio y referencia.
