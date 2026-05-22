### **Ejercicios 5 - Semana 5**


#### Ejercicio 1. Profundidad, altura y camino crítico en un árbol binario

Sea `T` un `BinaryTree<T>` no vacío y sea `u` un nodo cualquiera de `T`.

En la implementación de la semana, `BinaryTree` proporciona métodos para calcular `depth(u)`, `height(u)` y `subtreeSize(u)`.

1. Demuestra que para todo nodo `u` se cumple:

   $$
   depth(u) + height(u) \leq height(T)
   $$

2. Entrega una condición necesaria y suficiente para que se alcance la igualdad.

3. Construye al menos dos árboles de prueba:

   - uno donde la igualdad se cumpla para varios nodos,
   - otro donde la desigualdad sea estricta para algún nodo.

4. Explica la relación entre esta propiedad y la existencia de un camino raíz-hoja de longitud máxima.

#### Ejercicio 2. Tamaño y altura de un subárbol sin recursión

En `BinaryTree<T>` ya existen versiones recursivas para calcular la altura y el tamaño de un subárbol. Reescriba estos cálculos de forma iterativa.

Implementa los siguientes métodos:

```cpp
std::size_t subtreeSizeIterative(Node* u) const;
int heightIterative(Node* u) const;
```

Requisitos:

1. `subtreeSizeIterative(u)` debe devolver el número de nodos del subárbol enraizado en `u`.

2. `heightIterative(u)` debe devolver la altura del subárbol enraizado en `u`.

3. No se permite usar llamadas recursivas.

4. Puede usar `std::stack` o `std::queue`.

5. Compare sus respuestas contra `subtreeSize(u)` y `height(u)` usando árboles:

   - vacíos,
   - degenerados,
   - completos,
   - con ramas desbalanceadas.

Finalmente, indica la complejidad temporal y espacial de cada método.

#### Ejercicio 3. Árbol balanceado por tamaño en tiempo lineal

Un árbol binario está **balanceado por tamaño** si para todo nodo `u`, los tamaños de sus subárboles izquierdo y derecho difieren a lo más en uno.

Implementa:

```cpp
bool isSizeBalanced() const;
```

Requisitos:

1. El método debe ejecutarse en tiempo `O(n)`.

2. No debe recalcular repetidamente el tamaño de los mismos subárboles.

3. Diseña una función auxiliar que, para cada nodo, devuelva simultáneamente:

   - el tamaño del subárbol,
   - si el subárbol está balanceado por tamaño.

Además:

1. Prueba su implementación con un árbol completo.

2. Prueba su implementación con una lista enlazada simulada mediante hijos derechos.

3. Explica por qué una solución que llama a `subtreeSize()` en cada nodo puede tomar `O(n^2)` en el peor caso.

#### Ejercicio 4. Inserción, eliminación y actualización de alturas

En `BinTree<T>`, las operaciones `insertAsLC`, `insertAsRC`, `attachAsLC`, `attachAsRC`, `removeSubtree` y `secede` actualizan tamaños y alturas desde el nodo afectado hacia la raíz.

1. Demuestra que, al insertar o eliminar un subárbol no vacío, el tamaño de todos los ancestros del punto de modificación cambia necesariamente.

2. Demuestra que la altura de esos ancestros puede cambiar, pero no siempre cambia.

3. Demuestra que cualquier nodo que no sea ancestro del punto de modificación conserva su tamaño y su altura.

4. Reescribe `updateHeightAbove(Node* u)` para que termine anticipadamente cuando detecte que la altura de un nodo no cambió.

5. Explica si esta mejora cambia la complejidad asintótica en el peor caso.

#### Ejercicio 5. Correctitud y complejidad de los recorridos

La librería incluye recorridos en preorden, inorden, postorden y por niveles, tanto en versiones recursivas como iterativas.

Considera los métodos:

```cpp
travPre(...)
travPreIterative(...)
travIn(...)
travPost(...)
travPostIterative(...)
travLevel(...)
```

Para cada tipo de recorrido:

1. Indica el orden exacto en que deben visitarse los nodos.

2. Demuestra que cada nodo se visita exactamente una vez.

3. Demuestra que el tiempo de ejecución es `O(n)`.

4. Compara el uso de memoria auxiliar:

   - recursión,
   - pila explícita,
   - cola en recorrido por niveles.

5. Construye un árbol de ejemplo y muestra las secuencias producidas por:

   - preorden,
   - inorden,
   - postorden,
   - niveles.


#### Ejercicio 6. Búsqueda, cotas y eliminación en un árbol binario de búsqueda

La clase `BinarySearchTree<T>` implementa operaciones como `findLast`, `findEQ`, `lowerBound`, `upperBound`, `add`, `remove`, `splice`, `rotateLeft` y `rotateRight`.

Considera un BST sin elementos repetidos.

1. Explica la diferencia entre:

   - `findEQ(x)`,
   - `lowerBound(x)`,
   - `upperBound(x)`.

2. Demuestra que `lowerBound(x)` devuelve el menor elemento mayor o igual que `x`, si existe.

3. Demuestra que `upperBound(x)` devuelve el menor elemento estrictamente mayor que `x`, si existe.

4. Inserta los valores:

```cpp
8, 3, 10, 1, 6, 14, 4, 7, 13
```

Luego indica el resultado de:

```cpp
findEQ(6)
lowerBound(5)
upperBound(6)
lowerBound(15)
```

5. Elimina un nodo hoja, un nodo con un hijo y un nodo con dos hijos. Después de cada eliminación, verifica que el árbol sigue cumpliendo la propiedad BST.


#### Ejercicio 7. Heap binario: `bubbleUp`, `trickleDown` y `heapify`

La clase `BinaryHeap<T>` usa una representación implícita en arreglo y define las funciones `left(i)`, `right(i)`, `parent(i)`, `add`, `remove`, `bubbleUp`, `trickleDown`, `heapify` e `isHeap`.

1. Explica por qué los índices:

```cpp
left(i) = 2*i + 1
right(i) = 2*i + 2
parent(i) = (i - 1) / 2
```

representan correctamente un árbol binario completo almacenado en un arreglo.

2. Demuestra que `bubbleUp(i)` restaura la propiedad de heap después de insertar un elemento al final del arreglo.

3. Demuestra que `trickleDown(i)` restaura la propiedad de heap después de mover la última hoja a la raíz.

4. Compara dos formas de construir un heap con `n` elementos:

   - insertando uno por uno con `add`,
   - usando `heapify`.

5. Justifica por qué `heapify` puede ejecutarse en tiempo `O(n)`, mientras que insertar `n` veces cuesta `O(n log n)` en el peor caso.

6. Prueba su implementación con el arreglo:

```cpp
9, 4, 7, 1, 0, 3, 2, 8, 5, 6
```

y verifica el resultado usando `isHeap()`.


#### Ejercicio 8. Sucesor y predecesor inorden en `BinNode`

La clase `BinNode` incluye punteros `parent`, `left`, `right` y operaciones de navegación como `succ()` y `pred()`.

1. Explica qué significa que un nodo `v` tenga un **sucesor inorden**.

2. Dibuja los dos casos posibles para calcular `succ()`:

   - `v` tiene hijo derecho,
   - `v` no tiene hijo derecho.

3. Implementa el método simétrico:

```cpp
BinNodePosi(T) pred();
```

4. Tu implementación debe considerar los dos casos:

   - si `v` tiene hijo izquierdo, el predecesor está en el subárbol izquierdo,
   - si `v` no tiene hijo izquierdo, debe subir por los ancestros hasta encontrar el primer ancestro para el cual `v` pertenece a su subárbol derecho.

5. Demuestra que `succ()` y `pred()` toman tiempo `O(h)`, donde `h` es la altura del árbol.


#### Ejercicio 9. Análisis de `travIn_I3` sin pila auxiliar

La librería incluye varias versiones de recorrido inorden, incluyendo una versión iterativa sin pila auxiliar explícita.

Considera el recorrido inorden iterativo que usa `succ()` para avanzar al siguiente nodo.

1. Explica por qué el recorrido sigue produciendo el orden inorden correcto.

2. Aunque `succ()` puede tomar `O(h)` en una llamada individual, demuestre que el recorrido completo sigue siendo `O(n)`.

3. Justifica su respuesta usando el hecho de que cada arista del árbol se recorre un número constante de veces.

4. Compara esta versión contra una implementación con `std::stack`.

5. Indica la complejidad espacial de ambas versiones.

Luego, intenta reescribir el algoritmo de modo que no use:

```cpp
std::stack
bool backtrack
```

y dependa únicamente de punteros `parent`, `left`, `right` y de la relación entre el nodo actual y el nodo previamente visitado.


#### Ejercicio 10. Capacidad máxima de la cola en recorrido por niveles

El recorrido por niveles usa una cola auxiliar para visitar los nodos de arriba hacia abajo y de izquierda a derecha.

Sea `T` un árbol binario con `n` nodos.

1. Demuestra que durante el recorrido por niveles la cola nunca necesita almacenar más de `ceil(n/2)` nodos.

2. Identifica qué árboles pueden alcanzar realmente esa cota.

3. Explica por qué un árbol completo o casi completo puede requerir una cola de tamaño cercano a `n/2`.

4. Entrega un ejemplo con `n = 15` nodos y muestre el tamaño de la cola después de procesar cada nivel.

5. Indica la complejidad temporal y espacial del recorrido por niveles.


#### Ejercicio 11. Numeración por niveles y representación implícita de árboles completos

El `BinaryHeap` de la semana usa representación implícita en arreglo mediante las funciones `left(i)`, `right(i)` y `parent(i)`.

Considera un árbol binario completo cuyos nodos se numeran en orden por niveles empezando desde `0`.

1. Demuestra que, para un nodo con índice `i`, se cumple:

```cpp
left(i)  = 2*i + 1
right(i) = 2*i + 2
parent(i) = (i - 1) / 2
```

2. Demuestra que cada índice `i` con `0 <= i < n` corresponde a un único nodo.

3. Explica por qué esta numeración permite almacenar el árbol sin punteros.

4. Relaciona esta representación con la implementación de `BinaryHeap<T>`.

5. Diseña una función que determine si el nodo con índice `a` es ancestro del nodo con índice `b`.

Sugerencia: sube desde `b` usando repetidamente:

```cpp
b = (b - 1) / 2;
```

hasta llegar a la raíz o encontrar `a`.


#### Ejercicio 12. Propiedad de suma de ancestros

Sea `T` un árbol binario con valores numéricos en sus nodos. Para cada nodo `u`, definimos `sumAncestors(u)` como la suma de los valores de todos sus ancestros propios.

Diseña un algoritmo que determine si para todo nodo `u` se cumple:

```cpp
u->data >= sumAncestors(u)
```

Para la raíz, la suma de ancestros se considera `0`.

1. Implementa  una versión recursiva en tiempo `O(n)`.

2. Implementa una versión iterativa equivalente.

3. La versión iterativa puede usar una pila de pares:

```cpp
std::stack<std::pair<Node*, T>>
```

donde el segundo componente almacena la suma acumulada de ancestros.

4. Demuestra que ambos algoritmos son correctos.

5. Indica la complejidad temporal y espacial.


#### Ejercicio 13. Reemplazo de cada nodo por el máximo de sus descendientes

Sea `T` un árbol binario con valores comparables.

Diseña un algoritmo que reemplace el valor de cada nodo por el valor máximo almacenado originalmente en su subárbol.

Por ejemplo, si un nodo `u` tiene como descendientes valores:

```cpp
3, 8, 5, 12, 1
```

entonces después del algoritmo `u->data` debe ser `12`.

1. Implementa una versión recursiva usando postorden.

2. Explica por qué el recorrido postorden es necesario o conveniente.

3. Implementa una versión iterativa usando una pila.

4. Asegúrate de no perder los valores originales antes de calcular el máximo.

5. Demuestra que el algoritmo toma tiempo `O(n)`.

6. Indica la complejidad espacial en:

   - un árbol balanceado,
   - un árbol degenerado.


