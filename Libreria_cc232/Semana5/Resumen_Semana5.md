### Resumen final - Semana 5

#### Árboles binarios, recorridos, árboles binarios de búsqueda y heaps

La Semana 5 marca una transición importante dentro de CC-232. Hasta la Semana 4, las estructuras estudiadas tenían una organización esencialmente lineal: arreglos, vectores, listas, pilas y colas. En ellas, los elementos se recorren siguiendo una secuencia natural o una política temporal como `LIFO` o `FIFO`. En la Semana 5 se introduce una estructura semilineal y jerárquica: el árbol binario.

Un árbol binario no impone por sí mismo una única secuencia lineal sobre sus elementos. La relación principal ya no es "siguiente" o "anterior", sino padre, hijo izquierdo, hijo derecho, ancestro, descendiente y subárbol. 
Sin embargo, mediante recorridos como preorden, inorden, postorden o recorrido por niveles, la estructura jerárquica puede transformarse temporalmente en una secuencia. Esta idea conecta directamente con la lectura de Deng: el árbol no es lineal en su forma natural, pero puede linealizarse mediante un orden de visita.

La semana también distingue tres niveles técnicos. El primer nivel es la infraestructura enlazada de árbol binario, representada por `BinNode` y `BinTree`. 
El segundo nivel es la navegación y consulta estructural de `BinaryTree`, con profundidad, altura, tamaño de subárbol, sucesor, predecesor, iteración inorden y representación ASCII. 
El tercer nivel corresponde a estructuras especializadas: `BinarySearchTree`, que añade una propiedad de orden sobre las claves, y `BinaryHeap`, que añade una propiedad de prioridad sobre una representación implícita en arreglo.

El objetivo no es solo construir árboles. El objetivo es comprender qué invariante mantiene cada estructura, qué operaciones dependen de punteros, qué operaciones dependen de la altura, qué diferencia hay entre orden y prioridad, y qué evidencia permite defender que el código es correcto.

#### 1. Árbol como estructura jerárquica

Desde la teoría de grafos, un árbol es un grafo conexo y acíclico. En estructuras de datos casi siempre se trabaja con árboles enraizados: se elige un nodo 
especial llamado raíz y, desde él, se definen las relaciones jerárquicas del resto de nodos.

La raíz no tiene padre. Todo nodo distinto de la raíz tiene exactamente un padre. Los nodos directamente debajo de otro nodo son sus hijos. Los nodos ubicados 
sobre un camino hacia la raíz son ancestros. Los nodos ubicados debajo de un nodo son descendientes. El conjunto formado por un nodo y todos sus descendientes se llama subárbol.

| Concepto | Significado |
|---|---|
| Raíz | Nodo principal desde donde se organiza el árbol. |
| Padre | Nodo inmediatamente superior a otro. |
| Hijo | Nodo inmediatamente inferior a otro. |
| Hoja | Nodo sin hijos. |
| Nodo interno | Nodo con al menos un hijo. |
| Ancestro | Nodo ubicado en el camino desde un nodo hacia la raíz. |
| Descendiente | Nodo incluido dentro del subárbol de otro nodo. |
| Subárbol | Nodo junto con todos sus descendientes. |
| Profundidad | Número de aristas desde la raíz hasta el nodo. |
| Altura | Longitud del camino más largo desde el nodo hasta una hoja. |

La profundidad de la raíz es `0`. Si un nodo está en el nivel inmediatamente inferior a la raíz, su profundidad es `1`. 
La altura de una hoja es `0` y la altura de un árbol vacío se toma como `-1`. Esta convención permite escribir fórmulas uniformes, por ejemplo:

```cpp
height(u) = 1 + max(height(u->left), height(u->right))
```

Si `u` es una hoja, ambos hijos son nulos y la fórmula produce `1 + max(-1, -1) = 0`.

#### 2. Árbol binario y árbol binario ordenado

Un árbol binario es un árbol donde cada nodo tiene a lo más dos hijos. En un árbol binario ordenado se distingue entre hijo izquierdo e hijo derecho. 
Esta distinción no es decorativa: muchos algoritmos dependen de que el subárbol izquierdo y el subárbol derecho tengan significado separado.

En un árbol binario, cada nodo puede encontrarse en uno de estos estados estructurales:

| Estado | Condición |
|---|---|
| Raíz | `parent == nullptr` |
| Hoja | `left == nullptr` y `right == nullptr` |
| Hijo izquierdo | `parent != nullptr` y `parent->left == this` |
| Hijo derecho | `parent != nullptr` y `parent->right == this` |
| Nodo con un hijo | Tiene exactamente un hijo no nulo. |
| Nodo con dos hijos | Tiene hijo izquierdo e hijo derecho. |

Morin también introduce la idea de nodos externos. Si un nodo real no tiene hijo izquierdo o derecho, se puede imaginar que ese espacio vacío contiene un nodo externo. 
Con esta convención, un árbol binario con `n >= 1` nodos reales tiene `n + 1` nodos externos. Esta observación es útil para razonamientos inductivos sobre árboles binarios.

#### 3. Árbol multicamino y conversión a árbol binario

Deng presenta árboles multicamino para mostrar que un árbol puede tener más de dos hijos por nodo. Existen varias formas de representarlos.

| Representación | Ventaja | Desventaja |
|---|---|---|
| Vector de padres | Encontrar el padre es directo. | Encontrar hijos exige recorrer todos los nodos. |
| Lista de hijos por nodo | Enumerar hijos es eficiente. | Subir al padre puede no ser directo. |
| Padre más lista de hijos | Permite subir y bajar. | Actualizar listas de hijos puede ser costoso. |
| Hijo mayor más hermano | Reduce el árbol ordenado a dos enlaces por nodo. | La interpretación requiere conocer la conversión. |

La conversión hijo mayor más hermano permite representar un árbol multicamino ordenado como árbol binario. 
El puntero al hijo mayor se interpreta como hijo izquierdo. El puntero al siguiente hermano se interpreta como hijo derecho. Esta conversión muestra por qué los árboles binarios son tan expresivos: aunque tienen solo dos enlaces por nodo, pueden modelar estructuras jerárquicas más generales.

#### 4. Árboles de codificación y código prefijo

La lectura de Deng usa los árboles binarios para explicar esquemas de codificación. En una codificación binaria, cada carácter de un alfabeto se reemplaza por una cadena de bits. 
Codificar consiste en consultar una tabla de códigos y concatenar los códigos de cada carácter. Decodificar consiste en leer el flujo binario y reconstruir los caracteres originales.

El problema aparece cuando un código puede ser prefijo de otro. Por ejemplo, si un carácter tiene código `11` y otro tiene código `111`, al leer una secuencia que empieza con `111` puede existir ambigüedad.
Para evitarlo se usa una codificación prefija libre de ambigüedad: ningún código asignado a un carácter puede ser prefijo del código de otro carácter.

Un árbol binario permite visualizar esta propiedad. Cada movimiento a la izquierda puede representar el bit `0` y cada movimiento a la derecha puede representar el bit `1`. 
El código de un nodo es la cadena del camino desde la raíz hasta ese nodo. Si todos los caracteres se ubican en hojas, ningún carácter será ancestro de otro y,por tanto, ningún código será prefijo de otro.

La decodificación se realiza escaneando bits desde la raíz. Cada bit baja un nivel en el árbol. Cuando se alcanza una hoja, se emite el carácter y se vuelve
a la raíz. Esta estrategia es en línea porque puede comenzar antes de recibir todo el flujo binario.

#### 5. `BinNode`: unidad básica del árbol enlazado

La clase `BinNode` representa el nodo individual de un árbol binario enlazado. En la librería de la Semana 5, cada nodo almacena:

| Campo | Papel |
|---|---|
| `data` | Valor almacenado en el nodo. |
| `parent` | Puntero al padre. |
| `left` | Puntero al hijo izquierdo. |
| `right` | Puntero al hijo derecho. |
| `height` | Altura almacenada o mantenida por la estructura. |

La presencia del puntero `parent` es una decisión de diseño importante. Permite subir desde un nodo hacia la raíz, calcular profundidad, encontrar sucesores y predecesores inorden, actualizar alturas hacia arriba y simplificar algunas operaciones de eliminación y rotación. 
A cambio, exige mantener una consistencia estricta: si `u->left == v`, entonces debe cumplirse `v->parent == u`; si `u->right == v`, entonces debe cumplirse `v->parent == u`.

`BinNode` ofrece predicados estructurales como `hasLeft()`, `hasRight()`, `isRoot()`, `isLeaf()`, `isLeftChild()` e `isRightChild()`. Estos métodos no cambian la estructura, pero permiten escribir algoritmos más claros. También ofrece `insertAsLC` e `insertAsRC`, que insertan un
nuevo nodo como hijo izquierdo o derecho, siempre que ese hijo no exista todavía.

La operación `size()` calcula el tamaño del subárbol enraizado en el nodo actual. Su definición es recursiva: el tamaño del subárbol es uno más el tamaño del subárbol izquierdo y el tamaño del subárbol derecho. 
Su costo es `O(k)`, donde `k` es la cantidad de nodos en ese subárbol.

#### 6. Sucesor y predecesor inorden

El sucesor inorden de un nodo es el nodo que aparecería inmediatamente después de él en un recorrido inorden. El predecesor inorden es el nodo que aparecería inmediatamente antes.

Para calcular `succ()` existen dos casos:

| Caso | Regla |
|---|---|
| El nodo tiene hijo derecho | El sucesor es el nodo más a la izquierda del subárbol derecho. |
| El nodo no tiene hijo derecho | Se sube por `parent` hasta encontrar el primer ancestro para el cual el nodo actual quedó en su subárbol izquierdo. |

Para calcular `pred()` se aplica la regla simétrica:

| Caso | Regla |
|---|---|
| El nodo tiene hijo izquierdo | El predecesor es el nodo más a la derecha del subárbol izquierdo. |
| El nodo no tiene hijo izquierdo | Se sube por `parent` hasta encontrar el primer ancestro para el cual el nodo actual quedó en su subárbol derecho. |

Estas operaciones cuestan `O(h)` en el peor caso, donde `h` es la altura del árbol. Sin embargo, cuando se usan para recorrer todo un árbol mediante sucesores, cada arista se recorre un número constante de veces, por lo que el recorrido completo puede justificarse como `O(n)`.

#### 7. `BinTree`: administración del árbol completo

`BinTree` administra la estructura completa. Mientras `BinNode` representa un nodo individual, `BinTree` mantiene la raíz, el tamaño total y las operaciones que modifican la topología.

| Método | Responsabilidad |
|---|---|
| `insertAsRoot` | Crea la raíz de un árbol inicialmente vacío. |
| `insertAsLC` | Inserta un hijo izquierdo y actualiza metadatos. |
| `insertAsRC` | Inserta un hijo derecho y actualiza metadatos. |
| `updateHeight` | Recalcula la altura de un nodo a partir de sus hijos. |
| `updateHeightAbove` | Actualiza alturas desde un nodo hacia la raíz. |
| `attachAsLC` | Adjunta otro árbol como subárbol izquierdo. |
| `attachAsRC` | Adjunta otro árbol como subárbol derecho. |
| `secede` | Desprende un subárbol y lo devuelve como árbol independiente. |
| `removeSubtree` | Elimina y libera todos los nodos de un subárbol. |
| `checkParentLinks` | Verifica consistencia entre hijos y padres. |

La diferencia entre `secede` y `removeSubtree` es esencial. `secede` separa un subárbol sin destruirlo. El subárbol desprendido queda encapsulado como un nuevo árbol. 
En cambio, `removeSubtree` elimina los nodos y libera memoria. Por eso, `secede` preserva los datos y `removeSubtree` los destruye.

Cada modificación estructural debe actualizar tamaños y alturas. El tamaño cambia necesariamente para los ancestros del punto de modificación cuando se inserta, adjunta, separa o elimina un subárbol. 
La altura puede cambiar, pero no siempre cambia. Por ejemplo, insertar un nodo en una rama que no aumenta la rama más larga puede conservar la altura de algunos ancestros.

#### 8. `BinaryTree`: navegación y consultas estructurales

`BinaryTree` extiende la infraestructura base con operaciones de consulta y navegación. Sus métodos se concentran en estudiar la forma del árbol, no una propiedad de búsqueda ni de prioridad.

| Método | Idea |
|---|---|
| `depth(u)` | Cuenta cuántos pasos hay desde `u` hasta la raíz. |
| `height(u)` | Calcula la altura del subárbol enraizado en `u`. |
| `subtreeSize(u)` | Cuenta los nodos del subárbol de `u`. |
| `firstNode()` | Retorna el primer nodo inorden. |
| `lastNode()` | Retorna el último nodo inorden. |
| `nextNode(u)` | Avanza al sucesor inorden. |
| `prevNode(u)` | Retrocede al predecesor inorden. |
| `iterateBySuccessor()` | Recorre inorden usando sucesores. |
| `iterateByPredecessor()` | Recorre inorden inverso usando predecesores. |
| `asciiArt()` | Genera una representación textual del árbol. |

La función `depth(u)` sube por enlaces `parent`, de modo que su costo depende de la profundidad de `u`. La función `height(u)` baja recursivamente por los hijos, de modo que su costo depende del tamaño del subárbol consultado. `subtreeSize(u)` también recorre el subárbol completo.

Una propiedad útil para defensa es:

```text
depth(u) + height(u) <= height(T)
```

La igualdad ocurre exactamente cuando `u` pertenece a algún camino raíz-hoja de longitud máxima. Si `u` no está sobre ningún camino crítico, la desigualdad es estricta.

#### 9. Recorridos de árboles binarios

Recorrer un árbol significa visitar cada nodo una y solo una vez siguiendo una regla. Los recorridos convierten temporalmente una estructura jerárquica en una secuencia. Esta es la manera principal de observar, validar y procesar árboles.

| Recorrido | Orden de visita |
|---|---|
| Preorden | Nodo, subárbol izquierdo, subárbol derecho. |
| Inorden | Subárbol izquierdo, nodo, subárbol derecho. |
| Postorden | Subárbol izquierdo, subárbol derecho, nodo. |
| Por niveles | Nivel por nivel, de izquierda a derecha. |

El preorden es útil para copiar o serializar la estructura desde la raíz. El inorden es fundamental en árboles binarios de búsqueda porque produce las claves en orden creciente. 
El postorden es útil para destruir, liberar o resumir subárboles porque procesa hijos antes que el nodo padre. El recorrido por niveles usa una cola y permite observar la forma del árbol capa por capa.

La librería incluye versiones recursivas e iterativas. Las versiones recursivas son simples porque reflejan la definición autorreferencial del árbol.
Las versiones iterativas reemplazan la pila de llamadas por una pila explícita, una cola o por navegación usando `parent`, `succ()` y `pred()`.

| Versión | Estructura auxiliar habitual | Costo temporal | Espacio auxiliar |
|---|---|---|---|
| Preorden recursivo | Pila de llamadas | `O(n)` | `O(h)` |
| Preorden iterativo | `std::stack` | `O(n)` | `O(h)` en promedio, `O(n)` peor caso |
| Inorden recursivo | Pila de llamadas | `O(n)` | `O(h)` |
| Inorden iterativo con pila | `std::stack` | `O(n)` | `O(h)` |
| Inorden por sucesor | Punteros `parent` y `succ()` | `O(n)` amortizado | `O(1)` adicional |
| Postorden recursivo | Pila de llamadas | `O(n)` | `O(h)` |
| Postorden iterativo | Una o dos pilas | `O(n)` | `O(n)` peor caso |
| Por niveles | `std::queue` | `O(n)` | Hasta `O(n)` |

El recorrido por niveles puede requerir mucha memoria en un árbol completo, porque la cola puede almacenar una fracción grande de los nodos del último nivel. 
En contraste, en un árbol degenerado la cola permanece pequeña.

#### 10. `BinarySearchTree`: árbol binario con propiedad de orden

Un `BinarySearchTree` es un árbol binario donde cada nodo almacena una clave tomada de un orden total y cumple la propiedad BST:

```text
Para todo nodo u:
los valores del subárbol izquierdo de u son menores que u.data;
los valores del subárbol derecho de u son mayores que u.data.
```

Esta propiedad convierte un árbol binario estructural en una estructura de búsqueda ordenada. En un árbol binario común, para encontrar un valor podría ser 
necesario revisar todos los nodos. En un BST, cada comparación permite descartar un subárbol completo.

Si se busca `x` en un nodo `u`, hay tres casos:

| Comparación | Acción |
|---|---|
| `x < u.data` | Continuar por el hijo izquierdo. |
| `x > u.data` | Continuar por el hijo derecho. |
| `x == u.data` | La búsqueda fue exitosa. |

La operación `findEQ(x)` busca una coincidencia exacta. Si `x` no existe, falla. La operación `lowerBound(x)` busca el menor valor mayor o igual que `x`. 
La operación `upperBound(x)` busca el menor valor estrictamente mayor que `x`. Estas operaciones muestran que un BST no solo sirve para pertenencia, sino 
también para consultas de orden.

| Operación | Resultado esperado |
|---|---|
| `findEQ(x)` | Nodo con clave exactamente igual a `x`, si existe. |
| `find(x)` | En esta librería actúa como `lowerBound(x)`. |
| `lowerBound(x)` | Menor clave mayor o igual que `x`. |
| `upperBound(x)` | Menor clave estrictamente mayor que `x`. |
| `minNode()` | Menor clave del árbol. |
| `maxNode()` | Mayor clave del árbol. |
| `contains(x)` | Indica si existe una clave exacta. |

#### 11. Inserción en BST

Insertar en un BST reutiliza la lógica de búsqueda. Primero se busca el valor. Si ya existe, la inserción se rechaza para mantener claves únicas. 
Si no existe, el nuevo nodo se conecta como hijo del último nodo visitado.

La operación puede dividirse conceptualmente en dos partes:

| Función | Papel |
|---|---|
| `findLast(x)` | Encuentra el último nodo alcanzado por la búsqueda. |
| `addChild(parent, node)` | Conecta el nuevo nodo como hijo izquierdo o derecho. |

El nuevo nodo se inserta a la izquierda si su clave es menor que la del padre. Se inserta a la derecha si su clave es mayor. 
Después de conectar el nodo, deben actualizarse los enlaces `parent` y las alturas hacia la raíz.

La complejidad de inserción es `O(h)`, donde `h` es la altura del árbol. En un BST balanceado, `h = O(log n)`. En un BST degenerado, `h = O(n)`.

#### 12. Eliminación en BST y `splice`

Eliminar en un BST exige preservar la propiedad de orden. Hay tres casos principales:

| Caso | Estrategia |
|---|---|
| Nodo hoja | Se desconecta del padre. |
| Nodo con un hijo | Se reemplaza por su único hijo. |
| Nodo con dos hijos | Se copia el sucesor inorden y luego se elimina ese sucesor. |

La operación `splice(u)` elimina estructuralmente un nodo que tiene a lo más un hijo. Si `u` tiene un hijo, el padre de `u` pasa a apuntar a ese hijo y el hijo
actualiza su `parent`. Si `u` es la raíz, la raíz del árbol se actualiza.

Cuando el nodo tiene dos hijos, se busca su sucesor inorden: el menor nodo del subárbol derecho. Ese sucesor contiene la menor clave mayor que la clave eliminada. 
Se copia su dato al nodo original y luego se elimina el sucesor mediante `splice`, porque ese sucesor no tiene hijo izquierdo.

Después de eliminar, deben seguir siendo ciertos estos invariantes:

| Invariante | Razón |
|---|---|
| Propiedad BST | El inorden debe seguir ordenado. |
| Enlaces `parent` consistentes | Todo hijo debe apuntar al padre correcto. |
| Tamaño actualizado | El árbol debe descontar un nodo. |
| Alturas actualizadas | Las consultas estructurales deben seguir siendo coherentes. |

#### 13. Rotaciones en BST

Las rotaciones son transformaciones locales que cambian la forma del árbol sin cambiar el orden inorden de las claves. 
Son esenciales para estructuras balanceadas posteriores como AVL, Red-Black Tree, treaps y splay trees.

Una rotación izquierda sobre un nodo `u` sube a su hijo derecho `w`. El subárbol izquierdo de `w` pasa a ser el subárbol derecho de `u`. 
Luego `u` pasa a ser hijo izquierdo de `w`. La rotación derecha es simétrica: sube al hijo izquierdo y desplaza su subárbol derecho.

La razón por la que una rotación preserva el BST es que respeta las relaciones de orden entre los tres bloques involucrados. 
En una rotación izquierda, si `u < w`, entonces todos los valores del subárbol que se mueve desde `w.left` están entre `u` y `w`. 
Por eso pueden convertirse en `u.right` sin violar la propiedad de búsqueda.

Las rotaciones tienen costo `O(1)` para cambiar punteros locales, más el costo de actualizar alturas hacia arriba si la implementación mantiene ese metadato.

#### 14. Complejidad del BST no balanceado

Morin enfatiza una limitación importante: un `BinarySearchTree` no balanceado no garantiza altura logarítmica. Si las claves se insertan en orden creciente, el 
árbol puede degenerar en una lista enlazada. En ese caso, buscar, insertar y eliminar cuestan `O(n)`.

| Forma del BST | Altura | Costo de `find`, `add`, `remove` |
|---|---|---|
| Balanceado | `O(log n)` | `O(log n)` |
| Degenerado | `O(n)` | `O(n)` |
| No balanceado arbitrario | `h` | `O(h)` |

La Semana 5 no resuelve todavía el problema de balanceo automático. Lo deja claramente planteado. Las rotaciones y la construcción balanceada desde un arreglo
ordenado preparan el camino para AVL, Red-Black Tree y otras estructuras que sí controlan la altura.

#### 15. `BinaryHeap`: árbol de prioridad en arreglo implícito

Un heap binario es una estructura para colas de prioridad. En la Semana 5 se implementa un min-heap: el menor elemento debe quedar en la raíz. 
A diferencia de `BinaryTree` y `BinarySearchTree`, el heap no usa nodos enlazados. Se almacena en un `std::vector` como árbol binario completo implícito.

En una numeración por niveles desde `0`, las relaciones entre índices son:

```cpp
left(i) = 2 * i + 1
right(i) = 2 * i + 2
parent(i) = (i - 1) / 2
```

Estas fórmulas permiten navegar por el árbol sin punteros. El índice `0` corresponde a la raíz. Los hijos de cada posición se calculan aritméticamente. 
El padre también se calcula con división entera.

La propiedad de min-heap es:

```text
Para todo índice i, si left(i) existe, data[i] <= data[left(i)].
Para todo índice i, si right(i) existe, data[i] <= data[right(i)].
```

Esta propiedad garantiza que `top()` devuelva el mínimo. Sin embargo, no garantiza que un recorrido inorden o por niveles produzca una secuencia ordenada. 
El heap solo ordena parcialmente por prioridad local entre padre e hijos.

#### 16. Inserción, extracción y `heapify`

La operación `add(x)` inserta el nuevo elemento al final del vector para conservar la forma de árbol completo. Luego aplica `bubbleUp(i)`: mientras el nuevo 
elemento sea menor que su padre, se intercambia con él. Así se restaura la propiedad de heap desde abajo hacia arriba.

La operación `remove()` extrae el mínimo ubicado en la raíz. Para no dejar un hueco en el árbol completo, mueve el último elemento del vector a la raíz, elimina la última posición y aplica `trickleDown(0)`. 
En cada paso, el elemento baja intercambiándose con el menor de sus hijos cuando alguno de ellos viola la propiedad de heap.

| Operación | Idea | Costo |
|---|---|---|
| `top()` | Consulta la raíz. | `O(1)` |
| `add(x)` | Inserta al final y aplica `bubbleUp`. | `O(log n)` |
| `remove()` | Extrae raíz, mueve último elemento y aplica `trickleDown`. | `O(log n)` |
| `heapify()` | Construye el heap desde un arreglo completo. | `O(n)` |
| `isHeap()` | Verifica la propiedad local en todos los nodos. | `O(n)` |

Construir un heap insertando `n` elementos uno por uno cuesta `O(n log n)` en el peor caso. Construirlo con `heapify()` cuesta `O(n)` porque se aplica `trickleDown` desde los últimos nodos internos hacia la raíz. 
Aunque los nodos cerca de la raíz pueden bajar mucho, son pocos; los nodos cerca de las hojas bajan poco y son muchos. La suma total es lineal.

Si se extrae repetidamente de un min-heap hasta vaciarlo, la secuencia resultante sale ordenada de menor a mayor. 
Esto no significa que el arreglo interno esté totalmente ordenado, sino que cada extracción revela el mínimo actual y reestablece la propiedad de heap.

#### 17. BST frente a heap

BST y heap pueden visualizarse como árboles binarios, pero resuelven problemas distintos.

| Aspecto | `BinarySearchTree` | `BinaryHeap` |
|---|---|---|
| Propiedad central | Orden global relativo: izquierda menor, derecha mayor. | Prioridad local: padre menor o igual que hijos. |
| Representación | Nodos enlazados con `parent`, `left`, `right`. | Arreglo implícito con índices. |
| Consulta principal | Buscar claves y cotas. | Consultar mínimo. |
| Recorrido útil | Inorden produce claves ordenadas. | Extracciones repetidas producen orden. |
| Inserción | Sigue un camino de búsqueda. | Inserta al final y sube. |
| Eliminación principal | Elimina clave específica. | Extrae la raíz mínima. |
| Riesgo principal | Degeneración si no se balancea. | No permite búsqueda ordenada eficiente. |

Un BST es adecuado cuando se necesitan operaciones como `findEQ`, `lowerBound`, `upperBound`, sucesor, predecesor o recorrido ordenado. 
Un heap es adecuado cuando se necesita consultar y extraer repetidamente el elemento de mayor prioridad, como en planificación, colas de eventos, Dijkstra, Prim o simulaciones.

#### 18. Organización del código de la Semana 5

La carpeta `Semana5` está organizada como un módulo header-only dentro de `Libreria_cc232`. Su estructura permite estudiar cada concepto por separado y
luego conectarlo con demostraciones y pruebas.

| Archivo o carpeta | Papel |
|---|---|
| `include/BinNode.h` | Nodo enlazado con datos, padres, hijos, altura, sucesor, predecesor y recorridos. |
| `include/BinTree.h` | Árbol binario base con raíz, tamaño, inserción, adjunción, separación, eliminación y recorridos. |
| `include/BinaryTree.h` | Capa de navegación con profundidad, altura, tamaño de subárbol, iteración inorden y ASCII. |
| `include/BinarySearchTree.h` | BST con búsqueda, inserción, eliminación, cotas, rotaciones y validación. |
| `include/BinaryHeap.h` | Min-heap implícito con `add`, `remove`, `bubbleUp`, `trickleDown` y `heapify`. |
| `include/Capitulo5.h` | Header agregador de la semana. |
| `demos/` | Programas para observar comportamiento de árbol, BST, heap y panorama general. |
| `pruebas_publicas/` | Pruebas visibles del comportamiento esperado. |
| `pruebas_internas/` | Pruebas adicionales de invariantes y casos borde. |
| `lecturas/` | Notas de Deng y Morin. |
| `Actividad5-CC232.md` | Guía de trabajo, defensa y trazado. |
| `Ejercicios5-CC232.md` | Problemas de demostración, implementación y análisis. |

La separación es pedagógicamente importante. `BinNode` y `BinTree` muestran representación enlazada. `BinaryTree` muestra navegación. `BinarySearchTree` muestra orden. `BinaryHeap` muestra prioridad e implementación implícita. 
Esta separación evita mezclar propiedades distintas bajo la palabra genérica "árbol".

#### 19. Evidencia observable en demos y pruebas

Las demos permiten observar el comportamiento de la implementación. Las pruebas permiten validar invariantes. Ninguna de las dos sustituye una demostración
conceptual, pero juntas dan evidencia fuerte para defensa oral o escrita.

| Evidencia | Qué permite defender |
|---|---|
| Inorden del BST ordenado | La propiedad BST se mantiene. |
| Rechazo de duplicados | La política de claves únicas se respeta. |
| `findEQ(8)` | La búsqueda exacta funciona. |
| `lowerBound(9) = 10` | La consulta de cota inferior funciona. |
| `upperBound(8) = 10` | La consulta de cota superior estricta funciona. |
| Extracciones de heap ordenadas | La raíz siempre contiene el mínimo actual. |
| `isHeap()` | La propiedad de heap se cumple localmente. |
| `checkParentLinks()` | Los enlaces entre padres e hijos son consistentes. |
| `succ()` y `pred()` | La navegación inorden local es correcta. |
| Rotaciones con inorden conservado | Las rotaciones preservan la propiedad BST. |
| `asciiArt()` | La forma del árbol puede inspeccionarse visualmente. |

Pasar las pruebas públicas demuestra que los casos principales funcionan. No demuestra por sí solo que el código sea correcto para todos los casos posibles. 
Para una defensa completa se deben mencionar invariantes, complejidad, casos borde y razonamiento estructural.

#### 20. Invariantes centrales de la semana

La Semana 5 debe defenderse desde invariantes. Un invariante es una propiedad que debe mantenerse antes y después de cada operación relevante.

| Estructura | Invariante |
|---|---|
| `BinNode` | Si un nodo apunta a un hijo, el hijo apunta de vuelta al padre. |
| `BinTree` | `root_` identifica la raíz y `size_` coincide con la cantidad de nodos. |
| `BinaryTree` | Las operaciones de navegación respetan la forma enlazada del árbol. |
| Recorridos | Cada nodo se visita una vez y solo una vez. |
| BST | Todo subárbol izquierdo contiene claves menores y todo subárbol derecho contiene claves mayores. |
| Rotaciones | El orden inorden de las claves se conserva. |
| Heap | Ningún hijo tiene prioridad menor que su padre en un min-heap. |
| `heapify` | Después del proceso, cada posición satisface la propiedad de heap. |

Los errores más peligrosos en esta semana no son solo errores de salida. Son errores de estructura: padres inconsistentes, tamaños incorrectos, alturas 
obsoletas, eliminación que rompe enlaces, rotación que pierde un subárbol o heap que conserva forma pero viola prioridad.

#### 21. Complejidades principales

| Operación | Costo |
|---|---|
| `BinNode::size()` | `O(k)`, donde `k` es el tamaño del subárbol. |
| `BinaryTree::depth(u)` | `O(depth(u))`. |
| `BinaryTree::height(u)` | `O(k)`, donde `k` es el tamaño del subárbol. |
| Recorridos DFS | `O(n)` tiempo. |
| Recorrido por niveles | `O(n)` tiempo. |
| `BST::findEQ`, `lowerBound`, `upperBound` | `O(h)`. |
| `BST::add` | `O(h)`. |
| `BST::remove` | `O(h)`. |
| Rotación simple | `O(1)` más actualización de alturas. |
| `BinaryHeap::top` | `O(1)`. |
| `BinaryHeap::add` | `O(log n)`. |
| `BinaryHeap::remove` | `O(log n)`. |
| `BinaryHeap::heapify` | `O(n)`. |
| `BinaryHeap::isHeap` | `O(n)`. |

La variable `h` representa la altura del árbol. En un árbol balanceado puede ser logarítmica. En un árbol degenerado puede ser lineal. 
Esta dependencia de la altura es el tema que conecta la Semana 5 con las semanas posteriores sobre árboles balanceados.


#### 22. Conclusión general

La Semana 5 cambia el nivel de abstracción del curso. Ya no basta con entender cómo insertar al final de un vector, cómo enlazar nodos en una lista o 
cómo respetar `LIFO` y `FIFO`. Ahora se debe razonar sobre jerarquía, subárboles, caminos, altura, recorridos, invariantes locales y propiedades globales.

`BinNode` y `BinTree` enseñan cómo representar una estructura jerárquica con punteros. `BinaryTree` enseña cómo navegar, medir y recorrer esa estructura. 
`BinarySearchTree` enseña cómo una propiedad de orden convierte un árbol en una estructura de búsqueda. `BinaryHeap` enseña cómo una propiedad de prioridad permite implementar eficientemente una cola de prioridad usando un arreglo implícito.

La diferencia más importante es esta: el BST organiza los datos para responder preguntas de orden; el heap organiza los datos para responder preguntas de prioridad. Ambos son árboles binarios en sentido conceptual, pero sus invariantes, operaciones y usos son distintos.
