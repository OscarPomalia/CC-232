### Tablas hash y hash codes - Morin
### Resumen

Esta lectura presenta el capítulo de Morin dedicado a tablas hash. El objetivo es estudiar cómo implementar conjuntos y diccionarios no ordenados cuando las claves pueden transformarse en enteros y distribuirse dentro de una tabla mediante una hash function.

La idea central es distinta a la de los árboles balanceados vistos en la semana anterior. Un AVL o un Red-Black Tree garantiza operaciones `O(log n)` en el peor caso porque controla la altura del árbol. Una tabla hash busca otra meta: obtener `find(x)`, `add(x)` y `remove(x)` en tiempo esperado `O(1)`, siempre que la hash function distribuya bien las claves y que la tabla controle su load factor.

Morin estudia dos implementaciones principales. La primera es `ChainedHashTable`, que resuelve collisions mediante listas por bucket, es decir, mediante separate chaining. La segunda es `LinearHashTable`, que usa open addressing con linear probing, tombstones y resizing. El capítulo también explica cómo diseñar hash codes para tipos primitivos, objetos compuestos, arreglos y cadenas.

Para la Semana 8, esta lectura sirve como base conceptual para comparar `ChainedHashTable`, `LinearHashTable`, hashing universal, políticas de rehashing, tombstones, collision strategies y aplicaciones como conteo de frecuencias, detección de duplicados, `two-sum` e índices invertidos simples.

### Introducción

Un diccionario no ordenado permite insertar, buscar y eliminar elementos por clave. Una forma de implementarlo es usar una estructura ordenada, como un árbol binario de búsqueda balanceado. En ese caso, la clave se compara con otras claves y la eficiencia depende de mantener altura logarítmica.

El hashing toma otro camino. En lugar de ordenar las claves, calcula un table index a partir de ellas. Para una clave `x`, una hash function produce un valor `hash(x)` dentro del rango de slots disponibles. Si la distribución es buena, las claves quedan repartidas de manera uniforme y cada operación examina una cantidad constante de slots en promedio.

Esta eficiencia no aparece automáticamente. Una mala hash function puede enviar muchas claves al mismo slot, degradando la tabla hasta comportamiento lineal. Por eso Morin separa tres niveles que deben analizarse de forma distinta:

    original key
    hash code entero
    table slot

La implementación de la tabla depende de cómo se resuelven las collisions, de cuándo se ejecuta resizing o rehashing, y de qué garantía probabilística ofrece la hash function.

### Desarrollo

#### 1. Problema que resuelven las tablas hash

Morin parte del caso en que se desea almacenar un conjunto pequeño de `n` enteros provenientes de un universo grande:

    U = {0, ..., 2^w - 1}

Reservar un arreglo de tamaño `2^w` sería impráctico cuando `w` es grande. Una tabla hash evita ese costo usando una tabla mucho más pequeña y una función que transforma cada clave en un slot de esa tabla.

El objetivo no es preservar orden. El objetivo es permitir operaciones rápidas para pertenencia, inserción y eliminación. Por eso las tablas hash son adecuadas para conjuntos no ordenados, mapas, conteo de frecuencias, eliminación de duplicados y búsqueda por clave.

La diferencia con los árboles es importante. Un árbol balanceado permite recorrer claves en orden y responder consultas ordenadas. Una tabla hash normalmente no ofrece orden, pero puede ser más rápida para exact-match queries.

#### 2. ChainedHashTable y separate chaining

La estructura `ChainedHashTable` almacena un arreglo `t` de listas. Cada posición de `t` se denomina bucket. En `ChainedHashTable`, un bucket es el contenedor asociado a un índice hash y almacena una lista de elementos. Todos los elementos cuyo hash produce el mismo índice se almacenan en la misma lista:

    t[i] contiene los elementos x tales que hash(x) = i

La tabla mantiene un contador `n`, que representa el número total de elementos. Para que las listas no crezcan demasiado en promedio, se conserva el invariante:

    n <= t.length

De esa forma, el número promedio de elementos por bucket es:

    n / t.length <= 1

La operación `add(x)` primero verifica si `x` ya está presente. Luego revisa si la tabla debe ejecutar `grow()`. Si no hay duplicado, inserta `x` en la lista correspondiente a `t[hash(x)]`.

La operación `find(x)` busca linealmente dentro de la lista `t[hash(x)]`. La operación `remove(x)` hace lo mismo, pero elimina el elemento si lo encuentra. Por tanto, el costo de estas operaciones depende de la longitud de la lista donde cae `x`.

#### 3. Collisions y papel de la hash function

Una collision ocurre cuando dos claves distintas producen el mismo table index. En separate chaining, una collision no impide almacenar datos, pero aumenta la longitud de una lista.

Si la hash function distribuye bien, cada lista tendrá longitud esperada constante. Si distribuye mal, muchas claves pueden caer en el mismo bucket y las operaciones se vuelven lentas.

El análisis de Morin no dice simplemente que hashing es `O(1)`. La afirmación correcta es condicional:

    Las operaciones son esperadas O(1) si la hash function distribuye las claves de manera suficientemente uniforme y si la tabla controla su load factor.

Este matiz es esencial para la Semana 8, porque permite defender por qué se miden collisions, longitud máxima de bucket, load factor y cantidad de operaciones de rehashing.

#### 4. Multiplicative hashing

Morin presenta el hashing multiplicativo como una forma eficiente de transformar un entero de `w` bits en un índice de `d` bits. La tabla tiene tamaño:

    t.length = 2^d

Se elige un entero impar aleatorio `z` en el rango de enteros de `w` bits. Para una clave entera `x`, se calcula:

    hash(x) = ((z * x) mod 2^w) div 2^(w-d)

La interpretación binaria es simple. Primero se multiplica `x` por `z`. Luego se toma el resultado módulo `2^w`, que en muchos lenguajes aparece naturalmente por desbordamiento de enteros fijos. Finalmente se conservan los `d` bits más significativos.

En código de bajo nivel, la división por `2^(w-d)` puede implementarse como un desplazamiento de bits hacia la derecha. Esto hace que el método sea práctico y rápido.

#### 5. Garantía probabilística del multiplicative hashing

El resultado principal de Morin para hashing multiplicativo dice que, para dos valores distintos `x` e `y`, la collision probability está acotada por:

    Pr[hash(x) = hash(y)] <= 2 / 2^d

Esta cota no es perfecta, pero sí suficientemente buena para analizar separate chaining. Si la tabla tiene tamaño `2^d`, entonces `2^d = t.length`, y la probabilidad de que otro elemento caiga en el mismo bucket que `x` es pequeña.

A partir de esa cota, Morin demuestra que la longitud esperada de la lista `t[hash(x)]` es a lo más:

    n_x + 2

donde `n_x` es el número de ocurrencias de `x` en la tabla. En un conjunto sin duplicados, esto significa longitud esperada constante.

La idea de la demostración usa variables indicadoras. Para cada elemento `y` distinto de `x`, se define una variable que vale 1 si `y` produce collision con `x`, y 0 en caso contrario. La linealidad de la esperanza permite sumar las collision probabilities una por una.

#### 6. Resultado para ChainedHashTable

Ignorando el costo puntual de `grow()`, una `ChainedHashTable` soporta:

    add(x) en tiempo esperado O(1)
    remove(x) en tiempo esperado O(1)
    find(x) en tiempo esperado O(1)

Además, si la tabla empieza vacía, el costo total de todas las llamadas a `grow()` durante una secuencia de `m` inserciones y eliminaciones es `O(m)` amortizado.

La razón es la misma que en arreglos dinámicos. Aunque una operación de `grow()` puede costar lineal porque reinserta todos los elementos, esas llamadas a `grow()` no ocurren en cada operación. Su costo se reparte sobre muchas inserciones.

#### 7. LinearHashTable y open addressing

La segunda implementación principal es `LinearHashTable`. En lugar de tener listas por bucket, almacena directamente los elementos dentro del arreglo `t`. Cada slot contiene a lo más un valor.

La intención ideal es colocar `x` en el slot `hash(x)`. Si ese slot está ocupado, se prueba el siguiente slot:

    hash(x)
    hash(x) + 1
    hash(x) + 2
    ...

Los índices se interpretan módulo `t.length`, de modo que al llegar al final del arreglo se vuelve al inicio.

Esta estrategia se llama linear probing. Es simple, cache-friendly y fácil de implementar, pero puede sufrir agrupamiento: un run de slots ocupados puede hacer que varias búsquedas recorran muchos slots consecutivos.

#### 8. Estados de un slot en LinearHashTable

Morin distingue tres tipos de entries en la tabla:

    valor real
    null
    del

Un valor real representa un elemento activo. Un `null` indica que ese slot nunca ha sido ocupado desde la última reconstrucción. Un `del` indica que antes hubo un elemento, pero fue eliminado.

La tombstone `del` es necesaria para que las búsquedas sigan siendo correctas. Si al eliminar un elemento se escribiera `null`, una búsqueda posterior podría detenerse demasiado pronto y concluir equivocadamente que una clave no existe.

Por eso, en open addressing, eliminar no significa simplemente borrar la celda. Significa dejar una tombstone que preserve la continuidad de la probe sequence.

#### 9. Contadores n y q

La `LinearHashTable` usa dos contadores:

    n = número de elementos activos
    q = número de non-null slots

El contador `q` incluye tanto valores reales como tombstones `del`. Esta distinción es importante porque muchas tombstones `del` pueden hacer que las búsquedas recorran slots inútiles.

La tabla mantiene el invariante:

    t.length >= 2q

Esto asegura que al menos la mitad de la tabla sea `null`. Los `null` son esenciales porque una búsqueda termina cuando encuentra el primer `null`.

Cuando `q` crece demasiado, la tabla ejecuta un table rebuild. Cuando `n` baja demasiado, la tabla también puede reducirse. En ambos casos, el proceso elimina las tombstones `del` y reinserta solo los elementos activos.

#### 10. Búsqueda, inserción y eliminación con linear probing

Para buscar `x`, se empieza en `hash(x)` y se avanza linealmente hasta encontrar `x` o hasta encontrar `null`. Si se encuentra `x`, la búsqueda tiene éxito. Si se encuentra `null`, se concluye que `x` no está en la tabla.

Para insertar `x`, primero se verifica que no esté presente. Luego se busca el primer slot que sea `null` o `del`, y se coloca allí el nuevo valor. Si la inserción haría que la tabla exceda su ocupación permitida, se llama antes a `resize()`.

Para eliminar `x`, se busca usando la misma probe sequence. Si se encuentra, el slot se marca como `del` y se decrementa `n`. Si después de eliminar la tabla queda demasiado vacía, se ejecuta un table rebuild con menor table size.

El punto conceptual es que las tres operaciones comparten la misma probe sequence. La diferencia está en qué hacen al encontrar `x`, `null` o `del`.

#### 11. Resizing y limpieza de tombstones

El método `resize()` de `LinearHashTable` cumple varias funciones:

    ajusta el table size
    reinserta los elementos activos
    elimina las tombstones `del`
    reinicia q para que q = n

Morin elige una nueva dimensión `d` tal que:

    2^d >= 3n

Con esto, la nueva tabla tiene suficiente espacio libre. Luego recorre la tabla antigua y reinserta únicamente los elementos reales.

Este proceso es caro en una operación individual, pero su costo total se analiza de forma amortizada. Tal como en arreglos dinámicos, no se reconstruye en cada operación, sino solo cuando los load factors cruzan ciertos umbrales.

#### 12. Runs en linear probing

Para analizar `LinearHashTable`, Morin introduce el concepto de run. Un run de longitud `k` que empieza en un slot `i` es un bloque de `k` slots consecutivos no nulos, precedido y seguido por slots `null`.

En linear probing, el tiempo de una búsqueda está relacionado con la longitud del run donde cae el hash inicial. Si `hash(x)` cae dentro de un run largo, la operación puede examinar muchos slots antes de terminar.

La intuición básica dice que, si al menos la mitad de la tabla es `null`, los runs largos deberían ser raros. Morin formaliza esto bajo la suposición de que los valores hash son uniformes e independientes.

El lema principal afirma que la probabilidad de que un run de longitud `k` comience en un slot fijo decrece exponencialmente:

    O(c^k), para alguna constante 0 < c < 1

Esta caída exponencial implica que los runs largos son improbables.

#### 13. Tiempo esperado en LinearHashTable

Usando el lema sobre runs, Morin demuestra que una operación que empieza en un slot aleatorio examina una cantidad esperada constante de slots.

La idea es sumar la contribución de todos los posibles runs. Aunque un run de longitud `k` puede costar `O(k)`, la probabilidad de runs largos disminuye como `c^k`. Por eso la suma total:

    sum k^2 c^k

converge a una constante.

Como consecuencia, ignorando el costo de `resize()`, `LinearHashTable` ofrece:

    add(x) en tiempo esperado O(1)
    remove(x) en tiempo esperado O(1)
    find(x) en tiempo esperado O(1)

El costo de `resize()` se cubre con análisis amortizado, por lo que una secuencia de `m` operaciones invierte `O(m)` tiempo total en rebuilds.

#### 14. Limitación del supuesto de independencia

El análisis del linear probing supone que los valores hash son independientes y uniformes. Esta suposición es fuerte. En una implementación real, no podemos almacenar una función completamente aleatoria de todos los enteros posibles, porque requeriría demasiada memoria.

Morin usa esta observación para motivar el hashing por tabulación. La pregunta ya no es solo cómo implementar una hash function rápida, sino qué tan cercana debe ser a una hash function aleatoria para sostener el análisis.

Este punto es pedagógicamente importante. Una tabla hash puede tener buen rendimiento en datos normales y aun así comportarse mal en inputs adversariales. Por eso conviene medir collision patterns y discutir casos límite.

#### 15. Tabulation hashing

El hashing por tabulación divide un entero de `w` bits en bloques pequeños de `r` bits. Para cada bloque se consulta una tabla de valores aleatorios, y luego se combinan los resultados con XOR.

Por ejemplo, un entero de 32 bits puede dividirse en cuatro bytes. Cada byte indexa una tabla de 256 entries. Los cuatro valores obtenidos se combinan con XOR y luego se toman los bits necesarios para obtener el índice final.

La ventaja es que no se necesita una tabla gigantesca de table size `2^w`. Solo se necesitan varias tablas pequeñas. El método es rápido y produce una distribución suficientemente buena para varios usos prácticos.

Morin señala que el hashing por tabulación no produce independencia total para cualquier conjunto de claves. Sin embargo, sí es suficientemente fuerte para sostener garantías esperadas en linear probing, según resultados especializados.

#### 16. Hash codes y claves no enteras

Hasta este punto, las tablas hash trabajan con enteros de `w` bits. Pero en aplicaciones reales las claves pueden ser cadenas, objetos, arreglos, registros o estructuras compuestas.

Por eso se necesita una función `hashCode()` que convierta una clave en un entero. Morin establece dos propiedades necesarias:

    Si x e y son iguales, entonces x.hashCode() = y.hashCode().
    Si x e y son distintos, la collision probability debe ser pequeña.

La primera propiedad es obligatoria para la corrección. Si dos objetos iguales producen hash codes distintos, una búsqueda podría fallar aunque el elemento esté almacenado.

La segunda propiedad busca eficiencia. No se pueden evitar todas las collisions, porque hay más objetos posibles que enteros de `w` bits. Pero una buena hash function debe hacer que esas collisions sean raras y difíciles de provocar.

#### 17. Hash codes para tipos primitivos

Para tipos primitivos pequeños, como caracteres, bytes, enteros o flotantes, el hash code puede obtenerse a partir de su representación binaria.

Si el tipo ocupa como máximo `w` bits, se puede interpretar directamente como un entero de `w` bits. Si dos valores son iguales, tienen la misma representación. Si son distintos, usualmente tienen representaciones distintas.

Cuando el tipo ocupa más de `w` bits, como algunos enteros largos o números de doble precisión, puede tratarse como un objeto compuesto por varias partes.

#### 18. Hash codes para objetos compuestos

Un objeto compuesto puede tener varias partes:

    P0, P1, ..., P_{r-1}

Si sus hash codes son:

    x0, x1, ..., x_{r-1}

necesitamos combinarlos de forma robusta. Morin advierte que trucos simples, como combinar con XOR o sumas, pueden romperse fácilmente.

El método propuesto usa coeficientes aleatorios y una reducción final por hashing multiplicativo. La idea general es formar una combinación aleatoria de las partes y luego reducirla a un resultado de `w` bits.

La garantía es que, si dos objetos compuestos difieren en al menos una parte, la probabilidad de que obtengan el mismo hash code queda acotada por una cantidad pequeña, del orden de `1 / 2^w`.

Esto justifica no usar combinadores ingenuos cuando se necesita robustez.

#### 19. Por qué XOR y suma pueden ser malos combinadores

Morin incluye ejercicios que apuntan a un mensaje práctico: combinar componentes con operaciones demasiado simples puede producir muchas collisions.

Si un objeto tiene dos enteros `x` e `y`, usar:

    x XOR y

es malo porque todos los pares con `x = y` producen hash code 0.

Usar:

    x + y

también puede ser malo porque muchos pares distintos pueden tener la misma suma.

Estos ejemplos muestran que una hash function debe evaluarse contra familias completas de inputs, no solo contra algunos casos pequeños. Una hash function que parece razonable puede ser vulnerable a patrones estructurados.

#### 20. Hash codes para arreglos y cadenas

Los arreglos y cadenas tienen longitud variable. El método para objetos con número fijo de partes deja de ser suficiente porque requeriría un coeficiente aleatorio independiente para cada slot posible.

Morin propone usar polinomios sobre un campo primo. Para una secuencia:

    x0, x1, ..., x_{r-1}

se evalúa un polinomio módulo un número primo `p`. Además, se agrega un marcador de fin de secuencia para distinguir secuencias de distinta longitud, incluso cuando una es prefijo de la otra.

Esta técnica permite acotar la collision probability en función de la longitud de la secuencia. Si dos secuencias son distintas, la collision probability está acotada aproximadamente por:

    max(r, r') / p

donde `r` y `r'` son sus longitudes.

El marcador de fin es clave. Sin él, una cadena podría confundirse con otra que tiene la primera como prefijo.

#### 21. Relación con Semana 8

La Semana 8 del curso implementa y compara varias ideas que aparecen en Morin.

`ChainedHashTable` corresponde al separate chaining. Permite observar buckets, collisions y longitud máxima de lista. Es útil para entender que una collision no impide insertar, pero sí aumenta el costo local.

`LinearHashTable` corresponde al open addressing con linear probing. Permite estudiar active load factor, occupied load factor, tombstones, búsqueda hasta `null` y table rebuild.

Las extensiones como sondeo cuadrático, doble hashing y Robin Hood hashing permiten comparar collision strategies más allá del núcleo de Morin. Todas intentan controlar el costo de búsqueda cuando hay muchas collisions, pero lo hacen con reglas distintas.

Las métricas de la semana, como número de collisions, probes, tombstones y rehashing, sirven para convertir el análisis teórico en evidencia experimental.

#### 22. Comparación con árboles balanceados

Las tablas hash no reemplazan a los árboles balanceados en todos los escenarios. Resuelven otro problema.

    Estructura            Garantía principal              Preserva orden
    AVLTree               O(log n) peor caso              sí
    RedBlackTree          O(log n) peor caso              sí
    ChainedHashTable      O(1) esperado                   no
    LinearHashTable       O(1) esperado                   no

Un árbol balanceado es preferible si se necesitan recorridos ordenados, rangos, mínimo, máximo, predecesor o sucesor. Una tabla hash es preferible si se necesitan exact-match queries rápidas y no importa el orden.

Esta comparación ayuda a conectar Semana 7 y Semana 8. La Semana 7 estudia eficiencia garantizada mediante invariantes estructurales. La Semana 8 estudia eficiencia esperada mediante dispersión, aleatoriedad y control de load factor.

#### 23. Aplicaciones directas

Las tablas hash aparecen en muchos problemas básicos y reales:

    detectar duplicados
    eliminar repetidos preservando orden
    contar frecuencias
    resolver two-sum
    construir índices invertidos
    deduplicar logs
    mapear nombres a valores
    almacenar caché por clave

En todos estos casos, el patrón es similar. Se transforma una clave en una dirección de acceso rápido y se usa una collision policy para resolver conflictos.

El valor pedagógico de estos ejemplos es que obligan a separar interfaz y representación. Un diccionario dice qué operaciones existen. La tabla hash dice cómo se implementan.

#### 24. Riesgos y casos adversariales

Morin cierra señalando que las tablas hash pueden ser atacadas si la hash function es predecible o débil. Si un adversario logra construir muchas claves que caen en el mismo slot, puede forzar operaciones lineales.

Este riesgo no es solo teórico. En sistemas reales, collisions masivas pueden afectar servidores, parsers, mapas de parámetros, tablas de símbolos y estructuras internas de lenguajes.

Por eso una implementación seria debe considerar:

    hash function robusta
    semillas aleatorias cuando corresponda
    control de load factor
    table rebuild
    collision metrics
    pruebas con inputs adversariales

Este punto conecta con el enfoque experimental de la Semana 8: no basta con que una tabla pase pruebas funcionales. También debe mostrar comportamiento razonable bajo cargas y patrones distintos.

### Conclusiones

El capítulo de Morin muestra que las tablas hash son estructuras extremadamente eficientes, pero su eficiencia depende de decisiones internas precisas. No basta con tener un arreglo y aplicar una operación módulo. Se requiere una hash function adecuada, una collision strategy clara, una load policy y un mecanismo correcto de resizing.

`ChainedHashTable` resuelve collisions acumulando elementos en listas por bucket. Su análisis es directo cuando la hash function garantiza que las listas tienen longitud esperada constante. El hashing multiplicativo proporciona una forma simple y rápida de obtener esa garantía probabilística.

`LinearHashTable` usa open addressing y linear probing. Su implementación es compacta, pero requiere distinguir cuidadosamente entre `null` slots, active slots y slots `del`. Las tombstones son necesarias para preservar la corrección de las búsquedas, y el resizing es necesario para limpiar tombstones y controlar la ocupación.

La parte sobre hash codes amplía la discusión a claves reales. Tipos primitivos, objetos compuestos, arreglos y cadenas requieren estrategias distintas. Morin muestra que combinadores ingenuos como XOR o suma pueden producir muchas collisions, mientras que métodos basados en multiplicación aleatoria o polinomios sobre campos primos ofrecen mejores garantías.
