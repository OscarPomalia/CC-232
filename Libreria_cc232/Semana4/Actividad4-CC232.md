### Actividad 4 - Semana 4

- Duración: 3 horas de clase.
- Modalidad: Trabajo individual.
- Tiempo de instalación: 15 minutos al inicio.
- Entrega: Un archivo llamado `Actividad4-CC232.md`.

#### Objetivo

Consolidar lo trabajado en la Semana 4 a partir de código, demos, pruebas, experimentos y una defensa escrita breve.

La meta es distinguir con claridad cómo `Stack` y `Queue` dejan de ser solo estructuras lineales y pasan a funcionar como herramientas algorítmicas para resolver problemas de conversión de base, verificación de paréntesis, evaluación de expresiones, búsqueda con retroceso y simulación.

Además, se busca comparar explícitamente enfoques recursivos e iterativos, justificar qué información guarda cada estructura auxiliar, defender por qué una pila explícita puede reemplazar recursión implícita, y analizar cómo pequeñas decisiones de diseño cambian el comportamiento observable en N-Reinas, laberintos y simulación bancaria.

#### Material de trabajo

##### Código de la semana

- `Semana4/README.md`
- `Semana4/CMakeLists.txt`
- `Semana4/include/Stack.h`
- `Semana4/include/Queue.h`
- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/include/OperatorPriority.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/include/Queen.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/include/BankSimulation.h`
- `Semana4/include/Capitulo4.h`
- `Semana4/demos/demo_stack_queue.cpp`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/demos/demo_capitulo4_panorama.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`
- `Semana4/Ejercicios4-CC232.md`

#### Lecturas obligatorias

- Capítulo 4 de Deng: pilas, colas y aplicaciones.
- README de la Semana 4.

#### Bloque 0 - Instalación y preparación

1. Deja lista tu carpeta de trabajo.
2. Verifica que puedes abrir `Semana4`, las lecturas y el archivo de entrega.
3. Crea el archivo `Actividad4-CC232.md`.
4. Anota tu nombre completo.
5. Compila y ejecuta al menos una demostración y una prueba pública de Semana 4.

#### Bloque 1 - Núcleo conceptual de la semana

Revisa:

- `Semana4/README.md`
- `Semana4/include/Stack.h`
- `Semana4/include/Queue.h`
- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/include/BankSimulation.h`
- Capítulo 4 de Deng.

Responde:

1. Explica con tus palabras la diferencia entre acceso `LIFO` y acceso `FIFO`.
2. Explica por qué `Stack` resuelve naturalmente problemas donde importa "lo último pendiente".
3. Explica por qué `Queue` modela naturalmente procesos de espera y atención.
4. Explica qué significa reemplazar recursión implícita por una estructura explícita.
5. Explica qué información mínima debe guardarse para que una pila permita reconstruir una solución parcial.
6. Compara la conversión de base recursiva e iterativa: ¿qué comparten y qué cambia en el control del proceso?
7. Explica por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes.
8. Explica por qué el evaluador de expresiones necesita dos pilas y no una sola.
9. Explica por qué N-Reinas y laberinto son ejemplos naturales de backtracking.
10. Explica por qué la simulación bancaria no se modela bien con pila, pero sí con colas.
11. Explica qué relación hay entre estructura auxiliar, estado parcial y correctitud.
12. Explica qué diferencia conceptual hay entre "resolver un problema" y "simular un proceso".

#### Bloque 2 - Demostración y trazado guiado

Revisa:

- `Semana4/demos/demo_stack_queue.cpp`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/demos/demo_capitulo4_panorama.cpp`

Construye una tabla con cuatro columnas:

- Archivo
- Salida u observable importante
- Estructura o técnica central
- Qué concepto permite defender

Luego responde:

1. En `demo_stack_queue.cpp`, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?
2. En `demo_base_conversion.cpp`, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?
3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?
4. En `demo_nqueens.cpp`, ¿qué significan `solutions` y `checks`, y por qué no miden lo mismo?
5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?
6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante `t`?
7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?

#### Bloque 3 - Pruebas públicas, pruebas internas y correctitud

Revisa:

- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. ¿Qué operaciones mínimas valida la prueba pública para `Stack`?
2. ¿Qué operaciones mínimas valida la prueba pública para `Queue`?
3. ¿Qué valida la prueba pública sobre conversión de base?
4. ¿Qué valida la prueba pública sobre paréntesis balanceados?
5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?
6. ¿Qué valida la prueba pública sobre `NQueens`?
7. ¿Qué valida la prueba pública sobre `Maze`?
8. ¿Qué valida la prueba pública sobre `bestWindow` en la simulación bancaria?
9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?
10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?
11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos.

#### Bloque 4 - Comparación recursivo vs iterativo

Revisa:

- `Semana4/include/BaseConversion.h`
- `Semana4/include/Parentheses.h`
- `Semana4/demos/demo_base_conversion.cpp`
- `Semana4/demos/demo_paren_rpn.cpp`

Responde:

1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?
2. ¿Por qué los residuos se apilan antes de formar la cadena final?
3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?
4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?
5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen `[]` y `{}`?
6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?
7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?

##### Experimento 1

Ejecuta pruebas propias con al menos cinco números y cuatro bases distintas para `toBaseRecursive` y `toBaseIterative`.

Registra en una tabla:

- Número
- Base
- Salida recursiva
- Salida iterativa
- ¿Coinciden?
- Comentario

##### Experimento 2

Construye una batería de al menos ocho expresiones para paréntesis, incluyendo:

- una vacía,
- una sin paréntesis,
- una correctamente anidada,
- una con desbalance,
- una con cruce incorrecto,
- una con varios tipos de delimitadores,
- una larga,
- una inventada por ti.

Para cada caso indica:

- resultado recursivo,
- resultado iterativo,
- si ambos coinciden,
- qué explica el caso.

#### Bloque 5 - Evaluación de expresiones y prioridad de operadores

Revisa:

- `Semana4/include/OperatorPriority.h`
- `Semana4/include/ExpressionEvaluator.h`
- `Semana4/demos/demo_paren_rpn.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. Explica qué información guarda `EvaluationResult`.
2. Explica por qué primero se eliminan espacios.
3. Explica cómo se detecta el signo menos unario.
4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código.
5. Explica cómo la RPN se va construyendo durante la evaluación y no al final.
6. Explica qué significa la relación entre operador del tope y símbolo actual.
7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario.
8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?

##### Experimento 3

Propón y ejecuta al menos seis expresiones nuevas:

- dos válidas sin paréntesis,
- dos válidas con anidamiento,
- una con menos unario,
- una inválida.

Para cada una registra:

- expresión,
- RPN esperada,
- RPN obtenida,
- valor esperado u error esperado,
- valor obtenido o error observado,
- explicación breve.

##### Extensión opcional

Extiende el evaluador con un operador adicional elegido por ti.

La defensa debe incluir obligatoriamente:

- qué símbolo agregaste,
- su aridad,
- su prioridad,
- qué casos válidos probaste,
- qué caso inválido probaste,
- qué parte del código tuviste que modificar.

#### Bloque 6 - Backtracking explícito: N-Reinas y laberinto

Revisa:

- `Semana4/include/Queen.h`
- `Semana4/include/NQueens.h`
- `Semana4/include/Maze.h`
- `Semana4/demos/demo_nqueens.cpp`
- `Semana4/demos/demo_maze.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?
2. En `NQueens`, ¿qué representa exactamente la pila `solution`?
3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?
4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?
5. ¿Qué cambia cuando `collectPlacements` vale `false`?
6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?
7. ¿Qué información codifican `incoming` y `outgoing`?
8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?
9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?

##### Experimento 4

Ejecuta `placeQueens(n)` para al menos cuatro valores de `n`.

Registra en una tabla:

- `n`
- número de soluciones
- número de `checks`
- ¿crece rápido o lento?
- comentario

Luego responde:

1. ¿Qué patrón observas en el crecimiento de `checks`?
2. ¿Por qué contar verificaciones no es lo mismo que contar soluciones?
3. ¿Dónde aparece la "poda" en este código, aunque no haya una estructura formal con ese nombre?

##### Experimento 5

Diseña al menos tres laberintos propios:

- uno con camino claro,
- uno sin salida,
- uno donde el algoritmo deba retroceder varias veces.

Para cada laberinto registra:

- grilla usada,
- coordenadas de inicio y destino,
- longitud del camino o ausencia de camino,
- evidencia de retroceso,
- interpretación.

#### Bloque 7 - Simulación bancaria y experimentación con colas

Revisa:

- `Semana4/include/Queue.h`
- `Semana4/include/BankSimulation.h`
- `Semana4/demos/demo_bank.cpp`
- `Semana4/pruebas_publicas/test_public_week4.cpp`
- `Semana4/pruebas_internas/test_internal_week4.cpp`

Responde:

1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?
2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?
3. ¿Qué significa que la simulación use una semilla (`seed`)?
4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?
5. ¿Qué representa la línea de tiempo (`timeline`) en el resultado?
6. ¿Por qué esta aplicación necesita colas y no pilas?
7. ¿Qué simplificación del mundo real introduce este simulador?
8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?

##### Experimento 6

Ejecuta la simulación variando al menos tres parámetros:

- número de ventanillas,
- duración total,
- semilla.

Construye una tabla con:

- `nWin`
- `servTime`
- `seed`
- `totalArrivals`
- `totalServed`
- tamaño final de cada cola
- observación

Luego responde:

1. ¿Qué parámetro parece influir más en la congestión observable?
2. ¿Qué cambia cuando repites exactamente la misma semilla?
3. ¿Qué cambia cuando mantienes `nWin` y `servTime`, pero alteras la semilla?
4. ¿Qué evidencia usarías para defender que la cola más corta es una política razonable, aunque no necesariamente óptima?

#### Bloque 8 - Cierre comparativo y preparación de sustentación

Responde esta pregunta final:

**¿Qué cambia cuando pasamos de "usar pilas y colas como ADTs básicos" a "usarlas como mecanismos de control para resolver problemas"?**

La respuesta debe incluir obligatoriamente:

- una afirmación sobre `LIFO` y `FIFO`,
- una afirmación sobre recursión implícita frente a estructura explícita,
- una afirmación sobre evaluación de expresiones,
- una afirmación sobre backtracking,
- una afirmación sobre simulación,
- una afirmación sobre correctitud experimental,
- una comparación entre conversión de base, paréntesis, N-Reinas, laberinto y banco.

#### Formato sugerido de entrega

```md
## Actividad 4-CC232

### Estudiante
- Nombre completo

#### Bloque 1 (respuestas)
#### Bloque 2 (tabla y respuestas)
#### Bloque 3 (respuestas)
#### Bloque 4 (respuestas y experimentos 1-2)
#### Bloque 5 (respuestas y experimento 3)
#### Bloque 6 (respuestas y experimentos 4-5)
#### Bloque 7 (respuestas y experimento 6)
#### Bloque 8 (respuesta final)

#### Autoevaluación breve
- Qué puedo defender con seguridad:
- Qué todavía confundo:
- Qué experimento me dio mejor evidencia:
- Qué evidencia usaría en una sustentación:
```

#### Criterio general de trabajo

Se espera lectura real de los archivos, respuestas breves pero justificadas, y conexión explícita entre código, correctitud, estado, estructuras auxiliares, recursión, backtracking, simulación y evidencia experimental.

No basta con ejecutar el programa: debes poder explicar por qué funciona, qué información mantiene cada estructura, qué decisión toma el algoritmo en cada paso y qué evidencia experimental respalda tu defensa.
