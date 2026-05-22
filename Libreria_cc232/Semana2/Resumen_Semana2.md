### Resumen final - Semana 2

La Semana 2 estuvo centrada en el estudio de las **estructuras lineales basadas en arreglos** y en la forma en que un arreglo simple puede convertirse en una estructura dinámica, abstracta y eficiente. 
El punto de partida fue la diferencia entre **arreglo** y **vector**. Mientras el arreglo ofrece memoria contigua y acceso directo por índice en tiempo constante, el vector aparece como una abstracción más poderosa que encapsula no solo los elementos, sino también su tamaño real, la capacidad disponible y un conjunto de operaciones que permiten insertar, eliminar, buscar, ordenar y recorrer datos de forma controlada. 
Así, el objetivo de la semana no fue únicamente trabajar con una implementación concreta, sino comprender cómo se construye un **ADT Vector** sobre la base de un arreglo lineal.

En esta abstracción, el vector se apoya en tres componentes internos fundamentales: el arreglo de respaldo `_elem`, el tamaño efectivo `_size` y la capacidad `_capacity`. 
Sobre ellos se definen operaciones como `size()`, `get(r)`, `put(r,e)`, `insert(r,e)`, `remove(r)`, `find(e)`, `search(e)`, `sort()`, `deduplicate()`, `uniquify()` y `traverse()`. 
Además, para mantener la comodidad del acceso por índice, se introduce la sobrecarga del operador `[]`, lo que permite acceder a los elementos de manera similar a un arreglo convencional, pero ahora dentro de una estructura más general y segura. 
Esta parte muestra cómo una representación física simple puede convertirse en una interfaz mucho más rica y flexible.

Uno de los temas más importantes fue la **gestión dinámica del espacio**. Un vector no puede trabajar con una capacidad fija durante toda su vida útil, porque eso produciría desbordamientos cuando se llena o desperdicio de memoria cuando queda muy vacío. 
Por ello se estudian los procesos de `expand()` y `shrink()`. Cuando el arreglo interno se llena, se reserva un nuevo bloque de memoria, normalmente del doble de capacidad, se copian los elementos y se libera el bloque anterior. 
Aunque esta operación individual es costosa, el análisis amortizado demuestra que su costo promedio por inserción sigue siendo constante, ya que no ocurre en cada operación, sino solo después de varias inserciones. 
De forma análoga, cuando el vector queda demasiado vacío, conviene reducir su capacidad para mejorar el uso del espacio. 
Con esto, la semana introduce una idea fundamental en estructuras de datos: una operación puede ser cara de manera puntual y aun así resultar eficiente en promedio.

Sobre esta base se analizan las operaciones elementales del vector. Insertar un elemento en una posición `r` obliga a desplazar hacia la derecha todos los sucesores para abrir espacio, mientras que eliminar un elemento o un intervalo requiere desplazar sucesores hacia la izquierda para cerrar el hueco. 
Por eso, el costo de `insert()` y `remove()` depende de la cantidad de elementos desplazados, lo que explica por qué las secuencias basadas en arreglos son muy buenas para acceso aleatorio, pero menos eficientes para inserciones y eliminaciones en posiciones internas. 
Junto a estas operaciones también se introducen métodos auxiliares como `unsort()`, que mezcla aleatoriamente los elementos de un vector o de un intervalo, y `traverse()`, que permite aplicar una misma operación a todos los elementos mediante una función o un objeto función.

Otro aspecto conceptual importante fue distinguir entre **igualdad** y **comparación de orden**. La igualdad permite decidir si dos objetos representan el mismo valor, y es esencial para operaciones como `find()` o la eliminación de duplicados. 
La comparación de orden, en cambio, permite establecer si un elemento es menor o mayor que otro, y resulta indispensable para operaciones como `search()`, `sort()` y `uniquify()`. 
Esta diferencia se vuelve especialmente importante en tipos complejos, donde puede no existir una comparación “natural” y es necesario definir comparadores o sobrecargar operadores para decidir cómo deben ordenarse los objetos. 
También se discute el caso de punteros, donde no interesa comparar direcciones de memoria, sino los objetos apuntados.

Cuando el vector **no está ordenado**, la búsqueda se realiza mediante `find()`, que aplica una búsqueda secuencial recorriendo el vector y devolviendo, por convenio, la última ocurrencia del elemento buscado. 
En el peor caso, si el elemento no existe, es necesario revisar todo el vector, por lo que la complejidad es lineal. En este mismo contexto aparece `deduplicate()`, que elimina elementos repetidos en un vector no ordenado revisando si cada elemento ya apareció antes en su prefijo. 
Aunque el método es correcto, su costo puede crecer hasta `O(n^2)`, ya que combina búsquedas sucesivas con eliminaciones que implican desplazamientos. 
Esto permite ver que, cuando no existe orden en los datos, muchas operaciones siguen siendo posibles, pero raramente son óptimas.

La situación mejora notablemente cuando el vector pasa a ser un **vector ordenado**. En este caso, los elementos están en orden no decreciente, lo que permite explotar la estructura interna de los datos para acelerar varias operaciones. 
Antes de usar algoritmos específicos, se puede verificar si el vector está ordenado con `disordered()`, que cuenta cuántos pares adyacentes están invertidos, si este valor es cero, el vector está ordenado. 
Esta operación marca el paso desde un vector general hacia una estructura más especializada, donde el orden ya no es solo una propiedad descriptiva, sino una herramienta que permite acelerar búsquedas y eliminar duplicados de forma mucho más eficiente.

Una de las consecuencias más claras del orden aparece en `uniquify()`. En un vector ordenado, los elementos repetidos quedan agrupados en bloques contiguos, por lo que ya no hace falta eliminarlos uno por uno con desplazamientos repetidos. 
La versión eficiente de `uniquify()` usa dos índices: uno mantiene la frontera de los elementos únicos ya consolidados y el otro recorre el vector en busca de nuevos valores. 
Cada vez que encuentra un valor distinto, lo mueve a la siguiente posición válida. Al final, basta con ajustar el tamaño del vector y, si es necesario, reducir capacidad. 
Gracias a ello, la eliminación de duplicados en un vector ordenado se realiza en tiempo lineal `O(n)`, lo cual representa una mejora radical frente al costo cuadrático de la versión ingenua.

La búsqueda en vectores ordenados se formaliza mediante `search()`. Aquí aparece la **búsqueda binaria**, uno de los algoritmos clásicos más importantes del curso. 
Su idea consiste en comparar el objetivo con el elemento central de un intervalo y, según el resultado, descartar la mitad izquierda o la mitad derecha. Al repetir este proceso, el tamaño del problema se reduce a la mitad en cada iteración, por lo que la complejidad total es `O(log n)`. 
Los documentos no se limitan a presentar el algoritmo, sino que además analizan su longitud de búsqueda, el número de comparaciones efectuadas y las diferencias entre búsquedas exitosas y fallidas. Esto resulta valioso porque enseña que dos algoritmos con la misma complejidad asintótica 
pueden comportarse de manera distinta según el número de comparaciones que realicen y cómo se distribuyan sus ramas de decisión.

Como variante y refinamiento se introduce la **búsqueda Fibonacci**. En lugar de partir siempre el intervalo exactamente a la mitad, este método elige el pivote utilizando números de Fibonacci, de modo que las particiones sigan una proporción distinta, más cercana a la proporción áurea. 
La motivación es mejorar el equilibrio real de las comparaciones cuando las ramas no cuestan exactamente lo mismo. Aunque la complejidad sigue siendo logarítmica, la búsqueda Fibonacci se presenta como una alternativa interesante a la búsqueda 
binaria tradicional y como una muestra de que incluso en algoritmos clásicos aún es posible optimizar factores constantes y ajustar mejor el comportamiento práctico.

En paralelo al desarrollo del ADT Vector, la semana también estudia varias **estructuras de datos basadas en arreglos**. La primera es `ArrayStack`, que implementa una lista sobre un único arreglo y permite `get()` y `set()` en tiempo constante, mientras que `add(i,x)` y `remove(i)` dependen del número de elementos desplazados. 
Su mecanismo de `resize()` conecta directamente con la idea de expansión y reducción amortizada vista en el vector. Luego aparece `FastArrayStack`, que no modifica la idea teórica, pero sí la implementación práctica, reemplazando bucles manuales por primitivas de copia más rápidas. 
Con esto se muestra que la eficiencia no depende solo del algoritmo abstracto, sino también de cómo se aprovechan las herramientas del lenguaje y del entorno.

Después se estudia `ArrayQueue`, que resuelve el problema de implementar una cola FIFO sobre un arreglo. Para ello utiliza un **arreglo circular**  y aritmética modular, manteniendo un índice `j` para el frente lógico y un contador `n` para el tamaño actual. 
Gracias a esta técnica, `add(x)` y `remove()` pueden realizarse en tiempo constante, ignorando el costo ocasional de `resize()`. A partir de la misma idea se construye `ArrayDeque`, que permite insertar y eliminar eficientemente en ambos extremos, o cerca de ellos, desplazando el lado más corto del arreglo. 
Con esto se obtiene un costo proporcional a `1 + min{i, n-i}`, lo cual es mucho mejor que desplazar siempre una sección completa sin considerar la posición de la operación.

Más adelante aparece `DualArrayDeque`, una estructura que construye un deque usando dos `ArrayStack`, uno para la parte frontal y otro para la parte posterior. 
La mitad delantera se almacena en orden inverso y la trasera en orden normal, de manera que las operaciones cercanas a ambos extremos sigan siendo rápidas. 
Cuando una mitad crece demasiado con respecto a la otra, se aplica `balance()`, que redistribuye los elementos para mantener una proporción razonable entre ambas partes. 
Aunque este rebalanceo puede costar `O(n)` en una llamada aislada, el análisis amortizado mediante el método del potencial demuestra que el costo total de todos los rebalanceos a lo largo de muchas operaciones sigue siendo lineal. 
Esta estructura es importante porque enseña cómo construir diseños más sofisticados a partir de componentes simples.

Finalmente, la semana introduce `RootishArrayStack`, una estructura orientada a optimizar el uso del espacio. En vez de almacenar todos los elementos en un solo arreglo grande, los distribuye en bloques de tamaños crecientes: 1, 2, 3, ..., `r`. 
Gracias a ello, el espacio desperdiciado se reduce a `O(√n)`, una mejora importante frente a estructuras con grandes arreglos parcialmente vacíos. 
Sin embargo, esto introduce un problema adicional: dado un índice `i`, es necesario calcular en qué bloque se encuentra.
Para resolverlo aparece la función `i2b(i)` y, asociada a ella, la técnica `FastSqrt`, que muestra cómo calcular raíces cuadradas de forma eficiente usando preprocesamiento. 
De este modo, la semana también deja claro que el diseño de estructuras de datos no solo trata de acelerar operaciones, sino de administrar memoria con el menor desperdicio posible.

En síntesis, la Semana 2 ofrece una visión amplia y coherente sobre las secuencias implementadas con memoria contigua. Parte del arreglo lineal, lo abstrae en la forma de un vector, estudia cómo hacerlo dinámico mediante expansión y contracción amortizadas, analiza inserciones, eliminaciones, búsquedas y eliminación de duplicados, y demuestra cómo el orden en los datos permite mejoras decisivas como `uniquify()`, búsqueda binaria y búsqueda Fibonacci. Paralelamente, presenta especializaciones como `ArrayStack`, `ArrayQueue`, `ArrayDeque`, `DualArrayDeque` y `RootishArrayStack`, cada una diseñada para responder de manera distinta al equilibrio entre acceso rápido, actualización eficiente y uso razonable del espacio. 
En conjunto, la semana no solo enseña estructuras específicas, sino también los trade-off fundamentales entre **tiempo, espacio, orden de los datos e implementación**.
