### Semana 4 - Pilas, colas y aplicaciones del capítulo 4 de Deng

Esta carpeta continúa la estructura de `Libreria_cc232` con una implementación autocontenida de los contenidos centrales de la semana 4 del curso: pilas, colas y varias aplicaciones clásicas del capítulo 4 de Deng.

El objetivo principal es estudiar cómo `Stack` y `Queue` funcionan no solo como estructuras lineales básicas, sino también como herramientas algorítmicas para resolver problemas de recursión, evaluación de expresiones, búsqueda con retroceso y simulación.

#### Contenido principal

La carpeta incluye las siguientes estructuras y componentes:

- `Stack.h`: pila LIFO con operaciones `push`, `pop`, `top`, `size`, `empty`
- `Queue.h`: cola FIFO con operaciones `enqueue`, `dequeue`, `front`, `size`, `empty`
- `BaseConversion.h`: conversión de base en versión recursiva e iterativa
- `Parentheses.h`: verificación de paréntesis en versión recursiva e iterativa
- `OperatorPriority.h`: definición de relaciones de prioridad entre operadores
- `ExpressionEvaluator.h`: evaluación de expresiones y conversión a RPN
- `Queen.h`: representación de una reina para el problema de N-Reinas
- `NQueens.h`: algoritmo iterativo de N-Reinas con pila explícita
- `Maze.h`: celda de laberinto, consulta de adyacencia, avance y búsqueda de ruta
- `BankSimulation.h`: cliente, selección de la cola más corta y simulación bancaria
- `Capitulo4.h`: header agregador de la semana

#### Organización práctica

Además de los headers, esta carpeta incluye:

- `demos/`: demostraciones de uso básico y panorama general del capítulo
- `pruebas_publicas/`: validaciones públicas de comportamiento esperado
- `pruebas_internas/`: casos adicionales para cobertura de la implementación
- `Actividad4-CC232.md` y `Ejercicios4-CC232.md`: material complementario de trabajo

#### Nota de diseño

Para que `Semana4` pueda integrarse sin romper el flujo de las semanas anteriores, esta versión está implementada en estilo *header-only*, con `namespace ods`, y sin depender internamente de la implementación concreta de `Semana2` o `Semana3`.

Esto permite que la semana se pueda:

- usar como módulo independiente,
- compilar desde su propia carpeta,
- o integrar directamente dentro de `Libreria_cc232` junto con las demás semanas.

#### ¿Desde dónde se compila?

Para mantener la misma forma de trabajo de la librería completa, la recomendación es compilar desde la raíz del proyecto:

    cd Libreria_cc232

Ese será el supuesto de todos los comandos de este README.

> En otras palabras:
> no entres a `Semana4/` para compilar si ya integraste la semana al repositorio.
> Entra a la raíz `Libreria_cc232/`, configura el proyecto una sola vez y luego compila o ejecuta los targets de la semana 4.

#### Aclaración sobre `build-debug`

El nombre de la carpeta `build-debug` es solo una convención.
No activa Debug por sí mismo.

Para compilar realmente en modo Debug:

- en Linux hay que pasar `-DCMAKE_BUILD_TYPE=Debug`
- en Windows con Visual Studio hay que usar `--config Debug`

#### Relación con las lecturas

Esta semana está alineada con el capítulo 4 de Deng: pilas, colas y aplicaciones.

En particular:

- `Stack` modela acceso LIFO y sirve como base para conversión de base, paréntesis, RPN y backtracking
- `Queue` modela acceso FIFO y sirve como base para la simulación bancaria
- la conversión de base compara un enfoque recursivo con uno iterativo
- la verificación de paréntesis muestra el paso de divide y vencerás a una solución lineal con pila
- la evaluación de expresiones usa una pila de operandos y otra de operadores
- N-Reinas y laberinto muestran cómo reemplazar recursión implícita por estructuras explícitas
- la simulación bancaria usa colas múltiples y selección de ventanilla mínima

### Linux

#### 1. Configurar todo el proyecto en modo Debug

    cd Libreria_cc232
    cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug

Este comando prepara el árbol de compilación completo del proyecto.

#### 2. Compilar solo la semana 4

Si quieres compilar únicamente los targets principales de esta semana:

    cmake --build build-debug --target \
      sem4_demo_stack_queue \
      sem4_demo_base_conversion \
      sem4_demo_paren_rpn \
      sem4_demo_nqueens \
      sem4_demo_maze \
      sem4_demo_bank \
      sem4_demo_capitulo4_panorama \
      sem4_test_public \
      sem4_test_internal

Si prefieres compilar todo el repositorio, usa:

    cmake --build build-debug

#### 3. Ejecutar todas las pruebas de la semana 4

    ctest --test-dir build-debug -R semana4 --output-on-failure

#### 4. Ejecutar los demos paso a paso

##### `Stack` y `Queue`

    ./build-debug/Semana4/sem4_demo_stack_queue

##### Conversión de base

    ./build-debug/Semana4/sem4_demo_base_conversion

##### Paréntesis y RPN

    ./build-debug/Semana4/sem4_demo_paren_rpn

##### N-Reinas

    ./build-debug/Semana4/sem4_demo_nqueens

##### Laberinto

    ./build-debug/Semana4/sem4_demo_maze

##### Simulación bancaria

    ./build-debug/Semana4/sem4_demo_bank

##### Panorama general del capítulo

    ./build-debug/Semana4/sem4_demo_capitulo4_panorama

### Windows (Visual Studio)

#### 1. Configurar todo el proyecto

    cd Libreria_cc232
    cmake -S . -B build-debug

#### 2. Compilar solo la semana 4 en modo Debug

    cmake --build build-debug --config Debug --target `
      sem4_demo_stack_queue `
      sem4_demo_base_conversion `
      sem4_demo_paren_rpn `
      sem4_demo_nqueens `
      sem4_demo_maze `
      sem4_demo_bank `
      sem4_demo_capitulo4_panorama `
      sem4_test_public `
      sem4_test_internal

Si prefieres compilar todo el repositorio, usa:

    cmake --build build-debug --config Debug

#### 3. Ejecutar todas las pruebas de la semana 4

    ctest --test-dir build-debug -C Debug -R semana4 --output-on-failure

#### 4. Ejecutar los demos paso a paso

##### `Stack` y `Queue`

    .\build-debug\Semana4\Debug\sem4_demo_stack_queue.exe

##### Conversión de base

    .\build-debug\Semana4\Debug\sem4_demo_base_conversion.exe

##### Paréntesis y RPN

    .\build-debug\Semana4\Debug\sem4_demo_paren_rpn.exe

##### N-Reinas

    .\build-debug\Semana4\Debug\sem4_demo_nqueens.exe

##### Laberinto

    .\build-debug\Semana4\Debug\sem4_demo_maze.exe

##### Simulación bancaria

    .\build-debug\Semana4\Debug\sem4_demo_bank.exe

##### Panorama general del capítulo

    .\build-debug\Semana4\Debug\sem4_demo_capitulo4_panorama.exe

### Targets principales

#### Demos

- `sem4_demo_stack_queue`
- `sem4_demo_base_conversion`
- `sem4_demo_paren_rpn`
- `sem4_demo_nqueens`
- `sem4_demo_maze`
- `sem4_demo_bank`
- `sem4_demo_capitulo4_panorama`

#### Pruebas

- `sem4_test_public`
- `sem4_test_internal`

### Compilación aislada de `Semana4`

Si todavía no integraste `Semana4` al `CMakeLists.txt` raíz, también puedes compilarla por separado desde su propia carpeta:

    cd Libreria_cc232/Semana4
    cmake -S . -B build
    cmake --build build
    ctest --test-dir build --output-on-failure

En ese caso, los ejecutables quedarán directamente dentro de `Semana4/build/`.
