### Resumen final - Semana 7

#### Árboles balanceados: AVL, Red-Black Tree y control de altura

La Semana 7 continúa el recorrido iniciado en las semanas anteriores sobre estructuras jerárquicas. En la Semana 5 se introdujeron árboles binarios, recorridos, árboles binarios de búsqueda, sucesores, eliminación y rotaciones básicas. 
En la Semana 6 se estudiaron colas de prioridad, heaps, Huffman, MeldableHeap y Treap, mostrando que una estructura puede incorporar una propiedad adicional, como prioridad o aleatorización, para mejorar su comportamiento.

La Semana 7 se concentra en una pregunta central: ¿cómo evitar que un árbol binario de búsqueda se degrade en una lista? Un BST común puede tener muy buen rendimiento si su forma es equilibrada, pero puede caer a tiempo lineal si las claves llegan en un orden desfavorable. 
Las estructuras balanceadas resuelven ese problema agregando invariantes estructurales.

La idea principal es la siguiente:

1. Un BST mantiene orden por clave.
2. Un AVL mantiene, además, balance por altura.
3. Un Red-Black Tree mantiene, además, balance por colores.
4. Un ScapegoatTree mantiene altura logarítmica mediante reconstrucción parcial.
5. Todas estas estructuras conservan el recorrido inorder ordenado.
6. Las rotaciones y reconstrucciones no cambian el orden lógico de las claves.

El objetivo no es memorizar casos aislados, sino entender qué invariante se mantiene, qué operación puede romperlo, qué reparación se aplica y cuál es el costo de esa reparación.

#### 1. Problema de partida: búsqueda dinámica eficiente

Las estructuras lineales permiten almacenar colecciones, pero no siempre permiten combinar dos objetivos importantes:

| Objetivo | Estructura lineal típica | Problema |
|---|---|---|
| Buscar rápido | Vector ordenado | Insertar o eliminar puede costar `O(n)`. |
| Insertar rápido | Lista enlazada | Buscar puede costar `O(n)`. |
| Acceder por posición | Vector | La posición no equivale necesariamente a la clave. |
| Acceder por clave | Diccionario o árbol | Requiere una organización especial. |

La búsqueda por clave consiste en localizar una entrada mediante un identificador comparable. Una entrada puede verse como un par:

```text
Entry = (key, value)
```

La clave permite comparar entradas. El valor contiene la información real. Por ejemplo, en un sistema de inventario, `key` puede ser el código del producto y `value` puede contener precio, stock y descripción.

Para que un árbol binario de búsqueda funcione, las claves deben admitir comparación. En la versión más simple se asume un orden total: dadas dos claves `a`
y `b`, debe poder decidirse si `a < b`, `a == b` o `a > b`.

#### 2. Árbol binario de búsqueda

Un árbol binario de búsqueda, o BST, es un árbol binario ordenado que cumple esta propiedad:

```text
Para todo nodo r:
  toda clave del subárbol izquierdo de r es menor que r
  toda clave del subárbol derecho de r es mayor que r
```

En una variante con repetidos, la regla puede ajustarse para permitir claves iguales siempre en un lado o para almacenar multiplicidades. 
En el material de la semana se trabaja principalmente con claves distintas, porque eso simplifica las explicaciones de búsqueda, inserción, eliminación y rotación.

La propiedad BST es global, no solo local. No basta con verificar que cada hijo izquierdo sea menor que su padre y cada hijo derecho sea mayor que su padre. 
También debe cumplirse que todos los descendientes del subárbol izquierdo respeten el límite superior impuesto por el ancestro, y que todos los descendientes
del subárbol derecho respeten el límite inferior correspondiente.

Ejemplo de restricción global:

```text
        20
       /  \
     10    30
       \
        25
```

Aunque `25` es mayor que `10`, el árbol no es un BST válido porque `25` está dentro del subárbol izquierdo de `20` y debería ser menor que `20`.

#### 3. Recorrido inorder como certificado de orden

El recorrido inorder visita primero el subárbol izquierdo, luego el nodo actual y finalmente el subárbol derecho.

```text
inorder(u):
  inorder(u.left)
  visit(u)
  inorder(u.right)
```

En un BST, el recorrido inorder produce una secuencia ordenada. Esta propiedad es fundamental por tres razones:

1. Permite verificar funcionalmente que el árbol conserva el orden.
2. Permite comparar dos BST equivalentes aunque tengan forma distinta.
3. Permite entender por qué las rotaciones son operaciones válidas.

Dos BST son equivalentes si contienen las mismas claves y producen la misma secuencia inorder. Pueden tener alturas diferentes, padres diferentes y formas distintas, pero representan el mismo conjunto ordenado.

Esta idea permite resumir las rotaciones así:

```text
Una rotación cambia la forma vertical del árbol,
pero conserva el orden izquierda-derecha del inorder.
```

Por eso una rotación puede reparar altura o color sin destruir la propiedad de búsqueda.

#### 4. Búsqueda en un BST

La búsqueda en un BST usa la estrategia de reducir el espacio de búsqueda en cada comparación.

Si la clave buscada es `e` y el nodo actual contiene `x`:

| Comparación | Acción |
|---|---|
| `e == x` | La búsqueda termina con éxito. |
| `e < x` | Continuar en el subárbol izquierdo. |
| `e > x` | Continuar en el subárbol derecho. |
| Se llega a vacío | La búsqueda termina sin éxito. |

En el estilo Deng, la búsqueda devuelve una referencia a la posición donde se encontró la clave o donde debería insertarse. Además, usa `_hot` para recordar el padre del último nodo visitado. Esta convención es importante porque inserción y eliminación necesitan saber
dónde conectar o desde dónde actualizar alturas.

La idea puede verse así:

```text
search(e):
  si e existe:
    retorna la posición real del nodo con clave e
    _hot queda como su padre
  si e no existe:
    retorna la posición vacía donde debería ir e
    _hot queda como el último nodo real visitado
```

Esta semántica evita repetir trabajo. Después de una búsqueda fallida, la inserción ya sabe dónde colocar el nuevo nodo. 
Después de una búsqueda exitosa, la eliminación ya sabe qué nodo debe retirar.

#### 5. Inserción en un BST

La inserción ordinaria en un BST tiene dos fases:

1. Buscar la clave.
2. Si no existe, crear un nodo hoja en la posición vacía hallada.

El nuevo nodo siempre entra como hoja. Eso conserva la propiedad BST porque la búsqueda ya descendió por el único camino compatible con las comparaciones.

Después de insertar, se actualizan datos auxiliares como altura, tamaño o punteros. En una implementación como la de Deng, se actualiza la altura desde 
el nodo insertado o desde `_hot` hacia arriba.

```text
insert(e):
  x = search(e)
  si x existe:
    retornar x
  crear nuevo nodo con clave e
  conectar nuevo nodo como hijo de _hot
  actualizar alturas hacia la raíz
```

El costo depende de la altura `h` del árbol. Si el árbol está balanceado, `h = O(log n)`. Si el árbol se degrada, `h = O(n)`.

#### 6. Eliminación en un BST

La eliminación ordinaria en un BST distingue tres casos.

| Caso | Tratamiento |
|---|---|
| Nodo hoja | Se desconecta directamente. |
| Nodo con un hijo | El hijo reemplaza al nodo eliminado. |
| Nodo con dos hijos | Se intercambia con su sucesor inorder y luego se elimina el sucesor. |

El caso de dos hijos se reduce al caso de cero o un hijo. El sucesor inorder de un nodo con hijo derecho es el nodo más a la izquierda dentro de su subárbol 
derecho. Ese sucesor no tiene hijo izquierdo, por lo que es más fácil de retirar.

La operación `succ()` es importante porque permite localizar el sucesor inmediato en el orden inorder. La lógica general es:

```text
succ(u):
  si u tiene hijo derecho:
    ir al subárbol derecho
    bajar todo lo posible por hijos izquierdos
  si u no tiene hijo derecho:
    subir hasta encontrar un ancestro donde u esté en su lado izquierdo
```

Después de eliminar, también se actualizan alturas desde el primer ancestro afectado hacia la raíz. En el estilo Deng, esa posición queda representada por `_hot`.

#### 7. El problema de la degeneración

Un BST común no garantiza buena altura. Si se insertan claves ordenadas, el árbol puede convertirse en una cadena.

Secuencia:

```text
10, 20, 30, 40, 50, 60, 70
```

BST resultante sin balanceo:

```text
10
  \
   20
     \
      30
        \
         40
           \
            50
              \
               60
                 \
                  70
```

La altura de este árbol es `6` si la raíz tiene altura `0`. La búsqueda de `70` visita todos los nodos. En general, para `n` claves ordenadas, la 
altura puede ser `n - 1`, y búsqueda, inserción y eliminación pueden costar `O(n)`.

Este es el problema que motivan las estructuras balanceadas. No basta con conservar orden. También hay que controlar la forma.

#### 8. Balance ideal y balance moderado

Un árbol idealmente balanceado tiene altura mínima o casi mínima. Sin embargo, mantener un árbol perfectamente balanceado después de cada inserción o
eliminación puede ser demasiado costoso.

Por eso se introduce el concepto de balance moderado. Una estructura tiene balance moderado si mantiene altura `O(log n)` sin exigir una forma perfectamente completa.

Ejemplos:

| Estructura | Criterio adicional | Garantía principal |
|---|---|---|
| AVL | Altura de subárboles | Altura `O(log n)` en peor caso. |
| Red-Black Tree | Colores y altura negra | Altura a lo más `2 log n`. |
| ScapegoatTree | Reconstrucción parcial | Altura logarítmica, actualizaciones amortizadas. |
| Treap | Prioridad aleatoria | Altura esperada logarítmica. |

La Semana 7 enfatiza AVL y Red-Black Tree, pero los documentos también permiten ubicar ScapegoatTree como otra solución importante al mismo problema.

#### 9. Transformaciones equivalentes y rotaciones

Una rotación es una transformación local que modifica enlaces padre-hijo sin cambiar el orden inorder.

Rotación izquierda sobre `u`:

```text
    u                  w
     \                /
      w      pasa a  u
     /                \
    B                  B
```

Antes de rotar:

```text
A < u < B < w < C
```

Después de rotar:

```text
A < u < B < w < C
```

El orden no cambia. Lo que cambia es la profundidad relativa de los nodos. En una rotación izquierda, el hijo derecho sube y el nodo original baja hacia 
la izquierda. En una rotación derecha ocurre lo simétrico.

Las rotaciones son la herramienta básica de AVL, Treap y Red-Black Tree. Cada estructura decide cuándo rotar usando un criterio diferente:

| Estructura | Criterio para rotar |
|---|---|
| AVL | Diferencia de alturas. |
| Treap | Prioridad aleatoria. |
| Red-Black Tree | Violaciones de color y altura negra. |

#### 10. Reconstrucción 3 + 4

El método `connect34()` o reconstrucción `3 + 4` abstrae los cuatro casos de rotación AVL. La idea es tomar tres nodos relevantes y cuatro subárboles, 
ordenarlos según inorder y reensamblarlos de forma balanceada.

Si los tres nodos se renombran como:

```text
a < b < c
```

y los cuatro subárboles como:

```text
T0, T1, T2, T3
```

entonces la secuencia inorder local debe ser:

```text
T0, a, T1, b, T2, c, T3
```

La forma balanceada local es:

```text
        b
      /   \
     a     c
    / \   / \
   T0 T1 T2 T3
```

Esta reconstrucción conserva el orden BST y repara la altura local. Por eso permite implementar `rotateAt(x)` sin escribir por separado todos los casos
LL, RR, LR y RL.

#### 11. Árbol AVL

Un árbol AVL es un BST en el que cada nodo cumple una condición de balance por altura.

Para cada nodo `v`:

```text
balFac(v) = height(v.left) - height(v.right)
```

La condición AVL exige:

```text
|balFac(v)| <= 1
```

Convención de alturas usada en el material:

| Estructura | Altura |
|---|---|
| Árbol vacío | `-1` |
| Hoja | `0` |
| Nodo interno | `1 + max(height(left), height(right))` |

Un árbol AVL sigue siendo un BST. La diferencia es que además restringe la diferencia de alturas entre subárboles. 
Esto impide que el árbol se convierta en una cadena larga.

#### 12. Altura de un AVL

La razón por la que AVL funciona es que un árbol AVL de altura `h` necesita una cantidad mínima de nodos que crece como una sucesión de Fibonacci.

La intuición es esta:

```text
Para que un AVL tenga altura h con el mínimo número de nodos:
  un subárbol debe tener altura h - 1
  el otro subárbol debe tener altura h - 2
```

Si ambos fueran más pequeños, se rompería la altura `h`. Si uno fuera demasiado pequeño frente al otro, se rompería la condición AVL.

Por eso el tamaño mínimo satisface una recurrencia tipo Fibonacci. Como Fibonacci crece exponencialmente, la altura crece logarítmicamente respecto al 
número de nodos.

Conclusión:

```text
altura AVL = O(log n)
```

Por tanto:

```text
search(e) = O(log n)
insert(e) = O(log n)
remove(e) = O(log n)
```

#### 13. Inserción en AVL

La inserción en AVL empieza igual que en un BST:

1. Buscar la posición.
2. Insertar el nuevo nodo como hoja.
3. Actualizar alturas hacia la raíz.

La diferencia es que, durante la subida, se verifica si algún ancestro queda desbalanceado. El primer ancestro desbalanceado desde abajo se suele denotar 
como `g`.

Luego se identifica:

```text
g = primer nodo desbalanceado
p = hijo más alto de g
v = hijo más alto de p
```

Con `g`, `p` y `v` se determina el caso de rotación.

Después de insertar en un AVL, basta reparar el primer ancestro desbalanceado porque la rotación o reconstrucción local restaura la altura del subárbol 
afectado al valor compatible con los ancestros superiores.

#### 14. Casos de rotación AVL

Los cuatro casos clásicos son:

| Caso | Forma | Reparación |
|---|---|---|
| LL | Inserción en lado izquierdo del hijo izquierdo | Rotación derecha. |
| RR | Inserción en lado derecho del hijo derecho | Rotación izquierda. |
| LR | Inserción en lado derecho del hijo izquierdo | Rotación izquierda sobre el hijo y luego derecha sobre el abuelo. |
| RL | Inserción en lado izquierdo del hijo derecho | Rotación derecha sobre el hijo y luego izquierda sobre el abuelo. |

Caso LL:

```text
      g
     /
    p
   /
  v
```

Se corrige con rotación derecha sobre `g`.

Caso RR:

```text
  g
   \
    p
     \
      v
```

Se corrige con rotación izquierda sobre `g`.

Caso LR:

```text
      g
     /
    p
     \
      v
```

Se corrige con rotación izquierda sobre `p` y luego rotación derecha sobre `g`.

Caso RL:

```text
  g
   \
    p
   /
  v
```

Se corrige con rotación derecha sobre `p` y luego rotación izquierda sobre `g`.

La rotación simple aparece cuando el camino desde `g` hasta `v` va en la misma dirección dos veces. La rotación doble aparece cuando el camino cambia 
de dirección.

#### 15. Eliminación en AVL

La eliminación en AVL empieza igual que en BST:

1. Buscar la clave.
2. Eliminar usando los casos BST.
3. Actualizar alturas.
4. Rebalancear si aparece desequilibrio.

A diferencia de la inserción, después de eliminar puede ser necesario seguir revisando varios ancestros. La razón es que una eliminación puede disminuir 
la altura de un subárbol. Esa disminución puede propagarse hacia arriba y provocar nuevos desequilibrios.

Por eso el algoritmo de eliminación AVL sube desde `_hot` hasta la raíz. En cada nodo:

```text
si el nodo está balanceado:
  actualizar altura
si el nodo está desbalanceado:
  aplicar rotateAt(tallerChild(tallerChild(g)))
  actualizar altura del nuevo subárbol
continuar hacia la raíz
```

El número de ancestros revisados es `O(log n)`, porque la altura AVL es logarítmica. Aunque puedan aparecer varios rebalanceos, el costo total sigue siendo `O(log n)`.

#### 16. AVL como estructura estricta

AVL es más estricto que Red-Black Tree. Exige que en cada nodo la diferencia de alturas sea como máximo uno. Esta restricción suele producir árboles más bajos.

Ventaja:

```text
Búsquedas muy eficientes por menor altura.
```

Desventaja:

```text
Puede requerir más trabajo de rebalanceo durante actualizaciones, sobre todo eliminaciones.
```

Por eso AVL suele ser una buena opción cuando hay muchas búsquedas y menos modificaciones. Red-Black Tree suele preferirse en bibliotecas generales donde
inserciones y eliminaciones frecuentes también deben ser robustas y eficientes.

#### 17. ScapegoatTree

Un ScapegoatTree es un BST balanceado mediante reconstrucción parcial. A diferencia de AVL y Red-Black Tree, no repara el árbol mediante pequeñas rotaciones locales en cada actualización. 
En lugar de eso, cuando detecta que la altura excede un límite, busca un subárbol responsable y lo reconstruye completamente.

La estructura mantiene dos contadores:

| Variable | Significado |
|---|---|
| `n` | Número actual de nodos. |
| `q` | Cota superior reciente para el tamaño del árbol. |

La condición básica es:

```text
q/2 <= n <= q
```

Y la altura se controla con una cota del tipo:

```text
height <= log_{3/2}(q)
```

Cuando una inserción crea un nodo demasiado profundo, se busca un nodo scapegoat en el camino hacia la raíz.

El scapegoat es un nodo muy desbalanceado que cumple una relación como:

```text
size(child_on_path) / size(parent_region) > 2/3
```

Una vez encontrado, se reconstruye su subárbol como un BST perfectamente balanceado.

#### 18. Reconstrucción parcial en ScapegoatTree

La reconstrucción parcial tiene tres pasos:

1. Recorrer el subárbol en inorder y guardar sus nodos en un arreglo.
2. Tomar el elemento medio como nueva raíz del subárbol.
3. Reconstruir recursivamente la mitad izquierda y la mitad derecha.

Como el arreglo proviene de un recorrido inorder, queda ordenado. Por tanto, al reconstruir usando el elemento medio se conserva la propiedad BST.

Ejemplo conceptual:

```text
Arreglo inorder:
[1, 2, 3, 4, 5, 6, 7]
```

Árbol reconstruido:

```text
        4
      /   \
     2     6
    / \   / \
   1   3 5   7
```

El costo de reconstruir un subárbol de tamaño `k` es `O(k)`. Sin embargo, ese costo se paga solo ocasionalmente. Por análisis amortizado, una secuencia de 
operaciones mantiene costo total controlado.

#### 19. Inserción y eliminación en ScapegoatTree

Inserción:

```text
add(x):
  insertar como en BST
  actualizar n y q
  medir profundidad del nuevo nodo
  si la profundidad no excede log_{3/2}(q):
    terminar
  si la profundidad excede el límite:
    buscar un scapegoat hacia la raíz
    reconstruir el subárbol del scapegoat
```

Eliminación:

```text
remove(x):
  eliminar como en BST
  decrementar n
  si q > 2n:
    reconstruir todo el árbol
    fijar q = n
```

ScapegoatTree es útil para explicar balance amortizado y reconstrucción global de subárboles. Su ventaja conceptual es que no necesita almacenar altura ni color en cada nodo. 
Su costo práctico puede ser mayor que el de AVL o Red-Black Tree, porque reconstruir subárboles grandes puede ser costoso cuando ocurre.

#### 20. Árboles 2-4

Antes de estudiar Red-Black Tree conviene entender los árboles 2-4. Un árbol 2-4 es un árbol de búsqueda multicamino con estas propiedades:

1. Todas las hojas están a la misma profundidad.
2. Cada nodo interno tiene 2, 3 o 4 hijos.

Como cada nodo interno tiene al menos dos hijos, un árbol 2-4 con `n` hojas tiene altura `O(log n)`.

Las operaciones principales son:

| Operación | Problema posible | Reparación |
|---|---|---|
| Insertar hoja | Un nodo puede quedar con 5 hijos. | Dividir el nodo. |
| Eliminar hoja | Un nodo puede quedar con 1 hijo. | Pedir prestado a un hermano o fusionar. |

La división puede propagarse hacia la raíz. La fusión también puede propagarse hacia la raíz. Aun así, como la altura es logarítmica, cada operación se mantiene eficiente.

Red-Black Tree puede verse como una forma binaria de simular árboles 2-4.

#### 21. Red-Black Tree

Un Red-Black Tree es un BST donde cada nodo tiene un color: rojo o negro.

Mantiene estas propiedades:

| Propiedad | Significado |
|---|---|
| Propiedad BST | El inorder sigue ordenado. |
| Raíz negra | La raíz se conserva negra al finalizar las operaciones. |
| Nodos externos negros | Las hojas nulas se tratan como negras. |
| Sin rojo-rojo | Un nodo rojo no puede tener padre rojo. |
| Altura negra uniforme | Todo camino desde un nodo hasta una hoja nula tiene el mismo número de nodos negros. |

La altura negra es el número de nodos negros en un camino desde un nodo hasta una hoja externa. La uniformidad de altura negra impide que un lado sea demasiado más profundo que otro en términos de nodos negros. 
La regla de no rojo-rojo impide encadenar muchos nodos rojos entre dos negros.

La combinación de ambas reglas garantiza:

```text
height <= 2 log n
```

Por eso las operaciones de búsqueda, inserción y eliminación tienen costo `O(log n)` en el peor caso.

#### 22. Relación entre Red-Black Tree y árbol 2-4

La correspondencia conceptual es esta:

| Red-Black Tree | Árbol 2-4 simulado |
|---|---|
| Nodo negro sin hijos rojos | Nodo 2, una clave. |
| Nodo negro con un hijo rojo | Nodo 3, dos claves. |
| Nodo negro con dos hijos rojos | Nodo 4, tres claves. |

Los nodos rojos representan claves adicionales pegadas a un nodo negro. Cuando se contraen los nodos rojos hacia su padre negro, aparece un árbol 2-4.

La propiedad de altura negra garantiza que todas las hojas del árbol 2-4 simulado estén al mismo nivel. La regla de no rojo-rojo garantiza que un nodo
negro no acumule cadenas rojas arbitrarias.

Así se entiende la altura del Red-Black Tree:

```text
cada camino tiene O(log n) nodos negros
entre dos negros puede haber como máximo un rojo
por tanto la altura total es a lo más el doble
```

#### 23. Inserción en Red-Black Tree

La inserción empieza como en un BST: se busca la posición y se inserta una nueva hoja. La nueva hoja suele insertarse roja.

¿Por qué roja? Porque insertar un nodo rojo no cambia la altura negra de ningún camino. El problema que puede aparecer es una violación rojo-rojo si el 
padre también es rojo.

La reparación puede usar:

| Reparación | Idea |
|---|---|
| Recoloreo | Cambiar colores para simular una división en árbol 2-4. |
| Rotación | Cambiar forma local para eliminar una arista rojo-rojo. |
| `pushBlack` | Bajar negrura hacia hijos, equivalente a dividir o redistribuir. |
| `flipLeft` y `flipRight` | Corregir orientación local en variantes inclinadas a la izquierda. |

Conceptualmente, si un nodo negro tiene dos hijos rojos y se agrega otro rojo dentro de esa zona, se está simulando un nodo 2-4 que desbordó. 
El arreglo consiste en dividir ese nodo, promoviendo información hacia arriba mediante recoloreo y, si hace falta, rotaciones.

Al final, la raíz se fuerza a negro.

#### 24. Eliminación en Red-Black Tree

La eliminación es más difícil que la inserción. Al igual que en BST, se reduce a eliminar un nodo con a lo más un hijo real. Si el nodo eliminado es rojo, 
no se altera la altura negra. Si el nodo eliminado es negro, puede quedar un déficit de negro en uno de los caminos.

Ese déficit se modela como un nodo doble negro.

La reparación puede incluir:

1. Subir el doble negro hacia la raíz.
2. Tomar prestado negro de un hermano.
3. Hacer recoloreos.
4. Aplicar rotaciones.
5. Resolver casos simétricos según si el nodo es hijo izquierdo o derecho.

La implementación de Morin usa funciones de corrección como `removeFixup`, además de operaciones auxiliares como `pushBlack`, `pullBlack`, `flipLeft` y 
`flipRight`. La complejidad sigue siendo `O(log n)` porque cada iteración sube o resuelve una zona local, y la altura total del árbol es `O(log n)`.

#### 25. Variante Left-Leaning Red-Black

La carpeta de Semana 7 incluye una variante compacta llamada `RedBlackTreeLLRB.h`. LLRB significa Left-Leaning Red-Black Tree.

La idea pedagógica de esta variante es imponer una regla adicional: los enlaces rojos deben inclinarse hacia la izquierda. 
Esto simula árboles 2-3 o una versión restringida de árboles 2-4, y permite código más corto para fines didácticos.

No reemplaza necesariamente a la implementación completa, pero sirve para comparar:

| Red-Black clásico | LLRB |
|---|---|
| Más casos. | Menos casos. |
| Simula 2-4 de forma más general. | Suele simular 2-3 o 2-4 con orientación. |
| Implementación más delicada. | Mejor para demostración pedagógica. |

La Semana 7 usa ambas visiones para separar teoría completa y demostración compacta.

#### 26. Comparación entre BST, Treap, AVL, Scapegoat y Red-Black Tree

| Estructura | Propiedad de orden | Propiedad adicional | Reparación | Garantía |
|---|---|---|---|---|
| BST común | Inorder ordenado | Ninguna | No repara altura | `O(n)` en peor caso. |
| Treap | BST por clave | Heap por prioridad aleatoria | Rotaciones | `O(log n)` esperado. |
| AVL | BST por clave | Balance por altura | Rotación simple o doble | `O(log n)` peor caso. |
| ScapegoatTree | BST por clave | Cota de altura con `q` | Reconstrucción parcial | `O(log n)` amortizado en actualizaciones. |
| Red-Black Tree | BST por clave | Colores y altura negra | Recoloreo y rotaciones | `O(log n)` peor caso. |

La diferencia conceptual está en el tipo de invariante:

```text
BST: solo orden.
Treap: orden más prioridad aleatoria.
AVL: orden más altura local estricta.
Scapegoat: orden más reconstrucción por tamaño.
Red-Black: orden más restricciones de color.
```

#### 27. Comparación AVL frente a Red-Black Tree

AVL y Red-Black Tree resuelven el mismo problema general, pero con criterios distintos.

| Criterio | AVL | Red-Black Tree |
|---|---|---|
| Invariante principal | Diferencia de alturas como máximo 1. | Altura negra uniforme y sin rojo-rojo. |
| Balance | Más estricto. | Más flexible. |
| Altura típica | Menor. | Puede ser mayor, pero acotada. |
| Búsqueda | Muy eficiente. | Eficiente. |
| Inserción | Requiere rotaciones cuando rompe altura. | Requiere recoloreo y a veces rotaciones. |
| Eliminación | Puede propagar rebalanceo hacia la raíz. | Más compleja por doble negro. |
| Uso didáctico | Excelente para entender altura. | Excelente para entender invariantes indirectos. |
| Uso práctico | Bueno cuando predominan búsquedas. | Muy usado en bibliotecas generales. |

Un AVL puede ser más bajo, pero Red-Black Tree suele equilibrar bien el costo de búsqueda, inserción y eliminación.

#### 28. Correctitud funcional y correctitud estructural

En estructuras balanceadas no basta con probar que el inorder está ordenado.

Un árbol puede tener inorder correcto y aun así no ser AVL ni Red-Black Tree válido.

Ejemplo:

```text
1
 \
  2
   \
    3
     \
      4
```

El inorder es:

```text
1, 2, 3, 4
```

Eso demuestra que el árbol conserva la propiedad BST, pero no demuestra balance. Para AVL habría que verificar factores de balance. 
Para Red-Black Tree habría que verificar colores, altura negra y ausencia de rojo-rojo.

Por eso hay dos niveles de correctitud:

| Nivel | Pregunta |
|---|---|
| Correctitud funcional | ¿La estructura contiene las claves correctas y las devuelve en orden? |
| Correctitud estructural | ¿La estructura mantiene sus invariantes de balance? |

Las pruebas de Semana 7 deben validar ambas cosas.

#### 29. Invariantes que deben defenderse

Para BST:

```text
Todo nodo del subárbol izquierdo es menor que la raíz local.
Todo nodo del subárbol derecho es mayor que la raíz local.
El recorrido inorder produce claves ordenadas.
```

Para AVL:

```text
Sigue siendo BST.
Toda altura almacenada debe coincidir con la altura calculada.
Todo nodo cumple |height(left) - height(right)| <= 1.
Las rotaciones conservan inorder.
```

Para Red-Black Tree:

```text
Sigue siendo BST.
La raíz final es negra.
Las hojas nulas se consideran negras.
No hay padre rojo con hijo rojo.
Todos los caminos hacia hojas nulas tienen la misma altura negra.
```

Para ScapegoatTree:

```text
Sigue siendo BST.
El contador n representa el tamaño actual.
El contador q es una cota superior reciente.
La altura no debe exceder la cota logarítmica definida.
Las reconstrucciones conservan inorder.
```

#### 30. Evidencia esperada en los demostraciones

La carpeta de Semana 7 incluye demostraciones para observar comportamiento y validar invariantes.

| Demo | Propósito |
|---|---|
| `demo_avl_deng_core.cpp` | Inserción, eliminación, inorder y validación AVL. |
| `demo_avl_compact_rotations.cpp` | Casos LL, RR, LR y RL. |
| `demo_bst_deng_vs_avl.cpp` | Comparar degeneración BST frente a control AVL. |
| `demo_redblack_morin.cpp` | Inserción, eliminación y validación Red-Black. |
| `demo_redblack_llrb.cpp` | Variante compacta inclinada a la izquierda. |
| `demo_compare_avl_vs_redblack.cpp` | Comparar alturas y validez. |
| `demo_compare_with_semana5.cpp` | Conectar con el BST base. |
| `demo_capitulo7_panorama.cpp` | Ver la semana completa de forma panorámica. |

Una demostración sirve para observar. Una prueba automatizada sirve para verificar condiciones de forma repetible. Ambas son útiles, pero no cumplen el mismo papel.

#### 31. Pruebas de Semana 7

Las pruebas públicas e internas deben revisar más que una salida visual. Deben comprobar propiedades observables.

Pruebas mínimas recomendables:

| Prueba | Qué valida |
|---|---|
| Inorder ordenado | Propiedad BST. |
| Búsqueda exitosa | Las claves insertadas existen. |
| Búsqueda fallida | La estructura responde correctamente ante ausentes. |
| Altura AVL | El árbol no se degrada. |
| Factor de balance AVL | Todo nodo cumple la restricción. |
| Raíz negra | Invariante Red-Black final. |
| Sin rojo-rojo | No hay violaciones locales de color. |
| Altura negra uniforme | Balance Red-Black global. |

Pasar pruebas públicas no demuestra ausencia total de errores. Solo demuestra que los casos probados fueron satisfechos. Por eso se recomienda combinar pruebas públicas, pruebas internas, trazados manuales y argumentos de complejidad.

#### 32. Lectura técnica de la organización de Semana 7

La carpeta conserva dos líneas pedagógicas:

```text
Línea Deng:
  Entry.h
  BinNode.h
  BinTree.h
  BST.h
  AVL.h
```

Esta línea enfatiza `BinNode`, altura, `_hot`, `rotateAt()` y la reconstrucción `3 + 4`.

```text
Línea Morin:
  BinaryTree.h
  BinarySearchTree.h
  RedBlackTree.h
```

Esta línea enfatiza nodo centinela `nil`, `splice()`, rotaciones, colores, `addFixup()` y `removeFixup()`.

La coexistencia de ambas líneas es intencional. No se trata de duplicación accidental, sino de dos formas complementarias de enseñar árboles balanceados.

#### 33. Cierre conceptual

El paso de BST común a estructuras balanceadas cambia la naturaleza de la estructura. Ya no basta con almacenar claves en orden. Ahora cada operación debe preservar dos niveles de significado:

1. El significado de búsqueda: inorder ordenado.
2. El significado estructural: altura o color bajo control.

AVL representa el enfoque estricto: controlar directamente la altura local. Red-Black Tree representa el enfoque flexible: controlar la altura mediante colores y altura negra. ScapegoatTree representa el enfoque reconstructivo: permitir cierto desequilibrio y corregir reconstruyendo subárboles. Treap representa el enfoque probabilístico: usar prioridades aleatorias para inducir forma esperada balanceada.

La lección central de la Semana 7 es que las estructuras de datos eficientes no se justifican solo por sus operaciones, sino por sus invariantes. Un estudiante debe poder defender cada estructura respondiendo cuatro preguntas:

```text
¿Qué orden mantiene?
¿Qué invariante adicional exige?
¿Qué operación puede romperlo?
¿Qué reparación lo restaura y con qué costo?
```

Si esas cuatro preguntas se responden correctamente, entonces AVL y Red-Black Tree dejan de ser colecciones de casos y se convierten en diseños algorítmicos coherentes.
