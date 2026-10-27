# Esbozo original de solución del quiz

**Remitente:** Francisco Torres <torresrojas.cursos.02@gmail.com>  
**Enviado:** 2026-10-13T16:30:31-06:00  
**Recibido:** 2026-10-13T16:30:55-06:00  
**Fuente:** [[COM-UCR] Esbozo de solución del Quiz](https://mail.google.com/mail/u/0/#all/1a13763e15fa9c6b)

## Texto del correo

1a) Agregamos un nuevo estado X (de rechazo). Todos los estados de aceptación de la máquina original se conectan con transiciones epsilon al estado X, y se cambian a estados de rechazo. Todas las flechas del autómata se reversan de dirección (i.e., si iban del estado I al estado J, ahora van del estado J al estado I). El estado X que agregamos será el nuevo estado inicial del DFA, y el viejo estado inicial de la máquina será el único estado de aceptación.

---

1b) X - Y = X intersección con Y complementado. X es regular, Y es regular, Y complementado es regular, X intersección Y complementado es regular. Por tanto X - Y es regular.

---

1c) Dado un entero N, hay N casos posibles de divisibilidad con respecto a N (i.e., números de la forma k\*N, o de la forma K\*N + 1,o de la forma K\*N + 2, etc. Al tomar N+1 números enteros arbitrarios y querer clasificarlos en N categorías, al menos 2 de ellos caen en la misma, al restarlos la diferencia es un número múltiplo de N.

---

1d) Basta con dividir el cuadrado de borde 2 en 4 cuadrados de borde 1.

```text
+----------+----------+
|             |            |
+----------+----------+
|             |            |
+----------+----------+
```

Al escoger 5 puntos aleatorios dentro del cuadrado de borde 2, al menos 2 estarán en el mismo cuadrado de borde 1. En estos cuadraditos la máxima distancia es la diagonal la cual mide (por Pitágoras) raíz cuadrada de 2.

---

1e) Si tomamos los primeros N enteros, con N impar, es fácil notar que si N = 2k + 1, hay k números pares y k+1 números impares. Hago un reacomodo arbitrario de estos N números (A1, A2, ... AN). Hay 3 casos posibles:

I) Algún número quedó en la misma posición que tenía originalmente, lo que haría que al menos un factor del producto es 0, el resultado es 0 y es par.

o...

II) Nadie quedó en su posición original, pero si a algún número par le resto una posición par, tendemos un factor par, y el gran producto es par.

o....

III) A todos los k números pares les restaron k números impares, pero como hay k + 1 impares, sobra al menos una posición impar que le resta a un número impar, dando al menos un factor par (porque impar - impar es par), y haciendo par al gran producto.
