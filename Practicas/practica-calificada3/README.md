### PC3 - CC232

#### Estudiante
- Nombre: Oscar Alberto Pomalia Suyo
- Código: 20240385I
- Problema asignado: Codeforces 817F - MEX Queries
- Enlace oficial: https://codeforces.com/problemset/problem/817/F

#### Referencia oficial
- CSV oficial: https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6
- Semana principal: Semanas 5 y 6
- Estructura usada: Treap de Intervalos Disjuntos (Lazy Concept)
- Estructura de la librería `cc232` relacionada: `Treap.h` y `BST`

#### Resumen de la solución
El problema requiere actualizar rangos de hasta 10^18. Para evitar TLE, comprimimos la información usando un Treap donde cada nodo representa un intervalo disjunto `[L, R]` de valores presentes. Al insertar, remover o invertir, fusionamos o partimos los intervalos. El MEX es siempre el primer hueco no cubierto desde 1.

#### Compilación
```bash
cmake -S . -B build
cmake --build build