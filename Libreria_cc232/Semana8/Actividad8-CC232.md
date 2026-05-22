# Actividad 8 - Hashing, diccionarios y comparación experimental

## Propósito

Construir, usar y defender implementaciones de tablas hash como diccionarios no ordenados. La actividad debe conectar el diseño de la función hash, la estrategia de resolución de colisiones, el factor de carga, la eliminación perezosa y el rehashing.

## Parte A - Núcleo obligatorio

1. Ejecuta y explica `ChainedHashTable<int>`.
   - Mide `loadFactor()` y `longestBucket()`.
   - Fuerza colisiones con claves como `0, 8, 16, 24, ...`.

2. Ejecuta y explica `LinearHashTable<int>`.
   - Mide `loadFactor()`, `occupiedFactor()` y `tombstoneCount()`.
   - Inserta, elimina y vuelve a insertar para observar tombstones.

3. Usa `HashtableOA<string,int>` como diccionario.
   - Implementa conteo de frecuencia de palabras.
   - Explica por qué `put` falla cuando la clave ya existe.

4. Compara las tres métricas básicas:
   - colisiones,
   - longitud máxima de sondeo,
   - cantidad de rehashings.

## Parte B - Extensión avanzada

Compara al menos tres estrategias:

- chaining,
- linear probing,
- quadratic probing,
- double hashing,
- Robin Hood hashing.

Usa `demo_collision_strategies.cpp` y complementa con tus propios datos.

## Parte C - Aplicaciones

Implementa o modifica una aplicación:

1. `twoSum`: resolver en `O(n)` esperado.
2. `wordFrequencyFromText`: contador de frecuencias.
3. `deduplicateLogs`: eliminar repetidos preservando orden.
4. `invertedIndex`: construir un índice palabra -> documentos.

## Producto esperado

Entrega un informe corto con:

- tabla comparativa de las estrategias,
- explicación de la función hash usada,
- factor de carga final,
- cantidad de colisiones,
- longitud máxima de búsqueda,
- evidencia de rehashing,
- conclusión: cuándo elegirías hash table y cuándo AVL/Red-Black Tree.

## Sustentación oral

Debes poder responder:

- por qué `O(1)` es esperado y no garantizado,
- por qué existen colisiones,
- por qué no basta con eliminar una celda en open addressing,
- cuándo Robin Hood hashing mejora a linear probing,
- cuándo preferir un árbol balanceado.
