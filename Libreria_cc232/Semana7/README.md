### Semana 7 - Árboles balanceados: AVL y Red-Black Tree

Esta carpeta continúa el trabajo de `Semana5` y `Semana6` dentro de `Libreria_cc232`. El objetivo principal es estudiar cómo un árbol binario de búsqueda puede mantener altura logarítmica mediante rotaciones, reglas de balance y correcciones locales después de insertar o eliminar.

La semana se organiza como una continuación natural de las semanas anteriores:

* `Semana5` introduce la infraestructura de árboles binarios, recorridos, heaps y árboles binarios de búsqueda.
* `Semana6` extiende esa base con colas de prioridad, heaps, Huffman, rotaciones y Treap como puente entre búsqueda ordenada y prioridad.
* `Semana7` estudia árboles de búsqueda balanceados: **AVL** y **Red-Black Tree**.

La idea central es comparar un BST común con estructuras que evitan la degeneración lineal usando invariantes adicionales:

* AVL mantiene balance por altura.
* Red-Black Tree mantiene balance por colores.
* Ambas estructuras usan rotaciones para conservar el orden inorder del BST.

#### Contenido principal

La carpeta incluye los siguientes componentes:

* `Entry.h`: par clave-valor básico usado por la línea de implementación estilo Deng.
* `BinNode.h`: nodo binario con enlaces a padre, hijo izquierdo, hijo derecho y altura.
* `BinTree.h`: árbol binario base para la línea Deng.
* `BST.h`: árbol binario de búsqueda de la línea Deng, con búsqueda, inserción, eliminación y rotaciones.
* `AVL.h`: árbol AVL que hereda de `BST` y agrega rebalanceo por altura.
* `BinaryTree.h`: árbol binario genérico estilo Morin con nodo centinela.
* `BinarySearchTree.h`: BST genérico estilo Morin con búsqueda, inserción, eliminación, `splice` y rotaciones.
* `RedBlackTree.h`: Red-Black Tree basado en `BinarySearchTree`, con reglas de color y correcciones después de insertar o borrar.
* `AVLTreeCompact.h`: versión compacta de AVL para demostraciones rápidas de rotaciones.
* `RedBlackTreeLLRB.h`: variante compacta Left-Leaning Red-Black para contraste pedagógico.
* `Capitulo7.h`: header agregador de la semana.

#### Qué continúa de `Semana5` y `Semana6`

`Semana7` debe leerse como continuación conceptual y práctica de las semanas anteriores.

Desde `Semana5` se retoman estas ideas:

* árbol binario enlazado,
* árbol binario de búsqueda,
* recorrido inorder,
* búsqueda, inserción y eliminación,
* rotaciones izquierda y derecha.

Desde `Semana6` se retoman estas ideas:

* prioridad como criterio adicional sobre una estructura,
* Treap como puente entre BST y heap,
* rotaciones como operación local que preserva el orden inorder,
* comparación entre estructuras que mantienen eficiencia por propiedades adicionales.

La relación conceptual puede leerse así:

```text
Semana5
  └── árboles binarios, BinaryTree, BinarySearchTree, BinaryHeap

Semana6
  └── priority queues, heaps, Huffman, rotaciones y Treap

Semana7
  └── AVL, Red-Black Tree, balanceo, rebalanceo y comparación de alturas
```

#### Aclaración importante sobre herencia y reutilización

En C++ conviene distinguir dos ideas:

* una carpeta no hereda de otra carpeta,
* una clase sí puede heredar de otra clase.

Por eso, no se debe decir que `Semana7` hereda de `Semana5` o de `Semana6`. Lo correcto es decir que `Semana7` continúa esas semanas y reutiliza sus ideas de diseño.

La herencia real aparece dentro del código de la semana:

```cpp
AVL<T, Compare> : public BST<T, Compare>
```

En esa línea, `AVL.h` incluye:

```cpp
#include "BST.h"
```

y por tanto el AVL de esta entrega hereda del `BST.h` local de `Semana7`, no directamente del `BinarySearchTree.h` de `Semana5`.

También aparece una segunda línea de herencia para Red-Black Tree:

```cpp
RedBlackTree<Node, T> : public BinarySearchTree<Node, T>
```

En este caso, `RedBlackTree.h` usa la infraestructura estilo Morin formada por `BinaryTree.h` y `BinarySearchTree.h`.

#### Por qué siguen apareciendo `BinNode.h`, `BinTree.h`, `BinaryTree.h` y `BinarySearchTree.h`

En esta entrega esos archivos siguen apareciendo porque el código contiene dos líneas pedagógicas distintas:

```text
Línea Deng
  Entry.h
  BinNode.h
  BinTree.h
  BST.h
  AVL.h

Línea Morin
  BinaryTree.h
  BinarySearchTree.h
  RedBlackTree.h
```

La línea Deng se usa para explicar AVL siguiendo la cadena:

```text
BinNode -> BinTree -> BST -> AVL
```

La línea Morin se usa para explicar Red-Black Tree siguiendo la cadena:

```text
BinaryTree -> BinarySearchTree -> RedBlackTree
```

Aunque algunos nombres coinciden con archivos trabajados en `Semana5`, aquí no son simples copias decorativas: forman parte de las interfaces que necesitan `AVL.h` y `RedBlackTree.h` para compilar.

Por ejemplo, el AVL entregado usa elementos propios de la línea Deng:

* `_hot` para recordar el último nodo visitado en la búsqueda;
* `search()` para devolver una referencia al lugar donde está o debería estar la clave;
* `rotateAt()` para reestructurar el árbol;
* `updateHeight()` para mantener alturas;
* macros auxiliares como `CC232_STATURE`, `CC232_BAL_FAC` y `CC232_TALLER_CHILD`.

Eliminar `BinNode.h`, `BinTree.h` o `BST.h` sin refactorizar `AVL.h` rompería esa implementación.

De forma similar, eliminar `BinaryTree.h` o `BinarySearchTree.h` sin adaptar `RedBlackTree.h` rompería la implementación de Red-Black Tree.

La regla de diseño para esta semana es:

```text
No duplicar por descuido.
Sí conservar una base local cuando la implementación la necesita y la diferencia está documentada.
```

#### Organización práctica

Además de los headers, la carpeta contiene:

* `demos/`: demostraciones de AVL, Red-Black Tree, variantes compactas y comparaciones.
* `pruebas_publicas/`: validaciones públicas del comportamiento esperado.
* `pruebas_internas/`: casos adicionales de cobertura.
* `lecturas/Notas.md`: guía corta para orientar el estudio de AVL, Red-Black Tree y rotaciones.
* `Actividad7-CC232.md` y `Ejercicios7-CC232.md`: material complementario de trabajo.

#### Demos incluidos

Los demos principales son:

* `demo_avl_deng_core.cpp`: inserción, eliminación, recorrido inorder y validación AVL.
* `demo_avl_compact_rotations.cpp`: casos de rotación AVL en una implementación compacta.
* `demo_bst_deng_vs_avl.cpp`: comparación entre un BST no balanceado y un AVL.
* `demo_redblack_morin.cpp`: inserción, eliminación y validación de Red-Black Tree.
* `demo_redblack_llrb.cpp`: variante Left-Leaning Red-Black.
* `demo_compare_avl_vs_redblack.cpp`: comparación de altura y validez entre AVL y Red-Black Tree.
* `demo_compare_with_semana5.cpp`: comparación conceptual con el BST base trabajado previamente.
* `demo_capitulo7_panorama.cpp`: recorrido panorámico de las estructuras de la semana.

#### Nota de diseño

La semana mantiene el estilo header-only usado en las semanas anteriores para facilitar la integración dentro de `Libreria_cc232`.

Esta entrega conserva dos líneas pedagógicas separadas:

* **Deng**: `Entry`, `BinNode`, `BinTree`, `BST` y `AVL`.
* **Morin**: `BinaryTree`, `BinarySearchTree` y `RedBlackTree`.

Esa separación es intencional. La línea Deng permite mostrar AVL con alturas, `rotateAt()` y reestructuración local. La línea Morin permite mostrar Red-Black Tree con centinela `nil`, `splice()`, rotaciones y correcciones de color.

Si se quisiera que `Semana7` use físicamente los headers de `Semana5` sin mantener versiones locales, habría que hacer una refactorización adicional:

* adaptar `AVL.h` para heredar de la clase base de `Semana5`;
* adaptar nombres de nodos, punteros, alturas y operaciones internas;
* revisar las firmas de búsqueda, inserción y eliminación;
* ajustar `RedBlackTree.h` para usar exactamente el `BinarySearchTree` disponible en `Semana5`.

Esta entrega no hace esa refactorización. En su lugar, deja documentado qué hereda cada clase y por qué existen headers locales con nombres parecidos.


#### ¿Desde dónde se compila?

Para mantener la misma forma de trabajo de la librería completa, la recomendación es compilar desde la raíz del proyecto:

```bash
cd Libreria_cc232
```

Ese será el supuesto de todos los comandos de este README.

> En otras palabras: no entres a `Semana7/` para compilar si ya integraste la semana al repositorio. Entra a la raíz `Libreria_cc232/`, configura el proyecto una sola vez y luego compila o ejecuta los targets de la semana 7.

#### Aclaración sobre `build-debug`

El nombre de la carpeta `build-debug` es solo una convención. No activa Debug por sí mismo.

Para compilar realmente en modo Debug:

* en Linux hay que pasar `-DCMAKE_BUILD_TYPE=Debug`;
* en Windows con Visual Studio hay que usar `--config Debug`.

### Linux

#### 1. Configurar todo el proyecto en modo Debug

```bash
cd Libreria_cc232
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
```

Este comando prepara el árbol de compilación completo del proyecto.

#### 2. Compilar solo la semana 7

Si quieres compilar únicamente los targets principales de esta semana:

```bash
cmake --build build-debug --target \
  sem7_demo_avl_deng_core \
  sem7_demo_avl_compact_rotations \
  sem7_demo_bst_deng_vs_avl \
  sem7_demo_redblack_morin \
  sem7_demo_redblack_llrb \
  sem7_demo_compare_avl_vs_redblack \
  sem7_demo_compare_with_semana5 \
  sem7_demo_capitulo7_panorama \
  sem7_test_public \
  sem7_test_internal
```

Si prefieres compilar todo el repositorio, usa:

```bash
cmake --build build-debug
```

#### 3. Ejecutar todas las pruebas de la semana 7

```bash
ctest --test-dir build-debug -R semana7 --output-on-failure
```

#### 4. Ejecutar los demos paso a paso

##### AVL estilo Deng

```bash
./build-debug/Semana7/sem7_demo_avl_deng_core
```

##### Rotaciones AVL compactas

```bash
./build-debug/Semana7/sem7_demo_avl_compact_rotations
```

##### BST vs AVL

```bash
./build-debug/Semana7/sem7_demo_bst_deng_vs_avl
```

##### Red-Black Tree estilo Morin

```bash
./build-debug/Semana7/sem7_demo_redblack_morin
```

##### Red-Black Tree LLRB

```bash
./build-debug/Semana7/sem7_demo_redblack_llrb
```

##### Comparación AVL vs Red-Black Tree

```bash
./build-debug/Semana7/sem7_demo_compare_avl_vs_redblack
```

##### Comparación con Semana5

```bash
./build-debug/Semana7/sem7_demo_compare_with_semana5
```

##### Panorama general del capítulo

```bash
./build-debug/Semana7/sem7_demo_capitulo7_panorama
```

### Windows con Visual Studio

#### 1. Configurar todo el proyecto

```powershell
cd Libreria_cc232
cmake -S . -B build-debug
```

#### 2. Compilar solo la semana 7 en modo Debug

```powershell
cmake --build build-debug --config Debug --target `
  sem7_demo_avl_deng_core `
  sem7_demo_avl_compact_rotations `
  sem7_demo_bst_deng_vs_avl `
  sem7_demo_redblack_morin `
  sem7_demo_redblack_llrb `
  sem7_demo_compare_avl_vs_redblack `
  sem7_demo_compare_with_semana5 `
  sem7_demo_capitulo7_panorama `
  sem7_test_public `
  sem7_test_internal
```

Si prefieres compilar todo el repositorio, usa:

```powershell
cmake --build build-debug --config Debug
```

#### 3. Ejecutar todas las pruebas de la semana 7

```powershell
ctest --test-dir build-debug -C Debug -R semana7 --output-on-failure
```

#### 4. Ejecutar demos paso a paso

##### AVL estilo Deng

```powershell
.\build-debug\Semana7\Debug\sem7_demo_avl_deng_core.exe
```

##### Rotaciones AVL compactas

```powershell
.\build-debug\Semana7\Debug\sem7_demo_avl_compact_rotations.exe
```

##### BST vs AVL

```powershell
.\build-debug\Semana7\Debug\sem7_demo_bst_deng_vs_avl.exe
```

##### Red-Black Tree estilo Morin

```powershell
.\build-debug\Semana7\Debug\sem7_demo_redblack_morin.exe
```

##### Red-Black Tree LLRB

```powershell
.\build-debug\Semana7\Debug\sem7_demo_redblack_llrb.exe
```

##### Comparación AVL vs Red-Black Tree

```powershell
.\build-debug\Semana7\Debug\sem7_demo_compare_avl_vs_redblack.exe
```

##### Comparación con Semana5

```powershell
.\build-debug\Semana7\Debug\sem7_demo_compare_with_semana5.exe
```

##### Panorama general del capítulo

```powershell
.\build-debug\Semana7\Debug\sem7_demo_capitulo7_panorama.exe
```

### Targets principales

#### Demos

* `sem7_demo_avl_deng_core`
* `sem7_demo_avl_compact_rotations`
* `sem7_demo_bst_deng_vs_avl`
* `sem7_demo_redblack_morin`
* `sem7_demo_redblack_llrb`
* `sem7_demo_compare_avl_vs_redblack`
* `sem7_demo_compare_with_semana5`
* `sem7_demo_capitulo7_panorama`

#### Pruebas

* `sem7_test_public`
* `sem7_test_internal`

### Compilación aislada de `Semana7`

También se puede compilar desde la carpeta `Semana7`:

```bash
cd Libreria_cc232/Semana7
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug --output-on-failure
```

En ese caso, los ejecutables quedarán dentro de:

```text
Semana7/build-debug/
```

### Qué debes poder explicar

Al terminar esta semana, deberías poder sustentar:

1. Por qué un BST puede degenerar a altura lineal.
2. Cómo AVL mantiene balance usando alturas.
3. Qué rotaciones aparecen en AVL: LL, RR, LR y RL.
4. Por qué una rotación preserva el recorrido inorder.
5. Qué representa `BST<T, Compare>` dentro de la implementación de AVL.
6. Por qué `AVL.h` hereda de `BST.h` local en esta entrega.
7. Cómo Red-Black Tree logra altura logarítmica usando colores.
8. La diferencia entre balance estricto de AVL y balance más flexible de Red-Black Tree.
9. Por qué Treap, AVL y Red-Black Tree son respuestas distintas al mismo problema: mantener búsqueda ordenada eficiente.
10. La diferencia entre continuar una semana anterior, reutilizar una interfaz y heredar de una clase base.
