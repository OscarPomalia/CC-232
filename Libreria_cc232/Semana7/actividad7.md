### Actividad 7 - CC232
#### Estudiante

- Nombre: Oscar Alberto Pomalia Suyo

#### Bloque 1 - Diagnóstico inicial de la Semana 7

- Targets de demostración en `Semana7/CMakeLists.txt`:
  - `sem7_demo_avl_deng_core`
  - `sem7_demo_avl_compact_rotations`
  - `sem7_demo_bst_deng_vs_avl`
  - `sem7_demo_redblack_morin`
  - `sem7_demo_redblack_llrb`
  - `sem7_demo_compare_avl_vs_redblack`
  - `sem7_demo_compare_with_semana5`
  - `sem7_demo_capitulo7_panorama`
  - `sem7_test_public`
  - `sem7_test_internal`

- Pruebas públicas e internas:
  - `semana7_public`
  - `semana7_internal`

- Archivos incluidos en `Capitulo7.h`:
  - `Entry.h`
  - `BinNode.h`
  - `BinTree.h`
  - `BST.h`
  - `AVL.h`
  - `BinaryTree.h`
  - `BinarySearchTree.h`
  - `RedBlackTree.h`
  - `AVLTreeCompact.h`
  - `RedBlackTreeLLRB.h`

- Relación conceptual entre semanas:
  1. `Semana5` introduce árboles binarios, BST y rotaciones básicas.
  2. `Semana6` agrega prioridad, heaps, Treap y refuerza cómo las invariantes adicionales controlan altura.
  3. `Semana7` estudia árboles balanceados (AVL y Red-Black) que garantizan altura `O(log n)`.

- Por qué no es correcto decir que una carpeta "hereda" de otra carpeta:
  - Una carpeta es una organización de archivos, no una relación de programación.
  - La herencia en C++ es entre clases, no entre directorios.
  - `Semana7` reutiliza ideas de `Semana5` y `Semana6`, pero no "hereda" estructura de carpetas.

- Clases que sí usan herencia dentro del código:
  - `ods::AVL<T, Compare> : public ods::BST<T, Compare>`
  - `ods::RedBlackTree<Node, T, Compare> : public ods::BinarySearchTree<Node, T, Compare>`

- Evidencia inicial:
  - `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` -> configuración exitosa.
  - `cmake --build build-debug --config Debug` -> compilación exitosa.
  - `ctest --test-dir build-debug -R semana7 --output-on-failure` -> "No tests were found" desde la raíz, porque `Semana7` no está incluido en el CMake principal del repositorio.
  - `cd Semana7 && cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug` -> configuración independiente exitosa.
  - `cd Semana7 && cmake --build build --config Debug` -> compilación independiente exitosa.
  - `cd Semana7/build && ctest --output-on-failure` -> 2/2 tests pasaron.

| Comando | Resultado | Error | Interpretación |
|---|---|---|---|
| `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` | Éxito | - | Generación de build desde la raíz.
| `cmake --build build-debug --config Debug` | Éxito | - | Compilación completa.
| `ctest --test-dir build-debug -R semana7 --output-on-failure` | No tests found | - | La raíz del repositorio no incluye `Semana7`.
| `cd Semana7 && cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug` | Éxito | - | Configuración del subproyecto Semana7.
| `cd Semana7 && cmake --build build --config Debug` | Éxito | - | Targets de Semana7 compilados.
| `cd Semana7/build && ctest --output-on-failure` | 2 passed | - | Pruebas públicas e internas de Semana7 funcionan.

Archivos revisados primero:
- `Semana7/README.md`
- `Semana7/CMakeLists.txt`
- `Semana7/include/Capitulo7.h`
- `Semana7/include/AVL.h`
- `Semana7/include/RedBlackTree.h`
- `Semana7/demos/demo_avl_deng_core.cpp`
- `Semana7/demos/demo_redblack_morin.cpp`

#### Bloque 2 - BST como punto de partida

1. Propiedad formal de un BST:
   - Para cada nodo `u`, todas las claves del subárbol izquierdo son menores que `u->x` y todas las claves del subárbol derecho son mayores que `u->x`.
   - Esta condición se mantiene recursivamente en todos los nodos.

2. Por qué `inorder` de un BST produce una secuencia ordenada:
   - `inorder` visita el subárbol izquierdo, luego la raíz y luego el subárbol derecho.
   - Debido a la propiedad BST, las claves del izquierdo son menores que la raíz y las del derecho son mayores, así que el recorrido entrega valores en orden ascendente.

3. Por qué insertar claves ordenadas puede producir un BST degenerado:
   - Si se insertan claves en orden creciente, cada nueva clave es mayor que todas las anteriores y se inserta siempre en la rama derecha.
   - El árbol se convierte en una lista enlazada hacia la derecha.

4. Árbol resultante de insertar `10, 20, 30, 40, 50, 60, 70`:

```
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

5. Altura si no hay balanceo:
   - Altura = 6 (aristas desde la raíz hasta la hoja más profunda).
   - En número de nodos, la profundidad máxima es 7.

6. Por qué una búsqueda puede costar `O(n)`:
   - En un árbol degenerado, la búsqueda recorre un solo camino derecho que visita todos los nodos.
   - El costo en el peor caso es lineal en el número de elementos.

7. Problema que intenta resolver AVL:
   - Evita que el BST crezca en una rama única manteniendo un balance por alturas locales.
   - Garantiza que la altura del árbol permanezca `O(log n)`.

8. Problema que intenta resolver Red-Black Tree:
   - Controla la altura usando un invariante de colores en lugar de exigir un balance perfecto.
   - Mapea el árbol a un equivalente con altura negra equilibrada para garantizar `O(log n)`.

#### Bloque 3 - AVL: balance por altura

1. Qué significa que un nodo esté balanceado en AVL:
   - Su factor de balance está en `{-1, 0, 1}`.
   - Es decir, la diferencia de alturas entre hijo izquierdo y derecho no excede 1.

2. Cálculo del factor de balance:
   - `bf(u) = altura(u->lc) - altura(u->rc)`.

3. Información de altura que debe mantenerse:
   - Cada nodo almacena su `height` correctamente.
   - Tras insertar o eliminar, se actualizan las alturas de los ancestros afectados.

4. Qué representa `_hot` en la línea Deng:
   - Es el último nodo visitado en la búsqueda que precede al lugar de inserción o eliminación.
   - Ayuda a iniciar el rebalanceo desde el ancestro más cercano al punto de cambio.

5. Por qué AVL hereda de `BST<T, Compare>`:
   - `AVL` reutiliza las operaciones de búsqueda e inserción básicas de `BST`.
   - Luego extiende esas operaciones con el rebalanceo por altura.

6. Operación que restaura localmente la forma del árbol:
   - `rotateAt(tallerChild(tallerChild(g)))`.
   - Dependiendo de los hijos altos, realiza rotación LL, RR, LR o RL.

7. Por qué una rotación no destruye la propiedad BST:
   - Las rotaciones mantienen el orden relativo inorder de los nodos.
   - Solo cambian la estructura local de los enlaces sin alterar el orden de las claves.

8. Por qué suele bastar reparar el primer ancestro desbalanceado tras insertar:
   - La primera violación de balance es la más cercana al nodo insertado.
   - Una rotación allí corrige el desequilibrio sin crear nuevos desequilibrios más arriba.

9. Por qué tras eliminar puede requerirse revisar hasta la raíz:
   - La eliminación reduce la altura de un subárbol y puede alterar el factor de balance de muchos ancestros.
   - Es necesario actualizar alturas y verificar cada ancestro hasta la raíz.

Invariantes AVL:
- Orden BST mantenido.
- Para todo nodo `u`, `|altura(izq) - altura(der)| <= 1`.
- Cada nodo almacena su altura correcta.

Trazado de inserción con rotación (ejemplo):
- Insertar `30, 20, 10` en un AVL vacía produce un desbalance LL en `30`.
- Se realiza rotación derecha en `30`, quedando raíz `20` con hijos `10` y `30`.
- El inorder antes y después sigue siendo `10, 20, 30`.

Evidencia de `demo_avl_deng_core.exe`:
```
AVL inorder: 10 20 22 25 27 30 40 50 
AVL level-order: 30 20 40 10 25 50 22 27 
Valido AVL: si
Tras borrar 20 y 40: 10 22 25 27 30 50 
Valido AVL: si
```
Esta salida muestra que la inserción y eliminación logran mantener la validez AVL y el orden inorder.

#### Bloque 4 - Rotaciones AVL: casos LL, RR, LR y RL

- Rotación simple: se aplica cuando los dos hijos altos están en la misma dirección (`LL` o `RR`).
- Rotación doble: se aplica cuando los hijos altos están en direcciones opuestas (`LR` o `RL`).

Por qué LL y RR se corrigen con una sola rotación:
- En esos casos el árbol desbalanceado es lineal hacia un lado.
- Una rotación simple reestructura esa cadena y reduce la altura del subárbol.

Por qué LR y RL requieren dos pasos:
- Primero se corrige la dirección opuesta del hijo interno.
- Luego se realiza la rotación principal en el ancestro desbalanceado.

Qué cambia y qué permanece igual:
- Cambia la estructura local de las conexiones entre el nodo desbalanceado y sus hijos.
- Permanece igual el conjunto de claves en cada subárbol y el orden inorder.

Por qué el inorder es idéntico antes y después:
- Las rotaciones solo mueven nodos entre subárboles adyacentes.
- No se cambia la relación relativa entre valores menores, el nodo raíz local y valores mayores.

Evidencia de `demo_avl_compact_rotations.exe`:
```
insert(30) -> root=30, height=0
insert(20) -> root=30, height=1
insert(10) -> root=20, height=1
insert(25) -> root=20, height=2
insert(28) -> root=20, height=2
insert(27) -> root=25, height=2
inorder: 10 20 25 27 28 30 
level: 25 20 28 10 27 30 
AVLTreeCompact(size=6, height=2)
isAVL = true
```
Esto muestra rotaciones y un árbol balanceado con altura 2 tras inserciones que sin balanceo producirían una rama no equilibrada.

Tabla de casos de rotación (ejemplo conceptual):
| Caso | Secuencia insertada | Nodo desbalanceado | Rotación | Inorder antes | Inorder después | Altura final |
|---|---|---|---|---|---|---|
| LL | 30, 20, 10 | 30 | Rotación derecha | 10 20 30 | 10 20 30 | 1 |
| RR | 10, 20, 30 | 10 | Rotación izquierda | 10 20 30 | 10 20 30 | 1 |
| LR | 30, 10, 20 | 30 | Rotación izquierda en 10 + derecha en 30 | 10 20 30 | 10 20 30 | 1 |
| RL | 10, 30, 20 | 10 | Rotación derecha en 30 + izquierda en 10 | 10 20 30 | 10 20 30 | 1 |

#### Bloque 5 - Red-Black Tree: balance por colores

1. Propiedad BST que mantiene Red-Black Tree:
   - Sigue siendo un árbol binario de búsqueda: izquierdo menor, derecho mayor.

2. Propiedades de color a cumplir:
   - Cada nodo es rojo o negro.
   - La raíz es negra.
   - Ningún nodo rojo puede tener un padre rojo.
   - Todas las rutas desde la raíz a una hoja nula tienen la misma cantidad de nodos negros.

3. Por qué la raíz debe terminar negra:
   - La raíz negra asegura consistencia en el conteo de altura negra y evita un caso especial de violación de color.

4. Qué significa no poder haber dos nodos rojos consecutivos:
   - Un nodo rojo debe tener padres negros.
   - Esto evita cadenas largas de nodos rojos que empeorarían el balance.

5. Qué representa la altura negra:
   - Es el número de nodos negros en cualquier camino desde un nodo hasta una hoja nula.
   - Todas las rutas válidas tienen igual altura negra.

6. Por qué Red-Black Tree permite un balance menos estricto que AVL:
   - AVL exige diferencia de altura = 1 en cada nodo.
   - Red-Black Tree permite subárboles más desiguales siempre que el número de nodos negros sea uniforme.

7. Correcciones al insertar:
   - Recoloración cuando el tío es rojo.
   - Rotaciones y cambios de color cuando el tío es negro.

8. Correcciones al eliminar:
   - Ajustes de color y rotaciones para mantener la altura negra.
   - El algoritmo puede propagar el "doble negro" hacia arriba.

9. Papel de las rotaciones en Red-Black Tree:
   - Reestructuran el árbol localmente.
   - Mantienen la propiedad BST mientras corrigen desequilibrios de color.

10. Papel del cambio de colores:
   - Reequilibra la cantidad de nodos negros en los subárboles.
   - Permite que la estructura mantenga la invariante de altura negra sin rotar en todos los casos.

Invariantes de Red-Black:
- Orden BST.
- Raíz negra.
- No hay dos nodos rojos consecutivos.
- Misma altura negra en todas las rutas.

Evidencia de `demo_redblack_morin.exe`:
```
RB inorder: 2 3 6 7 8 10 11 13 18 22 26 
Valido RedBlack: si
Tras borrar 18 y 11: 2 3 6 7 8 10 13 22 26 
Valido RedBlack: si
```
Esta salida comprueba la validez del BST y de los invariantes de Red-Black antes y después de eliminaciones.

#### Bloque 6 - Comparación: BST, Treap, AVL y Red-Black Tree

| Estructura | Propiedad de orden | Propiedad adicional | Reparación | Altura esperada/garantizada | Caso donde conviene usarla |
|---|---|---|---|---|---|
| BST común | Ordenamiento inorder | Ninguna | Ninguna | `O(n)` peor caso | Datos aleatorios o temporales, cuando no se necesita balance estrictamente |
| Treap | Orden BST por clave | Heap por prioridad | Rotaciones según prioridad | `O(log n)` esperado | Cuando se necesita estructura balanceada probabilística con prioridades |
| AVL | Orden BST | Factor de balance por alturas | Rotaciones LL/RR/LR/RL | `O(log n)` garantizado | Cuando se requiere búsquedas rápidas y alturas muy controladas |
| Red-Black Tree | Orden BST | Colores y altura negra | Rotaciones y recoloración | `O(log n)` garantizado | Cuando se desea buen rendimiento promedio con reglas de balance más flexibles |

#### Bloque 7 - Evidencia de compilación y pruebas



