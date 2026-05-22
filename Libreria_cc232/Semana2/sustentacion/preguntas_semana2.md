### Preguntas de sustentacion - Semana 2

Esta sustentación busca verificar que el estudiante comprende las ideas centrales de la semana y sabe relacionarlas con las implementaciones desarrolladas en código.

#### 1. Arreglo, memoria contigua y vector

1. ¿Qué significa que un arreglo use memoria contigua?
2. ¿Por qué acceder a `A[i]` es una operación de costo `O(1)`?
3. ¿Qué diferencia hay entre `size` y `capacity`?
4. ¿Por qué un arreglo dinámico necesita espacio libre además de los elementos válidos?
5. ¿Qué ventaja ofrece la memoria contigua frente a una lista enlazada?
6. **[Código]** En `ArrayStackExplicado`, ¿qué invariante debe cumplirse siempre entre `n_` y `capacity_`?
7. **[Código]** En `DengVector`, ¿qué responsabilidad separan `_size` y `_capacity`?

#### 2. DengVector y resizing

8. ¿Qué papel cumple `copyFrom(...)` dentro de una clase vector propia?
9. **[Código]** ¿Por qué el constructor por copia debe reservar memoria nueva y no reutilizar el puntero original?
10. **[Código]** ¿Qué protege el operador de asignación cuando aparece la autoasignación?
11. **[Código]** ¿Cuándo debe activarse `expand()` en `DengVector`?
12. **[Código]** ¿Por qué `insert(r, e)` necesita desplazar elementos hacia la derecha?
13. **[Código]** ¿Qué diferencia conceptual hay entre `remove(r)` y `remove(lo, hi)`?
14. **[Código]** ¿Qué condición evita que `shrink()` redimensione demasiado seguido?
15. **[Código]** ¿Qué muestra `demo_deng_vector.cpp` sobre el crecimiento de capacidad?
16. **[Código]** En las pruebas, ¿cómo se verifica que la copia es profunda?
17. **[Código]** ¿Qué ventaja didáctica tiene `traverse()` frente a recorrer el arreglo directamente en `main`?

#### 3. ArrayStack y resizing

18. ¿Qué hace `ArrayStack` cuando ya no hay espacio para insertar un nuevo elemento?
19. ¿Por qué `resize()` crea un arreglo nuevo en lugar de "alargar" el mismo bloque?
20. ¿Qué costo tiene una expansión aislada?
21. ¿Por qué `add(size(), x)` puede ser `O(1)` amortizado aunque a veces active una copia completa?
22. **[Código]** En `ArrayStack.h`, ¿por qué `resize()` usa `max(2*n, 1)`?
23. **[Código]** ¿Por qué `add(i, x)` desplaza elementos desde `j = n` hasta `i + 1`?
24. **[Código]** ¿Qué pasa en `remove(i)` y por qué luego puede ejecutarse un `resize()` si `a.length >= 3*n`?
25. **[Código]** En las pruebas públicas, ¿qué propiedades se validan cuando se inserta `99` en medio y luego se elimina?

#### 4. FastArrayStack

26. ¿Qué idea mejora `FastArrayStack` respecto a `ArrayStack`?
27. **[Código]** ¿Qué papel cumplen `std::copy` y `std::copy_backward` en `FastArrayStack`?
28. **[Código]** ¿Por qué `copy_backward` es apropiado al insertar y no `copy` directo?
29. ¿La complejidad asintótica de `FastArrayStack` cambia respecto a `ArrayStack`, o cambia más bien la constante oculta?
30. **[Código]** En la prueba pública, ¿qué se verifica cuando se inserta `7` entre `5` y `6` y luego se elimina el índice `0`?

#### 5. Análisis amortizado

31. ¿Qué diferencia hay entre costo peor caso y costo amortizado?
32. ¿Por qué no basta decir "una inserción a veces cuesta `O(n)`, entonces todas cuestan `O(n)`"?
33. ¿Cómo se reparte el costo de una expansión entre muchas inserciones?
34. ¿Qué pasaría si la capacidad creciera de uno en uno en vez de duplicarse?
35. ¿Por qué usar un umbral holgado para reducir evita redimensionamientos demasiado frecuentes?
36. **[Código]** ¿Qué tipo de comportamiento intenta estresar `resize_stress_week2.cpp` cuando inserta cientos de elementos y luego elimina muchos?

#### 6. ArrayQueue y arreglos circulares

37. ¿Qué problema intenta resolver `ArrayQueue` frente a usar un arreglo lineal con corrimientos para una cola?
38. ¿Qué representa el índice `j` en `ArrayQueue`?
39. **[Código]** ¿Por qué `add(x)` escribe en `a[(j+n) % a.length]`?
40. **[Código]** ¿Por qué `remove()` avanza con `j = (j + 1) % a.length` en lugar de desplazar todos los elementos?
41. ¿Por qué se habla de arreglo circular aunque físicamente siga siendo un arreglo lineal?
42. **[Código]** En la prueba extendida, ¿qué propiedad FIFO se confirma cuando salen `1, 2, 3, 4` en ese orden?
43. **[Código]** En la prueba interna extendida, ¿qué demuestra el patrón "entra `1..20`, salen `1..10`, entra `21..30`, salen `11..30`"?

#### 7. ArrayDeque

44. ¿Qué operaciones adicionales permite un deque frente a una cola simple?
45. **[Código]** En `ArrayDeque`, ¿por qué `get(i)` y `set(i, x)` usan `(j+i) % a.length`?
46. **[Código]** ¿Por qué `add(i, x)` decide entre mover la mitad izquierda o la mitad derecha según `i < n/2`?
47. **[Código]** ¿Cuál es la intuición para que un deque mueva el lado más corto?
48. **[Código]** En la prueba pública, ¿qué se verifica cuando se agrega `10`, `30` y luego `20` en el medio?
49. **[Código]** En la prueba interna extendida, ¿qué validan las inserciones `deq.add(0, 100)` y `deq.add(4, 200)`?

#### 8. DualArrayDeque y rebalanceo

50. ¿Qué idea central tiene `DualArrayDeque`?
51. **[Código]** ¿Por qué `front` guarda los elementos en orden invertido respecto a la vista lógica?
52. **[Código]** ¿Cómo se explica que `get(i)` use `front.get(front.size() - i - 1)` en la parte delantera?
53. **[Código]** ¿Cuándo se activa `balance()` y por qué la condición usa un factor `3` entre ambos lados?
54. **[Código]** ¿Qué ocurre durante el rebalanceo con `nf = n/2` y `nb = n - nf`?
55. **[Código]** En la prueba pública, ¿qué propiedad se verifica cuando `dual` contiene `5, 6, 7` y luego se elimina el del medio?
56. **[Código]** En la prueba interna extendida, ¿qué intenta comprobar la secuencia de insertar 40 elementos y luego borrar 10 del inicio y 10 del final?

#### 9. RootishArrayStack

57. ¿Qué problema de espacio intenta mejorar `RootishArrayStack` frente a `ArrayStack`?
58. ¿Por qué en `RootishArrayStack` los bloques tienen tamaños `1, 2, 3, ..., r`?
59. **[Código]** ¿Por qué la capacidad total con `r` bloques es `r(r+1)/2`?
60. **[Código]** ¿Qué hace la función `i2b(i)` y por qué necesita una fórmula con raíz cuadrada?
61. **[Código]** ¿Cómo se obtiene el offset local `j = i - b*(b+1)/2` dentro del bloque?
62. ¿Por qué `RootishArrayStack` ya no depende de un único bloque contiguo de memoria?
63. **[Código]** ¿Qué ocurre en `grow()` y `shrink()`?
64. **[Código]** En la prueba pública, ¿qué se comprueba cuando se hace `set(4, 40)` después de insertar 6 elementos?
65. **[Código]** En la prueba interna extendida, ¿qué valida que luego de `remove(10)` el elemento en `get(10)` pase a ser `22`?

#### 10. FastSqrt como apoyo matemático

66. ¿Por qué aparece `FastSqrt` dentro de una semana sobre estructuras basadas en arreglo?
67. **[Código]** ¿Qué relación tiene `FastSqrt` con el cálculo de bloques en `RootishArrayStack`?
68. **[Código]** ¿Qué valida la prueba pública al comparar `FastSqrt::sqrt(x)` con `floor(sqrt(x))` en varios valores?
69. **[Código]** ¿Qué aporta la prueba interna que recorre todos los valores entre `0` y `50000`?

#### 11. Preguntas integradoras

70. Explica la relación entre memoria contigua, `resize()`, costo amortizado y `ArrayStack`.
71. Compara `DengVector` y `ArrayStack` en términos de interfaz, resizing y uso didáctico.
72. Compara `ArrayStack`, `ArrayQueue` y `ArrayDeque` en términos de corrimientos y uso de índices modulares.
73. Compara `ArrayDeque` y `DualArrayDeque`: ¿qué gana cada uno y qué complica cada uno?
74. Compara `ArrayStack` y `RootishArrayStack` en tiempo, simplicidad y desperdicio espacial.
75. ¿Qué estructuras de semana 2 dependen directamente de la idea de arreglo circular?
76. ¿Qué estructuras de semana 2 dependen directamente de redimensionamiento amortizado?
77. ¿Cuál dirías que es la idea más importante de la semana: contigüidad, circularidad, rebalanceo o amortización? Sustenta tu respuesta.
