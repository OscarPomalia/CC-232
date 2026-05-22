### Rubrica - Semana 2

#### 1. Comprensión conceptual

- **Logrado:** define con claridad memoria contigua, arreglo dinámico, `size`, `capacity`, `resize`, costo amortizado, arreglo circular, deque, rebalanceo, representación por bloques en `RootishArrayStack` y el papel de `FastSqrt`.
- **En proceso:** reconoce los conceptos principales de la semana, pero todavía mezcla algunos términos o no diferencia bien unas estructuras de otras.
- **Por reforzar:** no logra distinguir las ideas centrales de la semana ni explicar cómo se relacionan.

#### 2. Sustentación de correctitud

- **Logrado:** justifica por qué las operaciones funcionan, explicando corrimientos, conservación del orden lógico, uso correcto de índices modulares, criterio para mover el lado más corto en `ArrayDeque`, rebalanceo entre `front` y `back` en `DualArrayDeque`, y mapeo de índice a bloque en `RootishArrayStack`.
- **En proceso:** da intuiciones correctas sobre el funcionamiento de las operaciones, pero con una justificación parcial o poco precisa.
- **Por reforzar:** afirma que la estructura "funciona" sin sustento conceptual ni explicación del comportamiento de sus operaciones.

#### 3. Análisis de eficiencia

- **Logrado:** identifica y compara correctamente costos temporales y espaciales usando lenguaje asintótico básico, incluyendo acceso por índice, corrimientos en inserción y borrado, costo de `resize`, diferencia entre peor caso y amortizado, ventaja de índices modulares en colas, criterio de movimiento en deques y compromiso tiempo-espacio en `RootishArrayStack`.
- **En proceso:** reconoce qué operaciones son más rápidas o más lentas, pero confunde algunos costos o no justifica bien la diferencia entre costo individual y costo amortizado.
- **Por reforzar:** no logra relacionar las operaciones con su costo o presenta explicaciones incorrectas sobre eficiencia.

#### 4. Aplicación al código de la semana

- **Logrado:** conecta la teoría con implementaciones concretas de la semana, explicando con precisión operaciones y decisiones de diseño en `ArrayStack`, `FastArrayStack`, `ArrayQueue`, `ArrayDeque`, `DualArrayDeque`, `RootishArrayStack` y `FastSqrt`.
- **En proceso:** menciona ejemplos del código de la semana y reconoce algunas decisiones de implementación, pero con análisis parcial o superficial.
- **Por reforzar:** no logra vincular la teoría con las implementaciones ni con los ejercicios y pruebas trabajadas en Semana 2.

#### 5. Claridad de comunicación

- **Logrado:** responde de forma ordenada, precisa y entendible, usando ejemplos, comparaciones o trazas breves cuando ayudan a sustentar la respuesta.
- **En proceso:** comunica la idea general, pero con desorden, ambigüedad o poca precisión en algunos términos.
- **Por reforzar:** da respuestas vagas, contradictorias o difíciles de seguir.

#### Orientación para la sustentación de semana 2

Se espera especialmente que el estudiante pueda:

- explicar por qué `ArrayStack` necesita `resize()` y por qué `add(size(), x)` es `O(1)` amortizado
- justificar el uso de índices modulares en `ArrayQueue` y `ArrayDeque`
- explicar por qué `ArrayDeque` intenta mover el lado más corto
- describir cómo `DualArrayDeque` reparte elementos entre `front` y `back` y cuándo rebalancea
- sustentar cómo `RootishArrayStack` organiza sus elementos en bloques y cómo se obtiene el bloque correspondiente a un índice
- relacionar `FastSqrt` con el cálculo eficiente usado en `RootishArrayStack`.
