BLOQUE 1:
1. En Semana6/CMakeLists.txt aparecen estos targets:

sem6_demo_pq_complheap_basico
sem6_demo_heapify_floyd
sem6_demo_heapsort
sem6_demo_left_heap_merge
sem6_demo_huffman
sem6_demo_compare_with_semana5
sem6_demo_bst_rotations
sem6_demo_treap_basico
sem6_demo_capitulo6_panorama
sem6_test_public
sem6_test_internal
Además, ctest registra dos pruebas:

semana6_public
semana6_internal
2. PQ.h
PQ_ComplHeap_macro.h
PQ_ComplHeap.h
PQ_ComplHeap_getMax.h
PQ_ComplHeap_insert.h
PQ_ComplHeap_percolateUp.h
PQ_ComplHeap_delMax.h
PQ_ComplHeap_percolateDown.h
PQ_ComplHeap_heapifyFloyd.h
PQ_LeftHeap.h
PQ_LeftHeap_merge.h
PQ_LeftHeap_insert.h
PQ_LeftHeap_delMax.h
vector_heapSort.h
Huffman_PQ.h
Treap.h
3. Capitulo6.h es el header principal de la semana 6, con los includes reales de las estructuras y demos de priority queues, heap, Huffman y Treap.
Capitulo10.h es solo un alias de compatibilidad que incluye Capitulo6.h.

BLOQUE 2: 
1. Legibilidad

pqParent(i), pqLeftChild(i), pqRightChild(i) dicen directamente qué significado tienen esos índices. 
Evita leer expresiones como (i - 1) / 2 o 2*i + 1 repetidas en varios sitios.
Menos duplicación

Si la forma de calcular el padre o los hijos cambia, se cambia en un solo lugar.
Eso reduce errores y hace el código más consistente.
Condiciones de borde más claras

Funciones como pqHasLeftChild, pqHasRightChild, pqIsLeaf o pqIsInternal explican si un nodo tiene hijos o si es hoja.
El percolateDown queda más fácil de entender porque no mezcla “cálculo de índices” con “lógica del algoritmo”.
Seguridad y mantenimiento

Las funciones pequeñas son más fáciles de probar y de usar correctamente.
También evitan errores de off-by-one o de inclusión/exclusión de límites.
Cero coste práctico

Al ser constexpr y inline, el compilador puede expandirlas sin penalización significativa.
Se obtiene una abstracción limpia sin perder rendimiento.

2.  ventajas del constexpr:
    1. Tipo seguro
Las macros no respetan tipos ni ámbito.
Con constexpr, el compilador sabe el tipo de la función y valida llamadas correctamente.

 Mejor depuración
Los errores de una macro suelen verse como texto expandido, difícil de leer.
Con constexpr, el compilador puede reportar errores en el contexto de la función real.

 Scope y encapsulación
Las macros globales pueden colisionar o contaminar el código.
constexpr vive en el espacio de nombres y puede usarse como una función normal.

 Comportamiento de función real
constexpr tiene semántica de función:

puede tener argumentos,
devuelve un valor,
puede ser usada en expresiones constantes,
y permite sobrecarga/organización más limpia.
 Menos efectos secundarios ocultos
Las macros pueden evaluar argumentos varias veces y provocar comportamientos inesperados.
Una función constexpr evalúa de forma controlada.

 Compatible con optimización
El compilador puede expandir y optimizar constexpr igual que una macro, pero con mejor seguridad y legibilidad.
3. Cuando un nodo tiene solo hijo izquierdo, no existe hijo derecho válido.
Eso es un borde importante porque la reparación no puede comparar dos hijos: solo debe considerar el hijo izquierdo como candidato.

En la representación implícita, esto ocurre cuando:

left(i) < n, pero
right(i) >= n.
En ese caso, si el hijo izquierdo es mayor que el nodo actual, se intercambia con él; si no, no se hace nada.
4. Condición de hoja
En la representación implícita, un nodo es hoja cuando no tiene hijos:

left(i) >= n
o equivalentemente:

i no es interno, es decir, no cumple pqIsInternal(i, n).
Como left(i) = 2i + 1, si ese índice ya está fuera del tamaño del heap, entonces el nodo no tiene descendientes.

5. Qué cambió en percolateDown
Después de usar las funciones auxiliares, percolateDown quedó más claro y más robusto porque:

deja de repetir manualmente las fórmulas de índices,
usa comprobaciones de frontera (tener hijo izquierdo, tener hijo derecho, ser hoja) de forma explícita,
y el flujo de reparación se basa en condiciones semánticas (si tiene hijo izquierdo, si tiene hijo derecho, etc.) en lugar de expresiones crudas.
En práctica:

la lógica del algoritmo no cambia,
pero el código se vuelve más legible,
más fácil de mantener,
y menos propenso a errores de borde.