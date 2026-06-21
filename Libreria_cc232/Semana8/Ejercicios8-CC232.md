### Ejercicios 8 - Hashing

#### Propósito

Estos ejercicios acompañan la Semana 8 sobre hashing, tablas hash y diccionarios no ordenados. El objetivo no es solo ejecutar una tabla hash, sino justificar cómo influyen la `hash function`, el `hash code`, la política de colisiones, el `load factor`, los `buckets`, los `slots`, los `tombstones` y el `rehashing` en el costo observado de `insert`, `contains`, `find`, `remove`, `put` y `get`.

En `ChainedHashTable`, usa el término `bucket` para referirse a la lista asociada a un valor hash. En tablas de direccionamiento abierto, usa los términos `slot`, `entry`, `probe sequence`, `tombstone` y `occupied factor`.

#### Indicaciones generales

1. Trabaja desde la carpeta raíz de la librería.

```bash
cd Libreria_cc232
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug -R semana8 --output-on-failure
```

2. Cada respuesta debe incluir evidencia. Según el ejercicio, la evidencia puede ser código, tabla de resultados, salida de ejecución, explicación matemática, contraejemplo o defensa escrita.
3. No basta con indicar que algo funciona. Se debe explicar por qué la estructura conserva o pierde sus garantías.
4. Cuando compares estructuras, reporta al menos tres dimensiones: tiempo observado, memoria conceptual y garantía de complejidad.
5. Usa `std::unordered_set` o `std::unordered_map` solo como referencia externa, no como reemplazo de las estructuras de la semana.

#### Básicos

1. Inserta 100 enteros en `ChainedHashTable` y reporta `loadFactor()` y `longestBucket()`.

   Producto esperado:
   - código de prueba o demo,
   - número de elementos insertados,
   - tamaño de la tabla,
   - `loadFactor()`,
   - `longestBucket()`,
   - explicación breve de por qué un `bucket` largo indica acumulación de colisiones.

2. Inserta 100 enteros en `LinearHashTable`, elimina 40 y reporta `tombstoneCount()`.

   Producto esperado:
   - cantidad inicial de elementos,
   - cantidad final de elementos activos,
   - número de `tombstones`,
   - `loadFactor()`,
   - `occupiedFactor()`,
   - explicación de por qué los `tombstones` pueden afectar el costo de búsqueda aunque haya pocos elementos activos.

3. Usa `HashtableOA<string,int>` para contar palabras en un texto.

   Producto esperado:
   - texto de entrada de al menos 40 palabras,
   - normalización usada,
   - tabla de frecuencias,
   - explicación de cómo `put`, `get` y `contains` implementan un diccionario `key-value`.

4. Implementa una prueba que compare `contains` contra `std::unordered_set`.

   Producto esperado:
   - generación de al menos 1000 claves,
   - inserciones en ambas estructuras,
   - consultas positivas y negativas,
   - verificación de que ambas estructuras responden igual,
   - explicación de por qué esta prueba valida comportamiento funcional, pero no demuestra complejidad.

5. Analiza el caso de los números secuenciales de estudiantes.

   Una universidad asigna códigos de estudiante en orden creciente. Para una clase nueva de 100 estudiantes, discute si conviene usar los dos primeros dígitos o los dos últimos dígitos como base de un `hash code` simple.

   Producto esperado:
   - respuesta justificada,
   - ejemplo numérico,
   - explicación de qué dígitos cambian más dentro de una misma cohorte,
   - conclusión sobre distribución y colisiones.

6. Ejecuta `demo_chained.cpp` y explica la diferencia entre elementos, `buckets` y colisiones.

   Producto esperado:
   - salida relevante del demo,
   - definición de `bucket`,
   - explicación de cuándo dos claves colisionan,
   - relación entre `longestBucket()` y costo de `find`.

7. Ejecuta `demo_linear.cpp` y describe una búsqueda exitosa y una búsqueda fallida.

   Producto esperado:
   - una clave que sí esté en la tabla,
   - una clave que no esté en la tabla,
   - secuencia conceptual de `slots` inspeccionados,
   - explicación del criterio de parada al encontrar un `null slot`.

8. Explica la diferencia entre `hashCode(x)` y `hash(x)`.

   Producto esperado:
   - definición de ambos términos,
   - ejemplo con una clave de tipo `string`,
   - explicación de por qué `hashCode` puede tener más bits que el índice final de la tabla,
   - relación con `table index`.

#### Intermedios

9. Construye un dataset adversarial para `LinearHashTable`.

   Producto esperado:
   - descripción de las claves elegidas,
   - motivo por el cual generan agrupamiento,
   - medición de `maxProbeLength`,
   - comparación con un dataset aleatorio del mismo tamaño.

10. Compara `LinearHashTable`, `QuadraticHashTable` y `DoubleHashTable` usando las mismas claves.

    Producto esperado:
    - mismo conjunto de datos para las tres estructuras,
    - misma secuencia de inserciones, búsquedas y eliminaciones,
    - tabla con colisiones, sondeos y longitud máxima de sondeo,
    - explicación de cuándo el sondeo cuadrático o el doble hashing reducen el agrupamiento.

11. Modifica `RehashPolicy` y mide cómo cambia la longitud máxima de sondeo.

    Producto esperado:
    - política original,
    - política modificada,
    - comparación de `loadFactor`, `occupiedFactor`, número de `rehashings` y `maxProbeLength`,
    - conclusión sobre el costo de crecer antes o después.

12. Explica por qué `occupiedFactor()` puede ser alto aunque `loadFactor()` sea bajo.

    Producto esperado:
    - definición de `loadFactor()`,
    - definición de `occupiedFactor()`,
    - ejemplo con eliminaciones,
    - explicación del papel de los `tombstones`.

13. Demuestra que, si una tabla usa `2^d` posiciones, hay conjuntos grandes de claves que pueden caer en el mismo índice.

    Producto esperado:
    - argumento usando conteo o principio del palomar,
    - ejemplo con `n = 2^d`,
    - explicación de por qué esto no contradice el análisis esperado cuando el multiplicador se elige aleatoriamente.

14. Para un multiplicador fijo `z`, describe una familia de claves que tienda a concentrarse en un mismo índice.

    Producto esperado:
    - descripción algebraica o experimental,
    - relación con hashing multiplicativo,
    - al menos una prueba con valores concretos de `w`, `d` y `z`,
    - discusión de por qué una elección fija puede ser vulnerable.

15. Analiza una versión lenta de `add` en sondeo lineal que no reutiliza correctamente `tombstones`.

    Producto esperado:
    - secuencia de operaciones `add`, `remove` y `find`,
    - explicación de cómo se acumulan `tombstones`,
    - argumento de por qué una secuencia de longitud `O(n)` puede producir costo total cuadrático,
    - comparación con la versión que sí limpia mediante `rehashing`.

16. Diseña cadenas distintas que produzcan el mismo `hashCode` si una función ignora la mitad de sus caracteres.

    Producto esperado:
    - regla de construcción de cadenas,
    - al menos 8 ejemplos,
    - explicación de por qué ignorar posiciones de la cadena destruye información,
    - conclusión sobre colisiones artificiales.

17. Muestra por qué `x XOR y` no es un buen `hash code` para un objeto compuesto por dos enteros.

    Producto esperado:
    - conjunto grande de pares distintos `(x, y)` con el mismo resultado,
    - caso particular donde el resultado sea 0,
    - explicación de por qué se pierde información estructural,
    - propuesta de mejora.

18. Muestra por qué `x + y` no es un buen `hash code` para un objeto compuesto por dos enteros.

    Producto esperado:
    - conjunto grande de pares distintos con la misma suma,
    - explicación de la colisión,
    - comparación breve con `x XOR y`,
    - propuesta de combinación más robusta.

#### Avanzados

19. Explica el método MAD de `UniversalHash` y prueba dos semillas distintas.

    Producto esperado:
    - fórmula del método MAD,
    - descripción de los parámetros aleatorios,
    - dos ejecuciones con semillas distintas,
    - comparación de distribución y colisiones,
    - explicación de por qué una familia universal reduce la dependencia de patrones específicos de entrada.

20. Compara `RobinHoodHashTable` contra `LinearHashTable` usando `maxProbeLength` y `maxDisplacement`.

    Producto esperado:
    - mismo dataset para ambas estructuras,
    - valor de `maxProbeLength`,
    - valor de `maxDisplacement`,
    - explicación de la regla Robin Hood,
    - conclusión sobre búsquedas exitosas y fallidas.

21. Implementa una variante de `twoSum` que devuelva todas las parejas distintas.

    Producto esperado:
    - firma de función en inglés,
    - manejo de repetidos,
    - salida sin parejas duplicadas,
    - complejidad esperada,
    - prueba con números positivos, negativos y repetidos.

22. Extiende `invertedIndex` para ignorar palabras vacías como `de`, `la`, `el`, `and`, `the`.

    Producto esperado:
    - conjunto de palabras vacías,
    - normalización de texto,
    - índice invertido antes y después del filtro,
    - explicación de por qué hashing es útil para consultar pertenencia en el conjunto de palabras vacías.

23. Diseña un benchmark BST, AVL y HashTable.

    No basta con tiempo. Reporta también memoria conceptual, ordenamiento y garantías de complejidad.

    Producto esperado:
    - operaciones medidas: inserción, búsqueda exitosa, búsqueda fallida y eliminación,
    - tabla comparativa,
    - explicación de si la estructura mantiene orden,
    - garantía en peor caso o garantía esperada,
    - recomendación técnica.

24. Redacta una defensa de una página sobre la estructura que usaría para un directorio de estudiantes por código.

    Producto esperado:
    - estructura elegida,
    - estructura descartada,
    - supuestos sobre el patrón de consultas,
    - discusión sobre ordenamiento por código,
    - discusión sobre colisiones o balanceo,
    - conclusión defendible.

25. Demuestra que la cota de colisión del hashing multiplicativo no puede mejorarse en general sin cambiar el método.

    Producto esperado:
    - elección de dos claves dependientes de `w` y `d`,
    - análisis binario del producto con el multiplicador,
    - explicación del evento de colisión,
    - conclusión sobre la cota `2 / 2^d`.

26. Rehaz el análisis de una racha de longitud `k` en linear probing usando Stirling completo.

    Producto esperado:
    - definición de `run`,
    - probabilidad de que una racha de longitud `k` comience en una posición fija,
    - uso explícito de la aproximación completa de Stirling,
    - conclusión de decaimiento exponencial,
    - relación con costo esperado `O(1)`.

27. Demuestra por conteo que cualquier función determinista de dos enteros de `w` bits a un entero de `w` bits tiene colisiones grandes.

    Producto esperado:
    - dominio y codominio,
    - argumento con principio del palomar,
    - tamaño mínimo de una clase de colisión,
    - interpretación para objetos compuestos,
    - relación con la necesidad de mezclar información.

28. Explica la identidad modular usada para calcular `x mod (2^w - 1)` sin una división completa.

    Producto esperado:
    - demostración de la congruencia,
    - interpretación de `x mod 2^w` como bits bajos,
    - interpretación de `x div 2^w` como bits altos,
    - ejemplo numérico con `w = 8`,
    - pseudocódigo del algoritmo iterativo.

29. Diseña un experimento contra una implementación real de tabla hash.

    Usa una implementación de uso común o una implementación de la Semana 8. Busca un conjunto de claves que produzca búsquedas lineales o una longitud de sondeo muy alta.

    Producto esperado:
    - implementación elegida,
    - método para descubrir claves problemáticas,
    - programa de prueba,
    - medición de tiempo o cantidad de sondeos,
    - explicación de por qué el caso es adversarial,
    - recomendación para mitigar el problema.

30. Compara hashing con chaining y open addressing bajo eliminaciones intensivas.

    Producto esperado:
    - secuencia con muchas eliminaciones,
    - comportamiento de `ChainedHashTable`,
    - comportamiento de `LinearHashTable`,
    - efecto de `tombstones`,
    - conclusión sobre cuándo conviene limpiar o reconstruir la tabla.

#### Entrega mínima sugerida

Para considerar completa la práctica de ejercicios de Semana 8, entrega al menos:

1. cuatro ejercicios básicos,
2. cinco ejercicios intermedios,
3. tres ejercicios avanzados,
4. una defensa escrita de diseño,
5. una tabla experimental comparando al menos tres estructuras.
