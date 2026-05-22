### Actividad 1 - Semana 1 

* Duración: 3 horas de clase.
* Modalidad: Trabajo en parejas.
* Tiempo de instalación: 15 minutos al inicio.
* Entrega: Un archivo llamado `actividad1_semana1.md`.

#### Objetivo

Consolidar la Semana 1 a partir de código, demos, pruebas y una defensa escrita breve. La meta es distinguir con claridad problema, algoritmo, ADT e implementación, justificar correctitud básica, identificar qué se mide realmente cuando hablamos de costo 
y empezar a separar evidencia conceptual de evidencia experimental.

#### Archivos a usar

##### Núcleo principal

* `Semana1/README.md`
* `Semana1/src/bubble_sort.cpp`
* `Semana1/src/power.cpp`
* `Semana1/src/fibonacci.cpp`
* `Semana1/src/count_ones.cpp`
* `Semana1/demos/demo_bubblesort.cpp`
* `Semana1/demos/demo_power.cpp`
* `Semana1/demos/demo_fibonacci.cpp`
* `Semana1/demos/demo_countones.cpp`
* `Semana1/demos/demo_adt_secuencia.cpp`
* `Semana1/pruebas_publicas/README.md`
* `Semana1/pruebas_publicas/test_public_week1.cpp`
* `Semana1/pruebas_publicas/test_public_week1_extra.cpp`
* `Semana1/sustentacion/preguntas_semana1.md`
* `Semana1/sustentacion/rubrica_semana1.md`

##### Enlace común

* `Proyecto0/apps/demo_const_refs.cpp`
* `Proyecto0/bench/bench_vector_growth.cpp`
* `Proyecto0/bench/bench_vector_ops.cpp`
* `Proyecto0/bench/bench_cache_effects.cpp`

#### Extensión breve

* `Ejercicios0.md`
* `INSTRUCCIONES_Ejercicios0_v4.2.md`
* `stl_optimizacion_demostracion.cpp`
* `resolver_ejercicios0_v4.2.sh`

#### Bloque 0 - Instalación y preparación

1. Dejen lista su carpeta de trabajo.
2. Verifiquen que pueden abrir `Semana1`, `Proyecto0`, `Ejercicios0.md`, `INSTRUCCIONES_Ejercicios0_v4.2.md`, `stl_optimizacion_demostracion.cpp` y `resolver_ejercicios0_v4.2.sh`.
3. Creen el archivo `actividad1_semana1.md`.
4. Anoten los nombres de los integrantes.

#### Bloque 1 - Núcleo conceptual de Semana1

Revisen:

* `Semana1/README.md`
* `Semana1/src/bubble_sort.cpp`
* `Semana1/src/power.cpp`
* `Semana1/src/fibonacci.cpp`
* `Semana1/src/count_ones.cpp`
* `Semana1/demos/demo_adt_secuencia.cpp`

Respondan:

1. Expliquen con sus palabras la diferencia entre **problema**, **algoritmo**, **ADT** e **implementación**.
2. En `bubble_sort.cpp`, expliquen qué observable conecta correctitud y costo.
3. En `power.cpp`, expliquen por qué `power` mejora la idea de una versión ingenua.
4. En `fibonacci.cpp`, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.
5. En `count_ones.cpp`, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.
6. En `demo_adt_secuencia.cpp`, expliquen por qué la misma interfaz puede convivir con representaciones distintas.

#### Bloque 2 - Demos y trazado guiado

Revisen:

* `Semana1/demos/demo_bubblesort.cpp`
* `Semana1/demos/demo_power.cpp`
* `Semana1/demos/demo_fibonacci.cpp`
* `Semana1/demos/demo_countones.cpp`

Construyan una tabla con cuatro columnas:

* archivo,
* salida u observable importante,
* idea algorítmica,
* argumento de costo.

Luego respondan:

1. En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?
2. En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?
3. En `demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?
4. En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?

#### Bloque 3 - Pruebas públicas y preparación de sustentación

Revisen:

* `Semana1/pruebas_publicas/README.md`
* `Semana1/pruebas_publicas/test_public_week1.cpp`
* `Semana1/pruebas_publicas/test_public_week1_extra.cpp`
* `Semana1/sustentacion/preguntas_semana1.md`
* `Semana1/sustentacion/rubrica_semana1.md`

Respondan:

1. ¿Qué funciones o ideas están verificando las pruebas públicas?
2. ¿Qué sí demuestra una prueba pública?
3. ¿Qué no demuestra una prueba pública?
4. Elijan **una** pregunta de `preguntas_semana1.md` y respóndanla bien.
5. Usen la rúbrica para autoevaluarse en:

   * comprensión conceptual,
   * sustentación de correctitud,
   * análisis de eficiencia.


#### Bloque 4 - Puente corto con Proyecto0

Revisen:

* `Proyecto0/apps/demo_const_refs.cpp`
* `Proyecto0/bench/bench_vector_growth.cpp`
* `Proyecto0/bench/bench_vector_ops.cpp`
* `Proyecto0/bench/bench_cache_effects.cpp`

Respondan brevemente:

1. ¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?
2. En `bench_vector_growth.cpp`, ¿qué cambia con `reserve`?
3. En `bench_vector_ops.cpp`, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?
4. En `bench_cache_effects.cpp`, ¿qué intuición deja sobre localidad de memoria?

#### Bloque 5 - Extensión breve con Ejercicios0

Revisen:

* `Ejercicios0.md`
* `INSTRUCCIONES_Ejercicios0_v4.2.md`
* `stl_optimizacion_demostracion.cpp`
* `resolver_ejercicios0_v4.2.sh`

Respondan:

1. Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?
2. ¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?
3. ¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?
4. ¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?
5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?

### Bloque 6 - Cierre comparativo

Respondan esta pregunta final:

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**

La respuesta debe incluir obligatoriamente:

* una afirmación de especificación,
* una afirmación de correctitud,
* una afirmación de costo,
* una afirmación de representación o memoria,
* una advertencia metodológica.


#### Formato sugerido de entrega

```md
## Actividad 1- CC232

### Integrantes
- Nombre 1
- Nombre 2

#### Bloque 1
(respuestas)

#### Bloque 2
(tabla y respuestas)

#### Bloque 3
(respuestas)

#### Bloque 4
(respuestas)

#### Bloque 5
(respuestas)

#### Bloque 6
(respuesta final)

#### Autoevaluación breve
- Qué podemos defender con seguridad:
- Qué todavía confundimos:
- Qué evidencia usaríamos en una sustentación:
```

#### Criterio general de trabajo

Se espera lectura real de los archivos, respuestas breves pero justificadas, y conexión explícita entre código, correctitud, costo, representación y evidencia.
