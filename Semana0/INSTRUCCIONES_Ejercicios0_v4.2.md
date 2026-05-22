### Instrucciones de uso

Este archivo explica cómo ejecutar los experimentos de `Ejercicios0.md` usando el script `resolver_ejercicios0_v4.2.sh` y el programa base `stl_optimizacion_demostracion.cpp`.

#### 1. Archivos que debes tener en la misma carpeta

Coloca estos archivos juntos en una misma carpeta de trabajo:

- `Ejercicios0.md`
- `resolver_ejercicios0_v4.2.sh`
- `stl_optimizacion_demostracion.cpp`

Ejemplo:

```bash
Semana0/
├── Ejercicios0.md
├── resolver_ejercicios0_v4.2.sh
└── stl_optimizacion_demostracion.cpp
```

También puedes tener otros archivos en la carpeta, pero esos tres son los importantes para este laboratorio.

#### 2. Qué hace el script

El script automatiza los experimentos pedidos en `Ejercicios0.md`.

Según el enunciado, los ejercicios incluyen:

1. escalera de optimización
2. comparación STL con el algoritmo correcto
3. LTO
4. PGO
5. sanitizers
6. cobertura con `gcov`
7. cobertura de condiciones y caminos
8. warnings dependientes de optimización
9. profiling con `gprof`
10. checklist final de medición

El archivo `stl_optimizacion_demostracion.cpp` es el programa base para los experimentos principales, en especial el experimento STL del punto 2.

#### 3. Cómo abrir la terminal

##### En Windows

Si usas MSYS2, abre preferentemente **UCRT64**.

##### En Linux o WSL

Abre una terminal normal y entra a la carpeta del laboratorio.

#### 4. Dar permiso de ejecución al script

En Git Bash, MSYS2, WSL o Linux:

```bash
chmod +x resolver_ejercicios0_v4.2.sh
```

#### 5. Ver la ayuda del script

Para ver los ejercicios disponibles:

```bash
./resolver_ejercicios0_v4.2.sh help
```

#### 6. Ejecutar todos los ejercicios

```bash
./resolver_ejercicios0_v4.2.sh all
```

Esto genera binarios, logs y un reporte dentro de la carpeta:

```bash
ejercicios0_out/
```

#### 7. Ejecutar ejercicio por ejercicio

Puedes correr un solo experimento indicando su número.

##### Ejercicio 1: escalera de optimización

```bash
./resolver_ejercicios0_v4.2.sh 1
```

##### Ejercicio 2: STL y algoritmo correcto

```bash
./resolver_ejercicios0_v4.2.sh 2
```

##### Ejercicio 3: LTO

```bash
./resolver_ejercicios0_v4.2.sh 3
```

##### Ejercicio 4: PGO

```bash
./resolver_ejercicios0_v4.2.sh 4
```

##### Ejercicio 5: sanitizers

```bash
./resolver_ejercicios0_v4.2.sh 5
```

##### Ejercicio 6: cobertura con `gcov`

```bash
./resolver_ejercicios0_v4.2.sh 6
```

##### Ejercicio 7: cobertura de condiciones y caminos

```bash
./resolver_ejercicios0_v4.2.sh 7
```

##### Ejercicio 8: warnings dependientes de optimización

```bash
./resolver_ejercicios0_v4.2.sh 8
```

##### Ejercicio 9: profiling con `gprof`

```bash
./resolver_ejercicios0_v4.2.sh 9
```

##### Ejercicio 10: resumen final

```bash
./resolver_ejercicios0_v4.2.sh 10
```

#### 8. También puedes usar aliases

El script acepta aliases además de números.

Ejemplos:

```bash
./resolver_ejercicios0_v4.2.sh opt
./resolver_ejercicios0_v4.2.sh stl
./resolver_ejercicios0_v4.2.sh pgo
./resolver_ejercicios0_v4.2.sh san
./resolver_ejercicios0_v4.2.sh cov
./resolver_ejercicios0_v4.2.sh gprof
```

#### 9. Cómo funciona el archivo base

Por defecto, el script busca el archivo:

```bash
stl_optimizacion_demostracion.cpp
```

en la **misma carpeta donde está el script**.

Si ese archivo está en otro lugar, puedes pasarlo explícitamente así:

```bash
./resolver_ejercicios0_v4.2.sh ./stl_optimizacion_demostracion.cpp 2
```

O con una ruta completa:

```bash
./resolver_ejercicios0_v4.2.sh C:/ruta/al/archivo/stl_optimizacion_demostracion.cpp 2
```

#### 10. Dónde quedan los resultados

Todos los resultados quedan en:

```bash
ejercicios0_out/
```

Dentro de esa carpeta encontrarás:

- ejecutables generados
- archivos `.log`
- salidas estándar y de error
- el reporte principal:

```bash
ejercicios0_out/reporte_ejercicios0.md
```

#### 11. Qué revisar después de cada ejecución

Después de correr un ejercicio, revisa:

1. la salida mostrada en terminal
2. el archivo `reporte_ejercicios0.md`
3. los logs de compilación si aparece algún error

Por ejemplo, si falla un ejercicio, el script normalmente indica qué archivo revisar, como:

- `O0.compile.log`
- `stl_demo.compile.log`
- `demo_asan_ubsan.compile.log`
- `gcov_summary.txt`
- `gprof.stderr.txt`

#### 12. Observaciones importantes sobre Windows

En Windows con Git Bash o MSYS2 pueden aparecer limitaciones del entorno.

Ejemplos comunes:

- `ASan`, `UBSan` o `TSan` pueden no enlazar correctamente
- `gcov` puede requerir ajustes extra según el entorno
- `gprof` puede fallar o no generar perfiles útiles

Por eso:

- para compilar normalmente: **UCRT64** suele ser la mejor opción en MSYS2
- para sanitizers, cobertura y profiling: **WSL Ubuntu** o Linux nativo suele funcionar mejor

#### 13. Recomendación didáctica 

Orden sugerido de trabajo:

1. correr `2` para ver primero el experimento STL principal
2. luego correr `1` para comparar niveles de optimización
3. después `3` y `4` para LTO y PGO
4. finalmente `5`, `6`, `7` y `9` para correctitud, cobertura y profiling
5. cerrar con `10`

#### 14. Ejemplo de sesión completa

```bash
chmod +x resolver_ejercicios0_v4.2.sh
./resolver_ejercicios0_v4.2.sh help
./resolver_ejercicios0_v4.2.sh 2
./resolver_ejercicios0_v4.2.sh 1
./resolver_ejercicios0_v4.2.sh 5
./resolver_ejercicios0_v4.2.sh 6
./resolver_ejercicios0_v4.2.sh 9
```

#### 15. Qué entregar

Una entrega mínima podría incluir:

- capturas o texto de la terminal
- `ejercicios0_out/reporte_ejercicios0.md`
- breve comentario de qué observó el estudiante en cada ejercicio
- nota de limitaciones del entorno si trabajó en Windows

#### 16. Resumen corto

Si tienes los archivos separados, basta con poner en una misma carpeta:

- `Ejercicios0.md`
- `resolver_ejercicios0_v4.2.sh`
- `stl_optimizacion_demostracion.cpp`

Luego ejecutar:

```bash
chmod +x resolver_ejercicios0_v4.2.sh
./resolver_ejercicios0_v4.2.sh help
./resolver_ejercicios0_v4.2.sh 2
./resolver_ejercicios0_v4.2.sh all
```

