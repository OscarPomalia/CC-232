### Semana 5 - Árboles binarios, heaps y árboles binarios de búsqueda

Esta carpeta continúa la estructura de `Libreria_cc232` con una implementación autocontenida de los contenidos centrales  del curso: árboles binarios enlazados, recorridos, colas de prioridad basadas en heap y árboles binarios de búsqueda.

El objetivo principal es distinguir con claridad tres niveles: la **infraestructura base** de árbol (`BinNode` y `BinTree`), la **navegación y recorridos** de un `BinaryTree`, y las **estructuras especializadas** de la semana (`BinaryHeap` y `BinarySearchTree`). Esto coincide con el sílabo: colas de prioridad, heaps, heapify y árboles binarios de búsqueda, usando como apoyo la base de árboles introducida en la semana anterior. 

#### Contenido principal

La carpeta incluye las siguientes estructuras y componentes:

* `BinNode.h`: nodo enlazado con `parent`, `left`, `right`, `height`, inserción de hijos, `succ()` y `pred()`
* `BinTree.h`: árbol binario base con inserción de raíz/hijos, actualización de altura, `attach`, `secede`, `removeSubtree` y recorridos
* `BinaryTree.h`: capa de apoyo estilo Morin con `depth`, `height`, `subtreeSize`, `firstNode`, `lastNode`, iteración inorder y representación ASCII
* `BinarySearchTree.h`: BST con `findLast`, `find`, `findEQ`, `lowerBound`, `upperBound`, `addChild`, `add`, `splice`, `remove`, `rotateLeft`, `rotateRight` y construcción balanceada desde arreglo ordenado
* `BinaryHeap.h`: heap binario mínimo en arreglo implícito con `left`, `right`, `parent`, `add`, `remove`, `bubbleUp`, `trickleDown` y `heapify`
* `Capitulo5.h`: header agregador de la semana

#### Recorridos incluidos

Esta versión deja listos los recorridos más útiles para práctica, pruebas y defensa oral:

* preorden recursivo
* preorden iterativo
* inorden recursivo
* inorden iterativo `#1`, `#2` y `#3`
* postorden recursivo
* postorden iterativo
* recorrido por niveles

#### Organización práctica

Además de los headers, esta carpeta incluye:

* `demos/`: demostraciones de árbol binario base, BST, heap y panorama general del capítulo
* `pruebas_publicas/`: validaciones públicas del comportamiento esperado
* `pruebas_internas/`: casos adicionales de cobertura
* `lecturas/Notas.md`: guía corta para orientar el estudio de Deng y Morin
* `Actividad5-CC232.md` y `Ejercicios5-CC232.md`: material complementario de trabajo

#### Nota de diseño

Para que `Semana5` pueda integrarse sin romper el flujo de las semanas anteriores, esta versión está implementada en estilo header-only, con `namespace ods`, y sin depender internamente de una implementación externa de árboles.

Esto permite que la semana se pueda:

* usar como módulo independiente,
* compilar desde su propia carpeta,
* o integrar directamente dentro de `Libreria_cc232` junto con las demás semanas.

Además, se dejó una separación deliberada entre:

* **árbol binario base** (`BinNode`, `BinTree`),
* **árbol binario navegable** (`BinaryTree`),
* **BST** (`BinarySearchTree`),
* **heap implícito** (`BinaryHeap`).

Esa separación ayuda a defender oralmente qué parte del comportamiento depende de la representación enlazada y qué parte depende de la propiedad de orden o de prioridad.

#### ¿Desde dónde se compila?

Para mantener la misma forma de trabajo de la librería completa, la recomendación es compilar desde la raíz del proyecto:

    cd Libreria_cc232

Ese será el supuesto de todos los comandos de este README.

> En otras palabras: no entres a `Semana5/` para compilar si ya integraste la semana al repositorio. Entra a la raíz `Libreria_cc232/`, configura el proyecto una sola vez y luego compila o ejecuta los targets de la semana 5.

#### Aclaración sobre `build-debug`

El nombre de la carpeta `build-debug` es solo una convención. No activa Debug por sí mismo.

Para compilar realmente en modo Debug:

* en Linux hay que pasar `-DCMAKE_BUILD_TYPE=Debug`
* en Windows con Visual Studio hay que usar `--config Debug`

#### Relación con las lecturas

Esta semana está alineada con el bloque del sílabo sobre colas de prioridad, heaps, heapify y árboles binarios de búsqueda. La base de árboles también recoge parte del trabajo conceptual de la semana 4. El repositorio y las lecturas se conectan así:

* **Deng**: base enlazada con `BinNode` y `BinTree`
* **Deng**: punto unificado de inorden
* **Deng**: mantenimiento de alturas
* **Deng**: recorridos recursivos
* **Deng**: sucesor inorder
* **Deng**: recorrido por niveles
* **Morin `BinaryTree`**: profundidad, altura, navegación y recorrido inorder
* **Morin `BinaryHeap`**: representación implícita en arreglo y operaciones de prioridad
* **Morin `BinarySearchTree`**: búsqueda, inserción, borrado, `splice` y rotaciones

Como extra útil para semanas posteriores, esta versión también deja rotaciones y utilidades de validación (`isBST`, `isHeap`, `checkParentLinks`) listas para reutilizar en AVL o estructuras balanceadas.

### Linux

#### 1. Configurar todo el proyecto en modo Debug

    cd Libreria_cc232
    cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug

Este comando prepara el árbol de compilación completo del proyecto.

#### 2. Compilar solo la semana 5

Si quieres compilar únicamente los targets principales de esta semana:

    cmake --build build-debug --target \
      sem5_demo_binary_tree \
      sem5_demo_bst \
      sem5_demo_heap \
      sem5_demo_capitulo5_panorama \
      sem5_test_public \
      sem5_test_internal

Si prefieres compilar todo el repositorio, usa:

    cmake --build build-debug

#### 3. Ejecutar todas las pruebas de la semana 5

    ctest --test-dir build-debug -R semana5 --output-on-failure

#### 4. Ejecutar los demos paso a paso

##### `BinaryTree`

    ./build-debug/Semana5/sem5_demo_binary_tree

##### `BinarySearchTree`

    ./build-debug/Semana5/sem5_demo_bst

##### `BinaryHeap`

    ./build-debug/Semana5/sem5_demo_heap

##### Panorama general del capítulo

    ./build-debug/Semana5/sem5_demo_capitulo5_panorama

### Windows (Visual Studio)

#### 1. Configurar todo el proyecto

    cd Libreria_cc232
    cmake -S . -B build-debug

#### 2. Compilar solo la semana 5 en modo Debug

    cmake --build build-debug --config Debug --target `
      sem5_demo_binary_tree `
      sem5_demo_bst `
      sem5_demo_heap `
      sem5_demo_capitulo5_panorama `
      sem5_test_public `
      sem5_test_internal

Si prefieres compilar todo el repositorio, usa:

    cmake --build build-debug --config Debug

#### 3. Ejecutar todas las pruebas de la semana 5

    ctest --test-dir build-debug -C Debug -R semana5 --output-on-failure

#### 4. Ejecutar los demos paso a paso

##### `BinaryTree`

    .\build-debug\Semana5\Debug\sem5_demo_binary_tree.exe

##### `BinarySearchTree`

    .\build-debug\Semana5\Debug\sem5_demo_bst.exe

##### `BinaryHeap`

    .\build-debug\Semana5\Debug\sem5_demo_heap.exe

##### Panorama general del capítulo

    .\build-debug\Semana5\Debug\sem5_demo_capitulo5_panorama.exe

### Targets principales

#### Demos

* `sem5_demo_binary_tree`
* `sem5_demo_bst`
* `sem5_demo_heap`
* `sem5_demo_capitulo5_panorama`

#### Pruebas

* `sem5_test_public`
* `sem5_test_internal`

### Compilación aislada de `Semana5`

Si todavía no integraste `Semana5` al `CMakeLists.txt` raíz, también puedes compilarla por separado desde su propia carpeta:

    cd Libreria_cc232/Semana5
    cmake -S . -B build
    cmake --build build
    ctest --test-dir build --output-on-failure

En ese caso, los ejecutables quedarán directamente dentro de `Semana5/build/`.
