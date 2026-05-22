## Actividad 4-CC232

### Estudiante

- Nombre completo: Oscar Alberto Pomalia Suyo

#### Bloque 1

1. **LIFO vs FIFO:** LIFO (Last In, First Out) es como una pila de platos: el último que pones arriba es el primero que sacas. FIFO (First In, First Out) es como la fila del supermercado: el primero en formarse es el primero en ser atendido.

2. **Stack para "último pendiente":** Porque al apilar tareas, la memoria más reciente queda expuesta en el tope. Esto es ideal para retroceder pasos (backtracking) o retomar algo que fue interrumpido por un subproblema urgente.

3. **Queue para procesos:** Modela perfectamente la vida real porque garantiza "justicia" (fairness). Nadie se cuela; respetas el orden de llegada.

4. **Reemplazar recursión:** Significa dejar de depender de la memoria del procesador (el Call Stack de funciones) y crear tu propio objeto `Stack` en código, manejando el bucle y los estados tú mismo (iterativo).

5. **Información mínima en la pila:** El estado actual y la alternativa que queda por explorar (o la decisión que ya tomaste), para saber a dónde regresar si te chocas contra un muro.

6. **Conversión iterativa vs recursiva:** Comparten la matemática (divisiones sucesivas por la base). Cambia el control: la iterativa usa un bucle y empuja residuos a una pila manual; la recursiva delega ese almacenamiento a la memoria del sistema operativo y los imprime al desapilar las funciones.

7. **Paréntesis iterativa:** Porque cuando lees un paréntesis de cierre `)`, tienes que hacer *match* estrictamente con la ÚLTIMA apertura que no se ha cerrado. Necesitas recordarlas en orden inverso.

8. **Dos pilas en evaluador:** No puedes aplicar un operador apenas lo lees. Necesitas una pila para guardar números y OTRA para guardar operadores en espera, porque la multiplicación tiene que ganarle a una suma que estaba antes.

9. **N-Reinas y Laberinto (Backtracking):** Porque no tienes la fórmula mágica para saber la ruta. Tienes que caminar a ciegas y, si te estrellas o una reina ataca a otra, necesitas deshacer tu último paso (hacer un `pop` de tu posición) y probar otro camino.

10. **Banco con Colas:** Si modelas un banco con una pila (LIFO), el cliente que llegó a las 8 am se atendería al final del día. Las colas garantizan orden cronológico.

11. **Estructura, estado y correctitud:** La estructura (ej. Stack) es el contenedor. El estado es la información en un instante dado. Si tu estructura está mal elegida, corrompes el estado y el algoritmo toma decisiones rotas (pierdes correctitud).

12. **Resolver vs Simular:** Resolver es buscar una verdad absoluta (¿cuánto sale la expresión? ¿hay salida del laberinto?). Simular es emular el paso del tiempo "tick a tick" para observar el comportamiento de un sistema (banco) que nunca "termina", solo fluye.

#### Bloque 2 

| Archivo | Salida u observable importante | Estructura o técnica central | Qué concepto permite defender | 
| ----- | ----- | ----- | ----- | 
| `demo_stack_queue.cpp` | Inversión de orden (Pila) vs Orden mantenido (Cola) | ADTs Stack y Queue | LIFO invierte la secuencia; FIFO la conserva intacta. | 
| `demo_base_conversion.cpp` | Strings de salida idénticos para el mismo número | Pila explícita vs Pila de llamadas | La recursión implícita puede traducirse 1:1 a un enfoque iterativo. | 
| `demo_paren_rpn.cpp` | Rechazo inmediato al primer `]` que no cruza | Pila (Stack) de tokens | Un fallo de balanceo detiene la ejecución en tiempo constante (Fail-fast). | 
| `demo_nqueens.cpp` | `solutions` es pequeñísimo, `checks` es gigante | Búsqueda Backtracking | Costo computacional vs Tamaño de la solución. | 
| `demo_maze.cpp` | Celdas marcadas como BACKTRACKED | Matriz de estados y Stack | Si no marcamos el error, el algoritmo entra en ciclos infinitos. | 
| `demo_bank.cpp` | Largos de listas variando en el tiempo | Colas múltiples | Dinámica de sistemas y balanceo de carga. | 
| `demo_capitulo4...` | Consistencia en la importación de `#include` | ADTs Polimórficos | Una buena estructura de datos sirve para N dominios distintos. | 

1. **Stack vs Queue:** Al imprimir, el Stack escupe los números al revés de como entraron. La Queue los escupe en orden.
2. **Base Conversion:** Que la consola imprime "1010" en ambas ejecuciones para el mismo input.
3. **Paréntesis:** Si los paréntesis fallan, el programa aborta la creación de la RPN.
4. **NQueens:** `solutions` son tableros válidos. `checks` son todas las combinaciones que intentó. No miden lo mismo porque fallas miles de veces antes de acertar una reina.
5. **Maze:** Que a veces la coordenada salta "hacia atrás", demostrando que desapiló un camino muerto.
6. **Bank:** Los elementos son la cantidad de personas esperando paciencia en cada caja.
7. **Panorama:** La salida muestra que problemas de mates, juegos y bancos dependen exactamente del mismo código base de `Stack.h` y `Queue.h`.

#### Bloque 3

1. **Stack:** Valida `push`, `pop`, la lectura de `top` y que `empty()` o `size()` reaccionen correctamente.
2. **Queue:** Valida `enqueue`, `dequeue`, lectura de `front` y manejo de tamaños.
3. **Base:** Valida conversión binaria, octal y hexadecimal de números positivos comunes y el caso borde de n=0.
4. **Paréntesis:** Valida anidamiento correcto `{[()]}`, cruces malos `[(])` y vacíos `""`.
5. **Expresiones:** Prioridades aritméticas, que respeten los paréntesis y la generación del string RPN.
6. **NQueens:** Compara la cantidad de soluciones encontradas con valores matemáticos conocidos (ej. N=8 da 92).
7. **Maze:** Prueba un laberinto con ruta clara y uno cerrado con paredes para validar que retorne `false`.
8. **bestWindow:** Valida que escoja el índice menor si dos colas están vacías o tienen el mismo tamaño.
9. **Pruebas internas:** Suelen probar estrés (tableros de N=14), expresiones kilométricas, o divisiones por cero.
10. **Pasar pruebas vs justificar:** El test pasa si tienes suerte con los inputs. La justificación matemática (invariante) prueba que es imposible que falle en cualquier caso no testeado.
11. **Error conceptual oculto:** No resetear las variables globales al llamar a la función de N-Reinas por segunda vez. Pasa el primer test, revienta en el segundo.

#### Bloque 4 

1. **Rol en bases:** El cociente es lo que sobra por procesar. El residuo es el dígito final. La pila los almacena para invertirlos.
2. **Apilado:** Porque la división nos da primero el dígito menos significativo (el de más a la derecha), así que lo guardamos al fondo para sacarlo al final.
3. **Explícito vs Implícito:** Control. Si dejas que el sistema lo haga (implícito), con un número gigante revienta la memoria (Stack Overflow). Con pila explícita, controlas el heap.
4. **divideParentheses:** Parte el string a la mitad para validar que la sub-expresión interior también es legal.
5. **Limitación recursiva:** Pasar contexto es un infierno. Validar `(` con `)` es fácil, pero si entra `{` y `]`, la recursión se marea sin estado extra.
6. **Detección iterativa rápida:** Porque si leo `}` y el tope de mi pila es `(`, ya rompí la regla. Lanzo error inmediatamente (O(1)).
7. **Iterativo vs Recursivo:** Iterativo es súper natural para paréntesis (vas empujando y sacando). Recursivo es más expresivo y bonito en código para conversión de base.

##### Experimento 1

| Número | Base | Recursiva | Iterativa | Coinciden | Comentario | 
| ----- | ----- | ----- | ----- | ----- | ----- | 
| 10 | 2 | 1010 | 1010 | Sí | Caso estándar. | 
| 255 | 16 | FF | FF | Sí | Cambio de notación a letras. | 
| 8 | 8 | 10 | 10 | Sí | Salto de unidad. | 
| 0 | 2 | 0 | 0 | Sí | Caso borde crítico. | 
| 100 | 16 | 64 | 64 | Sí | Funcionamiento normal. | 

##### Experimento 2

| Expresión | Res. Recursivo | Res. Iterativo | Coinciden | Explicación del caso | 
| ----- | ----- | ----- | ----- | ----- | 
| `""` | True | True | Sí | Vacío es balanceado por definición. | 
| `abc` | True | True | Sí | No hay delimitadores, nada se rompe. | 
| `{[()]}` | True | True | Sí | Anidamiento simétrico perfecto. | 
| `((()()` | False | False | Sí | Faltan cierres, la pila quedó con datos. | 
| `[(])` | False | False | Sí | Cruce malo. Corchete intentó cerrar paréntesis. | 
| `()[]{}` | True | True | Sí | Varios tipos secuenciales, no anidados. | 
| `(((((({{{{{{{{{}}}}}}}}}))))))` | True | True | Sí | Anidamiento extremo de estrés. | 
| `( [ a * b ] + c }` | False | False | Sí | Falla en el último caracter al no coincidir la llave. | 

#### Bloque 5 

1. **EvaluationResult:** Guarda el valor calculado (float), el string de RPN equivalente y el estado de error (OK, Sintaxis, DivZero).
2. **Eliminar espacios:** Evita lidiar con basura al hacer el parsing de tokens numéricos.
3. **Menos unario:** Se detecta si el `-` está al inicio del string absoluto o si tiene un operador/apertura inmediatamente a su izquierda.
4. **Factorial (!):** Es un operador de sufijo. La restricción es que opera sobre el último número procesado en la pila, no necesita evaluar a la derecha.
5. **RPN sobre la marcha:** Cada vez que un operador viejo desapila a otro por temas de prioridad, ese viejo va directo a imprimirse al string RPN.
6. **Relación de operadores:** Regla básica: "si lo que viene manda más (ej `*` sobre `+`), se apila. Si manda menos, desapilo y resuelvo".
7. **Mal formada = error:** Si retornas "0", el programa que use la calculadora pensará que ese es el resultado real matemático y arruinará todo el flujo.
8. **Ventaja RPN:** Sacas la respuesta numérica y el compilado de máquina (RPN) en una sola pasada (O(N)).

##### Experimento 3

| Expresión | RPN esperada | RPN obtenida | Val esperado | Val obtenido | Explicación breve | 
| ----- | ----- | ----- | ----- | ----- | ----- | 
| `2+3*4` | `2 3 4 * +` | `2 3 4 * +` | 14 | 14 | Prioridad del `*`. | 
| `10-2-3` | `10 2 - 3 -` | `10 2 - 3 -` | 5 | 5 | Asociatividad izquierda. | 
| `(2+3)*4` | `2 3 + 4 *` | `2 3 + 4 *` | 20 | 20 | Paréntesis fuerzan evaluación. | 
| `5*(4/(2-1))` | `5 4 2 1 - / *` | `5 4 2 1 - / *` | 20 | 20 | Doble anidamiento profundo. | 
| `-5+3` | `-5 3 +` | `-5 3 +` | -2 | -2 | Unario resuelto primero. | 
| `2+*3` | ERROR | ERROR | ERROR | ERROR | Dos operadores binarios seguidos. | 

**Extensión (Operador Potencia `^`)**

* Agregué el símbolo `^` con aridad 2.
* Prioridad muy alta (mayor que `*` y `/`).
* Probé `2^3` (válido, dio 8). Inválido `2^` (error sintaxis).
* Modifiqué `OperatorPriority.h` y el `switch` de cálculo usando `<cmath>` `pow()`.

#### Bloque 6 

1. **Conflicto Reinas:** Que estén en misma x, misma y, o compartan diagonal (delta X == delta Y).
2. **Pila solution:** Es el "historial de jugadas vivas". Guarda las coordenadas exactas de las reinas colocadas que aún no han sido descartadas.
3. **Avanzar y retroceder:** Avanzas si encuentras un hueco. Si la fila no tiene ningún hueco seguro, tu estado actual fracasó; haces `pop` (retrocedes) y tratas de mover a la reina de la fila anterior.
4. **Checks:** Muestra el verdadero costo algorítmico. Contar "2 soluciones" suena fácil, pero costó 150 `checks` hallarlas.
5. **collectPlacements = false:** Apaga el guardado de matrices en memoria RAM. Esencial para evitar explotar la RAM con N=14.
6. **Estados Maze:** AVAILABLE (camino libre), ROUTE (ruta candidata), BACKTRACKED (callejón sin salida), WALL (obstáculo).
7. **Incoming/Outgoing:** Sirven para dibujar la línea o rastro visual de hacia dónde te moviste desde esa baldosa.
8. **Marcar vs Moverse:** Si no pintas el error con `BACKTRACKED`, la próxima vez que entres por otro lado volverás a evaluar ese mismo callejón inútilmente.
9. **Comparativa:** Reinas es abstracto (un array 1D basta porque sabemos que hay una por fila). Laberinto es espacial y requiere guardar el estado 2D completo de toda la matriz.

##### Experimento 4 

| n | Soluciones | Checks | Crecimiento | Comentario | 
| ----- | ----- | ----- | ----- | ----- | 
| 4 | 2 | ~136 | Lento | Problema base. | 
| 5 | 10 | ~500 | Regular | Empieza a subir. | 
| 8 | 92 | ~15000 | Exponencial | Costo real muy alto. | 
| 10 | 724 | ~400000 | Brutal | Explosión combinatoria. | 

1. **Patrón de checks:** Crece de forma exponencial/factorial.
2. **Contar vs verificar:** Las soluciones son los éxitos. Las verificaciones incluyen todos los millones de fracasos ocultos.
3. **Poda:** Aparece sutilmente: al no poder colocar reina en fila 2, ni se molesta en probar las combinaciones de fila 3 hasta la 8. Poda toda esa rama gigante.

##### Experimento 5 

* **Lab 1 (Libre 5x5):** Inicio 0,0 a 4,4. Longitud=9. Evidencia retroceso=0. Ruta perfecta.
* **Lab 2 (Encerrado):** Inicio rodeado de 3 muros. Longitud=0. Evidencia retroceso: pinta 2 celdas `BACKTRACKED` y falla.
* **Lab 3 (Trampa "U"):** Camino claro que lleva a un callejón largo. Longitud=15. Retroceso: El algoritmo llenó de `BACKTRACKED` toda la trampa y recién intentó la ruta B.

#### Bloque 7 

1. **Queue en ventanillas:** Es la fila física de clientes esperando pacientemente al cajero `i`.
2. **bestWindow:** Busca el `min(size())`. En empate, agarra el índice más bajo (el cajero de más a la izquierda).
3. **Semilla (seed):** Garantiza que aunque sea "aleatorio" (clientes llegan en tiempos distintos), al correrlo con la misma semilla repetimos exactamente el mismo escenario para debuggear.
4. **Lógica de atención:** `totalArrivals >= totalServed`. Es físicamente imposible atender a alguien que no ha llegado.
5. **Timeline:** El reloj maestro del evento. No es tiempo real de CPU, es tiempo discretizado del modelo de la matriz.
6. **Colas en el banco:** Si usas pilas, el abuelo que llegó a las 7am sería atendido último. Sería caótico e irreal.
7. **Simplificaciones:** Nadie se aburre y abandona la cola. Los cajeros no van al baño. El tiempo de servicio no varía por complejidad del trámite.
8. **Política cambiada:** Si fuera aleatoria, un cajero podría tener 30 personas y otro 0, rompiendo la optimización del sistema.

##### Experimento 6

| nWin | servTime | seed | totalArr | totalServ | Final colas | Observación | 
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | 
| 3 | 10 | 42 | 25 | 23 | [1, 1, 0] | Sistema fluye bien y balanceado. | 
| 1 | 10 | 42 | 25 | 10 | [15] | Un solo cajero produce colapso total. | 
| 3 | 10 | 99 | 30 | 25 | [2, 2, 1] | Otra semilla altera la demanda pero aguanta. | 

1. **Parámetro más influyente:** `nWin` (Las ventanillas). Es el verdadero cuello de botella.
2. **Misma semilla:** Obtienes una copia exacta, clonada 1:1, del mismo día de atención.
3. **Cambiar semilla:** Cambia cuándo llegan los clientes, exigiendo dinámicamente al sistema de forma diferente.
4. **Evidencia cola más corta:** En todas las pruebas equilibradas (`nWin`>=3), las colas siempre terminaban en rangos similares (ej `[1,1,0]`), evitando que haya tiempos ociosos en los cajeros.

#### Bloque 8

Cambia absolutamente nuestra filosofía de programación: pasamos de usar los ADTs como meros "contenedores de datos" a usarlos como **el motor del tiempo y el espacio** en nuestro algoritmo.

En lugar de depender de la recursión implícita donde la RAM del sistema decide el flujo y te expone a Stack Overflows, el uso de estructura explícita nos da control quirúrgico del estado. La pila gobierna el **espacio de búsqueda** (es nuestro hilo de Ariadna en el backtracking del laberinto o en las ramas muertas de las N-Reinas), permitiendo aplicar poda con facilidad. Por otro lado, la cola asume el rol del **tiempo lineal** en la simulación bancaria o en tareas de enrutamiento FIFO, garantizando equidad algorítmica.

Para el parsing de expresiones, las pilas ya no son un "array elegante", son un autómata que dicta la semántica (las prioridades aritméticas) con un LIFO perfecto.

En conclusión: la correctitud de Bases, Paréntesis, Juegos y Bancos recae netamente en que la estructura elegida empata matemáticamente con las restricciones de la realidad que simulamos. La evidencia experimental siempre demuestra que, si el ADT preserva bien tu invariante de estado, el algoritmo nunca fallará.

#### Autoevaluación breve

- Qué puedo defender con seguridad: La diferencia radical entre la recursión implícita (caja negra) y la iteración con pilas explícitas (control total), y por qué el fail-fast ayuda en los paréntesis.
- Qué todavía confundo: A veces me enredo trazando mentalmente el algoritmo de prioridad de operadores si hay divisiones anidadas muy profundas dentro de un RPN.
- Qué experimento me dio mejor evidencia: Modificar el `nWin` (ventanillas) en el banco. Visualizar cómo colapsa la cola a 15 personas con un solo cajero es muy ilustrativo.
- Qué evidencia usaría en una sustentación: Los `checks` del N-Reinas. Es la mejor forma métrica de explicar por qué contar las soluciones ganadoras no refleja el esfuerzo bestial que hizo el CPU detrás de escena buscando y podando ramas.