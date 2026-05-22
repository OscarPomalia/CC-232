### Experimentos con `g++` para analizar optimización, sanitizers, pruebas y benchmarks en CC232


Estos experimentos se pueden realizar con `g++` y son muy útiles para un curso como **CC232**, porque permiten mostrar que el rendimiento de un programa no 
depende solo del compilador, sino también de la **elección del algoritmo**, de la **estructura de datos**, de la **correctitud del código** y de la **calidad de las pruebas**.

La idea principal es esta:

* primero se debe elegir bien el algoritmo
* luego verificar que el programa sea correcto
* después medir rendimiento
* y finalmente explorar optimizaciones más avanzadas del compilador.

Dicho de otro modo: **`-O3` no reemplaza a `nth_element`, a `lower_bound`, a un buen `reserve()`, ni a una prueba bien hecha**.

> Utiliza el archivo dado: [https://github.com/kapumota/CC-232/blob/main/Semana0/stl_optimizacion_demostracion.cpp](https://github.com/kapumota/CC-232/blob/main/Semana0/stl_optimizacion_demostracion.cpp)  para estos experimentos.

#### 1. Experimento base: escalera de optimización

Compilar el mismo programa con distintos niveles de optimización y comparar:

* tiempo de ejecución,
* tamaño del ejecutable,
* facilidad para depurar,
* warnings que aparecen o cambian.

Esto permite mostrar que no existe una única bandera "mejor" para todo.
`-O0` es útil para depuración básica, `-Og` busca conservar una experiencia de depuración razonable con algunas optimizaciones, `-O2` suele ser la opción de trabajo general, `-O3` puede o no mejorar, y `-Os` prioriza tamaño.

##### Comandos

```bash
g++ -std=c++17 -O0 -g -Wall -Wextra -pedantic demo.cpp -o demo_O0
g++ -std=c++17 -Og -g -Wall -Wextra -pedantic demo.cpp -o demo_Og
g++ -std=c++17 -O1 -DNDEBUG demo.cpp -o demo_O1
g++ -std=c++17 -O2 -DNDEBUG demo.cpp -o demo_O2
g++ -std=c++17 -O3 -DNDEBUG demo.cpp -o demo_O3
g++ -std=c++17 -Os -DNDEBUG demo.cpp -o demo_Os
```

##### Qué observar

* cuánto tarda cada ejecutable con el mismo input
* cuánto pesa cada binario
* si el debugger "sigue bien" el código fuente
* si algún warning aparece más claramente en ciertos builds.

##### Complemento útil para clase

```bash
g++ -Q -O2 --help=optimizers
g++ -Q -O3 --help=optimizers
g++ -Q -Os --help=optimizers
```

#### 2. Experimento STL: el algoritmo correcto gana más que el microajuste

Usar un programa como `stl_optimizacion_demostracion.cpp` para comparar pares clásicos de diseño algorítmico con STL:

* `sort()` vs `nth_element()` para mediana o k-ésimo
* `sort()` completo vs `partial_sort()` o `nth_element()` para Top-K
* búsqueda lineal vs `lower_bound()` sobre vector ordenado
* `push_back()` con y sin `reserve()`.

##### Comando base

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic stl_optimizacion_demostracion.cpp -o stl_demo
./stl_demo --light
```

##### Qué observar

* cuánto cambia el tiempo al usar el algoritmo correcto
* qué decisiones mejoran por complejidad y no solo por microajuste
* cómo una mejor estrategia supera diferencias pequeñas entre `-O2` y `-O3`.

#### 3. Experimento LTO: optimización entre archivos

Mostrar qué pasa cuando el compilador puede optimizar a nivel de programa completo y no solo por archivo individual.

##### Comandos

```bash
g++ -std=c++17 -O2 -c a.cpp -o a.o
g++ -std=c++17 -O2 -c b.cpp -o b.o
g++ -std=c++17 -O2 a.o b.o -o app_no_lto

g++ -std=c++17 -O2 -flto -c a.cpp -o a_lto.o
g++ -std=c++17 -O2 -flto -c b.cpp -o b_lto.o
g++ -std=c++17 -O2 -flto a_lto.o b_lto.o -o app_lto
```

##### Qué observar

* si cambia el tiempo de ejecución
* si cambia el tamaño del ejecutable
* si algunas funciones parecen inlinarse o simplificarse mejor.

##### Nota importante

Para que LTO funcione de verdad, `-flto` debe usarse **tanto al compilar como al enlazar**.


#### 4. Experimento PGO: optimización guiada por perfil

Mostrar que el compilador puede optimizar mejor cuando observa una carga real de trabajo.

##### Fase 1: generar perfil

```bash
g++ -std=c++17 -O2 -fprofile-generate demo.cpp -o demo_pgo_gen
./demo_pgo_gen < input_representativo.txt
```

##### Fase 2: usar perfil

```bash
g++ -std=c++17 -O2 -fprofile-use demo.cpp -o demo_pgo_use
```

##### Qué observar

* si mejora el tiempo con inputs similares al de entrenamiento
* si el efecto cambia cuando el input real no se parece al perfil usado
* cómo la optimización depende del patrón de entrada.

#### 5. Experimento con sanitizers: correctitud y errores de memoria

Separar claramente dos tipos de problemas:

* errores lógicos,
* errores de memoria o comportamiento indefinido.

##### Build con AddressSanitizer y UBSan (opcional)

```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined demo.cpp -o demo_asan_ubsan
./demo_asan_ubsan
```

##### Build con ThreadSanitizer

```bash
g++ -std=c++17 -O1 -g -fsanitize=thread demo_threads.cpp -o demo_tsan
./demo_tsan
```

##### Qué probar

* accesos fuera de rango en `vector`
* uso de iteradores inválidos
* overflow o UB
* carreras de datos si hay una versión con hilos.

##### Subexperimento útil

```bash
g++ -std=c++17 -O1 -g -fsanitize=undefined -fsanitize-recover=undefined demo.cpp -o demo_recover
g++ -std=c++17 -O1 -g -fsanitize=undefined -fno-sanitize-recover=undefined demo.cpp -o demo_stop
```

##### Qué observar

* si el programa reporta varios errores y sigue
* o si se detiene en el primero.


#### 6. Experimento de cobertura: tests que pasan no significa tests buenos

Mostrar que un conjunto de pruebas puede pasar y aun así dejar ramas importantes sin cubrir.

##### Comandos

```bash
g++ -std=c++17 --coverage -O0 tests.cpp modulo.cpp -o tests_cov
./tests_cov
gcov tests.cpp modulo.cpp
```

##### Qué observar

* líneas ejecutadas y no ejecutadas
* ramas del código que nunca fueron probadas
* casos borde olvidados.

#### 7. Experimento avanzado de cobertura de condiciones y caminos

Ir más allá de cobertura de líneas y estudiar decisiones booleanas y caminos de ejecución.

##### Comandos

```bash
g++ -std=c++17 -O0 -fcondition-coverage demo.cpp -o demo_cond
g++ -std=c++17 -O0 -fpath-coverage demo.cpp -o demo_path
```

##### Dónde usarlo en clase

Es especialmente útil en funciones con muchos `if`, por ejemplo:

* balanceo AVL
* validación de invariantes
* lógica de hashing
* casos de merge o partition.

##### Qué observar

* si una condición booleana realmente influyó en la decisión
* cuántos caminos diferentes atraviesa el programa
* qué parte de la lógica sigue sin ser ejercitada por los tests.


#### 8. Experimento de warnings dependientes de optimización

Mostrar que algunos warnings mejoran cuando el compilador tiene más información de flujo de control y flujo de datos.

##### Comandos

```bash
g++ -std=c++17 -O0 -Wall -Wextra -Wpedantic demo.cpp -o demo_w0
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic demo.cpp -o demo_w2
```

##### Variante interesante

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -flto a.cpp b.cpp -o demo_lto_warn
```

##### Qué observar

* warnings que aparecen solo en builds optimizadas
* warnings que se vuelven más precisos
* diferencias entre análisis local y análisis global.

#### 9. Experimento clásico de profiling con `gprof`

Identificar funciones calientes y visualizar dónde se va el tiempo total.

##### Comandos

```bash
g++ -std=c++17 -O2 -pg demo.cpp -o demo_gprof
./demo_gprof
gprof demo_gprof gmon.out
```

##### Qué observar

* qué funciones consumen más tiempo
* dónde conviene empezar a optimizar
* cómo una intuición equivocada puede hacerte optimizar la parte menos importante.

#### 10. Qué medir en todos los experimentos

Para que los resultados sean comparables, conviene observar siempre lo mismo:

* tiempo total
* tamaño del ejecutable
* correctitud del resultado
* estabilidad entre corridas
* uso de memoria, si es posible.

Y conviene mantener constantes:

* el mismo input
* la misma máquina
* el mismo compilador
* varias repeticiones
* el mismo entorno de ejecución.
