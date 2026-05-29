### Colas de prioridad y heaps - Deng

### Resumen

Deng presenta las **colas de prioridad** como un tipo de estructura de datos orientada al acceso eficiente del elemento de mayor prioridad. 
A diferencia de un diccionario o de un árbol de búsqueda, una cola de prioridad no necesita mantener un orden total entre todos los elementos: basta con conservar 
una **relación de orden parcial** que garantice que el elemento extremo pueda identificarse y eliminarse con eficiencia. 
Esta idea permite diseñar estructuras más ligeras y adecuadas para problemas donde se selecciona repetidamente el elemento más importante, urgente, pesado, pequeño 
o grande, según el criterio definido por la aplicación.

El capítulo desarrolla primero el **ADT cola de prioridad**, cuyas operaciones principales son `insert()`, `getMax()` y `delMax()`. 
Luego estudia su implementación mediante **heaps**, en particular el **heap binario completo**, representado de forma compacta mediante un vector. 
Esta representación aprovecha la correspondencia entre un árbol binario completo y los índices de un arreglo: para un nodo en la posición `i`, sus hijos están en `2i + 1` y `2i + 2`, mientras que su padre está en `(i - 1) / 2`. Gracias a esta estructura, la operación `getMax()` cuesta `O(1)`, y las operaciones `insert()` y `delMax()` se resuelven en `O(log n)` mediante filtrado hacia arriba y filtrado hacia abajo, respectivamente.

También se explica la construcción eficiente de heaps mediante el **algoritmo de Floyd**, que transforma un vector arbitrario en un heap en tiempo `O(n)`, mejorando 
la construcción por inserciones sucesivas, que cuesta `O(n log n)`. 
A partir de esta técnica, Deng presenta la **ordenación por heap in situ** o *heapsort*, que ordena un vector en `O(n log n)` usando solo `O(1)` espacio auxiliar.

Finalmente, el capítulo introduce el **heap izquierdista** (*leftist heap*), una variante diseñada para soportar de manera eficiente la operación de **fusión** (`merge`) entre dos heaps. 
Para ello, abandona la estructura rígida del heap binario completo y utiliza un árbol binario flexible que mantiene la propiedad de heap y una propiedad adicional basada en la **longitud de camino a nodo nulo** (`npl`). 
Esta propiedad asegura que el camino más a la derecha sea corto, de longitud `O(log n)`, lo que permite fusionar heaps, insertar elementos y eliminar el máximo también
en `O(log n)`.

#### Introduccion

Las estructuras estudiadas antes de las colas de prioridad, como árboles de búsqueda, diccionarios o tablas hash, están pensadas para permitir el acceso a elementos específicos dentro de un conjunto. 
En ellas, el usuario puede buscar una clave determinada, insertar un dato concreto o eliminar un elemento identificado. 
En cambio, una cola de prioridad responde a una necesidad diferente: no interesa acceder a cualquier elemento, sino al que tiene la **mayor prioridad global**.

Esta diferencia aparece con claridad en ejemplos cotidianos. Una cola ordinaria atiende elementos según el principio FIFO: primero en entrar, primero en salir. 
Sin embargo, en un hospital no siempre conviene atender al paciente que llegó primero; si llega alguien con una emergencia grave, debe recibir atención antes que otros casos menos urgentes.
En este contexto, la prioridad no depende solo del orden de llegada, sino de un criterio externo: gravedad, urgencia, distancia, peso, costo, frecuencia, etc.

En términos algorítmicos, esta idea aparece en problemas como la ordenación por selección, donde se extrae repetidamente el máximo; en la codificación de Huffman, donde 
se seleccionan repetidamente los árboles de menor peso; y en algoritmos de barrido o de grafos, donde se procesan eventos o vértices según alguna prioridad. 
Por ello, las colas de prioridad son una estructura fundamental para transformar procesos de selección repetida en algoritmos más eficientes.

La idea central del capítulo es que una cola de prioridad no necesita mantener todos los elementos completamente ordenados. 
Mantener un orden total puede ser costoso e innecesario. Para ejecutar `getMax()` o `delMax()`, basta con saber cuál es el elemento máximo actual. 
Esta observación conduce al uso de heaps, estructuras que mantienen únicamente el orden necesario para que el elemento extremo esté siempre en una posición accesible.

#### Desarrollo

#### 1. ADT cola de prioridad

Una **cola de prioridad** es una estructura de datos que almacena entradas asociadas a un criterio de prioridad. Cada entrada posee un **código clave** (*key*) que permite compararla con otras entradas. 
A diferencia de un diccionario, donde basta con comparar igualdad entre claves, en una cola de prioridad se requiere un comparador que determine qué entrada tiene mayor prioridad.

El ADT descrito por Deng se compone principalmente de estas operaciones:

- `size()`: informa cuántas entradas hay en la cola de prioridad.
- `insert(e)`: inserta una nueva entrada.
- `getMax()`: devuelve la entrada con mayor prioridad sin eliminarla.
- `delMax()`: elimina y devuelve la entrada con mayor prioridad.

Una característica importante es que pueden existir varias entradas con la misma clave. Por ello, `insert()` no necesita fallar por duplicados: toda nueva entrada puede agregarse.

La cola de prioridad permite expresar de forma uniforme algoritmos que seleccionan repetidamente un extremo. Por ejemplo, si se insertan todos los elementos de un 
arreglo en una cola de prioridad y luego se llama varias veces a `delMax()`, los elementos salen en orden descendente. 
De este modo, una versión basada en cola de prioridad de la ordenación por selección puede mejorar el costo de `O(n^2)` a `O(n log n)`, siempre que las operaciones 
de la cola tengan costo logarítmico.

#### 2. Aplicación a la codificación de Huffman

Deng muestra que la cola de prioridad proporciona una interfaz adecuada para el algoritmo de **Huffman**. 
En este algoritmo se mantiene un bosque de árboles; en cada iteración se extraen los dos árboles de menor peso, se fusionan en un nuevo árbol y se reinserta el resultado en el bosque.

Aunque la interfaz general está orientada a `getMax()` y `delMax()`, se puede invertir la relación de comparación para que los elementos de menor peso tengan mayor prioridad. 
Así, el algoritmo de Huffman puede implementarse de manera uniforme usando la misma interfaz `PQ`.

Esta abstracción es importante porque separa el algoritmo de su implementación concreta. El mismo código de Huffman puede funcionar con una cola de prioridad basada en lista, heap binario completo o heap izquierdista. 
Si la cola de prioridad ofrece operaciones en `O(log n)`, la construcción del árbol de Huffman toma `O(n log n)`, una mejora sustancial frente a una búsqueda lineal repetida del mínimo.

#### 3. Heaps y orden parcial

La sección de heaps parte de una observación clave: las implementaciones basadas en listas o vectores ordenados suelen favorecer una operación a costa de otra. 
Por ejemplo, mantener una lista ordenada puede hacer rápido el acceso al máximo, pero encarece la inserción. 
Una lista no ordenada facilita insertar, pero hace costosa la extracción del máximo.

El problema se debe a que esas estructuras intentan mantener demasiado orden. Una cola de prioridad no requiere conocer la posición relativa exacta de todos los elementos, 
solo necesita asegurar que el máximo esté disponible. Por ello se usa un **heap**, que mantiene un orden parcial.

En un **heap de máximo**, todo nodo distinto de la raíz tiene prioridad no mayor que la de su padre. Como consecuencia, la raíz contiene siempre el elemento de mayor prioridad. 
En un **heap de mínimo**, la relación se invierte y la raíz contiene el elemento de menor prioridad. Ambos modelos son equivalentes si se invierte el comparador.

#### 4. Heap binario completo

El **heap binario completo** combina dos propiedades:

1. **Estructuralidad**: su forma lógica corresponde a un árbol binario completo.
2. **Propiedad de orden de heap**: cada nodo tiene prioridad no mayor que la de su padre, en el caso de un heap de máximo.

La estructuralidad garantiza que la altura del heap sea `O(log n)`. Esto es esencial porque las operaciones de ajuste recorren como máximo un camino desde una hoja 
hasta la raíz o desde la raíz hasta una hoja.

La implementación usa un vector. Si la raíz se almacena en la posición `0`, entonces:

```text
left(i)  = 2i + 1
right(i) = 2i + 2
parent(i) = floor((i - 1) / 2)
```

Esta representación evita almacenar punteros explícitos entre nodos, mejora la localidad de memoria y usa espacio `O(n)`. La forma del árbol queda determinada únicamente por el tamaño del vector.

#### 5. Operación `getMax()`

En un heap de máximo (max-heap), la entrada de mayor prioridad siempre está en la raíz. Como la raíz corresponde a la primera celda del vector, `getMax()` simplemente devuelve `_elem[0]`. 
Por tanto, su tiempo de ejecución es `O(1)`.

Esta operación ilustra la razón de ser del heap: aunque el conjunto no esté totalmente ordenado, el elemento más importante siempre está disponible de inmediato.

#### 6. Inserción y filtrado hacia arriba

Para insertar una entrada en un heap binario completo, primero se agrega al final del vector. Esto conserva la estructuralidad, porque el nuevo nodo ocupa la siguiente posición disponible del árbol completo. 
Sin embargo, puede violar la propiedad de heap si su prioridad es mayor que la de su padre.

Para corregirlo se aplica **filtrado hacia arriba** (*percolate up*):

1. Se compara el nuevo elemento con su padre.
2. Si el nuevo elemento tiene mayor prioridad, se intercambian.
3. El proceso se repite hasta que el elemento llegue a la raíz o su padre tenga prioridad mayor o igual.

Cada intercambio sube el elemento un nivel. Como la altura del heap es `O(log n)`, el costo de `insert()` es `O(log n)` en el peor caso. 
Deng también señala que, en distribuciones comunes, el número promedio de niveles ascendidos suele ser menor que el peor caso.

#### 7. Eliminación del máximo y filtrado hacia abajo

La operación `delMax()` elimina la raíz, que contiene el máximo. Para preservar la estructura de árbol completo, se coloca en la raíz el último elemento del vector y se reduce el tamaño del heap. 
Este reemplazo puede romper la propiedad de heap, porque el nuevo elemento de la raíz podría tener menor prioridad que alguno de sus hijos.

La corrección se realiza mediante **filtrado hacia abajo** (*percolate down*):

1. Se compara el elemento con sus hijos.
2. Si alguno de los hijos tiene mayor prioridad, se intercambia con el hijo de mayor prioridad.
3. El proceso continúa hasta que el elemento sea mayor o igual que sus hijos, o hasta llegar a una hoja.

Como cada intercambio baja un nivel y la altura es `O(log n)`, la operación `delMax()` también cuesta `O(log n)`.

#### 8. Construcción del heap y algoritmo de Floyd

Una forma simple de construir un heap a partir de `n` entradas consiste en empezar con un heap vacío e insertar los elementos uno por uno. 
Este método es correcto, pero cuesta:

```text
O(log 1 + log 2 + ... + log n) = O(n log n)
```

Deng presenta una alternativa más eficiente: el **algoritmo de Floyd**. La idea es colocar primero todos los elementos en un vector con forma de árbol binario completo 
y luego aplicar filtrado hacia abajo a cada nodo interno, recorriéndolos de abajo hacia arriba.

El algoritmo se puede resumir así:

```text
for i = LastInternal(n) down to 0:
    percolateDown(n, i)
```

La diferencia frente a la construcción por inserciones es que el costo se mide por la **altura** de los nodos y no por su profundidad. 
En un árbol binario completo hay muchos nodos cerca de las hojas, pero esos nodos tienen poca altura y requieren poco trabajo. 
Por eso, la suma total de alturas es `O(n)`. Así, Floyd construye el heap en tiempo lineal, que es óptimo porque al menos deben examinarse todos los elementos.

#### 9. Ordenación por heap

El heap binario completo permite implementar **heapsort**. La estrategia se parece a la ordenación por selección: se divide el vector en una parte no ordenada `H` y una parte ordenada `S`. 
La diferencia es que `H` se mantiene como heap, por lo que encontrar y extraer el máximo cuesta `O(log n)`.

El procedimiento general es:

1. Construir un heap sobre todo el vector.
2. Intercambiar la raíz, que contiene el máximo, con el último elemento de la zona no ordenada.
3. Reducir el tamaño lógico del heap.
4. Aplicar filtrado hacia abajo para restaurar la propiedad de heap.
5. Repetir hasta que todo el vector esté ordenado.

El algoritmo realiza `n` extracciones, cada una con costo `O(log n)`, por lo que el tiempo total es `O(n log n)`. 
Además, como trabaja dentro del mismo vector y solo necesita espacio auxiliar constante para intercambios, es un algoritmo de ordenación **in situ**, con espacio adicional `O(1)`.

#### 10. Heap izquierdista

La última parte del capítulo estudia el **heap izquierdista**. Esta estructura surge para resolver eficientemente una operación que el heap binario completo no maneja tan bien: la **fusión** de dos heaps.

Si se tienen dos heaps `A` y `B`, una solución ingenua es extraer repetidamente elementos de `B` e insertarlos en `A`, lo que puede costar `O(m log n)`. 
Otra opción es juntar todos los elementos y reconstruir un heap con Floyd, en `O(n + m)`. 
Aunque esta segunda opción es mejor, no aprovecha completamente que ambos grupos ya poseen orden parcial.

El heap izquierdista introduce una condición deliberadamente asimétrica: en lugar de buscar equilibrio, inclina la estructura hacia la izquierda para que el camino derecho sea corto. 
Esto permite que la fusión solo afecte un número logarítmico de nodos.

#### 11. Longitud de camino a nodo nulo y propiedad izquierdista

Para controlar la inclinación del heap izquierdista, Deng define la **longitud de camino a nodo nulo**, o `npl(x)`. Para un nodo externo o nulo:

```text
npl(null) = 0
```

Para un nodo interno:

```text
npl(x) = 1 + min(npl(lc(x)), npl(rc(x)))
```

La **propiedad izquierdista** exige que, para todo nodo interno `x`:

```text
npl(lc(x)) >= npl(rc(x))
```

Es decir, el hijo izquierdo debe tener un `npl` al menos tan grande como el del hijo derecho. 
Esto no significa necesariamente que el subárbol izquierdo tenga mayor altura real, sino que el camino más corto hacia un nodo nulo es mayor o igual por la izquierda.

En un heap izquierdista, el `npl` de un nodo queda determinado por su hijo derecho:

```text
npl(x) = 1 + npl(rc(x))
```

Por ello, el camino más a la derecha desde la raíz tiene longitud `O(log n)`. Esta es la propiedad que hace eficiente la fusión.

#### 12. Fusión de heaps izquierdistas

La operación `merge(a, b)` fusiona dos heaps izquierdistas. El algoritmo sigue estos pasos:

1. Si uno de los heaps está vacío, devuelve el otro.
2. Compara las raíces y asegura que la raíz de mayor prioridad quede como raíz principal.
3. Fusiona recursivamente el subheap derecho de la raíz principal con el otro heap.
4. Al regresar de la recursión, verifica la propiedad izquierdista.
5. Si el `npl` del hijo izquierdo es menor que el del derecho, intercambia ambos hijos.
6. Actualiza el `npl` del nodo.

La recursión solo avanza por los caminos más a la derecha de los heaps involucrados. Como esos caminos tienen longitud `O(log n)` y `O(log m)`, la fusión cuesta:

```text
O(log n + log m) = O(log(max(n, m)))
```

Esta eficiencia es superior a fusionar mediante extracciones e inserciones repetidas.

#### 13. Inserción y eliminación en heaps izquierdistas

Una vez que `merge()` está disponible, las operaciones principales de la cola de prioridad se simplifican.

Para insertar un elemento `x`, se crea un heap de un solo nodo y se fusiona con el heap actual:

```text
insert(x) = merge(H, {x})
```

Para eliminar el máximo, se elimina la raíz y se fusionan sus dos subheaps izquierdo y derecho:

```text
delMax() = merge(left(root), right(root))
```

Como ambas operaciones dependen de una sola llamada a `merge()`, su complejidad es `O(log n)`. La ventaja del heap izquierdista no está en mejorar
asintóticamente `insert()` o `delMax()` respecto al heap binario completo, sino en ofrecer una operación de fusión eficiente y natural.

#### Conclusiones

El capítulo muestra que las colas de prioridad son estructuras esenciales cuando un algoritmo necesita acceder repetidamente al elemento de prioridad extrema. 
Su potencia proviene de una idea simple: no es necesario mantener todos los elementos totalmente ordenados, basta con conservar un orden parcial que coloque el máximo  o
el mínimo según el comparador, en una posición accesible.

El **heap binario completo** es una implementación compacta, eficiente y práctica. Gracias a su representación vectorial, evita punteros, usa espacio `O(n)` y
ofrece `getMax()` en `O(1)`, además de `insert()` y `delMax()` en `O(log n)`. 
Sus mecanismos centrales son el filtrado hacia arriba y el filtrado hacia abajo, que restauran la propiedad de heap recorriendo solo una trayectoria de 
longitud logarítmica.

El **algoritmo de Floyd** es una mejora importante porque construye un heap en `O(n)`, aprovechando que la mayoría de los nodos de un árbol completo tienen poca altura. 
Esta construcción lineal hace posible inicializar colas de prioridad grandes de forma eficiente y sirve como base para **heapsort**, un algoritmo de ordenación 
`O(n log n)` que trabaja in situ y requiere solo espacio auxiliar constante.

El **heap izquierdista** amplía el alcance de los heaps al hacer eficiente la operación de fusión. 
En vez de buscar balance perfecto, impone una inclinación hacia la izquierda controlada por el valor `npl`, lo que garantiza que el camino derecho sea corto. 
Así, `merge()`, `insert()` y `delMax()` pueden implementarse en tiempo `O(log n)`.

En conjunto, Deng presenta las colas de prioridad como una solución elegante para problemas de selección repetida.
El capítulo destaca una lección central de diseño de estructuras de datos: reducir la información mantenida por una estructura, pasando de orden total a orden parcial, 
puede producir implementaciones más simples, rápidas y adecuadas para la operación que realmente importa.
