# Apuntes de Compiladores: páginas 44–50 y hoja siguiente

Continúa [las páginas 39–43](paginas-39-43-continuacion.md). Se sigue la **numeración manuscrita**: `10800.jpg` a `10805.jpg` son las páginas 44–49; `10807.jpg` es la 50. `10806.jpg` continúa el ejercicio de la página 50, pero **su número de página no es visible**. Los esquemas se pasan a texto y tablas cuando las flechas se distinguen; las discrepancias se señalan expresamente.

## Página 44 — Concatenación, potencias y cierre de lenguajes (`10800.jpg`)

### Concatenación de lenguajes: ejemplos

Con `L = {000, 010, 100, 110}` y `M = {0, 1, 11}`, el ejemplo enumera:

`LM = {0000, 0001, 00011, 0100, 0101, 01011, 1000, 1001, 10011, 1100, 1101, 11011}`.

Aunque dos concatenaciones distintas puedan producir la misma hilera, el conjunto resultante no repite miembros.

Si `L` es el conjunto de hileras binarias que terminan en `00` y `M` el de las que empiezan en `1`, las hileras de `LM` admiten una partición `xy` en la que `x` termina en `00` y `y` empieza en `1`; por eso contienen `001` en el punto de unión. El apunte ilustra esa forma con ejemplos de hileras.

**Propiedades anotadas:** la concatenación de lenguajes es **asociativa**, no conmutativa en general, no idempotente en general, tiene elemento neutro `{ε}` y es cerrada en `Σ*`.

### Potencia de un lenguaje

`L¹ = L`, `L² = LL`, `L³ = LLL` y, en general, `Lⁿ` concatena `n` hileras tomadas de `L`. El caso base es `L⁰ = {ε}`.

Para `L = {000, 010, 100, 110}`, se listan miembros de `L²`, como `000000`, `000010`, `000100`, `000110`, `110000`, `110010`, `110100` y `110110`.

El apunte también toma `M = {000, 010, 100, 110, ε}` y observa que `M²` incluye las concatenaciones de dos hileras de longitud tres, las hileras originales (al concatenar con `ε`) y `ε`.

**Relaciones:** `Lⁿ = Lⁿ⁻¹L = LLⁿ⁻¹` para `n ≥ 1`; si `L ⊆ Σ*`, entonces `Lⁿ ⊆ Σ*`.

### Cierre de Kleene de un lenguaje

`L* = ⋃ₙ₌₀^∞ Lⁿ = L⁰ ∪ L¹ ∪ L² ∪ ⋯`. Por incluir `L⁰`, siempre `ε ∈ L*`. En el margen inferior se anota `L* ∪ {ε} = L*`.

## Página 45 — Reconocedores, generadores y autómatas finitos (`10801.jpg`)

### Mecanismos de lenguajes formales

**Reconocedor de `L`:** acepta o rechaza hileras; acepta únicamente las de `L` y no rechaza ninguna hilera de `L`.

**Generador de `L`:** genera todas las hileras de `L` y no genera las que no pertenecen a `L`.

**Autómatas finitos determinísticos (17/09/2026).** Procesan hileras y las aceptan o rechazan. Siempre hay un estado actual.

**Estructura dibujada:** nodos que representan estados, arcos que representan transiciones, etiquetas sobre los arcos y dos tipos de nodos (ordinarios y de aceptación). Un estado de aceptación se dibuja con doble círculo.

**Mecánica:** se consume un símbolo a la vez y se pasa a otro estado o al mismo según el estado actual y el símbolo. Los estados son finitos; para cada par estado–símbolo hay un siguiente estado único. El texto indica que si faltan transiciones, la hilera se rechaza; para un DFA **formal y total**, esos casos se representan con transiciones a un estado de rechazo. Si el estado inicial es de aceptación, `ε` también se acepta.

Los dibujos de esta página muestran ejemplos de nodos, flechas etiquetadas `0` y `1`, y dos posibles recorridos; uno lleva la nota «`w = ε` se acepta».

## Página 46 — Definición formal de DFA y representación (`10802.jpg`)

Un DFA se define como la quíntupla **`M = (Q, Σ, δ, q₀, F)`**:

1. `Q`: conjunto finito de estados.
2. `Σ`: alfabeto.
3. `δ: Q × Σ → Q`: función de transición.
4. `q₀ ∈ Q`: estado inicial.
5. `F ⊆ Q`: conjunto de estados de aceptación.

**Ejemplo dibujado:** `Q = {a, b, c, d}`, `Σ = {0, 1}`, `F = {d}`. La flecha inicial apunta a `a`; el renglón que indica `q₀` se parece a «`d`», lo que contradice la flecha. Según el **diagrama**, `q₀ = a`.

La tabla de transiciones que se obtiene del diagrama es:

| Estado | `0` | `1` |
| --- | --- | --- |
| `a` | `b` | `a` |
| `b` | `b` | `c` |
| `c` | `d` | `a` |
| `d` | `d` | `d` |

**Implementación de un DFA.** Se mencionan nodos y transiciones, o una tabla de filas (estados) y columnas (símbolos), con el contenido correspondiente al siguiente estado. Un controlador general en C recibiría una tabla de transiciones, un vector de aceptación/rechazo, un puntero o posición en la hilera y el estado inicial.

## Página 47 — Lenguaje reconocido y diseño de DFA (`10803.jpg`)

Sea `M = (Q, Σ, δ, q₀, F)` y `w = w₁w₂⋯wₙ` una hilera sobre `Σ`. El DFA acepta `w` si existe una secuencia `r₀,r₁,⋯,rₙ` tal que:

1. Cada `rᵢ ∈ Q`.
2. `r₀ = q₀`.
3. `δ(rᵢ,wᵢ₊₁) = rᵢ₊₁` para `i = 0,⋯,n−1`.
4. `rₙ ∈ F`.

**Nota de transcripción:** el índice del estado usado en la condición 3 es poco nítido y puede leerse `r₀`; la condición coherente con la secuencia es `rᵢ`.

`L(M) = {w | M acepta w}`: conjunto de hileras reconocido por la máquina.

**Diseño:** se describe un lenguaje y se construye un DFA que acepte exactamente sus hileras. Hay que aceptar las que pertenecen al lenguaje y rechazar las demás. De cada estado debe salir una transición para cada símbolo del alfabeto, y la máquina debe tener un número finito de estados. Si `ε ∈ L`, el estado inicial debe aceptar.

**Ejemplo:** sobre `Σ = {0,1}`, diseñar un DFA para las hileras que **terminan en `1`**. El dibujo usa dos estados: `q₁` inicial y no aceptante; `q₂` aceptante. `q₁` se queda con `0` y va a `q₂` con `1`; `q₂` se queda con `1` y vuelve a `q₁` con `0`.

## Página 48 — Ejemplos de DFA (`10804.jpg`)

1. **Hileras que no terminan en `1`**, sobre `{0,1}`: los mismos dos estados y transiciones del ejemplo anterior, cambiando el conjunto de aceptación a `{q₁}`. Así se acepta también `ε`.
2. **Hileras que terminan en `01`**: el texto manuscrito parece decir `001`, pero el dibujo tiene `q₁ --0→ q₂ --1→ q₃`, con `q₂ --0→ q₂`, `q₃ --0→ q₂`, `q₁ --1→ q₁` y `q₃ --1→ q₁`. Ese DFA acepta las hileras que terminan en **`01`**; si el enunciado fuese `001`, el dibujo sería insuficiente. `q₃` es de aceptación.
3. **Hileras que no terminan en `00`**: `q₁` (inicial) y `q₂` son de aceptación; `q₃` rechaza. En `1` se vuelve a `q₁` desde cualquier estado; en `0`, `q₁→q₂→q₃` y `q₃` permanece en sí mismo.
4. **Hileras sobre `{A,T,C,G}` cuya longitud es múltiplo de tres**: el dibujo forma un ciclo de tres estados; cualquiera de las cuatro letras avanza una posición. La marca de aceptación no está clara en esta figura. Para incluir `ε`, se acepta el estado inicial (longitud `0 mod 3`); esta es una precisión formal respecto al dibujo.

## Página 49 — Módulo de longitud, subhilera prohibida y extremos (`10805.jpg`)

### Longitud que no sea múltiplo de cuatro

`Σ = {0,1}`. El diagrama tiene cuatro estados en ciclo, y cada símbolo de `Σ` avanza al siguiente. El estado inicial (longitud `0 mod 4`) rechaza; los estados de longitudes congruentes con `1`, `2` y `3 mod 4` aceptan.

### Hileras que no contienen la subhilera `GAGA`

`Σ = {A,T,C,G}`. El dibujo marca cinco estados, de los cuales los primeros cuatro aceptan y el quinto es sumidero de rechazo. El estado representa cuánto del prefijo `GAGA` coincide con el sufijo de lo leído:

| Estado | Progreso observado | `A` | `T` o `C` | `G` |
| --- | --- | --- | --- | --- |
| `q₁` | Nada | `q₁` | `q₁` | `q₂` |
| `q₂` | `G` | `q₃` | `q₁` | `q₂` |
| `q₃` | `GA` | `q₁` | `q₁` | `q₄` |
| `q₄` | `GAG` | `q₅` | `q₁` | `q₂` |
| `q₅` | Ya apareció `GAGA` | `q₅` | `q₅` | `q₅` |

Esta tabla explicita las flechas del diagrama; el rótulo de una de las flechas de retorno se ve tenue. La nota del autor dice que hace falta una heurística para construir casos así y pregunta cuál funciona y cuándo.

### Primer y último símbolo iguales

`Σ = {0,1}`. El estado inicial separa los casos según el **primer símbolo**; en cada rama dos estados registran si el **último símbolo** coincide con ese primero. Los estados correspondientes a «empezó en `0` y termina en `0`» y «empezó en `1` y termina en `1`» aceptan. El ejemplo siguiente pregunta por hileras que **no** terminan con el mismo símbolo con que empezaron y anota: «Igual al anterior, pero con estados de éxito opuestos».

**Matiz:** el estado inicial para `ε` también necesita una decisión explícita, pues la hilera vacía no tiene primer ni último símbolo.

## Página 50 — Condición sobre `CC` y números divisibles por 3 (`10807.jpg`)

### Condición de subhilera

`Σ = {A,T,C,G}`: diseñar un DFA para hileras que **no contengan `CC`**, donde toda `A` esté precedida por una `T`. La página contiene dos esquemas tentativos, marcas «GA → invalidan», «falta G,A» y «complicado». Algunas flechas se superponen o están incompletas; no se presenta una tabla total verificable. Se conserva el **enunciado**, sin convertir esos bosquejos en un DFA terminado.

### Número decimal divisible por 3

`Σ = {0,1,2,3,4,5,6,7,8,9}`: las hileras representan números en base `10` divisibles por `3`. Se indica como **convención del ejercicio** que `ε = 0`. El análisis separa los residuos `0`, `1` y `2`; «ser divisible» es tener residuo `0` o ser de la forma `3k`.

Si el número leído vale `n` y se agrega el dígito `q` a su derecha, el valor pasa a `10n + q`. La última pregunta plantea qué sucede al concatenar `0` a un número que ya era divisible por `3`; continúa en la hoja siguiente.

## Hoja posterior a la página 50 — Número no visible (`10806.jpg`)

### Continuación: divisibilidad por 3

El dibujo tiene tres estados: residuos `0` (aceptante), `3k+1` y `3k+2`. Agrupa los dígitos según su residuo:

- `D₀ = {0,3,6,9}`.
- `D₁ = {1,4,7}`.
- `D₂ = {2,5,8}`.

Como `10n+q ≡ n+q (mod 3)`, al leer un dígito del grupo `Dⱼ` desde residuo `r`, el siguiente residuo es `(r+j) mod 3`. La nota manuscrita menciona la regla de la suma de dígitos múltiplo de tres como heurística.

| Residuo actual | `D₀` | `D₁` | `D₂` |
| --- | --- | --- | --- |
| `0` | `0` | `1` | `2` |
| `1` | `1` | `2` | `0` |
| `2` | `2` | `0` | `1` |

### Número en base 3 no divisible por 5

Se plantea un DFA con estados de residuos `0,1,2,3,4` módulo `5`, sobre los dígitos `{0,1,2}`. El diagrama de cinco estados tiene varias flechas y rótulos superpuestos. El comentario dice que, sin razonamiento previo, el ejercicio toma más de una hora y que la heurística parece similar. **Regla que permite verificar o completar el bosquejo:** al agregar el dígito `d` a un número `n` en base 3, su nuevo residuo es `(3r+d) mod 5`; para «no divisible entre 5», se aceptan los residuos `1,2,3,4`. El estado `0` rechaza, salvo que otra convención sobre `ε` se indique explícitamente.

### Paridad de `A` y `B`

`Σ = {A,B}`: diseñar un DFA para hileras con un **número par de `A`** y un **número impar de `B`**. El dibujo combina cuatro estados, rotulados por la paridad de cada símbolo:

| Paridad de `A`, paridad de `B` | Al leer `A` | Al leer `B` | ¿Acepta? |
| --- | --- | --- | --- |
| Par, par (inicial) | Impar, par | Par, impar | No |
| Impar, par | Par, par | Impar, impar | No |
| Par, impar | Impar, impar | Par, par | Sí |
| Impar, impar | Par, impar | Impar, par | No |

La nota final dice que, al cambiar cuáles combinaciones de paridad se desean, se conservan las transiciones y se modifican los estados de aceptación.

---

**Estado de la secuencia:** páginas **1–50** numeradas y **una hoja posterior sin número visible** transcritas. Este tramo incorpora DFA y varios ejercicios de diseño; los diagramas incompletos se distinguen de las tablas verificables.
