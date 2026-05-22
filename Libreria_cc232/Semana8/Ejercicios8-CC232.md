# Ejercicios 8 - Hashing

## Básicos

1. Inserta 100 enteros en `ChainedHashTable` y reporta `loadFactor()` y `longestBucket()`.
2. Inserta 100 enteros en `LinearHashTable`, elimina 40 y reporta `tombstoneCount()`.
3. Usa `HashtableOA<string,int>` para contar palabras en un texto.
4. Implementa una prueba que compare `contains` contra `std::unordered_set`.

## Intermedios

5. Construye un dataset adversarial para linear probing.
6. Compara `LinearHashTable`, `QuadraticHashTable` y `DoubleHashTable` con las mismas claves.
7. Modifica `RehashPolicy` y mide cómo cambia la longitud máxima de sondeo.
8. Explica por qué `occupiedFactor()` puede ser alto aunque `loadFactor()` sea bajo.

## Avanzados

9. Explica el método MAD de `UniversalHash` y prueba dos semillas distintas.
10. Compara `RobinHoodHashTable` contra `LinearHashTable` usando `maxProbeLength` y `maxDisplacement`.
11. Implementa una variante de `twoSum` que devuelva todas las parejas distintas.
12. Extiende `invertedIndex` para ignorar palabras vacías como `de`, `la`, `el`, `and`, `the`.
13. Diseña un benchmark BST/AVL/HashTable. No basta con tiempo: reporta también memoria conceptual, ordenamiento y garantías de complejidad.
14. Redacta una defensa de una página: ¿qué estructura usarías para un directorio de estudiantes por código?
