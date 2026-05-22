### Preguntas de sustentación - Semana 1

Esta sustentación busca verificar que el estudiante no solo ejecuta programas, sino que también comprende qué es un algoritmo, cómo se justifica su correctitud, cómo se analiza su costo y cómo se relacionan estas ideas con las implementaciones de la semana.

#### 1. Concepto formal de algoritmo

1. ¿Qué es un algoritmo y qué condiciones debe cumplir para ser considerado correcto y útil?
2. Explica con tus palabras las nociones de:
   - entrada,
   - salida,
   - determinismo,
   - factibilidad,
   - finitud,
   - corrección.
3. Da un ejemplo de procedimiento que no califique como algoritmo y explica por qué.
4. ¿Por qué la corrección por sí sola no basta para considerar bueno a un algoritmo?
5. ¿Qué relación hay entre especificación e implementación?

#### 2. Bubblesort como caso de estudio

6. ¿Qué problema resuelve `bubble_sort` y cuál es su entrada y salida esperadas?
7. Explica la diferencia entre orden local y orden global.
8. ¿Por qué comparar e intercambiar elementos adyacentes ayuda a construir el orden global?
9. ¿Qué significa hacer un escaneo del arreglo en bubblesort?
10. Enuncia una invariante razonable para bubblesort.
11. ¿Qué significa decir que bubblesort es monótono respecto al desorden?
12. ¿Cómo justificarías la finitud de bubblesort?
13. ¿Cómo justificarías su correctitud sin revisar línea por línea el código?
14. ¿Qué ocurre en el mejor caso y en el peor caso de bubblesort?
15. ¿Por qué bubblesort es útil pedagógicamente aunque no sea el algoritmo más eficiente?

#### 3. Calidad práctica de los algoritmos

16. ¿Qué significa que un algoritmo sea robusto?
17. Menciona casos borde que deberían considerarse en funciones de esta semana.
18. ¿Qué entiendes por degeneración de un algoritmo o de un caso de ejecución?
19. ¿Qué significa reutilización en este contexto?
20. ¿Cómo influye una buena interfaz en la reutilización de una implementación?
21. Elige una función de la semana y explica cómo mejorarías su robustez.

#### 4. Eficiencia y estructuras de datos

22. ¿Qué diferencia hay entre que un problema sea computable y que sea tratable en la práctica?
23. ¿Qué significa eficiencia computacional?
24. ¿Por qué no basta decir "funciona"? ¿Por qué también importa cuánto tiempo y memoria consume?
25. ¿Qué relación existe entre algoritmos y estructuras de datos?
26. Da un ejemplo de cómo una mala representación de datos puede perjudicar el rendimiento.
27. ¿Cómo conecta esta semana con el estudio posterior de estructuras de datos?

#### 5. Medición de complejidad

28. ¿Qué es complejidad temporal?
29. ¿Qué es complejidad espacial?
30. ¿Qué significa analizar el costo de un algoritmo en función del tamaño de entrada?
31. ¿Por qué se usan funciones asintóticas en vez de medir solo tiempo real en segundos?
32. ¿Qué limitaciones tiene medir rendimiento únicamente con pruebas empíricas?
33. Da un ejemplo simple de costo temporal lineal y uno constante con funciones de la semana.

#### 6. Notaciones asintóticas

34. Explica la diferencia entre:
   - O grande,
   - Ω grande,
   - Θ grande.
35. ¿Qué representa el peor caso?
36. ¿Qué representa el mejor caso?
37. ¿Qué representa el caso promedio?
38. ¿Por qué dos algoritmos con la misma salida correcta pueden no ser igual de buenos?
39. ¿Cómo describirías informalmente el crecimiento de bubblesort con respecto a `n`?

#### 7. Niveles de complejidad

40. Ordena y comenta estos crecimientos de menor a mayor:
   - O(1),
   - O(log n),
   - O(n),
   - O(n^2),
   - O(2^n).
41. ¿Por qué una diferencia pequeña en la fórmula puede ser enorme cuando `n` crece?
42. ¿Qué papel juega el tamaño de entrada en el análisis?
43. ¿Por qué los algoritmos exponenciales suelen volverse inviables rápidamente?
44. ¿Qué significa decir que existe una jerarquía de complejidades?

#### 8. Recursión

45. ¿Qué es recursión?
46. ¿Cuál es la diferencia entre una definición recursiva correcta y una incorrecta?
47. ¿Qué papel cumple el caso base?
48. ¿Qué significa "disminuir y conquistar"?
49. ¿Cómo analizarías una función recursiva mediante trazado?
50. ¿Qué es una ecuación de recurrencia?
51. ¿Qué diferencia hay entre recursión lineal y recursión con múltiples direcciones?
52. Da un ejemplo de la semana con múltiples bases o múltiples llamadas recursivas.
53. ¿Qué ventajas y qué riesgos tiene la recursión frente a la iteración?
54. ¿Cuándo preferirías una solución iterativa y cuándo una recursiva?

#### 9. Preguntas aplicadas al código de la semana

55. Explica por qué `power(a, n)` puede ser mejor que una versión ingenua como `powerBF(a, n)`.
56. Compara una versión iterativa y una recursiva de Fibonacci en términos de claridad y costo.
57. ¿Qué costo temporal esperas para `fibI(n)` y por qué?
58. ¿Qué hace `count_ones` y cómo justificarías su correctitud?
59. En `max_algorithms`, ¿qué significa que un valor sea máximo y cómo se prueba que el algoritmo lo encuentra?
60. En `reverse_utils`, ¿qué propiedad debe preservarse al invertir o desplazar elementos?
61. ¿Qué idea matemática sostiene a `gcd`?
62. ¿Por qué `hanoi` es un buen ejemplo de recursión?
63. Elige una función de la semana y explica:
   - especificación,
   - idea del algoritmo,
   - correctitud,
   - costo temporal,
   - casos borde.

#### Preguntas integradoras

64. Explica cómo pasar de una especificación informal a una defensa de correctitud.
65. Relaciona correctitud, robustez y eficiencia en un mismo ejemplo.
66. ¿Por qué bubblesort sirve como puente entre correctitud y análisis de complejidad?
67. ¿Qué aporta la recursión al diseño algorítmico en esta semana?
68. ¿Qué aprendizaje conceptual de la semana consideras más importante y por qué?.
