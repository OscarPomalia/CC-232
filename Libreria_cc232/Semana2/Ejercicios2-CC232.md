### Lista de ejercicios - Semana 2

#### Ejercicio 1. Tiempo promedio vs tiempo amortizado en arreglos dinámicos

En la Semana 2 se trabaja con arreglos dinámicos, `resize()`, memoria contigua y análisis amortizado usando las implementaciones de `DengVector`, `ArrayStack` y `FastArrayStack`.

##### Se pide

1. Explicar, con tus palabras, la diferencia entre **tiempo promedio** y **tiempo amortizado**.
2. Construir una secuencia concreta de operaciones sobre `DengVector` o `ArrayStack` en la que una operación individual cueste mucho más que las demás.
3. Explicar por qué ese peor caso no contradice que el costo amortizado por operación sea `O(1)` en inserciones al final.
4. Indicar qué papel cumple la política de duplicar capacidad en ese análisis.
5. Comparar esta idea con lo que ocurre si la capacidad creciera por una cantidad fija en cada expansión.

#### Ejercicio 2. Copia profunda y seguridad de `copyFrom()`

La clase `DengVector` encapsula un arreglo dinámico y debe evitar aliasing accidental entre dos vectores distintos.

##### Se pide

1. Revisar la implementación de copia en `Semana2/include/DengVector.h`.
2. Explicar por qué el arreglo destino debe ser físicamente independiente del arreglo fuente.
3. Diseñar una prueba corta en C++ que muestre que la copia realizada es profunda y no superficial.
4. Ejecutar la prueba modificando un vector original y verificando que la copia no cambie.
5. Explicar qué problema aparecería si ambos objetos compartieran el mismo arreglo interno.

#### Ejercicio 3. Modificar `expand()`: crecimiento por constante vs duplicación

En `DengVector`, la expansión sigue la estrategia clásica de duplicar capacidad. Esta decisión está ligada al análisis amortizado.

##### Se pide

1. Crear una variante experimental de `DengVector` en la que `expand()` aumente la capacidad por una constante fija `c`.
2. Mantener la misma interfaz pública básica del vector.
3. Comparar conceptualmente esta variante con la versión original que duplica capacidad.
4. Explicar por qué el crecimiento por constante fija empeora el costo amortizado de inserciones repetidas.
5. Dar un ejemplo de secuencia de inserciones donde esa diferencia se vuelva evidente.

#### Ejercicio 4. `shrink()` y reducción amortizada

La reducción de capacidad también forma parte del diseño de un arreglo dinámico eficiente.

##### Se pide

1. Revisar cómo se reduce capacidad en `DengVector` y cómo se redimensiona el arreglo en `ArrayStack`.
2. Explicar qué condición debe cumplirse para que una reducción de capacidad sea razonable.
3. Justificar por qué no conviene reducir el arreglo después de cada eliminación.
4. Argumentar informalmente por qué el costo amortizado de las reducciones puede mantenerse en `O(1)` por operación.
5. Comparar el papel de `expand()` y `shrink()` dentro del equilibrio entre tiempo y espacio.

#### Ejercicio 5. Búsqueda secuencial en `DengVector`

La búsqueda en un vector no ordenado usa únicamente comparación por igualdad y no puede aprovechar orden alguno.

##### Se pide

1. Revisar la implementación de `find(e, lo, hi)` en `DengVector`.
2. Explicar por qué el mejor caso es `O(1)` y el peor caso es `O(n)`.
3. Indicar qué ocurre si existen varias coincidencias y cuál de ellas devuelve la implementación.
4. Probar el método con al menos tres casos:
   * elemento al final del intervalo
   * elemento ausente
   * múltiples repeticiones.
5. Justificar por qué esta operación es sensible a la entrada y no solo al tamaño del vector.

#### Ejercicio 6. Inserción y desplazamientos en memoria contigua

Insertar en una estructura basada en arreglo obliga a preservar la contigüidad física de los elementos.

##### Se pide

1. Revisar `insert(r, e)` en `DengVector` y `add(i, x)` en `ArrayStack`.
2. Explicar por qué insertar en una posición intermedia obliga a desplazar un sufijo del arreglo.
3. Justificar por qué el recorrido para desplazar elementos debe hacerse de atrás hacia adelante.
4. Explicar por qué, si la posición de inserción se distribuye uniformemente, el costo promedio es `O(n)`.
5. Comparar el caso de insertar al final con el caso de insertar al inicio.

#### Ejercicio 7. Eliminación por intervalo y orden correcto de copiado

Eliminar un intervalo completo puede implementarse de forma más eficiente que eliminar elemento por elemento.

##### Se pide

1. Revisar `remove(lo, hi)` en `DengVector`.
2. Explicar por qué no conviene implementar esta operación llamando repetidamente a `remove(r)` para cada posición del intervalo.
3. Describir cuál es la estrategia correcta para compactar el arreglo después de eliminar `[lo, hi)`.
4. Construir un ejemplo pequeño que muestre qué tipo de error aparece si el copiado se hace en un orden incorrecto.
5. Comparar el costo de eliminar un intervalo en bloque contra eliminarlo elemento por elemento.

#### Ejercicio 8. Recorrido uniforme con `traverse()`

La interfaz `traverse()` permite procesar todos los elementos del vector de manera uniforme.

##### Se pide

1. Revisar `traverse()` en `DengVector`.
2. Implementar una operación `decrease()` que reste `1` a todos los elementos del vector.
3. Implementar una operación `double()` que duplique el valor de todos los elementos del vector.
4. Probar ambas operaciones sobre un ejemplo pequeño y mostrar el estado del vector antes y después.
5. Explicar por qué `traverse()` es una buena interfaz para separar recorrido y operación aplicada.

#### Ejercicio 9. Inserción múltiple eficiente con `addAll(i, c)`

Agregar varios elementos de una sola vez permite razonar mejor sobre desplazamientos y redimensionamiento.

##### Se pide

1. Tomar como base `ArrayStack` o `FastArrayStack`.
2. Explicar por qué no es eficiente implementar `addAll(i, c)` como una secuencia de llamadas repetidas a `add(i, x)`.
3. Diseñar una versión más eficiente que haga, como máximo, un redimensionamiento principal y un desplazamiento grande del bloque afectado.
4. Implementar una versión sencilla de `addAll(i, c)` para insertar todos los elementos de un `std::vector<T>` en la posición `i`.
5. Comparar conceptualmente el costo de la solución ingenua con el de la solución mejorada.

#### Indicaciones generales

En todos los ejercicios:

* Justifica tus respuestas
* Usa notación asintótica cuando corresponda
* Cuando se pida correctitud, indica con claridad la invariante, el inicio, el mantenimiento y la terminación
* Cuando se use un ADT, distingue entre interfaz e implementación
* Apoya tus respuestas en el código de la `Semana 2`, especialmente en:
  * `Semana2/include/DengVector.h`
  * `Semana2/include/ArrayStack.h`
  * `Semana2/include/FastArrayStack.h`
  * `Semana2/include/RootishArrayStack.h`
  * `Semana2/pruebas_publicas/test_public_week2.cpp`
  * `Semana2/pruebas_internas/resize_stress_week2.cpp`
* Revisa las lecturas:
  * `Semana2/lecturas/Lectura4-Deng.md`
  * `Semana2/lecturas/Lectura5-Morin.md`
