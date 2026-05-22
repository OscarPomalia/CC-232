### Árboles binarios según Deng

###  Resumen

Deng estudia los **árboles binarios** como una estructura de datos jerárquica capaz de representar relaciones no lineales entre elementos. A diferencia de arreglos y listas, donde existe un orden lineal natural, en un árbol el orden depende de la relación padre-hijo y de los recorridos definidos sobre la estructura. El documento desarrolla conceptos como árbol, raíz, padre, hijo, hoja, profundidad, altura, subárbol, árbol binario, representación enlazada, árboles multicamino, árboles de codificación, codificación prefija, inserción, eliminación, separación de subárboles y recorridos. 

La librería CC232 de la carpeta `Semana5` permite conectar esas ideas con código concreto. Según el README, esta carpeta contiene implementaciones de `BinNode`, `BinTree`, `BinaryTree`, `BinaryHeap` y `BinarySearchTree`; además, incluye recorridos preorden, inorden, postorden y por niveles, tanto recursivos como iterativos en varios casos.

La idea central del informe es mostrar que Deng no presenta solo teoría: muchos de sus conceptos aparecen directamente como métodos, atributos y operaciones en la librería. Por ejemplo, `BinNode` contiene `data`, `parent`, `left`, `right` y `height`; `BinTree` administra raíz, tamaño, inserción, adjunción, separación, eliminación, actualización de altura y recorridos.


### Introducción

Las estructuras lineales, como arreglos y listas enlazadas, tienen ventajas y desventajas. Un arreglo permite acceder rápidamente a un elemento mediante índice, pero insertar o eliminar puede requerir mover elementos. Una lista enlazada permite insertar y eliminar con referencias, pero localizar un elemento por posición puede requerir un recorrido lineal. Deng plantea que el árbol permite superar parte de estas limitaciones porque organiza los datos de forma jerárquica, no meramente secuencial. 

Un árbol no tiene de forma natural un sucesor o predecesor inmediato para cada nodo. Por eso puede considerarse una estructura **semilineal**: no es lineal en su forma original, pero puede transformarse en una secuencia mediante recorridos como preorden, inorden, postorden o recorrido por niveles. Esta idea es fundamental, porque en la librería CC232 los métodos de recorrido convierten el árbol enlazado en vectores de valores o permiten visitar nodos mediante funciones `visit`.

### Desarrollo

#### 1. Concepto de árbol

Desde la teoría de grafos, un árbol es un grafo **conexo y acíclico**. En informática se suele escoger un nodo especial llamado **raíz**, desde el cual se organiza el resto de la estructura. Cada nodo puede tener padre, hijos, ancestros, descendientes y subárboles. 

| Concepto     | Descripción                                                |
| ------------ | ---------------------------------------------------------- |
| Raíz         | Nodo inicial del árbol. No tiene padre.                    |
| Padre        | Nodo inmediatamente superior a otro.                       |
| Hijo         | Nodo inmediatamente inferior a otro.                       |
| Hoja         | Nodo sin hijos.                                            |
| Nodo interno | Nodo que tiene al menos un hijo.                           |
| Ancestro     | Nodo que aparece en el camino desde un nodo hacia la raíz. |
| Descendiente | Nodo contenido dentro del subárbol de otro nodo.           |
| Subárbol     | Conjunto formado por un nodo y todos sus descendientes.    |
| Profundidad  | Número de aristas desde la raíz hasta un nodo.             |
| Altura       | Máxima profundidad dentro de un árbol o subárbol.          |

Deng adopta una convención importante: un árbol con un solo nodo tiene altura `0`, mientras que un árbol vacío tiene altura `-1`. Esta convención permite escribir de forma uniforme la fórmula de altura:

```text
height(x) = 1 + max(height(left), height(right))
```

En la librería, esta convención aparece en la función auxiliar `stature`, que devuelve `-1` si el nodo es `nullptr`; de lo contrario, devuelve `node->height`.

#### 2. Árbol binario

Un **árbol binario** es un árbol en el que cada nodo tiene como máximo dos hijos. Estos hijos se distinguen como **hijo izquierdo** e **hijo derecho**. Cuando se mantiene esta distinción, se habla de árbol binario ordenado. Deng asume esta versión ordenada cuando habla de árboles binarios. 

Una representación conceptual sería:

```cpp
template <typename T>
struct BinNode {
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;
    BinNode<T>* rc;
    int height;
};
```

En el código de CC232, los nombres cambian ligeramente:

```cpp
template <typename T>
struct BinNode {
    using Node = BinNode<T>;

    T data{};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};
    int height{0};
};
```

La equivalencia es:

| Deng     | CC232    |
| -------- | -------- |
| `lc`     | `left`   |
| `rc`     | `right`  |
| `parent` | `parent` |
| `height` | `height` |
| `data`   | `data`   |

Además, `BinNode` incluye métodos para consultar el estado de un nodo: `hasLeft`, `hasRight`, `isRoot`, `isLeaf`, `isLeftChild` e `isRightChild`. Esto coincide con los predicados que Deng usa para razonar sobre la posición de un nodo dentro del árbol.

#### 3. Representación de árboles multicamino

Deng también analiza árboles donde un nodo puede tener más de dos hijos. Estos se llaman **árboles multicamino** o árboles `k`-arios. Para representarlos, se presentan varias estrategias. 

| Representación       | Ventaja                                                   | Desventaja                                                   |
| -------------------- | --------------------------------------------------------- | ------------------------------------------------------------ |
| Nodo padre           | Encontrar el padre es rápido.                             | Encontrar los hijos puede requerir recorrer todos los nodos. |
| Lista de hijos       | Enumerar hijos es eficiente.                              | Encontrar el padre no es directo si no se almacena.          |
| Padre + hijos        | Permite acceder tanto al padre como a los hijos.          | Puede ser costoso mantener listas dinámicas de hijos.        |
| Hijo mayor + hermano | Convierte un árbol ordenado multicamino en árbol binario. | Requiere interpretar los punteros con otra semántica.        |

La conversión más importante es la de **hijo mayor + hermano**. En esta técnica, el hijo izquierdo representa al primer hijo de un nodo, y el hijo derecho representa al siguiente hermano. Deng explica que, si un árbol multicamino es ordenado, puede transformarse en un árbol binario haciendo corresponder el puntero al hijo mayor con el hijo izquierdo, y el puntero al siguiente hermano con el hijo derecho. 

#### Relación con `BinNode`

Aunque la librería CC232 no implementa una clase específica para árbol multicamino, `BinNode` ayuda a entender esta conversión porque cada nodo tiene exactamente dos enlaces: `left` y `right`. En un árbol binario común se interpretan así:

```text
left  = hijo izquierdo
right = hijo derecho
```

Pero en la técnica **hijo mayor + hermano**, se reinterpretan así:

```text
left  = primer hijo
right = siguiente hermano
```

Por ejemplo, este árbol multicamino:

```text
A
├── B
│   ├── E
│   └── F
├── C
└── D
```

puede representarse como árbol binario mediante:

```text
A.left  = B
B.right = C
C.right = D

B.left  = E
E.right = F
```

Visualmente:

```text
A
└── left -> B
           ├── left  -> E
           │           └── right -> F
           └── right -> C
                       └── right -> D
```

#### Ejemplo con código CC232

```cpp
#include "Semana5/include/BinTree.h"

#include <iostream>
#include <string>

using ods::BinTree;
using ods::BinNode;

template <typename T>
void imprimirComoMulticamino(BinNode<T>* nodo, int nivel = 0) {
    if (nodo == nullptr) return;

    for (int i = 0; i < nivel; ++i) {
        std::cout << "  ";
    }

    std::cout << nodo->data << "\n";

    // Interpretación hijo mayor + hermano:
    // left  = primer hijo
    // right = siguiente hermano
    for (auto* hijo = nodo->left; hijo != nullptr; hijo = hijo->right) {
        imprimirComoMulticamino(hijo, nivel + 1);
    }
}

int main() {
    BinTree<std::string> t;

    auto* A = t.insertAsRoot("A");

    // B es el primer hijo de A.
    auto* B = t.insertAsLC(A, "B");

    // C y D son hermanos de B.
    auto* C = t.insertAsRC(B, "C");
    auto* D = t.insertAsRC(C, "D");

    // E es el primer hijo de B.
    auto* E = t.insertAsLC(B, "E");

    // F es hermano de E.
    auto* F = t.insertAsRC(E, "F");

    imprimirComoMulticamino(t.root());

    return 0;
}
```

Salida esperada:

```text
A
  B
    E
    F
  C
  D
```

Hay una advertencia técnica importante: en `BinNode`, el puntero `parent` representa el padre dentro del árbol binario transformado. En cambio, en el árbol multicamino original, `B`, `C` y `D` tendrían como padre lógico a `A`. Por eso, esta representación sirve para entender la conversión, pero si se quisiera implementar un árbol multicamino completo, habría que decidir si `parent` guarda el padre binario o el padre lógico multicamino.


#### 4. Árboles de codificación

Deng usa los árboles binarios para explicar la codificación binaria. En este modelo, cada movimiento desde la raíz representa un bit:

```text
izquierda = 0
derecha   = 1
```

Así, cada nodo queda asociado a una cadena binaria formada por el camino desde la raíz hasta ese nodo. Deng llama a esta cadena **root path string** o cadena de camino desde la raíz. Además, la longitud del código coincide con la profundidad del nodo. 

Por ejemplo, si un carácter se encuentra siguiendo el camino:

```text
derecha -> derecha -> izquierda
```

entonces su código es:

```text
110
```

Porque:

```text
derecha   = 1
derecha   = 1
izquierda = 0
```

Visualmente:

```text
        raíz
          \
           *
            \
             *
            /
           X
```

El carácter `X` está almacenado en la hoja alcanzada por el camino:

```text
right -> right -> left
```

Por eso su código es:

```text
110
```

#### Implementación con `BinTree` y `BinNode`

La librería permite construir ese árbol directamente con `insertAsRoot`, `insertAsLC` e `insertAsRC`. `BinTree` implementa la inserción de raíz y de hijos, actualizando tamaño y alturas cuando corresponde.

```cpp
#include "Semana5/include/BinTree.h"

#include <algorithm>
#include <iostream>
#include <string>

using ods::BinTree;
using ods::BinNode;

template <typename T>
std::string codigoDesdeRaiz(BinNode<T>* nodo) {
    std::string bits;

    while (nodo != nullptr && nodo->parent != nullptr) {
        if (nodo->isLeftChild()) {
            bits.push_back('0');
        } else if (nodo->isRightChild()) {
            bits.push_back('1');
        }

        nodo = nodo->parent;
    }

    std::reverse(bits.begin(), bits.end());
    return bits;
}

int main() {
    BinTree<std::string> arbol;

    // La raíz no representa un carácter.
    auto* raiz = arbol.insertAsRoot("");

    // Primer bit: 1 -> derecha
    auto* n1 = arbol.insertAsRC(raiz, "");

    // Segundo bit: 1 -> derecha
    auto* n2 = arbol.insertAsRC(n1, "");

    // Tercer bit: 0 -> izquierda
    auto* X = arbol.insertAsLC(n2, "X");

    std::cout << "Caracter: " << X->data << "\n";
    std::cout << "Codigo: " << codigoDesdeRaiz(X) << "\n";

    return 0;
}
```

Salida esperada:

```text
Caracter: X
Codigo: 110
```

La función `codigoDesdeRaiz` usa el puntero `parent`. Como se empieza desde la hoja `X` y se sube hasta la raíz, los bits se obtienen en orden inverso. Por eso se aplica `std::reverse`.


#### 5. Codificación prefija libre de ambigüedad

El problema de una mala codificación es que un código puede ser prefijo de otro. Si eso ocurre, una misma cadena de bits puede tener varias interpretaciones. Deng muestra que esto sucede cuando un carácter está ubicado en un nodo que es ancestro de otro carácter. En términos de árboles, si un carácter queda en un nodo interno, su código puede convertirse en prefijo de los códigos de sus descendientes. 

Para evitarlo se usa una **codificación prefija**, también llamada **PFC**. En una codificación prefija, ningún código es prefijo de otro. En un árbol binario, esto se logra colocando todos los caracteres únicamente en nodos hoja. 

La regla central es:

```text
Si todos los caracteres están en hojas,
entonces ningún carácter es ancestro de otro,
por lo tanto, no hay ambigüedad en la decodificación.
```

#### Ejemplo con varios caracteres

Supongamos la siguiente tabla:

| Carácter | Código |
| -------- | -----: |
| `A`      |    `0` |
| `B`      |   `10` |
| `X`      |  `110` |
| `Y`      |  `111` |

El árbol correspondiente sería:

```text
              raíz
             /    \
            A      *
                  / \
                 B   *
                    / \
                   X   Y
```

Código:

```cpp
BinTree<std::string> arbol;

auto* raiz = arbol.insertAsRoot("");

// A = 0
auto* A = arbol.insertAsLC(raiz, "A");

// Rama para códigos que empiezan con 1
auto* n1 = arbol.insertAsRC(raiz, "");

// B = 10
auto* B = arbol.insertAsLC(n1, "B");

// Rama para códigos que empiezan con 11
auto* n2 = arbol.insertAsRC(n1, "");

// X = 110
auto* X = arbol.insertAsLC(n2, "X");

// Y = 111
auto* Y = arbol.insertAsRC(n2, "Y");

std::cout << "A: " << codigoDesdeRaiz(A) << "\n";
std::cout << "B: " << codigoDesdeRaiz(B) << "\n";
std::cout << "X: " << codigoDesdeRaiz(X) << "\n";
std::cout << "Y: " << codigoDesdeRaiz(Y) << "\n";
```

Salida esperada:

```text
A: 0
B: 10
X: 110
Y: 111
```

Todos los caracteres están en hojas: `A`, `B`, `X` y `Y`. Por eso ningún código es prefijo de otro.

#### Decodificación de un mensaje

La decodificación se hace leyendo la cadena de bits de izquierda a derecha. Se parte de la raíz y, por cada bit, se baja a la izquierda o a la derecha. Al llegar a una hoja, se emite el carácter y se vuelve a la raíz. Deng señala que este procedimiento puede realizarse de forma incremental y sin retroceder si el código es prefijo-libre. 

```cpp
#include <stdexcept>

std::string decodificarMensaje(
    BinNode<std::string>* raiz,
    const std::string& bits
) {
    std::string salida;
    auto* actual = raiz;

    for (char bit : bits) {
        if (bit == '0') {
            actual = actual->left;
        } else if (bit == '1') {
            actual = actual->right;
        } else {
            throw std::invalid_argument("La cadena contiene un símbolo que no es bit");
        }

        if (actual == nullptr) {
            throw std::logic_error("El mensaje contiene un camino inexistente");
        }

        if (actual->isLeaf()) {
            salida += actual->data;
            actual = raiz;
        }
    }

    if (actual != raiz) {
        throw std::logic_error("El mensaje terminó antes de completar un carácter");
    }

    return salida;
}
```

Si el mensaje codificado es:

```text
010110111
```

se interpreta como:

```text
0 | 10 | 110 | 111
A | B  | X   | Y
```

Uso:

```cpp
std::cout << decodificarMensaje(arbol.root(), "010110111") << "\n";
```

Salida esperada:

```text
ABXY
```

#### 6. Nodo de árbol binario

El nodo binario es la unidad básica de implementación. Deng propone una clase `BinNode` que contiene datos, puntero al padre, puntero al hijo izquierdo, puntero al hijo derecho y altura. También menciona posibles campos auxiliares para estructuras posteriores. 

En CC232, `BinNode` aparece así en esencia:

```cpp
template <typename T>
struct BinNode {
    using Node = BinNode<T>;

    T data{};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};
    int height{0};

    BinNode() = default;

    explicit BinNode(const T& value, Node* p = nullptr)
        : data(value), parent(p) {}
};
```

También incluye operaciones de consulta:

```cpp
bool hasLeft() const;
bool hasRight() const;
bool isRoot() const;
bool isLeaf() const;
bool isLeftChild() const;
bool isRightChild() const;
```

Estas funciones permiten escribir algoritmos más claros. Por ejemplo, `isLeaf()` verifica si `left == nullptr && right == nullptr`; `isLeftChild()` verifica si el padre existe y si el nodo actual es el hijo izquierdo de ese padre; `isRightChild()` hace lo mismo con el hijo derecho. 

#### 7. Inserción de hijos

Deng define operaciones para insertar un nuevo nodo como hijo izquierdo o derecho. La idea es crear un nodo, establecer su padre y enlazarlo desde el nodo actual. 

Pseudocódigo conceptual:

```cpp
template <typename T>
BinNode<T>* insertAsLC(BinNode<T>* x, const T& e) {
    x->lc = new BinNode<T>(e, x);
    return x->lc;
}

template <typename T>
BinNode<T>* insertAsRC(BinNode<T>* x, const T& e) {
    x->rc = new BinNode<T>(e, x);
    return x->rc;
}
```

En CC232, `BinNode` implementa esa idea con `left` y `right`. Además, valida que no se sobrescriba un hijo ya existente. Si el hijo izquierdo o derecho ya existe, lanza una excepción.

Versión adaptada:

```cpp
Node* insertAsLC(const T& value) {
    if (left != nullptr) {
        throw std::logic_error("El hijo izquierdo ya existe");
    }

    left = new Node(value, this);
    return left;
}

Node* insertAsRC(const T& value) {
    if (right != nullptr) {
        throw std::logic_error("El hijo derecho ya existe");
    }

    right = new Node(value, this);
    return right;
}
```

Ejemplo:

```cpp
BinTree<std::string> t;

auto* A = t.insertAsRoot("A");
auto* B = t.insertAsLC(A, "B");
auto* C = t.insertAsRC(A, "C");
```

Árbol resultante:

```text
    A
   / \
  B   C
```

#### 8. Clase de árbol binario

Deng separa el nodo individual (`BinNode`) del árbol completo (`BinTree`). Esta separación es importante porque el nodo sabe quiénes son su padre e hijos, pero el árbol completo administra la raíz, el tamaño y las operaciones globales. 

Una estructura conceptual sería:

```cpp
template <typename T>
class BinTree {
protected:
    int _size;
    BinNode<T>* _root;
};
```

En CC232, `BinTree` usa:

```cpp
std::size_t size_{0};
Node* root_{nullptr};
```

y ofrece métodos como:

```cpp
size()
empty()
root()
insertAsRoot()
insertAsLC()
insertAsRC()
updateHeight()
updateHeightAbove()
attachAsLC()
attachAsRC()
removeSubtree()
secede()
travPre()
travIn()
travPost()
travLevel()
levelOrder()
```

El README de Semana5 resume precisamente que `BinTree.h` implementa un árbol binario base con inserción de raíz e hijos, actualización de altura, `attach`, `secede`, `removeSubtree` y recorridos. 


#### 9. Actualización de altura

La altura de un nodo depende de la altura de sus hijos:

```text
height(x) = 1 + max(height(left), height(right))
```

Con la convención:

```text
height(nullptr) = -1
```

una hoja queda con altura:

```text
1 + max(-1, -1) = 0
```

Deng explica que, cuando se inserta o elimina un nodo, puede cambiar la altura del nodo afectado y también la de sus ancestros. Por eso se actualiza hacia arriba usando el puntero `parent`. 

En CC232, esta lógica aparece en `updateHeight` y `updateHeightAbove`:

```cpp
int updateHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }

    node->height = 1 + std::max(stature(node->left), stature(node->right));
    return node->height;
}

void updateHeightAbove(Node* node) {
    while (node != nullptr) {
        updateHeight(node);
        node = node->parent;
    }
}
```

Cada vez que `BinTree` inserta un hijo izquierdo o derecho, aumenta el tamaño y llama a `updateHeightAbove(parent)`. 

Ejemplo:

```cpp
BinTree<int> t;

auto* A = t.insertAsRoot(10);
auto* B = t.insertAsLC(A, 5);
auto* C = t.insertAsRC(A, 20);

std::cout << A->height << "\n";
```

Después de insertar `B` y `C`, la raíz `A` tiene altura `1`, porque sus hijos son hojas de altura `0`.


#### 10. Inserción, adjunción, eliminación y separación de subárboles

Además de insertar nodos individuales, Deng presenta operaciones sobre **subárboles completos**. Estas operaciones son importantes porque una estructura arbórea puede modificarse no solo agregando o quitando un nodo, sino también moviendo o eliminando ramas completas. 

#### 10.1 Inserción de raíz

Se usa cuando el árbol está vacío o cuando se quiere reinicializar el árbol con una nueva raíz.

En CC232:

```cpp
Node* insertAsRoot(const T& value) {
    clear();
    root_ = new Node(value);
    size_ = 1;
    return root_;
}
```

La implementación limpia el árbol actual, crea un nuevo nodo raíz, actualiza el tamaño a `1` y devuelve el puntero a la raíz.

Uso:

```cpp
BinTree<std::string> t;

auto* raiz = t.insertAsRoot("A");

std::cout << raiz->data << "\n";
std::cout << t.size() << "\n";
```

Salida:

```text
A
1
```

#### 10.2 Inserción de hijos

```cpp
BinTree<std::string> t;

auto* A = t.insertAsRoot("A");
auto* B = t.insertAsLC(A, "B");
auto* C = t.insertAsRC(A, "C");
```

Representación:

```text
    A
   / \
  B   C
```

En `BinTree`, `insertAsLC` y `insertAsRC` verifican que el padre no sea `nullptr`, insertan el nodo usando el método del nodo, aumentan `size_` y actualizan alturas desde el padre hacia arriba. 

#### 10.3 Adjuntar un subárbol

Adjuntar un subárbol significa conectar un árbol completo como hijo izquierdo o derecho de un nodo existente.

En CC232:

```cpp
attachAsLC(parent, subtree)
attachAsRC(parent, subtree)
```

Estas funciones conectan la raíz del subárbol como hijo del nodo `parent`, actualizan el puntero `parent` de la raíz adjuntada, suman los tamaños, actualizan alturas y dejan vacío el árbol que fue adjuntado. 

Ejemplo:

```cpp
BinTree<std::string> principal;

auto* A = principal.insertAsRoot("A");
auto* B = principal.insertAsLC(A, "B");

BinTree<std::string> subarbol;

auto* X = subarbol.insertAsRoot("X");
subarbol.insertAsLC(X, "Y");
subarbol.insertAsRC(X, "Z");

// Adjuntar como hijo derecho de A.
auto* X_en_principal = principal.attachAsRC(A, subarbol);
```

Antes:

```text
Principal:

    A
   /
  B

Subárbol:

    X
   / \
  Y   Z
```

Después:

```text
      A
     / \
    B   X
       / \
      Y   Z
```

#### 10.4 Eliminar un subárbol

Eliminar un subárbol implica cortar el enlace desde el padre y destruir todos los nodos descendientes. En CC232, la operación es:

```cpp
removeSubtree(node)
```

La función calcula el tamaño del subárbol, corta el enlace desde el padre, pone el padre del nodo en `nullptr`, destruye recursivamente los nodos, disminuye el tamaño total y actualiza alturas desde el padre. 

auto* A = t.insertAsRoot("A");
auto* B = t.insertAsLC(A, "B");
auto* C = t.insertAsRC(A, "C");
t.insertAsLC(B, "D");
t.insertAsRC(B, "E");

std::size_t eliminados = t.removeSubtree(B);
```

Antes:

```text
      A
     / \
    B   C
   / \
  D   E
```

Después de eliminar el subárbol con raíz en `B`:

```text
A
 \
  C
```

#### 10.5 Separar un subárbol

Separar un subárbol se parece a eliminarlo, pero el subárbol no se destruye. Se corta del árbol original y se devuelve como un nuevo `BinTree`.

En CC232:

```cpp
BinTree<T> secede(Node* node)
```

`secede` crea un nuevo árbol, corta el enlace desde el padre, asigna `node` como raíz del nuevo árbol, pone `node->parent = nullptr`, ajusta tamaños y actualiza alturas en el árbol original.

Ejemplo:

```cpp
BinTree<std::string> t;

auto* A = t.insertAsRoot("A");
auto* B = t.insertAsLC(A, "B");
auto* C = t.insertAsRC(A, "C");
t.insertAsLC(B, "D");
t.insertAsRC(B, "E");

BinTree<std::string> separado = t.secede(B);
```

Árbol original después:

```text
A
 \
  C
```

Nuevo árbol separado:

```text
  B
 / \
D   E
```

Diferencia fundamental:

| Operación          | Resultado                                                            |
| ------------------ | -------------------------------------------------------------------- |
| `removeSubtree(B)` | Corta y destruye el subárbol de `B`.                                 |
| `secede(B)`        | Corta el subárbol de `B`, pero lo conserva como árbol independiente. |


#### 11. Recorridos de árboles binarios

El recorrido consiste en visitar todos los nodos una sola vez siguiendo un orden determinado. Como el árbol no tiene un orden lineal natural, los recorridos permiten convertirlo en una secuencia. Deng presenta tres recorridos principales: **preorden**, **inorden** y **postorden**. 

En CC232, estos recorridos están implementados dentro de `BinNode`, y `BinTree` los invoca desde la raíz si el árbol no está vacío.

#### 11.1 Recorrido en preorden

Orden:

```text
Nodo -> Subárbol izquierdo -> Subárbol derecho
```

También se expresa como:

```text
VLR
```

donde:

```text
V = visitar nodo
L = recorrer izquierda
R = recorrer derecha
```

Código conceptual:

```cpp
template <typename T, typename VST>
void travPre(BinNode<T>* x, VST visit) {
    if (!x) return;
    visit(x->data);
    travPre(x->lc, visit);
    travPre(x->rc, visit);
}
```

En CC232, el método equivalente es:

```cpp
template <typename Visit>
void travPre(Visit visit) {
    visit(*this);

    if (left != nullptr) {
        left->travPre(visit);
    }

    if (right != nullptr) {
        right->travPre(visit);
    }
}
```

La parte clave es:

```cpp
visit(*this);
left->travPre(visit);
right->travPre(visit);
```

Esto coincide exactamente con la regla **nodo, izquierda, derecha**. 

Ejemplo:

```text
      A
     / \
    B   C
   / \
  D   E
```

Preorden:

```text
A B D E C
```

Uso:

```cpp
BinTree<std::string> t;

auto* A = t.insertAsRoot("A");
auto* B = t.insertAsLC(A, "B");
auto* C = t.insertAsRC(A, "C");
t.insertAsLC(B, "D");
t.insertAsRC(B, "E");

t.root()->travPre([](auto& nodo) {
    std::cout << nodo.data << " ";
});
```

Salida:

```text
A B D E C
```

#### 11.2 Recorrido en inorden

Orden:

```text
Subárbol izquierdo -> Nodo -> Subárbol derecho
```

También se expresa como:

```text
LVR
```

Código conceptual:

```cpp
template <typename T, typename VST>
void travIn(BinNode<T>* x, VST visit) {
    if (!x) return;
    travIn(x->lc, visit);
    visit(x->data);
    travIn(x->rc, visit);
}
```

En CC232:

```cpp
template <typename Visit>
void travInRecursive(Visit visit) {
    if (left != nullptr) {
        left->travInRecursive(visit);
    }

    visit(*this);

    if (right != nullptr) {
        right->travInRecursive(visit);
    }
}
```

La secuencia esencial es:

```cpp
left->travInRecursive(visit);
visit(*this);
right->travInRecursive(visit);
```

Esto coincide con la regla **izquierda, nodo, derecha**. 

Ejemplo:

```text
      A
     / \
    B   C
   / \
  D   E
```

Inorden:

```text
D B E A C
```

Uso:

```cpp
t.root()->travIn([](auto& nodo) {
    std::cout << nodo.data << " ";
});
```

Salida:

```text
D B E A C
```

El recorrido inorden es especialmente importante porque permite definir una relación de **sucesor** y **predecesor** entre nodos. Esa relación aparece luego en la función `succ()` y en recorridos iterativos basados en sucesores.

#### 11.3 Recorrido en postorden

Orden:

```text
Subárbol izquierdo -> Subárbol derecho -> Nodo
```

También se expresa como:

```text
LRV
```

Código conceptual:

```cpp
template <typename T, typename VST>
void travPost(BinNode<T>* x, VST visit) {
    if (!x) return;
    travPost(x->lc, visit);
    travPost(x->rc, visit);
    visit(x->data);
}
```

En CC232:

```cpp
template <typename Visit>
void travPost(Visit visit) {
    if (left != nullptr) {
        left->travPost(visit);
    }

    if (right != nullptr) {
        right->travPost(visit);
    }

    visit(*this);
}
```

Aquí `visit(*this)` aparece al final, después de recorrer ambos subárboles. 

Ejemplo:

```text
      A
     / \
    B   C
   / \
  D   E
```

Postorden:

```text
D E B C A
```

Este recorrido es útil cuando se necesita procesar primero los descendientes y luego el nodo raíz del subárbol. Por ejemplo, destruir un árbol suele hacerse en postorden: primero se destruyen los hijos y luego el nodo padre.

#### Ejemplo completo de los tres recorridos

```cpp
#include "Semana5/include/BinTree.h"

#include <iostream>
#include <string>

using ods::BinTree;

int main() {
    BinTree<std::string> t;

    auto* A = t.insertAsRoot("A");
    auto* B = t.insertAsLC(A, "B");
    auto* C = t.insertAsRC(A, "C");
    t.insertAsLC(B, "D");
    t.insertAsRC(B, "E");

    std::cout << "Preorden: ";
    t.root()->travPre([](auto& nodo) {
        std::cout << nodo.data << " ";
    });

    std::cout << "\nInorden: ";
    t.root()->travIn([](auto& nodo) {
        std::cout << nodo.data << " ";
    });

    std::cout << "\nPostorden: ";
    t.root()->travPost([](auto& nodo) {
        std::cout << nodo.data << " ";
    });

    std::cout << "\n";

    return 0;
}
```

Salida esperada:

```text
Preorden: A B D E C
Inorden: D B E A C
Postorden: D E B C A
```

#### 12. Recorridos iterativos

Aunque los recorridos recursivos son simples, Deng también presenta versiones iterativas. Estas versiones ayudan a entender cómo funciona internamente la recursión y permiten controlar explícitamente estructuras auxiliares como pilas o colas. 

La librería CC232 implementa varias versiones: preorden iterativo, tres variantes de inorden iterativo, postorden iterativo y recorrido por niveles. El README enumera esos recorridos como parte de la carpeta Semana5. 

#### 12.1 Inorden iterativo con pila

La idea clásica consiste en bajar por la rama izquierda apilando nodos. Cuando ya no se puede bajar más, se desapila, se visita el nodo y se avanza al subárbol derecho.

Pseudocódigo:

```cpp
template <typename T, typename VST>
void travInIter(BinNode<T>* x, VST visit) {
    std::stack<BinNode<T>*> s;

    while (x || !s.empty()) {
        while (x) {
            s.push(x);
            x = x->lc;
        }

        x = s.top();
        s.pop();

        visit(x->data);
        x = x->rc;
    }
}
```

En CC232, esta idea aparece como `travInIterative1`:

```cpp
template <typename Visit>
void travInIterative1(Visit visit) {
    std::stack<Node*> st;
    Node* u = this;

    while (u != nullptr || !st.empty()) {
        while (u != nullptr) {
            st.push(u);
            u = u->left;
        }

        u = st.top();
        st.pop();

        visit(*u);
        u = u->right;
    }
}
```

Esta versión evita llamadas recursivas explícitas, pero usa una pila auxiliar cuyo tamaño depende de la altura del árbol. 

Ejemplo:

```text
      A
     / \
    B   C
   / \
  D   E
```

Inorden esperado:

```text
D B E A C
```

Uso:

```cpp
#include "Semana5/include/BinTree.h"

#include <iostream>
#include <string>

using ods::BinTree;
using ods::InorderStrategy;

int main() {
    BinTree<std::string> t;

    auto* A = t.insertAsRoot("A");
    auto* B = t.insertAsLC(A, "B");
    auto* C = t.insertAsRC(A, "C");
    t.insertAsLC(B, "D");
    t.insertAsRC(B, "E");

    t.root()->travIn(
        [](auto& nodo) {
            std::cout << nodo.data << " ";
        },
        InorderStrategy::Iterative1
    );

    return 0;
}
```

Salida:

```text
D B E A C
```

#### 12.2 Segunda variante: inorden iterativo usando `parent`

La librería también implementa `travInIterative2`. Esta versión no usa una pila explícita. En lugar de eso, mantiene dos punteros:

```text
prev = nodo desde donde venimos
curr = nodo actual
```

La idea es detectar el movimiento:

```text
Si vengo desde el padre:
    bajo a la izquierda si existe.
    si no existe, visito el nodo y voy a la derecha o regreso al padre.

Si vengo desde el hijo izquierdo:
    visito el nodo y voy a la derecha o regreso al padre.

Si vengo desde el hijo derecho:
    ya terminé ese subárbol, regreso al padre.
```

Versión adaptada:

```cpp
template <typename Visit>
void travInIterative2(Visit visit) {
    Node* prev = nullptr;
    Node* curr = this;

    while (curr != nullptr) {
        Node* next = nullptr;

        if (prev == curr->parent) {
            if (curr->left != nullptr) {
                next = curr->left;
            } else {
                visit(*curr);
                next = (curr->right != nullptr) ? curr->right : curr->parent;
            }
        } else if (prev == curr->left) {
            visit(*curr);
            next = (curr->right != nullptr) ? curr->right : curr->parent;
        } else {
            next = curr->parent;
        }

        prev = curr;
        curr = next;
    }
}
```

Esta variante muestra la utilidad del puntero `parent`: permite simular el recorrido sin pila auxiliar explícita. 

#### 12.3 Tercera variante: inorden usando `succ()`

La tercera variante, `travInIterative3`, usa el sucesor inorden. La idea es:

```text
1. Ir al nodo más a la izquierda.
2. Visitarlo.
3. Avanzar a su sucesor.
4. Repetir.
```

En CC232:

```cpp
template <typename Visit>
void travInIterative3(Visit visit) {
    Node* end = rightmost()->succ();

    for (Node* u = leftmost(); u != end; u = u->succ()) {
        visit(*u);
    }
}
```

Esta versión conecta directamente con la sección del sucesor inmediato en inorden. Una vez definido `succ()`, el árbol puede recorrerse como si fuera una lista ordenada por inorden.

#### 12.4 Comparación

| Versión      | Idea principal                                     | Usa pila |       Usa `parent` | Usa `succ()` |
| ------------ | -------------------------------------------------- | -------: | -----------------: | -----------: |
| `Iterative1` | Bajar por izquierda, apilar, visitar, ir a derecha |       Sí |  No necesariamente |           No |
| `Iterative2` | Usar `prev`, `curr` y `parent`                     |       No |                 Sí |           No |
| `Iterative3` | Empezar en `leftmost()` y avanzar con `succ()`     |       No | Sí, indirectamente |           Sí |


#### 13. Sucesor inmediato en inorden

Una vez definido el recorrido inorden, se puede hablar del **sucesor inmediato** de un nodo. El sucesor inmediato es el nodo que aparece justo después del nodo actual en la secuencia inorden. 

El recorrido inorden sigue este orden:

```text
Subárbol izquierdo -> Nodo -> Subárbol derecho
```

Por eso hay dos casos principales.

#### 13.1 Caso 1: el nodo tiene hijo derecho

Si el nodo tiene hijo derecho, su sucesor está dentro del subárbol derecho. Más específicamente, es el nodo más a la izquierda dentro de ese subárbol.

```text
succ(x) = leftmost(x->right)
```

En CC232:

```cpp
Node* succ() {
    Node* s = this;

    if (right != nullptr) {
        s = right;
        while (s->left != nullptr) {
            s = s->left;
        }
        return s;
    }

    while (s->isRightChild()) {
        s = s->parent;
    }

    return s->parent;
}
```

El primer bloque corresponde al caso con hijo derecho.

Ejemplo:

```text
      D
     / \
    B   F
       / \
      E   G
```

El sucesor de `D` es `E`, porque `D` tiene hijo derecho `F`, y el nodo más a la izquierda en el subárbol de `F` es `E`.

#### 13.2 Caso 2: el nodo no tiene hijo derecho

Si el nodo no tiene hijo derecho, su sucesor debe estar entre sus ancestros. Se sube mientras el nodo actual sea hijo derecho. Cuando se deja de subir desde una rama derecha, el padre encontrado es el sucesor.

Regla:

```text
Mientras el nodo sea hijo derecho:
    subir al padre.

Al detenerse:
    el padre es el sucesor.
```

En CC232:

```cpp
while (s->isRightChild()) {
    s = s->parent;
}

return s->parent;
```

Ejemplo:

```text
      D
     / \
    B   F
   / \
  A   C
```

Inorden:

```text
A B C D F
```

El sucesor de `C` es `D`. Como `C` no tiene hijo derecho, se sube:

```text
C es hijo derecho de B -> subir a B
B es hijo izquierdo de D -> detenerse
sucesor = D
```

#### 13.3 Ejemplo completo

```cpp
#include "Semana5/include/BinTree.h"

#include <iostream>
#include <string>

using ods::BinTree;

int main() {
    BinTree<std::string> t;

    auto* D = t.insertAsRoot("D");
    auto* B = t.insertAsLC(D, "B");
    auto* F = t.insertAsRC(D, "F");

    auto* A = t.insertAsLC(B, "A");
    auto* C = t.insertAsRC(B, "C");

    auto* E = t.insertAsLC(F, "E");
    auto* G = t.insertAsRC(F, "G");

    std::cout << "Sucesor de A: " << A->succ()->data << "\n";
    std::cout << "Sucesor de B: " << B->succ()->data << "\n";
    std::cout << "Sucesor de C: " << C->succ()->data << "\n";
    std::cout << "Sucesor de D: " << D->succ()->data << "\n";
    std::cout << "Sucesor de E: " << E->succ()->data << "\n";
    std::cout << "Sucesor de F: " << F->succ()->data << "\n";

    if (G->succ() == nullptr) {
        std::cout << "G no tiene sucesor\n";
    }

    return 0;
}
```

Árbol:

```text
        D
       / \
      B   F
     / \ / \
    A  C E  G
```

Inorden:

```text
A B C D E F G
```

Salida esperada:

```text
Sucesor de A: B
Sucesor de B: C
Sucesor de C: D
Sucesor de D: E
Sucesor de E: F
Sucesor de F: G
G no tiene sucesor
```

`succ()` es importante porque permite recorrer el árbol como una estructura lineal. Además, `travInIterative3` se apoya directamente en `leftmost()` y llamadas sucesivas a `succ()`. 


#### 14. Recorrido por niveles

El **recorrido por niveles** visita los nodos de arriba hacia abajo y de izquierda a derecha. A diferencia de preorden, inorden y postorden, este recorrido no se basa directamente en la recursión, sino en una **cola**. 

La estrategia es:

```text
1. Encolar la raíz.
2. Mientras la cola no esté vacía:
   2.1. Desencolar un nodo.
   2.2. Visitarlo.
   2.3. Encolar su hijo izquierdo si existe.
   2.4. Encolar su hijo derecho si existe.
```

Código conceptual:

```cpp
template <typename T, typename VST>
void travLevel(BinNode<T>* root, VST visit) {
    if (!root) return;

    std::queue<BinNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        BinNode<T>* x = q.front();
        q.pop();

        visit(x->data);

        if (x->lc) q.push(x->lc);
        if (x->rc) q.push(x->rc);
    }
}
```

En CC232, `BinNode` implementa `travLevel` usando `std::queue<Node*>`. Primero encola `this`, luego repite: toma el frente, lo desencola, lo visita, y encola `left` y `right` si existen. 
```cpp
template <typename Visit>
void travLevel(Visit visit) {
    std::queue<Node*> q;
    q.push(this);

    while (!q.empty()) {
        Node* u = q.front();
        q.pop();

        visit(*u);

        if (u->left != nullptr) {
            q.push(u->left);
        }

        if (u->right != nullptr) {
            q.push(u->right);
        }
    }
}
```

`BinTree` ofrece una envoltura `travLevel`, que delega en la raíz si el árbol no está vacío. También ofrece `levelOrder()`, que devuelve un vector con los valores en orden por niveles.

Ejemplo:

```cpp
#include "Semana5/include/BinTree.h"

#include <iostream>
#include <string>

using ods::BinTree;

int main() {
    BinTree<std::string> t;

    auto* A = t.insertAsRoot("A");
    auto* B = t.insertAsLC(A, "B");
    auto* C = t.insertAsRC(A, "C");
    t.insertAsLC(B, "D");
    t.insertAsRC(B, "E");

    std::cout << "Recorrido por niveles: ";

    t.travLevel([](auto& nodo) {
        std::cout << nodo.data << " ";
    });

    std::cout << "\n";

    return 0;
}
```

Árbol:

```text
      A
     / \
    B   C
   / \
  D   E
```

Salida:

```text
Recorrido por niveles: A B C D E
```

También puede usarse:

```cpp
auto valores = t.levelOrder();

for (const auto& x : valores) {
    std::cout << x << " ";
}
```

La diferencia con los otros recorridos es que preorden, inorden y postorden profundizan por subárboles, mientras que el recorrido por niveles procesa primero todos los nodos de una capa antes de pasar a la siguiente.

| Recorrido   | Estructura auxiliar típica | Orden                      |
| ----------- | -------------------------- | -------------------------- |
| Preorden    | Recursión o pila           | Nodo -> Izquierda -> Derecha |
| Inorden     | Recursión o pila           | Izquierda -> Nodo -> Derecha |
| Postorden   | Recursión o pila           | Izquierda -> Derecha -> Nodo |
| Por niveles | Cola                       | Nivel por nivel            |


### Conclusión

Deng presenta los árboles binarios como una estructura esencial para organizar datos jerárquicos. Sus conceptos centrales son raíz, padre, hijo, hoja, subárbol, profundidad, altura, representación enlazada, recorridos y sucesor inorden. La librería CC232 permite ver esos conceptos convertidos en código mediante `BinNode` y `BinTree`: los nodos almacenan dato, padre, hijo izquierdo, hijo derecho y altura; el árbol administra raíz, tamaño, inserciones, adjunciones, eliminaciones, separación de subárboles y recorridos. 

La conversión de árboles multicamino mediante **hijo mayor + hermano** muestra por qué un árbol binario puede representar estructuras más generales si se reinterpretan sus punteros. Los árboles de codificación muestran otra aplicación importante: cada camino desde la raíz hasta una hoja puede leerse como una cadena de bits, y si todos los caracteres están en hojas se obtiene una codificación prefija libre de ambigüedad. 

Finalmente, los recorridos permiten transformar el árbol en una secuencia. Preorden visita primero la raíz; inorden visita entre subárbol izquierdo y derecho; postorden deja el nodo para el final; y el recorrido por niveles procesa el árbol capa por capa usando una cola. El método `succ()` completa esta idea porque permite avanzar por la secuencia inorden nodo por nodo, como si el árbol pudiera recorrerse linealmente. En conjunto, Deng  y este informe aporta el fundamento teórico y CC232 muestra una implementación concreta, reutilizable y coherente con esa teoría.

