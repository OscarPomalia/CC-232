### Semana 6 - Colas de prioridad, heaps, Huffman y Treap

Esta carpeta continúa el trabajo de `Semana5` y extiende la librería con estructuras basadas en prioridad. El objetivo principal es separar tres ideas que suelen confundirse:

* una **cola de prioridad** entrega rápidamente el elemento de mayor prioridad,
* un **heap** es una representación eficiente para implementar esa cola de prioridad,
* un **árbol de búsqueda** organiza claves para búsqueda ordenada, y un **Treap** combina orden BST con prioridad tipo heap.

La semana está organizada como una continuación natural de la semana anterior: reutiliza la infraestructura de árboles/BST de `Semana5` y añade las estructuras propias de priority queues, heaps, Huffman y Treap.

#### Contenido principal

La carpeta incluye los siguientes componentes:

* `PQ.h`: interfaz abstracta para una cola de prioridad genérica.
* `PQ_ComplHeap.h`: implementación de una cola de prioridad máxima usando heap binario completo sobre arreglo implícito.
* `PQ_ComplHeap_getMax.h`: consulta del máximo sin retirarlo.
* `PQ_ComplHeap_insert.h`: inserción con restauración de la propiedad heap.
* `PQ_ComplHeap_delMax.h`: eliminación del máximo.
* `PQ_ComplHeap_percolateUp.h`: subida de un nodo para reparar el heap después de insertar.
* `PQ_ComplHeap_percolateDown.h`: bajada de un nodo para reparar el heap después de eliminar.
* `PQ_ComplHeap_heapifyFloyd.h`: construcción de heap usando el método de Floyd.
* `PQ_ComplHeap_macro.h`: utilidades `parent`, `left` y `right` como funciones `constexpr`.
* `PQ_LeftHeap.h`: heap izquierdista con operación central `merge`.
* `PQ_LeftHeap_merge.h`: mezcla de dos leftist heaps.
* `PQ_LeftHeap_insert.h`: inserción como caso particular de `merge`.
* `PQ_LeftHeap_delMax.h`: eliminación del máximo mediante mezcla de subárboles.
* `vector_heapSort.h`: ordenamiento por heapsort sobre `std::vector`.
* `Huffman_PQ.h`: construcción de Huffman usando una cola de prioridad uniforme.
* `Huffman_PQ_generateTree.h`: integración auxiliar para generación del árbol de Huffman.
* `MeldableHeap.h`: heap mezclable de apoyo conceptual.
* `Treap.h`: árbol aleatorizado que mantiene propiedad BST por clave y propiedad heap por prioridad.
* `Capitulo6.h`: header agregador de la semana.
* `Capitulo10.h`: alias de compatibilidad para el material de priority queues del capítulo 10.

#### Qué reutiliza de `Semana5`

La carpeta `Semana6` está pensada para ubicarse como carpeta hermana de `Semana5` dentro de `Libreria_cc232`.

Desde `../Semana5/include` se reutiliza:

* `BinaryTree`
* `BinarySearchTree`
* `BinaryHeap`
* `Capitulo5.h`

Esta reutilización permite comparar directamente:

* `BinaryHeap`, como heap binario usado para prioridades;
* `BinarySearchTree`, como estructura de búsqueda ordenada;
* `Treap`, como estructura que mezcla claves ordenadas y prioridades.

#### Organización práctica

Además de los headers, la carpeta contiene:

* `demos/`: programas pequeños para ejecutar y observar cada estructura.
* `pruebas_publicas/`: pruebas públicas esperadas para validar comportamiento básico.
* `pruebas_internas/`: pruebas adicionales de cobertura.
* `lecturas/Notas.md`: resumen conceptual de priority queues, heaps, Huffman y Treap.
* `Actividad6-CC232.md`: guía de actividad para ejecutar demos y sustentar operaciones.
* `Ejercicios6-CC232.md`: espacio para ejercicios de la semana.
* `VALIDACION.md`: registro de compilación y pruebas.

#### Demos incluidos

* `demo_pq_complheap_basico.cpp`: uso básico de `PQ_ComplHeap`.
* `demo_heapify_floyd.cpp`: construcción de heap con `heapify` de Floyd.
* `demo_heapsort.cpp`: ordenamiento con heapsort.
* `demo_left_heap_merge.cpp`: mezcla de heaps izquierdistas.
* `demo_huffman.cpp`: construcción de Huffman con cola de prioridad.
* `demo_compare_with_semana5.cpp`: comparación con estructuras de `Semana5`.
* `demo_bst_rotations.cpp`: rotaciones sobre BST.
* `demo_treap_basico.cpp`: inserción, búsqueda y eliminación en Treap.
* `demo_capitulo6_panorama.cpp`: recorrido panorámico de la semana.

#### Nota de diseño

La implementación mantiene el estilo header-only del proyecto para facilitar la integración dentro de `Libreria_cc232`. Las estructuras de la semana se pueden estudiar como módulos separados, pero también se conectan entre sí mediante una idea común: la prioridad.

La separación intencional es la siguiente:

* `PQ<T>` define la interfaz de cola de prioridad.
* `PQ_ComplHeap<T>` implementa la cola de prioridad con heap binario completo.
* `PQ_LeftHeap<T>` implementa la cola de prioridad con heap izquierdista.
* `Huffman_PQ` usa la cola de prioridad sin depender de una única implementación concreta.
* `Treap` reutiliza la idea de prioridad, pero dentro de un árbol de búsqueda.

Esto ayuda a defender oralmente qué parte del comportamiento corresponde a la interfaz, qué parte corresponde a la representación del heap y qué parte corresponde a la propiedad de orden de un árbol de búsqueda.

#### Relación con las lecturas

Esta semana está alineada con el bloque de colas de prioridad y heaps. El proyecto conecta las lecturas así:

* Deng: ADT de cola de prioridad.
* Deng: heap binario completo.
* Deng: `getMax`, `insert`, `delMax`, `percolateUp`, `percolateDown` y `heapify`.
* Deng: heap izquierdista y operación `merge`.
* Huffman: construcción de árbol óptimo usando repetidamente los elementos de menor frecuencia o mayor prioridad, según la convención implementada.
* Morin: comparación con `BinaryHeap`, `BinarySearchTree` y estructuras mezclables.
* Puente a semanas posteriores: rotaciones, árboles balanceados y Treap.

#### ¿Desde dónde se compila?

La forma recomendada es compilar desde la raíz del proyecto:

```bash
cd Libreria_cc232
```

Ese será el supuesto de los comandos principales. En esa ubicación deben existir, como mínimo, las carpetas:

```text
Libreria_cc232/
├── Semana5/
└── Semana6/
```

`Semana6` usa headers de `Semana5`, por eso no conviene compilarla en una carpeta completamente aislada si no existe `../Semana5/include`.

#### Aclaración sobre `build-debug`

El nombre `build-debug` es solo una convención de carpeta. Para activar realmente modo Debug en Linux se debe pasar:

```bash
-DCMAKE_BUILD_TYPE=Debug
```

En Windows con Visual Studio se debe usar:

```bash
--config Debug
```


### Linux

#### 1. Configurar todo el proyecto en modo Debug

```bash
cd Libreria_cc232
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
```

#### 2. Compilar solo la semana 6

```bash
cmake --build build-debug --target \
  sem6_demo_pq_complheap_basico \
  sem6_demo_heapify_floyd \
  sem6_demo_heapsort \
  sem6_demo_left_heap_merge \
  sem6_demo_huffman \
  sem6_demo_compare_with_semana5 \
  sem6_demo_bst_rotations \
  sem6_demo_treap_basico \
  sem6_demo_capitulo6_panorama \
  sem6_test_public \
  sem6_test_internal
```

Si prefieres compilar todo el repositorio:

```bash
cmake --build build-debug
```

#### 3. Ejecutar todas las pruebas de la semana 6

```bash
ctest --test-dir build-debug -R semana6 --output-on-failure
```

#### 4. Ejecutar demos paso a paso

##### Cola de prioridad con heap completo

```bash
./build-debug/Semana6/sem6_demo_pq_complheap_basico
```

##### Heapify de Floyd

```bash
./build-debug/Semana6/sem6_demo_heapify_floyd
```

##### Heapsort

```bash
./build-debug/Semana6/sem6_demo_heapsort
```

##### Heap izquierdista

```bash
./build-debug/Semana6/sem6_demo_left_heap_merge
```

##### Huffman

```bash
./build-debug/Semana6/sem6_demo_huffman
```

##### Comparación con Semana5

```bash
./build-debug/Semana6/sem6_demo_compare_with_semana5
```

##### Rotaciones en BST

```bash
./build-debug/Semana6/sem6_demo_bst_rotations
```

##### Treap

```bash
./build-debug/Semana6/sem6_demo_treap_basico
```

##### Panorama general

```bash
./build-debug/Semana6/sem6_demo_capitulo6_panorama
```

### Windows con Visual Studio

#### 1. Configurar todo el proyecto

```powershell
cd Libreria_cc232
cmake -S . -B build-debug
```

#### 2. Compilar solo la semana 6 en modo Debug

```powershell
cmake --build build-debug --config Debug --target `
  sem6_demo_pq_complheap_basico `
  sem6_demo_heapify_floyd `
  sem6_demo_heapsort `
  sem6_demo_left_heap_merge `
  sem6_demo_huffman `
  sem6_demo_compare_with_semana5 `
  sem6_demo_bst_rotations `
  sem6_demo_treap_basico `
  sem6_demo_capitulo6_panorama `
  sem6_test_public `
  sem6_test_internal
```

Si prefieres compilar todo el repositorio:

```powershell
cmake --build build-debug --config Debug
```

#### 3. Ejecutar todas las pruebas de la semana 6

```powershell
ctest --test-dir build-debug -C Debug -R semana6 --output-on-failure
```

#### 4. Ejecutar demos paso a paso

##### Cola de prioridad con heap completo

```powershell
.\build-debug\Semana6\Debug\sem6_demo_pq_complheap_basico.exe
```

##### Heapify de Floyd

```powershell
.\build-debug\Semana6\Debug\sem6_demo_heapify_floyd.exe
```

##### Heapsort

```powershell
.\build-debug\Semana6\Debug\sem6_demo_heapsort.exe
```

##### Heap izquierdista

```powershell
.\build-debug\Semana6\Debug\sem6_demo_left_heap_merge.exe
```

##### Huffman

```powershell
.\build-debug\Semana6\Debug\sem6_demo_huffman.exe
```

##### Comparación con Semana5

```powershell
.\build-debug\Semana6\Debug\sem6_demo_compare_with_semana5.exe
```

##### Rotaciones en BST

```powershell
.\build-debug\Semana6\Debug\sem6_demo_bst_rotations.exe
```

##### Treap

```powershell
.\build-debug\Semana6\Debug\sem6_demo_treap_basico.exe
```

##### Panorama general

```powershell
.\build-debug\Semana6\Debug\sem6_demo_capitulo6_panorama.exe
```

### Targets principales

#### Demos

* `sem6_demo_pq_complheap_basico`
* `sem6_demo_heapify_floyd`
* `sem6_demo_heapsort`
* `sem6_demo_left_heap_merge`
* `sem6_demo_huffman`
* `sem6_demo_compare_with_semana5`
* `sem6_demo_bst_rotations`
* `sem6_demo_treap_basico`
* `sem6_demo_capitulo6_panorama`

#### Pruebas

* `sem6_test_public`
* `sem6_test_internal`


### Compilación aislada de `Semana6`

También se puede compilar desde la carpeta `Semana6`, siempre que `Semana5` exista como carpeta hermana:

```bash
cd Libreria_cc232/Semana6
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug --output-on-failure
```

En ese caso, los ejecutables quedarán dentro de:

```text
Semana6/build-debug/
```


### Qué debes poder explicar 

Al terminar esta semana, el estudiante debería poder sustentar:

1. Qué problema resuelve una cola de prioridad.
2. Por qué un heap binario completo permite `getMax`, `insert` y `delMax` eficientemente.
3. Cómo funcionan `percolateUp` y `percolateDown`.
4. Por qué `heapify` de Floyd construye un heap desde un vector.
5. Cómo heapsort reutiliza la propiedad heap.
6. Por qué un heap izquierdista usa `merge` como operación central.
7. Por qué Huffman necesita una cola de prioridad.
8. Qué diferencia hay entre heap, BST y Treap.
9. Cómo las rotaciones preservan el orden inorder de un BST.
10. Cómo `Treap` combina búsqueda por clave con prioridad aleatoria.