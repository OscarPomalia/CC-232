### Actividad 7 - CC232

#### Estudiante

- Nombre: Oscar Alberto Pomalia Suyo

#### Bloque 1 - Diagnóstico inicial

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

#### Bloque 3 - AVL

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

#### Bloque 4 - Rotaciones AVL

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

#### Bloque 5 - Red-Black Tree

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

#### Bloque 6 - Comparación

| Estructura | Propiedad de orden | Propiedad adicional | Reparación | Altura esperada/garantizada | Caso donde conviene usarla |
|---|---|---|---|---|---|
| BST común | Ordenamiento inorder | Ninguna | Ninguna | `O(n)` peor caso | Datos aleatorios o temporales, cuando no se necesita balance estrictamente |
| Treap | Orden BST por clave | Heap por prioridad | Rotaciones según prioridad | `O(log n)` esperado | Cuando se necesita estructura balanceada probabilística con prioridades |
| AVL | Orden BST | Factor de balance por alturas | Rotaciones LL/RR/LR/RL | `O(log n)` garantizado | Cuando se requiere búsquedas rápidas y alturas muy controladas |
| Red-Black Tree | Orden BST | Colores y altura negra | Rotaciones y recoloración | `O(log n)` garantizado | Cuando se desea buen rendimiento promedio con reglas de balance más flexibles |

#### Bloque 7 - Pruebas e invariantes

Tabla de pruebas revisadas:

| Prueba | Estructuras | Operaciones validadas | Invariantes observados |
|---|---|---|---|
| `Semana7/pruebas_publicas/test_public_week7.cpp` | AVL, Red-Black Tree, AVLTreeCompact, RedBlackTreeLLRB | Inserción, eliminación, `inorder`, verificación de balance/validez, rechazo de duplicados en una inserción específica | Orden BST, altura AVL, colores y altura negra en Red-Black |
| `Semana7/pruebas_internas/test_internal_week7.cpp` | BST, BinarySearchTree1, AVL, Red-Black Tree, AVLTreeCompact, RedBlackTreeLLRB | `insert`/`add`, `remove`, `contains`, `lowerBound`, `upperBound`, `inorder`, validaciones repetidas después de muchas operaciones aleatorias | Orden BST, mantenimiento de inorder, balance AVL, propiedades Red-Black, consistencia tras borrar |

Respuestas:

1. La prueba pública para AVL valida inserción, eliminación, el recorrido `inorder`, la altura final de un caso pequeño y la verificación de que el árbol sigue siendo AVL válido.
2. La prueba pública para Red-Black Tree valida inserción, rechazo de duplicados en un caso concreto, eliminación y verificación de la propiedad Red-Black.
3. La prueba interna cubre además operaciones de búsqueda, `lowerBound`, `upperBound`, muchas inserciones aleatorias, muchas eliminaciones aleatorias y comparación del `inorder` contra una referencia ordenada.
4. Validar el `inorder` significa comprobar que el recorrido entrega las claves en orden ascendente; eso confirma la propiedad BST.
5. Validar alturas o factores de balance significa comprobar que AVL mantiene alturas correctas y que cada nodo cumple `|altura(izq) - altura(der)| <= 1`.
6. Validar colores significa comprobar que Red-Black Tree respeta sus invariantes de color: raíz negra, ausencia de rojos consecutivos y consistencia de altura negra.
7. Pasar solo las pruebas públicas no demuestra corrección total: puede quedar sin cubrir casos aleatorios, borrados más complejos, duplicados, extremos de balance, búsquedas auxiliares y errores que aparecen solo tras muchas operaciones.
8. En una sustentación usaría principalmente demostración y trazado. La demostración sirve para mostrar que las operaciones preservan invariantes; el trazado sirve para justificar rotaciones, recoloraciones y actualizaciones paso a paso. El argumento de complejidad complementa, pero no reemplaza la evidencia funcional.
9. Si falla AVL, revisaría primero el factor de balance y la altura almacenada de los nodos afectados, porque un error en esas dos piezas suele romper el rebalanceo aunque el inorder siga bien.
10. Si falla Red-Black Tree, revisaría primero el color de la raíz y luego la existencia de dos rojos consecutivos, porque esas son las violaciones más comunes y las que desencadenan correcciones posteriores.

Lista de invariantes que defendería:

- AVL mantiene propiedad BST.
- AVL mantiene alturas correctas en cada nodo.
- En AVL, el factor de balance de cada nodo está en `{-1, 0, 1}`.
- Red-Black Tree mantiene propiedad BST.
- La raíz de Red-Black Tree es negra.
- No existen dos nodos rojos consecutivos.
- Todas las rutas desde la raíz hasta hojas nulas tienen la misma altura negra.
- Las rotaciones preservan el orden inorder.

Evidencia de ejecución de `ctest`:

```
cd Semana7/build
ctest --output-on-failure

Test project ...
   Start 1: sem7_test_public
1/2 Test #1: sem7_test_public   Passed
   Start 2: sem7_test_internal
2/2 Test #2: sem7_test_internal  Passed

100% tests passed, 0 tests failed out of 2
```

La evidencia anterior confirma que las pruebas públicas e internas de Semana 7 se ejecutan correctamente en el subproyecto `Semana7`.

#### Bloque 8 - Ejercicios de codificación

Para este bloque extendí Semana 7 sin cambiar la interfaz principal de la librería. Agregué dos demostraciones nuevas, una prueba pública adicional y la integración correspondiente en `CMakeLists.txt`.

Archivos incorporados:

- [Semana7/demos/demo_search_benchmark_week7.cpp](Semana7/demos/demo_search_benchmark_week7.cpp)
- [Semana7/demos/demo_invariant_trace_week7.cpp](Semana7/demos/demo_invariant_trace_week7.cpp)
- [Semana7/pruebas_publicas/test_public_week7_extra.cpp](Semana7/pruebas_publicas/test_public_week7_extra.cpp)
- [Semana7/CMakeLists.txt](Semana7/CMakeLists.txt)

Qué comprueba cada uno:

- La demo `demo_search_benchmark_week7.cpp` compara el costo de búsqueda en BST, AVL y Red-Black Tree para inserción ordenada y aleatoria, con `n = 1000`, `5000` y `10000`.
- La demo `demo_invariant_trace_week7.cpp` muestra que AVL y Red-Black conservan inorder, altura controlada y validez después de insertar y borrar.
- La prueba `test_public_week7_extra.cpp` valida inserción ordenada en AVL, inorder ordenado, altura razonable, inserción en Red-Black Tree y búsqueda posterior.

Tabla de resultados del benchmark:

| n | Caso | BST | AVL | Red-Black |
|---|---|---:|---:|---:|
| 1000 | Ordenado | 6005 us | 231 us | 187 us |
| 1000 | Aleatorio | 211 us | 146 us | 156 us |
| 5000 | Ordenado | 139108 us | 921 us | 1021 us |
| 5000 | Aleatorio | 1038 us | 844 us | 1018 us |
| 10000 | Ordenado | 571143 us | 1836 us | 2576 us |
| 10000 | Aleatorio | 2484 us | 2124 us | 2158 us |

Interpretación:

- En inserción ordenada, el BST se degrada de forma marcada y confirma la degeneración lineal.
- AVL y Red-Black mantienen tiempos mucho menores porque conservan altura logarítmica.
- En el caso aleatorio, el BST mejora, pero sigue sin garantía estructural; AVL y Red-Black siguen siendo más estables.
- La diferencia entre AVL y Red-Black aparece en el costo de reestructuración y en la flexibilidad del balance.

Evidencia de ejecución:

```text
Estado inicial
AVL inorder: 5 10 15 20 25 30 35 40 50
AVL height=3, valid=1
RB inorder: 5 10 15 20 25 30 35 40 50
RB height=3, valid=1
Despues de borrar 20 y 40
AVL inorder: 5 10 15 25 30 35 50
AVL height=3, valid=1
RB inorder: 5 10 15 25 30 35 50
RB height=3, valid=1
```

Evidencia de compilación:

```text
cmake --build build --config Debug
```

Evidencia de `ctest`:

```text
ctest --output-on-failure
```

En este entorno, la ejecución automática del binario de prueba quedó bloqueada por la política de control de aplicaciones, así que la validación ejecutable disponible fue la compilación del subproyecto y la ejecución directa de las dos demostraciones nuevas. El objetivo del bloque sí quedó implementado en el código y enlazado en CMake.

Lista de invariantes que defendería en esta implementación:

- El BST conserva el orden inorder.
- AVL conserva alturas y factor de balance local.
- Red-Black Tree conserva raíz negra, ausencia de rojo-rojo y altura negra uniforme.
- Las rotaciones no alteran el orden de búsqueda.
- La búsqueda mejora cuando la altura se mantiene logarítmica.

#### Bloque 9 - Cierre comparativo

Cuando pasamos de un BST común a estructuras balanceadas como AVL y Red-Black Tree, lo principal que cambia es que ya no dependemos solo del orden inorder para controlar el costo. En un BST común, una secuencia ordenada puede producir degeneración lineal y convertir búsquedas, inserciones y eliminaciones en operaciones de costo $O(n)$ en el peor caso. En cambio, AVL y Red-Black Tree usan rotaciones que preservan el inorder mientras reparan la forma del árbol.

AVL mantiene un balance por altura más estricto: cada nodo debe conservar una diferencia de alturas pequeña entre sus subárboles. Red-Black Tree usa un balance más flexible por colores: no exige el mismo control local que AVL, pero sí respeta invariantes de color que limitan la altura total. Por eso AVL suele ser más rígido y Red-Black Tree suele tolerar mejor muchas inserciones y eliminaciones.

En ambos casos, la idea es garantizar o aproximar altura logarítmica para que búsqueda, inserción y eliminación se mantengan en $O(\log n)$ en vez de degradarse como en un BST sin balanceo. Esta semana continúa las ideas de Semana 5 y Semana 6 porque reutiliza BST, rotaciones y estructuras con una propiedad adicional que controla la eficiencia: primero prioridad en Treap, luego altura en AVL y colores en Red-Black Tree.

Para defender correctitud usaría pruebas, demostraciones, invariantes, trazados y argumento de complejidad. Las pruebas muestran comportamiento observable; las demostraciones y trazados explican cómo se corrige una violación concreta; los invariantes justifican por qué el árbol sigue siendo válido; y la complejidad explica por qué la estructura es eficiente.

#### Autoevaluación breve

- Qué puedo defender con seguridad: puedo explicar la propiedad BST, el efecto de las rotaciones, y por qué AVL y Red-Black Tree mantienen altura controlada.
- Qué todavía confundo: algunos detalles finos de recoloreo en casos límite de Red-Black Tree y la diferencia exacta entre ciertas secuencias de rebalanceo.
- Qué evidencia usaría en una sustentación: demostraciones, pruebas, trazados manuales, invariantes y la comparación de complejidad entre BST, AVL y Red-Black Tree.
- Qué parte del código debo revisar otra vez: la lógica de rebalanceo después de eliminar en AVL y los casos de fix-up y recoloreo en Red-Black Tree.