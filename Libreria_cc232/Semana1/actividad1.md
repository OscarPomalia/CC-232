## Actividad 1- CC232

### Integrantes
- Oscar Alberto Pomalia Suyo
- Brian Jair La Torre Urbina

#### Bloque 1

1. El PROBLEMA es la descripción abstracta de qué se quiere resolver.
Incluye entrada válida, salida esperada y las condiciones que debes satisfacer(correctitud).
El ALGORITMO es la "receta" paso a paso para resolver un problema.
Define qué hacer (secuencias de operaciones, decisiones, bucles, recursión) desde la entrada hasta obtener la salida.
EL ADT(Abstract Data Type) es el modelo lógico de un tipo de dato centrado en operaciones y comportamiento, no en cómo se almacena.
La implementación es el detalle concreto de cómo se hace el algoritmo o el ADT usando una estructura de datos real y el lenguaje de programación.
2. El observable común que conecta correctitud y costo es: resultado de la ejecución (outputs + metadatos de recursos)
3. Porque realiza menos operaciones para grandes n, menor tiempo y menor peso en recursos(comparaciones/multiplicaciones) y aun produce el mismo resultado (correctitud conservada) porque usa descomposición n = suma de potencias de 2.
4. La función Fibonacci es correcta: cualquier entrada válida produce la salida esperada, pero es mala elección práctica porque el tiempo de ejecución crece brutalmente, requiere mucha pila (profundidad recursiva) y memoria temporal, no escala a casos reales grandes.
5. El tamaño de entrada es la medida de la complejidad (número de elementos/longitudes, o números de bits).
El valor númerico es lo que se almacena en cada elemento o en la entrada misma, son conceptos distintos, y analizarlos bien evita confundirse al estimar costo/eficiencia.
6. El ADT define "qué operaciones existen y qué propiedades deben mantener"(interfaz). Cada implementación puede usar estructuras diferentes (arreglo fijo, vector, lista, árbol) mientras que el cliente sigue viendo la misma "promesa funcional".

#### Bloque 2

1. Para justificar costo (tiempo/espacio) tenemos que hacer que el programa imprima métricas de ejecución por ejemplo:
-Comparaciones
-Intercambios/movimientos
-Iteraciones de bucle
-Pasadas completas
2. La mejora algorítmica es: mismo base*exp, pero de O(n) (lineal) a O(log n) y eso es la comparación concreta que buscamos.
3. Podemos verificar que nos dan el mismo resultado ambos algoritmos, tanto fib(n) como fibI(n). Con la demo podemos ver que se obtienen el mismo resultado, pero el tiempo es diferente pues fib(n) es exponencial y fibI(n) es lineal.
4. El ejemplo implementado ayuda mucho a identificar que el tamaño de la entrada no siempre coincide con el valor numérico. En este caso, el valor numérico es 361, pero el tamaño de la entrada son los 9 bits. 

#### Bloque 3

1. Las pruebas publicas verifican el comportamiento basico de las funciones implementadas en la semana. En test_public_week1.cpp se prueban: las tres versiones de sum, las funciones de potencia, las tres versiones de Fibonacci y la clase Fib. En test_public_week1_extra.cpp se prueban: bubbleSortOptimized verificando orden y que haya comparaciones, countOnes1 y countOnes2 contando bits en 1, maxI, maxRLinear y maxRDivide para encontrar el maximo, reverseRecursive y shiftLeftByK para invertir y desplazar arreglos, gcdCN para el maximo comun divisor, y solveHanoi.
2. Una prueba publica demuestra que la funcion produce la salida esperada para casos concretos y conocidos. Si la prueba pasa, confirma que para esas entradas especificas el resultado es correcto. Tambien sirve como documentacion ejecutable de que es lo que se espera que haga la funcion.
3. Una prueba publica no demuestra correctitud general. Que pase para unos pocos casos no garantiza que funcione para todas las entradas posibles. No demuestra eficiencia ni costo temporal o espacial. Tampoco casos borde que no esten incluidos explicitamente, ni asegura robustez ante entradas invalidas o extremas.
4. Explica con tus palabras las nociones de:
- entrada: se brinda el problema al algoritmo para que pueda tener un resultado final que sea correcto y útil.
- salida: Resultado obtenido a partir del procesamiento del algoritmo del problema brindado, tiene que ser correcto y útil. 
- determinismo: significa que la descripción del algoritmo siempre debe ser el mismo.   
- factibilidad: cuando corresponden los pasos que se han descrito al modelo elegido, que tenga sentido y sea posible poderlos implementar.
- finitud: el algoritmo debe tener una cantidad de pasos finitas para poder llegar al resultado. 
- corrección: el resultado del algoritmo, satisface lo que el problema de entrada pide. Si termina, debe de resolver.
5. -Comprensión conceptual(Logrado): Identifiqué correctamente los conceptos de algoritmo, correctitud, finitud, eficiencia, complejidad y  	recursión en el código(power, bubble_sort,etc).
   -Sustentación de correctitud(En proceso): Dije que el resultado final debe ser igual (base*exp, ordenamiento correcto y que esto se 	respalda con el concepto de invariante).
   - Análisis de eficiencia(Logrado): Comparé clases de complejidad(exp. lineal vs logarítmica, bubble O(n²) vs merge O(n log n), etc.) y 	propuse métricas concretas (comparaciones, swaps, recursión).

#### Bloque 4

1. La diferencia clave observable es:
Lectura y copia dejan el original sin cambios.
Modificación altera el vector original inmediatamente.
La copia permite modificar un vector sin afectar el original del llamador.
2. Se vuelve más eficiente, ya que elimina la mayoría de las realocaciones. El tiempo se reduce a O(n) puro (solo inserciones), con una constante mucho menor.
3. Tienen costos radicalmente diferentes por la forma fundamental en que std::vector almacena y maneja sus elementos. Aunque todas las funciones usan reserve(n) (evitando realocaciones), el lugar de inserción determina cuántos elementos deben ser desplazados en memoria, lo que genera diferencias dramáticas en rendimiento.
4. El benchmark compara tres escenarios de recorrido de datos para ilustrar un concepto fundamental de rendimiento en sistemas modernos: la localidad de memoria y cómo el caché del CPU impacta dramáticamente en velocidad, más allá de la complejidad algorítmica Big-O. La intuición que deja es poderosa y desafía suposiciones comunes.

#### Bloque 5

1. El orden correcto antes de optimizar es:
    -Elegir bien el algoritmo.
    -Verificar que el programa sea correcto.
    -Medir rendimiento.
    -Explorar optimizaciones más avanzadas del compilador.
2. -reserve: Compara el crecimiento incremental de un std::vector sin reservar espacio vs. usando reserve() para preasignar capacidad. También incluye una variante con resize() y asignación directa por índice.
   -nth_element: Compara encontrar el k-ésimo elemento (ej. la mediana) usando nth_element vs. ordenar todo el arreglo con sort.
   -partial_sort: Compara obtener los Top-K elementos usando partial_sort vs. ordenar todo el arreglo. Incluye una variante híbrida con nth_element + sort parcial.
   -lower_bound: Compara búsquedas en un vector ordenado usando lower_bound (búsqueda binaria) vs. búsqueda lineal con find.
3. Produce evidencia empírica y documental para validar conceptos de rendimiento, corrección y herramientas de desarrollo.
4. El archivo INSTRUCCIONES_Ejercicios0_v4.2.md menciona limitaciones específicas relacionadas con el entorno de ejecución, enfocándose principalmente en Windows.
5. Semana0 extiende Semana1 al asumir correctitud y enfocarse en calidad/eficiencia, pero no la reemplaza porque la verificación fundamental es esencial para cualquier código.

#### Bloque 6

En Semana1, la especificación es algorítmica: "calcula la suma de n números" o "ordena un arreglo". En Semana0 experimental, la especificación se expande a incluir restricciones de rendimiento y recursos. Ya no es solo "calcula correctamente", sino "calcula correctamente en ≤ X microsegundos, usando ≤ Y bytes de memoria, con ≤ Z realocaciones". La correctitud se bifurca. En Semana1, verificas que sum([1,2,3]) == 6 con un test. En Semana0, asumes que ambas implementaciones son correctas (ambas producen el mismo resultado), y en su lugar verificas que la medición es reproducible y que el ambiente experimental es controlado. En Semana1, razonas: "Esta recursión es O(2^n), esta iteración es O(n), la iterativa gana". En Semana0 experimental, medimos costos reales con constantes. En Semana1, declares std::vector<int> y asumes que cabe en RAM. En Semana0 experimental, medimos y reportamos cómo la representación interna impacta rendimiento. Los benchmarks pueden engañar. resolver_ejercicios0_v4.2.sh reporta "El script usa /usr/bin/time o time para medir, y estadísticas pueden variar según compilador, optimizaciones, CPU y sistema operativo". Una medición de 10 ms hoy puede ser 5 ms en otra máquina o con diferente versión de compilador. Los benchmarks que mostramos son ilustrativos, no absolutos.

#### Autoevaluación breve
- Qué podemos defender con seguridad: Que entendemos la diferencia entre problema, algoritmo, ADT e implementación.
- Qué todavía confundimos: Cuándo una función es correcta pero no práctica por su costo (fibonacci recursivo).
- Qué evidencia usaríamos en una sustentación: Comparación de pasos/operaciones para mostrar mejora algorítmica.