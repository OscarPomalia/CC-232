## Actividad 3-CC232

### Estudiante

- Nombre: Oscar Alberto Pomalia Suyo

#### Bloque 1

1. El cambio es de una representación basada en un bloque continuo de memoria a una representación basada en nodos enlazados; eso modifica cómo accedes, cómo insertas/borras y cómo afecta el costo y el uso de memoria.
2. -rango = índice directo en memoria contigua;
   -posición/enlace = recorrido explícito de nodos en estructuras dinámicas enlazadas.
3. La lista enlazada es buena para cambios locales cuando ya conoces el nodo donde operar. Pero si necesitas acceder a un elemento por su índice numérico, pierdes la ventaja de acceso directo y terminas recorriendo nodos.
4. Ambas estructuras aprovechan operaciones en los extremos, SLList mantiene acceso rápido al primer nodo (head) y al último nodo (tail), las operaciones requeridas son O(1) porque solo actualizan punteros de uno o dos nodos, sin recorrer la lista completa.
5. SLList es eficiente en un extremo (el frente) y puede ser eficiente en el otro extremo para inserción si guarda tail, pero no puede manejar simétricamente todas las operaciones de un Deque con el mismo costo porque le falta el enlace hacia atrás.
6. El dummy actúa como un "ancla" que permite operaciones consistentes en una lista doblemente enlazada, facilitando la implementación sin lógica extra para casos límite.
7. El método getNode(i) navega eficientemente: si i < n/2, avanza desde el inicio (dummy.next) i pasos; si no, retrocede desde el final (&dummy) n-i pasos. Esto toma O(min(i, n-i)) tiempo. Una vez localizado el nodo, las operaciones son O(1): get y set acceden/modifican directamente; add usa addBefore para insertar antes del nodo; remove usa removeNode para eliminar y ajustar punteros. El 1 representa la operación constante después de la navegación, aprovechando los enlaces bidireccionales para minimizar el recorrido.
8. Es un trade-off entre acceso (mejor que lista pura) y espacio (mejor que arreglo puro), con complejidad amortizada O(b) para operaciones locales.
9. Porque simplifica la implementación, aprovechando la eficiencia de arreglos para acceso y la flexibilidad de deques para actualizaciones.
10. No reemplaza a las estructuras de Morin (SLList, DLList, SEList) porque estas se centran en representaciones específicas con costos optimizados para operaciones básicas (e.g., DLList para acceso bidireccional eficiente, SEList para trade-off espacio-acceso). DengList es complementaria: se usa vía MorinDengBridge para aplicar algoritmos genéricos sin reescribir lógica estructural, permitiendo reutilización pero manteniendo las ventajas de cada representación. Es una separación de concerns entre estructura y algoritmos.
 
#### Bloque 2 

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
| :--- | :--- | :--- | :--- |
| `demo_sllist.cpp` | Push y pop afectan el mismo extremo. | Punteros simples (`head`, `tail`). | $O(1)$ en extremos, ideal para Stack/Queue. |
| `demo_dllist.cpp` | Inserción intermedia fluida. | Centinela + Doble enlace. | Optimización de recorrido a $O(n/2)$. |
| `demo_selist.cpp` | Impresión agrupada por bloques limitados. | Nodos con arreglos internos (BDeque). | Trade-off: menos punteros, mejor caché. |
| `demo_deng_list.cpp` | Lista ordenada y sin repetidos. | ADT enriquecido. | Esconder complejidad algorítmica en la API. |
| `demo_morin_deng_bridge.cpp` | SLList ordenada sin tener `sort()`. | Patrón Adaptador/Puente. | Reutilización sin reescribir lógica base. |
| `demo_min_structures.cpp` | Responde `min()` al instante tras un pop. | Nodos con metadatos de estado. | Espacio extra a cambio de búsquedas en $O(1)$. |
| `demo_xor_list.cpp` | Recorrido bidireccional. | Aritmética XOR con punteros. | Hack espacial para simular DLList con 1 puntero. |
| `demo_linked_adapters.cpp` | Nombres semánticos (`push`, `enqueue`). | Composición de clases. | Reusabilidad directa de SLList. |
| `demo_contiguous_vs_linked.cpp` | Tiempos de iteración secuencial vs aleatoria. | Caché de CPU vs Heap fragmentado. | Arreglos ganan en barridos por el pre-fetching. |

**Respuestas de trazado:**
1. En `demo_sllist.cpp`, la secuencia de `push` y `pop` (que actúan en el mismo extremo) frente a `add` y `remove` que simulan colas.
2. La operación de inserción en medio (`add(i, x)`), porque no pierde la cadena de enlaces al abrir espacio.
3. Que el orden lógico de los elementos se mantiene intacto independientemente de cómo se partan internamente los bloques de la SEList.
4. La ejecución directa de funciones típicas de la STL como `sort()` o `unique()` que no existen en Morin.
5. El puente permite extraer datos, ordenarlos externamente con Deng y reinyectarlos sin tocar el archivo `.h` original de Morin.
6. Guardar la información del mínimo en cada nodo gasta el doble de espacio, pero aplana el tiempo de búsqueda a $O(1)$.
7. `LinkedStack` encapsulando a `SLList` demuestra perfectamente cómo ocultar métodos complejos y exponer solo `push` y `pop`.
8. El arreglo contiguo es drásticamente más rápido en acceso secuencial puro gracias a la localidad de memoria (caché).

#### Bloque 3

1. Para SLList el test público valida estas operaciones mínimas:

add(x) en el final de la lista
push(x) al frente
size()
peek() del elemento del frente
pop() del frente
remove() del frente
2. Para DLList la prueba pública valida estas operaciones mínimas:

add(i, x) en posiciones específicas
d.add(0, 10)
d.add(1, 30)
d.add(1, 20)
size()
get(i) en índices 0, 1 y 2
remove(1)
3. Para SEList la prueba pública valida estas operaciones mínimas:

creación de SEList<int> s(3) con tamaño de bloque b = 3
add(i, x) en posiciones crecientes (s.add(i, i) para i = 0..9)
size()
get(i) en índice medio (s.get(5))
set(i, x) en índice medio (s.set(5, 50))
remove(i) en índice medio (s.remove(5))
4. SLList:
-add(1, 20) inserción en posición intermedia
-to_vector()
-secondLast()
-reverse()
-checkSize()
DLList:
-rotate(1)
-to_vector()
-isPalindrome()
-checkSize()
MinStack:
-push()
-min()
-pop()
MinQueue
-add()
-remove()
-front()
-min()
MinDeque:
-addFirst()
-addLast()
-front()
-back()
-removeLast()
-min()
XorList:
-push_back()
-push_front()
-to_vector()
-reverse()
5. LinkedStack:
-empty() inicial
-push(x) varias veces
-size()
-top()
-pop()
-empty() final
LinkedQueue:
-empty() inicial
-add(x) varias veces
-size()
-front()
-remove() varias veces
-empty() final
LinkedDeque:
-empty() inicial
-addFirst(x) y addLast(x)
-size()
-front() y back()
-removeFirst() y removeLast()
-empty() final
6. Valida la integración de una capa de algoritmo común (Deng) con las estructuras base de Morin, mostrando que se puede aplicar ordenamiento, eliminación de duplicados y reversa a diferentes implementaciones usando el mismo puente/reutilización.
7. Crecimiento con muchas inserciones al principio: s.add(i, i) 500 veces en posición 0
borrado repetido del frente: s.remove(0) 250 veces
re-inserciones adicionales al frente: s.add(i, -i) 100 veces
verificación del tamaño lógico final: assert(s.size() == 350)
8. Prueba que la lista enlazada funciona correctamente para las secuencias específicas de uso que cubre el test.
9.Una prueba pública demuestra solo que algunos ejemplos específicos funcionan; no reemplaza entender el diseño, las invariantes, los punteros y la complejidad.
10. Los tests confirman comportamiento puntual; la explicación de invariantes, punteros y complejidad es la que justifica que la estructura es correcta, segura y eficiente en general.

#### Bloque 4

- **reverse() en SLList:** Me pareció fascinante cómo se puede invertir la lista en una sola pasada usando tres punteros temporales para "voltear las flechas" sin crear una lista nueva.
- **isPalindrome() en DLList:** Aprovecha que podemos caminar desde ambos extremos hacia el centro simultáneamente, comparando los valores en $O(n/2)$.
- **Location en SEList:** Es la "dirección" de un dato: en qué bloque vive y en qué posición del arreglo interno se encuentra.

#### Bloque 5

- `LinkedStack` y `LinkedQueue` simplemente redirigen sus llamadas a una `SLList` interna. Es un gran ejemplo de **reutilización de código**.
- `MinQueue` usa dos stacks para simular el comportamiento de cola y mantener el rastro del mínimo en $O(1)$ amortizado.

#### Bloque 6

1. Ordenamiento (`sort`), eliminación de duplicados (`deduplicate` / `uniquify`) e inversión (`reverse`).
2. Separa responsabilidades. Morin maneja el core de la memoria, y Deng aporta algoritmos avanzados sin ensuciar ni reescribir el código base.
3. `to_deng` envuelve la lista original para que pueda usar los algoritmos. `assign_from_deng` toma los resultados procesados y los devuelve a la lista base.
4. Extrae los datos, los ordena usando la lógica genérica de Deng, y los reinyecta. La lista original no necesita saber cómo ordenarse a sí misma.
5. Elimina nodos adyacentes iguales, reduciendo el tamaño en $O(n)$. Generalmente requiere que la lista esté ordenada previamente.
6. La lógica de cambiar punteros para invertir se escribe una sola vez en el adaptador y sirve para cualquier estructura subyacente que use esa API.
7. Introduce un costo de copia/movimiento $O(n)$. Vale la pena cuando la ganancia algorítmica (ej. un `sort` eficiente) compensa este costo.

#### Bloque 7

1. `ArrayDeque` usa un arreglo contiguo circular que sufre pausas costosas de `resize()`. `LinkedDeque` usa nodos, asegurando $O(1)$ constante pero sin beneficios de caché.
2. Significa que, al estar físicamente adyacentes en la RAM, la CPU puede cargar bloques enteros a la memoria caché L1/L2 (Prefetching), siendo extremadamente rápido de leer.
3. Inserciones masivas en el medio de la colección o uniones (splicing) de dos listas muy grandes.
4. Para acceso aleatorio, medir ráfagas de `get(i)`. Para extremos, alternar operaciones de simulación de colas.
5. Porque el tiempo de ejecución en milisegundos depende del hardware del alumno, carga del SO y optimizaciones del compilador en ese momento.
6. Intenta simular una lista doblemente enlazada usando un solo "pseudo-puntero" calculado con la operación XOR entre las direcciones vecinas.
7. Es insegura, muy difícil de depurar y hace que los algoritmos de Garbage Collection fallen por no tener punteros explícitos.

#### Bloque 8 

Pasar de arreglos a estructuras enlazadas es cambiar velocidad de acceso por flexibilidad. En los arreglos el acceso es instantáneo (O(1)) pero mover datos es costoso. En las listas enlazadas (`SLList`, `DLList`), el acceso es lento (O(n)) pero las inserciones son quirúrgicas y baratas. La `SEList` es el punto medio que intenta darnos lo mejor de ambos mundos. Los adaptadores cierran el círculo permitiendo que estas estructuras complejas se comporten como herramientas simples (Pilas/Colas) para resolver problemas reales.

#### Autoevaluación breve

- Qué puedo defender con seguridad: Entiendo bien el relinkeo de punteros en DLList y el uso de centinelas.
- Qué todavía confundo: A veces me mareo un poco con los índices de los bloques en SEList.
- Qué evidencia usaría en una sustentación: Usaría la demo de `reverse()` para mostrar cómo manipulo punteros físicamente.

