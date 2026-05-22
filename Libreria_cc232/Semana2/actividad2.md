## Actividad 2-CC232

### Integrantes
- Oscar Alberto Pomalia Suyo
- Brian Jair La Torre Urbina

#### Bloque 1 

1. **Memoria contigua:** Significa que los elementos de la estructura están almacenados en posiciones de memoria físicamente adyacentes, una tras otra. Esto permite que el hardware acceda de forma extremadamente rápida a los datos.
2. **Acceso A[i] en O(1):** Debido a la contigüidad, la dirección de cualquier elemento se calcula con una fórmula aritmética simple: `dirección = base + (i * tamaño_del_tipo)`. Al ser un cálculo directo, el tiempo es constante independientemente de `i`.
3. **Size vs Capacity:** `size` representa la cantidad de elementos reales almacenados actualmente, mientras que `capacity` es el tamaño total del bloque de memoria reservado en el heap.
4. **Resize() y reserva nueva:** Los arreglos no pueden crecer "en el mismo sitio" porque la memoria adyacente podría estar ocupada por otros datos. Por ello, se debe reservar un bloque nuevo de mayor tamaño, copiar los elementos y liberar el bloque antiguo.
5. **Costo amortizado O(1):** Al duplicar la capacidad, la operación costosa de copiado (O(n)) ocurre con poca frecuencia. Si repartimos ese costo total entre todas las inserciones que lo precedieron, el promedio por operación resulta ser constante (O(1)).
6. **ArrayStack y DengVector:** Comparten la representación base de un arreglo dinámico. `ArrayStack` (Morin) se enfoca en la lógica algorítmica simplificada, mientras que `DengVector` (Deng) enfatiza la implementación robusta tipo C++ con manejo de memoria y interfaces más completas.
7. **Mejora de FastArrayStack:** Optimiza el rendimiento mediante el uso de funciones de bajo nivel como `std::copy` o `memmove`, que mueven bloques de memoria a nivel de hardware más rápido que un bucle `for` manual.
8. **Idea de RootishArrayStack:** Su objetivo es reducir el desperdicio de espacio (memoria no utilizada) manteniendo la interfaz de lista, utilizando una serie de bloques en lugar de un solo arreglo masivo.
9. **Bloques 1, 2, 3...:** Esta progresión permite que el desperdicio de espacio sea solo de $O(\sqrt{n})$, ya que el último bloque es el único que puede estar parcialmente vacío.
10. **Tríada Representación-Costo-Espacio:** La representación contigua favorece el tiempo de acceso (O(1)) a cambio de un costo de redimensionamiento que debe amortizarse y un desperdicio espacial que estructuras como `Rootish` intentan minimizar.

#### Bloque 2

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
| :--- | :--- | :--- | :--- |
| `demo_arraystack_explicado.cpp` | Trazas de desplazamiento de elementos. | Desplazamiento manual en `add/remove`. | El costo es $O(n-i)$ por los desplazamientos necesarios. |
| `demo_fastarraystack.cpp` | Tiempos de ejecución reducidos. | Uso de `std::copy`. | Mejora la constante de tiempo del sistema. |
| `demo_rootisharraystack.cpp` | Mapeo de índice a bloque y offset. | Estructura de bloques incrementales. | Desperdicio espacial reducido a $O(\sqrt{n})$. |
| `demo_deng_vector.cpp` | Saltos en la capacidad (`capacity`). | Crecimiento exponencial (duplicación). | Justifica el costo amortizado $O(1)$. |

**Respuestas:**
- **demo_arraystack_explicado.cpp:** Muestra claramente el costo de mover elementos uno a uno al insertar en posiciones iniciales.
- **demo_rootisharraystack_explicado.cpp:** Es la mejor para explicar cómo un índice lógico se traduce a una ubicación física en bloques.
- **Amortización vs Espacio:** `demo_deng_vector.cpp` es ideal para defender la amortización (por el crecimiento exponencial), mientras que `demo_rootisharraystack.cpp` defiende mejor el uso eficiente del espacio.

#### Bloque 3 

1. **Operaciones mínimas:** Valida `get(i)`, `set(i, x)`, `add(i, x)` y `remove(i)` bajo condiciones normales de uso.
2. **Prueba pública:** Demuestra que la estructura cumple con su contrato básico de funcionalidad y correctitud observable para el usuario.
3. **Lo que NO demuestra:** No garantiza que la complejidad asintótica sea la correcta (podrías tener un $O(n)$ en lugar de un $O(1)$ y pasar el test si el $n$ es pequeño) ni detecta fugas de memoria sutiles.
4. **resize_stress_week2.cpp:** Evalúa la estabilidad de la estructura ante ráfagas masivas de inserciones y eliminaciones que fuerzan múltiples redimensionamientos.

#### Bloque 4 

1. **_size, _capacity, _elem:** `_elem` es el puntero al bloque de datos, `_size` es la cantidad de datos válidos y `_capacity` el tamaño total disponible.
2. **expand():** Debe ejecutarse siempre que `_size == _capacity` antes de intentar insertar un nuevo elemento.
3. **Copia profunda:** Se evidencia en la demo cuando se asigna un vector a otro y ambos mantienen estados independientes tras modificaciones.
4. **Traverse():** Permite aplicar una operación a todos los elementos, facilitando la validación y el procesamiento uniforme.

#### Bloque 5 

1. **Bloques:** Los elementos se reparten en bloques donde el bloque $k$ tiene capacidad para $k+1$ elementos.
2. **Capacidad total:** Sigue la suma de una progresión aritmética (Gauss), resultando en $r(r+1)/2$ para $r$ bloques.
3. **i2b(i):** Resuelve la ecuación cuadrática para encontrar el índice del bloque correspondiente a un índice lógico `i` en tiempo $O(1)$.
4. **Espacio:** Se gana eficiencia frente a `ArrayStack` porque el espacio desperdiciado nunca supera el tamaño del último bloque, es decir, $O(\sqrt{n})$.

#### Bloque 6 

1. **operator[]:** Aporta la interfaz intuitiva de arreglo, permitiendo que el vector se use sintácticamente igual que un arreglo nativo.
2. **find(e):** Supone que los elementos soportan el operador de igualdad (`==`) para realizar la búsqueda secuencial.
3. **Traverse():** Muestra cómo desacoplar la lógica de recorrido de la lógica de procesamiento de los datos.

#### Bloque 7

Pasar de "usar un arreglo" a "diseñar una estructura dinámica" implica un cambio radical en la **representación**: dejamos de manejar memoria estática para gestionar un puntero a memoria dinámica en el heap que debe redimensionarse. La **correctitud** se garantiza encapsulando la lógica de `resize()`, la cual, aunque costosa individualmente (O(n)), se justifica mediante un **costo amortizado** $O(1)$ al duplicar la capacidad.

En términos de **uso de espacio**, estructuras como `ArrayStack` y `FastArrayStack` aceptan un desperdicio de hasta $O(n)$ para ganar velocidad. En contraste, `RootishArrayStack` utiliza un mapeo matemático de bloques para reducir ese desperdicio a $O(\sqrt{n})$. Mientras `FastArrayStack` mejora el rendimiento práctico mediante operaciones de memoria en bloque, `RootishArrayStack` ofrece el mejor balance teórico entre acceso rápido y eficiencia espacial.

#### Autoevaluación breve
- Qué podemos defender con seguridad: La lógica del costo amortizado y la implementación de inserciones con desplazamientos.
- Qué todavía confundimos: La deducción matemática exacta de la fórmula cuadrática para el índice del bloque en `RootishArrayStack`.
- Qué evidencia usaríamos en una sustentación: Los resultados de `resize_stress_week2.cpp` para demostrar que la estructura no falla ante cambios de escala masivos.