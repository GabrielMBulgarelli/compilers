# Apuntes de Compiladores: semana I, clases I y II

Transcripción de las páginas 1–10 del cuaderno, fotografiadas en `10759.jpg`–`10768.jpg`. Se conserva el contenido y el orden de las notas; se normalizan saltos de línea, puntuación y acentos para facilitar la lectura. Las cifras y afirmaciones se presentan como **apuntes originales**, sin validación histórica adicional. Una duda puntual de lectura queda señalada entre corchetes.

## Semana I — Clase I

### Página 1 — Nacimiento de los lenguajes

#### John Mauchly y John Eckert

**Contexto.** Mauchly fue un físico estadounidense, nacido en 1907 y fallecido en 1980, con un Ph. D. de Johns Hopkins University. Eckert fue un ingeniero eléctrico estadounidense, nacido en 1919 y fallecido en 1995, con un máster de Pennsylvania University.

**Relación.** Se conocieron en la Universidad de Pensilvania y se hicieron amigos para trabajar posteriormente en la creación de ENIAC.

#### ENIAC

**Definición.** ENIAC es acrónimo de *Electronic Integrator and Computer* y fue la primera computadora electrónica de propósito general.

**Propósito.** Utilizada para resolver problemas de balística.

**Características:**

- Utilizaba tubos al vacío y se quemaron con frecuencia.
- Era funcional la mitad del tiempo.
- Fue mil veces más rápida que modelos viejos.
- Costó $500 000, equivalentes a $7 millones hoy.

### Página 2 — EDVAC y John von Neumann

#### EDVAC

**Definición.** Significa *Electronic Discrete Variable Automatic Computer* y fue una computadora electrónica binaria.

**Contexto.** Desarrollada por Mauchly y Eckert; empezaron mientras trabajaban con ENIAC. En su creación, John von Neumann participó como consultor y tomó apuntes. Funcionó entre 1949 y 1961.

**Características:**

- Funcionaba por 20 horas diarias.
- MTBF de 8 horas.
- Costó aproximadamente $500 000.
- 6000 tubos al vacío, 42 m de espacio y 66 kW de potencia.

#### John von Neumann

**Contexto.** Matemático húngaro-estadounidense que vivió entre 1903 y 1957. Trabajó en el Proyecto Manhattan y fue miembro original de IAS. Publicó el *First Draft* de EDVAC.

**Aportes.** Trabajó en arquitectura de computadoras, computación, teoría de juegos, conjuntos, física e investigación de operaciones.

### Página 3 — *First Draft*, Maurice Wilkes y EDSAC

#### *First Draft*

- **Programa almacenado:** se lee desde memoria en vez de estar físicamente alambrado.
- **Ciclo *fetch*:** proceso donde la máquina busca y trae de memoria la instrucción de un programa.
- **Conjunto de instrucciones:** conjunto de operaciones que la máquina puede realizar.
- **Software:** aparece al poder ejecutar diferentes programas sin modificar el hardware.
- **Estructura de una computadora:** E/S, memoria y CPU.

#### Maurice Wilkes

**Contexto.** Fue un físico inglés que vivió entre 1912 y 2010; se presenta como uno de los fundadores de computación e investigación de operaciones.

**Aporte.** Inventó el concepto de microprogramación y fue creador de EDSAC.

**Reconocimiento.** Premio Turing de 1967.

#### EDSAC

**Definición.** Significa *Electronic Delay Storage Automatic Computer*. Fue una computadora electrónica desarrollada en UK. Estuvo en funcionamiento entre 1946 y 1958.

**Referencia.** El primer libro de programación usaba EDSAC: *The Preparation of Programs for an Electronic Computer*.

### Página 4 — IBM 701 y John Backus

#### IBM 701

**Definición.** Primera computadora comercial en abril de 1952.

**Características:**

- 19 unidades.
- Alquilada por $23 700/mes.
- 4096 palabras de memoria de 36 bits.
- 150 000 instancias/segundo [lectura de la palabra manuscrita; podría decir «instancias»].
- 150 tarjetas por segundo en entrada.
- 100 tarjetas por segundo en salida.

#### John Backus

**Contexto.** Matemático y científico de computación estadounidense que vivió entre 1924 y 2007. Trabajó en IBM desde 1950.

**Problema.** Su primer proyecto fue calcular posiciones de la Luna mediante un programa de lenguaje máquina. Al parecer detestó trabajar así y creó *Speedcoding* para evitar programar en lenguaje máquina o ensamblador.

**Aportes:**

- 1953 → FORTRAN para IBM 704; el desarrollo termina en 1956. Primer lenguaje de alto nivel.
- 1958 → BNF (luego *Backus–Naur Form*) se utilizó para describir lenguajes de programación libres de contexto.

**Reconocimiento.** Premio Turing de 1977.

### Página 5 — Grace Murray Hopper, John McCarthy y Peter Naur

#### Grace Murray Hopper

**Contexto.** Matemática y científica de computación estadounidense que vivió entre 1906 y 1992. Obtuvo su Ph. D. en Yale. Fue almirante de la Marina de EE. UU.

**Aporte.** Creación de COBOL; se le atribuyen los términos de «compilador» y *debugging*.

#### John McCarthy

**Contexto.** Matemático y científico de computación estadounidense que vivió entre 1927 y 2011. Obtuvo su Ph. D. de Princeton. Fue influenciado por trabajo de von Neumann.

**Aportes:**

- Pionero de la inteligencia artificial.
- Inventó LISP e inventó *Garbage Collection*.
- Trabajó en ALGOL.

**Reconocimiento.** Premio Turing de 1971.

#### Peter Naur

**Contexto.** Astrónomo y científico de computación que vivió entre 1928 y 2016. Obtuvo un Ph. D. de astrofísica en 1957.

**Aportes:**

- Mejoró la notación creada por Backus y se denominó BNF.
- Fue líder en desarrollo de ALGOL 60.

**Reconocimiento.** Premio Turing de 2005.

### Página 6 — Cuatro grandes lenguajes: FORTRAN, LISP y COBOL

#### FORTRAN

**Contexto.** Viene de *Formal Translation*. Su desarrollo comenzó en 1954 en IBM bajo John Backus. Su primer compilador estuvo disponible alrededor de 1957 para IBM 704.

**Características:**

- Lenguaje de alto nivel de uso extendido.
- Se sigue usando, especialmente en HPC.
- Sintaxis similar a notación matemática.
- Asignación con `=`, ciclos con `DO`, condiciones con `IF`, etiquetas con `GOTO` y números.

#### LISP

**Contexto.** Viene de *List Processing*. John McCarthy lo desarrolló en 1958 mientras trabajaba en I. A.

**Características:**

- Relacionado históricamente con I. A.
- Programación funcional.
- Basado en listas y expresiones simbólicas.
- Gran cantidad de paréntesis y notación prefija.
- Las llamadas son funciones como listas cuyo primer elemento identifica la operación. Ejemplo: `(+ 2 3)`.

#### COBOL

**Contexto.** Viene de *Common Business-Oriented Language*. Se sitúa su creación en 1959 y bajo creación de Grace Hopper. Busca ser similar al inglés.

### Página 7 — COBOL, ALGOL y comienzo de la clase II

#### COBOL (continuación)

**Características:**

- Código de gran tamaño.
- No tenía gran aceptación académica, según narrativa.
- Programas organizados jerárquicamente.
- Usa palabras como `MOVE`, `DISPLAY`, `PERFORM`, `IF`, `STOP` y `RUN`.
- Gran aceptación industrial y aún utilizado. ¿65 % de código actual?

#### ALGOL

**Contexto.** Viene de *Algorithmic Language*. Peter Naur lideró su desarrollo en 1958. Buscaba resolver defectos presentes en FORTRAN. Fue descrito usando BNF.

**Características:**

- Usa bloques `begin`–`end` para agrupar instrucciones.
- Permite uso de variables locales, llamadas por valor o por referencia.
- Usa `;` para separar instrucciones, asignación con `:=`, condiciones `if ... then ... else`, ciclos `for ... do`.

## Semana I — Clase II

### Página 7 — Unidad de control

**Definición.** La unidad de control refleja el ciclo *fetch* dentro del CPU. Se estudia usando como referencia la arquitectura von Neumann.

### Página 8 — Ciclo *fetch*, estructura del CPU y diseño de una CU

#### Ciclo *fetch*

**Definición.** El ciclo *fetch* representa el proceso repetitivo de obtener y ejecutar instrucciones.

**Procedimiento.** Actualizar el *program counter* para apuntar a la siguiente dirección, recuperar de memoria dicha instrucción y decodificar la instrucción obtenida. También obtiene operandos, comprueba interrupciones y condiciones, más almacenar resultados.

El *program counter* es el registro que contiene la dirección de la siguiente instrucción.

#### Estructura del CPU

**Contexto.** Incluye unidad de control, ALU, FPU, registros y cachés dentro de CPU.

- **FPU:** unidad especializada de punto flotante.
- **Caché:** memoria rápida utilizada temporalmente para mantener datos o instrucciones de uso frecuente.

El CPU se comunica con la memoria principal.

#### Diseño de una CU (unidad de control)

**Relación.** Organización de computadoras → lógica digital; arquitectura de computadoras → lenguaje máquina.

**Clasificación.** Puede ser alambrada o programada.

### Página 9 — Unidades de control alambrada y microprogramada

#### Unidad de control alambrada

**Definición.** El conjunto de instrucciones se encuentra alambrado físicamente dentro de la unidad de control.

**Funcionamiento.** Cada instrucción posee una implementación fija y física. La unidad de control establece el lenguaje máquina. Es muy rápida pero poco flexible.

#### Unidad de control microprogramada

**Definición.** Las instrucciones se construyen mediante programación sobre una organización subyacente. Se atribuye el concepto a «Wilkins» [así se lee en esta página; en la página 3 figura «Wilkes»] en 1952.

**Estructura.** Tiene micro-memoria con microinstrucciones. Una microinstrucción es una instrucción interna que genera operaciones de control del procesador. Las microinstrucciones se organizan para formar microprogramas. Es más flexible que el alambrado; las instrucciones pueden venir programadas o permitir programación.

**Relación.** RISC → usualmente programadas en alambrados. CISC → usualmente microprogramadas.

*Complex Instruction Set Computer* y *Reduced Instruction Set Computer* definen si es más complejo o más reducido.

### Página 10 — Máquinas multinivel y microprogramación

#### Máquinas multinivel

**Idea.** El hardware constituye la base física y sobre él se agregan capas que facilitan la programación.

**Estructura anotada:** hardware → microprogramación → lenguaje máquina → ensamblador → alto nivel.

Cada capa aumenta la abstracción del hardware.

#### Microprogramación

**Idea.** Presenta al hardware como la parte físicamente real de la máquina.

**Propósito.** Rodea al hardware para permitir utilizarlo mediante una capa programable.

> «En teoría todo se puede lograr con microprogramación que en alto nivel».

**Problema.** Trabajar exclusivamente en esta capa requeriría demasiado tiempo y reduciría la productividad.

Ofrece mucha eficiencia y poca productividad.

---

**Nota de transcripción.** Se retienen afirmaciones, dudas y fechas del cuaderno (incluido el signo de interrogación sobre COBOL). La palabra después de «150 000» en la página 4 y el apellido «Wilkins» en la página 9 merecen cotejo con el original si se reutilizan como hechos en una guía de estudio.
