# Apuntes de Compiladores: continuación, páginas 29–38

Continúa [las páginas 20–28](paginas-20-28-continuacion.md). Se sigue la **numeración manuscrita** de las fotografías. La página 36 corresponde a `10811.jpg`, aunque ese nombre no siga la secuencia de los demás archivos. Se transcribe el apunte de clase con puntuación y diagramas adaptados a Markdown; se señalan las partes ambiguas. Las definiciones y los ejemplos se conservan como figuran en el cuaderno, sin presentarlos como una corrección técnica independiente.

## Página 29 — *Linker*, *loader* y *debugger* (`10788.jpg`)

### *Linker*

El *linker* responde a referencias externas. ¿Existe dinámico y estático? ¿DDL o DLL?

`Source File → Object → Linker → Executable Program`

Una *runtime library* aparece como otra entrada al *linker* en el diagrama.

### *Loader*

**Definición.** Es como dice el nombre: un cargador. Toma un módulo ejecutable y lo carga en memoria. ¿Realiza algo más? Un compilador, no. El compilador crea un mapa de relocalización. El *loader* solo se usa luego de aplicar un ejecutable; toma un ejecutable y lo carga en memoria [el apunte repite la idea].

Fijo MMU y, al parecer, debo conocer también PCB. Negocia espacio y crea estructuras de control. Crea el PCB. *Schedulable* [término anotado junto a PCB].

Agrupación:

`Compiler (source) → Linker (linkable) → Loader (imagen linkable) → Executable Image`

### *Debugger*

**Definición.** Permiten la ejecución en forma controlada de otro programa. Para que un *debugger* funcione, necesita que el compilador brinde información y el sistema operativo trabaje [la oración termina allí en la fotografía].

## Página 30 — Características, *profiler*, editor de texto y versiones (`10789.jpg`)

### Características [del *debugger*, por continuidad]

- Instrucción a instrucción.
- Usa e implementa *breakpoints*.
- Ver el contenido de variables.
- Relación fuerte con lenguaje máquina.

### *Profiler*

**Definición.** Programa que recolecta estadísticas de un programa, como el número de veces que cada función es llamada, con el porcentaje de ejecución en lugares del programa. Se usa para mejorar la calidad de programas ejecutados. Reescribe funciones en ensamblador o mejora el diseño. Necesita información creada por el compilador.

Compilador se beneficia de datos recaudados por el *profiler* [en el cuaderno hay una palabra tachada antes de «profiler»].

### Editor de texto

**Definición.** Hay programas fuente escritos con editores de texto; usan técnicas de compilación, expresiones regulares y código cargado para detectar proyectos. Puede informar errores sintácticos.

Editores de propósito general. IDE = *integrated development environment*.

**Manejador de versiones.** Registra versiones de código y maneja la distribución de archivos; coordina versiones de las fuentes. Documenta quién hizo qué y cuándo. Puede ser independiente del lenguaje.

## Página 31 — Estructura básica, análisis y síntesis (`10790.jpg`)

**Semana 4 — Clase 6 (07/09/26). Compiladores: estructura básica.**

`Entrada → Salida` y `Fuente → Compilador → Objeto`.

**Representación intermedia.** Según el apunte, «escribe el *backend* antes del IR y el *frontend* va después» [se transcribe literalmente; la dirección se ve conflictiva con el diagrama inmediatamente siguiente].

`Fuente → Frontend → IR → Backend → Objeto`

### Análisis y síntesis

- **Analizar:** tomar algo y descomponerlo en partes para entenderlo.
- **Sintetizar:** construir algo a partir de piezas sueltas.

`Frontend → Análisis` y `Backend → Síntesis`.

**Ejemplo gráfico.** Un bloque `C` con dos bloques `L` aparece marcado `L = Linux`; un bloque `C` con `W` y bloques `L` se identifica como *crosscompiler de C en Linux para Windows*. El texto añade: «Se puede estudiar el compilador y distinguir qué puede ser frontend y qué puede ser backend».

## Página 32 — Estructura detallada y primeras fases (`10791.jpg`)

**Compiladores — Estructura detallada.**

**Pasada.** Lectura de código fuente de inicio a fin. N pasadas → leer N veces fuente. Más pasadas: más flexibilidad, pero más tiempo de compilación.

**Esquema de fases dibujado:**

`Fuente → Scanner (analizador léxico) → Parser (analizador semántico, según rótulo manuscrito) → Diseminador de fuente → Representación intermedia → Generador de código → Optimizador de código → Objeto`

El dibujo agrupa varios pasos en una «pasada» e indica que la lectura del código fuente puede repetirse.

### Analizador léxico (*scanner*)

Toma código fuente y lo descompone en unidades léxicas mínimas. Usa autómatas de estados finitos. Genera *tokens*.

Los analizadores léxicos categorizan y pueden incluir varias categorías, como operadores, separadores o palabras reservadas.

### Analizador sintáctico (*parser*)

Verifica que la sintaxis o estructura morfológica de las líneas de *tokens* siga construcciones válidas; requiere gramática. Utiliza construcciones para identificar correcciones. Implementado con «push-down automatas». Genera árboles de expresiones.

## Página 33 — Análisis semántico, optimización y fases (`10792.jpg`)

### Análisis semántico

Representa el significado de programas y revisa que tenga sentido lo que se pida; determina el comportamiento en tiempo de corrida al ejecutarse. Revisa declaraciones y revisión de tipos. Construye la tabla de símbolos y genera el árbol de atributos.

### Optimizador de código fuente (generador de código intermedio)

Introduce optimizaciones y realiza cálculo de constantes y propagación de constantes; también puede eliminar código innecesario. Se ejecuta sobre el árbol de atributos. Dice que se asemeja a un ensamblador de tres direcciones.

**Ejemplo del dibujo:**

```text
T1 = B * C
T2 = D * E
T3 = T1 + T2
A  = T3
```

El árbol dibujado tiene `A =` en la raíz, `+` bajo la asignación, multiplicaciones `B * C` y `D * E` en las ramas, y etiquetas `T1`, `T2`, `T3`, `T4` para valores intermedios.

**Diagrama de fases:**

```text
Fuente → Scanner → Tokens → Parser → Árbol sintáctico
                                ↓
                       Análisis semántico
                        ↙             ↘
              Tabla de símbolos    Árbol de atributos
                        ↘             ↙
                     Optimizador de código
                              ↓
                              IR
                              ↓
                     Generador de código
                              ↓
                       Lenguaje máquina
                              ↓
                         Optimizador
                              ↓
                       Lenguaje máquina mejorado
```

La fotografía presenta flechas entre análisis semántico, tabla de símbolos y árbol de atributos; el esquema textual conserva las dependencias principales sin precisar el sentido de cada flecha manuscrita.

## Página 34 — Generación y optimización de código; *tokens* (`10793.jpg`)

### Generador de código

Mencionado como *backend* del compilador y convierte código intermedio en código real. Se define con representación de datos en cantidad de bytes y restricciones de colocación.

**Ejemplo de entrada:**

```text
T1 = B * C
T2 = D * E
T3 = T1 + T2
A  = T3
```

**Dos columnas de instrucciones manuscritas (se conserva la notación del ejemplo):**

| Columna izquierda | Columna derecha |
| --- | --- |
| `mov ax, C` | `mov ax, C` |
| `mul B` | `mul B` |
| `mov ax, E` | `mov dx, ax` |
| `mul D` | `mov ax, D` |
| `mov T2, ax` | `mul E` |
| `mov ax, T2` | `add ax, dx` |
| `add ax, T1` | `mov A, ax` |
| `mov T3, ax` | — |
| `mov A, ax` | — |

La grafía de algunas instrucciones y registros es tenue; las columnas se transcriben como ejemplos de los apuntes y no como programas comprobados.

### Optimizador de código

Instrucciones equivalentes con mayor rapidez, con modos de direccionamiento mejores; elimina código redundante, etc.

**Estructuras de datos de un compilador (10/09/2026).**

**Token.** Brindados por *scanner* y caracterizado por dos espacios. Código de un token: variable. Además del código incluye un lexema. Categorías: variable, integer-constant, left-parenthesis, comma [etiquetas inglesas aproximadas a la escritura].

**Árbol sintáctico.** Creado por *parser* y es «decorado» por analizador semántico; en memoria dinámica pueden representarse de distintas formas. En ocasiones no existe explícitamente.

## Página 35 — Tablas, representación intermedia y escáner (`10794.jpg`)

### Tabla de símbolos

Cualquier cosa con símbolos o representaciones termina aquí: variables, procedimientos, constantes y tipos de datos. Es la estructura más usada en compilación. Interactúa con *parser*, *scanner* y analizador semántico. Puede ser formada por varias tablas y acceso *hash*.

### Tabla de literales

Todas las constantes residen en memoria y su valor no cambia en ejecución. Pueden venir punteros y ayuda a reducir código [así aparece en el apunte].

### Código o representación intermedia

En un compilador con *frontend* y *backend*, puede representarse en implementaciones de varias formas: arreglo de punteros a hileras, archivo de texto, lista enlazada. Eliminar, reorganizar, etc.

### Archivos temporales

Archivos de vida corta; pueden vivir segundos. Se crean → graban → leen → se borran.

### Análisis léxico (*scanner*)

Descompone en categorías léxicas mínimas (*tokens*), equivalen a palabras en lenguaje natural. Siempre se buscan los *tokens* más grandes posibles.

**Traducción dirigida por sintaxis.** El *parser* dirige el proceso y también llama al *scanner* cuando «necesita» un *token*. También se invocan rutinas semánticas. Genera código intermedio o, según se menciona, hasta lenguaje de máquina. El *parser* es «cliente» del *scanner*.

## Página 36 — `GetToken()`, lexema y espacios (`10811.jpg`)

**Ejemplo `GetToken()`:**

`Parser → Scanner → Rutina semántica`; un `Token` vuelve al *parser*, que produce un producto [según las flechas del dibujo].

Bajo este modelo, revisa el siguiente *token*, representa un conjunto de hileras sintácticamente equivalentes. Engloba una cantidad pequeña de elementos como `int`, `float` o `char`. La nota manuscrita indica «Conjunto potencialmente infinito» para números o hileras.

### Token y lexema

Un *token* es una categoría léxica y el lexema es la hilera particular en el programa que corresponde al *token*. El programa termina como una hilera en memoria.

En `GetToken()` el *scanner* mantiene la posición actual, se «salta espacios» como blancos, saltos de línea, tabs y comentarios, y avanza hasta reconocer un *token*.

En FORTRAN antes se eliminaban «todos los blancos»; la instrucción `DO` en Fortran permite hacer *loops*. Al eliminar espacios y encontrar *tokens* había ambigüedad y problemas al reconocer variables. Debe conocer separadores de *tokens* para no mezclar léxico con sintaxis. El ejemplo del cuaderno es `DO J=1, 10` [la coma y algunos caracteres son poco nítidos]. Eliminar espacios es una mala idea.

## Página 37 — Generadores de escáneres y lenguajes formales (`10795.jpg`)

### Generadores de *scanners*

Teoría y experiencia acumulada respecto a análisis léxico; más se puede automatizar con `lex`, `flex`, `yacc`, `bison`. Es posible o necesario agregar código a mano.

**Detección de *tokens*.** *Scanner* usa técnicas derivadas de lenguajes formales, teoría de autómatas y autómatas determinísticos de estados finitos.

### Lenguajes formales

**Lenguaje.** Habilidad humana para adquirir y usar complejos sistemas de comunicación. Sonido articulado con que el hombre manifiesta lo que piensa o siente [el apunte intercala dos definiciones].

Existen lenguajes matemáticos, de programación y naturales. «Mínimo» [nota breve al lado de lenguajes formales].

**Símbolo o carácter.** Concepto «primitivo» de representaciones; una idea o entidad con un significado convencional. Denotados como `a`, `b`, `c`.

**Alfabeto.** Conjunto finito y no vacío de símbolos, denotado con `Σ`. Una hilera sobre `Σ` es una secuencia de longitud arbitraria formada con símbolos tomados de un alfabeto `Σ`, que pueden repetirse; son llamadas palabras o frases.

**Longitud de una hilera.** Sea `w` una hilera sobre `Σ`: `|w|` es la longitud de la cantidad de símbolos. Prefijos de una hilera [continúa en la página 38].

**Hilera vacía.** `ε` o `λ`; `|ε| = 0`.

## Página 38 — Prefijos, sufijos, subhileras y concatenación (`10796.jpg`)

### Prefijos de una hilera

Hilera formada tomando el mismo orden de los primeros `k` símbolos desde la «izquierda» de `w`, `0 ≤ k ≤ |w|`. Si `k < |w|`, tenemos un prefijo propio; tenemos un prefijo vacío `ε` y un prefijo de cualquier hilera.

**Ejemplo.** `Σ = {A, T, C, G}`, `w = TTGACATGCA` [lectura aproximada de la hilera manuscrita]. Algunos prefijos anotados: `T`, `TGA`, `ε` [las grafías de la cadena y los prefijos no son completamente nítidas].

### Sufijos de una hilera

Sea `w` una hilera sobre `Σ`: una hilera formada por `0 ≤ k ≤ |w|` símbolos del extremo derecho de `w`; si `k < |w|`, sufijo propio. Algunos sufijos de `w`: `GCAA`, `TGCAA` [la escritura del ejemplo no coincide claramente con la cadena anterior].

### Subhilera de una hilera

Hilera formada tomando en el mismo orden `k` símbolos consecutivos de `w` a partir de posición `j`.

`0 ≤ k, j ≤ |w|` y `0 ≤ k + j ≤ |w|`; si `k + j ≤ |w|` y `j < 0`, tenemos subhilera propia [la condición `j < 0` se lee en la página, aunque parece contradecir el rango previo]. Si `k = 0`, subhilera vacía. `ε` es subhilera de cualquier hilera. Algunos ejemplos escritos: `GCAA`, `A`, `CTGCA` [hay trazos tenues].

### Concatenación de hileras

Sean `v` y `w` dos hileras sobre `Σ`. Si `v = a₁a₂…aₖ`, `w = b₁b₂…bₙ`, entonces concatenar es `a₁a₂…aₖb₁b₂…bₙ` y se denota `vw`.

**Ejemplo.** `Σ = {0, 1}`; se consideran `v = 111`, `w = 01000`; `vw = 11101000`, `wv = 01000111` [la longitud de `w` y la última cifra aparecen tenues en la fotografía].

---

**Estado de la secuencia:** páginas **1–38** transcritas; este archivo incorpora las **29–38**. Las dudas, contradicciones y posibles errores técnicos en los originales se conservan como tales. Las lecturas inciertas se identifican entre corchetes.

**Continuación:** [páginas 39–43](paginas-39-43-continuacion.md).
