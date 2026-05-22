### Semana 2

Esta semana introduce las primeras estructuras de datos dinámicas basadas en arreglos, con énfasis en memoria contigua, crecimiento de capacidad, costo amortizado y organización eficiente del acceso.
Además, se presentan variantes que permiten estudiar distintos trade-off entre simplicidad, costo de actualización y uso de memoria.

#### Temas trabajados

- Arreglos dinámicos
- Memoria contigua
- Resizing
- Análisis amortizado
- Arreglos circulares
- Deques y rebalanceo
- rootish arrays
- `fast sqrt` como apoyo matemático del capítulo 2
- vector estilo Deng como puente entre teoría y código de la semana

#### Estructuras cubiertas en esta versión

- `array`
- `ArrayStack`
- `FastArrayStack`
- `ArrayQueue`
- `ArrayDeque`
- `DualArrayDeque`
- `RootishArrayStack`
- `FastSqrt`
- `DengVector`

### Build

Desde la raíz de `Semana2`:

#### Linux/macOS o generadores single-config

```bash
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

#### Windows con Visual Studio o generadores multi-config

En Windows, cuando el proyecto se genera con Visual Studio u otro generador multi-config, `ctest` necesita que se indique explícitamente la configuración (`Debug` o `Release`).

```bash
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Si deseas compilar en `Release`:

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

#### Ejecutables

* `sem2_demo_array_basico`
* `sem2_demo_arraystack`
* `sem2_demo_fastarraystack`
* `sem2_demo_arrayqueue`
* `sem2_demo_arraydeque`
* `sem2_demo_dualarraydeque`
* `sem2_demo_rootisharraystack`
* `sem2_demo_fastsqrt`
* `sem2_demo_capitulo2_panorama`
* `sem2_demo_deng_vector`
* `sem2_demo_arraystack_explicado`: capacidad, desplazamientos e invariante
* `sem2_demo_rootisharraystack_explicado`: bloques, mapeo índice -> (bloque, offset) y crecimiento
* `sem2_demo_stl_vector_contraste`: contraste conceptual con `std::vector`

#### Pruebas

* `sem2_test_public`
* `sem2_test_internal`
* `sem2_resize_stress`
* `sem2_test_public_cap2`
* `sem2_test_internal_cap2`

#### Ejecución manual en Windows (Debug)

Si compilaste con:

```bash
cmake --build build --config Debug
```

entonces los ejecutables quedan dentro de `build/Debug/` o `build/Semana2/Debug/`, según el generador.

#### PowerShell o CMD

```powershell
.\build\Debug\sem2_demo_array_basico.exe
.\build\Debug\sem2_demo_arraystack.exe
.\build\Debug\sem2_demo_arraystack_explicado.exe
.\build\Debug\sem2_demo_fastarraystack.exe
.\build\Debug\sem2_demo_arrayqueue.exe
.\build\Debug\sem2_demo_arraydeque.exe
.\build\Debug\sem2_demo_dualarraydeque.exe
.\build\Debug\sem2_demo_rootisharraystack.exe
.\build\Debug\sem2_demo_rootisharraystack_explicado.exe
.\build\Debug\sem2_demo_fastsqrt.exe
.\build\Debug\sem2_demo_capitulo2_panorama.exe
.\build\Debug\sem2_demo_deng_vector.exe
.\build\Debug\sem2_demo_stl_vector_contraste.exe
.\build\Debug\sem2_test_public.exe
.\build\Debug\sem2_test_internal.exe
.\build\Debug\sem2_resize_stress.exe
.\build\Debug\sem2_test_public_cap2.exe
.\build\Debug\sem2_test_internal_cap2.exe
```

#### Git Bash

```bash
./build/Debug/sem2_demo_array_basico.exe
./build/Debug/sem2_demo_arraystack.exe
./build/Debug/sem2_demo_arraystack_explicado.exe
./build/Debug/sem2_demo_fastarraystack.exe
./build/Debug/sem2_demo_arrayqueue.exe
./build/Debug/sem2_demo_arraydeque.exe
./build/Debug/sem2_demo_dualarraydeque.exe
./build/Debug/sem2_demo_rootisharraystack.exe
./build/Debug/sem2_demo_rootisharraystack_explicado.exe
./build/Debug/sem2_demo_fastsqrt.exe
./build/Debug/sem2_demo_capitulo2_panorama.exe
./build/Debug/sem2_demo_deng_vector.exe
./build/Debug/sem2_demo_stl_vector_contraste.exe
./build/Debug/sem2_test_public.exe
./build/Debug/sem2_test_internal.exe
./build/Debug/sem2_resize_stress.exe
./build/Debug/sem2_test_public_cap2.exe
./build/Debug/sem2_test_internal_cap2.exe
```

#### Nota sobre `ctest` en Windows

Si aparece un mensaje como el siguiente:

```text
Test not available without configuration. (Missing "-C <config>"?)
```

eso no significa que los tests hayan fallado. Significa que `ctest` no sabe si debe buscar los ejecutables de prueba en `Debug` o en `Release`.

Usa:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

o, si compilaste en `Release`:

```bash
ctest --test-dir build -C Release --output-on-failure
```

#### Cobertura conceptual

Con estas piezas, la semana 2 queda preparada para explicar:

* Crecimiento dinámico de arreglos y costo de `resize`
* Diferencia entre costo individual y costo amortizado
* Ventajas de la memoria contigua
* Inserción y borrado con desplazamientos
* Uso de índices modulares en arreglos circulares
* Operaciones en colas, pilas y deques
* Estrategias de rebalanceo entre arreglos
* Representación por bloques en `RootishArrayStack`
* Constructor por copia, asignación y recorrido en un vector propio
* Relación entre diseño de estructura de datos y eficiencia

#### Enfoque de integración

`DengVector` vive como implementación paralela a Morin. No reemplaza `ArrayStack`, `FastArrayStack` ni `RootishArrayStack`; sirve para conectar los códigos del capítulo 2 de Deng con los invariantes y pruebas de la semana.
