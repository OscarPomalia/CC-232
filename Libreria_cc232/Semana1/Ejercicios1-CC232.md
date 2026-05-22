### Lista de ejercicios - Semana 1

#### Ejercicio 1. Bubble sort: correctitud básica e invariantes

Considera dos versiones del algoritmo **Bubble Sort**: una versión básica y una versión optimizada que detiene la ejecución cuando en una pasada no ocurre ningún intercambio.

##### Se pide
1. Ejecutar ambas versiones sobre los siguientes arreglos:
   - un arreglo ya ordenado,
   - un arreglo ordenado en sentido inverso,
   - un arreglo casi ordenado.
2. Para cada caso, registrar el número de comparaciones y el número de intercambios.
3. Enunciar una invariante de ciclo para una pasada de Bubble Sort.
4. Explicar por qué el algoritmo termina.
5. Justificar por qué la versión optimizada sigue siendo correcta.


#### Ejercicio 2. Cadena bien balanceada usando el ADT Pila

Una cadena formada por los símbolos `(`, `)`, `[`, `]`, `{`, `}` se dice **bien balanceada** si cada símbolo de apertura tiene su correspondiente símbolo de cierre y el orden de anidamiento es correcto.

##### Se pide
1. Especificar las operaciones básicas del **ADT Pila** que se necesitan para resolver este problema.
2. Diseñar un algoritmo que determine si una cadena está bien balanceada.
3. Enunciar una invariante del recorrido de la cadena.
4. Justificar la correctitud básica del algoritmo.
5. Indicar su complejidad temporal en función de la longitud de la cadena.


#### Ejercicio 3. Logaritmos y notación asintótica

Sean `a, b > 1`. Se sabe que los logaritmos en distintas bases difieren solo en un factor constante.

#### Se pide
1. Demostrar que `log_a n = Θ(log_b n)`.
2. Probar que, para todo `ε > 0`, se cumple que `log n = O(n^ε)`.
3. Explicar por qué estos resultados permiten ignorar la base del logaritmo en el análisis asintótico.
4. Dar un ejemplo concreto en el que este hecho simplifique el análisis de un algoritmo.


#### Ejercicio 4. Afirmaciones con notación `O`: demostrar o refutar

Sean `f(n)` y `g(n)` funciones no negativas. Suponga que `f(n) = O(n^2)` y `g(n) = O(n)`.

##### Para cada afirmación siguiente
Indique si es siempre verdadera o no. Si es verdadera, demuéstrela; si no lo es, entrega un contraejemplo.

1. `f(n) + g(n) = O(n^2)`
2. `f(n) · g(n) = O(n^3)`
3. `f(n) / g(n) = O(n)`
4. `g(n) = O(f(n))`

Finalmente, explica brevemente por qué en notación asintótica no basta "intuir" el crecimiento, sino que se necesita una justificación formal.

#### Ejercicio 5. Conteo de bits en 1 y tamaño real de la entrada

Considera el problema de contar cuántos bits en `1` tiene la representación binaria de un entero no negativo `n`.

### Se pide
1. Diseñar un algoritmo que resuelva el problema.
2. Expresar su complejidad temporal en función del número de bits de `n`.
3. Explicar por qué, en este problema, el tamaño de entrada no debe interpretarse como el valor numérico de `n`, sino como la longitud de su representación.
4. Comparar conceptualmente una versión que revisa bit por bit con otra que solo procesa los bits en `1`.
5. Indicar en qué sentido este ejercicio se relaciona con el modelo RAM.

#### Ejercicio 6. Potencia rápida y mejora asintótica

Considera el problema de calcular `2^n` para `n >= 0`.

##### Se pide
1. Plantear una solución ingenua basada en multiplicar por `2` exactamente `n` veces.
2. Diseñar una versión más eficiente basada en dividir el problema en subproblemas más pequeños.
3. Escribir el algoritmo de la versión eficiente, ya sea de forma iterativa o recursiva.
4. Analizar la complejidad temporal de ambas versiones.
5. Explicar claramente cuál es la idea que permite pasar de tiempo lineal a tiempo logarítmico.

#### Ejercicio 7. Máximo de un arreglo: iteración, recursión y correctitud

Dado un arreglo de `n` enteros, se desea hallar el valor máximo.

##### Se pide
1. Diseñar un algoritmo iterativo para hallar el máximo.
2. Diseñar un algoritmo recursivo para el mismo problema.
3. Enunciar una invariante de ciclo para la versión iterativa.
4. Identificar el caso base y la hipótesis de correctitud para la versión recursiva.
5. Comparar ambas soluciones en términos de complejidad temporal y uso de memoria.

### Indicaciones generales

En todos los ejercicios:

- justifique tus respuestas
- usa notación asintótica cuando corresponda
- cuando se pida correctitud, indica con claridad la invariante, el inicio, el mantenimiento y la terminación
- cuando se use un ADT, distingue entre **interfaz** e **implementación**.
