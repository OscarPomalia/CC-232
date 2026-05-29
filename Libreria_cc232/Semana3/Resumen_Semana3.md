### Resumen final - Semana 3

#### Listas enlazadas, listas dobles, listas por bloques y ADT de listas

La Semana 3 se concentra en estructuras lineales basadas en enlaces. En la Semana 2, las estructuras principales estaban construidas sobre arreglos: `ArrayStack`, `ArrayQueue`, `ArrayDeque`, `DualArrayDeque` y `RootishArrayStack`. En ellas, la memoria se organiza de forma contigua o casi contigua, lo que permite acceder directamente a un elemento a partir de su índice. En esta semana se cambia el punto de partida: los datos ya no tienen que estar en posiciones físicas consecutivas, sino que se almacenan en nodos conectados mediante punteros o referencias.

Este cambio modifica el balance de eficiencia. Las estructuras basadas en arreglos suelen tener acceso por índice eficiente, pero pueden requerir desplazamientos costosos al insertar o eliminar en posiciones internas. 
Las listas enlazadas, en cambio, hacen más baratas las modificaciones locales cuando ya se conoce el nodo relevante, pero hacen más costoso encontrar un elemento por índice, porque para llegar a él normalmente hay que recorrer la lista.

La idea central es que una lista representa una secuencia lógica:

```text
L = {a0, a1, a2, ..., a(n-1)}
```

El orden lógico existe aunque los nodos estén dispersos en memoria. La relación entre elementos consecutivos se mantiene mediante enlaces. En una lista simplemente enlazada cada nodo conoce a su sucesor, en una lista doblemente enlazada cada nodo conoce a su sucesor y a su predecesor, en una lista por bloques se combinan nodos enlazados con arreglos pequeños internos.

#### 1. De arreglos a listas enlazadas

En un arreglo, la posición lógica y la posición física están fuertemente relacionadas. Si se desea acceder al elemento de índice `i`, basta con calcular su dirección mediante una fórmula basada en la posición inicial del arreglo y el tamaño de cada elemento. Por eso, estructuras como `ArrayStack` o `ArrayDeque` pueden implementar `get(i)` y `set(i, x)` en tiempo constante.

En una lista enlazada, esa fórmula deja de existir. Cada nodo puede estar en cualquier lugar de memoria. Para saber dónde está el elemento de índice `i`, hay que empezar desde una posición conocida y seguir enlaces. Esto puede ser costoso, pero a cambio se gana flexibilidad: insertar o eliminar un nodo no exige mover todos los elementos posteriores, sino solo modificar punteros locales.

Deng describe este cambio como una transición del **acceso por rango** al **acceso por posición**.

- **Acceso por rango**: se usa un índice entero para localizar directamente un elemento. Es natural en vectores y arreglos.
- **Acceso por posición**: se usa una referencia o puntero a un nodo. Es natural en listas enlazadas.

El rango sigue teniendo sentido lógico en una lista, porque todavía podemos hablar del primer, segundo o i-ésimo elemento. 
Sin embargo, no es el mecanismo eficiente de acceso. El mecanismo eficiente es conservar posiciones ya obtenidas y operar localmente sobre ellas.

#### 2. Nodos y enlaces

Un nodo es la unidad básica de una lista enlazada. Como mínimo, almacena un dato y uno o más enlaces.

En una lista simplemente enlazada, un nodo puede representarse así:

```cpp
template <typename T>
struct Node {
    T x;
    Node<T>* next;
};
```

El campo `x` almacena el valor. El campo `next` apunta al siguiente nodo. El último nodo tiene `next == nullptr`.

En una lista doblemente enlazada, el nodo incluye también un enlace hacia atrás:

```cpp
template <typename T>
struct Node {
    T x;
    Node<T>* prev;
    Node<T>* next;
};
```

El campo `prev` permite llegar al nodo anterior. Esta diferencia parece pequeña, pero cambia de forma importante las operaciones posibles. En una lista simplemente enlazada, eliminar el último nodo es difícil porque no se puede retroceder desde `tail`. 
En una lista doblemente enlazada, eliminar desde ambos extremos es natural.

#### 3. SLList: lista simplemente enlazada

La primera estructura importante es `SLList` (*singly-linked list*). Es una secuencia de nodos donde cada nodo apunta únicamente al siguiente. 
La estructura mantiene tres variables principales:

```cpp
Node* head;
Node* tail;
int n;
```

- `head` apunta al primer nodo.
- `tail` apunta al último nodo.
- `n` almacena el número de elementos.

Esta estructura es muy buena para implementar pilas y colas FIFO, siempre que las operaciones se asignen a los extremos correctos.

#### 3.1 Uso como pila

Una pila usa la política **LIFO** (*last in, first out*): el último elemento que entra es el primero que sale. En una `SLList`, la cima de la pila se ubica en `head`.

La operación `push(x)` inserta al inicio:

1. Se crea un nuevo nodo `u` con dato `x`.
2. `u->next` apunta al antiguo `head`.
3. `head` se actualiza para apuntar a `u`.
4. Si la lista estaba vacía, `tail` también pasa a apuntar a `u`.
5. Se incrementa `n`.

Esta operación cuesta `O(1)` porque no depende del tamaño de la lista.

La operación `pop()` elimina desde el inicio:

1. Si la lista está vacía, no hay nada que eliminar.
2. Se guarda el dato del nodo `head`.
3. Se avanza `head` al siguiente nodo.
4. Se libera el nodo eliminado.
5. Se decrementa `n`.
6. Si la lista queda vacía, `tail` se vuelve `nullptr`.

También cuesta `O(1)`.

Por tanto, `SLList` implementa eficientemente una pila:

| Operación | Descripción | Complejidad |
|---|---|---|
| `push(x)` | Inserta en la cabecera | `O(1)` |
| `pop()` | Elimina desde la cabecera | `O(1)` |
| `top()` / `peek()` | Consulta la cabecera | `O(1)` |

#### 3.2 Uso como cola FIFO

Una cola FIFO usa la política **first in, first out**: el primer elemento que entra es el primero que sale. En una `SLList`, lo natural es insertar por `tail` y eliminar por `head`.

La operación `add(x)` inserta al final:

1. Se crea un nuevo nodo `u`.
2. Si la lista está vacía, `head = u`.
3. Si no está vacía, `tail->next = u`.
4. Se actualiza `tail = u`.
5. Se incrementa `n`.

Gracias a `tail`, no es necesario recorrer toda la lista para insertar al final. Por eso `add(x)` cuesta `O(1)`.

La operación `remove()` elimina desde el frente, igual que `pop()`. Por tanto, también cuesta `O(1)`.

| Operación | Descripción | Complejidad |
|---|---|---|
| `add(x)` | Inserta al final | `O(1)` |
| `remove()` | Elimina desde el frente | `O(1)` |
| `front()` | Consulta el frente | `O(1)` |

#### 3.3 Limitación de SLList como deque

Una `SLList` casi puede implementar un deque, pero falla en una operación esencial: eliminar desde el final.

Un deque necesita:

- insertar al inicio,
- insertar al final,
- eliminar al inicio,
- eliminar al final.

En una `SLList`, insertar al inicio, insertar al final y eliminar al inicio son operaciones constantes. El problema es `removeLast()`. Para eliminar el último nodo, hay que actualizar `tail` para que apunte al penúltimo nodo. 
Pero el último nodo no conoce a su anterior, y `tail` tampoco permite retroceder. La única forma de encontrar el penúltimo nodo es recorrer desde `head` hasta el nodo cuyo `next` sea `tail`.

Ese recorrido cuesta `O(n)`.

Esta es una conclusión importante: una estructura puede ser excelente para ciertas operaciones y deficiente para otras. `SLList` es buena para `Stack` y `Queue`, pero no para un deque completo.

#### 3.4 Operaciones adicionales en el código

El código de Semana 3 amplía `SLList` con operaciones de lista general:

- `get(i)`: obtiene el elemento de índice `i`.
- `set(i, x)`: reemplaza el elemento de índice `i`.
- `add(i, x)`: inserta en una posición.
- `removeAt(i)`: elimina en una posición.
- `reverse()`: invierte la lista.
- `secondLast()`: obtiene el penúltimo elemento.
- `checkSize()`: verifica consistencia del tamaño.
- `to_vector()`: exporta la lista a un `std::vector`.

Estas operaciones muestran el costo de usar una lista simplemente enlazada como lista por índice. Para `get(i)` y `set(i, x)`, la estructura debe recorrer desde `head` hasta el nodo i-ésimo. Por tanto, el costo es `O(i + 1)` y en el peor caso `O(n)`.

La operación `reverse()` es interesante porque sí se adapta bien a enlaces. Puede hacerse en `O(n)` sin crear una nueva lista. 
La idea es recorrer los nodos y revertir cada puntero `next`.


#### 4. DLList: lista doblemente enlazada

La segunda estructura principal es `DLList` (*doubly-linked list*). Cada nodo tiene dos enlaces:

- `prev`: apunta al nodo anterior.
- `next`: apunta al nodo siguiente.

Esto permite recorrer la lista en ambos sentidos. También permite eliminar un nodo conocido en tiempo constante, porque ya no es necesario buscar su predecesor 
desde la cabecera.

#### 4.1 Nodo centinela `dummy`

Morin presenta `DLList` usando un nodo centinela llamado `dummy`. Este nodo no almacena un dato real. Su función es simplificar los casos de frontera.

En una `DLList` circular con `dummy`:

- `dummy.next` apunta al primer nodo real.
- `dummy.prev` apunta al último nodo real.
- El último nodo apunta hacia `dummy` como sucesor.
- El primer nodo apunta hacia `dummy` como predecesor.
- Si la lista está vacía, `dummy.next = &dummy` y `dummy.prev = &dummy`.

Esta técnica evita muchos casos especiales. Sin centinela, habría que tratar por separado:

- insertar en una lista vacía,
- insertar antes del primer nodo,
- insertar después del último nodo,
- eliminar el único nodo,
- eliminar el primero,
- eliminar el último.

Con `dummy`, todos los nodos visibles tienen siempre un predecesor y un sucesor válidos.

#### 4.2 Inserción antes de un nodo

Si se tiene una referencia a un nodo `w` y se quiere insertar un nuevo nodo `u` antes de `w`, se hacen cuatro cambios:

```cpp
u->prev = w->prev;
u->next = w;
u->prev->next = u;
u->next->prev = u;
```

Después se incrementa `n`.

La operación cuesta `O(1)` si `w` ya está localizado.

#### 4.3 Eliminación de un nodo

Eliminar un nodo `w` también es local:

```cpp
w->prev->next = w->next;
w->next->prev = w->prev;
delete w;
n--;
```

La operación cuesta `O(1)` si `w` ya está localizado.

#### 4.4 Búsqueda por índice con `getNode(i)`

Para ofrecer operaciones como `get(i)`, `set(i, x)`, `add(i, x)` y `remove(i)`, la lista debe convertir un índice en un nodo. `DLList` aprovecha que puede recorrer en ambos sentidos.

Si `i < n/2`, conviene empezar desde el frente. Si `i >= n/2`, conviene empezar desde el final.

Por eso, el costo de localizar el nodo i-ésimo es:

```text
O(1 + min(i, n - i))
```

Después de localizar el nodo, leer, modificar, insertar o eliminar es constante.

| Operación | Costo |
|---|---|
| `get(i)` | `O(1 + min(i, n - i))` |
| `set(i, x)` | `O(1 + min(i, n - i))` |
| `add(i, x)` | `O(1 + min(i, n - i))` |
| `remove(i)` | `O(1 + min(i, n - i))` |
| insertar antes de un nodo conocido | `O(1)` |
| eliminar un nodo conocido | `O(1)` |

#### 4.5 Operaciones adicionales en el código

El código de `DLList.h` incluye operaciones como:

- `front()` y `back()`.
- `get(i)` y `set(i, x)`.
- `add(i, x)` y `remove(i)`.
- `clear()`.
- `to_vector()`.
- `rotate(r)`.
- `isPalindrome()`.
- `truncate(i)`.
- `checkSize()`.

Estas operaciones demuestran que una lista doblemente enlazada permite transformaciones estructurales manipulando enlaces. Por ejemplo, una rotación puede hacerse conectando y desconectando segmentos, sin mover individualmente todos los datos. `isPalindrome()` aprovecha el acceso desde ambos extremos: compara el primer nodo con el último, luego el segundo con el penúltimo, y así sucesivamente.

#### 5. Comparación entre SLList y DLList

`SLList` y `DLList` representan dos balances distintos.

`SLList` usa menos memoria por nodo porque solo guarda un enlace. Es simple y eficiente para pilas y colas FIFO. 
Sin embargo, no puede retroceder, así que algunas operaciones se vuelven costosas.

`DLList` usa más memoria por nodo porque guarda dos enlaces. A cambio, permite recorrer en ambos sentidos, eliminar nodos conocidos en
tiempo constante y operar eficientemente en ambos extremos.

| Aspecto | `SLList` | `DLList` |
|---|---|---|
| Enlaces por nodo | 1 (`next`) | 2 (`prev`, `next`) |
| Memoria por nodo | Menor | Mayor |
| Recorrido hacia adelante | Sí | Sí |
| Recorrido hacia atrás | No | Sí |
| Insertar al inicio | `O(1)` | `O(1)` |
| Insertar al final | `O(1)` con `tail` | `O(1)` |
| Eliminar al inicio | `O(1)` | `O(1)` |
| Eliminar al final | `O(n)` | `O(1)` |
| Deque completo | No ideal | Sí |
| Acceso por índice | Lineal desde la cabecera | Lineal desde el extremo más cercano |


#### 6. SEList: lista enlazada eficiente en espacio

La tercera estructura principal de Morin es `SEList` (*space-efficient list*). Su objetivo es reducir el desperdicio de espacio de una lista doblemente enlazada.

En una `DLList`, cada nodo almacena un dato, pero también dos punteros. Si los datos son pequeños, los punteros pueden ocupar una parte considerable de la memoria. `SEList` reduce ese costo agrupando varios elementos dentro de cada nodo.

En vez de tener un nodo por elemento, `SEList` tiene una lista doblemente enlazada de bloques. Cada nodo contiene un bloque, y cada bloque almacena varios elementos en una estructura llamada `BDeque`.

##### 6.1 Bloques y parámetro `b`

`SEList` se parametriza por un tamaño de bloque `b`. Cada bloque puede almacenar hasta `b + 1` elementos. Además, la estructura mantiene una regla importante:

> Excepto posiblemente el último bloque, cada bloque debe contener al menos `b - 1` elementos y como máximo `b + 1` elementos.

Esto garantiza que los bloques estén casi llenos. Si una lista contiene `n` elementos, entonces el número de bloques es aproximadamente `O(n / b)`.

La ventaja es que ya no se paga el costo de dos punteros por cada elemento, sino por cada bloque. Si cada bloque contiene alrededor de `b` elementos, el costo de enlaces se reparte entre muchos datos.

##### 6.2 BDeque

Cada bloque de `SEList` usa una `BDeque`, una versión acotada de `ArrayDeque`.

La diferencia principal es que `BDeque` tiene un arreglo de tamaño fijo `b + 1`. No crece ni se reduce. Esto es útil porque el bloque debe tener una capacidad controlada.

Las operaciones sobre un bloque permiten insertar o eliminar por el frente o por el final, lo cual facilita mover elementos entre bloques vecinos.

##### 6.3 Ubicación de elementos

Para acceder al elemento de índice `i`, `SEList` debe encontrar dos cosas:

1. El nodo `u` cuyo bloque contiene al elemento.
2. El índice interno `j` dentro de ese bloque.

Por eso se usa una estructura auxiliar como:

```cpp
struct Location {
    Node* u;
    int j;
};
```

La búsqueda puede empezar desde el frente o desde el final. Cada vez que se avanza de un nodo al siguiente, no se avanza un solo elemento, sino un bloque completo de aproximadamente `b` elementos. Por eso, ubicar un índice cuesta:

```text
O(1 + min(i, n - i) / b)
```

Luego, acceder al elemento dentro del bloque cuesta poco, porque se usa una estructura basada en arreglo.

#### 6.4 Inserción en SEList

Insertar en `SEList` es más complejo que insertar en `SLList` o `DLList`, porque hay que mantener el equilibrio de los bloques.

Para `add(x)` al final:

1. Se revisa el último bloque.
2. Si no existe o está lleno, se crea un nuevo bloque.
3. Se inserta `x` al final del bloque.
4. Se incrementa `n`.

Para `add(i, x)` en una posición interna:

1. Se localiza la posición `(u, j)`.
2. Se revisa si el bloque `u` tiene espacio.
3. Si no tiene espacio, se buscan bloques hacia adelante que puedan recibir elementos.
4. Si se encuentra un bloque con espacio, se desplazan elementos de bloque en bloque.
5. Si se llega al final, se crea un nuevo bloque.
6. Si hay `b` bloques consecutivos llenos, se llama a `spread(u)`.

#### 6.5 `spread(u)`

`spread(u)` se usa cuando hay demasiados bloques llenos consecutivos. La idea es insertar un nuevo bloque y redistribuir los elementos para que los bloques queden menos llenos.

Antes de `spread`, puede haber `b` bloques con `b + 1` elementos cada uno. Después de crear un bloque adicional, los elementos se reparten para que cada bloque tenga aproximadamente `b` elementos. Esto crea espacio para la inserción.

Una llamada a `spread` puede costar `O(b²)`, porque mueve muchos elementos. Sin embargo, no ocurre en cada inserción. Después de redistribuir, deben ocurrir muchas inserciones antes de que la misma zona vuelva a estar saturada. Por eso, el análisis se hace de forma amortizada.

#### 6.6 Eliminación en SEList

Eliminar es simétrico a insertar.

Para `remove(i)`:

1. Se localiza la posición `(u, j)`.
2. Se elimina el elemento del bloque.
3. Si el bloque queda con suficientes elementos, termina.
4. Si queda por debajo del mínimo, se intenta pedir prestado un elemento a bloques posteriores.
5. Si se llega al último bloque, puede permitirse que tenga menos elementos.
6. Si hay `b` bloques consecutivos demasiado vacíos, se llama a `gather(u)`.

#### 6.7 `gather(u)`

`gather(u)` es la operación complementaria de `spread(u)`. Se usa cuando una región de bloques está demasiado vacía. La operación reúne elementos y elimina un bloque para restaurar la condición de ocupación mínima.

También puede costar `O(b²)` en una llamada aislada, pero su costo se amortiza en una secuencia larga de operaciones.

#### 6.8 Complejidades de SEList

| Operación | Complejidad |
|---|---|
| `get(i)` | `O(1 + min(i, n - i) / b)` |
| `set(i, x)` | `O(1 + min(i, n - i) / b)` |
| `add(i, x)` | `O(b + min(i, n - i) / b)` amortizado |
| `remove(i)` | `O(b + min(i, n - i) / b)` amortizado |
| espacio desperdiciado | `O(b + n / b)` |

La elección de `b` es importante. Si `b` es pequeño, hay muchos bloques y muchos punteros. Si `b` es grande, cada bloque es más pesado de reorganizar. Un valor cercano a `√n` permite equilibrar el desperdicio de espacio `O(b + n/b)`.

#### 7. ArrayDeque como comparación contigua

Aunque la semana se centra en listas enlazadas, también aparece `ArrayDeque`. Esta estructura usa un arreglo circular con dos variables principales:

```cpp
int j; // inicio lógico
int n; // número de elementos
```

El elemento lógico `i` se encuentra físicamente en:

```cpp
(j + i) % a.length
```

Esta fórmula permite acceso rápido por índice. Para insertar o eliminar en una posición interna, `ArrayDeque` decide si conviene desplazar la parte izquierda o la derecha. Si `i < n/2`, mueve los elementos del lado izquierdo; si no, mueve los del lado derecho. Así, el costo de inserción o eliminación es:

```text
O(1 + min(i, n - i))
```

La comparación con `DLList` es útil. Ambas tienen una expresión parecida para operaciones por índice, pero el mecanismo es distinto:

- `ArrayDeque` desplaza datos dentro de un arreglo.
- `DLList` recorre punteros y luego modifica enlaces.

`ArrayDeque` suele tener mejor localidad de caché porque sus datos están en memoria contigua. `DLList` puede ser mejor cuando se tienen posiciones ya conocidas y se quiere insertar o eliminar localmente.

#### 8. Adaptadores: Stack, Queue y Deque enlazados

Una parte importante del código de Semana 3 consiste en construir ADT más simples sobre listas.

Un adaptador toma una estructura existente y expone solo las operaciones de un ADT específico. Esto mejora encapsulamiento: el usuario no necesita conocer nodos, punteros ni detalles internos.

#### 8.1 LinkedStack

`LinkedStack` se construye sobre `SLList`.

Operaciones típicas:

- `push(x)`
- `pop()`
- `top()`
- `size()`
- `empty()`
- `clear()`

La pila usa la cabecera de la lista como cima. `push` y `pop` son `O(1)`.

#### 8.2 LinkedQueue

`LinkedQueue` también se construye sobre `SLList`.

Operaciones típicas:

- `add(x)` o `enqueue(x)`
- `remove()` o `dequeue()`
- `front()`
- `size()`
- `empty()`

La cola inserta al final y elimina al inicio. Gracias a `head` y `tail`, ambas operaciones son `O(1)`.

#### 8.3 LinkedDeque

`LinkedDeque` se construye sobre `DLList`, porque un deque necesita operar en ambos extremos.

Operaciones típicas:

- `addFirst(x)`
- `addLast(x)`
- `removeFirst()`
- `removeLast()`
- `front()`
- `back()`

En una lista doblemente enlazada con centinela, estas operaciones son constantes en los extremos.


#### 9. Estructuras con mínimo: MinStack, MinQueue y MinDeque

La semana también incluye estructuras que permiten consultar el mínimo de forma eficiente.

#### 9.1 MinStack

`MinStack` almacena, junto con cada elemento, el mínimo acumulado hasta ese punto. Por ejemplo, si se insertan valores en una pila, cada nodo o entrada puede guardar:

```text
(valor, mínimo_hasta_esta_posición)
```

Así, `min()` se responde en `O(1)` mirando la cima.

Operaciones:

| Operación | Complejidad |
|---|---|
| `push(x)` | `O(1)` |
| `pop()` | `O(1)` |
| `top()` | `O(1)` |
| `min()` | `O(1)` |

#### 9.2 MinQueue

`MinQueue` puede implementarse usando dos `MinStack`:

- una pila de entrada `in_`,
- una pila de salida `out_`.

Los elementos nuevos se insertan en `in_`. Para eliminar del frente, se usa `out_`. Si `out_` está vacía, se transfieren todos los elementos de `in_` hacia `out_`. Esa transferencia invierte el orden y permite comportamiento FIFO.

El mínimo de la cola es el menor entre:

- el mínimo de `in_`,
- el mínimo de `out_`.

Aunque una transferencia individual puede costar `O(n)`, cada elemento se mueve como máximo una vez de `in_` a `out_`, por lo que el costo amortizado por operación es `O(1)`.

#### 9.3 MinDeque

`MinDeque` extiende la idea para permitir operaciones en ambos extremos. Usa dos estructuras internas para representar el lado frontal y el lado posterior. Cuando una parte se vacía y se necesita operar desde ese extremo, la estructura puede reconstruir una distribución equilibrada.

La idea pedagógica es importante: se pueden construir ADT más potentes combinando estructuras más simples. `MinDeque` no solo permite insertar y eliminar por ambos extremos, sino también consultar el mínimo.


#### 10. XorList

`XorList` es una estructura especial que busca ahorrar memoria. En una lista doblemente enlazada normal, cada nodo guarda dos punteros: `prev` y `next`. En una lista XOR, cada nodo guarda un solo campo que representa el XOR bit a bit de las direcciones de su predecesor y su sucesor.

La idea es:

```text
link = prev XOR next
```

Si durante el recorrido se conoce `prev` y se tiene `link`, se puede recuperar `next`:

```text
next = prev XOR link
```

Y si se conoce `next`, se puede recuperar `prev`:

```text
prev = next XOR link
```

La ventaja es que se ahorra un puntero por nodo. La desventaja es que el código se vuelve más delicado. Depende de manipular direcciones de memoria de bajo nivel, es más difícil de depurar y no se adapta bien a lenguajes con recolección de basura o modelos de memoria administrados.

En el código de Semana 3, `XorList` mantiene:

- `head_`,
- `tail_`,
- `n_`,
- operaciones como `push_front`, `push_back`, `pop_front`, `pop_back`, `get`, `reverse` y `to_vector`.

Una propiedad interesante es que `reverse()` puede hacerse intercambiando `head_` y `tail_`, porque los enlaces XOR no tienen una dirección explícita fija.


#### 11. Deng: ADT de lista

Deng presenta la lista desde una perspectiva de ADT. Una lista no se entiende solo como nodos conectados, sino como una estructura con operaciones bien definidas.

##### 11.1 ListNode

Un nodo de Deng contiene:

```cpp
template <typename T>
struct ListNode {
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;
};
```

Además, ofrece operaciones locales:

- `insertAsPred(e)`: inserta un nuevo nodo antes del nodo actual.
- `insertAsSucc(e)`: inserta un nuevo nodo después del nodo actual.

Estas operaciones son locales y cuestan `O(1)` si el nodo actual ya está localizado.

#### 11.2 List con centinelas `header` y `trailer`

Deng usa dos centinelas:

- `header`: antes del primer nodo real.
- `trailer`: después del último nodo real.

Al inicio:

```cpp
header->succ = trailer;
header->pred = nullptr;
trailer->pred = header;
trailer->succ = nullptr;
_size = 0;
```

Los centinelas no son visibles externamente. Su función es simplificar operaciones de frontera.

#### 11.3 Interfaz principal de List

La lista de Deng ofrece operaciones como:

#### Consulta

- `size()`
- `empty()`
- `first()`
- `last()`
- `valid(p)`
- `operator[](r)`
- `find(e)`
- `search(e)`
- `selectMax(p, n)`
- `disordered()`

#### Modificación

- `insertAsFirst(e)`
- `insertAsLast(e)`
- `insertA(p, e)`
- `insertB(p, e)`
- `remove(p)`
- `sort()`
- `deduplicate()`
- `uniquify()`
- `reverse()`
- `traverse()`

La interfaz destaca una idea clave: muchas operaciones reciben una posición `p`. Esto supone que la posición ya fue obtenida por una búsqueda previa, una operación anterior o algún proceso externo.

#### 11.4 Operador `[]`

Deng implementa `operator[](r)` para acceder por rango, pero recalca que no es eficiente en listas.

La operación empieza en el primer nodo y avanza `r` veces:

```cpp
ListNodePosi(T) p = first();
while (0 < r--) p = p->succ;
return p->data;
```

El costo es `O(r + 1)`. Esto contrasta con el acceso `O(1)` de un vector.

La conclusión es importante: aunque se pueda ofrecer acceso por índice en una lista, no debe considerarse su operación natural.

#### 11.5 Inserción y eliminación

Insertar antes de un nodo actual:

```cpp
ListNodePosi(T) x = new ListNode(e, pred, this);
pred->succ = x;
pred = x;
return x;
```

Insertar después es simétrico:

```cpp
ListNodePosi(T) x = new ListNode(e, this, succ);
succ->pred = x;
succ = x;
return x;
```

Eliminar un nodo `p`:

```cpp
T e = p->data;
p->pred->succ = p->succ;
p->succ->pred = p->pred;
delete p;
_size--;
return e;
```

Todas estas operaciones cuestan `O(1)` si la posición ya se conoce.

#### 12. Búsqueda, duplicados y ordenamiento en listas

#### 12.1 Búsqueda en lista no ordenada

En una lista no ordenada, buscar un valor requiere recorrer nodos secuencialmente. No hay acceso directo al medio, por lo que no se puede aplicar búsqueda binaria de forma eficiente.

El costo de `find(e)` es `O(n)` en el peor caso.

#### 12.2 Búsqueda en lista ordenada

En una lista ordenada, Deng define `search(e)` como una búsqueda que devuelve el nodo de mayor rango con valor menor o igual que `e`.

Aunque el orden ayuda para razonar sobre la posición del resultado, la búsqueda sigue siendo secuencial. A diferencia de un vector ordenado, una lista ordenada no permite saltar directamente al elemento central.

Por tanto, la búsqueda en lista ordenada sigue siendo `O(n)`.

#### 12.3 Eliminación de duplicados en lista no ordenada

`deduplicate()` elimina duplicados en una lista no ordenada. La estrategia típica es:

1. Recorrer la lista de izquierda a derecha.
2. Para cada nodo actual, buscar si el mismo valor apareció antes.
3. Si apareció, eliminar el duplicado.
4. Si no apareció, continuar.

Como para cada elemento puede hacerse una búsqueda previa lineal, el costo total puede ser `O(n²)`.

#### 12.4 Eliminación de duplicados en lista ordenada

`uniquify()` aprovecha que la lista está ordenada. En una lista ordenada, los duplicados quedan juntos. Por eso basta comparar nodos adyacentes.

Si dos nodos consecutivos tienen el mismo valor, se elimina uno. Si no, se avanza.

Esta operación cuesta `O(n)`.

#### 12.5 Ordenamiento

Deng discute algoritmos clásicos sobre listas:

#### Insertion sort

Procesa los nodos uno por uno e inserta cada elemento en la posición correcta dentro del prefijo ordenado. Puede ser eficiente en listas casi ordenadas, pero en el peor caso cuesta `O(n²)`.

#### Selection sort

Busca repetidamente el máximo o mínimo de un tramo y lo coloca en su posición final. También suele costar `O(n²)`.

#### Merge sort

Es especialmente adecuado para listas, porque la fusión de dos secuencias ordenadas se adapta bien a enlaces. En general, `mergeSort` ofrece costo `O(n log n)` y evita depender de acceso aleatorio.

#### 13. CleanList y DengList en el código

El código de Semana 3 implementa la parte de Deng mediante estructuras como `CleanList` y `DengList`.

#### 13.1 CleanList

`CleanList` es una lista doblemente enlazada con dos centinelas:

- `header_`,
- `trailer_`.

Mantiene además:

- `size_`,
- nodos con `pred` y `succ`,
- operaciones de inserción, eliminación, búsqueda, ordenamiento, deduplicación y recorrido.

Incluye métodos como:

- `insertFirst`
- `insertLast`
- `insert_before`
- `insert_after`
- `remove`
- `find`
- `search`
- `sort`
- `dedup`
- `uniquify`
- `reverse`
- `traverse`
- `to_vector`

Algunas operaciones pueden implementarse convirtiendo temporalmente a `std::vector`, aplicando algoritmos estándar y escribiendo los valores de vuelta. Esto no siempre reproduce la implementación más pura de una lista enlazada, pero resulta claro, seguro y fácil de probar.

#### 13.2 DengList

`DengList` funciona como una fachada o envoltorio sobre `CleanList`. Expone nombres más cercanos al uso didáctico:

- `push_front`
- `push_back`
- `add`
- `get`
- `set`
- `remove`
- `contains`
- `find_index`
- `sort`
- `dedup`
- `uniquify`
- `reverse`
- `to_vector`

La idea es separar implementación interna e interfaz externa. El usuario puede trabajar con una lista tipo Deng sin depender de los detalles de `CleanList`.

#### 14. MorinDengBridge

`MorinDengBridge` conecta las estructuras de Morin con la interfaz de Deng. Su función es convertir una estructura como `DLList` o `SEList` a una `DengList`, aplicar operaciones de Deng y reconstruir la estructura original.

Esto permite reutilizar operaciones como:

- ordenar,
- eliminar duplicados,
- invertir,
- convertir entre representaciones.

La idea importante es que varias estructuras pueden compartir la misma semántica de lista aunque tengan implementaciones internas distintas.

Por ejemplo:

- `DLList` representa una lista mediante nodos individuales con `prev` y `next`.
- `SEList` representa una lista mediante bloques enlazados.
- `DengList` representa una lista mediante una interfaz ADT más rica.

El puente permite comparar y combinar estas perspectivas.


#### 15. Capitulo3.h y organización del código

`Capitulo3.h` funciona como encabezado agregador de la semana. Reúne las estructuras principales para facilitar su uso en demostraciones, pruebas y ejercicios.

Incluye estructuras como:

- `SLList`
- `DLList`
- `SEList`
- `ArrayDeque`
- `LinkedStack`
- `LinkedQueue`
- `LinkedDeque`
- `MinStack`
- `MinQueue`
- `MinDeque`
- `XorList`

La organización permite separar el núcleo de listas enlazadas de componentes opcionales como el puente con Deng. Esto mantiene el código modular.

#### 16. Demostraciones, pruebas y benchmarks

Las demostraciones de la Semana 3 cumplen una función didáctica. No solo muestran que el código compila; también permiten observar cómo cada estructura responde a operaciones concretas.

#### 16.1 Demostraciones de estructuras base

Las demostraciones de `SLList`, `DLList` y `SEList` permiten ver:

- inserciones,
- eliminaciones,
- acceso por índice,
- conversión a vector,
- comportamiento en extremos,
- consistencia del tamaño.

#### 16.2 Demostraciones de adaptadores

Las demostraciones de `LinkedStack`, `LinkedQueue` y `LinkedDeque` muestran cómo una lista puede usarse para implementar ADT específicos.

La lección es que el usuario de una pila no necesita saber que internamente hay una `SLList`. Solo necesita que `push`, `pop` y `top` cumplan su contrato.

#### 16.3 Benchmarks

Los benchmarks ayudan a comparar estructuras enlazadas y contiguas. La conclusión esperada no es que una estructura sea siempre mejor, sino que cada una tiene un dominio de eficiencia.

Por ejemplo:

- Un arreglo puede ser mejor para recorrer datos contiguos por localidad de caché.
- Una lista puede ser mejor para eliminar un nodo si ya se tiene su posición.
- Una `SEList` puede balancear mejor espacio y acceso que una `DLList` simple.

#### 17. Resumen de complejidades

| Estructura | Operación | Complejidad |
|---|---|---|
| `SLList` | `push(x)` | `O(1)` |
| `SLList` | `pop()` | `O(1)` |
| `SLList` | `add(x)` al final | `O(1)` |
| `SLList` | `remove()` del frente | `O(1)` |
| `SLList` | `get(i)` | `O(i + 1)` |
| `SLList` | `set(i, x)` | `O(i + 1)` |
| `SLList` | eliminar último | `O(n)` |
| `DLList` | nodo conocido: insertar/eliminar | `O(1)` |
| `DLList` | `get(i)` | `O(1 + min(i, n - i))` |
| `DLList` | `set(i, x)` | `O(1 + min(i, n - i))` |
| `DLList` | `add(i, x)` | `O(1 + min(i, n - i))` |
| `DLList` | `remove(i)` | `O(1 + min(i, n - i))` |
| `SEList` | `get(i)` | `O(1 + min(i, n - i) / b)` |
| `SEList` | `set(i, x)` | `O(1 + min(i, n - i) / b)` |
| `SEList` | `add(i, x)` | `O(b + min(i, n - i) / b)` amortizado |
| `SEList` | `remove(i)` | `O(b + min(i, n - i) / b)` amortizado |
| `ArrayDeque` | acceso por índice | `O(1)` |
| `ArrayDeque` | insertar/eliminar en índice | `O(1 + min(i, n - i))` amortizado |
| `MinStack` | `min()` | `O(1)` |
| `MinQueue` | `min()` | `O(1)` amortizado |
| `XorList` | `reverse()` | `O(1)` si solo intercambia extremos |

#### 18. Comparación conceptual de estructuras

| Estructura | Representación | Ventaja principal | Desventaja principal |
|---|---|---|---|
| `SLList` | Nodos con `next` | Simple y eficiente para pila/cola | No permite retroceder |
| `DLList` | Nodos con `prev` y `next` | Inserción/eliminación local simétrica | Más memoria por nodo |
| `SEList` | Lista de bloques | Menor desperdicio de espacio | Implementación más compleja |
| `ArrayDeque` | Arreglo circular | Buena localidad y acceso por índice | Desplazamientos internos |
| `DengList` | ADT de lista con centinelas | Interfaz rica de lista | Acceso por rango lineal |
| `XorList` | Enlace XOR | Ahorra un puntero | Código delicado y menos portable |

####  19. Conclusión general

La Semana 3 introduce una forma distinta de pensar las estructuras lineales. En vez de asumir que los datos están en memoria contigua, se trabaja con nodos enlazados. Esto cambia las prioridades de diseño.

Las listas enlazadas son buenas cuando se necesitan modificaciones locales y se dispone de posiciones. Las estructuras basadas en arreglos son buenas cuando se necesita acceso rápido por índice y buena localidad de memoria. Las listas doblemente enlazadas agregan memoria para ganar simetría. Las listas por bloques agregan 
complejidad para mejorar uso de espacio. Las listas XOR reducen memoria, pero aumentan dificultad de implementación.

Morin aporta el análisis estructural y asintótico de `SLList`, `DLList` y `SEList`. Deng aporta la visión de ADT: posiciones, centinelas, operaciones locales, búsqueda, duplicados, ordenamiento y recorrido. El código de Semana 3 integra ambas perspectivas mediante implementaciones concretas, adaptadores, estructuras auxiliares,
demostraciones, pruebas y puentes entre representaciones.

La conclusión más importante es que no existe una estructura universalmente superior. Cada representación responde a un conjunto distinto de 
prioridades: acceso por índice, inserción local, eliminación local, eficiencia espacial, simplicidad de implementación o riqueza de interfaz. 
Elegir bien una estructura de datos significa entender esas prioridades y relacionarlas con las operaciones que el problema realmente necesita.

- Deng, Capítulo 3: listas, acceso por posición, ADT `ListNode`/`List`, centinelas, búsqueda, duplicados y ordenamiento.
- Código de Semana 3 del repositorio `CC-232`: implementaciones de `SLList`, `DLList`, `SEList`, adaptadores enlazados, estructuras con mínimo, `XorList`, `DengList` y `MorinDengBridge`.
