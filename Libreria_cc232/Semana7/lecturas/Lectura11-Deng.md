### Arboles binarios de busqueda balanceados y AVL - Deng

### Resumen

Deng presenta los arboles binarios de busqueda balanceados como una respuesta al problema central de los BST convencionales: aunque `search()`, `insert()` y `remove()` siguen una logica sencilla basada en comparaciones de claves, su tiempo de ejecucion depende de la altura del arbol. Si el arbol se degenera en una cadena, esas operaciones pueden caer a `O(n)`, perdiendo la ventaja frente a estructuras lineales.

El capitulo introduce primero la necesidad de controlar la altura del arbol. Para ello compara dos formas de analizar arboles de busqueda: los arboles generados aleatoriamente por secuencias de insercion y los arboles compuestos aleatoriamente por todas las topologias posibles. Esta comparacion muestra que confiar solo en el comportamiento promedio no es suficiente, porque en aplicaciones reales las claves pueden llegar ordenadas o casi ordenadas.

A partir de esa motivacion, Deng introduce la idea de equilibrio moderado. No se exige que el arbol sea perfectamente completo, sino que su altura se mantenga asintoticamente en `O(log n)`. Bajo esta idea aparecen los arboles binarios de busqueda balanceados, entre ellos AVL, Splay, Red-Black y kd-tree. En esta lectura el foco principal es AVL.

La lectura tambien explica que dos BST son equivalentes si tienen el mismo recorrido inorder. Esta propiedad permite modificar localmente la forma del arbol sin alterar el orden de las claves. Las rotaciones `zig` y `zag` son transformaciones locales que preservan el inorder y cuestan `O(1)`. Por eso sirven como operacion basica para reparar desequilibrios.

Finalmente, Deng desarrolla los arboles AVL. Un AVL es un BST donde el factor de equilibrio de cada nodo, definido como la diferencia entre la altura del subarbol izquierdo y la altura del subarbol derecho, tiene valor absoluto a lo mas 1. Esta condicion permite mantener altura `O(log n)` y, por tanto, garantiza busqueda, insercion y eliminacion en `O(log n)`.

En la implementacion estilo Deng, `AVL` se construye sobre `BST`. La busqueda se reutiliza, mientras que `insert()` y `remove()` se reescriben para agregar rebalanceo. El mecanismo central es subir desde el punto modificado, detectar el primer nodo desequilibrado y aplicar una reestructuracion local mediante `rotateAt()` y `connect34()`, que resumen los casos de rotacion simple y doble bajo el esquema de 3 nodos y 4 subarboles.

#### Introduccion

En un arbol binario de busqueda, cada comparacion permite descender hacia el subarbol izquierdo o derecho. Esta idea generaliza la busqueda binaria de un arreglo ordenado, pero con una ventaja potencial: el conjunto puede modificarse dinamicamente mediante inserciones y eliminaciones.

El problema aparece cuando el arbol pierde forma balanceada. Si las claves se insertan en orden creciente, decreciente o con algun patron monotono, el BST puede convertirse en una estructura parecida a una lista. En ese caso, la altura pasa a ser lineal y las operaciones fundamentales dejan de ser eficientes.

Por ello, el objetivo de los arboles balanceados no es cambiar la propiedad de orden del BST, sino controlar su altura. Para lograrlo, se agregan invariantes locales y operaciones de reparacion. En AVL, el invariante se expresa mediante alturas; en Red-Black Tree, mediante colores. La lectura de Deng se concentra principalmente en la linea AVL.

Dentro de la Semana 7 de la libreria `cc232`, esta lectura se conecta con la linea:

```text
Entry.h -> BinNode.h -> BinTree.h -> BST.h -> AVL.h
```

Esta cadena permite estudiar como una estructura base de busqueda se transforma en una estructura balanceada mediante alturas, rotaciones y reestructuracion local.

#### Desarrollo

#### 1. Por que un BST comun no basta

Un BST comun tiene operaciones conceptualmente simples. Para buscar una clave, se compara con la raiz y luego se desciende a la izquierda o a la derecha. Para insertar, primero se busca la posicion donde deberia estar la clave y luego se agrega un nuevo nodo hoja. Para eliminar, se localiza el nodo y se aplican los casos clasicos: nodo hoja, nodo con un hijo o nodo con dos hijos.

El costo de todas estas operaciones depende de la altura del arbol. Si la altura es `h`, entonces `search()`, `insert()` y `remove()` cuestan `O(h)`. Cuando el arbol esta razonablemente balanceado, `h = O(log n)`. Pero cuando el arbol degenera, `h = O(n)`.

Esta observacion conduce a la idea principal del capitulo: para obtener busqueda y modificacion dinamica eficientes, no basta con mantener la propiedad de orden. Tambien es necesario imponer algun criterio de balance.

#### 2. Generacion aleatoria y composicion aleatoria

Deng distingue dos formas de pensar el comportamiento promedio de un BST.

En la generacion aleatoria, se parte de una secuencia aleatoria de inserciones. Cada permutacion de las claves produce un BST. Bajo este modelo, la altura promedio tiende a ser logaritmica.

En la composicion aleatoria, se consideran todas las posibles formas topologicas de BST que respetan el mismo conjunto de claves. Bajo este criterio, la longitud media de busqueda puede crecer como `Theta(sqrt(n))`, lo cual muestra un comportamiento menos favorable.

La diferencia es importante porque varias permutaciones pueden producir el mismo arbol. Ademas, los arboles mas balanceados pueden ser contados mas veces en el modelo de generacion aleatoria. Por ello, confiar solo en una intuicion promedio puede ocultar casos desfavorables.

En aplicaciones reales, las claves no siempre llegan en orden aleatorio. Pueden llegar ordenadas, casi ordenadas o con patrones repetidos. Por eso, una estructura robusta debe garantizar balance en el peor caso o al menos mantener una cota logaritmica despues de cada actualizacion.

#### 3. Equilibrio ideal y equilibrio moderado

El equilibrio ideal exige que el arbol tenga altura minima para su numero de nodos. Esta idea es atractiva, pero demasiado rigida para una estructura dinamica. Mantener un arbol completamente balanceado despues de cada insercion o eliminacion podria requerir cambios globales costosos.

Deng propone una idea mas util: equilibrio moderado. En lugar de exigir forma perfecta, se exige que la altura no exceda asintoticamente `O(log n)`. Este criterio permite estructuras mas flexibles, faciles de actualizar y suficientemente eficientes.

Los arboles AVL pertenecen a esta familia. No intentan ser arboles completos, pero mantienen una restriccion local sobre la diferencia de alturas entre subarboles hermanos. Esa restriccion local es suficiente para garantizar altura logaritmica.

#### 4. Transformaciones equivalentes

Dos arboles binarios de busqueda son equivalentes si tienen el mismo recorrido inorder. Esto significa que almacenan las mismas claves en el mismo orden, aunque su forma pueda ser distinta.

La idea clave es:

```text
La forma vertical puede cambiar, pero el orden izquierda-derecha no debe cambiar.
```

Esta propiedad permite reparar el balance modificando localmente enlaces entre nodos, sin violar la propiedad de busqueda. En otras palabras, se puede cambiar la topologia del arbol mientras se conserva la secuencia ordenada de claves.

Este principio es esencial para AVL. Las rotaciones no son operaciones arbitrarias: son transformaciones equivalentes que conservan el inorder y, por tanto, preservan la validez del BST.

#### 5. Rotaciones `zig` y `zag`

La rotacion `zig` corresponde a una rotacion horaria alrededor de un nodo. Se usa cuando el subarbol izquierdo tiene una forma que conviene promover. El hijo izquierdo sube y el nodo original baja hacia la derecha.

La rotacion `zag` es la operacion simetrica. Corresponde a una rotacion antihoraria. Se usa cuando el subarbol derecho debe promoverse. El hijo derecho sube y el nodo original baja hacia la izquierda.

Ambas rotaciones tienen tres propiedades importantes:

- Preservan el recorrido inorder.
- Solo modifican una region local del arbol.
- Toman tiempo `O(1)`.

Estas propiedades explican por que las rotaciones son la herramienta basica para implementar AVL y otras variantes balanceadas.

#### 6. Definicion de arbol AVL

Un arbol AVL es un BST donde cada nodo cumple una condicion de balance por altura. El factor de equilibrio se define como:

```text
balanceFactor(v) = height(left(v)) - height(right(v))
```

El invariante AVL exige:

```text
-1 <= balanceFactor(v) <= 1
```

para todo nodo `v`.

Esta condicion local impide que una rama crezca demasiado respecto de su hermana. Aunque no obliga a que el arbol sea completo, si obliga a que la altura crezca de manera logaritmica respecto al numero de nodos.

Deng justifica esta cota mediante una relacion con la sucesion de Fibonacci. Un AVL de altura `h` necesita al menos una cantidad de nodos proporcional a Fibonacci, y de esa relacion se obtiene que la altura debe ser `O(log n)`.

#### 7. La interfaz AVL sobre BST

En la linea Deng, `AVL` se define como una especializacion de `BST`. Esto significa que reutiliza la estructura general de un arbol binario de busqueda, pero redefine las operaciones que pueden cambiar la altura del arbol.

La organizacion conceptual es:

```text
BST
  search(e)
  insert(e)
  remove(e)

AVL : BST
  reutiliza search(e)
  redefine insert(e)
  redefine remove(e)
```

La busqueda no necesita cambiar porque el AVL sigue siendo un BST valido. Lo que cambia es el tratamiento posterior a la insercion o eliminacion: despues de modificar la estructura, se revisan alturas y se aplican rotaciones si aparece un nodo desequilibrado.

En el codigo de Semana 7, esta idea se refleja en `AVL.h`, que trabaja sobre `BST.h` y usa funciones auxiliares para alturas, factor de balance, hijo mas alto y rotacion unificada.

#### 8. Insercion en AVL

La insercion en AVL empieza igual que en un BST. Primero se busca la clave. Si ya existe, la operacion puede terminar. Si no existe, se crea un nuevo nodo en la posicion encontrada.

Despues de insertar el nodo, puede aumentar la altura de algunos ancestros. Por eso, el algoritmo sube desde el padre del nuevo nodo hasta la raiz, revisando el balance de cada ancestro.

El primer ancestro desequilibrado se denomina `g`. A partir de `g`, se elige el hijo mas alto `p` y luego el nieto mas alto `v`. Con esos tres nodos se decide la reestructuracion local.

En insercion AVL, basta reequilibrar el primer nodo desequilibrado. La razon es que, despues de la rotacion simple o doble, la altura del subarbol local se restaura, y por tanto los ancestros superiores tambien recuperan su balance.

El esquema general es:

```text
insertar como BST
subir desde _hot
si aparece un nodo g no balanceado:
    aplicar rotateAt(tallerChild(tallerChild(g)))
    detener el proceso
actualizar alturas en el camino
```

El costo total sigue siendo `O(log n)`: la busqueda cuesta `O(log n)`, la subida por ancestros cuesta `O(log n)` y la reestructuracion local cuesta `O(1)`.

#### 9. Eliminacion en AVL

La eliminacion tambien empieza igual que en un BST. Primero se busca la clave. Si no existe, se devuelve fracaso. Si existe, se elimina usando la logica clasica de BST.

La diferencia con la insercion es que la eliminacion puede hacer que la altura de un subarbol disminuya. Esa disminucion puede propagarse hacia arriba. Por eso, despues de eliminar un nodo, no basta necesariamente con una sola reparacion local.

El algoritmo sube desde `_hot`, revisa cada ancestro y reequilibra cuando detecta un nodo no balanceado. Despues de cada posible reestructuracion, actualiza la altura y continua hacia la raiz.

El esquema general es:

```text
eliminar como BST
subir desde _hot
para cada ancestro g:
    si g no esta balanceado:
        g = rotateAt(tallerChild(tallerChild(g)))
    actualizar altura de g
continuar hasta la raiz
```

A diferencia de la insercion, en la eliminacion pueden requerirse varios reajustes a lo largo del camino hacia la raiz. Aun asi, como solo se recorren ancestros y cada reparacion local cuesta `O(1)`, el costo total es `O(log n)`.

#### 10. Rotacion simple y rotacion doble

Deng distingue dos tipos de reparacion local.

La rotacion simple aparece cuando los nodos `g`, `p` y `v` estan alineados en la misma direccion. Esto corresponde a los casos izquierda-izquierda o derecha-derecha.

La rotacion doble aparece cuando los nodos cambian de direccion. Esto corresponde a los casos izquierda-derecha o derecha-izquierda. En esta situacion, se aplican dos rotaciones consecutivas: primero sobre el padre y luego sobre el abuelo.

Sin embargo, implementar estos casos por separado puede hacer que el codigo sea largo y propenso a errores. Por eso Deng introduce un algoritmo unificado.

#### 11. Rebalanceo unificado con 3 nodos y 4 subarboles

El rebalanceo unificado observa que todos los casos de rotacion simple y doble pueden expresarse como una reconstruccion local con:

```text
3 nodos: a, b, c
4 subarboles: T0, T1, T2, T3
```

La idea es ordenar localmente los tres nodos segun el inorder y reconectarlos asi:

```text
        b
      /   \
     a     c
    / \   / \
   T0 T1 T2 T3
```

Esta reconstruccion es precisamente el papel de `connect34()`. Luego `rotateAt(v)` identifica cual de los cuatro casos ocurre:

```text
zig-zig
zig-zag
zag-zag
zag-zig
```

y llama a `connect34()` con los argumentos adecuados.

La ventaja pedagogica y tecnica es fuerte: no necesitas memorizar cuatro bloques de codigo completamente distintos. Puede entender que todos los casos son variaciones de una misma reestructuracion local que conserva el inorder.

#### 12. Relacion con el codigo de Semana 7

Esta lectura se relaciona directamente con la parte Deng del codigo de Semana 7.

Los archivos principales son:

```text
Libreria_cc232/Semana7/include/Entry.h
Libreria_cc232/Semana7/include/BinNode.h
Libreria_cc232/Semana7/include/BinTree.h
Libreria_cc232/Semana7/include/BST.h
Libreria_cc232/Semana7/include/AVL.h
```

La correspondencia conceptual es:

- `Entry.h` representa la idea de clave y valor.
- `BinNode.h` aporta nodos con padre, hijo izquierdo, hijo derecho y altura.
- `BinTree.h` da la infraestructura general de arbol binario.
- `BST.h` implementa busqueda, insercion, eliminacion y rotaciones base.
- `AVL.h` agrega el invariante de balance por altura y el rebalanceo.

Los demostraciones mas relacionados son:

```text
sem7_demo_avl_deng_core
sem7_demo_avl_compact_rotations
sem7_demo_bst_deng_vs_avl
sem7_demo_compare_avl_vs_redblack
sem7_demo_capitulo7_panorama
```

El objetivo practico es observes que un BST comun puede degenerarse, mientras que AVL mantiene altura logaritmica mediante correcciones locales.

#### 13. Relacion con Red-Black Tree

La lectura de Deng menciona a Red-Black Tree como otro ejemplo de arbol binario de busqueda balanceado de equilibrio moderado. Sin embargo, el desarrollo detallado de esta lectura se concentra en AVL.

Por eso, para Semana 7 conviene separar las lineas de estudio:

```text
Deng -> BST, transformaciones equivalentes, rotaciones, AVL
Morin -> arboles 2-4, Red-Black Tree, colores y correcciones de color
```

Ambas estructuras buscan evitar la degeneracion lineal del BST, pero usan invariantes distintos. AVL usa alturas; Red-Black Tree usa colores. AVL suele ser mas estricto en altura, mientras que Red-Black suele tener actualizaciones con menos rotaciones en muchas implementaciones.

#### Conclusiones

La lectura muestra que el problema central de un BST comun no es la busqueda por clave, sino la falta de control sobre la altura. Si la altura crece linealmente, las operaciones principales tambien se vuelven lineales.

Deng propone resolver este problema mediante equilibrio moderado. No se exige una forma perfectamente completa, sino una altura `O(log n)`. Esta idea permite obtener estructuras dinamicas eficientes sin reconstruir todo el arbol en cada modificacion.

Las transformaciones equivalentes son la base tecnica del balanceo. Gracias a que una rotacion preserva el recorrido inorder, el arbol puede cambiar localmente su forma sin perder la propiedad de busqueda.

Los arboles AVL concretan esta idea imponiendo un factor de equilibrio en cada nodo. Si despues de insertar o eliminar una clave aparece un nodo desequilibrado, el algoritmo localiza una region de tres nodos y cuatro subarboles, y la reconstruye mediante rotaciones.

La insercion AVL requiere como maximo una reparacion local, porque la altura del subarbol modificado se restaura. La eliminacion puede requerir varias reparaciones hacia la raiz, porque la disminucion de altura puede propagarse. En ambos casos, el tiempo total sigue siendo `O(log n)`.

En la Semana 7, esta lectura sirve como base para comprender la linea Deng del codigo: `Entry`, `BinNode`, `BinTree`, `BST` y `AVL`. Tambien prepara el puente conceptual hacia Red-Black Tree, donde la misma meta: mantener altura logaritmica, se alcanza mediante reglas de color en lugar de factores de altura.
