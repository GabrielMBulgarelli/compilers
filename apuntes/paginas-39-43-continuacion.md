# Apuntes de Compiladores: continuación, páginas 39–43

Continúa [las páginas 29–38](paginas-29-38-continuacion.md). Se sigue la **numeración manuscrita**: `10797.jpg` es la página 39, `10810.jpg` la 40, `10798.jpg` la 41, `10799.jpg` la 42 y `10809.jpg` la 43. Se preservan los ejemplos y las afirmaciones del cuaderno; las discrepancias formales se identifican en notas, sin corregir silenciosamente la fuente.

## Página 39 — Concatenación y clausura de Kleene (`10797.jpg`)

### Propiedades de la concatenación de cadenas

- **Asociativa:** `vwx = (vw)x = v(wx)`.
- **No conmutativa en general:** `vw ≠ wv`.
- **Las longitudes se suman:** `|vw| = |v| + |w|`.
- **Elemento neutro:** `vε = εv = v`.

### Potencia de una hilera

Si `v` es una hilera sobre `Σ`, su potencia n-ésima consiste en concatenar `n` copias de `v`; se denota `vⁿ`. Caso especial: `v⁰ = ε`.

### Multiplicación de alfabetos (14/09/2026)

Sea `Σ = {0, 1}`. El cuaderno enumera:

- `Σ³ = {000, 001, 010, 011, 100, 101, 110, 111}`.
- `Σ² = {00, 01, 10, 11}`.
- `Σ¹ = {0, 1}`.
- `Σ⁰ = {ε}`.

La página escribe que `Σ*` reúne todas las hileras sobre `Σ` «tales que tengan una longitud de `k`». **Aclaración de lectura:** los ejemplos muestran que el conjunto de longitud exactamente `k` es `Σᵏ`; `Σ*` reúne todas las longitudes finitas.

### Conjunto `Σ*`

Definición recursiva anotada:

1. `ε ∈ Σ*`.
2. Si `w ∈ Σ*` y `a ∈ Σ`, entonces `wa ∈ Σ*`.
3. Una hilera pertenece a `Σ*` solo si puede construirse desde `ε` aplicando repetidamente el paso 2.

`Σ* = ⋃ᵢ₌₀^∞ Σⁱ`. El apunte señala que cada nivel `Σⁱ` es finito para un alfabeto finito, mientras que `Σ*` es infinito si el alfabeto no está vacío.

## Página 40 — Kleene, `Σ+` y reverso de una hilera (`10810.jpg`)

### Stephen Cole Kleene

«Ph.D. en Princeton, matemático que vivió entre 1909 y 1994. Uno de los creadores de los lenguajes formales y las expresiones regulares». El cierre de Kleene se denota `Σ*`.

Ejemplo de miembros de `Σ*` para `Σ = {0, 1}`: `{ε, 01, 001, 100, 110, …}`.

### Conjunto `Σ+`

Definición recursiva anotada:

1. Si `a ∈ Σ`, entonces `a ∈ Σ+`.
2. Si `w ∈ Σ+` y `a ∈ Σ`, entonces `wa ∈ Σ+`.
3. `w ∈ Σ+` solo si puede construirse a partir de un símbolo de `Σ` aplicando repetidamente el paso 2.

Relaciones escritas: `Σ+ = Σ* − {ε}` y `Σ* = Σ+ ∪ {ε}`. **Discrepancia del apunte:** la fórmula de unión situada junto a ellas parece comenzar en `i = 0`; para `Σ+` el índice debe comenzar en **1**, porque `Σ⁰ = {ε}`.

### Reverso de una hilera

Si `w ∈ Σ*`, la «reversa» de `w` se denota `wᴿ` o `w⁻¹`. El ejemplo manuscrito es `w = aaabc`, `wᴿ = cbaaa`.

**Teorema:** si `u, v ∈ Σ*`, entonces `(uv)ᴿ = vᴿuᴿ`. Ejemplo del cuaderno: `u = abc`, `v = def`; la reversa de `uv = abcdef` es `fedcba`.

## Página 41 — Lenguajes formales y unión (`10798.jpg`)

### Lenguaje formal

Sea `Σ` un alfabeto. Un lenguaje formal `L` sobre `Σ` es un conjunto de hileras: `L ⊆ Σ*`. Hay lenguajes finitos, infinitos y vacíos. El dibujo muestra `L` como un subconjunto dentro de `Σ*`.

### Ejemplos

1. Para `Σ = {0, 1}`:
   - `L₁`: hileras sobre `Σ` que terminan en `00`.
   - `L₂`: hileras sobre `Σ` que empiezan en `1`.
   - `L₃`: hileras sobre `Σ` de longitud impar.
2. Para `Σ = {A, U, C, G}`:
   - `L₁`: hileras sobre `Σ` que no incluyen `UUU`.
   - `L₂`: hileras sobre `Σ` cuya longitud es múltiplo de `3`.
   - `L₃`: hileras sobre `Σ` que empiezan por `AUG`, tienen longitud múltiplo de `3` y terminan en `UAA`, `UAG` o `UGA`.

### Operaciones sobre lenguajes formales: unión

Para lenguajes `L` y `M` sobre `Σ`, `L ∪ M = {x | x ∈ L o x ∈ M}`. El cuaderno añade que también puede denotarse `L + M` y que los conjuntos no repiten miembros.

## Página 42 — Unión, intersección y diferencia (`10799.jpg`)

### Unión: ejemplo y propiedades

Si `L` contiene las hileras sobre `Σ` que terminan en `00` y `M` las que empiezan en `1`, entonces `L ∪ M` contiene las que **terminan en `00` o empiezan en `1`**.

Propiedades anotadas: conmutativa (`L ∪ M = M ∪ L`), asociativa, idempotente (`L ∪ L = L`), elemento neutro `∅` y cierre (`L, M ⊆ Σ* ⇒ L ∪ M ⊆ Σ*`).

### Intersección de lenguajes

La intersección de `L` y `M` se denota `L ∩ M`; contiene las hileras que pertenecen a ambos.

**Ejemplo discreto:** `L = {000, 010, 100, 110}` y `M = {0, 1, 11}`. No comparten elementos, por lo que `L ∩ M = ∅`. **En la página se escribió `{∅}`**, que sería un conjunto con un elemento y no el resultado de la intersección de esos conjuntos.

**Ejemplo descriptivo:** con `L` formado por las hileras que terminan en `00` y `M` por las que comienzan en `1`, `L ∩ M` son las hileras que **empiezan en `1` y terminan en `00`**.

Propiedades anotadas: conmutativa, asociativa, idempotente, cierre, y `L ∩ ∅ = ∅`. **Nota formal:** la página dice «elemento neutro igual que la unión»; para intersección entre lenguajes sobre `Σ`, el neutro es `Σ*`, pues `L ∩ Σ* = L`.

### Diferencia de lenguajes

`L − M = {x | x ∈ L y x ∉ M}`: hileras de `L` que no están en `M`.

**Ejemplo:** `L = {1, 11, 111, 1111}` y `M = {0, 1, 11}`; por tanto `L − M = {111, 1111}`.

El último renglón vuelve al ejemplo de descripciones de hileras, pero contiene palabras superpuestas y queda truncado por el borde de la foto. No se infiere de esa línea una definición adicional.

## Página 43 — Diferencia, complemento, reverso y concatenación (`10809.jpg`)

### Propiedades de la diferencia

El cuadro indica: **no conmutativa**, **no asociativa**, **no idempotente**, y cierre en `Σ*`. Anota «elemento neutro: `∅`». **Precisión formal:** `L − ∅ = L`, pero `∅ − L = ∅`; por eso `∅` solo es neutro **por la derecha**, no por ambos lados.

### Complemento de lenguajes

El complemento de `L` sobre `Σ` se denota `L̅` y está definido por:

`L̅ = {x | x ∈ Σ* y x ∉ L} = Σ* − L`.

**Ejemplos:**

- Si `Σ = {0, 1}` y `L = {000, 010, 100, 110}`, entonces `L̅ = Σ* − {000, 010, 100, 110}`.
- Si `L` es el conjunto de hileras binarias que terminan en `00`, `L̅` contiene las hileras binarias que **no** terminan en `00`.

Propiedades anotadas: `complemento(Σ*) = ∅`, `complemento(complemento(L)) = L`, y cierre para `L ⊆ Σ*`.

### Inverso o reverso de un lenguaje

El apunte lo denota `L⁻¹`: el conjunto formado al invertir el orden de los símbolos de cada hilera de `L`. Con la notación de la página 40, `L⁻¹ = {xᴿ | x ∈ L}`.

**Ejemplo:** si `L = {000, 010, 100, 110}`, entonces `L⁻¹ = {000, 010, 001, 011}`. Se anota cierre y que esta operación «no es idempotente» en general. Aplicarla dos veces devuelve `L`.

### Concatenación de lenguajes

Se denota `LM` y se define como `LM = {xw | x ∈ L y w ∈ M}`: se forma concatenando una hilera de `L` con una hilera de `M`. La frase final continúa fuera de esta página.

---

**Estado de la secuencia:** páginas **1–43** transcritas; este archivo incorpora las **39–43**. Las notas de discrepancia distinguen lo escrito en el cuaderno de la formulación matemática correcta.

**Continuación:** [páginas 44–50 y hoja posterior](paginas-44-50-continuacion.md).
