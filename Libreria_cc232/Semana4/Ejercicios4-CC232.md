### Lista de ejercicios - Semana 4

#### Ejercicio 1. Variante de `Stack` basada en lista enlazada
En la `semana 4` se trabaja con una implementación de `Stack` y `Queue`, además de varias aplicaciones clásicas de pilas y colas. La carpeta `Semana4/include/Stack.h` sirve como referencia para el comportamiento esperado del ADT pila, pero este ejercicio pide construir una variante con representación enlazada para comparar decisiones de diseño y complejidad.

##### Se pide
1. Revisar la interfaz de `Stack` en `Semana4/include/Stack.h`.
2. Diseñar e implementar una clase `StackList<T>` basada en nodos enlazados simples o dobles.
3. Implementar al menos las operaciones `push(x)`, `pop()`, `top()`, `size()` y `empty()`.
4. Justificar la complejidad temporal de cada operación.
5. Comparar esta implementación con la pila actual basada en almacenamiento contiguo o adaptador estándar.
6. Construir una prueba corta que verifique comportamiento LIFO con enteros y cadenas.

#### Ejercicio 2. Cola propia sobre buffer circular
La `semana 4` incluye `Queue.h` como cola FIFO lista para usar. Sin embargo, una buena forma de consolidar el tema es implementar una cola propia sobre arreglo circular, entendiendo manejo de capacidad, avance modular y diferencia entre frente lógico y posición física.

##### Se pide
1. Revisar la interfaz pública de `Semana4/include/Queue.h`.
2. Diseñar una clase `QueueArray<T>` basada en un arreglo circular.
3. Implementar `enqueue(x)`, `dequeue()`, `front()`, `size()` y `empty()`.
4. Explicar cómo se distinguen los casos de cola vacía y cola llena.
5. Resolver correctamente los casos de envoltura (*wrap-around*) del frente y del final.
6. Justificar la complejidad temporal de las operaciones y discutir cuándo sería necesario redimensionar.

#### Ejercicio 3. Conversión de base: comparación recursiva e iterativa
La `semana 4` incluye `BaseConversion.h`, donde se compara una versión recursiva con una versión iterativa apoyada en pila explícita. Este ejercicio busca que el estudiante no solo ejecute ambas, sino que también compare qué papel cumple la recursión y qué papel cumple la pila.

##### Se pide
1. Revisar `Semana4/include/BaseConversion.h`.
2. Ejecutar conversiones de varios números en bases 2, 8, 10 y 16.
3. Comparar la versión recursiva con la iterativa en claridad, número de pasos y uso de memoria auxiliar.
4. Explicar en qué sentido la pila de llamadas de la versión recursiva cumple un papel análogo a una pila explícita.
5. Proponer una ampliación para soportar bases entre 2 y 36.
6. Diseñar pruebas que cubran casos pequeños, casos grandes y el caso especial `n = 0`.

#### Ejercicio 4. Verificación de paréntesis con diagnóstico de error
La carpeta de la semana incluye `Parentheses.h`, donde se presenta la verificación de paréntesis como aplicación clásica de pilas. El siguiente paso natural es no solo decidir si la cadena es válida, sino también reportar el primer punto de falla.

##### Se pide
1. Revisar `Semana4/include/Parentheses.h`.
2. Extender la verificación iterativa para admitir `()`, `[]` y `{}`.
3. Hacer que la función devuelva además la posición del primer error detectado.
4. Indicar qué símbolo se esperaba cuando ocurra un cierre incorrecto.
5. Probar la rutina con casos de cierre sobrante, apertura sin cerrar, anidamiento correcto y anidamiento incorrecto.
6. Discutir si una verificación por tipos separados de paréntesis sería suficiente o no, justificando tu respuesta.

#### Ejercicio 5. Extensión del verificador a etiquetas tipo HTML
Además del problema clásico de paréntesis, se propone verificar etiquetas emparejadas del tipo `<tag>...</tag>`. Este ejercicio adapta esa idea al como una extensión directa del trabajo hecho en `Parentheses.h`.

##### Se pide
1. Partir de la solución del ejercicio anterior.
2. Implementar una rutina que verifique emparejamiento anidado de etiquetas simples de la forma `<tag>` y `</tag>`.
3. Hacer que el algoritmo use una pila de cadenas en lugar de una pila de caracteres.
4. Detectar y reportar errores de cierre en orden incorrecto o etiquetas faltantes.
5. Preparar ejemplos válidos y no válidos con al menos tres niveles de anidamiento.
6. Explicar qué partes del algoritmo de paréntesis se conservan y cuáles deben cambiar.

#### Ejercicio 6. Evaluador de expresiones: robustez y nuevas operaciones
La `semana 4` incluye `OperatorPriority.h` y `ExpressionEvaluator.h`, donde se implementa la evaluación de expresiones infijas y su conversión a RPN. Este es uno de los núcleos algorítmicos de la semana y conviene reforzarlo con extensiones pequeñas pero conceptualmente importantes.

##### Se pide
1. Revisar `Semana4/include/OperatorPriority.h` y `Semana4/include/ExpressionEvaluator.h`.
2. Explicar el papel de la pila de operandos y de la pila de operadores.
3. Modificar el evaluador para soportar al menos una extensión, por ejemplo `sqrt(x)`, `max(a,b)` o `min(a,b)`.
4. Ajustar el operador `^` para que sea asociativo por la derecha.
5. Mejorar el manejo de errores sintácticos para distinguir paréntesis desbalanceados, operador inválido y operando faltante.
6. Construir una prueba con expresiones correctas y otra con expresiones anómalas.

#### Ejercicio 7. Traza paso a paso del algoritmo `evaluateExpression()`
Entender el evaluador no consiste solo en obtener el resultado final. También es importante observar cómo evolucionan ambas pilas durante el procesamiento de una expresión no trivial.

##### Se pide
1. Elegir una expresión que combine paréntesis, potencia y al menos tres operadores binarios.
2. Mostrar paso a paso el contenido de la pila de operandos y la pila de operadores.
3. Indicar en qué momentos se apila un operador, en qué momentos se desapila y cuándo se genera salida en RPN.
4. Verificar que el resultado final coincide con la evaluación esperada.
5. Redactar una conclusión breve sobre cómo la tabla de precedencias controla el flujo del algoritmo.

#### Ejercicio 8. N-Reinas con pila explícita y métricas de poda
La `semana 4` incluye `Queen.h` y `NQueens.h`, donde se modela el problema de N-Reinas mediante una búsqueda iterativa con retroceso y pila explícita. Este ejercicio busca conectar la implementación con el concepto de backtracking y con el costo real de la exploración.

##### Se pide
1. Revisar `Semana4/include/Queen.h` y `Semana4/include/NQueens.h`.
2. Ejecutar el algoritmo para varios valores de `n`, por ejemplo desde 4 hasta 10.
3. Registrar el número de soluciones y el número de verificaciones realizadas.
4. Explicar en qué momento el algoritmo avanza y en qué momento retrocede.
5. Relacionar la pila explícita del algoritmo con la recursión implícita de una solución recursiva clásica.
6. Presentar una tabla o gráfica simple con los resultados obtenidos.

#### Ejercicio 9. Laberinto: búsqueda con pila versus camino mínimo
La carpeta de la semana incluye `Maze.h`, donde se presenta una búsqueda de ruta basada en pila y retroceso. Este enfoque encuentra una ruta si existe, pero no necesariamente la más corta. Por eso es útil contrastarlo con una búsqueda en anchura basada en cola.

##### Se pide
1. Revisar `Semana4/include/Maze.h`.
2. Explicar cómo la pila representa el camino actual durante la búsqueda.
3. Ejecutar la búsqueda en al menos dos laberintos distintos y reportar la ruta encontrada.
4. Implementar adicionalmente una versión BFS con cola para hallar un camino mínimo.
5. Comparar ambas estrategias en longitud del camino hallado y número de celdas visitadas.
6. Discutir en qué tipo de problema conviene una pila y en cuál conviene una cola.

#### Ejercicio 10. Simulación bancaria con criterio de selección más realista
La `semana 4` incluye `BankSimulation.h`, donde la simulación usa varias colas y una política de selección de ventanilla. Se propone mejorar este tipo de simulación para acercarla más a situaciones reales.

##### Se pide
1. Revisar `Semana4/include/BankSimulation.h`.
2. Identificar cómo se decide actualmente la ventanilla a la que entra un nuevo cliente.
3. Modificar `bestWindow()` para que el criterio sea el tiempo total restante de servicio y no solo el tamaño de la cola.
4. Ejecutar ambas versiones con la misma semilla o con la misma secuencia de llegadas.
5. Comparar tiempo promedio de espera, tiempo máximo de espera y distribución de carga entre ventanillas.
6. Discutir por qué una cola con menos personas puede no ser la mejor opción.

#### Ejercicio 11. `reverse()` para `Stack` y `Queue`
Se propone invertir el orden de una pila y de una cola. Este ejercicio encaja bien con la `Semana 4` porque obliga a razonar solo a partir del ADT y a distinguir claramente entre comportamiento externo y representación interna.

##### Se pide
1. Diseñar una operación `reverse()` para `Stack`.
2. Diseñar una operación `reverse()` para `Queue`.
3. Indicar si tu solución usa recursión, otra estructura auxiliar o solo operaciones del propio ADT.
4. Probar el comportamiento con estructuras vacías, con un solo elemento y con varios elementos.
5. Justificar la complejidad temporal y espacial de cada solución.
6. Comparar cuál de las dos inversiones resulta conceptualmente más directa y por qué.

#### Ejercicio 12. `Deque` como extensión opcional avanzada
Aunque la `semana 4` se centra en pilas y colas, una extensión natural del tema es la cola de doble extremo. Este ejercicio queda como opcional avanzado para quienes quieran extender la semana.

##### Se pide
1. Diseñar una estructura `Deque<T>` con operaciones `insertFront`, `insertRear`, `removeFront`, `removeRear`, `front` y `rear`.
2. Elegir una representación adecuada, por ejemplo lista doblemente enlazada o buffer circular.
3. Justificar la complejidad temporal de cada operación.
4. Construir pruebas con inserciones y eliminaciones por ambos extremos.
5. Dar un ejemplo de aplicación concreta, por ejemplo verificación de palíndromos o mantenimiento de ventanas deslizantes.

#### Indicaciones generales
En todos los ejercicios:

* Justifica tus respuestas.
* Usa notación asintótica cuando corresponda.
* Cuando se pida correctitud, indica con claridad la invariante, el inicio, el mantenimiento y la terminación.
* Distingue entre interfaz y representación interna.
* Apoya tus respuestas en el código de la `semana 4`, especialmente en:
  * `Semana4/include/Stack.h`
  * `Semana4/include/Queue.h`
  * `Semana4/include/BaseConversion.h`
  * `Semana4/include/Parentheses.h`
  * `Semana4/include/OperatorPriority.h`
  * `Semana4/include/ExpressionEvaluator.h`
  * `Semana4/include/Queen.h`
  * `Semana4/include/NQueens.h`
  * `Semana4/include/Maze.h`
  * `Semana4/include/BankSimulation.h`
  * `Semana4/include/Capitulo4.h`
  * `Semana4/demos/demo_stack_queue.cpp`
  * `Semana4/demos/demo_base_conversion.cpp`
  * `Semana4/demos/demo_paren_rpn.cpp`
  * `Semana4/demos/demo_nqueens.cpp`
  * `Semana4/demos/demo_maze.cpp`
  * `Semana4/demos/demo_bank.cpp`
  * `Semana4/demos/demo_capitulo4_panorama.cpp`
  * `Semana4/pruebas_publicas/test_public_week4.cpp`
  * `Semana4/pruebas_internas/test_internal_week4.cpp`
* Usa también las lecturas y el material teórico del curso.
