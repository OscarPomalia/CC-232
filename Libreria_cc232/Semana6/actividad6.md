## Actividad 6 - CC232

### Estudiante
- Nombre: Oscar Alberto Pomalia Suyo
- Código: 20240385I
- Fecha: 7 de junio del 2026

### Resumen de modificaciones
| Bloque | Archivo modificado | Cambio realizado | Evidencia |
|---|---|---|---|
| 2 | `PQ_ComplHeap_macro.h` | Reemplazo de macros por `constexpr` functions | Mejora seguridad de tipos; compila correctamente. |
| 3 | `PQ_ComplHeap_percolateUp.h`| Agregada función `complHeapPercolateUpCount` | Traza de intercambios en inserción comprobada. |
| 4 | `PQ_ComplHeap_percolateDown.h`| Agregada función `complHeapPercolateDownCount` | Trazado de delMax instrumentado correctamente. |
| 5 | `PQ_ComplHeap.h` | Nueva función `complHeapIsValid()` | Pruebas unitarias pasan validando invariantes. |
| 7 | `vector_heapSort.h` | `heapSort` con parámetro `ascending` | Ordenamiento bidireccional y con repetidos validado. |
| 8 | `PQ_LeftHeap.h` | Función `isValidLeftHeap()` | Verifica NPL e invariante heap en `merge`. |
| 9 | `Huffman_PQ.h` | Manejo de caso de un símbolo y empate | Árbol libre de prefijos comprobado. |
| 10 | `Treap.h` | Instrumentación de `bubbleUpCount` y operaciones | Treap verificado como BST y Heap a la vez. |

### Bloque 1 - Diagnóstico inicial

**Ejecución de CMake inicial:**
| Comando ejecutado | Resultado / Error | Interpretación |
|---|---|---|
| `cmake -S . -B build` | Build files generated successfully | Entorno y CMakeLists.txt están bien configurados. |
| `cmake --build build` | Targets construidos al 100% | Ausencia de errores de sintaxis en el código base. |
| `ctest --test-dir build` | 100% tests passed | La librería original funciona correctamente antes de intervenirla. |

**Respuestas:**
1. **Targets:** `demo_pq_complheap_basico`, `demo_heapsort`, `demo_huffman`, `demo_treap_basico`, `test_public_week6`, `test_internal_week6`, entre otros.
2. **Archivos desde Capitulo6.h:** Cabeceras de `PQ`, Heaps Completos, Izquierdistas y algoritmos como HeapSort.
3. **Capitulo6 vs Capitulo10:** El capítulo 6 abarca colas de prioridad básicas (Heaps), mientras que el 10 suele adentrarse en colas de prioridad avanzadas o estructuras de búsqueda especializadas como Treaps (según la convención de Deng).
4. **Dependencias:** Todo Treap hereda o usa la noción de `BinNode` y `BST` de la Semana 5. El Heap implícito usa el arreglo secuencial (Vector) en lugar de punteros.
5. **Prioridad pura:** `PQ_ComplHeap` y `PQ_LeftHeap`.
6. **Búsqueda ordenada:** `BinarySearchTree` (Semana 5).
7. **Híbrida:** `Treap` (Tree + Heap).
8. **Evidencia:** Que el modelo inicial compila y la representación implícita pasa los test básicos.

### Bloque 2 - Utilidades de heap completo

**Código modificado (PQ_ComplHeap_macro.h):**
```cpp
// MOD-A6-B2: Reemplazo de macros por constexpr para seguridad de tipos
constexpr std::size_t pqHasLeftChild(std::size_t i, std::size_t n) { return 2 * i + 1 < n; }
constexpr std::size_t pqHasRightChild(std::size_t i, std::size_t n) { return 2 * i + 2 < n; }
constexpr bool pqIsLeaf(std::size_t i, std::size_t n) { return !pqHasLeftChild(i, n); }
constexpr bool pqIsInternal(std::size_t i, std::size_t n) { return pqHasLeftChild(i, n); }
```

**Respuestas:**
1. **Funciones pequeñas:** Aumentan la legibilidad matemática de la navegación en el arreglo implícito sin penalizar el rendimiento (por ser inline/constexpr).
2. **Ventaja `constexpr` vs macros:** Evitan efectos secundarios ocultos (como evaluar argumentos múltiples veces si pasas `i++`), ofrecen tipado estricto (`std::size_t`) y pueden ser depuradas, a diferencia de las macros de preprocesador que solo hacen reemplazo de texto.
3. **Caso borde un hijo:** En un heap completo, si un nodo tiene solo un hijo, *obligatoriamente* es el izquierdo.
4. **Hoja:** Un nodo es hoja si su hijo izquierdo caería fuera del tamaño `n` del arreglo.
5. **Complejidad:** La complejidad de `percolateDown` no cambia (sigue siendo $O(\log n)$) porque `constexpr` se resuelve y optimiza en tiempo de compilación.

### Bloque 3 - Conteo en percolateUp

**Código nuevo:**
```cpp
// MOD-A6-B3: Conteo de intercambios en percolateUp
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (i > 0) {
        std::size_t p = (i - 1) / 2; // padre
        if (comp(a[p], a[i])) { // Si padre es menor estricto (en max-heap)
            std::swap(a[i], a[p]);
            swaps++;
            i = p;
        } else break;
    }
    return swaps;
}
```

**Respuestas:**
1. **Cero intercambios:** Cuando el elemento insertado ya cumple la prioridad de ser menor o igual que su padre desde el inicio.
2. **$O(\log n)$ intercambios:** Cuando se inserta el elemento de máxima prioridad absoluta, obligándolo a burbujear hasta la raíz del árbol.
3. **Relación posición/altura:** El número máximo de intercambios es exactamente la profundidad actual del nodo en el árbol lógico, que está acotada por la altura del heap $\lfloor \log_2(n) \rfloor$.
4. **Arreglo no ordenado:** El heap solo garantiza una relación vertical (padre > hijos). Los hermanos no tienen restricción de orden entre ellos.
5. **Propiedad garantizada:** La Propiedad Heap (Invariante estructural).

### Bloque 4 - Conteo en percolateDown

**Código nuevo:**
```cpp
// MOD-A6-B4: Conteo en percolateDown
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (pqHasLeftChild(i, n)) {
        std::size_t j = 2 * i + 1;
        if (pqHasRightChild(i, n) && comp(a[j], a[j + 1])) j++; // Elegir el mayor
        if (comp(a[i], a[j])) {
            std::swap(a[i], a[j]);
            swaps++;
            i = j;
        } else break;
    }
    return swaps;
}
```

**Respuestas:**
1. **Último a la raíz:** Para mantener la forma de "árbol binario completo" del arreglo implícito. Borrar desde el final asegura que no queden "agujeros" en memoria.
2. **Baja y no sube:** Porque colocamos un elemento pequeño (hoja) en la raíz. Por definición viola la prioridad, así que debe hundirse ("percolar") hasta su nivel adecuado.
3. **Elección de hijo:** Se compara a ambos hijos. En un Max-Heap, el padre debe intercambiarse con el hijo de **mayor** valor para garantizar que el nuevo padre domine a ambos.
4. **Solo hijo izquierdo:** Simplemente se evalúa contra ese único hijo izquierdo.
5. **Costo $O(\log n)$:** Porque baja un nivel a la vez, y la altura del árbol completo es exactamente $\log_2(n)$.

### Bloque 5 - Validación de propiedad heap

**Código de validación:**
```cpp
// MOD-A6-B5: validacion de propiedad heap
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        if (left < n && comp(a[i], a[left])) return false;
        if (right < n && comp(a[i], a[right])) return false;
    }
    return true;
}
```

**Respuestas:**
1. **Invariante verificado:** Que para todo nodo, su prioridad sea mayor o igual que la de sus hijos directos.
2. **Revisar relaciones locales:** Por la propiedad transitiva de la desigualdad. Si $A \ge B$ y $B \ge C$, matemáticamente $A \ge C$.
3. **Evitar descendientes globales:** Porque el chequeo local propagado cubre todo el árbol gracias a la transitividad (y mantiene el algoritmo en O(n)).
4. **Costo:** $O(n)$, visita cada índice del vector constante veces.
5. **Útil en pruebas:** Porque el $O(n)$ ralentizaría operaciones que idealmente deben ser $O(1)$ o $O(\log n)$ en producción si se llama tras cada modificación.

### Bloque 6 - Inserciones sucesivas vs Floyd

| Método | Intercambios | Complejidad de construcción |
|---|---|---|
| Inserciones (`percolateUp`) | ~18 | $O(n \log n)$ |
| Floyd (`heapify`) | ~7 | $O(n)$ |

**Respuestas:**
1. **Heaps válidos diferentes:** Porque un mismo conjunto de números puede acomodarse en diferentes configuraciones de Max-Heap sin violar la regla padre > hijo. (Los hijos no están ordenados entre sí).
2. **Costo $O(n \log n)$ inserciones:** Porque empujar $n$ elementos al final implica ejecutar `percolateUp` que toma hasta $\log n$ para cada uno de los elementos.
3. **Costo $O(n)$ Floyd:** Floyd arranca desde los últimos padres hacia la raíz. La mayoría de los nodos (las hojas) no se mueven (0 intercambios). Matemáticamente, la suma del esfuerzo decae rápidamente convergiendo a $O(n)$.
4. **Nodos procesados primero:** Los padres del último nivel interno (el índice $\lfloor n/2 \rfloor - 1$) bajando hacia la raíz (0).
5. **Hojas ignoradas:** Porque las hojas no tienen hijos, por ende no tienen hacia dónde hundirse (ya cumplen trivialmente la propiedad heap).

### Bloque 7 - heapSort

**Código modificado:**
```cpp
// MOD-A6-B7: heapSort direccional in situ
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
    // 1. Construir el heap en O(n) usando Floyd
    for (int i = a.size() / 2 - 1; i >= 0; --i) {
        complHeapPercolateDown(a, a.size(), i, comp);
    }
    // 2. Extraer iterativamente in situ
    for (int n = a.size(); n > 1; ) {
        std::swap(a[0], a[--n]);
        complHeapPercolateDown(a, n, 0, comp);
    }
    // 3. Ajustar el orden si es necesario
    if (!ascending) {
        std::reverse(a.begin(), a.end());
    }
}
```

**Respuestas:**
1. **In situ:** Porque al extraer la raíz, el espacio que queda libre "al final" del rango activo del arreglo se usa para almacenar el valor extraído en su posición definitiva.
2. **Destruye el heap:** La fase de extracción (`std::swap(a[0], a[--n])`) reduce artificialmente el tamaño $n$ del heap válido, colocando valores ordenados fuera de la jurisdicción de las operaciones.
3. **Costo $O(n \log n)$:** El heapify toma $O(n)$, pero luego haces $n$ extracciones, cada una exigiendo un `percolateDown` de costo $O(\log n)$.
4. **Estabilidad:** No es estable. Ejemplo: `[5A, 5B, 1]`. Al armar el Max-Heap e intercambiar la raíz con el último elemento, el `5A` perderá su posición relativa frente a `5B`.
5. **Diferencia con `delMax` repetido:** `delMax` clásico asume reducir el tamaño del contenedor, `heapSort` recicla inteligentemente ese mismo contenedor como almacenamiento final.

### Bloque 8 - Heap izquierdista

**Código de validación:**
```cpp
// MOD-A6-B8: Validación Leftist Heap
bool isValidLeftHeap(Node* root) const {
    if (!root) return true;
    if (root->left && root->priority < root->left->priority) return false;
    if (root->right && root->priority < root->right->priority) return false;
    int nplL = root->left ? root->left->npl : 0;
    int nplR = root->right ? root->right->npl : 0;
    if (nplL < nplR) return false; // Invariante izquierdista
    return isValidLeftHeap(root->left) && isValidLeftHeap(root->right);
}
```

**Respuestas:**
1. **Centralidad de `merge`:** Porque en un Leftist Heap, absolutamente todas las operaciones mutables dependen de fusionar. Insertar un nodo es fusionar el árbol con un árbol de tamaño 1. Eliminar la raíz es fusionar el subárbol izquierdo con el derecho.
2. **Insertar:** Se crea un nodo unitario y se llama a `merge(root, newNode)`.
3. **delMax:** Se guarda la raíz a devolver, y el nuevo `root` es simplemente `merge(root->left, root->right)`.
4. **Diferencia con Heap Completo:** No usa un arreglo implícito, sino una estructura enlazada sesgada a la izquierda (donde el Null Path Length del hijo izquierdo es siempre $\ge$ al del hijo derecho).
5. **Ventaja:** Permitir fusiones de colas de prioridad enteras en tiempo $O(\log N)$, algo que obligaría a rearmar en $O(N)$ en un heap binario estándar de arreglos.

### Bloque 9 - Huffman

**Tabla de ejecución (Alfabeto A-E):**
| Símbolo | Frecuencia | Código (Ejemplo) | Longitud |
|---|---|---|---|
| E | 20 | 0 | 1 bit |
| C | 10 | 110 | 3 bits |
| D | 10 | 111 | 3 bits |
| A | 5 | 100 | 3 bits |
| B | 5 | 101 | 3 bits |

**Respuestas:**
1. **PQ necesaria:** Porque el algoritmo es Greedy: en cada paso DEBE agrupar estrictamente a los dos bosques con menor frecuencia.
2. **Elementos extraídos:** Los dos árboles/hojas con las frecuencias combinadas más pequeñas.
3. **Elemento insertado:** El nuevo árbol combinado cuya frecuencia es la suma de los dos extraídos (padre).
4. **Caso un solo símbolo:** Generaría un bosque con 1 nodo que nunca entra al ciclo de fusión, dejando un árbol plano al que es imposible asignarle direcciones 0/1. Requiere una rama dummy o un parche duro.
5. **Libre de prefijos:** Ningún código (ej. "10") es el inicio exacto de otro código ("101"). Garantiza decodificación sin ambigüedades.
6. **Empate:** Cambia qué nodos se combinan primero, alterando el diseño de ramas y el código binario asignado.
7. **Longitud total ponderada invariable:** El empate no afecta el coste global. La matemática demuestra que ambas configuraciones lograrán la compresión teórica óptima idéntica.

### Bloque 10 - Treap

**Respuestas Teóricas:**
1. **Inorden inmutable:** Porque la propiedad de Heap solo reordena verticalmente (padre-hijo mediante rotaciones). Las rotaciones (Left/Right) respetan 100% la propiedad BST horizontal, así que la lectura izquierda-raíz-derecha no se altera.
2. **Raíz cambiante:** Si entra un nodo con prioridad masiva, las rotaciones lo "burbujearán" hasta convertirlo en la nueva raíz física.
3. **Nodo que sube:** El nodo recién insertado (si usa Min-Heap para prioridades).
4. **Conservación de rotación local:** Conserva la "Propiedad de Árbol Binario de Búsqueda" ($L < P < R$).
5. **Restauración de `bubbleUp`:** Intenta restaurar la "Propiedad Heap" violada.

**Respuestas Instrumentación y Eliminación:**
1. **Secuencia de rotaciones repetidas:** Porque al forzar inserciones descendentes con prioridad cada vez mayor, cada nuevo nodo se auto-promociona hasta la raíz.
2. **`bubbleUpCount` = 0:** Cuando el nodo ingresado tiene una prioridad menor (o mayor en Max-Heap) que las de su padre; se queda quieto en las hojas.
3. **Peor caso de rotaciones:** $O(h)$ donde $h$ es la profundidad de inserción.
4. **Eliminación no clásica:** Borrar un nodo intermedio directamente dejaría huecos o destruiría el Invariante de Heap. Debe rotarse (hundirse con `trickleDown`) hacia las hojas para luego cortarlo limpiamente.
5. **Hijo de menor prioridad (`trickleDown`):** Para rotarlo hacia arriba y que este hijo asuma el rol dominante respetando la propiedad heap.
6. **Invariantes post-splice:** La propiedad BST de la estructura y la integridad estructural subyacente.
7. **`lowerBound`/`upperBound` dependen del BST:** La prioridad es aleatoria (para balance), las claves controlan la lógica secuencial útil. El Treap se comporta como BST en *búsquedas*, y como Heap en *topología y balance estadístico*.
8. **No reemplaza a PQ:** Porque cada nodo carga un puntero costoso y la estructura gasta mucha RAM, a diferencia de la matriz implícita O(1) de `PQ_ComplHeap`.

### Bloque 11 - Comparación con Semana 5

| Estructura | Operación principal | Propiedad mantenida | Evidencia/Uso ideal |
|---|---|---|---|
| `BinaryHeap` (S5) | Arbol de demostración | Topológica básica | Fines pedagógicos. |
| `PQ_ComplHeap` (S6) | `getMax`, `insert` | Prioridad Min/Max implícita | Extraer máximos repetidamente ($O(1)$ buscar, $O(\log n)$ borrar). |
| `BinarySearchTree` (S5) | `find`, `lowerBound` | Orden L-P-R absoluto | Responder a búsquedas ordenadas. |
| `Treap` (S6) | `add`, `remove`, `find` | BST + Heap mixto | Búsqueda ordenada con autobalanceo probabilístico ($O(\log n)$ esperado). |

### Bloque 12 - Pruebas

Se agregaron a `test_public_week6.cpp`:
- `test_complheap_validity()`: Prueba el invariante post-inserciones para prevenir desincronización de índices.
- `test_heapsort_stability()`: Confirma funcionamiento con arrays de elementos iguales o invertidos.
- `test_huffman_single()`: Comprueba el caso borde de diccionario de tamaño 1 (evita segment fault).
- `test_treap_dual_invariant()`: Verifica simultáneamente `isBST()` e `isHeapByPriority()`.

*Explicación Bug:* La prueba conjunta del Treap atrapa fallas mortales en la función de rotación (si las ramas subyacentes se reconectan mal tras un Right-Rotate, `isBST()` devuelve false).

### Bloque 13 - Defensa escrita

El modificar de forma directa las estructuras base me demostró que usar ADTs como "cajas negras" esconde el verdadero motor algorítmico subyacente. La **interfaz abstracta PQ** nos permite dictar un contrato lógico, pero la **representación implícita de un heap binario completo** es la que logra un ahorro masivo de RAM al prescindir de punteros físicos mediante el enrutamiento matemático `2*i+1`.

Comprendí la sutileza de **percolateUp** que compara contra un solo padre en $O(\log N)$ y de **percolateDown** que requiere elegir dominantemente entre los hijos. Esta diferencia de flujo dictamina por qué la asombrosa técnica **heapify de Floyd** logra reensamblar un desorden en asombrosos $O(N)$, mientras que insertar $N$ veces cuesta $O(N \log N)$. Este mismo motor acciona el **heapSort**, demostrando ser rápido en espacio $O(1)$ in situ, pero inherentemente inestable.

Del **heap izquierdista**, asimilé la función **merge**. Reducir inserción y extracción a una simple fusión acorta radicalmente el acoplamiento y brinda una solución potente y de coste amortizado garantizado. 

Al programar **Huffman**, la cola de prioridad pasó a ser simplemente un engranaje subordinado a una heurística Greedy, donde resolver los desempates demostró que diferentes formas de árbol rinden idénticas eficiencias ponderadas, exigiendo extremo cuidado en los bordes como un alfabeto unitario. 

Finalmente, el **Treap** fue el eslabón más revelador. Entender que puede obedecer simultáneamente a una prioridad aleatorizada en su eje-Y (propiedad heap) para probabilísticamente evitar un árbol degenerado, sin jamás alterar el eje-X secuencial de las llaves (**BST**, manteniendo intacto su Inorden), cambia la forma en que pensamos sobre el equilibrio dinámico y hace que **BinaryHeap** y **BST** puros de la Semana 5 se sientan como componentes aislados de un motor más grande. En general, someter el código a pruebas rigurosas e invariantes explícitas asegura una transición de un código "que funciona a veces" a un software de nivel ingenieril infalible.