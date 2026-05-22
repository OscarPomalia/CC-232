### Árboles binarios según Morin

### Resumen

El documento de Morin introduce los **árboles binarios** como una estructura fundamental para representar relaciones jerárquicas y para construir estructuras de datos más especializadas.
Su desarrollo comienza con la noción de `BinaryTree`, donde cada nodo mantiene referencias a su hijo izquierdo, hijo derecho y padre, luego avanza hacia operaciones estructurales como cálculo de profundidad, tamaño, altura y 
recorridos y finalmente presenta el `BinarySearchTree`, una especialización del árbol binario que impone una propiedad de orden sobre los datos almacenados. 

Para el curso, este documento se usa principalmente como fundamento teórico de los árboles binarios de búsqueda. El curso aborda **colas de prioridad, heaps, heapify y árboles binarios de búsqueda**, y señala como bibliografía de apoyo a Morin para `BinaryHeap` y `BinarySearchTree`. 
La librería CC232 para la semana 5 refleja esa organización: incluye una infraestructura base de árboles binarios, una capa de navegación tipo `BinaryTree`, una implementación de `BinarySearchTree` y una implementación de `BinaryHeap`. 


Desde un punto de vista técnico, Morin aporta tres ideas centrales. La primera es que un árbol binario puede representarse con nodos enlazados mediante punteros `left`, `right` y `parent`. 
La segunda es que muchas propiedades del árbol, como profundidad, tamaño y altura se obtienen siguiendo caminos o recurriendo sobre subárboles. 
La tercera es que, al imponer la propiedad de búsqueda binaria, las operaciones `find`, `add` y `remove` se reducen a seguir un camino desde la raíz, por lo que su complejidad depende directamente de la altura del árbol. 

### Introducción

En la programación de estructuras de datos, los árboles binarios ocupan una posición intermedia entre las estructuras lineales y las estructuras jerárquicas más complejas.  A diferencia de un arreglo o una lista, un árbol no organiza sus elementos en una única secuencia lineal. 
En cambio, cada nodo puede ramificarse hacia otros nodos, lo que permite modelar jerarquías, decisiones, particiones de datos y relaciones de orden parcial.

Morin parte de una definición matemática: un árbol binario puede entenderse como un grafo finito, conexo, no dirigido y sin ciclos, donde ningún vértice tiene grado mayor que tres. Al enraizar el árbol, se distingue un nodo especial llamado raíz; desde ahí se definen las relaciones de padre, hijo izquierdo e hijo derecho. 
Esta visión es importante porque muestra que la estructura no depende inicialmente de claves ni prioridades: antes de hablar de búsqueda o de heaps, se necesita comprender la estructura base del árbol binario. 

En el código para la semana 5, esta base se vuelve operativa. El repositorio separa deliberadamente cuatro niveles: árbol binario base (`BinNode`, `BinTree`), árbol binario navegable (`BinaryTree`), árbol de búsqueda (`BinarySearchTree`) y heap implícito (`BinaryHeap`). 
Esa separación permite distinguir qué operaciones dependen únicamente de la representación enlazada y cuáles dependen de una propiedad adicional, como la propiedad de orden en un BST o la propiedad de prioridad en un heap. 

### Desarrollo

#### 1. Árbol binario como estructura enlazada

Morin presenta el árbol binario usando nodos que almacenan tres referencias estructurales: hijo izquierdo, hijo derecho y padre. 
Esta representación permite moverse hacia abajo en la estructura, mediante `left` y `right`, y también hacia arriba, mediante `parent`. 

Conceptualmente, un nodo de árbol binario tiene esta forma:

```cpp
class BTNode {
    N* left;
    N* right;
    N* parent;
};
```

La importancia de esta representación es que cada nodo conoce su contexto local. Con `left` y `right`, el nodo define los subárboles que dependen de él. Con `parent`, el nodo puede recuperar el camino hacia la raíz. 
Esta última referencia no es estrictamente necesaria para todas las operaciones, pero facilita recorridos no recursivos, cálculo de profundidad, navegación inorden y operaciones de eliminación o rotación.

En el código para la semana 5, esta idea aparece en `BinNode.h`, que el README describe como un nodo enlazado con `parent`, `left`, `right`, `height`, inserción de hijos, sucesor y predecesor. 
Así, Morin proporciona el modelo abstracto y la librería lo convierte en una estructura C++ reutilizable.


#### 2. Raíz, profundidad, altura y subárboles

Una vez fijada la raíz, cada nodo adquiere una posición dentro del árbol. Morin define la **profundidad** de un nodo como la longitud del camino desde ese nodo hasta la raíz. 
Esta definición tiene una interpretación algorítmica inmediata: para calcular la profundidad de un nodo, basta subir por `parent` hasta alcanzar la raíz, contando los pasos. 

El algoritmo conceptual es:

```cpp
int depth(Node* u) {
    int d = 0;
    while (u != r) {
        u = u->parent;
        d++;
    }
    return d;
}
```

Este algoritmo tiene costo proporcional a la profundidad del nodo. Si el nodo está cerca de la raíz, el cálculo es rápido; si está en un camino largo, el costo aumenta. 
Esto introduce una idea que se repetirá durante todo el capítulo: en árboles binarios, muchas operaciones dependen de la **altura** o de la **longitud del camino recorrido**.

Morin también define el **subárbol** de un nodo `u` como el árbol formado por `u` y todos sus descendientes. Esta noción permite expresar operaciones recursivas de forma natural. 
El tamaño de un subárbol, por ejemplo, se define como uno más el tamaño del subárbol izquierdo y el tamaño del subárbol derecho:

```cpp
int size(Node* u) {
    if (u == nil) return 0;
    return 1 + size(u->left) + size(u->right);
}
```

La altura de un nodo se calcula de forma similar:

```cpp
int height(Node* u) {
    if (u == nil) return -1;
    return 1 + max(height(u->left), height(u->right))
}
```

La convención `height(nil) = -1` es técnicamente conveniente porque hace que una hoja tenga altura `0`. Si una hoja no tiene hijos, ambos hijos son `nil`; por tanto, su altura es `1 + max(-1, -1) = 0`. 

En la librería, estas ideas aparecen en la capa `BinaryTree`, que el README describe como una capa estilo Morin con `depth`, `height`, `subtreeSize`, navegación, iteración inorden y representación ASCII.

#### 3. Recursión estructural en árboles binarios

Una de las ideas más importantes de Morin es que los árboles binarios se prestan naturalmente a algoritmos recursivos.
Esto se debe a que un árbol binario está definido de manera autorreferencial: cada nodo tiene un subárbol izquierdo y un subárbol derecho, que también son árboles binarios.

Por eso, funciones como `size` y `height` siguen el mismo patrón:

1. Resolver el caso base: el nodo es `nil`.
2. Resolver recursivamente el subárbol izquierdo.
3. Resolver recursivamente el subárbol derecho.
4. Combinar los resultados.

Esta forma de razonamiento es fundamental para justificar correctitud. Por ejemplo, para demostrar que `size(u)` devuelve el número de nodos del subárbol enraizado en `u`, se argumenta por inducción estructural: si `u` es `nil`, el 
tamaño es cero; si `u` no es `nil`, el subárbol contiene el nodo `u`, todos los nodos del subárbol izquierdo y todos los nodos del subárbol derecho.

Sin embargo, Morin también advierte que la recursión tiene un costo práctico: la profundidad máxima de la pila de llamadas es la altura del árbol. Si el árbol está muy desbalanceado, esa altura puede ser lineal en el número de nodos, y una implementación recursiva puede consumir demasiada memoria de pila. 

Esta observación es relevante para la semana 5 porque el código no solo ofrece recorridos recursivos, sino también recorridos iterativos. 
El README enumera preorden recursivo, preorden iterativo, inorden recursivo, tres variantes iterativas de inorden, postorden recursivo, postorden iterativo y recorrido por niveles. 


#### 4. Recorridos no recursivos y uso del puntero `parent`

Morin presenta una técnica especialmente interesante para recorrer un árbol sin usar recursión. La técnica mantiene tres punteros: el nodo actual `u`, el nodo desde donde se llegó `prev` y el siguiente nodo a visitar `next`. 
La decisión de movimiento depende de la relación entre `prev` y `u`.

Si se llega a `u` desde su padre, el recorrido intenta bajar primero al hijo izquierdo. Si se llega desde el hijo izquierdo, intenta avanzar al hijo derecho. Si se llega desde el hijo derecho, significa que el subárbol de `u` ya fue procesado y corresponde regresar al padre. 

La lógica puede resumirse así:

```text
Si prev == u->parent:
    entrar al subárbol izquierdo si existe;
    si no, entrar al derecho;
    si no, subir al padre.

Si prev == u->left:
    entrar al subárbol derecho si existe;
    si no, subir al padre.

Si prev == u->right:
    subir al padre.
```

La importancia técnica de este enfoque es que reemplaza la pila implícita de la recursión por información local almacenada en los punteros del árbol. 
En árboles con `parent`, el camino de regreso hacia la raíz ya está codificado en la estructura, por lo que no siempre es necesario usar una pila explícita.

Esta idea también aparece en el diseño de la librería para la semana 5. Aunque la librería incluye recorridos clásicos con pila, también ofrece variantes iterativas que aprovechan `parent` y sucesores inorden. 
La separación entre `BinNode`, `BinTree` y `BinaryTree` permite estudiar estas estrategias de navegación de forma aislada antes de aplicarlas a BST o heaps. 


#### 5. Recorrido por niveles

Morin distingue el recorrido en anchura, o **breadth-first traversal**, de los recorridos recursivos clásicos. Mientras que preorden, inorden y postorden siguen relaciones de subárbol, el recorrido en anchura procesa el árbol por
niveles: primero la raíz, luego sus hijos, luego sus nietos, y así sucesivamente. 

La estructura auxiliar adecuada para este recorrido es una cola. La razón es que los nodos deben procesarse en el mismo orden en que fueron descubiertos. El algoritmo encola la raíz; luego, mientras la cola no está vacía, desencola un nodo, lo procesa y encola sus hijos no nulos.

Técnicamente, este recorrido es importante por dos razones. Primero, permite observar la forma del árbol capa por capa, lo que es útil para depuración, visualización y verificación de completitud. 
Segundo, anticipa la idea de los heaps binarios, donde la estructura lógica se interpreta como un árbol casi completo recorrido por niveles, aunque físicamente se almacene en un arreglo.

En el código para la semana 5, el recorrido por niveles está incluido explícitamente entre los recorridos implementados. 

#### 6. BinarySearchTree como especialización de BinaryTree

La parte más directamente vinculada con la semana 5 es el `BinarySearchTree`. Morin define un árbol binario de búsqueda como un árbol binario cuyos nodos almacenan valores provenientes de un orden total y que satisfacen la propiedad de búsqueda binaria:

```text
Para cada nodo u:
    todo valor del subárbol izquierdo de u es menor que u.x;
    todo valor del subárbol derecho de u es mayor que u.x.
```

Esta propiedad transforma una estructura puramente jerárquica en una estructura de búsqueda ordenada. Ya no se trata solo de recorrer todos los nodos, sino de decidir en cada paso qué mitad del árbol descartar. 
Si el valor buscado es menor que el nodo actual, se baja por la izquierda; si es mayor, se baja por la derecha; si es igual, la búsqueda termina. 

Esta es la diferencia conceptual entre `BinaryTree` y `BinarySearchTree`: un `BinaryTree` solo impone forma; un `BinarySearchTree` impone forma y orden. 
En el código, `BinarySearchTree.h` aparece como una estructura especializada con `findLast`, `find`, `findEQ`, `lowerBound`, `upperBound`, `addChild`, `add`, `splice`, `remove`, rotaciones y construcción balanceada desde arreglo ordenado.


#### 7. Búsqueda exacta en BST

La búsqueda exacta en un BST consiste en seguir un camino descendente desde la raíz. Morin la presenta mediante la operación `findEQ(x)`. 
En cada nodo `w`, se compara `x` con `w.x`. Si `x` es menor, se avanza al hijo izquierdo; si es mayor, al hijo derecho; si es igual, se devuelve el valor encontrado. 

El esquema es:

```cpp
T findEQ(T x) {
    Node* w = r;
    while (w != nil) {
        int comp = compare(x, w->x);
        if (comp < 0) {
            w = w->left;
        } else if (comp > 0) {
            w = w->right;
        } else {
            return w->x;
        }
    }
    return null;
}
```

La correctitud de este algoritmo depende enteramente del invariante BST. Si `x < w.x`, entonces `x` no puede estar en el subárbol derecho de `w`, porque todo valor allí es mayor que `w.x`. 
De modo análogo, si `x > w.x`, no puede estar en el subárbol izquierdo. Por tanto, cada comparación elimina una rama completa de la búsqueda.

El costo temporal es proporcional a la longitud del camino recorrido. Si la altura del árbol es `h`, la búsqueda cuesta `O(h)`. 
En un árbol equilibrado, `h` puede ser `O(log n)`. En un árbol degenerado, `h` puede ser `O(n)`.


#### 8. Búsqueda por cota: menor valor mayor o igual que `x`

Morin también presenta una operación más refinada: `find(x)`, que devuelve el menor valor almacenado en el árbol que sea mayor o igual que `x`. Esta operación es conceptualmente cercana a `lower_bound` en C++.

La idea es mantener un candidato `z`. Cada vez que la búsqueda encuentra un nodo `w` con `x < w.x`, ese nodo es un candidato válido porque es mayor que `x`; sin embargo, podría existir un candidato más pequeño en el subárbol izquierdo, así que se continúa hacia la izquierda. 
Si `x > w.x`, el nodo `w` no puede ser respuesta, así que se continúa hacia la derecha. 

Este patrón es técnicamente importante porque muestra que un BST no solo sirve para pertenencia exacta, sino también para consultas de orden. 
En la librería esta idea aparece en operaciones como `lowerBound` y `upperBound` dentro de la implementación de `BinarySearchTree`. 

La diferencia entre búsqueda exacta y búsqueda por cota es la siguiente:

```text
findEQ(x):
    devuelve x si existe; si no existe, falla.

find(x) / lower_bound(x):
    devuelve el menor elemento >= x, exista o no x exactamente.
```

Este tipo de consulta es una razón fundamental para estudiar árboles binarios de búsqueda frente a estructuras como heaps. 
Un heap permite recuperar prioridades extremas, pero no está diseñado para responder eficientemente consultas de orden como "menor elemento mayor o igual que x".

#### 9. Inserción en BST

La inserción en un árbol binario de búsqueda reutiliza el algoritmo de búsqueda. Para insertar `x`, primero se sigue el camino que habría seguido una búsqueda de `x`. 
Si se encuentra un nodo con ese valor, la inserción puede rechazarse para mantener unicidad. Si no se encuentra, se inserta un nuevo nodo como hijo izquierdo o derecho del último nodo visitado.

Morin separa la operación en dos partes: `findLast(x)` y `addChild(p, u)`. `findLast(x)` localiza el último nodo alcanzado durante la búsqueda. 
`addChild(p, u)` conecta el nuevo nodo como hijo de `p`, respetando la comparación entre `u.x` y `p.x`. 

Esta separación es importante. `findLast` responde a la pregunta "¿dónde debería estar el valor?", mientras que `addChild` modifica la estructura. De esta forma, se separa la lógica de búsqueda de la lógica de enlace.

El invariante que debe preservarse es el siguiente:

```text
Si u.x < p.x, entonces u debe insertarse como hijo izquierdo de p.
Si u.x > p.x, entonces u debe insertarse como hijo derecho de p.
Si u.x == p.x, la inserción debe rechazarse o manejar duplicados explícitamente.
```

Después de insertar, las referencias estructurales deben quedar consistentes: el padre debe apuntar al hijo nuevo, y el hijo nuevo debe apuntar de vuelta a su padre. 
En implementaciones que almacenan altura o tamaño de subárbol, también deben actualizarse los metadatos desde el punto de inserción hacia la raíz.


#### 10. Eliminación en BST y operación `splice`

La eliminación es la operación más delicada del BST porque debe modificar la estructura sin romper la propiedad de orden. Morin divide el problema en dos escenarios: eliminar un nodo con cero o un hijo, y eliminar un nodo con dos hijos. 

Si el nodo tiene cero hijos, es una hoja: basta desconectarlo de su padre. Si tiene un solo hijo, se puede reemplazar el nodo por su hijo. 
Morin encapsula esta operación en `splice(u)`. La operación `splice` elimina estructuralmente a `u` conectando el padre de `u` con el único hijo de `u`, si existe. 

Conceptualmente:

```text
Si u tiene un único hijo s:
    el padre de u pasa a apuntar a s;
    s pasa a apuntar al padre de u.

Si u es la raíz:
    la raíz se actualiza a s.
```

Esta operación funciona porque, si `u` tiene solo un hijo, ese hijo ya ocupa una posición compatible con la propiedad BST. No hay que reorganizar dos subárboles; solo se reconecta una rama.

El caso difícil aparece cuando el nodo tiene dos hijos. En ese caso, no se puede simplemente conectar su padre con uno de sus hijos, porque se perdería o desplazaría incorrectamente el otro subárbol. 
La solución de Morin consiste en buscar el sucesor inorden de `u`: el menor nodo del subárbol derecho. Ese nodo contiene el menor valor mayor que `u.x`, por lo que puede reemplazar el valor de `u` sin romper el orden. 
Luego, el sucesor se elimina con `splice`, porque el menor nodo del subárbol derecho no tiene hijo izquierdo. 

El proceso es:

```text
Si u tiene dos hijos:
    w = nodo más a la izquierda en u.right;
    copiar w.x en u.x;
    eliminar w mediante splice.
```

Técnicamente, esta estrategia preserva el invariante BST porque todo valor del subárbol izquierdo de `u` sigue siendo menor que el nuevo `u.x`, y todo valor del subárbol derecho sigue siendo mayor o igual según la política de duplicados. 
En implementaciones sin duplicados, el sucesor es estrictamente mayor que todos los valores del subárbol izquierdo y menor que los demás valores del subárbol derecho.
La implementación de `BinarySearchTree` incluye `splice` y `remove`, de modo que esta parte de Morin se usa de forma directa en la librería.


#### 11. Complejidad y dependencia de la altura

Morin subraya que las operaciones `find`, `add` y `remove` en un BST siguen un camino desde la raíz hasta algún nodo. Por ello, el costo de estas operaciones es proporcional a la altura del árbol. 

Si `h` es la altura del árbol:

```text
find(x)   = O(h)
add(x)    = O(h)
remove(x) = O(h)
```

Sin embargo, en un BST no balanceado no hay garantía de que `h = O(log n)`. Si los elementos se insertan en orden creciente, el árbol puede degenerar en una cadena:

```text
1
 \
  2
   \
    3
     \
      4
       \
        ...
```

En ese caso, la altura es `n - 1`, y las operaciones se degradan a `O(n)`. Morin resume esta situación con un teorema: un `BinarySearchTree` no balanceado soporta `add`, `remove` y `find` en tiempo `O(n)` por operación en el peor caso.

Esta conclusión es central para el curso. El BST simple permite entender la propiedad de orden y las operaciones básicas, pero también revela su principal debilidad: la falta de control sobre la altura. 
Por eso, después de estudiar BST, el curso puede avanzar hacia estructuras balanceadas como AVL o árboles rojo-negro. 


#### 12. Diferencia conceptual entre BST y heap

Aunque el documento de Morin subido desarrolla principalmente `BinaryTree` y `BinarySearchTree`, la semana 5 también incluye heaps y colas de prioridad. 
El repositorio implementa `BinaryHeap.h` como un heap binario mínimo en arreglo implícito, con operaciones `left`, `right`, `parent`, `add`, `remove`, `bubbleUp`, `trickleDown` y `heapify`. 

La distinción teórica es importante:

```text
BST:
    estructura para búsqueda ordenada,
    permite buscar valores, cotas, sucesores y predecesores,
    depende de la propiedad izquierda < nodo < derecha.

Heap:
    estructura para prioridad,
    permite acceder eficientemente al mínimo o máximo,
    depende de la propiedad padre <= hijos en un min-heap,
    no mantiene orden total inorden.
```

Un BST responde naturalmente preguntas como "¿está x?", "¿cuál es el menor elemento mayor o igual que x?" o "¿cuál es el sucesor de x?". Un heap responde naturalmente preguntas como "¿cuál es el elemento de mayor prioridad?" o "¿cuál es el mínimo actual?". 
Por eso, aunque ambas estructuras pueden visualizarse como árboles binarios, resuelven problemas abstractos distintos.

Esta diferencia coincide con el logro del curso: distinguir entre estructuras para prioridad y estructuras para búsqueda ordenada. 


### Conclusiones

El documento de Morin es esencial porque formaliza la transición desde un árbol binario básico hacia un árbol binario de búsqueda. 
Primero establece la representación enlazada con `left`, `right` y `parent`, luego muestra cómo calcular profundidad, tamaño y altura, después analiza recorridos recursivos y no recursivos y finalmente introduce la propiedad BST 
y las operaciones de búsqueda, inserción y eliminación. 

La contribución más importante de Morin es mostrar que el comportamiento de un BST depende de un invariante de orden. 
Gracias a ese invariante, la búsqueda no necesita revisar todos los nodos: en cada comparación descarta un subárbol completo. Sin embargo, Morin también deja claro que esta ventaja depende de la altura. 
Si el árbol se desbalancea, las operaciones pueden degradarse a tiempo lineal. 

La librería CC232  implementa estos conceptos de forma modular. `BinaryTree` recoge la parte estructural y navegable, `BinarySearchTree` implementa la búsqueda ordenada con operaciones como `find`, `add`, `remove` y `splice`, `BinaryHeap` cubre 
la parte de prioridad y heapify. 

En términos de estudio, Morin debe leerse con tres objetivos técnicos. Primero, comprender cómo la representación con punteros determina las operaciones posibles. 
Segundo, dominar la propiedad BST y su efecto sobre búsqueda, inserción y eliminación. 
Tercero, entender que la complejidad real de estas operaciones no depende solo del número de nodos, sino de la forma del árbol, especialmente de su altura. 
Esta última idea prepara el camino para estructuras balanceadas posteriores, como AVL.
