# Respuestas Obligatorias - PC3 (Codeforces 817F - MEX Queries)

## Preguntas y retos específicos por problema (Codeforces 817F)

**1. ¿Cómo representas rangos cubiertos o invertidos?**
Se representan mediante un Treap donde cada nodo almacena un intervalo disjunto `[l, r]`. Si un número pertenece a un intervalo del árbol, significa que su valor actual es 1 (cubierto). Los valores 0 no se almacenan, se representan implícitamente como los "huecos" entre los nodos.

**2. ¿Cómo se obtiene el menor entero positivo ausente (MEX)?**
Aprovechando la propiedad de BST del Treap, se busca el nodo más a la izquierda (el mínimo). Si este nodo empieza en 1 (`l <= 1`), el MEX es estrictamente el límite superior de dicho bloque más uno (`r + 1`), lo cual está garantizado por el invariante de fusión. Si el nodo mínimo empieza en un valor $>1$ o el Treap está vacío, el MEX es directamente 1.

**3. ¿Qué caso rompe una solución que actualiza punto por punto?**
El límite de las consultas donde $L, R \le 10^{18}$. Actualizar un tramo tan masivo iterando punto por punto causaría *Time Limit Exceeded* (TLE) y *Memory Limit Exceeded* (MLE) inmediatamente.

---

## 11. Preguntas comunes obligatorias

**1. ¿Cuál es el problema exacto asignado?**
Codeforces 817F - MEX Queries. Consiste en procesar consultas masivas para agregar (llenar con 1s), remover (llenar con 0s) o invertir (1s a 0s y 0s a 1s) rangos de elementos, reportando el menor entero positivo ausente (MEX) después de cada operación.

**2. ¿Qué recibe la entrada y qué produce la salida?**
Recibe un entero $N$ seguido de $N$ operaciones compuestas por (Tipo de Operación, $L$, $R$). Produce como salida el MEX del conjunto tras ejecutar cada consulta.

**3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
Los valores de las coordenadas pueden llegar hasta $10^{18}$.

**4. ¿Cuál sería la solución ingenua y cuál es su complejidad?**
Usar un arreglo booleano o un `std::set` e iterar elemento por elemento desde $L$ hasta $R$ para actualizarlos, y luego iterar desde 1 para buscar el MEX. Su complejidad sería $O(R)$ por operación, lo que es inmanejable.

**5. ¿Qué estructura de datos elegiste?**
Un Treap de intervalos disjuntos. Es una adaptación de un árbol balanceado donde cada nodo comprime un rango entero continuo `[l, r]`.

**6. ¿Qué estructura de la librería cc232 se parece más?**
Se basa directamente en el `Treap.h` de la Semana 6 (árbol balanceado por prioridades aleatorias tipo Heap) combinado con la lógica de búsqueda de rangos de los árboles BST de la Semana 5.

**7. ¿Qué operación domina el tiempo?**
La recolección de nodos que se solapan mediante las búsquedas de `lowerBound` y el recorrido con `successor`. 

**8. ¿Qué invariante mantiene tu estructura?**
El Invariante de Disyunción y Orden: No existen dos intervalos en el árbol que se toquen (ej. `[1,2]` y `[3,4]`) o se solapen. Siempre están estrictamente separados y ordenados.

**9. ¿Dónde se actualiza ese invariante en el código?**
En los bucles `while` de las funciones `addInterval`, `removeInterval` e `invertInterval`. Allí se recalcan los límites (`newL`, `newR`) y se eliminan los nodos viejos/superpuestos antes de insertar los nuevos nodos recortados o fusionados.

**10. ¿Qué caso borde puede romper una solución superficial?**
Consultar el MEX cuando no se ha insertado ningún elemento (debe retornar 1 de forma segura) o aplicar una operación de inversión que divida un solo nodo en tres partes diferentes.

**11. ¿Cómo manejas duplicados, empates o elementos obsoletos?**
Al insertar un rango sobre uno que ya existe (duplicados), el algoritmo recolecta los nodos obsoletos en un arreglo temporal (`toRemove`), los extrae físicamente del Treap usando `removeNode` y los reemplaza por un solo nodo grande consolidado.

**12. ¿Cuál es la complejidad temporal por operación?**
Es $O(\log M + K \log M)$ amortizado, donde $M$ es la cantidad de intervalos vivos en el árbol y $K$ es el número de intervalos afectados/solapados por la consulta.

**13. ¿Cuál es la complejidad total?**
$O(N \log N)$ amortizado en el peor de los casos para procesar todas las operaciones.

**14. ¿Cuál es la complejidad espacial?**
$O(M)$, acotado por $O(N)$, ya que en el peor caso cada operación crea a lo sumo un par de intervalos disjuntos nuevos en memoria.

**15. ¿Qué parte del código sería más fácil de romper?**
Recorrer el árbol con iteradores/punteros mientras simultáneamente se borran nodos. Se solucionó recolectando primero los punteros en un `std::vector` y borrándolos en una fase posterior.

**16. ¿Qué alternativa de estructura existe y qué perderías con ella?**
Un *Dynamic Segment Tree* o usar *Lazy Propagation* con compresión de coordenadas. Se perdería la simplicidad del manejo dinámico de memoria, y obligaría a leer todos los datos primero (procesamiento *offline*) para comprimir coordenadas.

**17. ¿Qué prueba propia escribiste?**
Una prueba de inversión con solapamientos (ej. Añadir `[1, 10]` y luego Invertir `[5, 15]`), validando que el Treap divida correctamente el rango interno y el MEX retorne 5.

**18. ¿Qué cambiaste durante el bloque sin cortes?**
*(Nota para el video: Imprimí el estado lógico del Treap (recorrido in-order de los rangos) tras agregar una operación de fusión y partición de intervalos, mostrando cómo el árbol actualiza el MEX).*

**19. ¿Cómo sabes que el cambio no rompió la solución?**
Porque la modificación (impresión del estado interno) fue de solo lectura. Se recompiló, se ejecutó y la salida final hacia Codeforces no se vio afectada, manteniendo la estructura disjunta.

**20. ¿Qué demuestra que no es una solución de caja negra?**
Que no se usó `std::set` con `lower_bound`. Se programó a mano la representación interna (`Node`), la gestión de memoria (`insertNode`, `removeNode`), la búsqueda por punteros (`lowerBound`, `successor`) y la auto-organización logarítmica con prioridades aleatorias (`bubbleUp`, `trickleDown`).