# Bitácora de Desarrollo - PC3

## Día 1: Análisis y Configuración Inicial
* **Problema asignado:** Codeforces 817F - MEX Queries.
* **Análisis:** El problema requiere actualizar rangos masivos (hasta $10^{18}$) y consultar el menor entero ausente (MEX). Actualizar elemento por elemento causará TLE.
* **Decisión técnica:** Utilizaré una adaptación de la estructura `Treap` (Semana 6) combinada con conceptos de `BST` (Semana 5). Cada nodo representará un intervalo disjunto `[L, R]` de números presentes.
* **Avance:** Configuración de carpetas (`include`, `src`, `docs`) y creación del archivo CMakeLists.txt inicial.

## Día 2: Diseño de Estructura e Invariantes
* **Avance técnico:** Creación del archivo `include/IntervalTreap.h`. Se definió el esqueleto de la clase `IntervalTreap` y su `Node`.
* **Invariantes definidos:**
  1. *Invariante de búsqueda (BST):* El límite superior (`r`) de cualquier intervalo en el subárbol izquierdo es estrictamente menor al límite inferior (`l`) del nodo actual. No hay solapamientos.
  2. *Invariante de prioridad (Heap):* La prioridad de un nodo padre es siempre menor o igual a la de sus hijos, garantizando altura logarítmica esperada.
* **Mecánica agregada:** Implementación de las funciones de soporte `rotateLeft`, `rotateRight` y control de memoria `clear`.
* **Próximo paso (Día 3):** Implementar la lógica para dividir (split) y fusionar (merge) intervalos cuando una consulta interseca parcialmente un nodo.

## Día 3: Lógica de Fusión Disjunta e Inserción
* **Avance técnico:** Implementación de `addInterval`, `lowerBound`, `successor` y mantenimiento del Treap (`bubbleUp`, `trickleDown`, `insertNode`, `removeNode`).
* **Justificación de la lógica (Codeforces 817F):** Para evitar la actualización punto por punto (que daría TLE con $10^{18}$), la función `addInterval(L, R)` busca todos los nodos existentes que se solapen o sean adyacentes al nuevo rango usando `lowerBound(L - 1)`. 
  Dos intervalos `[a,b]` y `[c,d]` se tocan/solapan si `max(a,c) <= min(b,d) + 1`. Si hay choque, el algoritmo elimina los nodos viejos, absorbe sus límites (`newL`, `newR`) e inserta un único gran intervalo fusionado.
* **Invariante protegido:** Esto garantiza que el Treap solo contenga intervalos 100% disjuntos y ordenados.
* **Próximo paso (Día 4):** Implementar la lógica inversa (`removeInterval`) cortando los nodos que se solapen, la función `invertInterval` y el cálculo del `MEX`.
* **Infraestructura:** Se añadió el `CMakeLists.txt`, el `src/main.cpp` y el `README.md` oficial para cumplir con la estructura de proyecto requerida y permitir la compilación con CMake.