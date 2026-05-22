### Listas basadas en arreglos: fundamentos, variantes y eficiencia algorítmica

**Resumen.** Las **listas basadas en arreglos** constituyen una familia de estructuras lineales que explotan la **contigüidad en memoria** para ofrecer **acceso directo** a los elementos y, al mismo tiempo, implementan operaciones de actualización, inserción y eliminación mediante distintas estrategias de desplazamiento y redimensionamiento. Dentro de esta familia destacan **ArrayStack**, **FastArrayStack**, **ArrayQueue** y **ArrayDeque**, estructuras que comparten un arreglo de respaldo pero difieren en la forma en que administran los extremos de la secuencia, el costo de las modificaciones internas y el uso de **aritmética modular** para simular continuidad circular. En conjunto, estas variantes muestran que una misma base física puede sostener interfaces abstractas distintas, como **List**, **Stack**, **Queue** y **Deque** siempre que se diseñen reglas adecuadas para organizar los datos y para amortizar el costo de las operaciones caras, especialmente las llamadas a **resize()**.   

**Palabras clave:** **listas basadas en arreglos**, **arreglo de respaldo**, **acceso directo**, **ArrayStack**, **FastArrayStack**, **ArrayQueue**, **ArrayDeque**, **arreglo circular**, **aritmética modular**, **redimensionamiento**, **análisis amortizado**, **cola FIFO**, **deque**, **complejidad temporal**.

### Introducción

Las estructuras lineales pueden implementarse de múltiples maneras, pero las representaciones basadas en arreglos ocupan un lugar central porque aprovechan una propiedad extremadamente valiosa: el acceso a una posición puede calcularse directamente, sin necesidad de recorrer elementos previos. Esta ventaja convierte al arreglo en una base natural para la implementación de colecciones indexadas, ya que operaciones como consulta y actualización por índice se resuelven con gran eficiencia. Sin embargo, esa misma representación impone una restricción importante: la estructura física es rígida, de modo que cualquier inserción o eliminación que altere el orden interno obliga a mover elementos ya almacenados. 

El estudio de estas estructuras tiene interés no solo práctico, sino también metodológico. Permite observar cómo una representación muy simple, basada en un único bloque de memoria, puede adaptarse a comportamientos abstractos distintos mediante decisiones de diseño como el **desplazamiento de bloques**, la **copia optimizada**, la **circularidad del arreglo** y la política de **crecimiento** y **reducción** del almacenamiento. También permite distinguir entre el costo de una operación individual y el costo global de una secuencia extensa de operaciones, distinción que da lugar al **análisis amortizado**.  

Desde esa perspectiva, **ArrayStack** representa la forma más directa de implementar una lista sobre un arreglo; **FastArrayStack** conserva esa lógica pero mejora el rendimiento práctico con rutinas de copia más eficientes; **ArrayQueue** utiliza un arreglo circular para implementar una cola **FIFO** con operaciones constantes; y **ArrayDeque** generaliza la misma idea para permitir inserciones y eliminaciones eficientes cerca de ambos extremos. Cada una de estas variantes ilustra una manera distinta de negociar la relación entre **rapidez de acceso** y **costo de actualización estructural**.   

### Desarrollo

#### 1. Fundamento general de las listas basadas en arreglos

Una lista basada en arreglos mantiene sus elementos en un **arreglo de respaldo** y utiliza una variable para distinguir entre la capacidad total del arreglo y el número real de elementos almacenados. Esta separación es esencial: permite conservar espacio libre para futuras inserciones y evita la necesidad de reconstruir la estructura después de cada modificación. Gracias a esta organización, las operaciones de acceso y actualización por índice tienen costo **O(1)**, mientras que las operaciones de inserción y eliminación dependen del número de elementos que deban desplazarse para preservar el orden lógico de la secuencia. 

Esta observación encierra la idea central de toda la familia. El arreglo ofrece una representación físicamente compacta y excelente para acceso posicional, pero no es flexible de manera natural ante cambios en el tamaño o en la distribución interna de los elementos. Por ello, toda estructura basada en arreglos debe responder a dos preguntas: cómo reorganizar los datos cuando se inserta o elimina un elemento, y cómo redefinir el bloque de almacenamiento cuando el espacio disponible deja de ser adecuado.  

#### 2. ArrayStack: implementación secuencial de la interfaz List

**ArrayStack** implementa la interfaz **List** con dos componentes principales: un arreglo **a** y una variable **n** que indica cuántos elementos están actualmente almacenados. Los elementos válidos ocupan las posiciones desde **a[0]** hasta **a[n-1]**, mientras que el arreglo puede tener capacidad adicional aún no utilizada. Esta disposición hace que **get(i)** y **set(i, x)** se resuelvan en tiempo constante, ya que basta con acceder directamente a la posición indicada. 

La operación **add(i, x)** revela, en cambio, el costo real de preservar el orden secuencial. Antes de insertar, la estructura debe comprobar si el arreglo está lleno; si lo está, se ejecuta **resize()** para obtener un nuevo bloque más grande. Luego, todos los elementos del segmento comprendido entre la posición **i** y el final lógico de la lista deben desplazarse una posición hacia la derecha. Solo entonces puede escribirse el nuevo valor y aumentar **n**. El tiempo de esta operación, ignorando el redimensionamiento, es **O(1 + n - i)**; por ello, insertar al final es barato, mientras que insertar cerca del inicio es caro. 

La operación **remove(i)** es simétrica. Primero se guarda el elemento que será devuelto; después, los elementos a la derecha de **i** se desplazan una posición hacia la izquierda para cerrar el hueco; finalmente, se decrementa **n** y se evalúa si el arreglo ha quedado demasiado grande respecto del número de elementos útiles. Si la utilización es baja, se llama a **resize()** para reducir espacio. También aquí el costo, dejando aparte el redimensionamiento, es **O(1 + n - i)**. 

**Pseudocódigo de inserción en ArrayStack**

```text
función ADD(i, x)
    si n + 1 > longitud(a) entonces
        RESIZE()
    fin si

    para j desde n hasta i + 1 hacer
        a[j] <- a[j - 1]
    fin para

    a[i] <- x
    n <- n + 1
fin función
```

**Pseudocódigo de eliminación en ArrayStack**

```text
función REMOVE(i)
    x <- a[i]

    para j desde i hasta n - 2 hacer
        a[j] <- a[j + 1]
    fin para

    n <- n - 1

    si longitud(a) ≥ 3n entonces
        RESIZE()
    fin si

    retornar x
fin función
```

Estas operaciones muestran un principio estructural importante: en un arreglo, modificar la colección no significa solo añadir o quitar un dato, sino también restaurar la continuidad lógica del almacenamiento. En consecuencia, el costo de actualización está gobernado por la cantidad de elementos que deben ser movidos. 

#### 3. El sentido del redimensionamiento y del análisis amortizado

El método **resize()** constituye el mecanismo que convierte a un arreglo rígido en una estructura dinámica. Cuando el arreglo se llena, se crea uno nuevo, normalmente de tamaño cercano a **2n**, y se copian allí los elementos existentes. Cuando la estructura queda demasiado vacía, se reduce el arreglo para evitar desperdicio excesivo de espacio. Vista de manera aislada, cada llamada a **resize()** cuesta tiempo lineal, porque copia todos los elementos activos. 

No obstante, el análisis correcto no debe fijarse solo en una llamada particular. El texto demuestra que, comenzando con un **ArrayStack** vacío, cualquier secuencia de **m** operaciones **add(i, x)** y **remove(i)** produce en total solo **O(m)** tiempo invertido en todas las llamadas a **resize()**. La razón es que entre dos redimensionamientos sucesivos deben ocurrir muchas operaciones ordinarias. Si el arreglo se llena y se redimensiona, antes de necesitar otra expansión debieron realizarse numerosas inserciones; si el arreglo se encoge, ello solo ocurre después de una cantidad suficiente de eliminaciones. En ambos casos, las operaciones caras quedan suficientemente espaciadas y su costo se reparte sobre muchas operaciones baratas. 

Esta idea es una aplicación directa del **análisis amortizado**. No se afirma que toda operación individual sea barata; se afirma algo más potente para el diseño de estructuras: que el costo promedio atribuible al mantenimiento del almacenamiento es constante cuando se observa una secuencia larga de actualizaciones. Esto justifica el uso de arreglos dinámicos en contextos donde una inspección superficial podría llevar a pensar que el redimensionamiento los vuelve ineficientes. 

#### 4. ArrayStack como implementación eficiente de pila

Aunque **ArrayStack** está diseñado para implementar **List**, su comportamiento lo hace especialmente apto para representar una **Stack**. Si se define **push(x)** como **add(n, x)** y **pop()** como **remove(n - 1)**, ambas operaciones actúan sobre el extremo final de la lista y evitan desplazamientos masivos. En ese caso, el costo relevante es solo el del posible redimensionamiento, que ya se sabe amortizado. Por ello, una pila implementada con **ArrayStack** soporta sus operaciones fundamentales en tiempo amortizado **O(1)**. 

Esta observación es conceptualmente importante. Muestra que una estructura no debe evaluarse en abstracto, sino en relación con el patrón de operaciones que va a soportar. La misma representación física que resulta costosa para inserciones al inicio puede ser excelente cuando las modificaciones se concentran sistemáticamente al final. 

#### 5. FastArrayStack: optimización sin cambio asintótico

**FastArrayStack** conserva la estructura lógica de **ArrayStack**, pero sustituye los bucles explícitos de copia y desplazamiento por rutinas especializadas como **memcpy**, **memmove**, **std::copy** o equivalentes del entorno de programación. En la implementación mostrada, tanto **resize()** como **add(i, x)** delegan el movimiento de bloques a funciones optimizadas de biblioteca. 

El punto crucial es que esta mejora no modifica las cotas asintóticas: una operación lineal sigue siendo lineal. Sin embargo, el rendimiento práctico puede mejorar de manera significativa, porque esas rutinas suelen estar ajustadas a bajo nivel e incluso aprovechar instrucciones especiales del procesador. El propio texto señala aceleraciones de entre dos y tres veces en implementaciones de C++, según el tipo de operación y de datos utilizado. Así, **FastArrayStack** ilustra una distinción clásica entre dos clases de mejora: la mejora **asintótica**, que cambia el orden de crecimiento, y la mejora **constante**, que no altera la teoría de complejidad pero sí puede tener gran impacto empírico.  

Desde una perspectiva académica, esta variante recuerda que el análisis de estructuras no se agota en la notación asintótica. Dos implementaciones con la misma complejidad teórica pueden exhibir comportamientos muy distintos en la práctica si difieren en la forma de usar memoria, en la granularidad de sus copias o en la cercanía de sus operaciones al hardware subyacente. 

#### 6. ArrayQueue: implementación de colas mediante arreglo circular

Una **cola FIFO** exige insertar por un extremo y eliminar por el otro. Si se intentara implementarla directamente con **ArrayStack**, una de esas dos operaciones tendría que realizarse sobre la cabeza de la lista, lo que provocaría tiempo lineal por los desplazamientos internos. El texto señala explícitamente que, por esa razón, **ArrayStack** es una mala elección para una cola FIFO.  

La solución consiste en abandonar la interpretación puramente lineal del arreglo y tratarlo como un **arreglo circular**. Para ello, **ArrayQueue** mantiene un arreglo **a**, un índice **j** que apunta al siguiente elemento a eliminar y una variable **n** que cuenta cuántos elementos hay en la cola. Si el arreglo fuese infinito, la idea sería trivial: los elementos ocuparían las posiciones **a[j]**, **a[j+1]**, ..., **a[j+n-1]**. Como el arreglo es finito, se emplea **aritmética modular** para hacer que los índices "den la vuelta" al llegar al final del bloque físico. Así, los elementos se interpretan como **a[j mod a.length]**, **a[(j+1) mod a.length]**, ..., **a[(j+n-1) mod a.length]**. 

Esta decisión transforma por completo el rendimiento de la estructura. Para insertar, basta verificar si el arreglo está lleno y, si no lo está, escribir el nuevo valor en **a[(j+n) mod a.length]** e incrementar **n**. Para eliminar, se guarda **a[j]**, luego se actualiza **j** como **(j+1) mod a.length**, se decrementa **n** y, si hace falta, se llama a **resize()**. Ignorando el costo de redimensionar, ambas operaciones se ejecutan en **O(1)** por operación. 

**Pseudocódigo de inserción en ArrayQueue**

```text
función ENQUEUE(x)
    si n + 1 > longitud(a) entonces
        RESIZE()
    fin si

    a[(j + n) mod longitud(a)] <- x
    n <- n + 1
    retornar verdadero
fin función
```

**Pseudocódigo de eliminación en ArrayQueue**

```text
función DEQUEUE()
    x <- a[j]
    j <- (j + 1) mod longitud(a)
    n <- n - 1

    si longitud(a) ≥ 3n entonces
        RESIZE()
    fin si

    retornar x
fin función
```

El método **resize()** en esta estructura merece atención especial. Como la cola puede estar físicamente "partida" entre el final y el inicio del arreglo circular, no basta copiar el bloque tal como está almacenado. La estructura debe copiar los elementos en su **orden lógico FIFO** a un nuevo arreglo y luego restablecer **j = 0**. De este modo, el arreglo vuelve a quedar normalizado sin alterar el comportamiento abstracto de la cola. El texto resume esta eficiencia en el teorema correspondiente: ignorando el costo de **resize()**, **add(x)** y **remove()** son **O(1)**, y el costo total de todas las redimensiones en una secuencia de **m** operaciones es **O(m)**. 

#### 7. El papel conceptual de la aritmética modular

La **aritmética modular** no cumple aquí una función decorativa, sino estructural. Permite simular un arreglo "infinito" reutilizando de forma cíclica las celdas disponibles del arreglo físico. En otras palabras, evita que las posiciones vacías ubicadas al inicio del arreglo se desperdicien una vez que el índice **j** ha avanzado. Este uso del operador **mod** convierte una representación lineal cerrada en una representación circular abierta a reutilización continua. 

Desde el punto de vista algorítmico, esta transformación es elegante porque elimina la necesidad de desplazar elementos en cada eliminación. En lugar de mover datos para que el frente de la cola vuelva a la posición cero, la estructura mueve solo el significado del índice inicial. Así, el costo que antes recaía sobre la memoria se desplaza a una operación aritmética constante sobre índices. 

#### 8. ArrayDeque: generalización para ambos extremos

**ArrayDeque** amplía la idea de **ArrayQueue**. Mantiene también un arreglo **a**, un índice inicial **j** y una longitud lógica **n**, pero implementa la interfaz **List** en vez de limitarse a la disciplina FIFO. Sus operaciones **get(i)** y **set(i, x)** siguen siendo directas, porque el elemento lógico de índice **i** se almacena en la posición física **a[(j+i) mod a.length]**. Esto preserva el acceso constante incluso cuando la estructura está "envuelta" circularmente. 

La verdadera innovación de **ArrayDeque** aparece en **add(i, x)** y **remove(i)**. En lugar de desplazar siempre el mismo lado de la estructura, compara la posición **i** con **n/2**. Si la operación ocurre cerca del inicio, mueve el prefijo; si ocurre cerca del final, mueve el sufijo. Esta estrategia garantiza que el número de elementos desplazados sea siempre proporcional a **min{i, n - i}**, por lo que el tiempo de inserción o eliminación es **O(1 + min{i, n - i})**. En términos prácticos, la estructura aprovecha el hecho de tener dos extremos disponibles para minimizar el trabajo de reacomodo. 

Esta decisión es especialmente relevante porque introduce una forma de **adaptación dinámica**. La estructura no aplica una única política rígida, sino que elige en cada operación el lado más barato para desplazar. Así, mejora de manera notable frente a **ArrayStack** cuando las operaciones se concentran cerca del inicio o del final, sin perder la ventaja del acceso indexado constante. 

#### 9. Comparación conceptual entre ArrayStack, FastArrayStack, ArrayQueue y ArrayDeque

Las cuatro estructuras analizadas comparten un mismo soporte físico, pero no ofrecen el mismo perfil algorítmico. **ArrayStack** destaca por su simplicidad y por su eficiencia cuando las operaciones se concentran al final. **FastArrayStack** no cambia su comportamiento teórico, pero mejora la ejecución práctica mediante copias especializadas. **ArrayQueue** resuelve con elegancia el problema de la cola **FIFO** gracias al arreglo circular y la aritmética modular. **ArrayDeque**, finalmente, ofrece una solución más flexible, porque permite trabajar eficientemente en ambos extremos sin abandonar el acceso indexado.   

En un nivel más abstracto, estas variantes muestran un principio general del diseño de estructuras de datos: una representación se juzga por la manera en que alinea su geometría física con el patrón de operaciones que desea soportar. El arreglo es excelente para acceso directo; el problema consiste en decidir cómo compensar su rigidez para acercarlo al comportamiento de pilas, colas o deques. Cada una de las estructuras estudiadas responde a ese problema con una estrategia distinta.  

#### 10. Significado general del costo amortizado en esta familia

Uno de los aportes más valiosos de estas implementaciones es que muestran, de manera concreta, por qué el costo de una operación rara pero cara no invalida necesariamente la eficiencia global de una estructura. En **ArrayStack** y **ArrayQueue**, las llamadas a **resize()** son lineales, pero aparecen con baja frecuencia; el texto prueba que, comenzando desde una estructura vacía, cualquier secuencia de **m** operaciones produce en total solo **O(m)** tiempo invertido en redimensionamientos. Esto equivale a decir que el mantenimiento del almacenamiento tiene costo amortizado constante.  

Esta conclusión tiene un alcance más amplio que el caso particular del arreglo dinámico. Enseña a distinguir entre **peor caso local** y **rendimiento global distribuido**, y por ello constituye una herramienta central para evaluar estructuras dinámicas reales. Las implementaciones basadas en arreglos no serían tan útiles si se las juzgara únicamente por el costo de su operación más cara. Su verdadera eficiencia emerge cuando se analiza la frecuencia relativa de esas operaciones dentro de secuencias largas de uso. 

### Conclusión

Las **listas basadas en arreglos** ofrecen un ejemplo particularmente claro de cómo una estructura simple puede dar lugar a una familia completa de implementaciones con comportamientos muy distintos. Todas parten de la ventaja del **acceso directo**, pero divergen en la forma de tratar el problema de las modificaciones estructurales. **ArrayStack** resuelve listas y pilas sobre una secuencia contigua; **FastArrayStack** demuestra que las constantes importan en la práctica; **ArrayQueue** convierte el arreglo en una cola eficiente mediante circularidad y **ArrayDeque** explota ambos extremos para reducir desplazamientos y ampliar la flexibilidad operativa.   

Desde una perspectiva académica, el valor de estas estructuras no reside únicamente en su utilidad técnica. También permiten comprender con precisión la relación entre **representación física**, **interfaz abstracta**, **correctitud operativa** y **complejidad temporal**. En ese sentido, constituyen un laboratorio conceptual especialmente fértil para estudiar cómo se diseña una estructura de datos eficiente y cómo se justifica formalmente su rendimiento.  
