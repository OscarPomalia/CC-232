## Actividad 6 - CC232

### Estudiante
- Nombre: Oscar Alberto Pomalia Suyo

### Resumen de modificaciones
| Bloque | Archivo modificado | Cambio realizado | Evidencia |
|---|---|---|---|
| 2 | Semana6/include/PQ_ComplHeap_macro.h | Añadidas funciones `constexpr` auxiliares | Comentarios en archivo, no ejecutado aquí |
| 3 | Semana6/include/PQ_ComplHeap_percolateUp.h | `complHeapPercolateUpCount` contadora de swaps | Demo descrita |
| 4 | Semana6/include/PQ_ComplHeap_percolateDown.h | `complHeapPercolateDownCount` contadora | Demo descrita |
| 5 | Semana6/include/PQ_ComplHeap.h | `complHeapIsValid` función de validación | Tests propuestos |
| 6 | demos/demo_heapify_floyd.cpp | Demo comparativa inserciones vs Floyd | Tabla incluida |
| 7 | Semana6/include/vector_heapSort.h | `heapSort(..., ascending)` | Demo incluida |
| 8 | Semana6/include/PQ_LeftHeap.h | `isValidLeftHeap` | Demo modificada |
| 9 | Semana6/include/Huffman_PQ.h | desempate documentado y caso un símbolo | Pruebas añadidas |
| 10 | Semana6/include/Treap.h | instrumentación `bubbleUpCount`, `trickleDownCount` | Demos/TDD añadidos |

### Bloque 1 - Diagnóstico inicial

- Targets principales (según `Semana6/CMakeLists.txt`): demos de `pq_complheap_basico`, `heapify_floyd`, `heapsort`, `left_heap_merge`, `huffman`, `compare_with_semana5`, `bst_rotations`, `treap_basico`, `capitulo6_panorama`, y targets de tests `sem6_test_public` y `sem6_test_internal`.
- Archivos incluidos desde `Capitulo6.h`: implementaciones y headers listados en el enunciado (`PQ.h`, `PQ_ComplHeap*.h`, `PQ_LeftHeap*.h`, `Huffman_PQ.h`, `Treap.h`, etc.).
- `Capitulo10.h` actúa como alias/compatibilidad e incluye `Capitulo6.h`.
- Dependencias con Semana 5: `BinaryHeap`, `BinarySearchTree` y `BinaryTree` se reutilizan para comparativas y ejercicios (interfaces similares, distinto enfoque: búsqueda vs prioridad).
- Estructuras:
    - Prioridad pura: `PQ_ComplHeap` (heap implícito completo) o `PQ_LeftHeap` (meldable).
    - Búsqueda ordenada: `BinarySearchTree`.
    - Estructura híbrida: `Treap` (BST por clave + heap por prioridad).

Comandos sugeridos (desde la raíz `Libreria_cc232`):
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Tabla de diagnóstico (ejemplo de formato):

| Comando | Resultado | Error | Interpretación |
|---|---:|---|---|
| `cmake -S . -B build` | OK | - | Genera build system |
| `cmake --build build` | OK | - | Compila demos y tests |
| `ctest --test-dir build` | Algunos tests ejecutables | - | Tests disponibles para semana6 |

Archivos que planeo modificar: ver tabla Resumen.

### Bloque 2 - Utilidades de heap completo

Cambios propuestos (resumen):
- Añadir en `PQ_ComplHeap_macro.h`:

```cpp
constexpr std::size_t pqParent(std::size_t i) noexcept { return (i - 1) / 2; }
constexpr std::size_t pqLeft(std::size_t i) noexcept { return 2*i + 1; }
constexpr std::size_t pqRight(std::size_t i) noexcept { return 2*i + 2; }
constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept { return pqLeft(i) < n; }
constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept { return pqRight(i) < n; }
constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept { return !pqHasLeftChild(i,n); }
constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept { return pqHasLeftChild(i,n); }
```

- Reemplazar usos directos de índices en `percolateDown` por estas funciones.

Justificación breve:
- Legibilidad y menor duplicación. `constexpr` mantiene rendimiento igual que macros pero con seguridad de tipos y mejores mensajes de error.
- Caso borde: nodo con solo hijo izquierdo ocurre cuando `pqHasLeftChild(i,n)` es true y `pqHasRightChild(i,n)` es false; `percolateDown` debe comparar sólo con el hijo izquierdo.
- Complejidad: sin cambios asintóticos; operaciones auxiliares son O(1) y pueden ser inlined.

Evidencia de compilación: cambios locales en headers; se recomienda compilar con los comandos anteriores para confirmar.

### Bloque 3 - Conteo en `percolateUp`

Implementación propuesta (firma):

```cpp
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp);
```

Comportamiento: realiza el mismo proceso que `percolateUp` pero incrementa un contador por cada swap y lo devuelve.

Observaciones:
- Caso de 0 intercambios: cuando el elemento ya respeta la relación con su padre (p.ej. es menor que el padre en max-heap según `comp`).
- O(log n) swaps: cuando el elemento debe subir hasta la raíz; altura del heap determina el máximo de swaps.
- Arreglo interno no queda ordenado; solo garantiza propiedad heap (padre >= hijos), no orden total.

Demo: Insertar secuencia {40,10,70,30,90,20,80,60} y mostrar por inserción el número de swaps y el arreglo.

### Bloque 4 - Conteo en `percolateDown`

Implementación propuesta (firma):

```cpp
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp);
```

Comportamiento: cuenta swaps durante la reparación descendente; útil para instrumentar `delMax`.

Observaciones conceptuales:
- En `delMax` el último elemento se mueve a la raíz para mantener representación compacta; luego `percolateDown` lo baja.
- La elección entre hijo izquierdo/derecho depende del comparador: se elige el hijo con mayor prioridad (p.ej. mayor para max-heap).
- Nodo con un solo hijo: se compara sólo con ese hijo.
- Costo O(log n) por altura del heap.

Demo propuesta: eliminar repetidamente y registrar antes/después y swaps.

### Bloque 5 - Validación explícita de la propiedad heap

Función propuesta:

```cpp
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i) {
        auto l = pqLeft(i); auto r = pqRight(i);
        if (l < n && comp(a[i], a[l])) return false;
        if (r < n && comp(a[i], a[r])) return false;
    }
    return true;
}
```

Pruebas a agregar: heap vacío, 1 elemento, repetidos, construido por inserciones, construido por `heapify`, después de `delMax` repetidos.

Complejidad de validación: O(n). Basta revisar relaciones padre-hijo porque por transitividad la invariante se propaga.

### Bloque 6 - Inserciones sucesivas vs Floyd

Demo comparativa: construir heap con vectores dados por `insert` secuencial y por `heapify` de Floyd; medir intercambios contados por versiones instrumentadas.

Conclusiones esperadas:
- Ambos producen heaps válidos; arreglos finales pueden diferir.
- Inserciones sucesivas: O(n log n) en general.
- Floyd: O(n) porque empieza percolating desde la mitad hacia atrás y procesa nodos con alturas decrecientes.

### Bloque 7 - `heapSort` con orden seleccionable

Propuesta de firma:

```cpp
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending);
```

Idea: construir heap según `comp` y luego extraer en orden apropiado; para ascending puede usar max-heap y extraer al final invertir, o construir min-heap según convenga.

Heapsort es in situ, no estable y cuesta O(n log n).

### Bloque 8 - Heap izquierdista: validación de `merge`

Agregar `isValidLeftHeap()` que verifique propiedad heap y propiedad izquierdista (npl de hijo izquierdo >= npl de hijo derecho), consistencia de tamaños y `npl` si existe.

Demo: construir dos heaps, `merge`, y validar.

### Bloque 9 - Huffman

Modificaciones: documentar desempate consistente (por ejemplo: comparar frecuencias, y en empate comparar menor símbolo o timestamp de inserción para estabilidad determinística).

Prueba con el alfabeto dado y caso único `{ {'X',100} }` — producir código `0` para el único símbolo.

### Bloque 10 - Treap

Partes A–E: instrumentar `addWithPriorityCount`, `bubbleUpCount`, `trickleDownCount` y `removeCount` y añadir demos que impriman recorridos, raíz, y validaciones `isBST`, `isHeapByPriority`, `isTreap`.

Observaciones: recorrido inorden depende solo de la propiedad BST; rotaciones preservan inorden; prioridades determinan forma.

### Bloque 11 - Comparación con Semana 5

Demo: tabla comparativa entre `BinaryHeap`, `PQ_ComplHeap`, `BinarySearchTree` y `Treap` indicando operación principal, propiedad mantenida y casos de uso.

### Bloque 12 - Pruebas obligatorias

Lista de pruebas a agregar (resumen): conservar propiedad heap después de inserción/eliminación, `getMax` no cambia tamaño, `delMax` cambia tamaño, `heapifyFloyd` produce heap válido, `heapSort` ordena con repetidos, `PQ_LeftHeap` propiedades, Huffman cubre caso único, Treap conserva invariantes.

Evidencia de `ctest`: ejecutar localmente tras aplicar cambios.

### Bloque 13 - Defensa escrita (máx. 900 palabras)

Modificar y probar código enseña cosas que no se ven solo leyendo: la gestión explicita de índices en el heap revela los muchos casos borde (nodos con un solo hijo, hojas, límites de array) que obligan a una API limpia. La interfaz `PQ` separa operaciones abstractas (`insert`, `getMax`, `delMax`) de la representación, permitiendo comparar implementaciones sin cambiar uso. La representación implícita del heap es compacta y cache-friendly, pero obliga a razonamiento cuidadoso sobre índices y condiciones de frontera. `percolateUp` es local y su coste está acotado por la altura del nodo (por eso su número de swaps es O(log n) en el peor caso); instrumentarla muestra cuándo hace cero swaps (elemento ya en posición). `percolateDown` baja un elemento para restaurar la invariante; su elección del hijo dominante define la trayectoria de reparación y explica por qué `delMax` mueve el último elemento a la raíz antes de reparar. El `heapify` de Floyd procesa nodos desde la mitad hacia atrás y aprovecha que muchos nodos están cerca de hojas, por eso logra O(n) tiempo. `heapSort` reutiliza `heapify` y extracción y por tanto es in situ pero no estable. `merge` en heap izquierdista es la operación central: implementa insert y delMax por mezcla, y su propiedad izquierdista garantiza profundidad limitada del subárbol derecho. Huffman ilustra una aplicación práctica de colas de prioridad: extraer los dos mínimos repetidamente para construir el árbol; el caso de un único símbolo requiere una convención (p.ej. código "0"). En Treap, rotaciones preservan el orden inorden (BST) mientras restauran la propiedad de heap por prioridad; las prioridades fijas permiten pruebas deterministas. Finalmente, las pruebas automatizadas y funciones de validación (`complHeapIsValid`, `isValidLeftHeap`, `isTreap`) son fundamentales para atrapar regresiones y casos borde (duplicados, tamaños, enlaces `parent`).

### Archivos modificados (resumen final)
- Ver la tabla en el inicio del documento.
