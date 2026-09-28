# Compiladores: guía de estudio explicada

**Materia considerada:** apuntes de clase, páginas 1–50 y la hoja siguiente; quices 01–05; Fischer–LeBlanc, capítulo 2; Pinker, capítulos 1 y 2; Patrick sobre GM/NAA; artículo sobre ACK. También se incluyen los ejercicios de **ensamblador VOLE**. Quedan fuera los **NDAs**, el capítulo 3 de Pinker y la lectura separada de VOLE. Las preguntas desconocidas del quiz que no se aplicó no se inventan.

**Cómo leer esta guía.** Cada tema presenta primero sus conceptos, después un ejemplo que los utiliza y por último un checklist. Una casilla se marca cuando puedes explicar la respuesta **sin mirar** y comprobarla en un ejemplo nuevo. Cuando un enunciado admite dos interpretaciones, se fija la interpretación antes de resolverlo.

| Parte | Pregunta que resuelve | Temas |
| --- | --- | --- |
| I. La computadora | ¿Qué ejecuta la máquina y cómo se programa VOLE? | 1–3 |
| II. Traductores | ¿Cómo se transforma un programa y cómo se transporta un compilador? | 4–8 |
| III. Fundamentos formales | ¿Qué son hileras, lenguajes y DFA, y cómo se resuelven problemas? | 9–12 |
| IV. Lecturas | ¿Qué sostiene cada lectura y qué evidencia usa? | 13–17 |
| V. Repaso | ¿Qué preguntaron los quices, qué nombres debo distinguir y puedo resolver ejercicios? | 18–20 |

# Parte I. La computadora y sus instrucciones

## 1. Historia: qué problema resolvió cada avance

**Conceptos de esta sección:** ENIAC, EDVAC, EDSAC, programa almacenado, IBM 701/704, Speedcoding, SAP; FORTRAN, LISP, COBOL, ALGOL, Pascal, BNF, recolección de basura, productividad y eficiencia.

Las personas y máquinas de esta tabla **no son sinónimos**. Léela en orden: cada fila responde a una dificultad de la anterior.

| Máquina o trabajo | Persona(s) vinculadas | Qué aporta y qué NO debe confundirse |
| --- | --- | --- |
| **ENIAC** (*Electronic Numerical Integrator and Computer*) | **John Mauchly y J. Presper Eckert** dirigieron su desarrollo. | Computadora electrónica temprana. Originalmente cambiar de problema implicaba ajustar conexiones y controles; no seguía el modelo habitual de programa almacenado en memoria. |
| **EDVAC** | Eckert, Mauchly y otros trabajaron en su diseño; **John von Neumann** redactó el *First Draft of a Report on the EDVAC* (1945). | El informe difundió una organización en que instrucciones y datos se representan en memoria. El informe lleva el nombre de von Neumann; la idea no debe atribuirse a una sola persona. |
| **EDSAC** (*Electronic Delay Storage Automatic Calculator*) | **Maurice Wilkes** dirigió el equipo de Cambridge. | Ejecutó programas almacenados en 1949. Wilkes también propuso la **microprogramación** como forma de organizar el control interno de instrucciones. Es otra máquina, no EDVAC con otro nombre. |
| **IBM 701** | IBM; **John Backus** y colaboradores hicieron **Speedcoding**. | Computadora científica de IBM. Speedcoding era un sistema **interpretativo** para simplificar cálculos, especialmente numéricos: facilitaba programar, aunque consumía más recursos al ejecutar. No era el compilador FORTRAN. |
| **IBM 704** | IBM; equipo FORTRAN de Backus; equipos del monitor GM/NAA. | Máquina asociada al FORTRAN inicial y al sistema por lotes de Patrick. No confundas «dónde corría el compilador» con «lenguaje en que estaba escrito». |

**Programa almacenado, en un ejemplo.** Imagina que memoria contiene dos bytes que significan «cargar 7», otros dos que significan «sumar 2» y otros dos que significan «guardar». La CPU lee esas instrucciones una tras otra. Cambiar el programa consiste en cambiar los bytes de instrucciones, sin reconstruir las conexiones físicas de cada operación. El *First Draft* interesa al curso porque esa organización hizo posible elaborar ensambladores y compiladores para convertir programas legibles en bytes ejecutables.

### Lenguajes, autores y razón de existir

| Concepto | Explicación autónoma y ejemplo |
| --- | --- |
| **Lenguaje máquina** | Bits que una arquitectura concreta reconoce como instrucciones. Un byte que representa «sumar» en una máquina no tiene por qué significar lo mismo en otra. |
| **Lenguaje ensamblador** | Escritura simbólica cercana a instrucciones máquina, como `LOAD` o `ADD`; un programa llamado **ensamblador** la convierte en bytes. **SAP** (*Symbolic Assembly Program*), asociado a **Roy Nutt** e IBM 704 en los apuntes, es un caso histórico. |
| **Lenguaje de alto nivel** | Permite escribir una operación con abstracciones como expresiones, variables, listas o procedimientos, sin describir cada paso de registro. Un compilador o intérprete la lleva a una forma ejecutable. |
| **FORTRAN — John Backus** | Lenguaje de alto nivel para cálculo científico desarrollado por un equipo de IBM dirigido por Backus. Significa *Formula Translation*; `x = a + b` muestra su intención de expresar fórmulas. |
| **LISP — John McCarthy** | Lenguaje asociado al procesamiento de listas y símbolos y a la investigación temprana en IA. Sus implementaciones históricas impulsaron la **recolección de basura**: recuperación automática de memoria que el programa ya no puede alcanzar. |
| **COBOL — Grace Hopper como influencia** | Lenguaje para datos comerciales. Hopper trabajó en A-0 y **FLOW-MATIC**, que influyó en COBOL; COBOL fue una construcción colectiva, no obra exclusiva de Hopper. |
| **ALGOL — Peter Naur** | Lenguaje algorítmico influyente en bloques de código y descripción formal de la sintaxis. **BNF**, *Backus–Naur Form*, expresa una gramática mediante producciones: por ejemplo, `suma → número + número`. Backus y Naur están asociados a su nombre. |
| **Pascal — Niklaus Wirth** | Lenguaje diseñado por Wirth. Su transporte mediante código intermedio P-code es un caso central de la segunda parte. |
| **Productividad** | Trabajo útil que una persona puede desarrollar y mantener por unidad de esfuerzo. Una expresión de alto nivel puede ahorrar cientos de instrucciones escritas a mano. |
| **Eficiencia de ejecución** | Tiempo, memoria y otros recursos consumidos por el programa al correr. Un intérprete puede facilitar el desarrollo sin necesariamente ejecutar tan rápido como código nativo; son dos medidas distintas. |

**Checklist — tema 1**

- [ ] Puedo explicar ENIAC, EDVAC y EDSAC en orden y señalar qué cambia con el programa almacenado.
- [ ] Relaciono correctamente Mauchly/Eckert, von Neumann, Wilkes, Backus y Roy Nutt con sus aportes.
- [ ] Distingo IBM 701/Speedcoding de IBM 704/FORTRAN/monitor.
- [ ] Para FORTRAN, LISP, COBOL, ALGOL y Pascal doy autor o figura, propósito y ejemplo de aporte.
- [ ] Defino BNF, recolección de basura, productividad y eficiencia con ejemplos distintos.

## 2. CPU: qué ocurre cuando ejecuta una instrucción

**Conceptos de esta sección:** Memoria, direcciones, registros, PC, IR, *fetch*, opcode, control alambrado/microprogramado, RISC/CISC, máquinas multinivel y de cero a tres direcciones.

**Memoria** es una colección de celdas con dirección; **registro** es un espacio pequeño dentro de la CPU. Una **dirección** indica qué celda consultar; el **contenido** es el dato guardado allí. Si `M[04]=7`, `04` es la dirección y `7` el contenido. La CPU contiene registros, operaciones sobre datos y una **unidad de control** que ordena cada paso.

**PC** (*program counter*, contador de programa) conserva la dirección de la próxima instrucción. **IR** (*instruction register*, registro de instrucción) conserva los bits de la instrucción actual. El ciclo se entiende así:

1. **Búsqueda o *fetch*.** La CPU lee la instrucción desde memoria siguiendo el PC y la coloca en IR.
2. **Decodificación.** Interpreta el **opcode** (código de operación) y los campos que nombran registros, direcciones o datos inmediatos.
3. **Ejecución.** Realiza la operación: por ejemplo, mueve datos, suma o cambia el PC con un salto.

**Ejemplo:** si el PC vale `00` y las celdas `00` y `01` contienen `20` y `C0`, respectivamente, VOLE obtiene IR=`20C0`. Al buscar una instrucción de dos bytes, el PC normal pasa a `02`; el efecto de `20C0` es poner `C0` en `R0`. Si más adelante se ejecuta un salto a `0E`, el PC pasa a `0E` en lugar de continuar secuencialmente. El **lazo** aparece cuando un salto hace volver a un bloque hasta cumplir una condición.

La unidad de control puede ser **alambrada** (circuitos fijos producen las señales) o **microprogramada** (una secuencia interna de **microinstrucciones** produce las señales). La microinstrucción es interna a la CPU; no equivale a una línea del programa. **RISC** y **CISC** nombran enfoques de diseño del repertorio de instrucciones, más simples/regulares o con operaciones más complejas, respectivamente. Son categorías de arquitectura, no reglas que por sí solas predigan cuál programa corre más rápido.

Una **máquina multinivel** ofrece capas de operaciones. El programa de alto nivel usa abstracciones que el compilador traduce; el ensamblador expresa instrucciones del procesador; el sistema operativo expone servicios sobre el hardware. En generación de código también se clasifican arquitecturas por cuántas ubicaciones **explícitas** nombra una operación:

| Direcciones explícitas | Ejemplo conceptual para `c=a+b` | Dónde queda el resultado |
| --- | --- | --- |
| Tres | `ADD c,a,b` | En `c`. |
| Dos | `MOVE c,a; ADD c,b` | La suma reemplaza `c`. |
| Una | `LOAD a; ADD b; STORE c` | Se calcula en un acumulador implícito. |
| Cero | `PUSH a; PUSH b; ADD; POP c` | `ADD` toma dos valores de la pila y deja uno. |

**Checklist — tema 2**

- [ ] Al ver PC, IR y dos bytes de memoria, explico *fetch*, decodificación, ejecución y el efecto de un salto.
- [ ] Distingo dirección, contenido, dato inmediato, registro, opcode, IR y PC.
- [ ] Explico control alambrado, microprogramado, microinstrucción, RISC/CISC y capas de una máquina multinivel.
- [ ] Traduzco `c=a+b` a máquinas de 3, 2, 1 y 0 direcciones; explico qué hace la pila.

## 3. VOLE: instrucciones, memoria, lazos y promedio de 16 bytes

**Conceptos de esta sección:** Registros y memoria VOLE, hexadecimal y nibble, carga/almacenamiento, aritmética de ocho bits, acarreo, máscaras, rotación, salto, lazo, código automodificable y programa completo de dieciséis bytes.

**Modelo del ejercicio.** VOLE tiene dieciséis registros `R0`…`RF` de **un byte** cada uno, y memoria de 256 bytes `M[00]`…`M[FF]`. PC mide ocho bits, IR dieciséis bits. Cada instrucción ocupa **dos bytes** o cuatro dígitos hexadecimales. Un dígito hexadecimal representa cuatro bits (**nibble**); dos nibbles forman un byte. `FF` es 255 decimal. Una instrucción se lee según su **opcode**; la posición de los demás dígitos no significa siempre lo mismo.

| Forma del ejercicio | Lectura exacta | Ejemplo y efecto |
| --- | --- | --- |
| `2RXY` | Poner el valor **inmediato** `XY` en el registro `R`. | `20C0`: `R0←C0`. No lee `M[C0]`. |
| `1RXY` | Leer **memoria** en `XY` y poner el contenido en `R`. | `11B0`: `R1←M[B0]`. |
| `3RXY` | Escribir el contenido de `R` en memoria `XY`. | `3004`: `M[04]←R0`; `04` no es nombre de registro. |
| `40RS` | Copiar del registro indicado por el tercer dígito al indicado por el cuarto. | `4015`: `R5←R1`. |
| `5RST` | `RR←(RS+RT) mod 256`. | `5AA1`: `RA←RA+R1`. |
| `8RST` | `RR←RS AND RT`, operación bit a bit. | `8416`: `R4←R1 AND R6`. |
| `AR0X` | Rotar el registro `R` `X` bits a la derecha. | `A504`: rotar `R5` cuatro posiciones. |
| `BRXY` | Si `RR=R0`, poner el PC en `XY`. | `B826`: si `R8=R0`, saltar a `26`. `B00E` salta siempre porque `R0=R0`. |
| `C000` | Detener el programa. | No hay más *fetch*. |

**Suma modular y acarreo.** Un registro de ocho bits guarda valores de `0` a `255`. Si se suman `FF` y `01`, la suma matemática es `100` hexadecimal (256), pero el registro conserva `00`: es **suma módulo 256**. El **acarreo** es el bit que salió hacia una posición de mayor peso. Si el ejercicio pide la suma exacta de dieciséis bytes arbitrarios, se necesitan más bits: `16×FF=FF0` hexadecimal (4080 decimal). Un solo registro no puede contenerla. Esta limitación es física del modelo, no un error que se arregle con otro opcode.

### Ejercicio completo: `B0`–`BF` → suma baja en `A`, promedio en `F`

**Objetivo preciso:** los dieciséis datos están en `M[B0]` a `M[BF]`. Dejaremos en `RA` la **suma módulo 256** y en `RF` el promedio entero exacto `⌊suma matemática/16⌋`. Para evitar que el desbordamiento de `RA` contamine el promedio, separa cada byte `x` en `x=16q+r`, donde `q=⌊x/16⌋` y `r=x mod 16`. Así, `⌊Σx/16⌋ = Σq + ⌊Σr/16⌋`. Las sumas parciales caben: dieciséis valores de `q≤15` suman como máximo 240 y lo mismo ocurre con los residuos.

**Cómo se obtiene cada parte:** `x AND 0F` conserva los cuatro bits bajos, es decir `r`. Al rotar `x` cuatro posiciones a la derecha y después aplicar `AND 0F`, quedan los cuatro bits altos, es decir `q`. Sin la máscara, una rotación no equivale a desplazar: los bits descartados reaparecen por el otro lado.

| Dirección | Instrucción | Significado, en orden de ejecución |
| --- | --- | --- |
| `00` | `20C0` | `R0←C0`, dirección posterior al último dato. |
| `02` | `2200` | `R2←0`, suma de cocientes. |
| `04` | `2300` | `R3←0`, suma de residuos. |
| `06` | `260F` | `R6←0F`, máscara. |
| `08` | `2701` | `R7←1`, incremento. |
| `0A` | `28B0` | `R8←B0`, dirección actual. |
| `0C` | `2A00` | `RA←0`, suma baja. |
| `0E` | `11B0` | `R1←M[B0]`; su segundo byte cambiará en el lazo. |
| `10` | `5AA1` | Acumular byte en `RA` módulo 256. |
| `12` | `8416` | `R4←R1 AND R6`, parte baja. |
| `14` | `5334` | `R3←R3+R4`. |
| `16` | `4015` | Copiar `R1` a `R5`. |
| `18` | `A504` | Rotar `R5` cuatro bits. |
| `1A` | `8556` | `R5←R5 AND R6`, parte alta. |
| `1C` | `5225` | `R2←R2+R5`. |
| `1E` | `5887` | `R8←R8+R7`, siguiente dirección. |
| `20` | `B826` | Si `R8=C0`, terminar el lazo. |
| `22` | `380F` | Guardar `R8` en `M[0F]`: cambia el byte de dirección de la instrucción en `0E`. |
| `24` | `B00E` | Volver siempre a `0E`. |
| `26` | `4034` | Copiar suma de residuos `R3` a `R4`. |
| `28` | `A404` | Rotar `R4` cuatro bits. |
| `2A` | `8446` | Aplicar máscara: `R4=⌊Σr/16⌋`. |
| `2C` | `5F24` | `RF←R2+R4`, promedio entero. |
| `2E` | `C000` | Parar. |

**Una vuelta sin saltos mentales.** En la primera, `R8=B0` y `11B0` carga `M[B0]`. Tras procesar el dato, `R8=B1`. `380F` pone `B1` en la dirección `0F`, que es **el segundo byte de la instrucción** almacenada en `0E`–`0F`. La próxima vez esa instrucción será `11B1` y leerá `M[B1]`. Después de procesar `BF`, `R8=C0`; el salto de `20` va a `26` antes de intentar leer `M[C0]`. Esto se llama **código automodificable**: el programa escribe en bytes de sus propias instrucciones. Los datos están lejos del código (`B0`–`BF` frente a `00`–`2F`).

**Verificación numérica:** si todos los datos son `FF`, la suma es `4080=FF0₁₆`; `RA=F0` y `RF=FF` (255). Si los datos son `00,01,…,0F`, suman `120=78₁₆`; `RA=78` y `RF=07` porque `⌊120/16⌋=7`.

**Checklist — tema 3**

- [ ] Puedo decodificar carga inmediata, carga de memoria, almacenamiento, copia, suma, AND, rotación, salto y parada.
- [ ] Al sumar dos bytes distingo suma matemática, resultado módulo 256 y acarreo.
- [ ] Simulo las instrucciones `0E`–`24` para `B0`, luego `B1` y finalmente `BF`; sé por qué se escribe en `0F`.
- [ ] Explico `x=16q+r`, por qué una máscara sigue a la rotación y por qué el promedio sigue siendo exacto.
- [ ] Puedo calcular el caso de dieciséis `FF` sin afirmar que `RA` contiene `4080`.

# Parte II. Cómo se construye y se transporta un programa

## 4. Computadoras dedicadas, lotes y sistema operativo

**Conceptos de esta sección:** Máquina dedicada, lotes, monitor GM/NAA, tarjetas de control/JCL, tres fases de Patrick, E/S, drivers, llamadas al sistema y abstracción del SO.

Una **máquina dedicada** ejecuta un trabajo mientras una persona prepara y retira programas, datos y resultados. Si tarda diez minutos entre trabajos, esos minutos la máquina costosa permanece ociosa. El **procesamiento por lotes** reúne trabajos antes de ejecutarlos. Un **monitor** es el programa supervisor que pasa de un trabajo al siguiente; las **tarjetas de control** identifican trabajos e indican opciones. Un **JCL** (*job control language*) describe instrucciones de control de trabajos, no el algoritmo que el usuario quería calcular.

En la lectura de **Robert L. Patrick** sobre el **monitor GM/NAA del IBM 704**, la secuencia es concreta: (1) **traducción de entrada**, preparar tarjetas y datos; (2) **cálculo**, ejecutar los trabajos; (3) **traducción de salida**, producir resultados entregables. Patrick describió la arquitectura; **Owen Mock** y **George Ryckman** dirigieron equipos de las organizaciones que la implementaron. Un **ensamblador o compilador** podía ser uno de los programas invocados en un trabajo; el monitor no se convierte por eso en ensamblador o compilador.

La **entrada/salida (E/S)** comunica el programa con dispositivos. Un **driver** es software que controla detalles del dispositivo para ofrecer operaciones utilizables por el sistema. Una **llamada al sistema** permite pedir al sistema operativo un servicio, como leer datos. Llamar al SO una **máquina virtual** significa que ofrece al programa una vista más cómoda y uniforme del hardware. No implica necesariamente que ejecute un sistema operativo invitado ni que simule otra CPU.

**Ejemplo completo:** una tarjeta indica «compilar el trabajo 1»; el monitor prepara su fuente, llama al compilador, ejecuta el resultado y recoge la salida. Luego atiende el trabajo 2. **Compilar** transforma un programa; **administrar el lote** decide cuándo correr cada programa.

**Checklist — tema 4**

- [ ] Distingo máquina dedicada, lote, monitor, tarjeta de control y JCL mediante la secuencia de dos trabajos.
- [ ] Explico las tres fases del GM/NAA y relaciono a Patrick, Mock y Ryckman con su aporte.
- [ ] Distingo compilador de monitor; driver de llamada al sistema; hardware de abstracción del SO.

## 5. Traducir, interpretar y leer diagramas T

**Conceptos de esta sección:** Traductor, compilador, intérprete, fuente, objetivo, implementación, anfitriona, destino, compilación cruzada, composición T y *bootstrapping*.

Un **traductor** convierte una representación en otra conservando el significado que importa. Un **compilador** traduce un programa **fuente** a una forma **objetivo** (ensamblador, código máquina u otra representación). Un **intérprete** lee operaciones de una representación y las ejecuta o simula durante la corrida. **Ejemplo:** compilar una expresión a instrucciones y luego correrlas son dos etapas; un intérprete puede leer la expresión y realizar la operación cada vez que se ejecuta. En casos reales se combinan traducción e interpretación; los nombres indican el papel de cada etapa, no una promesa de velocidad.

Un **diagrama T** debe contestar **cinco preguntas**. (1) ¿Qué lenguaje entra? **Fuente.** (2) ¿Qué lenguaje sale? **Objetivo.** (3) ¿En qué lenguaje fue escrito el traductor? **Implementación.** (4) ¿Dónde corre el traductor ya ejecutable? **Anfitriona.** (5) ¿Dónde corre el programa que produce? **Destino.** La barra superior suele mostrar `fuente → objetivo`; el pie puede mostrar implementación cuando se dibuja el **fuente del compilador**, o plataforma anfitriona cuando se dibuja el **ejecutable**. Escribe qué convención estás usando; un mismo rótulo «C» no puede significar simultáneamente fuente del traductor y máquina donde ya corre.

**Compilador cruzado** significa que la anfitriona y el destino difieren. Por ejemplo, compilar en una PC x86-64 para producir código **ARM**; **MIPS** y ARM son familias de arquitecturas posibles, no lenguajes de implementación del compilador por el mero hecho de ser destinos. Una **composición de traductores** funciona si la salida de uno es una entrada válida del siguiente **y ambos se pueden ejecutar** en algún entorno disponible.

### Ejercicio de transporte con C, Fortran y COBOL

Supón que tienes un compilador **C versión 7 ejecutable en Linux**, el **fuente en C** de C versión 10, un **fuente en C** de un traductor `Fortran→C`, y «un compilador `COBOL→máquina` escrito en Fortran»:

1. Usa C v7 para compilar el **fuente de v10**. Obtienes el primer ejecutable C v10 en Linux.
2. Si se solicita una versión construida por sí misma, compila otra vez el mismo fuente con C v10. Esto es **bootstrapping**: usar herramientas anteriores para llegar a una implementación que puede compilarse a sí misma. No demuestra por sí solo que el resultado sea más correcto o rápido.
3. Usa el compilador C ejecutable para compilar el **fuente del traductor Fortran→C**. Ahora ese traductor sí puede correrse en Linux.
4. Si el compilador COBOL está disponible **como fuente Fortran**, tradúcelo a C y compila el C generado para obtener un ejecutable local. Si solo tienes un **binario incompatible** y ningún fuente, el paso no se puede hacer con esas herramientas: un traductor de Fortran requiere texto fuente Fortran.

**Regla de examen:** en cada flecha escribe «archivo fuente», «ejecutable» y «plataforma». Un traductor aún sin compilar no puede transformar otros programas. El código que produzca el compilador COBOL puede ser para una arquitectura distinta de la que ejecuta el compilador; no confundir estos dos destinos.

**Checklist — tema 5**

- [ ] Defino fuente, objetivo, implementación, anfitriona, destino, traductor, compilador e intérprete con un ejemplo propio.
- [ ] Dibujo un T y especifico qué significa su pie; identifico un compilador cruzado.
- [ ] Ejecuto mentalmente los cuatro pasos del ejercicio y detecto cuándo falta un fuente o un compilador ejecutable.
- [ ] Explico *bootstrapping* sin atribuirle mejoras automáticas de rendimiento o corrección.

## 6. Dos soluciones de portabilidad: Zurich y Amsterdam

**Conceptos de esta sección:** IR, máquina de pila, Pascal-P, P-code/P-machine, CDC 6600, ACK, EM, UNCOL, front ends, back ends y optimizaciones locales/globales.

**Problema compartido:** un compilador creado para una máquina concreta puede no correr en otra. Una **representación intermedia (IR)** es una forma del programa entre la entrada y el código nativo; separar esas etapas permite reutilizar trabajo. Una **máquina de pila** ejecuta operaciones sobre los valores superiores: `PUSH 2; PUSH 3; ADD` deja `5` en la pila, sin que `ADD` nombre registros explícitos.

### Zurich Compiler Kit: transportar Pascal

**Niklaus Wirth** diseñó Pascal. En el relato de clase, una implementación dependía de su entorno, incluido el **CDC 6600**. En **Pascal-P**, el compilador de Pascal produce **P-code**, instrucciones para una **P-machine** abstracta de pila. Para transportar el sistema a otro equipo, primero hay que disponer de una implementación de P-machine en ese equipo; después se puede ejecutar allí el compilador y los programas P-code. Finalmente, si se desea código nativo, se adapta un generador para esa máquina. El kit de Zurich está centrado en **Pascal**; P-code no es automáticamente código nativo.

**Ejemplo de arranque:** supón una computadora que tiene compilador Fortran pero aún no Pascal. Estudias el intérprete relativamente pequeño de la P-machine y lo implementas en Fortran; compilas ese intérprete con el Fortran existente; ahora puedes correr P-code y una versión del compilador Pascal que funcione sobre la P-machine. El paso exigente es implementar correctamente la máquina abstracta, no pronunciar la palabra «portable».

### Amsterdam Compiler Kit (ACK): varios lenguajes y máquinas

El **ACK** descrito por **Andrew S. Tanenbaum, Hans van Staveren, Ed Keizer y Johan Stevenson** usa varios **front ends** (cada uno entiende un lenguaje fuente) y varios **back ends** (cada uno produce código para una arquitectura). Entre ambos usa **EM**, código intermedio de una máquina abstracta de pila. La idea histórica **UNCOL** proponía un intermediario común. Si hay `N` lenguajes y `M` máquinas, la separación permite construir aproximadamente `N` frentes y `M` posteriores compartibles, en vez de una implementación aislada por cada pareja (`N×M`). Bibliotecas, pruebas, optimización y adaptación siguen costando trabajo; `N+M` describe la reutilización de componentes, no el costo total exacto.

**Ejemplo real del artículo:** la asignación `K := I+7` se expresa en EM aproximadamente como `LOL I; LOC 7; ADI 2; STL K`: cargar `I`, apilar `7`, sumar enteros de dos bytes y almacenar en `K`. El front end decide el **significado** de la fuente; el back end elige instrucciones de la CPU concreta. El optimizador **peephole** sustituye secuencias **cortas** por equivalentes mejores; el **global** razona sobre regiones más amplias, como bloques y bucles. ACK incluye componentes para interpretar o ensamblar EM, probarlo, generar ensamblador de destino y enlazar bibliotecas.

| Pregunta | Zurich/Pascal-P | Amsterdam/ACK |
| --- | --- | --- |
| Lenguajes iniciales | Principalmente Pascal. | Varios lenguajes con frentes diferentes. |
| Forma intermedia | P-code. | EM. |
| Máquina abstracta | P-machine basada en pila. | Máquina EM basada en pila. |
| Meta distintiva del curso | Transportar Pascal a otra plataforma. | Reutilizar frentes y posteriores entre lenguajes y máquinas. |

**Checklist — tema 6**

- [ ] Distingo IR, pila, P-code, P-machine, EM y UNCOL sin usarlos como sinónimos.
- [ ] Explico qué debe implementarse primero al llevar Pascal-P a una máquina nueva.
- [ ] Dibujo `Pascal→P-code→P-machine` y `lenguaje→front end→EM→back end→máquina`.
- [ ] Justifico `N+M` frente a `N×M` y doy el recorrido de `K := I+7`.
- [ ] Diferencio optimización local/peephole, global y específica de una máquina.

## 7. Herramientas alrededor del compilador

**Conceptos de esta sección:** Preprocesador, macro, ensamblador, dos pasadas, referencia adelantada, backpatching, objeto, relocalización, linker, enlace dinámico, loader, intérprete, desensamblador, debugger, profiler, editor, IDE y versiones.

La secuencia típica es `fuente → preprocesador → compilador → ensamblador → linker → loader → ejecución`. Cada nombre indica **qué entrada consume y qué salida produce**. Un diseño concreto puede integrar pasos, pero el papel conceptual permanece:

| Herramienta o dato | Entrada → salida / acción | Ejemplo que fija la diferencia |
| --- | --- | --- |
| **Preprocesador** | Texto fuente → texto transformado antes de compilar. | Expande una **macro** o incluye un archivo. Una macro es una regla de expansión textual, no una función ejecutada por la CPU. |
| **Ensamblador** | Instrucciones simbólicas → bytes de código **objeto**. | La etiqueta `inicio` debe convertirse en una dirección o referencia. |
| **Referencia adelantada** | Uso de un símbolo cuyo destino se define más adelante. | `JMP final` antes de escribir la etiqueta `final`. |
| **Dos pasadas** | Primera: localizar etiquetas/direcciones; segunda: emitir bytes usando la tabla obtenida. | Resuelve `final` después de haber leído todo el fuente. |
| **Backpatching** | Reservar un hueco en una instrucción o salto y completarlo cuando se conoce el destino. | En un `if`, emitir `si falso salta a ?` y rellenar `?` al terminar la rama. |
| **Linker / enlazador** | Archivos objeto y bibliotecas → salida enlazada. | Resuelve una llamada a una función definida en otro módulo. |
| **Tabla de relocalización** | Indica **dónde** ajustar una dirección, **a qué** símbolo o sección se refiere y **cómo** ajustarla al colocar los objetos. | El destino final de una llamada cambia cuando el linker ubica los módulos. |
| **Enlazado dinámico** | Resuelve referencias a bibliotecas compartidas al cargar o ejecutar, según el sistema. | `printf` puede provenir de una biblioteca compartida. |
| **Loader / cargador** | Ejecutable y dependencias → proceso preparado en memoria. | Coloca código y datos y transfiere control al punto de entrada. |
| **Intérprete** | Programa o código intermedio → ejecución de sus operaciones. | Una P-machine interpreta P-code. |
| **Desensamblador** | Bytes de máquina → representación ensamblador aproximada. | Recupera instrucciones, no los comentarios originales. |
| **Debugger / depurador** | Ejecución controlada para investigar fallos. | Pausa en una línea y examina registros o variables. |
| **Profiler** | Ejecución medida → distribución de tiempo/recursos. | Encuentra qué función consume la mayor parte del tiempo. |
| **Editor / IDE / gestor de versiones** | El editor cambia texto; el IDE integra herramientas; el gestor registra y coordina revisiones. | Git permite comparar cambios; ninguno sustituye el análisis sintáctico. |

**Diferencia crucial:** backpatching y relocalización dejan un cálculo pendiente, pero el primero suele completar saltos durante generación de código y la segunda ajusta referencias en objetos al enlazar/cargar. El **objeto** puede tener instrucciones aún no ubicadas definitivamente; el **ejecutable** ya tiene una organización enlazada apropiada para cargarse.

**Checklist — tema 7**

- [ ] Ordeno las herramientas y para cada una doy entrada, salida y momento de uso.
- [ ] Resuelvo una referencia adelantada con dos pasadas y otra con backpatching.
- [ ] Distingo backpatching, relocalización, enlace dinámico y carga mediante el ejemplo de `printf` y uno de `if`.
- [ ] Describo intérprete, desensamblador, debugger, profiler, editor, IDE y control de versiones sin llamarlos fases del parser.

## 8. Dentro de un compilador: una misma línea, etapa por etapa

**Conceptos de esta sección:** Scanner, token/lexema, `GetToken()`, generador léxico, gramática, parser, descenso recursivo, semántica, tablas, AST, IR, optimización, código objeto, una pasada, errores y proyecto MICRO.

Usaremos `total := x + 1` para dar un significado **autónomo** a cada etapa. **Fischer y LeBlanc, capítulo 2**, enseñan este recorrido con un compilador pequeño. La cadena conceptual es `caracteres → tokens → estructura → comprobaciones → código`; no afirma que toda implementación industrial guarde un archivo por etapa.

### 8.1 Análisis léxico: caracteres a tokens

El **scanner** (analizador léxico) recorre caracteres. Un **token** es una categoría útil para la gramática: `IDENTIFICADOR`, `ASIGNACIÓN`, `SUMA`, `ENTERO`. Un **lexema** es la hilera concreta que originó un token: `total` y `x` son dos lexemas de categoría `IDENTIFICADOR`; `1` es el lexema de `ENTERO`. El scanner puede asociar valor `1` al token numérico y suele omitir blancos y comentarios según las reglas del lenguaje. `GetToken()` representa la petición del **parser** al scanner para el próximo token.

| Fragmento leído | Token | Información que conviene conservar |
| --- | --- | --- |
| `total` | `IDENTIFICADOR` | Lexema `total` y ubicación en fuente. |
| `:=` | `ASIGNACIÓN` | Operador reconocido completo, no `:` seguido por `=` si la regla exige coincidencia larga. |
| `x` | `IDENTIFICADOR` | Lexema `x`. |
| `+` | `SUMA` | Operador. |
| `1` | `ENTERO` | Lexema `1`, valor numérico 1. |

Un **generador de scanners** produce el código del analizador a partir de patrones especificados. En muchos scanners se toma la coincidencia válida más larga, con reglas para desempates. El ejemplo histórico de FORTRAN en los apuntes muestra por qué **borrar indiscriminadamente todos los espacios** puede modificar cómo se distinguen nombres y sentencias (`DO` y una asignación son el caso clásico); omitir blancos solo es correcto conforme a las reglas léxicas precisas del lenguaje.

### 8.2 Análisis sintáctico y semántico

Una **gramática** describe formas permitidas mediante **producciones**. Por ejemplo, `asignación → IDENTIFICADOR ASIGNACIÓN expresión`; `expresión → término (SUMA término)*`. El **parser** (analizador sintáctico) comprueba que los tokens se puedan organizar así. En **descenso recursivo**, una función implementa cada construcción y llama a las funciones de sus partes; la función de asignación pide un identificador, `:=` y una expresión. Un **AST** (*árbol de sintaxis abstracta*) puede representar `asignar(total, sumar(x,1))`. Se llama «abstracto» porque no necesita conservar cada blanco o separador.

El **análisis semántico** pregunta si la estructura ya reconocida **tiene sentido según las reglas estáticas**: ¿existen `total` y `x`?, ¿son compatibles sus tipos?, ¿se permite asignar el resultado? Un **árbol decorado** puede conservar en cada nodo el tipo calculado. La **tabla de símbolos** asocia nombres con tipo, ámbito, dirección u otros atributos; una **tabla de literales** puede registrar constantes como `1` con el almacenamiento que necesiten. Un compilador no tiene necesariamente una tabla única ni todos esos campos: esas estructuras sirven al diseño.

**Tres fallos distintos:** `x @ 1` puede ser **léxico** si `@` no pertenece al lenguaje; `x + ;` es **sintáctico** porque falta operando; `x + verdadero` puede ser **semántico** si los tipos no admiten suma. Una entrada que compila y falla al ejecutar pertenece a otro momento; no la llames automáticamente error sintáctico.

### 8.3 Representación y generación

Una **IR** (representación intermedia) es una forma manipulable entre el fuente y el destino, por ejemplo `t1 := x+1; total := t1`. Puede almacenarse en un arreglo, lista o archivo temporal; un **archivo temporal** se usa mientras dura una etapa y puede borrarse después. **Optimización** transforma el programa conservando su comportamiento exigido: por ejemplo, calcular `2+3` como `5` cuando las reglas del lenguaje lo permiten. **Generación de código** elige instrucciones y ubicaciones concretas: cargar `x`, sumar 1, guardar en `total`. Un compilador **de una pasada** puede emitir instrucciones a medida que el parser reconoce construcciones; otros guardan AST e IR y hacen varias pasadas. **Front end** nombra el trabajo de comprender el fuente; **back end** el de producir código para el destino. Una implementación puede distribuir o fusionar tareas, pero las preguntas léxica, sintáctica y semántica siguen siendo distintas.

### 8.4 MICRO: caso real del proyecto de clase

El proyecto **MICRO** del repositorio usa scanner y parser de descenso recursivo y genera ensamblador x86-64 **durante** el análisis, sin construir AST ni IR separados. Para `read(x)`, el scanner reconoce `read`, `(`, identificador y `)`; el parser acepta la forma `READ(id_list);`; la acción de generación prepara la **dirección** de `x` y llama a `scanf`. Para `write(x+1)`, reconoce la lista de expresiones, calcula el valor y llama a `printf`. Variables y temporales se reservan en `.bss`. Entrada `4` en `read(x); write(x+1);` produce salida `5`. GCC se invoca después para ensamblar/enlazar el texto generado.

El condicional de MICRO es **`(E1 | E2 | E3)`**. Primero se evalúa `E1`; si su valor es distinto de cero, el resultado es `E2`; si es cero, el resultado es `E3`. El generador emite comparación, salto a la rama falsa, código de `E2`, salto al final, etiqueta falsa, código de `E3` y etiqueta final. Ambas ramas guardan en **el mismo temporal**; durante la ejecución **solo una** rama se evalúa. `(0 | 10 | 20)` da 20. Que el compilador emita instrucciones para las dos ramas no significa que las ejecute ambas.

**Checklist — tema 8**

- [ ] Para `total := x+1` separo lexemas/tokens, producción, AST opcional, comprobación de tipos y código resultante.
- [ ] Defino scanner, `GetToken()`, parser, descenso recursivo, gramática, producción y generador de scanners.
- [ ] Doy un ejemplo distinto de error léxico, sintáctico, semántico y de ejecución.
- [ ] Distingo tabla de símbolos, tabla de literales, árbol decorado, IR, archivo temporal, optimización y generación de código.
- [ ] Explico front end/back end y por qué un compilador de una pasada puede carecer de AST/IR explícitos.
- [ ] Reproduzco `read`, `write` y `(E1 | E2 | E3)` de MICRO, especialmente el salto que evita evaluar la rama descartada.

# Parte III. Hileras, lenguajes y autómatas

## 9. Hileras: definiciones antes de operar

**Conceptos de esta sección:** Alfabeto, símbolo, hilera, longitud, `ε`, prefijo, sufijo, subhilera, concatenación, potencia, reverso, `Σⁿ`, `Σ*` y `Σ+`.

Un **alfabeto** `Σ` es un conjunto finito de símbolos. Si `Σ={E,C,I}`, `ECCI` es una **hilera** sobre ese alfabeto: secuencia de cuatro símbolos, así que su **longitud** es `|ECCI|=4`. La **hilera vacía** `ε` tiene longitud cero. El orden importa: `EC` y `CE` son hileras diferentes; las repeticiones también: `ECI` y `ECCI` son diferentes.

### Prefijo, sufijo y subhilera son tres preguntas distintas

- **Prefijo:** empieza en el primer símbolo. `p` es prefijo de `w` si existe alguna hilera `x` con `w=px`.
- **Sufijo:** termina en el último símbolo. `s` es sufijo de `w` si existe alguna hilera `x` con `w=xs`.
- **Subhilera:** ocupa posiciones **consecutivas** en cualquier parte. `u` es subhilera de `w` si existen `x,y` con `w=xuy`.

| Longitud | Prefijo de `ECCI` | Sufijo de `ECCI` |
| ---: | --- | --- |
| 0 | `ε` | `ε` |
| 1 | `E` | `I` |
| 2 | `EC` | `CI` |
| 3 | `ECC` | `CCI` |
| 4 | `ECCI` | `ECCI` |

Por tanto, `Pref(ECCI)={ε,E,EC,ECC,ECCI}` y `Suf(ECCI)={ε,I,CI,CCI,ECCI}`. `CC` es subhilera porque `ECCI=E·CC·I`, pero no empieza al principio ni llega al final: no es prefijo ni sufijo. **Propio** significa «diferente de la hilera completa». En una hilera no vacía `ε` sí cuenta como prefijo y sufijo propios. Esta pregunta se recuerda del quiz que no llegó a aplicarse.

### Cuatro operaciones sobre hileras

| Operación | Definición precisa | Ejemplo |
| --- | --- | --- |
| **Concatenación** `uv` | Escribir `v` después de `u`. | `EC·CI=ECCI`; `ε·ECCI=ECCI`. |
| **Potencia** `wⁿ` | Escribir `n` copias de `w`; `w⁰=ε`. | `(CI)³=CICICI`; `(CI)⁰=ε`. |
| **Reverso** `wᴿ` | Invertir el orden de símbolos. | `(ECCI)ᴿ=ICCE`; `(uv)ᴿ=vᴿuᴿ`. |
| **Longitud de concatenación** | Contar símbolos de las dos partes. | `|EC·CI|=2+2=4`. |

La concatenación es **asociativa**: `(uv)z=u(vz)` porque ambos lados escriben `u`, luego `v`, luego `z`; es **no conmutativa** en general: `E·C=EC`, pero `C·E=CE`. Su **elemento neutro** es `ε` porque concatenar cero símbolos no cambia nada. No confundir «neutro de hileras» con el neutro de **lenguajes** de la sección siguiente.

`Σⁿ` es el **conjunto** de todas las hileras de longitud `n` sobre `Σ`. Para `Σ={0,1}`, `Σ⁰={ε}`, `Σ¹={0,1}`, `Σ²={00,01,10,11}`. `Σ*` reúne `Σ⁰∪Σ¹∪Σ²∪⋯`: **todas las hileras finitas**, incluida `ε`. `Σ+` reúne `Σ¹∪Σ²∪⋯`: todas las de longitud **positiva**. El asterisco se llama **clausura de Kleene** por **Stephen Cole Kleene**. `Σ*` no significa «una hilera inmensamente larga», sino un **conjunto infinito de hileras finitas** si `Σ` contiene al menos un símbolo.

**Checklist — tema 9**

- [ ] Construyo `Σ⁰`, `Σ¹`, `Σ²`, `Σ*` y `Σ+` y explico cuál contiene `ε`.
- [ ] Enumero prefijos y sufijos propios y no propios de `ECCI`, y encuentro subhileras interiores.
- [ ] Calculo concatenación, potencia y reverso con un ejemplo nuevo.
- [ ] Explico por qué concatenación de hileras es asociativa, no conmutativa, y tiene neutro `ε`.

## 10. Lenguajes: conjuntos cuyos elementos son hileras

**Conceptos de esta sección:** Lenguaje formal, reconocedor/generador, `∅` y `{ε}`, unión, intersección, diferencia, complemento, reverso, concatenación, potencias, `L*`, `L+` y elementos neutros.

Un **lenguaje formal** `L` sobre un alfabeto `Σ` es cualquier **subconjunto de `Σ*`**. `L={0,11}` es finito; el conjunto de hileras binarias que terminan en `1` es infinito. Un **reconocedor** responde «pertenece/no pertenece» para una hilera; un **generador** enumera hileras del lenguaje sin producir ajenas y puede llegar a cada miembro. Un generador de lenguaje infinito no termina de listarlo en un instante.

**La distinción más importante de este tema:** `ε` es una **hilera** de longitud cero. `{ε}` es un **lenguaje** con exactamente **un miembro**. `∅` es un **lenguaje** con **cero miembros**. Las tres escrituras designan objetos distintos. En particular, `ε∈{ε}`, pero `ε∉∅`.

### Operaciones de conjuntos: decide pertenencia de cada hilera

Usa el mismo universo `Σ={0,1}` y los lenguajes `L={ε,0,01}` y `M={0,1}`:

| Operación | Regla de pertenencia | Resultado del ejemplo |
| --- | --- | --- |
| **Unión** `L∪M` | La hilera está en `L` **o** en `M` (también si está en ambos). | `{ε,0,01,1}`. No se repite `0`. |
| **Intersección** `L∩M` | La hilera está en **ambos**. | `{0}`. |
| **Diferencia** `L\M` | Está en `L` y **no** en `M`. | `{ε,01}`; en cambio `M\L={1}`. |
| **Complemento** `Σ*\L` | Es una hilera de `Σ*` que no está en `L`. | `1`, `00`, `10`, `11`, …; **no** `ε`, `0` ni `01`. |
| **Reverso del lenguaje** `Lᴿ` | Invierte **cada hilera** de `L`. | `{ε,0,10}` porque `(01)ᴿ=10`. |

La unión es asociativa, conmutativa e idempotente (`L∪L=L`), y su neutro es `∅`: `L∪∅=L`. La intersección también es asociativa, conmutativa e idempotente, y su neutro **relativo a `Σ`** es `Σ*`: `L∩Σ*=L`. Para diferencia, `L\∅=L`, pero `∅\L=∅`; por eso **no** tiene un neutro bilateral del mismo modo y no es conmutativa. El **complemento siempre depende del alfabeto**: sin universo `Σ*` la expresión «todas las otras hileras» es incompleta.

### Concatenación, potencias y clausura de un lenguaje

La **concatenación de lenguajes** `LM` reúne todas las hileras `uv` con `u∈L` y `v∈M`. Para `L={0,01}` y `M={ε,1}`, calcula los cuatro pares: `0·ε=0`, `01·ε=01`, `0·1=01`, `01·1=011`. El resultado es el conjunto **`{0,01,011}`**: `01` aparece una sola vez aunque tenga más de una construcción.

`L⁰={ε}`; `L¹=L`; `L²=LL`; `L³=LLL`. `L* = L⁰∪L¹∪L²∪⋯` permite **cero o más** factores y siempre contiene `ε`. `L+ = L¹∪L²∪⋯` exige **al menos un factor**; aun así puede contener `ε` si `ε` ya pertenece a `L`. Para `L={ab}`, `L*={ε,ab,abab,ababab,…}` y `L+={ab,abab,ababab,…}`. Para `L=∅`, `L⁰={ε}`, `L*={ε}` y `L+=∅`.

La concatenación de lenguajes es **asociativa** porque `uvw` tiene la misma secuencia cualquiera que sea la agrupación. Generalmente no es conmutativa (`{a}{b}={ab}` frente a `{b}{a}={ba}`), ni idempotente (`{a}{a}={aa}≠{a}`). Su **neutro es `{ε}`** porque se elige una hilera vacía como factor; `∅` es **absorbente**, pues no hay hilera que pueda elegirse de un lenguaje vacío: `L∅=∅L=∅`.

| ¿Qué operación? | Neutro | Comprobación |
| --- | --- | --- |
| Concatenar **hileras** | `ε` | `wε=εw=w`. |
| Concatenar **lenguajes** | `{ε}` | `L{ε}={ε}L=L`. |
| Unir lenguajes | `∅` | `L∪∅=L`. |
| Intersectar lenguajes sobre `Σ` | `Σ*` | `L∩Σ*=L`. |

**Checklist — tema 10**

- [ ] Digo qué tipo de objeto es cada uno de `ε`, `{ε}`, `∅`, `Σ*` y `L`.
- [ ] Calculo unión, intersección, diferencias en ambos sentidos, complemento y reverso en un ejemplo finito.
- [ ] Calculo `LM`, `L²`, `L*`, `L+` y el caso `∅*`; quito duplicados porque son conjuntos.
- [ ] Elijo el neutro correcto según la operación y doy un contraejemplo para la no conmutatividad de concatenación.
- [ ] Explico reconocedor/generador y por qué el complemento requiere alfabeto explícito.

## 11. DFA: definición completa y lectura de un autómata

**Conceptos de esta sección:** Quíntupla `(Q,Σ,δ,q₀,F)`, transición total y extendida, aceptación, tabla/diagrama, `ε`, sumidero, complemento y ejemplos de sufijos.

Un **autómata finito determinista**, o **DFA**, es una máquina matemática que lee una hilera **de izquierda a derecha**, un símbolo por paso. En todo momento conserva un **estado**, que resume la información pasada necesaria para decidir al final. Su definición es la **quíntupla** `M=(Q,Σ,δ,q₀,F)`:

| Componente | Qué es, sin abreviaturas ambiguas | Ejemplo del DFA «termina en `1`» |
| --- | --- | --- |
| `Q` | Conjunto **finito** de estados. | `{q0,q1}`. |
| `Σ` | Alfabeto de símbolos que puede leer. | `{0,1}`. |
| `δ` | Función de transición **total** `Q×Σ→Q`: para cada estado y cada símbolo da **exactamente un** estado siguiente. | `δ(q0,1)=q1`. |
| `q₀` | Estado inicial, que pertenece a `Q`. | `q0`. |
| `F` | Subconjunto de `Q` formado por estados de aceptación. | `{q1}`. |

En un **diagrama**, una flecha que viene de fuera apunta al inicial; los estados finales tienen doble círculo; cada flecha interna lleva símbolo. En una **tabla**, cada fila es un estado y cada columna es un símbolo; la celda contiene el siguiente estado. **Total** significa que ninguna celda queda sin decisión. Si una entrada prohibida ya no puede salvarse, va a un **estado sumidero** no final que vuelve a sí mismo con todas las letras. Un dibujo que omite transiciones por abreviar debe completarse para ser un DFA formal.

**Aceptación.** Si `w=w₁…wₙ`, comienza en `r₀=q₀` y aplica `rᵢ₊₁=δ(rᵢ,wᵢ₊₁)` hasta leer **todo** `w`. Acepta si **el estado final** `rₙ` pertenece a `F`. El **lenguaje reconocido** `L(M)` contiene precisamente todas las hileras aceptadas. Haber visitado un estado final a mitad de la hilera **no basta** si luego se sale de él.

La **transición extendida** `δ̂(q,w)` significa «estado alcanzado al leer la hilera entera `w` desde `q`». Sus dos reglas son `δ̂(q,ε)=q` y `δ̂(q,wa)=δ(δ̂(q,w),a)`, donde `a` es el último símbolo. La primera dice: sin leer nada, permaneces donde estabas. **No es una transición ε** añadida al DFA. `ε` se acepta exactamente cuando `q₀∈F`.

### Tabla completa: binarias que terminan en `1`

Aquí `q0` significa «no se ha leído nada o el último símbolo es `0`»; `q1` significa «el último es `1`». El significado del estado **predice correctamente lo que pasa al añadir otro símbolo**:

| Estado actual | Leer `0` | Leer `1` | ¿Final? |
| --- | --- | --- | --- |
| `q0` (inicial) | `q0` | `q1` | No |
| `q1` | `q0` | `q1` | Sí |

`101` sigue `q0→q1→q0→q1` y acepta. `10` termina en `q0` y rechaza. `ε` comienza y termina en `q0`, por lo que rechaza. Para el lenguaje **«no termina en `1`»**, conserva **exactamente las mismas transiciones** y cambia `F` a `{q0}`; ahora `ε` se acepta. Esto es el **complemento de un DFA total**: sobre el mismo alfabeto, `F` se sustituye por `Q\F`. Si faltaban transiciones, primero completa la máquina y solo entonces intercambia finales/no finales.

### Sufijos de dos símbolos: `01` y el caso `00`

Para **«termina en `01`»**, tres estados guardan el sufijo relevante: `s0` = no termina en `0` ni en `01`; `s1` = termina en `0`; `s2` = termina en `01`. Solo `s2` acepta.

| Estado | Leer `0` | Leer `1` | ¿Final? |
| --- | --- | --- | --- |
| `s0` inicial | `s1` | `s0` | No |
| `s1` | `s1` | `s2` | No |
| `s2` | `s1` | `s0` | Sí |

`001` sigue `s0→s1→s1→s2` y acepta, pero `01` **también** sigue `s0→s1→s2` y acepta. En la página 48, el texto parece decir «termina en `001`», mientras el **dibujo** implementa `01`; la prueba con `01` demuestra la diferencia. No presentamos ese dibujo como solución de `001`.

Para **«no termina en `00`»**, usa `z0` (cero `0` consecutivos al final), `z1` (uno) y `z2` (dos o más). Con `1`, cualquier estado vuelve a `z0`; con `0`, avanza `z0→z1→z2→z2`. Aceptan `z0` y `z1`; `z2` rechaza. `ε` acepta porque `z0` es inicial/final. «Termina en `00`» usaría las **mismas transiciones** y aceptaría solo `z2`.

**Checklist — tema 11**

- [ ] Escribo los cinco elementos del DFA, incluyendo tipos `δ:Q×Σ→Q`, `q₀∈Q`, `F⊆Q`.
- [ ] Completo una tabla con una transición por estado y símbolo; sé cuándo añadir sumidero.
- [ ] Trazo una hilera entera, calculo `δ̂` y decido `ε` sin inventar una flecha ε.
- [ ] Construyo los DFA de «termina en `1`», «termina en `01`», «no termina en `00`» y sus complementos.
- [ ] Distingo el enunciado manuscrito `001` del dibujo `01` usando la hilera de prueba `01`.

## 12. Método para diseñar DFA difíciles: qué debe recordar el estado

**Conceptos de esta sección:** Procedimiento de diseño y prueba; patrón `GAGA`; restricciones `CC`/`A`; primer/último; longitud modular; divisibilidad por residuos; paridades y producto de estados.

**No empieces dibujando flechas.** Escribe una frase por estado: «he visto un prefijo de patrón», «el valor deja residuo 2», «hay un número impar de B». La frase debe bastar para decidir qué recordarás después de **cualquier** símbolo nuevo.

1. **Delimita el problema.** Escribe alfabeto, condición exacta y si `ε` debe aceptar. Para numerales, decide si `ε` representa cero y si se permiten ceros iniciales.
2. **Elige memoria finita.** No guardes toda la hilera: guarda solo lo que una continuación puede aprovechar (sufijo de patrón, último símbolo, residuo o paridad).
3. **Nombra estados con significado.** El estado inicial representa haber leído `ε`.
4. **Calcula cada transición.** Para cada par estado–símbolo, pregunta «¿qué información queda después de agregar esta letra?». Llena **toda** la tabla.
5. **Marca finales por condición.** Decidir finales después de definir los estados evita aceptar por accidente hileras inválidas.
6. **Intenta romper la solución.** Prueba `ε`, ejemplos cortos, patrones superpuestos y casos que deban caer en sumidero. Si una prueba falla, revisa la definición de estado o la transición que olvidó información.

### 12.1 Patrón prohibido con superposición: no contener `GAGA`

`Σ={A,T,C,G}`. **Idea del estado:** conserva el **sufijo más largo de lo leído que también es prefijo de `GAGA`**. Así se preserva un comienzo potencial aunque un intento anterior falle. Los prefijos propios del patrón son `ε`, `G`, `GA`, `GAG`; si aparece `GAGA`, el error ya es permanente.

| Estado (qué recuerda) | `A` | `T` | `C` | `G` | Acepta |
| --- | --- | --- | --- | --- | --- |
| `p0`: nada (`ε`), inicial | `p0` | `p0` | `p0` | `p1` | Sí |
| `p1`: termina en `G` | `p2` | `p0` | `p0` | `p1` | Sí |
| `p2`: termina en `GA` | `p0` | `p0` | `p0` | `p3` | Sí |
| `p3`: termina en `GAG` | `bad` | `p0` | `p0` | `p1` | Sí |
| `bad`: ya apareció `GAGA` | `bad` | `bad` | `bad` | `bad` | No |

**Flecha difícil:** desde `p3` con `G`, lo leído termina en `GAGG`. No se completó `GAGA`, pero la **última G** ya podría ser el inicio de una aparición futura, así que va a `p1`, no a `p0`. `GAGA` termina en `bad` y rechaza; `GAGG` termina en `p1` y acepta; `GAGGAGA` finalmente cae en `bad`. Como `ε` aún no contiene el patrón, `p0` es final.

### 12.2 Dos prohibiciones a la vez: `CC` y `A` sin `T` inmediata

La página 50 pregunta por hileras que **no contienen `CC`** y en las que **cada `A` está precedida por `T`**; su dibujo está incompleto. Aquí fijamos «precedida» como **inmediatamente precedida**. Para decidir la próxima letra basta saber si la **última** era `T`, `C` u otra (incluido no haber leído nada). Una infracción irreversible entra en `bad`:

| Estado | Leer `A` | Leer `T` | Leer `C` | Leer `G` | Acepta |
| --- | --- | --- | --- | --- | --- |
| `other` inicial: nada, `A` o `G` al final | `bad` | `t` | `c` | `other` | Sí |
| `t`: última fue `T` | `other` | `t` | `c` | `other` | Sí |
| `c`: última fue `C` | `bad` | `t` | `bad` | `other` | Sí |
| `bad`: regla violada | `bad` | `bad` | `bad` | `bad` | No |

**Por qué funciona:** después de `c`, leer `C` forma `CC`; después de un estado distinto de `t`, leer `A` incumple la condición de `T` inmediata. `ε`, `TA` y `CTAG` aceptan; `A`, `CA`, `CC` y `TACC` rechazan. Esta tabla es una **solución construida y verificada**, no una transcripción de flechas completas del cuaderno. Si «precedida por T» significara «alguna T en cualquier posición anterior», habría que resolver **otro** lenguaje.

### 12.3 Primer y último símbolo

Para binarias cuyo **primer y último símbolo son iguales**, antes de leer nada un estado `inicio` indica «no tengo extremos». Al leer el primer símbolo guardas ese valor (`0` o `1`); desde entonces el estado guarda el par `(primero,último)`. Leer otro símbolo cambia **solo el último**. Los cuatro pares alcanzables son `(0,0)`, `(0,1)`, `(1,0)`, `(1,1)`; aceptan `(0,0)` y `(1,1)`. La hilera `ε` no tiene primero ni último; el enunciado debe decir si se incluye. Para «no son iguales» en hileras no vacías aceptan los otros dos pares. Si se pide el **complemento formal** de un DFA total, también debe invertirse la aceptación del estado `inicio`.

### 12.4 Longitud módulo `k`

Si solo interesa `|w| mod k`, crea `k` estados para residuos `0,…,k−1`. **Cada símbolo** avanza un residuo porque añade una posición a la longitud. Para «longitud múltiplo de 3» acepta solo el residuo 0; `ε` tiene longitud cero y acepta. Para «longitud no múltiplo de 4» acepta residuos 1, 2 y 3; el inicial 0 rechaza. No crees un estado nuevo por cada longitud entera: cuatro residuos bastan para cualquier hilera.

### 12.5 Valor numérico módulo `m`

Al añadir el dígito `d` a la **derecha** de un número `n` en **base `b`**, el valor se convierte en `bn+d`. Si `n` deja residuo `r` al dividir entre `m`, la transición exacta es **`r'=(br+d) mod m`**. Ese cálculo crea la tabla completa de un DFA de residuos. No confundas el valor de una hilera de dígitos con su longitud.

**Decimales divisibles entre 3.** Como `10≡1 (mod 3)`, la actualización es `r'=(r+d) mod 3`. Agrupa dígitos `D0={0,3,6,9}`, `D1={1,4,7}`, `D2={2,5,8}`:

| Residuo actual | `D0` | `D1` | `D2` | Acepta |
| --- | --- | --- | --- | --- |
| `0`, inicial | `0` | `1` | `2` | Sí, bajo la convención del apunte `ε=0`. |
| `1` | `1` | `2` | `0` | No. |
| `2` | `2` | `0` | `1` | No. |

`12` hace `0→1→0` y acepta; `13` hace `0→1→1` y rechaza. En matemática usual un numeral debe tener por lo menos un dígito; los apuntes **adoptan** para este ejercicio `ε=0`. Si no se admite la hilera vacía, añade un estado inicial no final que al leer el primer dígito entra al estado de residuo correspondiente. Los ceros iniciales no cambian el residuo, pero su admisibilidad también depende del enunciado.

**Base 3, no divisible entre 5.** `Σ={0,1,2}`, `b=3`, `m=5`; estados `0,…,4`; finales `1,2,3,4`; transición `(3r+d) mod 5`:

| Residuo | Leer `0` | Leer `1` | Leer `2` | Acepta |
| --- | --- | --- | --- | --- |
| `0`, inicial | `0` | `1` | `2` | No |
| `1` | `3` | `4` | `0` | Sí |
| `2` | `1` | `2` | `3` | Sí |
| `3` | `4` | `0` | `1` | Sí |
| `4` | `2` | `3` | `4` | Sí |

`12₃=5₁₀` sigue `0→1→0` y rechaza; `20₃=6₁₀` sigue `0→2→1` y acepta. Aquí `ε` rechaza porque el estado inicial no es final; el numeral explícito `0` también rechaza.

### 12.6 Dos paridades y producto de memorias

La condición «**número par de `A` e impar de `B`**» sobre `{A,B}` necesita **dos bits de memoria**, no los conteos completos. Inicialmente `(par A,par B)`. Leer `A` cambia solo la primera paridad; leer `B` cambia solo la segunda. Los cuatro estados son `(P,P)`, `(I,P)`, `(P,I)`, `(I,I)`, y solo `(P,I)` acepta. `B` acepta; `AB` rechaza; `AAB` acepta.

Esta construcción es un **producto de estados**: si otro problema tiene dos DFA independientes con estados `q` y `r`, el nuevo estado `(q,r)` simula ambos. Para exigir **las dos** condiciones, acepta cuando ambos componentes cumplen; para «una u otra», cuando al menos uno cumple. Solo hay que dibujar los pares realmente alcanzables.

**Checklist — tema 12**

- [ ] Para cada problema escribo alfabeto, convención de `ε`, significado de estados, tabla completa y finales antes de probar hileras.
- [ ] Explico `GAGA` como «sufijo que es prefijo» y justifico la transición `GAG` + `G`.
- [ ] Resuelvo las dos restricciones `CC` y `A` después de `T` bajo la interpretación inmediata, indicando cuál tabla es nueva.
- [ ] Construyo estados para primer/último símbolo y decido la situación de `ε`.
- [ ] Construyo DFA de longitud múltiplo de 3 y no múltiplo de 4 sin crear estados infinitos.
- [ ] Derivo `(br+d) mod m`, lleno las tablas decimal/3 y ternaria/5 y compruebo `12`, `13`, `12₃`, `20₃`.
- [ ] Construyo los cuatro estados de paridad y sé cuándo usar producto y qué pares aceptan.

# Parte IV. Lecturas asignadas, una por una

## 13. Fischer y LeBlanc, *Crafting a Compiler with C*, capítulo 2

**Conceptos de esta sección:** Compilador sencillo de una pasada, secuencia caracteres→tokens→estructura→acciones→código y localización de errores.

**Objetivo de la lectura:** construir un compilador lo bastante pequeño para ver el recorrido **completo**. Empieza con texto, reconoce categorías, analiza construcciones, efectúa acciones semánticas y produce código. No es una afirmación de que todos los compiladores deban copiar su estructura exacta.

**Recorrido con `a := b+2`.** El scanner distingue los lexemas `a`, `:=`, `b`, `+`, `2` y entrega tokens como `IDENTIFICADOR`, `ASIGNACIÓN`, `IDENTIFICADOR`, `SUMA`, `ENTERO`. El parser comprueba que corresponde a una asignación cuya expresión es una suma. Una acción semántica encuentra los símbolos `a` y `b`, comprueba o utiliza sus atributos y decide qué código emitir; el generador carga `b`, suma 2 y almacena en `a`. El diseño sencillo puede generar código **a medida que** el parser reconoce la construcción. Por eso es posible un compilador **de una pasada** y **sin AST explícito** en este ejemplo; un AST es una técnica útil, no una obligación lógica del verbo «compilar».

**Qué demuestra cada error:** un carácter que no pertenece a ningún token falla en el scanner; una secuencia `a := b+` falla en el parser porque falta término; una suma de tipos incompatibles falla en las comprobaciones semánticas si la gramática sí aceptó la forma. La lectura te enseña a localizar la pregunta que cada componente responde, no a repetir una lista de nombres.

**Checklist — lectura 13**

- [ ] Sigo un programa sencillo desde caracteres hasta código sin saltarme la decisión que toma cada etapa.
- [ ] Distingo token de lexema, parser de acción semántica y tabla de símbolos de código generado.
- [ ] Explico por qué un diseño didáctico de una pasada no necesita AST/IR explícitos y por qué otro compilador sí podría usarlos.

## 14. Patrick, *General Motors/North American Monitor for the IBM 704 Computer*

**Conceptos de esta sección:** Motivación del procesamiento por lotes, monitor del IBM 704, tres fases, tarjetas de control y equipos históricos.

**Pregunta de la lectura:** ¿cómo evitar que una computadora costosa quedara ociosa entre trabajos preparados manualmente? El **monitor GM/NAA** coordina una secuencia de trabajos para el **IBM 704**. Cada trabajo puede contener datos, opciones y, si corresponde, pasos de traducción de un programa; el monitor organiza todo eso. La exposición de Patrick distingue **traducción de entrada**, **cálculo** y **traducción de salida**. La primera prepara datos e instrucciones; la segunda efectúa el trabajo; la tercera presenta resultados para el usuario.

**Ejemplo de tres trabajos:** si se ejecutan A, B y C, el operador no tiene que reconstruir manualmente el control completo entre A y B ni entre B y C; las tarjetas de control y el monitor indican qué sigue. El sistema busca mejor utilización de la máquina. Un compilador FORTRAN o un ensamblador puede formar parte de la preparación de A, pero no es el programa que administra por sí mismo los tres trabajos. **Robert L. Patrick** propuso/describió la arquitectura histórica; **Owen Mock** y **George Ryckman** dirigieron equipos participantes. El artículo se publicó después de los hechos que relata: distingue **fecha del relato** y **fecha del sistema**.

**Checklist — lectura 14**

- [ ] Explico el costo de los tiempos ociosos y cómo un monitor pasa de un trabajo al siguiente.
- [ ] Nombro las tres fases y digo qué ocurre en cada una.
- [ ] Distingo el papel de Patrick, Mock y Ryckman; monitor, compilador y sistema operativo moderno.

## 15. Tanenbaum y colaboradores, *A Practical Tool Kit for Making Portable Compilers* (ACK)

**Conceptos de esta sección:** Arquitectura del ACK, EM, frentes/posteriores, optimización, ejemplo `K := I+7` y reutilización entre lenguajes y destinos.

**Pregunta de la lectura:** ¿cómo construir compiladores para varios lenguajes y varias máquinas sin reescribir toda la traducción para cada pareja? El **front end** lee un lenguaje y produce **EM**, representación intermedia de una máquina abstracta de pila. El **back end** traduce EM a ensamblador de un destino. La cadena también puede preprocesar, optimizar EM, optimizar código destino, ensamblar, enlazar e interpretar EM para pruebas. «Portabilidad» significa reutilizar componentes al cambiar lenguaje o máquina; no que un mismo archivo binario funcione mágicamente en toda CPU.

**Ejemplo del artículo:** `K := I+7` se transforma en una secuencia EM como `LOL I; LOC 7; ADI 2; STL K`. Si añades un lenguaje nuevo, escribes un frente que produzca EM; si añades una CPU, escribes un posterior que consuma EM. Un optimizador **peephole** puede mejorar una secuencia local de EM y beneficiar varias máquinas; un optimizador específico del destino puede aprovechar instrucciones particulares de una CPU. **UNCOL** nombra la idea de intermedio común; EM es la realización concreta en ACK. La comparación `N+M` frente a `N×M` explica **cuántas combinaciones de traductores se evitan**, sin contar bibliotecas, pruebas y mantenimiento.

**Checklist — lectura 15**

- [ ] Explico entrada y salida de front end, EM, optimizador y back end.
- [ ] Interpreto la secuencia `LOL/LOC/ADI/STL` de una asignación sencilla.
- [ ] Comparo ACK con Pascal-P: objetivo de muchos lenguajes/máquinas frente a transporte de Pascal.
- [ ] Justifico la cuenta aproximada de reutilización e identifico sus costos no incluidos.

## 16. Pinker, *The Language Instinct*, capítulo 1: «An Instinct to Acquire an Art»

**Conceptos de esta sección:** Instinto/órgano mental como tesis, universalidad, productividad, escritura, gramática mental, Chomsky/GU y crítica al SSSM.

**Pregunta del capítulo:** ¿por qué los humanos aprenden lenguas naturales y crean oraciones que nunca habían oído? **Steven Pinker sostiene** que la **capacidad de adquirir lenguaje** tiene bases biológicas y fue favorecida evolutivamente; llama «instinto» a esa predisposición. No sostiene que el bebé nazca sabiendo **una lengua concreta**: aprende la de su comunidad mediante exposición e interacción. «**Órgano mental**» es una comparación para una función especializada de la mente, no un órgano aislado identificable como el hígado. La explicación por **selección natural** es la tesis defendida en la lectura; los detalles de la evolución del lenguaje siguen investigándose.

**Universalidad y productividad.** Todas las comunidades humanas conocidas tienen sistemas lingüísticos organizados. No tener escritura ni prestigio social no convierte una lengua en «primitiva». Sus hablantes pueden combinar recursos para decir y entender mensajes **nuevos**: eso es **productividad**, no una memoria de todas las oraciones posibles. La **escritura** es una tecnología cultural que suele requerir enseñanza deliberada; el aprendizaje ordinario de habla o señas ocurre en una comunidad lingüística sin clase formal de reglas.

**Gramática mental y gramática universal.** La **gramática mental** son patrones implícitos que una persona usa para hablar y comprender; no es el manual escolar de «hablar bien». **Noam Chomsky** impulsó las **gramáticas generativas**, reglas que describen cómo formar estructuras nuevas, y la hipótesis de una **gramática universal (GU)**: predisposiciones o restricciones compartidas por humanos al adquirir lenguas. No es un idioma que toda persona hable ni una lista cerrada de palabras heredadas. El capítulo usa el hecho de que se aprenden estructuras a partir de ejemplos finitos para motivar esa hipótesis; no demuestra por sí solo exactamente qué reglas son innatas.

**Crítica al SSSM.** El *Standard Social Science Model* que Pinker cuestiona, en su versión extrema, trata la mente como una **tabla rasa** que la cultura moldea por completo. Su respuesta es que aprender de un entorno requiere mecanismos del aprendiz. No elimina el papel del entorno: la predisposición hace posible aprender, mientras la comunidad determina **qué lengua** se aprende y proporciona datos e interacción. **Ejemplo:** una persona no infiere las palabras del español sin encontrarse con hablantes o señantes; tampoco basta memorizar frases si debe comprender combinaciones nuevas.

| Si te preguntan… | Respuesta centrada en el capítulo |
| --- | --- |
| «¿El lenguaje es una invención cultural?» | Pinker considera biológica la **capacidad** de adquirir lenguas; las lenguas concretas y la escritura tienen historia y transmisión cultural. |
| «¿Hay lenguas primitivas?» | No en el sentido de lenguas naturales carentes de gramática estructurada por ausencia de escritura o tecnología. |
| «¿Qué es GU?» | Hipótesis sobre predisposiciones/restricciones de la facultad humana de aprender gramáticas, no una lengua universal. |
| «¿Qué rechaza del SSSM?» | La versión de mente completamente indiferenciada y moldeada solo desde fuera; no rechaza la experiencia. |

**Checklist — lectura 16**

- [ ] Explico la tesis de Pinker como tesis, separando predisposición, lengua concreta, exposición y escritura.
- [ ] Defino productividad y universalidad con un ejemplo que no dependa de alfabetización.
- [ ] Distingo gramática mental, reglas escolares, gramática generativa y GU.
- [ ] Explico la crítica a la tabla rasa sin afirmar que el entorno no importa.

## 17. Pinker, capítulo 2: «Chatterboxes»

**Conceptos de esta sección:** Pidgin/criollo, Bickerton, LSN/ISN, Simon, BEV/AAVE/Labov, pobreza del estímulo, *motherese*, disociaciones, Broca, familia KE/FOXP2 y Williams.

**Pregunta del capítulo:** ¿qué enseñan casos de contacto lingüístico, señas, dialectos y neurología acerca de la adquisición de lenguaje? Léelos como **evidencias con alcance definido**. El ejemplo dado en clase puede estar simplificado; aquí se explica qué muestra y qué **no** permite concluir.

### 17.1 Contacto lingüístico y regularización infantil

| Caso | Definición y hecho relevante | Conclusión permitida; límite |
| --- | --- | --- |
| **Pidgin** | Forma de comunicación que surge entre hablantes sin lengua compartida y normalmente no comienza como lengua materna. | Puede tener convenciones; llamarlo «jerga sin gramática alguna» oculta su estructura. |
| **Criollo (*creole*)** | Lengua comunitaria plenamente funcional desarrollada en un contexto de contacto y transmitida entre hablantes. | La nativización y el papel de niños son relevantes en casos estudiados por Pinker, pero no todos los criollos surgieron por una secuencia idéntica y súbita. **Derek Bickerton** se asocia con hipótesis de criollización. |
| **LSN/ISN** | Etiquetas usadas para etapas/cohortes de la **Lengua de Señas Nicaragüense**: niños sordos compartieron y desarrollaron convenciones; cohortes posteriores sistematizaron recursos gramaticales espaciales. | **Ann Senghas y Marie Coppola** estudiaron esa sistematización; no son dos lenguas independientes ni una creación sin base comunicativa anterior. Las señas son una lengua natural, no español codificado gesto a gesto. |
| **Simon** | Niño sordo expuesto a ASL (*American Sign Language*) de padres que usaban ciertos **morfemas** —unidades de forma y función gramatical— de modo inconsistente. | **Jenny Singleton y Elissa Newport** encontraron más regularidad en varios patrones producidos por Simon; no demostraron una gramática «perfecta» en todos los aspectos ni aprendizaje sin entrada. |

**Ejemplo que une los casos:** cuando las formas que oye o ve un niño varían, puede detectar patrones y usar algunos de manera más regular. Eso es más preciso que decir «los niños inventan de la nada un idioma entero». La primera cohorte nicaragüense también organizó recursos sobre los que trabajaron cohortes posteriores.

### 17.2 Dialectos, datos de aprendizaje y diferencias cognitivas

**BEV** (*Black English Vernacular*), hoy a menudo **AAVE**, es una variedad del inglés afroamericano estudiada por **William Labov**. Posee reglas propias; el **be habitual**, por ejemplo, marca que una situación ocurre de manera acostumbrada. Juzgar esa construcción con la gramática del inglés estándar y declararla «error sin reglas» confunde **prestigio social** con **estructura lingüística**. BEV/AAVE no es un pidgin ni inglés pronunciado al azar.

La **pobreza del estímulo** plantea que la entrada que recibe el niño es finita, variable y no trae un manual de todas las reglas y contraejemplos. Una regla sintáctica puede depender de la **estructura** de una oración, no del primer verbo que aparezca al leerla de izquierda a derecha. Este argumento motiva investigar restricciones o capacidades del aprendizaje; por sí mismo no determina una GU exacta. **Motherese** es el habla dirigida a niños con rasgos como entonación adaptada. Pinker señala que una forma especial de habla infantil no es un requisito **universal estricto**; esto **no** significa que exposición e interacción lingüística sean prescindibles.

**Disociación** significa que dos capacidades no siempre cambian juntas. **Doble disociación** compara perfiles opuestos: una capacidad relativamente débil junto a otra relativamente conservada y otro caso con un patrón inverso. Es evidencia de componentes parcialmente diferenciables, **no** de aislamiento absoluto del lenguaje respecto a inteligencia, movimiento o entorno.

| Caso clínico de la lectura | Qué se observa | Lo que sería una exageración |
| --- | --- | --- |
| **Afasia de Broca** | Una lesión adquirida puede causar habla lenta, poco fluida y dificultades gramaticales; algunas otras capacidades se conservan relativamente mejor. | «Toda la comprensión y toda la inteligencia lógica quedan intactas». La comprensión de estructuras complejas también puede verse afectada. |
| **Familia KE y Myrna Gopnik** | Familia con dificultades heredables de habla y lenguaje, incluidas tareas morfológicas; investigaciones posteriores relacionaron el caso con **FOXP2** y dificultades motoras del habla. | «Existe un único gen de la gramática» o «todos los trastornos específicos/del desarrollo del lenguaje (SLI/DLD) son idénticos». |
| **Síndrome de Williams y Ursula Bellugi** | En algunas personas ciertas habilidades verbales son relativamente fuertes frente a dificultades en otros dominios, en particular visoespaciales; hay variación individual. Suele deberse a una deleción de varios genes en **7q11.23, cromosoma 7**. | «Todas tienen retraso cognitivo severo y lenguaje perfecto». La referencia antigua del libro al cromosoma 11 quedó superada. |

**Checklist — lectura 17**

- [ ] Comparo pidgin/criollo sin llamar al primero «ausencia total de reglas» y relaciono Bickerton con hipótesis, no con ley universal.
- [ ] Explico LSN/ISN como cohortes y el aporte de Senghas/Coppola; explico Simon y Singleton/Newport sin «perfección».
- [ ] Defino BEV/AAVE y doy un ejemplo de regla documentada por Labov.
- [ ] Explico pobreza del estímulo, estructura y *motherese* distinguiendo ausencia de instrucción formal de ausencia de exposición.
- [ ] Distingo disociación, afasia de Broca, familia KE/FOXP2/SLI y Williams con conclusiones y límites precisos.

# Parte V. Repaso verificable

## 18. Quices: enunciado conocido y núcleo de la respuesta

**Conceptos de esta sección:** Preguntas de quices 01–05 y dos recuerdos del quiz no aplicado; *amathia*, historia, VOLE, diagramas T, MICRO, Pinker, DFA e hileras.

Los quices **01–05** se reconstruyeron a partir de las fotografías compartidas y tienen respuestas desarrolladas en [el documento de quices](../documento.md). Esta tabla da el **núcleo que debes poder explicar**, sin sustituir los ejercicios completos de las secciones anteriores.

| Quiz y pregunta | Respuesta que demuestra comprensión |
| --- | --- |
| **01. ¿Qué es *amathia* y por qué importa en la universidad?** | En el sentido usado en el quiz, ignorancia acompañada de confianza infundada en que se sabe. Se combate al probar una afirmación y admitir una laguna: si mi DFA acepta `01` cuando debía exigir `001`, la prueba revela lo que aún no domino. |
| **01. McCarthy, *First Draft*, Wilkes, FORTRAN, *fetch*, LISP, Hopper, control alambrado, productividad/eficiencia.** | McCarthy→LISP/IA; *First Draft*→EDVAC/von Neumann; Wilkes→EDSAC/microprogramación; FORTRAN→equipo de Backus y fórmulas; *fetch*→PC trae instrucción a IR; Hopper→A-0/FLOW-MATIC; control alambrado→lógica fija; productividad humana y costo de ejecución son medidas distintas. |
| **02. Chomsky y GU.** | Hipótesis de capacidades/restricciones humanas para adquirir gramáticas; no un idioma común. Las gramáticas generativas modelan estructuras que permiten nuevas expresiones. |
| **02. Speedcoding del IBM 701.** | Sistema interpretativo de Backus y colaboradores para facilitar cálculo numérico; no confundir con el compilador FORTRAN del IBM 704. |
| **02. VOLE: sumar 16 bytes y dividir.** | Distinguir suma matemática de `RA` módulo 256; dividir cada byte en cociente/residuo por 16 y combinar subtotales para `RF`. Seguir la modificación `11B0→11B1` del programa del tema 3. |
| **03. Enlace dinámico, relocalización, backpatching.** | Biblioteca compartida resuelta al cargar/correr; ubicación de objeto que requiere ajuste; salto provisional completado al conocer destino. No son tres nombres para un mismo paso. |
| **03. Zurich frente a ACK.** | Pascal-P/P-machine facilita llevar Pascal; ACK/EM reutiliza frentes/posteriores de varios lenguajes y máquinas. Ambos usan intermedio de pila, con metas distintas. |
| **03. Diagramas T con C v7/v10, Fortran→C y COBOL.** | Compilar v10 con v7, compilar traductor Fortran→C con C ejecutable; transportar el compilador COBOL requiere su **fuente Fortran** si el binario es incompatible. |
| **04. Pidgin, criollo, Broca, BEV, LSN.** | Dar una definición y un límite de cada uno: contacto frente a lengua comunitaria; afasia adquirida; variedad con reglas; lengua de señas natural entre cohortes. |
| **04. E/S y condicional de MICRO.** | `read/write` se reconocen en scanner/parser y generan llamadas a `scanf/printf`; `(E1|E2|E3)` compara `E1` con cero y ejecuta solo la rama elegida. |
| **05. Fases de compilador típico.** | Caracteres→tokens→sintaxis→semántica→IR si se usa→optimización→código; ensamblado, enlace y carga son pasos posteriores de cadena, no necesariamente internos al compilador. |
| **Quiz posterior no aplicado: DFA, neutro, `ECCI`.** | DFA=`(Q,Σ,δ,q₀,F)` con transición total; `ε` neutro de hileras, `{ε}` neutro de concatenación de lenguajes; `Pref(ECCI)={ε,E,EC,ECC,ECCI}` y `Suf(ECCI)={ε,I,CI,CCI,ECCI}`. **Las demás preguntas no se conocen.** |

**Checklist — tema 18**

- [ ] Puedo responder cada fila sin depender solo de nombres: siempre añado un ejemplo o una prueba.
- [ ] Cuando falta una parte del enunciado, digo cuál es la condición necesaria en vez de inventarla (fuente del compilador COBOL; preguntas no recordadas).

## 19. Índice de figuras históricas por aporte

**Conceptos de esta sección:** Personas de historia computacional, lenguajes, compiladores, autómatas y estudios de adquisición del lenguaje.

Esta tabla es de **consulta rápida** después de estudiar las secciones explicadas. Sirve para contestar «¿quién hizo qué?» sin confundir personas con máquinas, lenguajes o teorías.

| Persona(s) | Aporte relacionado con la materia |
| --- | --- |
| **Mauchly y Eckert** | Dirección de ENIAC y participación en el diseño de EDVAC. |
| **Von Neumann** | Redacción del *First Draft* sobre EDVAC y difusión de la organización de programa almacenado. |
| **Maurice Wilkes** | EDSAC y propuesta de microprogramación. |
| **Roy Nutt** | SAP, ensamblador simbólico del IBM 704 en los apuntes. |
| **John Backus** | Speedcoding, dirección de FORTRAN y nombre BNF. |
| **Grace Hopper** | A-0 y FLOW-MATIC; influencia en COBOL. |
| **John McCarthy** | LISP e IA temprana. |
| **Peter Naur** | ALGOL y nombre BNF. |
| **Niklaus Wirth** | Pascal y su implementación portable. |
| **Stephen Cole Kleene** | Clausura `*` de lenguajes formales. |
| **Robert L. Patrick; Owen Mock; George Ryckman** | Arquitectura narrada y equipos del monitor GM/NAA. |
| **Charles N. Fischer y Richard J. LeBlanc** | Compilador didáctico del capítulo 2. |
| **Andrew S. Tanenbaum y coautores** | ACK y EM como cadena de portabilidad. |
| **Steven Pinker** | Tesis de la capacidad lingüística especializada; capítulos 1–2. |
| **Noam Chomsky** | Gramáticas generativas y debate sobre GU. |
| **William Labov** | Reglas de variedades del inglés afroamericano. |
| **Derek Bickerton** | Hipótesis sobre criollización. |
| **Ann Senghas y Marie Coppola** | Evolución de recursos gramaticales entre cohortes de señas nicaragüenses. |
| **Jenny Singleton y Elissa Newport** | Regularización de patrones de ASL en Simon. |
| **Myrna Gopnik** | Estudio lingüístico de la familia KE. |
| **Ursula Bellugi** | Perfil lingüístico y cognitivo de personas con síndrome de Williams. |

**Checklist — tema 19**

- [ ] Al oír cada nombre identifico una contribución y el concepto que ilustra, sin confundir autor de un artículo con inventor exclusivo de una tecnología colectiva.
- [ ] Puedo distinguir las figuras de adquisición de lenguaje de las de computación, traducción y autómatas.

## 20. Práctica corta para comprobar si la guía funciona por sí sola

**Conceptos de esta sección:** Siete ejercicios con solución sobre lenguajes, DFA, bases numéricas, VOLE, diagramas T, MICRO y lectura crítica de Pinker.

**1. Hileras y lenguajes.** Sobre `Σ={0,1}`, sea `L={ε,01}` y `M={1}`. ¿Cuáles son `LM`, `L²` y `∅*`? ¿Está `ε` en `L+`? **Solución:** `LM={1,011}`; `L²={ε,01,0101}`; `∅*={ε}`; sí, `ε∈L+` porque `ε∈L` y se permite tomar un factor de `L`. El paso esencial es hacer las concatenaciones y luego quitar duplicados.

**2. DFA de `GAGA`.** ¿Acepta `GAGG`? ¿Y `GAGGAGA`? **Solución:** el primero termina en el estado «sufijo G» y acepta; el segundo termina en `bad` cuando la G que quedó como posible comienzo completa `GAGA` con `AGA`. La flecha de `GAG` tras `G` vuelve a «G», no a «nada».

**3. Divisibilidad en bases.** ¿Por qué `12₃` rechaza el DFA «no divisible por 5»? **Solución:** `12₃=1×3+2=5`; por fórmula, residuo `0→1→(3×1+2) mod 5=0`; el residuo 0 no es final. En cambio `20₃=6`, residuo `0→2→1`, acepta.

**4. VOLE y desbordamiento.** Si `RA=01` y `R1=FF`, ¿qué deja `5AA1` en `RA`? **Solución:** `01+FF=100₁₆`, pero solo cabe el byte bajo: `RA=00`; el acarreo indica el exceso. El promedio del problema grande no debe deducirse de ese `RA` truncado.

**5. Diagramas T.** Un traductor Fortran→C está escrito en C, pero solo tienes su **fuente**. ¿Puede traducir ya un archivo Fortran? **Solución:** no; primero se necesita un compilador C **ejecutable en la anfitriona** para convertir el propio traductor en ejecutable. Después sí podrá transformar fuente Fortran en fuente C.

**6. MICRO.** `read(x); write((0 | x+1 | 7));` recibe `4`. ¿Qué imprime? **Solución:** `7`; el primer valor del condicional es cero y se ejecuta **solo** la tercera expresión. El hecho de que el compilador haya generado código para `x+1` no obliga a ejecutarlo.

**7. Lectura de Pinker.** ¿Qué sería incorrecto en «Simon aprendió sin entrada lingüística una gramática perfecta»? **Solución:** tuvo exposición a ASL de sus padres, aunque con patrones inconsistentes; se observó regularización de varios morfemas, no perfección completa ni aprendizaje sin contacto. La conclusión debe ajustarse a la evidencia.

**Checklist — tema 20**

- [ ] Resuelvo las siete preguntas sin consultar la solución; después explico dónde usé una definición y dónde una convención del enunciado.

## Fuentes y límites de los apuntes

- [Transcripciones 1–10](../apuntes/semana-1-clases-1-y-2.md), [11–19](../apuntes/paginas-11-19-continuacion.md), [20–28](../apuntes/paginas-20-28-continuacion.md), [29–38](../apuntes/paginas-29-38-continuacion.md), [39–43](../apuntes/paginas-39-43-continuacion.md), [44–50 y hoja siguiente](../apuntes/paginas-44-50-continuacion.md), [preguntas de quices](../documento.md) y [diccionario de 177 conceptos](../apuntes/indice-temas-y-diccionario.md).
- Lecturas del curso: [Fischer–LeBlanc, capítulo 2](../projects/Fischer-Cap2.pdf), [Patrick](../readings/0101%20-%20Patrick.pdf), [ACK](../readings/ACK.pdf) y [desarrollo contrastado de Pinker 1–2](../conceptos-lecturas.md).
- Verificación externa: [Computer History Museum](https://www.computerhistory.org/), [IBM sobre FORTRAN](https://www.ibm.com/history/fortran), [Patrick/RAND](https://www.rand.org/pubs/papers/P7316.html), [artículo de ACK](https://tack.sourceforge.net/olddocs/toolkit.html), [definición de DFA en MIT OCW](https://ocw.mit.edu/courses/6-045j-automata-computability-and-complexity-spring-2011/pages/lecture-notes/), [Senghas–Coppola](https://siegler.tc.columbia.edu/wp-content/uploads/2020/08/Children_Creating_Language_How_Nicaraguan_Sign_Lan.pdf), [Singleton–Newport](https://pubmed.ncbi.nlm.nih.gov/15342259/), [familia KE/FOXP2](https://www.nature.com/articles/35097076/) y [MedlinePlus sobre Williams](https://medlineplus.gov/genetics/condition/williams-syndrome/).

**Límites concretos:** el diagrama de página 48 representa `01` pese a que su rótulo parece `001`; el ejercicio de `CC`/`A` en página 50 no tiene una tabla terminada y la solución aquí fija el significado de «precedida»; el quiz posterior no se aplicó y solo dos preguntas fueron recordadas. No se convierten esas lagunas en supuestas certezas.
