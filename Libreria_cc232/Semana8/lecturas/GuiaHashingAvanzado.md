# Guía de hashing avanzado

## 1. Encadenamiento separado

Cada cubeta almacena una lista de elementos con la misma dirección hash. Es simple, tolera cargas mayores que 1 y evita tombstones. Su problema aparece cuando una cubeta crece demasiado.

Indicadores útiles:

- `loadFactor()`
- `longestBucket()`
- `collisions`

## 2. Direccionamiento abierto

Todos los elementos viven dentro del arreglo. Cuando una posición está ocupada, se aplica una secuencia de sondeo.

Variantes incluidas:

- Linear probing: `h(x) + i`
- Quadratic probing: `h(x) + i^2`
- Double hashing: `h1(x) + i*h2(x)`
- Robin Hood hashing: intercambia elementos para reducir desigualdad en desplazamientos

## 3. Tombstones

En open addressing, una celda eliminada debe seguir indicando que la búsqueda no debe detenerse allí. Por eso se marca como `Deleted` o se usa un bitmap de eliminación perezosa.

Diferenciar:

```text
active load factor   = elementos activos / capacidad
occupied load factor = (activos + eliminados perezosos) / capacidad
```

## 4. Rehashing

Rehashing reconstruye la tabla cuando hay demasiada carga o demasiados tombstones. En esta semana se controla mediante `RehashPolicy`.

## 5. Universal hashing

Una familia universal reduce la dependencia de una única función hash fija. En esta carpeta se incluye una variante MAD:

```text
h(x) = ((a * code(x) + b) mod p) mod m
```

## 6. Métricas mínimas de informe

Para cada técnica, reportar:

- capacidad final,
- factor de carga activo,
- factor ocupado si aplica,
- colisiones,
- longitud máxima de sondeo,
- promedio de sondeo,
- cantidad de rehashings,
- tombstones.
