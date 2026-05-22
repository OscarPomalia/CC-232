## Pruebas unitarias, `assert`, AAA y TDD en C++ para CC232

### 1. ¿Qué es una prueba unitaria?

Una **prueba unitaria** verifica una pieza pequeña del programa, por ejemplo:

* una función como `sum`, `power` o `gcdCN`
* una operación de una estructura de datos como `add`, `remove`, `get` o `set`

En cursos como **CC232**, esto sirve para comprobar que los algoritmos y ADT's funcionan de manera **correcta, repetible y aislada**.


### 2. ¿Qué es `assert`?

`assert` es una macro de comprobación en tiempo de ejecución.
Se usa para verificar que una condición sea verdadera. Si falla, el programa se detiene. En C++, `assert` es una macro y su comportamiento depende de `NDEBUG`, además `static_assert` sirve para validaciones en compilación. ([Cppreference][1])

#### Ejemplo básico

```cpp
#include <cassert>

int main() {
    int x = 2 + 2;
    assert(x == 4);
}
```

### 3. Patrón AAA: Arrange, Act, Assert

AAA significa:

* **Arrange**: preparar datos y contexto
* **Act**: ejecutar la operación
* **Assert**: verificar el resultado

Es un patrón muy útil para escribir pruebas claras y ordenadas. ([Google GitHub][2])

#### Plantilla general

```cpp
// Arrange
// preparar datos

// Act
// ejecutar función o método

// Assert
// comprobar resultado
```

### 4. ¿Qué es TDD?

**TDD** significa **Test-Driven Development**.
La idea es:

1. escribir una prueba que falle
2. escribir el mínimo código para que pase
3. refactorizar

En un curso como CC232, TDD ayuda a que el estudiante piense primero en el **comportamiento esperado** antes de programar la solución completa.

### 5. Recursos recomendados

#### Recursos oficiales y útiles

* **`assert` en cppreference**: buena referencia para entender cómo funciona `assert`, cuándo se desactiva y cómo se diferencia de `static_assert`. ([Cppreference][1])
* **GoogleTest Primer**: explica el modelo básico de pruebas y las aserciones `EXPECT_*` y `ASSERT_*`. ([Google GitHub][2])
* **GoogleTest Quickstart con CMake**: útil cuando quieras migrar de `assert` a un framework formal. ([Google GitHub][3])
* **Catch2 Documentation**: framework de pruebas para C++ con sintaxis simple, útil para cursos y TDD. ([Catch2][4])
* **Tutorial oficial de CTest**: muy importante porque CMake integra `enable_testing()` y `add_test()` para descubrir y ejecutar pruebas. ([CMake][5])

#### Recomendación práctica

Para **CC232**, conviene aprender en este orden:

1. `assert`
2. patrón AAA
3. `CTest`
4. GoogleTest o Catch2

Ese orden reduce fricción y hace que el foco siga siendo el algoritmo, no la herramienta.

### 6. Ejemplos tomados de la librería del curso

Tus archivos ya traen material muy bueno para enseñar pruebas, por ejemplo en `Semana1/pruebas_publicas/test_public_week1.cpp` y `test_public_week1_extra.cpp` ya hay pruebas
con `assert`. En la semana 2 aparecen estructuras y pruebas para:

* `ArrayStack`
* `FastArrayStack`
* `RootishArrayStack`
* `ArrayQueue`
* `ArrayDeque`
* `DualArrayDeque`
* `DengVector`

Además, el `CMakeLists.txt` ya usa `include(CTest)` y `add_test(...)`, así que el curso puede conectar naturalmente con **CTest**. CMake integra pruebas mediante `enable_testing()` y `add_test()`, y `ctest` actúa como ejecutor de pruebas del árbol generado. ([CMake][5])

#### 7. Ejemplo 1: prueba con `assert` usando `sum`

Basado en el estilo de `Semana1/pruebas_publicas/test_public_week1.cpp`:

```cpp
#include <cassert>
#include "sum.h"

int main() {
    // Arrange
    int a[] = {1, 2, 3, 4};

    // Act
    int r1 = sumI(a, 4);
    int r2 = sum(a, 4);
    int r3 = sum(a, 0, 4);

    // Assert
    assert(r1 == 10);
    assert(r2 == 10);
    assert(r3 == 10);

    return 0;
}
```

#### Qué enseña este ejemplo

* una misma especificación puede validarse sobre varias implementaciones
* una prueba debe ser pequeña
* el resultado esperado debe quedar explícito.

#### 8. Ejemplo 2: prueba con `power`

Basado en `Semana1/pruebas_publicas/test_public_week1.cpp`:

```cpp
#include <cassert>
#include "power.h"

int main() {
    // Arrange
    long long base = 2;
    int exponente = 10;

    // Act
    long long r1 = powerBF(base, exponente);
    long long r2 = power(base, exponente);
    long long r3 = power2(exponente);

    // Assert
    assert(r1 == 1024);
    assert(r2 == 1024);
    assert(r3 == 1024);

    return 0;
}
```

#### Qué enseña este ejemplo

* comparar versión ingenua vs. optimizada
* comprobar equivalencia funcional
* usar pruebas para validar mejoras algorítmicas.

#### 9. Ejemplo 3: prueba con `reverseRecursive` y `shiftLeftByK`

Basado en `Semana1/pruebas_publicas/test_public_week1_extra.cpp`:

```cpp
#include <cassert>
#include "reverse_utils.h"

int main() {
    // Arrange
    int c[] = {1, 2, 3, 4, 5};

    // Act
    reverseRecursive(c, 5);

    // Assert
    assert(c[0] == 5 && c[4] == 1);

    // Act
    shiftLeftByK(c, 5, 2);

    // Assert
    int expected[] = {3, 2, 1, 5, 4};
    for (int i = 0; i < 5; ++i) {
        assert(c[i] == expected[i]);
    }

    return 0;
}
```

#### Qué enseña este ejemplo

* probar algoritmos que modifican arreglos
* verificar estado final, no solo valor de retorno
* usar arreglos esperados para comparar resultado.

#### 10. Ejemplo 4: prueba de estructura de datos con `ArrayStack`

Basado en `Semana2/pruebas_publicas/test_public_week2.cpp`:

```cpp
#include <cassert>
#include "ArrayStack.h"

int main() {
    // Arrange
    ods::ArrayStack<int> s;
    s.add(1);
    s.add(2);

    // Act
    s.add(1, 99);

    // Assert
    assert(s.size() == 3);
    assert(s.get(0) == 1);
    assert(s.get(1) == 99);
    assert(s.get(2) == 2);

    // Act
    int borrado = s.remove(1);

    // Assert
    assert(borrado == 99);
    assert(s.size() == 2);

    return 0;
}
```

#### Qué enseña este ejemplo

* probar inserción intermedia
* verificar tamaño y contenido
* comprobar contrato de `remove`

#### 11. Ejemplo 5: prueba con `ArrayQueue` y `DengVector`

Basado en `Semana2/pruebas_publicas/test_public_capitulo2_extendido.cpp`:

```cpp
#include <cassert>
#include "ArrayQueue.h"
#include "DengVector.h"

namespace {
void increaseByOne(int& x) {
    ++x;
}
}

int main() {
    // Queue
    ods::ArrayQueue<int> q;
    q.add(1);
    q.add(2);
    q.add(3);

    assert(q.remove() == 1);
    assert(q.remove() == 2);

    q.add(4);

    assert(q.remove() == 3);
    assert(q.remove() == 4);

    // Vector
    ods::DengVector<int> v;
    assert(v.empty());

    v.insert(0, 10);
    v.insert(1, 30);
    v.insert(1, 20);

    assert(v.size() == 3);
    assert(v[0] == 10 && v[1] == 20 && v[2] == 30);
    assert(v.find(20) == 1);
    assert(v.find(99) == -1);

    v.traverse(increaseByOne);
    assert(v[0] == 11 && v[1] == 21 && v[2] == 31);

    return 0;
}
```

#### 12. Cómo conectar esto con CTest

Como en la `Semana2/CMakeLists.txt` ya aparece `include(CTest)` y `add_test(...)`, puedes ejecutar pruebas con **CTest**. 
CMake configura la infraestructura de pruebas con `enable_testing()` o `include(CTest)`, y luego `add_test()` registra los ejecutables que `ctest` correrá. ([CMake][5])

#### Esquema típico

```cmake
include(CTest)

add_executable(mi_test test_algo.cpp)
add_test(NAME prueba_algo COMMAND mi_test)
```

Luego:

```bash
ctest
```

### Ventaja para CC232

* separa compilación y ejecución de pruebas
* permite tener varias pruebas organizadas
* prepara el camino para integrar GoogleTest después

#### 13. Cómo se vería el mismo enfoque con GoogleTest

GoogleTest organiza pruebas en suites y usa macros como `EXPECT_EQ` y `ASSERT_EQ`; `EXPECT_*` produce fallo no fatal y `ASSERT_*` fallo fatal. ([Google GitHub][2])

```cpp
#include <gtest/gtest.h>
#include "sum.h"

TEST(SumTest, FourElementsReturns10) {
    int a[] = {1, 2, 3, 4};

    EXPECT_EQ(sumI(a, 4), 10);
    EXPECT_EQ(sum(a, 4), 10);
    EXPECT_EQ(sum(a, 0, 4), 10);
}
```

#### Cuándo usarlo

Úsalo cuando quieras:

* reportes más claros
* varias suites de prueba
* integración más profesional con CMake

El quickstart oficial con CMake muestra cómo enlazar `GTest::gtest_main` y descubrir pruebas automáticamente con `gtest_discover_tests(...)`. ([Google GitHub][3])


[1]: https://en.cppreference.com/w/cpp/error/assert.html "assert"
[2]: https://google.github.io/googletest/primer.html "GoogleTest Primer"
[3]: https://google.github.io/googletest/quickstart-cmake.html "Quickstart: Building with CMake | GoogleTest"
[4]: https://catch2-temp.readthedocs.io/ "Catch2 documentation"
[5]: https://cmake.org/cmake/help/latest/guide/tutorial/Testing%20and%20CTest.html "Step 8: Testing and CTest"
