## Actividad 5 - CC232

### Estudiante

- Nombre: Oscar Alberto Pomalia Suyo

### Bloque 1 - Núcleo conceptual

1. **Árbol enlazado vs implícito:** Un árbol enlazado es una estructura dinámica dispersa en la memoria RAM (heap) unida por punteros explícitos. Un árbol implícito usa la continuidad matemática de un arreglo 1D para "simular" conexiones mediante saltos de índices (aritmética de punteros), ahorrando memoria estructural.
2. **`BinNode`:** Guarda el `data` (carga útil) y funciona como un "GPS estructural" guardando `parent` (arriba), `left` (abajo-izq), `right` (abajo-der) y la `height` precalculada para no iterar al verificar balanceos.
3. **Puntero `parent`:** Rompe la limitación unidireccional. Permite "dar marcha atrás" en un recorrido O(1) (básico para `succ` y `pred`) y es vital para notificar a los ancestros que su `height` debe recalcularse tras una inserción o eliminación.
4. **Responsabilidad de `BinTree`:** Es el administrador principal. Encapsula y "esconde" la estructura enlazada, siendo dueño de la raíz (`root_`) y manteniendo un contador global (`size_`) para devolver el tamaño en tiempo $O(1)$.
5. **Aporte de `BinaryTree`:** Agrega las "gafas algorítmicas" sobre la infraestructura muda de BinTree: implementa los iteradores abstractos, las reglas de navegación global (primer nodo, sucesores) y los recorridos formales (inorden, preorden, postorden).
6. **Propiedad BST:** Restricción de orden absoluto. Para cada nodo $u$, todo valor en el subárbol izquierdo es estrictamente menor a $u$, y todo valor en el subárbol derecho es estrictamente mayor a $u$.
7. **Propiedad Min-Heap:** Restricción estructural (árbol binario completamente lleno de izquierda a derecha en su último nivel) más una propiedad de orden parcial vertical (todo padre es menor o igual a sus hijos).
8. **Orden BST vs Prioridad Heap:** El BST mantiene un orden global horizontal y vertical (permite ordenar arreglos); el heap solo garantiza orden jerárquico vertical (el menor siempre arriba), pero no garantiza orden entre hermanos.
9. **Inorden en BST:** Porque el recorrido LVR (Left, Visit, Right) calza perfectamente con la restricción "Menores, luego el Medio, luego los Mayores", lo que por definición de matemáticas discretas genera una secuencia monótona creciente.
10. **Heap inorden fallido:** Porque los hijos izquierdo y derecho de un nodo en un heap no están obligados a mantener un orden de precedencia entre sí. Al aplicar Inorden, saldrán valores aleatoriamente intercalados que destruyen la secuencia ordenada.

### Bloque 2 - Navegación, altura, profundidad y tamaño

1. **`hasLeft/Right`**: Verifica que el puntero no sea `nullptr`. **`isRoot`**: `parent == nullptr`. **`isLeaf`**: `!hasLeft && !hasRight`. **`isLeft/RightChild`**: Revisa si el hijo correspondiente del `parent` apunta a `this` (a sí mismo).
2. **`succ()` bajando:** Ocurre si el nodo $u$ tiene hijo derecho. El sucesor lógico es el elemento más pequeño de los mayores, es decir, bajar a la derecha una vez y luego ir hacia la extrema izquierda (`right->leftmost()`).
3. **`succ()` subiendo:** Ocurre si $u$ no tiene hijo derecho y ya procesamos todo su subárbol. Se sube por los `parent` mientras uno sea el "hijo derecho" (ya que significa que ese padre ya fue procesado). Al ser hijo izquierdo, ese padre superior es el sucesor.
4. **`pred()` simétrico:** Si hay hijo izquierdo, vas al extremo derecho de ese subárbol (`left->rightmost()`). Si no, subes mientras seas hijo izquierdo y el primer padre donde gires desde la derecha es el predecesor.
5. **Dibujo ASCII - Árbol Inorden:**
           10
         /    \
        5      15
       / \    /  \
      3   7  12  18

- Nodo 7 -> succ: 10 | pred: 5
- Nodo 15 -> succ: 18 | pred: 12
- Nodo 5 -> succ: 7 | pred: 3
6. **`depth(u)`:** Distancia desde la raíz hasta $u$. Sube por `parent` sumando $+1$ hasta encontrar un nodo donde `isRoot()` sea verdadero.
7. **`height(u)`:** Distancia de $u$ hasta su descendiente hoja más lejana. Se calcula recursivamente hacia abajo sumando `1 + max(alturaIzq, alturaDer)`.
8. **`subtreeSize(u)`:** Cuántos descendientes tiene (incluyéndose). Cuenta `1 + izquierda + derecha`.
9. **Demostración `depth + height <= height(T)`:** La `height(T)` es la longitud del camino más largo en el árbol desde la raíz hasta alguna hoja `L`. Para cualquier nodo $u$, `depth(u)` es la distancia real "raíz -> u" y `height(u)` es la distancia máxima "u -> hoja de su subárbol". Al sumar este tramo, creas un camino real "raíz -> u -> hoja". Por definición matemática, ningún camino real en el grafo puede ser más largo que el diámetro o camino máximo `height(T)`.
10. **Condición de igualdad:** La igualdad se cumple si y solo si el nodo $u$ forma parte del camino crítico (el camino más largo del árbol completo que define la altura total `height(T)`).

### Bloque 3 - Recorridos y trazado guiado

| Recorrido | Versión revisada | Estructura auxiliar | Secuencia producida | Argumento de correctitud y costo | 
| ----- | ----- | ----- | ----- | ----- | 
| Preorden Rec. | `preorderRecursive` | Pila de llamadas | V-L-R | Correctitud por inducción matemática. O(n) tiempo, O(h) RAM. | 
| Preorden Iter. | `preorderIterative` | Pila (Stack) | V-L-R | LIFO apila primero el derecho, luego el izquierdo para sacarlo antes. O(n) | 
| Inorden Rec. | `inorderRecursive` | Pila de llamadas | L-V-R | Delega el orden simétrico al call stack del CPU. O(n) | 
| Inorden Iter 1 | `inorderIterative1` | Pila manual | L-V-R | Simula el descenso total a izquierda empujando a la pila, luego procesa y retrocede. | 
| Inorden Iter 2/3| Optimizaciones | Punteros | L-V-R | Reducen operaciones innecesarias de `push/pop` manejando el estado del iterador. | 
| Postorden Rec. | `postorderRecursive` | Pila de llamadas | L-R-V | Visita pospuesta hasta el retorno total de la recursión. O(n). | 
| Postorden Iter. | `postorderIterative` | Dos Pilas / 1 Pila | L-R-V | Requiere rastrear el último nodo visitado para evitar re-procesar subárboles derechos infinitamente. | 
| Niveles | `levelOrder` | Cola (Queue) | Izq -> Der, Top -> Bottom | FIFO asegura que todo el nivel jerárquico $d$ se procese antes que el nivel $d+1$. O(n) | 

1. **Preorden:** Procesar la información de la raíz actual antes de inspeccionar a sus hijos (útil para clonar árboles).
2. **Inorden:** Procesar la raíz justo en medio, después de terminar su lado izquierdo pero antes de tocar el derecho (útil para aplanar BST ordenado).
3. **Postorden:** Procesar los hijos completamente antes de evaluar a la raíz (útil para destruir memoria del árbol de hojas hacia arriba).
4. **Por niveles:** Barrido horizontal (BFS) capa por capa de arriba hacia abajo (útil para buscar el camino más corto o serializaciones).
5. **Tiempo O(n) recursivos:** Por la ecuación de recurrencia T(n) = T(k) + T(n-k-1) + O(1). Visitas cada nodo exactamente una vez y haces una operación de tiempo constante.
6. **Tiempo O(n) iterativos:** Porque cada puntero de nodo del árbol se empuja al stack explícito exactamente una vez y se saca exactamente una vez.
7. **Memoria rec balanceado:** O(log n) porque el árbol es chato, y el call stack solo profundiza hasta la altura log n.
8. **Memoria rec degenerado:** O(n) porque se comporta como una lista enlazada, requiriendo abrir $n$ funciones recursivas simultáneas (riesgo de Stack Overflow).
9. **Pila explícita vs Pila de llamadas:** La pila de llamadas gasta la memoria restringida de ejecución del thread del Sistema Operativo. La explícita asigna del Heap general que soporta millones de elementos sin romper el programa.
10. **Crecimiento de Cola (Niveles):** En árbol completo, el último nivel contiene ~n/2 hojas. La cola se llena con todas ellas (gasta O(n) espacio). En un árbol degenerado (una línea), el máximo en un nivel es 1, así que la cola nunca supera tamaño O(1).

### Bloque 4 - Demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño | 
| ----- | ----- | ----- | ----- | 
| `demo_binary_tree.cpp` | Listas de números bajo los labels "Inorden", "Preorden" | Polimorfismo algorítmico | El iterador abstrayendo a `succ()` rinde O(1) amortizado por paso. | 
| `demo_bst.cpp` | Impresión de lista estrictamente monótona | Invariante de búsqueda (BST Property) | Evidencia física de que el árbol mantiene el orden dinámicamente. | 
| `demo_heap.cpp` | El índice 0 del arreglo retiene el menor post-extracción | Memoria implícita | Extraer cuesta O(log n) por `trickleDown`, manteniendo array denso O(n). | 
| `demo_capitulo5...` | Todas las cabeceras logran compilar sin dependencias circulares | Arquitectura de Herencia | Unificación de bases modulares para diversas aplicaciones de la semana. | 

1. **`demo_binary_tree.cpp` salida:** Que los `cout` secuenciales en consola coinciden exactamente con la teoría matemática (orden natural de los números).
2. **Evidencia de `succ()` y `pred()`:** Recorrer de "firstNode a lastNode" usando llamadas consecutivas a `succ()` genera exactamente la misma salida visual que llamar a `inorderRecursive`.
3. **Evidencia del ASCII:** Permite una comprobación humana estructural instantánea, detectando desbalanceos visuales, rotaciones fallidas o inserciones que degeneraron el árbol.
4. **Observable en `demo_bst.cpp`:** Si inyectamos un array aleatorio de números desordenados, y al llamar a la iteración el arreglo sale de menor a mayor perfectamente.
5. **Búsquedas distinguidas:** `lowerBound` y `upperBound` se notan más porque si buscas un número impar que no está, la consola te escupe el inmediatamente superior en vez de romperse. `findEQ` tira null/error.
6. **Observable de `demo_heap.cpp`:** Sin importar en qué orden hagamos los `insert/add`, al hacer un `top()` o `print` de la capa física, el `array[0]` SIEMPRE arroja el elemento más pequeño (el mínimo).
7. **`add()` vs `heapify()`:** `add` procesa números gradualmente generando estados intermedios. `heapify()` se come un arreglo random entero y lo reestructura de golpe (de abajo a arriba) a menor costo de CPU.
8. **Comparación Panorama:** Muestra que en memoria todos son derivaciones de nodos/arrays, pero aplicamos `BinTree` para relaciones padre/hijo simples, `BST` para acceso/modificación ordenada y `Heap` solo para colas de urgencia.

### Bloque 5 - Pruebas e invariantes

1. **Prueba BST Pública:** Valida Inserciones, búsquedas exactas, cálculos de cotas (Bounds) y eliminaciones básicas comprobando el tamaño final de la colección.
2. **Caso de Duplicados:** Al ejecutar un `insert(val)` con una key que ya existe, la prueba hace un `assert(size_ == anterior)` comprobando que la memoria y nodos no aumentaron ilegalmente.
3. **Equivalencia de Inorden:** Demuestra que las tres estrategias iterativas (aunque optimizadas en CPU/Stack) convergen al mismo contrato de salida matemática (la lista de nodos visitados es idéntica usando `assert(vector1 == vector2)`).
4. **`findEQ(8)`:** Se espera que devuelva un puntero al nodo exacto cuya carga clave es 8. Si no está, se exige que devuelva un puntero nulo (`nullptr`).
5. **Cotas `lowerBound(9)` y `upperBound(8)`:** De `lower(9)` se espera el nodo >= 9 más cercano en la topología. De `upper(8)` el nodo inmediatamente mayor a 8 (>8), ignorando a un posible nodo que contenga exactamente 8.
6. **Validación `isBST()`:** Verificación recursiva exhaustiva post-modificación de que, para el 100% de los nodos, se sigue manteniendo la invariante `left < parent < right`.
7. **Eliminación `remove()`:** Verifica que el nodo buscado ya no sea encontrable, que el `size` se reduzca en 1, y crucialmente que `isBST()` retorne true indicando que la reestructuración con `splice` fue limpia.
8. **`checkParentLinks()`:** Comprueba doblemente las referencias para evitar punteros huérfanos (A -> B obliga a que B -> parent == A).
9. **Heap Pública:** Se valida `add`, `remove` iterativo y que en todo instante el `top()` no violente la jerarquía de mínimos `isHeap()`.
10. **Vaciado de Min-heap:** Demuestra experimentalmente un ciclo *Heapsort*. Todo el output final a medida que vacías el heap saldrá estrictamente de menor a mayor.
11. **Pruebas de `BinTree`:** Validan la semántica de movimiento de recursos (Move Semantics). El árbol original pierde sus subnodos y el target los gana actualizando raíces y tamaños, sin fugas de memoria.
12. **Aporte pruebas internas:** Someten la estructura a casos degenerados pesados (árboles inclinados) forzando rotaciones automáticas para comprobar si `trickleDown`/`bubbleUp` soportan la explosión combinatoria.
13. **Qué sí demuestra:** Demuestra la correcta implementación de la lógica base de las funciones en escenarios predecibles (correctitud parcial pragmática).
14. **Qué no demuestra:** No demuestra que el algoritmo sea óptimo en uso de memoria para todos los casos límite. Tampoco demuestra invulnerabilidad ante Stack Overflow por recursiones profundas.
15. **Invariantes en defensa:** Las pruebas fallan por "casualidad del input". Apelar a los Invariantes matemáticos demuestra correctitud absoluta ("es axiomáticamente imposible que esto falle") y la complejidad prueba viabilidad escalar.

### Bloque 6 - Lectura cercana de código

1. **Invariantes de puntero `BinNode`:** Consistencia bidireccional estricta. Si mi hijo es X, el padre de X debo ser obligatoriamente yo (`this`).
2. **Rechazo `insertAsLC/RC`:** Se rechaza (`assert`) porque si se permitiera sobrescribir un hijo ya existente, se "cortaría" y perdería en la memoria (memory leak grave) toda la rama que colgaba previamente.
3. **`size()` `BinNode`:** Actúa como recuento DFS. Retorna 1 (por el nodo actual) más el resultado de llamar recursivamente a `size()` sobre la rama izquierda y luego la derecha.
4. **`leftmost()` / `rightmost()`:** Bucles iterativos puros (`while p->left/right != nullptr`). Se desplazan hacia las profundidades de un solo flanco devolviendo la hoja más profunda lateralmente en O(h).
5. **Paso a paso `succ()`:** Revisa si tiene `right`. Si sí, se mete y llama a `leftmost()` de esa rama. Si no hay `right`, entabla un bucle ascendiendo por su `parent`. Si el nodo es `isRightChild()` de su padre, significa que ese padre ya pasó; sigue subiendo. En cuanto el nodo sea `isLeftChild()`, retorna el `parent` (que será el primer ancestro a la derecha superior). Si llega a `root` sin ser `isLeftChild`, retorna nulo.
6. **Paso a paso `pred()`:** Simétrico inverso. Mira si hay `left`, si lo hay retorna `rightmost()` de esa subrama. Si no, asciende mientras sea `isLeftChild()`, deteniéndose y retornando el primer padre donde sea `isRightChild()`.
7. **Papel de `root_` y `size_`:** El primero es el ancla gravitacional de todo el árbol; si pierdes `root_`, todo se destruye. El segundo previene el cuello de botella de tener que contar iterativamente para peticiones básicas.
8. **`updateHeight`:** Lee `h_izq` y `h_der`, obtiene el máximo de esos dos enteros y le suma 1 para refrescar la propia altura pasivamente O(1).
9. **`updateHeightAbove`:** El nodo actualiza su altura, pero ese cambio modifica las de sus ancestros en cascada ascendente. Sube en O(h) recalibrando hasta toparse con la raíz, garantizando integridad.
10. **Transmisión de `attachAsLC/RC`:** El árbol huésped A toma el árbol forastero B. Vincula el `root_` de B como hijo de una hoja en A, suma a `size_` de A los de B, purga el header de B sin borrar los datos internos, y recalibra alturas.
11. **Diferencia `removeSubtree` vs `secede`:** `removeSubtree` lanza un comando de aniquilación (`delete`) recursiva desde el nodo borrando permanentemente la memoria. `secede` es diplomático; poda la rama, actualiza al `parent` y devuelve la rama cortada viva.
12. **Supervivencia en `secede`:** Porque está diseñado para mover componentes sub-árbol, fragmentar árboles pesados o donar ramificaciones a otras lógicas sin destruirlas.
13. **Destrucción de `removeSubtree`:** Actúa como limpieza. Si no se liberan, causarían fugas de memoria gigantescas colapsando la máquina.
14. **Verificación `checkParentLinks()`:** Analiza todo el grafo cruzando direcciones de memoria bidireccionales y tirando un Fatal Exception si detecta inconsistencia.
15. **Iteradores `BinaryTree`:** Usan la filosofía del Inorden. `firstNode` busca el más pequeño. `lastNode` busca el máximo. Avanzar (`nextNode`) se rutea internamente delegando el trabajo a `succ()`.
16. **Iterador `succ()` = Inorden:** Porque `succ` significa "el próximo mayor inmediato en las llaves", lo cual dibuja en tiempo cronológico un barrido izquierda-raíz-derecha, la propia definición formal del Inorden.
17. **Aporte ASCII:** Reduce horas de depuración de punteros abstractos a un vistazo tipográfico rápido, logrando sustentar visualmente si las rotaciones están bien formadas.

### Bloque 7 - BST

1. **Definición Formal BST:** Sea T un árbol binario. Para todo nodo x, cada nodo y perteneciente a su subárbol Izquierdo tiene clave y < x. Además, cada nodo z de su subárbol Derecho satisface z > x.
2. **Inorden BST No Decreciente:** El recorrido LVR visita el flanco izquierdo (claves menores) antes de visitar la raíz actual, y deja para el final el flanco derecho (claves mayores). Esto genera una secuencia monótona creciente.
3. **`find` vs cotas:** `find` puede fallar al retorno. `findEQ` garantiza identidad absoluta. `lowerBound` devuelve al primer elemento >= al objetivo buscado. `upperBound` salta inmediatamente al primer elemento estrictamente superior (>).
4. **Falla en EQ sin fallar en cota:** Si en `{2,4,6}` ejecutas `findEQ(5)` retornará Nulo. Si haces `lowerBound(5)` interceptará con éxito devolviendo al nodo `6` como su aproximación superior.
5. **Construcción Manual BST: `7, 3, 10, 1, 5, 8, 12, 4, 6`**
           7
         /   \
        3     10
       / \    / \
      1   5   8  12
         / \
        4   6
6. **Recorridos del árbol manual:**
   - **Inorden:** 1, 3, 4, 5, 6, 7, 8, 10, 12
   - **Preorden:** 7, 3, 1, 5, 4, 6, 10, 8, 12
   - **Postorden:** 1, 4, 6, 5, 3, 8, 12, 10, 7
   - **Niveles:** 7, 3, 10, 1, 5, 8, 12, 4, 6
7. **Simulación:**
   - `lowerBound(9)`: 9>7 -> der(10). 9<10 -> izq(8). 9>8 -> der(null). El último viraje a la izq fue el 10. Retorna `10`.
   - `upperBound(8)`: 8>7 -> der(10). 8<10 -> izq(8). Queremos >8, entonces -> der(null). Último viraje izq fue 10. Retorna `10`.
8. **Casos Eliminación:** Hoja: Desenchufas y liberas RAM. Un hijo: El hijo hereda el "cargo" del padre borrado reconectándose al abuelo. Dos hijos: Intercambias clave con su sucesor inorden, aplicas caso de "Un hijo" sobre el nodo sucesor y liberas allí.
9. **El papel de `splice`:** Desconectar limpiamente "el cable" entre un padre y un hijo objetivo re-trenzando al abuelo. Mecánica quirúrgica que permite las extracciones eficientes.
10. **Invariantes vivos post-eliminación:** El BST debe ser no decreciente, tamaño reducido en 1, alturas correctas y bidireccionalidad de punteros perfecta.
11. **`remove(3)` Conserva Inorden:** Se intercambia con "4", que es el Inorden sucesor original (menor-de-los-mayores). Garantiza no romper asimetrías con `1` y `5`.
12. **`rotateLeft`:** El nodo "Hijo Derecho" se promociona hacia arriba tomando la raíz local. La antigua raíz se hunde a "Hijo Izquierdo". Rebalancea asimetrías Derechas.
13. **`rotateRight`:** Promociona un "Hijo Izquierdo", rebajando la raíz actual a "Hijo Derecho". Apacigua el sobrepeso Izquierdo.
14. **Rotación preserva BST:** Pre-rotación el inorden era A < x < B < y < C. Al girar lógicamente sobre los enlaces, la jerarquía muta, pero la lectura secuencial de Inorden sigue produciendo exactamente A < x < B < y < C.
15. **Construir desde ordenado:** Invocamos iteración binaria cortándolo al punto central O(1), logrando distribuir equilibradamente a Izq y Der en O(log n).
16. **Costo Balanced vs Degenerate:** Balanceado O(log n) tiempo logarítmico rapidísimo. Degenerado O(n) lineal, comportándose como una simple lista.

### Bloque 8 - Heap

1. **Vector sin punteros:** Mantiene completitud estructural. Las coordenadas relativas pueden traducirse con fórmulas aritméticas al saltar posiciones de un vector, economizando sobrecarga de punteros.
2. **Fórmulas Posición:** - izq(i): 2*i + 1. der(i): 2*i + 2.
   - padre(i): (i - 1) / 2.
3. **Propiedad Min-Heap:** Para la total amplitud del arreglo, se constata siempre que V[padre(i)] <= V[i].
4. **`top()` = mínimo:** Por definición transitiva el escalón superior siempre gana al hijo subyacente. Esto condensa irrevocablemente al menor número global en el `vector[0]`.
5. **`bubbleUp(i)`:** Evaluamos si V[i] < V[padre(i)]. Si afirmativo: Swap. $i$ sube de escalón y se repite la evaluación con el nuevo padre hasta detenerse legalmente.
6. **`trickleDown(i)`:** Borramos raíz. Agarramos al último elemento y lo ascendemos a (0). Evalúa hundirse: compara cuál de sus dos hijos menores le gana, haciendo swap y bajando escalón a escalón si lo superan.
7. **Último a raíz en `remove()`:** Si borráramos el 0 sin este parche, el array dejaría un "hueco interno". Empujar el final mantiene al vector secuencial completo y habilita a `trickleDown`.
8. **Verifica `isHeap()`:** Ejecuta un For-Loop del inicio al final comprobando matemáticamente que la relación hijo-ancestro no haya sido alterada.
9. **Construcción:** Ingresar elementos uno a uno obliga `bubbleUp` caras. `heapify()` coge el input masivo e ignora las hojas para solo filtrar `trickleDowns` sobre las capas medias/altas optimizándolo en O(n).
10. **Inserción uno por uno O(n log n):** El burbujeo en el peor caso trepa un árbol completo O(log n). Por $n$ iteraciones: n * log n.
11. **`heapify()` O(n):** Al concentrar el trabajo de burbujeo inverso únicamente en los niveles superiores y descontar el área foliar (n/2 nodos con 0 trabajos), la sumatoria matemática converge linealmente a O(n).
12. **Extracción completa `{7, 3, 10, 1, 5, 8, 2}`:** Saca 1. Acondiciona heap: saca 2. Secuencia final `1,2,3,5,7,8,10`. Salen ordenados por naturaleza extractiva iterada sobre mínimos (Heapsort).
13. **Heap vs BST Comparativa:** *Heap* domina urgencias en iteraciones al menor (Mínimos continuos u colas de prioridad). *BST* domina búsquedas exactas e inorden absoluto para Diccionarios de datos.

### Bloque 9 - Cierre comparativo

Cambia el poder y la complejidad del manejo de memoria no lineal. La **representación enlazada con nodos y punteros bidireccionales (`parent`/`left`/`right`)** rompe la secuencialidad plana (O(n)) y nos permite ramificaciones exponenciales que aceleran dramáticamente el ruteo algorítmico, pero requiere un mantenimiento local implacable, particularmente en el **mantenimiento de alturas precalculadas** para predecir degeneraciones.

Ganamos la maestría de emular jerarquías usando una **representación implícita en arreglos** contiguos de RAM, lo cual evita recargar punteros inútiles si garantizamos completitud simétrica (como en el Heap). 

Entendimos la diferencia entre imponer una simple *propiedad estructural* (padres dominan a hijos para crear **prioridad y costos O(log n)** en Min-Heaps) versus imponer una **propiedad de orden absoluto en BST** que restringe matemática y globalmente los flancos `left/right`, propiciando **búsquedas eficientes acotadas** y permitiendo extraer secuencias mediante **recorridos Inorden**.

Para mi defensa y sustentación futura, esta teoría me ha comprobado la vitalidad de la rigurosidad: depender de **trazados y visualizaciones** (Demos y ASCII) y el testeo unitario, complementados axiomáticamente con una sólida **justificación de las Invariantes pre y post modificación**, y el cálculo analítico de su **complejidad asintótica**.

### Autoevaluación breve

- Qué puedo defender con seguridad: La diferencia radical de aplicación y optimización de memoria entre el árbol explícito con punteros (BST) contra el modelo aritmético array-implícito del Min-Heap.
- Qué todavía confundo: La mecánica de seguimiento mental de punteros complejos al ejecutar `succ()` bajo un escenario de "rotaciones imaginarias" LR conjuntas.
- Qué evidencia usaría en una sustentación: Replicar en un diagrama la comprobación iterativa del cálculo O(n) de la operación `heapify()`, argumentando por qué aventaja a los $n$ insertos independientes.
- Qué parte del código me parece más importante para revisar otra vez: `remove()` y sus reajustes colaterales `splice` y repunterización hacia el abuelo dentro del entorno BST, por el peligro subyacente que acarrea en memory leaks.