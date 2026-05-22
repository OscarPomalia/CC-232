# Notas de Semana 8 - Hashing avanzado

## Objetivo

La semana refuerza el bloque de diccionarios no ordenados mediante tablas hash. La meta no es solo implementar `add`, `find` y `remove`, sino medir cuándo una tabla hash conserva costo esperado constante y cuándo se degrada.

## Núcleo obligatorio

1. `Dictionary.h`, `Entry.h`: interfaz de diccionario y par clave-valor.
2. `HashCode.h`, `PrimeUtils.h`: conversión de claves y capacidades primas.
3. `HashtableOA.h`: tabla hash de estilo Deng con `put`, `get`, `remove`, eliminación perezosa y rehashing.
4. `ChainedHashTable.h`: encadenamiento separado.
5. `LinearHashTable.h`: direccionamiento abierto con sondeo lineal.
6. `HashStats.h`, `RehashPolicy.h`: medición y política de crecimiento.

## Extensiones avanzadas agregadas

- `UniversalHash.h`: familia MAD universal `((a*x+b) mod p) mod m`.
- `QuadraticHashTable.h`: sondeo cuadrático.
- `DoubleHashTable.h`: doble hashing.
- `RobinHoodHashTable.h`: hashing Robin Hood con desplazamiento controlado.
- Aplicaciones: conteo de palabras, two-sum, deduplicación de logs e índice invertido.

## Ideas clave para la sustentación

- Una tabla hash no preserva orden. Si se necesita recorrido ordenado, conviene BST/AVL/Red-Black Tree.
- El costo `O(1)` es esperado, no garantizado para todas las entradas.
- El factor de carga afecta directamente la longitud de búsqueda.
- En open addressing, borrar físicamente una celda puede romper la cadena de búsqueda; por eso aparecen tombstones.
- Robin Hood hashing reduce la varianza de las longitudes de búsqueda intercambiando elementos según distancia al hash original.
