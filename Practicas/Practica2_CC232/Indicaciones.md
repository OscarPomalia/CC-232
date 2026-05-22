### Práctica Calificada 2 CC232

**Curso:** CC232  
**Modalidad:** Individual  
**Formato de evaluación:** Video + repositorio + evidencia de compilación, ejecución, pruebas y modificación del código  
**Nota:** Sobre 20  
**Entrega:** **1 de mayo de 2026 a las 8:00 a. m.**  
**La entrega debe incluir la dirección del repositorio personal donde se encuentre esta evaluación**.
> Una estructura de repositorio sugerida es:

```
Repositorio-personal/
├── Semana1/
│   └── actividad1-CC232/
├── Semana2/
│   └── practica-calificada2/
└── Semana3/
    └── Actividad3-CC232/
...
```
**No se permiten entregas tardías.**  
**Si entregas fuera de plazo, no se revisará el trabajo y se colocará `NP (No presentó)`.**

**Revisión del problema asignado:** Cada estudiante debe revisar su ejercicio en el siguiente enlace oficial del curso:  
`https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv`

**Importante:** El estudiante debe verificar en ese archivo CSV:
- el problema que le fue asignado,
- el enlace del problema,
- y que estos datos coincidan exactamente con su repositorio, su `README.md` y su video.


#### 1. Finalidad de la evaluación

Esta evaluación busca verificar que el estudiante:

1. comprende los **conceptos** de estructuras de datos y algoritmos trabajados en la librería `cc232`,
2. puede **explicar** con precisión su propia implementación,
3. puede **compilar, ejecutar, probar y modificar** su código,
4. demuestra **proceso real de desarrollo** mediante historial de commits,
5. no presenta código generado, copiado o reutilizado sin comprensión real.

La evaluación se apoya en los temas de:

- **Semana 2:** arreglos dinámicos, costo amortizado, arreglos circulares, deques, `RootishArrayStack`, memoria contigua.
- **Semana 3:** `SLList`, `DLList`, `SEList`, adaptadores `Stack/Queue/Deque`, memoria enlazada vs contigua.
- **Semana 4:** `Stack`, `Queue`, paréntesis, RPN, backtracking, N-Reinas, laberinto, simulación y parsing.

#### 2. Duración del video

El video debe durar entre **25 y 35 minutos**.

- **Menos de 25 minutos:** evidencia insuficiente.
- **Más de 35 minutos:** no aporta puntaje adicional, se evaluará solo el contenido pertinente.

#### Estructura obligatoria del video

1. **Presentación del problema y del repositorio** - 3 a 4 min  
2. **Explicación conceptual** - 8 a 10 min  
3. **Recorrido técnico del código** - 6 a 8 min  
4. **Compilación, ejecución y resultados** - 4 a 5 min  
5. **Historial de commits** - 2 a 3 min  
6. **Bloque de modificación/codificación grabada sin cortes** - 5 a 7 min  

#### 3. Reglas obligatorias

##### 3.1 Trabajo individual
Esta evaluación es **estrictamente individual**.

##### 3.2 Entrega fuera de plazo
No se permiten entregas tardías.

- **Entrega después del 1 de mayo de 2026 a las 8:00 a. m.** -> **NP**
- No se revisará el repositorio ni el video.

##### 3.3 Historial de commits
El estudiante debe mostrar en el video el historial de commits de su repositorio.

**Requisito mínimo obligatorio:**
- al menos **5 commits**,
- realizados en **5 días diferentes**,
- con mensajes coherentes con el progreso real del trabajo.

**No se consideran válidos:**
- commits vacíos,
- commits artificiales,
- commits repetitivos,
- commits hechos solo para aparentar avance,
- commits concentrados al final sin evidencia de evolución técnica.

**Regla**  
Si el repositorio no demuestra proceso real de desarrollo, el componente de autoría se considera **no logrado**.

##### 3.4 Uso de cabeceras
Solo se permite el uso de archivos de cabecera **`.h`**.

- El uso de `.hpp`, `.hh`, `.hxx` u otras variantes implica **nota 01**.

##### 3.5 Indicios de generación automática o copia
Se consideran **indicios de generación automática o copia** elementos como:

- separadores mecánicos o decorativos ajenos al estilo del curso,
- bloques de código repetitivos sin justificación,
- comentarios artificiales o excesivamente mecánicos,
- convenciones, nombres o formatos no trabajados en clase,
- patrones impropios del estilo usado durante el curso.

**Importante:**  
Estos indicios **por sí solos** no determinan automáticamente la sanción, pero **si aparecen junto con**:
- incapacidad de explicar el código,
- incapacidad de modificarlo,
- inconsistencia entre video y repositorio,
- o falta de proceso real de desarrollo,

la calificación será **01**.

##### 3.6 Actividades 1, 2 y 3 obligatorias
En el repositorio deben verse completas las **Actividades 1, 2 y 3** trabajadas en clase.

- Si no están completas, la **nota máxima total** del trabajo será **05**.
- No importa si el estudiante asistió o no a clase: las actividades forman parte del proceso mínimo esperado.

##### 3.7 Bloque sin cortes
El bloque de compilación, ejecución y modificación debe grabarse **sin cortes visibles**.

- Si este bloque tiene cortes, la evidencia pierde validez.
- Si no se ve compilación ni ejecución, el trabajo no puede obtener nota alta.

##### 3.8 Estructura del repositorio
Se debe seguir la estructura pedida para el repositorio de la evaluación.

##### 3.9 Coherencia obligatoria entre fuentes
Debe haber coherencia total entre:
- el problema asignado en el CSV oficial,
- el `README.md`,
- el código del repositorio,
- los resultados mostrados,
- y el video entregado.

Si hay inconsistencias, la evidencia se considera inválida.

#### 4. Causales directas de nota 01

Se colocará **nota 01** en cualquiera de los siguientes casos:

1. usa archivos `.hpp`, `.hh`, `.hxx` u otras variantes no permitidas
2. el video no muestra compilación real del proyecto
3. el estudiante no explica correctamente:
   - la estructura usada,
   - el invariante,
   - la complejidad,
   - el flujo básico de su solución,
   - y al menos conceptos centrales del curso vinculados a su problema
4. el repositorio contiene indicios fuertes de generación o copia y el video no logra justificarlos
5. el bloque de modificación/codificación grabada no se realiza
6. el estudiante muestra código que no coincide con el repositorio entregado
7. el historial de commits es artificial, vacío o está concentrado íntegramente al final
8. no aparecen las Actividades 1, 2 y 3 en el repositorio
9. el código no compila y el estudiante no muestra una corrección funcional
10. el video dura menos de 25 minutos y además omite explicación conceptual o demostración técnica
11. el estudiante responde de forma memorizada, superficial o desconectada de su propio código
12. no puede resolver el bloque obligatorio de modificación grabada sin cortes.

#### 5. Penalizaciones fuertes y topes de nota

Estas penalizaciones se aplican incluso si no se llega a 01 directamente.

##### 5.1 Trabajo realizado a última hora
Si el trabajo aparece realizado casi íntegramente en el último día y no hay evidencia de proceso real:
- el componente de autoría se considera **desaprobado**,
- si además falla la explicación conceptual o la modificación grabada, la nota será **01**.

##### 5.2 Commits grandes
Si algunos commits son significativamente más grandes que otros, el estudiante debe explicarlo en el video.

Ejemplos aceptables:
- "en este commit integré tests y benchmark",
- "aquí migré de `vector` a deque circular",
- "aquí corregí el manejo de índices y refactoricé".

Si no puede justificar un commit grande:
- la parte de proceso y autoría se reduce severamente.

##### 5.3 Inconsistencia entre video, README y repositorio
Si el video muestra una versión del código distinta de la entregada:
- evidencia inválida,
- fuerte reducción de nota,
- posible **01** si la inconsistencia es grave.

##### 5.4 Ausencia de pruebas
Si no muestra tests, casos borde o ejemplos propios:
- la sección de validación no obtiene puntaje alto,
- la nota máxima total será **10**.

##### 5.5 Explicación memorizada sin comprensión
Si el estudiante solo lee o repite definiciones, pero no puede conectar:
- estructura,
- operación,
- invariante,
- complejidad,
- caso borde,
- y código concreto,

entonces la parte conceptual se considera **no lograda**.

##### 5.6 Falta de respuesta suficiente
Si el estudiante no puede responder:
- al menos **8 de las 15 preguntas comunes**, y
- al menos **3 de las 4 preguntas específicas** de su problema,

la **nota máxima total** será **05**.

##### 5.7 Modificación grabada incompleta o fallida
Si intenta el bloque de modificación pero:
- no lo termina,
- no lo recompila,
- o no puede explicar qué cambió,

la **nota máxima total** será **08**.

##### 5.8 Dependencia excesiva del guion
Si el video consiste principalmente en leer el `README`, leer texto preparado o repetir una explicación memorizada sin conexión real con el código:
- la **nota máxima total** será **08**.

##### 5.9 Falta de trazabilidad técnica
Si el repositorio no permite ubicar con claridad:
- dónde está la solución,
- cómo compilar,
- cómo ejecutar,
- y cómo probar,

la **nota máxima total** será **08**.

#### 6. Conceptos mínimos que debe explicar sí o sí

El estudiante debe explicar **por lo menos 10** de los siguientes conceptos, y debe conectar varios con su problema concreto.

1. ADT vs implementación concreta  
2. Invariante de estructura  
3. Complejidad temporal por operación  
4. Complejidad espacial  
5. Peor caso vs costo amortizado  
6. Memoria contigua vs memoria enlazada  
7. `resize` y crecimiento de capacidad  
8. Índices modulares  
9. Arreglo circular  
10. Deque y doble extremo  
11. Stack monotónica  
12. Ventana deslizante  
13. Prefijos/sumas prefixadas  
14. Vecinos vivos/borrado eficiente  
15. Lista simple vs doble  
16. Nodo, punteros y relinkeo  
17. `HashMap + doubly linked list`  
18. Parsing con stack  
19. Backtracking  
20. Poda  
21. Casos borde  
22. Correctitud observable  
23. Casos de prueba  
24. Separación `.h` y `.cpp`  
25. API pública y representación interna  

#### 7. Lista común obligatoria de preguntas

Estas preguntas deben responderse **sí o sí** en el video, independientemente del problema asignado.

##### 7.1 Sobre el problema
1. ¿Cuál es el problema exacto que resolviste?  
2. ¿Qué recibe la entrada y qué debe producir la salida?  
3. ¿Cuál es la restricción más importante del problema?  
4. ¿Cuál sería una solución ingenua?  
5. ¿Por qué esa solución ingenua no basta?  

##### 7.2 Sobre la estructura y la técnica
6. ¿Qué estructura de datos elegiste?  
7. ¿Por qué esa estructura es apropiada?  
8. ¿Qué invariante debes mantener?  
9. ¿Qué operación es la más importante del algoritmo?  
10. ¿Qué parte del código sería más fácil romper?  

##### 7.3 Sobre complejidad
11. ¿Cuál es la complejidad temporal?  
12. ¿Cuál es la complejidad espacial?  
13. ¿Hay costo amortizado? ¿Dónde?  
14. ¿Qué operación domina el tiempo?  
15. ¿Qué estructura alternativa podría usarse y qué perderías con ella?  

##### 7.4 Sobre implementación
16. ¿Cómo representas internamente el estado?  
17. ¿Qué variables o contenedores son críticas?  
18. ¿Qué ocurre en el caso vacío?  
19. ¿Qué ocurre en el caso de un solo elemento?  
20. ¿Qué ocurre en el caso extremo de entrada?  

##### 7.5 Sobre validación
21. ¿Qué test propio escribiste?  
22. ¿Qué caso borde validaste?  
23. ¿Qué error tuviste y cómo lo corregiste?  
24. ¿Qué resultado muestra que tu implementación sí funciona?  
25. ¿Qué cambio pequeño podrías hacer sin romper la solución?  

#### 8. Preguntas  de comprensión

Estas preguntas se usan para discriminar si el estudiante **realmente entiende** lo que implementó.

1. ¿Cuál es el invariante antes y después de cada operación?  
2. ¿Qué línea o bloque del código asegura ese invariante?  
3. ¿Qué pasaría si cambias esa línea?  
4. ¿Dónde se actualiza el tamaño lógico?  
5. ¿Qué diferencia hay entre tamaño lógico y capacidad?  
6. ¿Qué ocurre si un índice queda fuera de rango?  
7. ¿Cómo detectas un caso inválido?  
8. ¿Qué parte sería distinta si la estructura fuera enlazada en lugar de contigua?  
9. ¿Qué parte sería distinta si la estructura fuera contigua en lugar de enlazada?  
10. ¿Qué error de memoria o puntero podría aparecer aquí?  
11. ¿Qué hace tu solución mejor que una simulación simple?  
12. ¿Qué subrutina podrías reutilizar en otro problema?  
13. ¿Tu solución depende del lenguaje o de la idea algorítmica?  
14. ¿Qué pasa si duplicas el tamaño de la entrada?  
15. ¿Qué prueba te daría más confianza antes de entregar?  

#### 9. Rúbrica sobre 20 puntos

##### 9.1 Dominio conceptual - 10 puntos
- **10 a 8:** explica con claridad estructura, invariante, complejidad, casos borde, correctitud y decisiones de diseño.
- **7 a 5:** entiende lo central, pero presenta vacíos parciales.
- **4 a 2:** explicación superficial, memorizada o desconectada del código.
- **1 a 0:** no demuestra comprensión real.

**Regla:**  
Si en dominio conceptual obtiene menos de **5/10**, la **nota máxima total** será **05**.  
Si además falla compilación o modificación, la nota será **01**.

##### 9.2 Comprensión del código - 4 puntos
- identifica funciones, flujo, estados y actualizaciones críticas,
- sabe señalar dónde se realiza la operación principal,
- puede justificar decisiones concretas del código.

##### 9.3 Compilación, ejecución y resultados - 2 puntos
- compila en video,
- ejecuta sin cortes,
- muestra resultados correctos,
- enseña al menos un caso borde.

**Regla**  
Si no compila ni ejecuta en video, el trabajo **puede bajar a 01**.

##### 9.4 Bloque de modificación/codificación grabada - 3 puntos
- realiza un cambio real sin cortes,
- recompila,
- vuelve a ejecutar,
- verifica que el cambio funciona,
- explica con precisión qué cambió y por qué.

**Regla:**  
Si no realiza este bloque, la evaluación se considera incompleta y puede quedar en **01**.

##### 9.5 Proceso y autoría - 1 punto
- historial real de commits,
- evidencia progresiva,
- actividades 1, 2 y 3 presentes,
- consistencia entre video y repositorio.

#### 10. Bloque obligatorio de codificación grabada sin cortes

Aunque la evaluación es solo por video, el estudiante debe incluir un bloque equivalente a **programación en vivo grabada**.

##### Reglas
1. Debe grabarse **sin cortes**.  
2. Debe ser un cambio **real** sobre el código.  
3. Debe recompilar y volver a ejecutar.  
4. Debe explicar qué cambió y por qué.  
5. Debe mostrar el resultado del cambio.  

##### Exigencia mínima
El estudiante debe resolver:
- **3 retos transversales**, y
- **1 reto específico** de su problema.

##### Retos transversales posibles
1. agregar un caso borde propio y probarlo,
2. cambiar nombres poco claros por nombres semánticos,
3. encapsular una operación repetida en una función,
4. agregar verificación de rango o validez,
5. imprimir un estado interno útil para depurar,
6. agregar un `assert` o test simple,
7. cambiar una estructura auxiliar y explicar el impacto,
8. corregir un bug pequeño preparado por él mismo,
9. demostrar una versión lenta y luego la versión correcta,
10. refactorizar una función muy grande en dos funciones,  
11. instrumentar el código con trazas para explicar el flujo,  
12. agregar un nuevo caso de prueba extremo y justificar su resultado.  

### 11. Lista por problema: preguntas obligatorias y reto grabado

> Cada estudiante responde el bloque correspondiente a su problema asignado.

#### 1. LeetCode 239 - Sliding Window Maximum
**Debe explicar:**
- por qué se usa deque,
- qué representa cada índice guardado,
- por qué se eliminan elementos por atrás,
- por qué se eliminan índices fuera de ventana.

**Debe responder:**
1. ¿Qué invariante mantiene la deque?  
2. ¿Por qué guardas índices y no valores?  
3. ¿Cómo sabes que el frente sigue siendo válido?  
4. ¿Qué complejidad tiene cada inserción amortizada?  

**Reto grabado:**  
Modificar el código para que también reporte el **mínimo** por ventana o justificar cómo lo haría con una segunda deque.

#### 2. LeetCode 84 - Largest Rectangle in Histogram
**Debe explicar:**
- nearest smaller to left/right,
- por qué una stack monotónica resuelve el problema,
- cómo se calcula el ancho.

**Debe responder:**
1. ¿Qué significa sacar un índice de la stack?  
2. ¿Cuándo se conoce el rectángulo máximo de una barra?  
3. ¿Por qué la complejidad es lineal?  
4. ¿Qué pasa con alturas repetidas?  

**Reto grabado:**  
Agregar impresión de `left`, `right` o del ancho calculado para un caso de prueba pequeño.

#### 3. LeetCode 862 - Shortest Subarray with Sum at Least K
**Debe explicar:**
- arreglo de prefijos,
- por qué se usa deque monotónica,
- cómo se detecta una respuesta válida.

**Debe responder:**
1. ¿Qué comparas entre prefijos?  
2. ¿Por qué una deque creciente ayuda?  
3. ¿Cómo se actualiza la mejor respuesta?  
4. ¿Qué pasa si hay valores negativos?  

**Reto grabado:**  
Agregar un caso con números negativos y explicar por qué sliding window común falla.

#### 4. LeetCode 907 - Sum of Subarray Minimums
**Debe explicar:**
- contribución por elemento,
- límites izquierdo y derecho,
- manejo de repetidos.

**Debe responder:**
1. ¿Cuántos subarreglos usan un valor como mínimo?  
2. ¿Cómo evitas contar doble con repetidos?  
3. ¿Por qué no enumeras todos los subarreglos?  
4. ¿Dónde está la parte combinatoria de la solución?  

**Reto grabado:**  
Mostrar para una entrada pequeña la contribución de cada posición.

#### 5. LeetCode 1438 - Longest Continuous Subarray With Absolute Diff <= Limit
**Debe explicar:**
- mantenimiento de máximo y mínimo en ventana,
- por qué se usan dos deques,
- cómo se contrae la ventana.

**Debe responder:**
1. ¿Qué representa cada deque?  
2. ¿Cuándo la ventana deja de ser válida?  
3. ¿Qué se mueve primero: izquierda o derecha?  
4. ¿Por qué el algoritmo es lineal?  

**Reto grabado:**  
Añadir trazas que muestren el valor actual de máximo, mínimo y tamaño de la ventana.

#### 6. LeetCode 1696 - Jump Game VI
**Debe explicar:**
- DP,
- mejor valor previo en una ventana,
- deque monotónica aplicada a DP.

**Debe responder:**
1. ¿Qué significa `dp[i]`?  
2. ¿Por qué basta mirar una ventana de tamaño `k`?  
3. ¿Qué valor guarda la deque?  
4. ¿Cómo descartas estados inútiles?  

**Reto grabado:**  
Implementar una versión lenta de referencia para entrada pequeña y comparar resultados.

#### 7. LeetCode 85 - Maximal Rectangle
**Debe explicar:**
- conversión de cada fila en histograma,
- reutilización de Largest Rectangle in Histogram.

**Debe responder:**
1. ¿Qué representa `heights[j]`?  
2. ¿Qué pasa cuando aparece un `0`?  
3. ¿Por qué la respuesta global sale de resolver muchos histogramas?  
4. ¿Qué complejidad total obtienes?  

**Reto grabado:**  
Imprimir el histograma acumulado para una matriz de ejemplo.

#### 8. Codeforces 547B - Mike and Feet
**Debe explicar:**
- mínimo dominante por rango,
- nearest smaller,
- postprocesamiento de respuestas.

**Debe responder:**
1. ¿Qué rango máximo cubre cada elemento como mínimo?  
2. ¿Por qué la respuesta se rellena de atrás hacia adelante?  
3. ¿Qué haces con tamaños que no aparecen directamente?  
4. ¿Qué relación tiene con histogramas?  

**Reto grabado:**  
Mostrar el tamaño de rango calculado para algunos elementos.

#### 9. Codeforces 1313C2 - Skyscrapers (hard)
**Debe explicar:**
- forma unimodal,
- uso de estructuras para contribución izquierda/derecha,
- reconstrucción del perfil.

**Debe responder:**
1. ¿Qué propiedad debe cumplir la configuración final?  
2. ¿Qué hace tu estructura al procesar una altura menor?  
3. ¿Cómo eliges el pico?  
4. ¿Cómo reconstruyes la respuesta?  

**Reto grabado:**  
Mostrar el pico elegido y reconstruir la solución para un caso pequeño.

#### 10. Codeforces 372C - Watching Fireworks is Fun
**Debe explicar:**
- DP por eventos,
- ventana de transición válida,
- optimización con estructura de máximos.

**Debe responder:**
1. ¿Qué estado modela el DP?  
2. ¿Por qué no puedes usar transición cuadrática directa?  
3. ¿Qué rango de posiciones es válido entre eventos?  
4. ¿Cómo optimizas la transición?  

**Reto grabado:**  
Explicar con un ejemplo pequeño qué transiciones sobreviven entre dos eventos.

#### 11. LeetCode 25 - Reverse Nodes in k-Group
**Debe explicar:**
- manipulación de punteros,
- identificación de bloque,
- relinkeo antes y después del segmento.

**Debe responder:**
1. ¿Cómo sabes si hay `k` nodos disponibles?  
2. ¿Qué punteros se rompen y se vuelven a conectar?  
3. ¿Qué pasa con el último bloque incompleto?  
4. ¿Por qué no pierdes nodos?  

**Reto grabado:**  
Agregar una función auxiliar que imprima la lista antes y después de invertir un bloque.

#### 12. LeetCode 23 - Merge k Sorted Lists
**Debe explicar:**
- heap o divide and conquer,
- criterio de extracción mínima.

**Debe responder:**
1. ¿Qué guardas en el heap?  
2. ¿Cuándo insertas el siguiente nodo?  
3. ¿Por qué es mejor que fusionar todo secuencialmente?  
4. ¿Qué complejidad total obtienes?  

**Reto grabado:**  
Añadir una versión `mergeTwoLists` y explicar su reutilización.

##### 13. LeetCode 146 - LRU Cache
**Debe explicar:**
- `HashMap + doubly linked list`,
- recencia,
- operaciones O(1).

**Debe responder:**
1. ¿Qué representa el frente y el final de la lista?  
2. ¿Qué haces en `get`?  
3. ¿Qué haces en `put` cuando la clave ya existe?  
4. ¿Qué haces cuando se excede la capacidad?  

**Reto grabado:**  
Mostrar el estado de la lista después de una secuencia corta de `get/put`.

#### 14. LeetCode 432 - All O`one Data Structure
**Debe explicar:**
- buckets por frecuencia,
- movimiento entre buckets,
- máximo y mínimo.

**Debe responder:**
1. ¿Qué guarda un bucket?  
2. ¿Cómo mueves una clave al incrementar?  
3. ¿Cuándo eliminas un bucket?  
4. ¿Cómo respondes máximo y mínimo en O(1)?  

**Reto grabado:**  
Agregar una impresión del estado por buckets para una secuencia corta.

#### 15. LeetCode 460 - LFU Cache
**Debe explicar:**
- frecuencia + recencia,
- por qué es más difícil que LRU,
- estructura elegida.

**Debe responder:**
1. ¿Qué criterio expulsa un elemento?  
2. ¿Cómo se actualiza la frecuencia?  
3. ¿Qué ocurre si dos claves tienen la misma frecuencia?  
4. ¿Cómo mantienes eficiencia?  

**Reto grabado:**  
Ejecutar un caso donde varias claves empatan en frecuencia y justificar la expulsión.

#### 16. LeetCode 430 - Flatten a Multilevel Doubly Linked List
**Debe explicar:**
- recorrido,
- conexión de hijos,
- preservación de `prev/next`.

**Debe responder:**
1. ¿Qué haces cuando aparece `child`?  
2. ¿Cómo reconectas el siguiente original?  
3. ¿Cómo garantizas que la lista resultante sigue siendo doble?  
4. ¿Qué casos borde hay?  

**Reto grabado:**  
Mostrar la lista antes y después del flatten con impresión de `prev/next`.

#### 17. LeetCode 1171 - Remove Zero Sum Consecutive Nodes from Linked List
**Debe explicar:**
- prefijos acumulados,
- mapa de suma prefija a nodo,
- borrado de segmentos.

**Debe responder:**
1. ¿Qué significa repetir una suma prefija?  
2. ¿Cómo identificas un segmento suma cero?  
3. ¿Por qué se necesita más de un recorrido?  
4. ¿Cómo evitas dejar referencias incorrectas?  

**Reto grabado:**  
Agregar trazas de sumas prefijas para una entrada pequeña.

#### 18. Codeforces 899E - Segments Removal
**Debe explicar:**
- segmentos consecutivos,
- vecinos vivos,
- prioridad del segmento mayor.

**Debe responder:**
1. ¿Qué representa cada segmento?  
2. ¿Qué estructura decides usar para escoger el mejor segmento?  
3. ¿Cuándo fusionas vecinos?  
4. ¿Cómo mantienes segmentos válidos después de borrar?  

**Reto grabado:**  
Mostrar el estado de segmentos después de una eliminación.

#### 19. AtCoder ABC344 E - Insert or Erase
**Debe explicar:**
- lista doble + mapa de valor a nodo,
- inserción después de un valor,
- borrado eficiente.

**Debe responder:**
1. ¿Por qué una lista sola no basta?  
2. ¿Qué aporta el mapa?  
3. ¿Cómo borras sin recorrer todo?  
4. ¿Qué casos inválidos debes evitar?  

**Reto grabado:**  
Ejecutar inserciones y borrados mostrando la secuencia resultante.

#### 20. AtCoder ABC273 E - Notebook
**Debe explicar:**
- historial persistente,
- `SAVE` y `LOAD`,
- representación de estados.

**Debe responder:**
1. ¿Qué representa cada estado guardado?  
2. ¿Cómo vuelves a un estado previo?  
3. ¿Por qué esto no es solo una pila simple?  
4. ¿Qué operación cambia el estado actual?  

**Reto grabado:**  
Mostrar una secuencia corta con `ADD`, `DELETE`, `SAVE`, `LOAD`.

#### 21. LeetCode 51 - N-Queens
**Debe explicar:**
- backtracking,
- conflictos por columnas y diagonales,
- poda.

**Debe responder:**
1. ¿Qué significa una decisión parcial válida?  
2. ¿Cómo detectas conflicto?  
3. ¿Qué ramas podas?  
4. ¿Qué estructura usas para diagonales?  

**Reto grabado:**  
Mostrar el tablero parcial en cada nivel para `n=4`.

#### 22. LeetCode 212 - Word Search II
**Debe explicar:**
- búsqueda en tablero,
- trie + backtracking,
- poda por prefijo.

**Debe responder:**
1. ¿Por qué un trie ayuda?  
2. ¿Cómo evitas visitar la misma celda dos veces?  
3. ¿Cuándo podas una rama?  
4. ¿Cómo evitas reportar duplicados?  

**Reto grabado:**  
Agregar impresión del prefijo actual durante la búsqueda de un ejemplo pequeño.

#### 23. LeetCode 37 - Sudoku Solver
**Debe explicar:**
- backtracking,
- restricciones por fila/columna/caja,
- poda.

**Debe responder:**
1. ¿Cómo verificas si un dígito es válido?  
2. ¿Qué eliges primero para explorar?  
3. ¿Cuándo retrocedes?  
4. ¿Cómo sabes que la solución completa es válida?  

**Reto grabado:**  
Mostrar en una celda vacía qué valores candidatos son válidos.

#### 24. LeetCode 282 - Expression Add Operators
**Debe explicar:**
- construcción incremental,
- manejo de producto con precedencia,
- backtracking sobre expresiones.

**Debe responder:**
1. ¿Qué llevas acumulado en cada paso?  
2. ¿Cómo manejas la multiplicación?  
3. ¿Qué haces con números con cero inicial?  
4. ¿Cómo evitas recomputar toda la expresión?  

**Reto grabado:**  
Mostrar el estado parcial de expresión y valor acumulado.

#### 25. LeetCode 301 - Remove Invalid Parentheses
**Debe explicar:**
- búsqueda de soluciones válidas,
- poda,
- eliminación mínima.

**Debe responder:**
1. ¿Qué hace válida una cadena de paréntesis?  
2. ¿Cómo garantizas remoción mínima?  
3. ¿Cómo evitas duplicados?  
4. ¿Qué estructura o estrategia usas para explorar?  

**Reto grabado:**  
Agregar una función que valide explícitamente una cadena y probarla.

#### 26. LeetCode 726 - Number of Atoms
**Debe explicar:**
- parsing,
- pila de contextos,
- multiplicación por paréntesis.

**Debe responder:**
1. ¿Cómo detectas un nombre de átomo?  
2. ¿Cómo procesas un número después de un átomo o grupo?  
3. ¿Qué guarda cada contexto en la pila?  
4. ¿Cómo combinas los conteos?  

**Reto grabado:**  
Mostrar el mapa parcial al cerrar un paréntesis.

#### 27. LeetCode 772 - Basic Calculator III
**Debe explicar:**
- parsing con precedencia,
- operadores y operandos,
- paréntesis.

**Debe responder:**
1. ¿Cómo decides cuándo aplicar una operación?  
2. ¿Qué prioridad tiene cada operador?  
3. ¿Qué haces al abrir y cerrar paréntesis?  
4. ¿Cómo separas tokens?  

**Reto grabado:**  
Agregar trazas de las pilas de operandos y operadores.

#### 28. Codeforces 670E - Correct Bracket Sequence Editor
**Debe explicar:**
- emparejamiento de paréntesis,
- vecinos vivos,
- borrado eficiente de segmentos.

**Debe responder:**
1. ¿Cómo emparejas los paréntesis?  
2. ¿Qué estructura mantiene vecinos?  
3. ¿Qué borras exactamente en una operación?  
4. ¿Cómo te mueves luego del borrado?  

**Reto grabado:**  
Mostrar el estado de vecinos antes y después de borrar un bloque.

#### 29. Codeforces 5C - Longest Regular Bracket Sequence
**Debe explicar:**
- balance,
- stack o DP,
- conteo de ocurrencias.

**Debe responder:**
1. ¿Cómo detectas una secuencia válida terminando en `i`?  
2. ¿Cómo obtienes la longitud máxima?  
3. ¿Cómo cuentas cuántas veces aparece?  
4. ¿Qué pasa si no existe ninguna?  

**Reto grabado:**  
Agregar un caso donde haya varias respuestas con la misma longitud máxima.

#### 30. Codeforces 1838D - Bracket Walk
**Debe explicar:**
- validez dinámica,
- estructura usada para mantener posiciones problemáticas,
- criterio para responder consultas.

**Debe responder:**
1. ¿Qué invalida una secuencia tras un cambio?  
2. ¿Qué conjunto o estructura mantienes?  
3. ¿Cómo respondes una consulta rápido?  
4. ¿Qué condiciones deben cumplirse para que la cadena sea válida?  

**Reto grabado:**  
Mostrar cómo cambia la estructura interna después de una actualización.

#### 12. Formato del repositorio de entrega

El repositorio debe contener, como mínimo:

```text
apellido_nombre_pc2/
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

#### Restricciones
- Solo cabeceras `.h`
- El código debe compilar desde el repositorio entregado
- Debe existir `README.md` con:
  - problema asignado,
  - enlace del problema,
  - referencia al archivo oficial de asignación,
  - instrucciones de compilación,
  - instrucciones de ejecución,
  - caso de prueba principal,
  - declaración breve de autoría


#### 13. Plantilla mínima de README.md del estudiante

````md
## PC2 - CC232

### Estudiante
- Nombre:
- Código:
- Problema asignado:
- Enlace:

### Referencia oficial
- Archivo de asignación:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv

### Tema principal
- Semana:
- Estructura o técnica principal:

### Resumen de la solución
Explica brevemente la idea principal de la solución.

### Complejidad
- Tiempo:
- Espacio:

### Invariante o idea clave
Describe el invariante o propiedad que se mantiene.

### Archivos relevantes
- include/
- src/
- tests/
- demos/

### Compilación
```bash
cmake -S . -B build
cmake --build build
```

### Ejecución
```bash
./build/tu_programa
```

### Casos de prueba
Describe al menos 3 casos:
1.
2.
3.

### Historial de commits
Indica que el historial debe verse en el video.

### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
````

#### 14. Recomendaciones finales para corrección estricta

No se pondrá una nota aprobatoria si el estudiante:

- no puede nombrar la estructura usada,
- no puede explicar el invariante,
- no puede justificar la complejidad,
- no puede mostrar compilación limpia,
- no puede ejecutar casos borde,
- no puede modificar el código sin cortes,
- solo lee texto preparado,
- muestra commits artificiales,
- presenta un repositorio sin proceso real,
- no logra conectar teoría, implementación y resultados.

#### 15. Criterio de severidad

Para frenar el uso de código generado sin comprensión:

- **sin explicación conceptual suficiente** -> **01**  
- **sin bloque de modificación grabada** -> **01**  
- **sin compilación y ejecución visibles** -> **01**  
- **sin proceso real de commits en días distintos** -> componente de autoría desaprobado  
- **sin Actividades 1, 2 y 3** -> nota máxima **05**  
- **evidencia fuerte de generación o copia + mala explicación** -> **01**  
- **inconsistencia grave entre CSV oficial, repositorio y video** -> **01**  
- **falla conceptual severa + imposibilidad de modificar el código** -> **01**

#### 16. Observación final

Este instrumento no evalúa solamente si "el programa funciona".  
Evalúa si el estudiante **entiende lo que programó**, puede **explicarlo**, puede **probarlo**, puede **modificarlo** y puede 
demostrar **proceso auténtico de construcción**.
