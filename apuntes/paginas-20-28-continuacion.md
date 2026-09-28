# Apuntes de Compiladores: continuación, páginas 20–28

Continúa [las páginas 11–19](paginas-11-19-continuacion.md). Se sigue la **numeración manuscrita**, no el orden de subida de las fotos: `10780.jpg` es la página 20, `10778.jpg` la 21 y `10779.jpg` la 22. `10786.jpg` y `10787.jpg` son dos fotografías de la **misma página 28**; se usa la más legible. Se conserva el contenido de clase, incluyendo dudas y anotaciones personales, con puntuación y saltos de línea adaptados a Markdown. Las afirmaciones no se validaron como datos históricos.

## Semana II — Clase IV (20/08/26)

### Página 20 — Lenguaje objeto, MIPS, compilador cruzado y ARM (`10780.jpg`)

#### Lenguaje objeto

**Contexto.** Generalmente se busca generar código ejecutable en la misma arquitectura que se usa.

#### Arquitectura MIPS

**Contexto.** Diseño original de MIPS Computer Systems, arquitectura RISC y conocida para academia.

#### Compilador cruzado

**Definición.** El código generado por el compilador no es el mismo que el lenguaje máquina de la máquina donde corre.

Máquina 1 (*host*) ≠ máquina 2 (*target*).

**Uso.** Si la máquina 1 aún no existe, tiene muchas limitaciones o pocos recursos. Usado en sistemas empotrados.

#### Arquitectura ARM

**Contexto.** Familia de arquitecturas de ARM Holdings con RISC, muy eficiente en energía y espacio. Usada en laptops, tablets y celulares; modelos de 64/32 bits. Arquitectura más usada del mundo, pues 325 millones en 2026, con 99 % de celulares y 30 % a 40 % de todos los dispositivos electrónicos [cifras tal como aparecen en el cuaderno].

### Página 21 — Lenguaje de implementación, *bootstrapping*, Wirth y Pascal (`10778.jpg`)

#### Lenguaje de implementación

**Contexto.** Es muy común escribir un compilador en su mismo lenguaje de implementación, tal que [diagrama T con `C` como fuente y como implementación, y `x86` como objeto]. Se pueden compilar compiladores para generar compiladores que corren nativamente.

#### *Bootstrapping*

**Definición.** Usar la misma herramienta para crearse o levantarse a sí misma. Frecuente en CC y diversas áreas.

#### Niklaus Emil Wirth

**Contexto.** Científico de la computación de Suiza; vivió desde 1934 a 2024. Estableció conceptos fundamentales en lenguajes de programación y diseñó Pascal a inicios de 1970 en homenaje a Blaise Pascal. «Turing Award en 19…» [el año queda incompleto en la fotografía].

#### Pascal

**Objetivos.** Diseñado para enseñar a programar con buenos hábitos, programación estructurada; usado para cursos introductorios y de origen académico.

## Semana III — Clase V (24/08/26)

### Página 22 — Compilando el compilador y primer compilador Pascal (`10779.jpg`)

**Anotación personal al inicio de la página:** «Estoy cansado, frustrado y triste con la forma en la que hemos abarcado la materia».

#### Compilando el compilador

La página abre con varios diagramas T superpuestos que contienen `C`, `Intel`, `Intel 16.2` y variantes; algunas etiquetas están tachadas. A la derecha figura la pregunta: «¿Por qué siento que debo caerle bien al profesor para pasar?» [Los trazos del esquema no permiten reconstruir una composición inequívoca].

#### Primer compilador Pascal

FORTRAN por Wirth en 1969 y genera código CDC 6600. La máquina fue hecha en 1964, primera supercomputadora de la historia y perduran ideas. CDC fue la más rápida de 1964 a 1969, seguida de la 7600.

**Diagrama T anotado:** fuente `Pascal`, objeto `CDC 6600`, implementación `FORTRAN`.

Pasó por varias iteraciones y abandona FORTRAN y busca escribir el compilador en Pascal.

No existen compiladores de Pascal y busca resolver el dilema. Su solución fue compilarlo a mano generando código CDC 6600.

#### ¿Cómo mejora el código?

Compilador genera buen código pero lento; se compila al compilador consigo mismo y mejora siendo más eficiente.

En el diagrama inferior aparecen `P`, `C` y `W`, con la leyenda: `P → Pascal`, `C → CDC 6600`, `W → Wirth`; los rótulos de varios diagramas T se superponen.

### Página 23 — Zurich Compiler Kit y máquinas por número de direcciones (`10781.jpg`)

#### Zurich Compiler Kit

**Máquina de tres direcciones.** Cada instrucción tiene un operador y tres direcciones.

**Máquinas de dos direcciones.** Operación sobre `Dir1` y `Dir2`, resultado en `D1`.

**Máquinas de una dirección.** Cada instrucción tiene un operando y una dirección. Existe un acumulador y es implícito. Operación sobre dirección y acumulador con resultado en acumulador.

**Máquinas de cero direcciones.** *Stack machine*: cero direcciones y un operador actúa sobre el *top* de la pila mientras se hacen *pops*.

#### P-Machine

**Definición.** *Portable machine* que ejecuta P-code. Máquina virtual que corre sobre infraestructura de hardware simple pero programable; varias direcciones [última frase según el manuscrito].

**Zurich P-Machine.** La dependencia de CDC 6600 crea necesidad de definir P-Machine en pila.

### Página 24 — Generando P-code y Zurich Compiler Kit (`10782.jpg`)

#### Generando P-code

Wirth modifica compilador para que genere P-code.

**Diagrama T.** Aparecen Pascal → P-code, un compilador en `C`, un compilador cruzado y una P-Machine que puede usarlo consigo mismo. Los rótulos parcialmente superpuestos se conservan aquí como descripción, sin inferir cada conexión.

El Compiler Kit incluía compilador Pascal en Pascal que genera P-code, el mismo compilador en P-code y una P-Machine escrita en Pascal. La página ilustra tres diagramas T numerados `1`, `2`, `3` con Pascal y P-code.

#### ¿Qué se hace con este Zurich Compiler Kit?

1. Estudiar intérprete de P-Machine, que es pequeño y escrito en Pascal, para reescribirlo en FORTRAN u otro lenguaje disponible. Dice que no es tan complicado pero no es trivial.
2. Intérprete de P-Machine escrito en lenguaje local y compilar hacia máquina actual con compilador. Ahora hay una P-Machine funcional.
3. P-Machine funcional escrita en P-code y con solo un compilador de Pascal escrito en P-code. Se puede correr Pascal.

### Página 25 — Pasos restantes del Zurich Compiler Kit (`10783.jpg`)

4. Poder escribir en Pascal y compilarlo; se puede ejecutar en P-Machine. Diagrama: «software Pascal» → compilador Pascal/P-code alojado en P-Machine IBM 370 → P-code alojado en P-Machine IBM 370.
5. Estudiar compilador Pascal y modificarlo a mano para que genere lenguaje local y no P-code. Se anota `Pascal → P-code → Pascal → IBM 370` bajo rótulos de los diagramas.
6. Compilar ese compilador. Los diagramas T representan traducción de Pascal para IBM 370 mediante compiladores ya disponibles; uno de los *hosts* se rotula «P-Machine» y otro «P-code».
7. De nuevo. Los diagramas finales muestran Pascal → IBM 370 sobre P-code, y después Pascal → IBM [rótulo recortado] sobre IBM; uno de los soportes se rotula «P-Machine».

### Página 26 — ¿Qué hicimos con el kit? Ensambladores (`10784.jpg`)

**¿Qué hicimos con el kit?** Un compilador compatible de Pascal nativo en lenguaje [redacción manuscrita].

#### Parientes de compiladores

Mucho software se relaciona directa o indirectamente. El desarrollo de software asociado a su uso y las técnicas de compiladores influyen en ellas.

#### Ensambladores

Inventados en 1950, bajo nivel, uno a uno con lenguaje máquina, con sintaxis «simple» [según el apunte].

**Características:**

- Campos fijos con etiquetas, códigos de operación o argumentos.
- Usan técnicas de compiladores.
- Utilizan «pasadas» donde la primera crea tabla de signos y verifica sintaxis o semántica y, en la segunda, se ejecuta el código [tal como está anotado].
- Primera línea que es reemplazada por otra dentro del código está ligada a tabla de símbolos.

La tabla de ejemplo del cuaderno lleva encabezados «Cod», «Arg» y «Comen» y contiene mnemónicos como `LI`, `INC`, `PUSH`, registros como `AX`, `BX`, `DX`, `CX` y las notas `PC`, `LC`, `counters`. La alineación entre columnas no se distingue con seguridad en la foto.

**Otras funciones asociadas:** crear diagrama de ensamblador y pasadas o elementos de apuntes.

*Backpatching* y *forward reference* permiten un ensamblador de una pasada.

### Página 27 — Desensambladores e intérpretes (`10785.jpg`)

#### Desensambladores

**Definición.** Inverso de un ensamblador donde toma lenguaje máquina y lo muestra en ensamblador.

**Características.** Similar a un simulador de arquitectura:

- Debe conocer formatos binarios.
- Reconoce formatos de direccionamiento y códigos de operación.
- Genera etiquetas y nombres de variables arbitrarios.

Entre las secciones aparece una hilera de dibujos de caras con la palabra «Great».

#### Semana III — Clase VI (27/08/26): Intérpretes

**Definición.** Combinan traducción con ejecución en línea por línea, con muchas técnicas equivalentes a las de compiladores y son independientes de arquitectura. Usan más *runtime environment*. Lentos en ejecución, todo se repite cada vez.

**Características:** ejecuta línea a línea. Algunos son LISP, BASIC, Python, Ruby y Forth.

### Página 28 — Preprocesador y *linker* (`10786.jpg` y `10787.jpg`)

#### Preprocesador

**Definición.** No se explicó nada hasta el momento; se usan en C. Ocurren antes de la compilación e incluyen archivos. Ahora sí, incluyen declaraciones que usan `#` y `##`; los archivos se juntan; solo estamos repitiendo que usan `#define` una y otra vez. O hay, reemplazan hileras tal como usan, o mejor dicho, funcionan las macros. Las macros son preprocesados. Los macros son manejados con estos [redacción y dudas del apunte].

**Nota adicional en una de las fotografías:** «La definición fue confusa; incluir concepto en repositorio».

**Lista de funciones/preguntas anotadas:**

- Incluyen archivos.
- Reemplazan hileras.
- ¿Se usan con «macros»? ¿Son las macros o los implementan?
- Eliminan comentarios.
- ¿Compilación condicional?
- Independientes del lenguaje.

#### Linker

**Definición.** ¿Programas? O funciones compiladas independientemente. No es una definición. Los *linkers* trabajan con un solo módulo ejecutable. Integrando con el compilador [la redacción aparece como duda en el cuaderno].

Los compiladores o ensambladores generan módulos objeto. Esto solo que confunde más. No es de *linkers*, es de los otros que ya vimos. No veo en qué aporta al concepto de *linker*. En el mar de «cosas» al parecer [el texto se interrumpe al terminar la página].

---

**Estado de la secuencia:** páginas **1–28** transcritas; este archivo incorpora las **20–28**. La página 28 llegó fotografiada dos veces. Las dudas escritas por el autor y las partes de diagramas T que no se pueden leer con seguridad se preservan o señalan; no son explicaciones verificadas del tema.
