### Árboles 2-4 y Árboles Rojo-Negro - Morin

### Resumen

Esta lectura continúa la secuencia sobre árboles binarios de búsqueda balanceados. Después de estudiar árboles aleatorios, Treaps y Scapegoat Trees, Morin introduce los árboles rojo-negro como una estructura que mantiene altura logarítmica en el peor caso y que, además, realiza pocas rotaciones en promedio amortizado por actualización.

Un árbol rojo-negro es un árbol binario de búsqueda en el que cada nodo tiene un color: rojo o negro. Su eficiencia no depende de prioridades aleatorias ni de reconstrucciones parciales, sino de dos invariantes: todos los caminos desde la raíz hasta una hoja tienen el mismo número de nodos negros, y no hay dos nodos rojos adyacentes. A partir de estas dos reglas se obtiene que la altura de un árbol rojo-negro con `n` nodos es a lo más `2 log n`.

La lectura de Morin no presenta los árboles rojo-negro como una técnica aislada. Primero introduce los árboles 2-4, que son árboles con todos sus nodos hoja a la misma profundidad y cuyos nodos internos tienen grado 2, 3 o 4. Luego muestra que un árbol rojo-negro puede entenderse como una simulación binaria de un árbol 2-4. Esta correspondencia explica por qué las operaciones de inserción y eliminación pueden mantenerse eficientes mediante recoloreos y rotaciones.

### Introduccion

Un árbol binario de búsqueda ordinario puede degradarse si las claves se insertan en un orden desfavorable. Por ejemplo, insertar una secuencia ordenada puede producir una cadena, y en ese caso `find(x)`, `add(x)` y `remove(x)` pueden costar `O(n)`.

Las estructuras vistas antes resuelven este problema de diferentes maneras. Un Treap usa prioridades aleatorias y mantiene una propiedad de heap sobre esas prioridades. Un ScapegoatTree permite cierto desbalance, pero reconstruye subárboles completos cuando una ruta se vuelve demasiado profunda. Los árboles rojo-negro siguen otra estrategia: mantienen reglas locales de color que garantizan una cota global sobre la altura.

Morin destaca tres propiedades principales de los árboles rojo-negro. Primero, un árbol rojo-negro con `n` valores tiene altura a lo más `2 log n`. Segundo, `add(x)`, `remove(x)` y `find(x)` se ejecutan en tiempo `O(log n)` en el peor caso. Tercero, el número amortizado de rotaciones durante inserciones y eliminaciones es constante. Esta combinación explica por qué aparecen en bibliotecas estándar y sistemas reales, aunque su implementación sea más delicada que la de otras estructuras.

### Desarrollo

#### 1. Árboles 2-4 como punto de partida

Un árbol 2-4 es un árbol con raíz que cumple dos propiedades. La primera es la propiedad de altura: todas las hojas tienen la misma profundidad. La segunda es la propiedad de grado: cada nodo interno tiene 2, 3 o 4 hijos.

Estas dos reglas hacen que la altura sea logarítmica. Si el árbol tiene altura `h`, entonces, como cada nodo interno tiene al menos 2 hijos, debe tener al menos `2^h` hojas. Si el número de hojas es `n`, se obtiene:

```text
n >= 2^h
```

Por tanto:

```text
h <= log n
```

El punto importante es que todos los caminos desde la raíz hasta una hoja tienen la misma longitud. Esta igualdad de profundidad es la base conceptual de la altura negra en árboles rojo-negro.

#### 2. Inserción en árboles 2-4

Agregar una hoja en un árbol 2-4 es sencillo mientras el padre de la nueva hoja no exceda el grado permitido. Si el padre tenía 2 o 3 hijos, se agrega la nueva hoja y el árbol sigue cumpliendo las reglas.

El problema aparece cuando el padre ya tenía 4 hijos. Al insertar una nueva hoja, tendría 5 hijos, lo cual viola la propiedad de grado. Para corregirlo, se divide el nodo en dos nodos: uno con 2 hijos y otro con 3 hijos. El nuevo nodo creado debe agregarse al padre del nodo original.

Este proceso puede propagarse hacia arriba. Si el padre también queda con demasiados hijos, se divide de la misma manera. Si la división llega a la raíz, se crea una nueva raíz con dos hijos. En ese caso, todas las hojas aumentan su profundidad en una unidad, por lo que la propiedad de altura se conserva.

En una inserción, puede bastar una sola división si el padre del nodo dividido todavía tiene grado menor que 4.

#### 3. Eliminación en árboles 2-4

Eliminar una hoja es más difícil. Si el padre de la hoja eliminada tenía 3 o 4 hijos, después de la eliminación todavía tiene al menos 2 hijos y el árbol sigue siendo válido. Si el padre tenía solo 2 hijos, queda con un único hijo y viola la propiedad de grado.

Para corregirlo, se mira un hermano del nodo afectado. Si el hermano tiene 3 o 4 hijos, se le toma prestado un hijo. Así, el nodo afectado recupera grado 2 y el hermano queda con un grado válido.

Si el hermano solo tiene 2 hijos, no hay hijo sobrante para prestar. En ese caso, el nodo afectado y su hermano se fusionan en un único nodo con 3 hijos, y luego se elimina recursivamente el hermano del padre. Esta fusión puede propagarse hasta la raíz. Si la raíz queda con un solo hijo, se elimina la raíz y su hijo pasa a ser la nueva raíz.

Una eliminación puede propagarse hasta la raíz cuando cada ancestro relevante y su hermano tienen solo 2 hijos.

#### 4. Árbol rojo-negro como simulación binaria de un árbol 2-4

La idea central de Morin es que un árbol rojo-negro puede verse como una representación binaria de un árbol 2-4. En un árbol rojo-negro cada nodo tiene color rojo o negro. El color negro representa la estructura principal del árbol 2-4, mientras que los nodos rojos se interpretan como partes internas del mismo nodo 2-4.

La transformación conceptual es la siguiente: se eliminan los nodos rojos y sus hijos se conectan directamente al padre negro. Después de esta transformación, queda un árbol formado solo por nodos negros. Un nodo negro sin hijos rojos representa un nodo de grado 2 en el árbol 2-4. Un nodo negro con un hijo rojo representa un nodo de grado 3. Un nodo negro con dos hijos rojos representa un nodo de grado 4.

Todo árbol rojo-negro tiene un árbol 2-4 asociado. Esta equivalencia explica por qué las operaciones de árboles rojo-negro pueden simular divisiones, fusiones y préstamos de árboles 2-4 usando recoloreos y rotaciones.

#### 5. Invariantes de color

Morin presenta dos propiedades fundamentales.

La primera es la altura negra o `black-height`:

```text
Todo camino desde la raíz hasta una hoja tiene el mismo número de nodos negros.
```

La segunda es la ausencia de aristas rojo-rojo o `no-red-edge`:

```text
No hay dos nodos rojos adyacentes.
```

Además, se asume que la raíz es negra. También se tratan los nodos externos `nil` como nodos negros. Este detalle simplifica la implementación porque cada nodo real tiene dos hijos con color bien definido.

Estas reglas no garantizan que el árbol sea perfectamente balanceado, pero sí impiden que una ruta sea demasiado larga. La propiedad de altura negra obliga a que todos los caminos tengan la misma cantidad de nodos negros. La propiedad sin aristas rojo-rojo impide que entre dos nodos negros aparezca una cadena larga de nodos rojos.

#### 6. Cota de altura

La cota de altura se entiende mejor usando la correspondencia con árboles 2-4. El árbol 2-4 asociado tiene `n + 1` hojas, correspondientes a los nodos externos del árbol rojo-negro. Como un árbol 2-4 con `n + 1` hojas tiene altura a lo más `log(n + 1)`, cada camino del árbol rojo-negro tiene a lo más esa cantidad de nodos negros.

Por la propiedad `no-red-edge`, entre nodos negros no puede aparecer más de un nodo rojo consecutivo. Por tanto, el camino más largo en el árbol rojo-negro tiene a lo más el doble de longitud que el camino negro correspondiente.

La consecuencia es:

```text
altura <= 2 log n
```

Esta cota es más fuerte que una garantía esperada: se cumple en el peor caso. Por eso los árboles rojo-negro son atractivos para bibliotecas donde no se quiere depender de la aleatoriedad ni aceptar operaciones individuales muy costosas.

#### 7. Inclinación a la izquierda

Morin trabaja con una variante de árboles rojo-negro con inclinación a la izquierda. Esta variante agrega una propiedad adicional:

```text
Si u.left es negro, entonces u.right también es negro.
```

Dicho de otro modo, no se permiten enlaces rojos inclinados hacia la derecha cuando el hijo izquierdo es negro. Esta restricción reduce el número de casos que deben tratarse durante las actualizaciones.

En términos de árboles 2-4, la inclinación a la izquierda produce una representación única. Un nodo 2-4 de grado 2 se representa como un nodo negro con dos hijos negros. Un nodo de grado 3 se representa como un nodo negro con hijo izquierdo rojo e hijo derecho negro. Un nodo de grado 4 se representa como un nodo negro con dos hijos rojos.

Esta decisión hace que el algoritmo sea más estructurado, aunque la eliminación sigue siendo compleja.

#### 8. Operaciones auxiliares de color y rotación

Morin introduce cuatro operaciones auxiliares importantes.

`pushBlack(u)` se aplica cuando `u` es negro y tiene dos hijos rojos. La operación vuelve rojo a `u` y vuelve negros a sus dos hijos. Esto simula una división en el árbol 2-4 subyacente.

`pullBlack(u)` es la operación inversa. Vuelve más negro a `u` y vuelve más rojos a sus hijos. Esta operación aparece durante la eliminación, cuando se necesita manejar un nodo doblemente negro.

`flipLeft(u)` intercambia los colores de `u` y `u.right`, y luego realiza una rotación a la izquierda. Es útil cuando hay un enlace rojo inclinado a la derecha que debe convertirse en un enlace rojo inclinado a la izquierda.

`flipRight(u)` es la operación simétrica: intercambia colores de `u` y `u.left`, y luego realiza una rotación a la derecha.

Estas cuatro transformaciones separan la implementación en piezas pequeñas: primero se entiende cómo se manipulan colores y rotaciones, y luego se estudian los casos de inserción y eliminación.

#### 9. Inserción en RedBlackTree

La inserción empieza igual que en un árbol binario de búsqueda ordinario. Se busca la posición de `x`, se crea una nueva hoja y se coloca allí. La diferencia es que la nueva hoja se colorea de rojo.

Esto no cambia la altura negra de ningún camino, porque un nodo rojo no suma a la cantidad de nodos negros. Por tanto, la propiedad `black-height` no se rompe. Sin embargo, pueden aparecer dos problemas: una violación de inclinación a la izquierda si el nuevo nodo rojo queda como hijo derecho, o una violación `rojo-rojo` si el padre del nuevo nodo también es rojo.

Para corregir estos problemas se llama a `addFixup(u)`. Este método analiza casos locales alrededor de `u`, su padre `w` y su abuelo `g`. Puede realizar `flipLeft(w)` para corregir la inclinación, `pushBlack(g)` para simular una división de un nodo 2-4, o `flipRight(g)` para reorganizar el subárbol y terminar la corrección.

Cada iteración de este proceso realiza trabajo constante y, si no termina, mueve el problema hacia la raíz. Como la altura del árbol es `O(log n)`, `addFixup(u)` cuesta `O(log n)` en el peor caso.

#### 10. Eliminación en RedBlackTree

La eliminación es la parte más delicada. Como en un árbol binario de búsqueda, se reduce el problema a eliminar un nodo `w` que tiene como máximo un hijo real `u`. Luego se reemplaza `w` por `u`.

El problema aparece cuando `w` es negro. Si se elimina un nodo negro, puede reducirse la altura negra en algunos caminos y romperse la propiedad `black-height`. Morin maneja esto sumando el color de `w` al color de `u`. Si ambos eran negros, `u` queda con color 2, que se interpreta como doble negro.

El método `removeFixup(u)` elimina ese doble negro mediante casos locales. Si `u` es la raíz, se lo vuelve negro y se termina. Si el hermano de `u` es rojo, se aplica una transformación que conduce a otro caso. Si el hermano es negro, se usan combinaciones de `pullBlack`, `flipLeft`, `flipRight`, rotaciones y `pushBlack` para mover o eliminar el doble negro.

La eliminación en árboles rojo-negro concentra muchos casos. Conceptualmente, todo el procedimiento simula las operaciones de préstamo y fusión del árbol 2-4 subyacente.

Cada iteración de `removeFixup(u)` toma tiempo constante. Los casos o terminan, o mueven el problema hacia arriba. Por eso, como la altura del árbol es `O(log n)`, la eliminación completa cuesta `O(log n)` en el peor caso.

#### 11. Análisis amortizado de las rotaciones

El teorema principal de Morin indica que `find(x)`, `add(x)` y `remove(x)` cuestan `O(log n)` en el peor caso. Además, hay un beneficio adicional: en una secuencia de `m` operaciones `add(x)` y `remove(x)`, el tiempo total dedicado a los procedimientos de corrección es `O(m)`.

La intuición se obtiene desde los árboles 2-4. Las divisiones y fusiones no pueden ocurrir demasiadas veces sin que antes se haya acumulado cierto potencial en la estructura.

Morin define un potencial para los nodos internos de un árbol 2-4:

```text
Phi(u) = 1, si u tiene 2 hijos
Phi(u) = 0, si u tiene 3 hijos
Phi(u) = 3, si u tiene 4 hijos
```

Cuando un nodo con 4 hijos se divide, el potencial disminuye. Cuando dos nodos con 2 hijos se fusionan, el potencial también disminuye. En cambio, las operaciones ordinarias de agregar o eliminar una hoja solo pueden aumentar el potencial en una cantidad constante.

Como el potencial nunca es negativo, el número total de divisiones y fusiones durante `m` actualizaciones está acotado por `O(m)`. Por la correspondencia entre árboles 2-4 y árboles rojo-negro, esto justifica que el trabajo total de corrección estructural sea lineal en la cantidad de actualizaciones.

#### 12. Comparación con Treap, ScapegoatTree y AVL

Los árboles rojo-negro ocupan una posición especial entre las estructuras estudiadas.

| Estructura | Mecanismo de balance | Garantía principal | Costo de actualización |
|---|---|---|---|
| Treap | Prioridades aleatorias y rotaciones | Tiempo esperado `O(log n)` | Esperado `O(log n)` |
| ScapegoatTree | Reconstrucción parcial | Altura logarítmica garantizada | Amortizado `O(log n)` |
| RedBlackTree | Colores, rotaciones y simulación 2-4 | Peor caso `O(log n)` | Peor caso `O(log n)` |
| AVLTree | Balance por alturas | Altura menor que rojo-negro | Peor caso `O(log n)` |

Los árboles AVL tienen una cota de altura más baja que los árboles rojo-negro. Morin recuerda que, si `F(h)` es el número mínimo de hojas en un AVL de altura `h`, aparece una recurrencia tipo Fibonacci. Esto lleva a una altura aproximada `log_phi n`, donde `phi` es la razón áurea. Por eso, los AVL pueden tener búsquedas más rápidas.

Sin embargo, los árboles rojo-negro tienen una ventaja práctica: controlan muy bien el número amortizado de rotaciones durante las actualizaciones. Esta propiedad los hace útiles en bibliotecas y sistemas donde se realizan muchas inserciones y eliminaciones.

### Conclusiones

Los árboles rojo-negro muestran una forma muy sólida de balancear árboles binarios de búsqueda. A diferencia de los Treaps, no dependen de aleatoriedad. A diferencia de los Scapegoat Trees, no necesitan reconstruir subárboles completos. Su estrategia consiste en mantener invariantes de color que simulan el comportamiento de un árbol 2-4.

La propiedad de altura negra garantiza que todos los caminos tengan la misma cantidad de nodos negros. La propiedad sin aristas rojo-rojo evita que una ruta acumule demasiados nodos adicionales. Juntas implican una altura máxima de `2 log n`, suficiente para asegurar `find(x)`, `add(x)` y `remove(x)` en tiempo `O(log n)` en el peor caso.

El precio de esta garantía es la complejidad de implementación. La inserción requiere corregir enlaces rojos mal ubicados y posibles violaciones rojo-rojo. La eliminación exige manejar el caso del doble negro, que es uno de los puntos más difíciles de los árboles rojo-negro. Por eso, Morin introduce primero los árboles 2-4: permiten entender que los recoloreos y rotaciones no son arbitrarios, sino simulaciones binarias de divisiones, fusiones y préstamos.

Para el curso, esta lectura sirve como puente entre árboles de búsqueda simples y estructuras balanceadas usadas en software real. El mensaje central es que una estructura de datos avanzada no se define solo por sus operaciones públicas, sino por los invariantes internos que garantizan su eficiencia. En los árboles rojo-negro, esos invariantes son suficientemente fuertes para dar garantías en el peor caso, pero suficientemente flexibles para permitir actualizaciones eficientes.
