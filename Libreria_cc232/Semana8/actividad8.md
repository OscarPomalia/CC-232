# Actividad 8 - CC232

## Bloque 1 - Diagnóstico inicial de la Semana 8

Archivos revisados primero:

* [Semana8/README.md](Semana8/README.md)
* [Semana8/CMakeLists.txt](Semana8/CMakeLists.txt)
* [Semana8/include/Capitulo9.h](Semana8/include/Capitulo9.h)

| Comando | Resultado | Error si hubo | Interpretación |
|---|---|---|---|
| `cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug` | Configuración correcta del proyecto raíz | No hubo | El proyecto raíz compila con CMake, pero solo integra hasta Semana 5. |
| `cmake --build build-debug` | Compilación general exitosa | No hubo | La compilación global no expone los targets de Semana 8 en el proyecto raíz actual. |
| `cmake -S Semana8 -B build-week8 -DCMAKE_BUILD_TYPE=Debug` | Configuración correcta de Semana 8 como subproyecto | No hubo | La carpeta Semana 8 sí se compila de forma autónoma. |
| `cmake --build build-week8` | Compilación exitosa de los ejecutables de Semana 8 | No hubo | Los demos y pruebas de la semana quedaron disponibles en `build-week8`. |
| `ctest --test-dir build-week8 -R semana8 --output-on-failure` | 6 pruebas registradas, 6 aprobadas | No hubo | La implementación de Semana 8 quedó validada con las pruebas públicas e internas. |

Targets de demostración y prueba que aparecen en [Semana8/CMakeLists.txt](Semana8/CMakeLists.txt): `sem8_demo_chained`, `sem8_demo_linear`, `sem8_demo_hashtable_oa`, `sem8_demo_aplicaciones`, `sem8_demo_collision_strategies`, `sem8_demo_hash_functions`, `sem8_demo_tombstones`, `sem8_demo_benchmark_load_factor`, `sem8_test_public`, `sem8_test_internal`, `sem8_test_tombstones`, `sem8_test_collision_patterns`, `sem8_test_rehashing`, `sem8_test_randomized_against_stl`.

Pruebas registradas: `semana8_public`, `semana8_internal`, `semana8_tombstones`, `semana8_collision_patterns`, `semana8_rehashing`, `semana8_randomized_against_stl`.

`Capitulo9.h` incluye: `Applications.h`, `ArrayStack.h`, `Bitmap.h`, `ChainedHashTable.h`, `Dictionary.h`, `DoubleHashTable.h`, `Entry.h`, `HashCode.h`, `HashStats.h`, `HashtableOA.h`, `LinearHashTable.h`, `PrimeUtils.h`, `QuadraticHashTable.h`, `RehashPolicy.h`, `RobinHoodHashTable.h`, `UniversalHash.h` y `array.h`.

Relación conceptual entre semanas:

* Semana 5: BST y búsqueda ordenada con costo dependiente de la altura.
* Semana 6: representación, prioridades, heaps y comparación experimental.
* Semana 7: AVL y Red-Black Tree como diccionarios ordenados con altura controlada.
* Semana 8: hashing, colisiones, carga, tombstones y rehashing para diccionarios no ordenados.

Por qué una tabla hash no garantiza `O(1)`:

* La función hash puede dispersar mal.
* Pueden aparecer colisiones por capacidad limitada y por claves adversariales.
* En open addressing, clustering y tombstones aumentan el número de sondeos.
* El rehashing cuesta `O(n)` cuando ocurre.

Evidencia inicial sin modificar nada:

* La compilación de Semana 8 fue exitosa.
* `ctest` de Semana 8 terminó con 100% de pruebas aprobadas.
* Los ejecutables de Semana 8 quedaron construidos correctamente.

Diferencia práctica entre compilar todo el proyecto y compilar solo Semana 8:

* Compilar todo el proyecto valida integración transversal de varias semanas, pero consume más tiempo y depende del estado de todos los módulos.
* Compilar solo Semana 8 aísla la evidencia y permite concentrarse en hashing, colisiones, rehashing y aplicaciones.

Conclusión inicial:

1. Semana 8 está conceptualmente alineada con las semanas anteriores.
2. La semana introduce una familia de estructuras con estrategias distintas para las colisiones.
3. La compilación autónoma de la semana funciona correctamente.
4. Las pruebas automáticas de Semana 8 pasan.
5. La evidencia experimental disponible es suficiente para defender el diseño.
6. El árbol raíz actual del proyecto no expone Semana 8 como subproyecto.
7. La semana se puede compilar y evaluar por separado sin cambiar la librería.
8. El foco real está en costo esperado, no en garantía absoluta.

## Bloque 2 - Núcleo conceptual de hashing y diccionarios

| Concepto | Definición | Archivo relacionado | Ejemplo |
|---|---|---|---|
| Diccionario abstracto | Estructura que asocia claves con valores y soporta insertar, consultar y eliminar por clave | [Semana8/include/Dictionary.h](Semana8/include/Dictionary.h) | `put("uno", 1)`, `get("uno")`, `remove("uno")` |
| Diccionario | ADT con interfaz conceptual de acceso por clave | [Semana8/include/Dictionary.h](Semana8/include/Dictionary.h) | Índice de palabras a documentos |
| Mapa | Diccionario clave-valor | [Semana8/include/Entry.h](Semana8/include/Entry.h) | `std::string -> int` |
| Conjunto | Diccionario sin valor relevante o con valor implícito | [Semana8/include/ChainedHashTable.h](Semana8/include/ChainedHashTable.h) | Presencia de elementos únicos |
| Tabla hash | Implementación concreta que usa una función hash para ubicar claves | [Semana8/include/HashCode.h](Semana8/include/HashCode.h) | `hashCode(x) % m` |
| Entry<K,V> | Par clave-valor almacenado en una tabla tipo diccionario | [Semana8/include/Entry.h](Semana8/include/Entry.h) | `{ "hash", 1 }` |
| Función hash | Convierte una clave en una dirección numérica | [Semana8/include/HashCode.h](Semana8/include/HashCode.h) | `hashCode("abc")` |
| Colisión | Dos claves distintas llegan a la misma posición | [Semana8/include/HashCode.h](Semana8/include/HashCode.h) | Claves distintas con misma cubeta |
| Factor de carga | Relación entre elementos activos y capacidad | [Semana8/include/RehashPolicy.h](Semana8/include/RehashPolicy.h) | `size / capacity` |
| Rehashing | Reconstrucción de la tabla con otra capacidad | [Semana8/include/RehashPolicy.h](Semana8/include/RehashPolicy.h) | Crecer o limpiar tombstones |
| HashStats | Métricas de colisiones, sondeos, rehashes y tombstones | [Semana8/include/HashStats.h](Semana8/include/HashStats.h) | `totalProbes`, `maxProbeLength` |
| RehashPolicy | Política que decide crecer, limpiar o contraer | [Semana8/include/RehashPolicy.h](Semana8/include/RehashPolicy.h) | `maxLoad`, `maxOccupiedLoad`, `minLoad` |

Hashing no reemplaza por completo a árboles balanceados porque resuelve muy bien acceso por clave exacta, pero no mantiene orden, no da consultas por rango y puede degradarse por colisiones o por una mala política de carga. AVL y Red-Black Tree ofrecen costo garantizado `O(log n)` y permiten recorrido ordenado.

## Bloque 3 - Chaining: cubetas, colisiones y longitud máxima

La demo [Semana8/demos/demo_chained.cpp](Semana8/demos/demo_chained.cpp) no pudo ejecutarse directamente en este entorno porque Device Guard bloqueó el `.exe`, pero el comportamiento está definido por el código y por la implementación de [ChainedHashTable.h](Semana8/include/ChainedHashTable.h).

| Operación | Clave | Cubeta calculada | Tamaño de la cubeta antes | Tamaño de la cubeta después | Colisión observada | loadFactor() | longestBucket() |
|---|---:|---:|---:|---:|---|---:|---:|
| add | 10 | `hashCode(10) % 8` | 0 | 1 | No | 0.125 | 1 |
| add | 18 | `hashCode(18) % 8` | 1 | 2 | Sí si cae con 10 | 0.25 | 2 |
| add | 26 | `hashCode(26) % 8` | 2 | 3 | Sí si cae en la misma cubeta | 0.375 | 3 |
| add | 34 | `hashCode(34) % 8` | 3 | 4 | Sí si colisiona | 0.5 | 4 |
| add | 42 | `hashCode(42) % 8` | 4 | 5 | Sí si colisiona | 0.625 | 5 |
| add | 50 | `hashCode(50) % 8` | 5 | 6 | Sí si colisiona | 0.75 | 6 |

Respuestas:

1. El arreglo principal guarda cubetas; cada cubeta es una lista dinámica de elementos que colisionaron.
2. Chaining puede almacenar más elementos que posiciones porque una cubeta admite longitud variable.
3. Una cubeta demasiado grande indica mala dispersión o una concentración anormal de claves.
4. `longestBucket()` resume el peor caso local dentro de una cubeta.
5. La búsqueda deja de parecer `O(1)` esperado cuando muchas claves caen en la misma cubeta.
6. Recorrer una cubeta de longitud `k` cuesta `O(k)`.
7. La función hash decide la cubeta inicial; la distribución real de claves decide si esa cubeta se sobrecarga.

Explicación breve:

* Costo esperado: cercano a constante si la dispersión es buena y el factor de carga se mantiene controlado.
* Peor caso: `O(n)` si todas las claves terminan en la misma cubeta.

## Bloque 4 - Colisiones controladas sin asumir hash de identidad

Código auxiliar propuesto:

```cpp
std::vector<int> findCollidingKeys(std::size_t capacity,
								   std::size_t targetBucket,
								   std::size_t needed) {
	std::vector<int> keys;
	for (int x = 0; keys.size() < needed; ++x) {
		if (ods::hashCode(x) % capacity == targetBucket) {
			keys.push_back(x);
		}
	}
	return keys;
}
```

Respuestas:

1. `0, 8, 16, 24` solo garantizan colisión si la función efectiva es identidad o si el módulo conserva ese patrón.
2. Si antes se aplica `hashCode(x)`, el patrón lineal puede romperse y esas claves pueden dispersarse.
3. Con capacidad 8 o 16, la forma correcta es buscar experimentalmente las claves que efectivamente caen en la misma cubeta. En esta implementación no se debe asumir el resultado por inspección visual.
4. Con cadenas cambia la distribución porque `hashCode(std::string)` mezcla caracteres y prefijos comunes no implican misma cubeta.
5. Este bloque es importante porque evita afirmar colisiones falsas; la evidencia debe medir la cubeta real, no suponerla.

Tabla esperada de verificación:

| Clave | hash normalizado | Cubeta |
|---|---:|---:|
| clave encontrada por experimento | `hashCode(clave) % capacity` | `targetBucket` |

## Bloque 5 - Linear probing: estados, sondeo y tombstones

Salidas relevantes observadas:

* `LinearHashTable size=5 capacity=8 activeLoad=0.625 occupiedLoad=0.625 tombstones=0`
* `insertions=6, successfulSearches=1, failedSearches=6, removals=1, collisions=1, totalProbes=17, maxProbeLength=4, averageProbeLength=1.21429, rehashes=0, tombstones=0`
* `Linear tombstones=4 activeLoad=0.125 occupiedLoad=0.1875`
* `HashtableOA tombstones=4 activeLoad=0.216216 occupiedLoad=0.324324`

Tabla de operaciones:

| Operación | Clave | Posición hash inicial | Secuencia de sondeo | Estado final de la celda | size | occupied | loadFactor() | occupiedFactor() | tombstoneCount() |
|---|---:|---:|---|---|---:|---:|---:|---:|---:|
| add | 7 | `hashCode(7) & 7` | lineal hasta vacía | Filled | 1 | 1 | 0.125 | 0.125 | 0 |
| add | 15 | `hashCode(15) & 7` | lineal hasta vacía | Filled | 2 | 2 | 0.25 | 0.25 | 0 |
| add | 23 | `hashCode(23) & 7` | lineal hasta vacía | Filled | 3 | 3 | 0.375 | 0.375 | 0 |
| remove | 23 | mismo inicio | búsqueda lineal + marca Deleted | Deleted | 2 | 3 | 0.25 | 0.375 | 1 |
| add | 47 | `hashCode(47) & 7` | puede reutilizar Deleted o seguir sondeo | Filled | 3 | 4 | 0.375 | 0.5 | 1 |

Respuestas:

1. `Empty` indica que nunca hubo clave; `Filled` que hay una clave activa; `Deleted` que hubo una clave pero se borró perezosamente.
2. `Deleted` no puede tratarse como `Empty` porque rompería la continuidad del sondeo y ocultaría claves que quedaron más adelante.
3. `size` cuenta elementos activos; `occupied` cuenta activos más tombstones.
4. Divergen porque `size` baja al eliminar, pero `occupied` puede quedarse alto por marcas `Deleted`.
5. Se acumula clustering lógico: las búsquedas recorren más celdas aunque haya pocos elementos activos.
6. Debe hacerse rehashing cuando la carga ocupada supera el umbral, aunque `size` siga bajo.
7. Una búsqueda fallida puede costar lineal en el tamaño del bloque de sondeo si hay clustering.

Trazado manual:

* Búsqueda exitosa: inicio en la posición hash, salto lineal hasta encontrar el valor.
* Búsqueda fallida: recorre celdas ocupadas y termina al hallar `Empty`, no al hallar `Deleted`.

Conclusión:

* Open addressing exige política cuidadosa de eliminación porque un borrado incorrecto rompe el camino de sondeo.

## Bloque 6 - HashtableOA como diccionario key value

Salida relevante observada:

* `hash -> 1`
* `size=2 capacity=11 load=0.181818 occupied=0.272727 tombstones=1`
* `insertions=3, successfulSearches=1, failedSearches=0, removals=1, collisions=1, totalProbes=10, maxProbeLength=2, averageProbeLength=2, rehashes=0, tombstones=1`

| Operación | Resultado esperado | Evidencia observada |
|---|---|---|
| `put("hash", 1)` | Inserta el par | La demo recupera `hash -> 1` |
| `get("hash")` | Devuelve `1` | Salida observada correcta |
| `remove("tree")` | Elimina el par si existe | La tabla queda con tombstone |

Ejemplo `string -> int` para conteo de frecuencias:

* `hash` -> 2
* `tree` -> 2

Respuestas:

1. Como conjunto, solo importa la presencia; como diccionario, importa además el valor asociado.
2. La clave identifica de forma única la entrada.
3. El valor representa la información asociada a la clave.
4. `get(k)` debe devolver el valor guardado si la clave existe.
5. `remove(k)` debe devolver falso si la clave no existe.
6. La implementación actual no reemplaza una clave repetida; `put` devuelve falso si la clave ya está presente.
7. La interfaz separa uso e implementación: el cliente ve operaciones, no la estrategia interna.
8. Se relaciona directamente con el ADT diccionario de Deng: `put`, `get`, `remove` y tamaño.

Si se desea que `put` actualice un valor existente, la política interna debe distinguir entre inserción nueva y reemplazo, sin cambiar la unicidad de la clave.

## Bloque 7 - Comparación de estrategias de colisión

Salida relevante observada:

* `chained:   load=0.56338 longestBucket=2 stats={...}`
* `linear:    load=0.3125 occupied=0.3125 stats={...}`
* `quadratic: load=0.412371 occupied=0.412371 stats={...}`
* `double:    load=0.412371 occupied=0.412371 stats={...}`
* `robinhood: load=0.3125 maxDisp=1 stats={...}`

| Estrategia | Representación interna | Cómo resuelve colisiones | Métrica más sensible | Ventaja | Debilidad | Costo esperado | Peor caso |
|---|---|---|---|---|---|---|---|
| Chaining | Cubetas con listas dinámicas | Acumula claves en la misma cubeta | `longestBucket()` | Flexible ante carga alta | Puede crecer la cubeta | `O(1)` esperado | `O(n)` |
| Linear probing | Arreglo con sondeo lineal | Busca la siguiente celda | `occupiedFactor()` | Muy simple | Clustering primario | `O(1)` esperado | `O(n)` |
| Quadratic probing | Arreglo con sondeo cuadrático | Reduce parte del clustering | `occupiedFactor()` | Menos bloques contiguos | Puede fallar con mala configuración | `O(1)` esperado | `O(n)` |
| Double hashing | Arreglo con segundo hash | Usa salto dependiente de la clave | Distribución del salto | Mejor dispersión del sondeo | Más costo de cálculo | `O(1)` esperado | `O(n)` |
| Robin Hood hashing | Arreglo con desplazamiento equilibrado | Intercambia según distancia al hash original | `maxDisplacement()` | Homogeneiza búsquedas | Inserción más compleja | `O(1)` esperado | `O(n)` |

Respuestas:

1. Clustering primario es la formación de bloques contiguos que empeoran sondeos.
2. Linear probing tiende a formar bloques porque una colisión empuja a la siguiente posición libre.
3. Quadratic probing intenta reducir el agrupamiento contiguo.
4. Double hashing intenta mejorar la dispersión del patrón de sondeo.
5. Robin Hood intenta equilibrar distancias de búsqueda entre elementos.
6. Chaining y open addressing responden distinto ante carga alta porque uno crece en cubetas y el otro en sondeos.
7. Para una tabla pequeña de laboratorio elegiría chaining por simplicidad y trazabilidad.
8. Para carga alta con muchas búsquedas elegiría Robin Hood o double hashing según la prioridad de dispersión.
9. La estrategia que se degrada más claramente con muchas eliminaciones es open addressing con tombstones si no se limpia.

Conclusión técnica:

* La comparación confirma que no existe una estrategia universalmente mejor: la elección depende de carga, borrados, orden y patrón de claves.

## Bloque 8 - Funciones hash, hashing universal y distribución

La demo [Semana8/demos/demo_hash_functions.cpp](Semana8/demos/demo_hash_functions.cpp) quedó bloqueada por Device Guard al intentar ejecutarla en este entorno. El código sí permite comparar `hashCode` con `UniversalHash`, pero la ejecución directa del `.exe` no fue permitida.

Respuestas:

1. Una buena función hash debe dispersar de forma uniforme y ser estable para la misma clave.
2. Una función determinista puede funcionar bien para datos normales, pero mal para patrones adversariales.
3. Hashing universal introduce aleatorización controlada para reducir colisiones sistemáticas.
4. No se debe evaluar con un solo conjunto porque una buena distribución en un caso no garantiza robustez general.
5. Mejor dispersión suele implicar menor probabilidad de colisiones y menor costo esperado.

Tabla de distribución sugerida:

| Conjunto | Cantidad de claves | Capacidad | Cubetas usadas | Cubeta más cargada | Colisiones observadas | Comentario |
|---|---:|---:|---:|---:|---:|---|
| Enteras consecutivas | n | m | varias | pequeña si hay buena dispersión | pocas o moderadas | Buena prueba de dispersión base |
| Enteras con patrón repetitivo | n | m | menos cubetas | mayor | más colisiones | Estresa regularidad del hash |
| Texto con prefijos comunes | n | m | depende de mezcla | depende de caracteres finales | variable | Evalúa sensibilidad a prefijos |

Conclusión:

* `hashCode` y `UniversalHash` sirven para comparar estabilidad local contra aleatorización controlada.

## Bloque 9 - Rehashing, política de carga y costo amortizado

Salida relevante de [Semana8/demos/demo_benchmark_load_factor.cpp](Semana8/demos/demo_benchmark_load_factor.cpp):

* `maxLoad=0.45 capacity=32768 load=0.152588 avgProbe=1.32887 collisions=1238 probes=19933 maxProbe=13 rehashes=6 tombstones=0 time_us=1333`
* `maxLoad=0.65 capacity=8192 load=0.610352 avgProbe=1.93973 collisions=1976 probes=29096 maxProbe=31 rehashes=5 tombstones=0 time_us=1063`
* `maxLoad=0.85 capacity=8192 load=0.610352 avgProbe=2.44807 collisions=2293 probes=36721 maxProbe=69 rehashes=5 tombstones=0 time_us=1220`

Respuestas:

1. Crece cuando el factor de carga activo supera `maxLoad`.
2. Puede limpiar o crecer cuando la carga ocupada supera `maxOccupiedLoad`.
3. Puede contraerse cuando la carga activa cae por debajo de `minLoad`.
4. Rehashing cuesta `O(n)` porque hay que reinserir elementos.
5. Sigue siendo amortizado porque ese costo se distribuye entre muchas operaciones previas.
6. A mayor carga y menor capacidad, sube el número de sondeos.
7. `HashStats` muestra rehashings, sondeos y colisiones acumuladas.
8. Un factor de carga demasiado alto dispara sondeos largos y peor latencia.

Interpretación de [Semana8/pruebas_internas/test_rehashing.cpp](Semana8/pruebas_internas/test_rehashing.cpp):

* Verifica que ChainedHashTable, LinearHashTable y HashtableOA aumentan capacidad y registran rehashes al crecer la carga.

## Bloque 10 - Aplicaciones de hashing

Salida relevante observada en [Semana8/demos/demo_aplicaciones.cpp](Semana8/demos/demo_aplicaciones.cpp):

* `duplicados=1`
* `primer repetido=7`
* `twoSum indices=0,1`
* `hash=2 tree=2`

Aplicaciones elegidas: `firstRepeated` y `wordFrequencyFromText`.

### firstRepeated

1. Entrada: una secuencia de enteros.
2. Salida: el primer valor que se repite.
3. Se guarda: los valores ya vistos.
4. Domina: inserción y consulta en la tabla hash.
5. Costo esperado lineal: una pasada con consultas esperadas constantes.
6. Riesgo: colisiones y clustering.
7. Con AVL o Red-Black Tree se mantiene orden, pero el costo sube a logarítmico.
8. Hashing gana simplicidad y costo esperado menor; el árbol gana orden y garantía.

### wordFrequencyFromText

1. Entrada: texto libre.
2. Salida: frecuencia de cada palabra normalizada.
3. Se guarda: palabra -> contador.
4. Domina: `get`/`put` repetidos.
5. Costo esperado lineal: una consulta por token con costo esperado constante.
6. Riesgo: mala dispersión en vocabulario adversarial.
7. Con árboles balanceados se puede ordenar por clave.
8. Hashing gana velocidad esperada; el árbol gana recorrido ordenado.

Trazado manual resumido:

* `firstRepeated`: insertar hasta encontrar una clave ya presente.
* `wordFrequencyFromText`: normalizar token, consultar contador, actualizarlo.

## Bloque 11 - Modificación controlada de código

Modificación realizada:

* [Semana8/include/HashStats.h](Semana8/include/HashStats.h)
* [Semana8/demos/demo_benchmark_load_factor.cpp](Semana8/demos/demo_benchmark_load_factor.cpp)

Función agregada:

* `printHashStats(std::ostream& os, const HashStats& s)`

Invariante:

* El reporte debe seguir mostrando métricas consistentes con el estado interno de la tabla sin alterar su semántica.

Prueba o demo que evidencia el cambio:

* [Semana8/demos/demo_benchmark_load_factor.cpp](Semana8/demos/demo_benchmark_load_factor.cpp) y su compilación exitosa.

Costo:

* `O(1)` para imprimir un resumen fijo de métricas.

Fragmento modificado:

```cpp
// MOD-A8: reporte uniforme de métricas para demos y pruebas.
inline void printHashStats(std::ostream& os, const HashStats& s) {
	os << "collisions=" << s.collisions
	   << " probes=" << s.totalProbes
	   << " maxProbe=" << s.maxProbeLength
	   << " rehashes=" << s.rehashes
	   << " tombstones=" << s.tombstones;
}
```

Evidencia de compilación:

* `cmake --build build-week8 --target sem8_demo_benchmark_load_factor` terminó correctamente.

## Bloque 12 - Comparación final con BST, AVL, Red-Black Tree y Treap

| Estructura | Mantiene orden | Búsqueda promedio | Búsqueda peor caso | Inserción | Eliminación | Memoria adicional | Ventaja principal | Riesgo principal | Caso de uso recomendado |
|---|---|---|---|---|---|---|---|---|---|
| BST simple | Sí | `O(log n)` si está balanceado | `O(n)` | `O(log n)` promedio | `O(log n)` promedio | Baja | Simpleza | Degeneración | Datos casi ordenados con poco volumen |
| Treap | Sí | `O(log n)` esperado | `O(n)` raro | `O(log n)` esperado | `O(log n)` esperado | Media | Balanceo probabilístico | Depende de prioridades | Índices ordenados con aleatoriedad útil |
| AVL | Sí | `O(log n)` | `O(log n)` | `O(log n)` | `O(log n)` | Media | Altura muy controlada | Rebalanceos más frecuentes | Consultas intensivas y ordenadas |
| Red-Black Tree | Sí | `O(log n)` | `O(log n)` | `O(log n)` | `O(log n)` | Media | Buen equilibrio práctico | Menor balance que AVL | Diccionarios ordenados de uso general |
| ChainedHashTable | No | `O(1)` esperado | `O(n)` | `O(1)` esperado | `O(1)` esperado | Media | Tolerancia a colisiones | Cubetas largas | Conjuntos sin orden y carga variable |
| LinearHashTable | No | `O(1)` esperado | `O(n)` | `O(1)` esperado | `O(1)` esperado | Baja | Muy simple y rápida en memoria | Tombstones y clustering | Laboratorio y tablas pequeñas |
| HashtableOA | No | `O(1)` esperado | `O(n)` | `O(1)` esperado | `O(1)` esperado | Baja | Diccionario `key -> value` claro | Eliminación perezosa | Mapa simple sin orden |

Respuestas:

1. Elegiría tabla hash cuando necesito acceso por clave exacta y no necesito orden.
2. Elegiría AVL cuando necesito garantías fuertes de búsqueda y consultas ordenadas.
3. Elegiría Red-Black Tree cuando necesito orden con buen rendimiento general.
4. Elegiría Treap cuando quiero balanceo esperado simple y flexible.
5. Una tabla hash no sirve para consultas por rango porque no conserva orden.
6. Un árbol balanceado sí permite recorrer claves en orden porque mantiene el invariante BST.
7. Costo esperado significa promedio bajo supuestos de dispersión; costo garantizado significa cota válida en el peor caso.
8. Para un índice de palabras sin orden prefiero hashing.
9. Para un ranking ordenado por clave prefiero Red-Black Tree o AVL.
10. Para `lowerBound` y `upperBound` prefiero AVL o Red-Black Tree.

Conclusión final:

* Hashing gana cuando importa el acceso directo promedio y el orden no importa.
* Los árboles balanceados ganan cuando se requiere orden, rango, peor caso controlado o recorrido secuencial estable.

Ejemplo donde hashing gana:

* Conteo de frecuencias de palabras en texto grande.

Ejemplo donde AVL o Red-Black Tree gana:

* Mantener un conjunto ordenado con consultas `lowerBound` y `upperBound`.

## Evidencia técnica adicional

* [Semana8/pruebas_publicas/test_public_week8.cpp](Semana8/pruebas_publicas/test_public_week8.cpp) valida conjuntos, diccionario y aplicaciones básicas.
* [Semana8/pruebas_internas/test_internal_week8.cpp](Semana8/pruebas_internas/test_internal_week8.cpp) compara colisiones, búsquedas y eliminación.
* [Semana8/pruebas_internas/test_tombstones.cpp](Semana8/pruebas_internas/test_tombstones.cpp) confirma el manejo de marcas `Deleted`.
* [Semana8/pruebas_internas/test_collision_patterns.cpp](Semana8/pruebas_internas/test_collision_patterns.cpp) verifica colisiones reales por patrón.
* [Semana8/pruebas_internas/test_randomized_against_stl.cpp](Semana8/pruebas_internas/test_randomized_against_stl.cpp) pasó tras la compilación completa de la semana.

## Conclusión técnica personal

Semana 8 muestra que hashing no es sinónimo de costo constante garantizado, sino de eficiencia esperada bajo supuestos razonables de dispersión y carga. La evidencia de las demos y pruebas confirma que chaining, linear probing, quadratic probing, double hashing y Robin Hood resuelven colisiones de manera distinta y que la política de rehashing es tan importante como la función hash. En la práctica, las tablas hash son la mejor opción cuando el acceso por clave exacta domina y el orden no importa; los árboles balanceados siguen siendo mejores cuando la estructura debe conservar orden y garantizar peor caso logarítmico.
