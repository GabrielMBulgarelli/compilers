# Guía integral de estudio — Compiladores, primer parcial

**Qué cubre.** Los apuntes manuscritos numerados 1–50 y una hoja posterior sin número, los quices 01–05, las dos preguntas recordadas del quiz que no se aplicó, el capítulo 2 de Fischer y LeBlanc, los capítulos 1–2 de Pinker, Patrick sobre el monitor GM/NAA y Tanenbaum y colaboradores sobre ACK. Los ejercicios de **ensamblador VOLE** sí entran; la lectura separada de VOLE, el capítulo 3 de Pinker y los NDAs quedan fuera conforme a lo indicado. Cuando un dibujo de los apuntes es incompleto, se dice; una solución construida aquí se identifica como tal.

**Cómo usar los checklists.** Lee cada explicación; luego tapa la página e intenta satisfacer cada casilla con palabras propias o con una solución escrita. Marcar una casilla significa poder justificar y probar la respuesta, no reconocer una palabra. El [diccionario de 177 entradas](indice-temas-y-diccionario.md) sirve como índice alfabético por bloques, y las fuentes están enlazadas al final.

## 1. Del programa cableado al lenguaje de alto nivel — páginas 1–7

### 1.1 ENIAC, EDVAC, EDSAC y programa almacenado

Una computadora ejecuta instrucciones; la diferencia histórica decisiva fue **cómo se le daban**. ENIAC, desarrollado bajo la dirección de **John Mauchly y J. Presper Eckert**, requería originalmente configurar conexiones y controles para cambiar de problema. En una máquina de **programa almacenado**, instrucciones y datos se representan en memoria. La CPU puede leer la próxima instrucción como una secuencia de bits y avanzar sin que alguien vuelva a cablear la máquina. El *First Draft of a Report on the EDVAC* (1945), redactado por **John von Neumann**, divulgó una organización influyente de esta idea; el diseño de EDVAC fue trabajo de más personas, entre ellas Eckert y Mauchly. **EDVAC** es el proyecto del informe; **EDSAC** es otra computadora, en Cambridge, dirigida por **Maurice Wilkes**, que ejecutó programas en 1949. Wilkes también propuso implementar el control de la CPU mediante **microprogramas**. ENIAC significa *Electronic Numerical Integrator and Computer*; EDSAC, *Electronic Delay Storage Automatic Calculator*.

**Ejemplo de causa y efecto.** Si las instrucciones `cargar`, `sumar`, `guardar` están en memoria, la CPU puede pasar de una a la siguiente siguiendo un contador; esa organización hace útil escribir un programa simbólico y traducirlo a bits. La máquina no «entiende FORTRAN»: entiende su propio juego de instrucciones. [Historia: Computer History Museum](https://www.computerhistory.org/revolution/birth-of-the-computer/4/88).

**Checklist — tema 1.1**

- [ ] Explico qué cambiaba físicamente al reprogramar ENIAC y qué cambia al almacenar instrucciones en memoria.
- [ ] Distingo ENIAC, EDVAC, EDSAC y sus personas asociadas sin atribuir toda la invención a von Neumann.
- [ ] Explico qué describe el *First Draft* y por qué EDSAC y microprogramación se asocian con Wilkes.

### 1.2 IBM 701/704, Speedcoding y los lenguajes fundacionales

**IBM 701** fue la primera computadora electrónica científica de IBM; **IBM 704** fue una sucesora importante para FORTRAN y para el monitor de la lectura de Patrick. **John Backus** y colaboradores hicieron **Speedcoding** para facilitar cálculos numéricos en el 701: un intérprete ejecutaba seudoinstrucciones de mayor nivel, con costo de tiempo y memoria. Más tarde Backus dirigió en IBM el equipo que construyó **FORTRAN**, un lenguaje compilado para cálculo científico; el nombre procede de *Formula Translation*, no «Formal Translation». La **BNF** (*Backus–Naur Form*) expresa reglas de sintaxis mediante producciones; **Peter Naur** participó en la definición de **ALGOL** y en la historia de esa notación. [IBM sobre FORTRAN](https://www.ibm.com/history/fortran).

**Grace Hopper** trabajó en A-0 y FLOW-MATIC; este último influyó en **COBOL**, orientado a datos comerciales y administrativos, desarrollado mediante un esfuerzo colectivo. **John McCarthy** creó **LISP**, ligado al procesamiento de listas, expresiones simbólicas e investigación temprana en IA; sus implementaciones impulsaron la **recolección de basura**, que recupera memoria que el programa ya no puede alcanzar. **ALGOL** influyó en los bloques y la descripción formal de lenguajes; **Niklaus Wirth** diseñó **Pascal**, que retomaremos en portabilidad. No memorices solo el nombre: asocia *problema → lenguaje → persona*: cálculo numérico → FORTRAN/Backus; negocio → COBOL/Hopper como influencia; listas/IA → LISP/McCarthy; notación y bloques → ALGOL/Naur; enseñanza y transporte → Pascal/Wirth.

**Checklist — tema 1.2**

- [ ] Distingo IBM 701 de 704 y Speedcoding interpretado de FORTRAN compilado.
- [ ] Relaciono Backus con FORTRAN y BNF; Naur con ALGOL y BNF; Wirth con Pascal.
- [ ] Explico por qué Hopper influyó en COBOL sin llamarla su única creadora.
- [ ] Relaciono McCarthy, LISP, listas, IA y memoria recuperable.
- [ ] Comparo FORTRAN, LISP, COBOL, ALGOL y Pascal por su propósito o aporte.

## 2. Cómo ejecuta instrucciones una máquina — páginas 7–13 y quiz 01

### 2.1 CPU, registros, control y ciclo de instrucción

La **CPU** contiene registros para valores inmediatos, una unidad que opera sobre datos y una **unidad de control** que ordena pasos. El **PC** (*program counter*) guarda la dirección de la próxima instrucción; el **IR** (*instruction register*) conserva la instrucción recuperada. En *fetch* se lee la instrucción desde memoria usando el PC; después se **decodifica** qué operación significa y se **ejecuta**. El PC suele avanzar a la siguiente instrucción durante la búsqueda, pero un salto puede reemplazarlo por una dirección de destino. No confundas el contenido de PC con el dato al que apunta.

La unidad de control **alambrada** produce señales mediante lógica fija; la **microprogramada** las organiza como una secuencia de **microinstrucciones internas**. Una microinstrucción no es una línea de FORTRAN ni la instrucción máquina que escribió el programador. **RISC/CISC** son enfoques de diseño de conjuntos de instrucciones; no equivalen a una prueba automática de que un programa o CPU será más rápido. Una **máquina multinivel** permite ver capas: hardware/control, conjunto de instrucciones, servicios de SO, ensamblador y lenguajes superiores. Cada capa expone operaciones que se implementan en otra inferior.

**Ejemplo.** En VOLE, si PC=`00`, los bytes `20 C0` forman IR=`20C0` y PC pasa a `02` antes de ejecutar la carga inmediata. Un salto posterior puede poner PC=`0E`: no obliga a continuar por `04`.

**Checklist — tema 2.1**

- [ ] Narro búsqueda, decodificación y ejecución indicando cómo cambian PC e IR.
- [ ] Distingo registro, memoria, dirección, dato y código de operación.
- [ ] Comparo control alambrado, control microprogramado y microinstrucción.
- [ ] Explico capas de una máquina multinivel y el alcance de RISC/CISC.

### 2.2 Lenguaje máquina, ensamblador, nivel alto y direcciones

El **lenguaje máquina** es la codificación que ejecuta una CPU específica. El **ensamblador** representa sus instrucciones y ubicaciones con símbolos legibles; un **ensamblador** (programa) convierte esa notación en bytes. Un **lenguaje de alto nivel** expresa tareas sin escribir cada movimiento de registros: facilita la **productividad**, cantidad de trabajo útil por esfuerzo de desarrollo. La **eficiencia de ejecución** mide recursos consumidos, como tiempo y memoria. Mejorar una no implica automáticamente mejorar la otra. **SAP** (*Symbolic Assembly Program*), asociado con Roy Nutt e IBM 704 en los apuntes, ilustra la evolución de ensambladores simbólicos.

Al generar código importa cuántos operandos nombra una instrucción. En una máquina de **tres direcciones**, `ADD t,a,b` deja `t=a+b`; en una de **dos**, `ADD a,b` puede reemplazar `a`; en una de **una**, un acumulador implícito guarda el resultado; en una de **cero**, `PUSH a; PUSH b; ADD` consume los dos valores superiores de una pila y deja su suma. El conteo se refiere a campos explícitos de la instrucción, no a la cantidad matemática de variables del programa.

**Checklist — tema 2.2**

- [ ] Puedo transformar una suma en versiones conceptuales de tres, dos, una y cero direcciones.
- [ ] Distingo la notación ensamblador del traductor llamado ensamblador y de bytes ejecutables.
- [ ] Doy un ejemplo concreto de productividad frente a eficiencia y ubico SAP históricamente.

## 3. VOLE: leer instrucciones y resolver un programa — página 13 y quiz 02

VOLE tiene **16 registros** `R0`–`RF` de un byte, **256 posiciones de memoria** `00`–`FF`, un PC de ocho bits y un IR de 16 bits. Cada instrucción ocupa **dos bytes**: cuatro dígitos hexadecimales, como `20C0`. Cada dígito hexadecimal codifica cuatro bits (**un nibble**); dos nibbles forman un byte. El primero señala la operación y los otros campos se interpretan según esa operación. En el modelo usado por el quiz, `20C0` pone `C0` en `R0`; `11B0` carga en `R1` el contenido de `M[B0]`; `3004` escribe `R0` en `M[04]` (el `04` es dirección, no registro 04). Hay que comprobar siempre el formato de **cada opcode**, no leer todos los campos como si significaran lo mismo.

| Patrón de los ejercicios | Efecto usado aquí | Ejemplo |
| --- | --- | --- |
| `2RXY` | Cargar el byte inmediato `XY` en `RR`. | `20C0`: `R0←C0`. |
| `1RXY` | Cargar de memoria `M[XY]` a `RR`. | `11B0`: `R1←M[B0]`. |
| `3RXY` | Guardar `RR` en `M[XY]`. | `3004`: `M[04]←R0`. |
| `40RS` | Copiar del registro indicado por el tercer dígito al indicado por el cuarto. | `4015`: `R5←R1`. |
| `5RST` | Sumar bytes de `RS` y `RT` y guardar en `RR` módulo 256. | `5AA1`: `RA←RA+R1`. |
| `8RST` | AND bit a bit de `RS` y `RT` a `RR`. | `8416`: `R4←R1 AND R6`. |
| `AR0X` | Rotar el registro `RR` `X` bits a la derecha. | `A504`: rota `R5` cuatro. |
| `BRXY` | Saltar a `XY` si `RR=R0`. | `B826`: si `R8=R0`, PC←`26`. |
| `C000` | Detener la ejecución. | No lee otra instrucción. |

**Cuidado:** en la tabla la forma de copiar se muestra tal como se usa en el programa (`4015`); no extrapoles campos a otras versiones de simulador sin la tabla de instrucciones que rija el examen. Un **lazo** repite un bloque mediante un salto mientras una condición lo indique. **Un byte se desborda:** `FF+01` deja `00` si solo se guarda el byte bajo; esa suma genera además un **acarreo** de 1 hacia el siguiente byte, que habrá que conservar por separado si se necesita el resultado completo. Si dieciséis registros de un byte valen `FF`, la suma matemática es `4080` decimal (`FF0` hexadecimal): no cabe en un único registro. Por ello, el requisito «guardar la suma en `A`» solo puede significar suma **módulo 256**, salvo que se destinen registros o memoria adicionales a los bits altos.

### Programa resuelto: sumar `M[B0]`–`M[BF]` y calcular su promedio entero

La solución del [quiz 02](../documento.md) pone la suma baja en `RA` y **el promedio exacto truncado** en `RF`. Para evitar que el desbordamiento corrompa el promedio, divide **cada byte** `x` como `x=16q+r`, donde `q=⌊x/16⌋` y `r=x mod 16`. Acumula por separado los dieciséis `q` y `r`. Entonces `⌊Σx/16⌋=Σq+⌊Σr/16⌋`. Cada subtotal cabe en un byte: `Σq≤240` y `Σr≤240`. Una rotación de cuatro bits seguida de AND `0F` obtiene la mitad alta del byte; AND `0F` obtiene la baja.

| Dirección | Bytes | Papel de la instrucción |
| --- | --- | --- |
| `00` | `20C0` | `R0←C0`: primera dirección posterior a `BF`. |
| `02` | `2200` | `R2←0`: suma de cocientes. |
| `04` | `2300` | `R3←0`: suma de residuos. |
| `06` | `260F` | `R6←0F`: máscara. |
| `08` | `2701` | `R7←1`: incremento. |
| `0A` | `28B0` | `R8←B0`: posición actual. |
| `0C` | `2A00` | `RA←0`: suma baja. |
| `0E` | `11B0` | `R1←M[B0]`: al repetir, cambia el operando `B0`. |
| `10` | `5AA1` | `RA←RA+R1` módulo 256. |
| `12` | `8416` | `R4←R1 AND 0F`: residuo. |
| `14` | `5334` | `R3←R3+R4`. |
| `16` | `4015` | `R5←R1`. |
| `18` | `A504` | Rotar `R5` cuatro bits a la derecha. |
| `1A` | `8556` | `R5←R5 AND 0F`: cociente. |
| `1C` | `5225` | `R2←R2+R5`. |
| `1E` | `5887` | `R8←R8+1`. |
| `20` | `B826` | Si `R8=C0`, ya se procesaron 16 posiciones; saltar a `26`. |
| `22` | `380F` | Escribir `R8` en `M[0F]`, segundo byte del `11B0` de `0E`. |
| `24` | `B00E` | Como `R0=R0`, volver siempre a `0E`. |
| `26` | `4034` | `R4←R3`. |
| `28` | `A404` | Rotar cuatro bits a la derecha. |
| `2A` | `8446` | `R4←R4 AND 0F` = `⌊Σr/16⌋`. |
| `2C` | `5F24` | `RF←R2+R4`: promedio entero. |
| `2E` | `C000` | Detener. |

**Traza de una vuelta.** Inicialmente `R8=B0`. La carga en `0E` lee `M[B0]`; luego `R8` se incrementa a `B1`. Como `B1≠C0`, `380F` pone `B1` en `M[0F]`, convirtiendo los bytes de la instrucción `11 B0` en `11 B1`; el salto vuelve a `0E` y ahora lee `M[B1]`. En la vuelta de `BF`, `R8` pasa a `C0`, por lo que salta antes de modificar otra vez la instrucción. Los datos deben estar en `B0`–`BF`, separados del programa `00`–`2F`. Para dieciséis `FF`, `RA=F0` (`4080 mod 256`) y `RF=FF` (`⌊4080/16⌋=255`). Esta solución usa **código automodificable**, apropiado para el ejercicio didáctico, no una técnica general requerida para programar sistemas modernos.

**Checklist — tema 3**

- [ ] Decodifico `20C0`, `11B0`, `3004`, un `ADD`, un `AND`, una rotación, un salto y `C000` distinguiendo registros y direcciones.
- [ ] Hago una tabla PC/IR/registros/memoria para tres instrucciones consecutivas y para un salto.
- [ ] Justifico por qué dieciséis bytes pueden desbordar `RA` y calculo suma modular y promedio por separado.
- [ ] Reproduzco la idea `x=16q+r` y explico por qué los dos acumuladores de partes sí caben.
- [ ] Trazo `B0→B1` y `BF→C0`, incluida la escritura en `M[0F]`.

## 4. De la máquina dedicada al monitor por lotes — páginas 14–17 y lectura de Patrick

En una **máquina dedicada**, preparar un trabajo, cargar datos, ejecutarlo, retirar resultados y empezar el siguiente dependía mucho del operador; los intervalos ociosos de una computadora costosa motivaron automatización. Un **lote** agrupa trabajos para procesarlos sucesivamente. Un **monitor** permanece al mando, reconoce **tarjetas de control** que separan e identifican trabajos y transfiere el control al programa apropiado. Un **JCL** es un lenguaje para describir trabajos, recursos y opciones; las tarjetas de aquellos sistemas son un antecedente. Esta explicación se refiere a operación histórica, no a que cualquier programa de la época tuviera un sistema operativo moderno.

En la lectura de **Robert L. Patrick**, el monitor **GM/NAA del IBM 704** organiza una fase de **traducción de entrada** (preparar tarjetas/datos), una de **cálculo** y una de **traducción de salida** (hacer entregables los resultados). Podía incluir ensamblado o compilación dentro de un trabajo, pero **el monitor no es el compilador**: coordina el uso de la máquina. Patrick describió la arquitectura; **Owen Mock** y **George Ryckman** dirigieron equipos asociados con su desarrollo. [Artículo histórico de Patrick](https://www.rand.org/pubs/papers/P7316.html).

Las operaciones de **entrada/salida** tienen detalles físicos distintos según el dispositivo. Un **driver** traduce peticiones generales a acciones para el dispositivo; una **llamada al sistema** permite que el programa solicite servicios de E/S al SO. Llamar al SO una **máquina virtual** significa que expone operaciones más cómodas que manipular directamente el hardware, no que siempre emule otra CPU. En varias capas se puede **traducir** un programa una vez hacia operaciones inferiores, o **interpretar** una operación superior cada vez que ocurre: en un intérprete hay trabajo de traducción/decisión durante la ejecución. Ninguno de esos verbos por sí solo determina velocidad exacta sin medir el sistema.

**Ejemplo.** Tres trabajos llegan en tarjetas: el monitor prepara el primero, usa un compilador si ese trabajo lo requiere, lo ejecuta, recoge su salida y pasa al segundo. El compilador traduce *un programa*; el monitor organiza *muchos trabajos*.

**Checklist — tema 4**

- [ ] Reconstruyo la secuencia de una máquina dedicada y la mejora concreta que aportó un monitor.
- [ ] Distingo trabajo, lote, monitor, tarjeta de control y JCL.
- [ ] Explico las tres fases GM/NAA y el aporte de Patrick, Mock y Ryckman.
- [ ] Relaciono E/S, driver y llamada al sistema sin confundirlos.
- [ ] Distingo traducción, interpretación y abstracción de SO con un ejemplo.

## 5. Traducir y transportar compiladores — páginas 18–25 y quiz 03

### 5.1 Fuente, destino, implementación y diagrama T

Un **traductor** transforma una representación en otra conservando el significado pertinente. Un **compilador** es un traductor que procesa un programa **fuente** y produce código o una representación **objetivo**; el propio compilador está escrito en un **lenguaje de implementación** y debe correr en una **máquina anfitriona**. El programa generado está destinado a una **máquina objetivo**. En un **diagrama T**, arriba se escribe `fuente → objetivo`; el pie identifica dónde puede ejecutarse el traductor ya construido o, si el dibujo representa *código fuente del traductor*, el lenguaje en que está implementado. Indica explícitamente cuál de las dos interpretaciones tiene el pie. Un **compilador cruzado** corre en una máquina y genera código para otra: por ejemplo, corre en x86-64 y emite instrucciones ARM. MIPS y ARM son familias de arquitecturas usadas como ejemplos de objetivos; generar bytes para una no permite ejecutarlos automáticamente en la otra.

**Composición.** Si `A→B` corre aquí y `B→C` también corre aquí, se puede convertir `A` en `C` pasando por `B`; hay que comprobar que la salida del primero sea precisamente la entrada que el segundo acepta. Si el segundo solo existe como *fuente* en lenguaje `D`, primero necesitas un compilador ejecutable para `D`. Ese es el punto difícil de los diagramas T: representar **dependencias reales**, no unir flechas por parecido visual.

**Ejercicio del quiz 03.** Existe un compilador C versión 7 ejecutable en Linux y el código fuente en C de la versión 10. (1) Compilas la fuente de v10 con v7 para obtener un ejecutable v10. (2) Si deseas, recompilas la misma fuente con v10; esto es un paso de **bootstrapping**, no una garantía de mejor calidad. (3) Un traductor `Fortran→C` escrito en C debe compilarse primero con el C ya disponible. (4) Un compilador `COBOL→máquina` escrito en Fortran solo puede transportarse con esa cadena si se dispone de **su fuente Fortran**: se traduce a C y luego se compila. Si solo hay un binario incompatible y no hay fuente, esos componentes no bastan. También debe coincidir la arquitectura del código máquina que genera. [Desarrollo completo de este enunciado](../documento.md).

### 5.2 Zurich Compiler Kit y Pascal-P

Si el compilador de **Pascal** estuviera atado a una computadora particular, llevar Pascal a otra exigiría reescribir partes difíciles. El enfoque **Pascal-P/Zurich Compiler Kit** hace que el compilador emita **P-code**, instrucciones para una **P-machine** abstracta basada en pila. Para llevarlo a otra plataforma, se implementa o transporta primero esa máquina P; así ya se puede ejecutar el compilador y programas en P-code, y después se puede trabajar en un generador nativo. **Niklaus Wirth** se vincula con Pascal y este enfoque. El apunte propone estudiar el intérprete de la P-machine, reescribirlo en un lenguaje disponible localmente, compilarlo, ejecutar el kit y finalmente adaptar el compilador para el destino. Un P-code puede interpretarse o traducirse; no se debe confundir *intermedio* con *binario nativo*.

**Checklist — tema 5**

- [ ] Dibujo un diagrama T y rotulo fuente, objetivo, implementación, anfitriona y destino sin mezclarlos.
- [ ] Explico qué es compilación cruzada con MIPS/ARM como destinos concretos.
- [ ] Resuelvo la secuencia C v7→v10→Fortran→C→COBOL, identificando qué archivo debe ser fuente y qué debe ser ejecutable.
- [ ] Explico *bootstrapping* y señalo qué parte de una composición T no puede ejecutarse aún por faltar compilador anfitrión.
- [ ] Reconstruyo por qué P-code/P-machine facilitan transportar Pascal y qué trabajo todavía exige cada máquina.
- [ ] Distingo máquina de pila y P-code de instrucciones nativas.

## 6. ACK, EM y portabilidad entre varios lenguajes — lectura ACK, páginas 23–25 y quiz 03

**Zurich** resuelve principalmente transportar Pascal. El **Amsterdam Compiler Kit (ACK)** persigue reutilizar una cadena para **varios lenguajes fuente y varias arquitecturas**. Cada *front end* entiende un lenguaje, como C o Pascal, y produce **EM**; cada *back end* traduce EM a la máquina correspondiente. EM es una representación intermedia para una **máquina abstracta de pila**. Esta separación retoma la idea **UNCOL**, un intermediario compartido. Con `N` lenguajes y `M` máquinas, se buscan aproximadamente `N` frentes y `M` posteriores reutilizables, además de bibliotecas, optimizadores y trabajo de integración, en lugar de crear `N×M` compiladores independientes. La cuenta explica la arquitectura; no promete que todo costo real sea solo `N+M`. [Artículo original de ACK](https://tack.sourceforge.net/olddocs/toolkit.html).

Un recorrido del artículo para `K := I+7` usa, conceptualmente, `LOL I` (apilar `I`), `LOC 7` (apilar 7), `ADI 2` (sumar enteros de dos bytes) y `STL K` (guardar en `K`). El *front end* decide que esa secuencia representa la asignación; el *back end* decide cómo implementarla en registros/instrucciones reales. Un optimizador **peephole** examina instrucciones próximas y sustituye patrones cortos por equivalentes mejores; un optimizador **global** considera regiones amplias, como flujos entre bloques o bucles. EM puede optimizarse de manera reutilizable; también se puede optimizar código específico de una máquina. ACK incluye además herramientas para ensamblar, enlazar, interpretar EM y probar componentes.

**Diferencia que suele salir en examen:** la P-machine y EM son *dos* máquinas intermedias basadas en pila, pero el kit de Zurich se presenta aquí por el transporte de Pascal y ACK por una familia extensible de lenguajes y destinos. Que ambos usen intermedio no los vuelve el mismo proyecto.

**Checklist — tema 6**

- [ ] Explico el flujo `fuente → front end → EM → back end → máquina` con una asignación sencilla.
- [ ] Distinguiría EM, P-code y UNCOL ante una pregunta de comparación.
- [ ] Justifico `N+M` frente a `N×M` indicando bibliotecas e integración que la cuenta omite.
- [ ] Identifico optimización local/peephole, global, independiente y específica del destino.
- [ ] Explico la función de intérprete de EM, ensamblador y enlazador dentro del kit.

## 7. Parientes del compilador y la cadena de ejecución — páginas 26–30 y quiz 03

Un **preprocesador** transforma texto antes del análisis principal: expande **macros**, incluye archivos o selecciona partes mediante condiciones. Un **ensamblador** traduce mnemónicos, etiquetas y operandos a un archivo objeto; puede hacer **dos pasadas**: primero calcular posiciones y registrar símbolos, y luego emitir bytes resolviendo referencias. Una **referencia adelantada** apunta a un símbolo que aún no apareció. **Backpatching** significa dejar un campo de salto pendiente y completarlo cuando se conoce su destino; puede ocurrir en generación de código y se parece en espíritu, pero no en ubicación exacta, a una **relocalización** aplicada más tarde durante el enlace. Un **desensamblador** intenta reconstruir instrucciones legibles a partir de bytes; no recupera por magia nombres, comentarios o estructura fuente.

El **linker** une objetos, resuelve símbolos de otros módulos o bibliotecas y aplica entradas de una **tabla de relocalización**, que indican dónde y cómo ajustar direcciones. En **enlazado dinámico**, referencias a bibliotecas compartidas se terminan de resolver al cargar o en ejecución. El **loader** prepara ejecutable y dependencias en memoria para correr. Un **intérprete**, en cambio, realiza directamente las operaciones de una representación en su propia ejecución. Un **debugger** pone puntos de ruptura, examina estados y permite avanzar paso a paso; un **profiler** mide dónde se consumen recursos. **Editor** sirve para escribir, **IDE** integra funciones de desarrollo y **gestor de versiones** conserva y coordina cambios; ninguno de los tres reemplaza al compilador.

**Ejemplo.** Un programa C usa `printf`. El compilador puede producir una llamada a un símbolo que no define el archivo actual. El objeto conserva una referencia y una indicación de cómo ajustar el sitio de llamada. El linker y, según el tipo de biblioteca, el cargador dinámico resuelven el destino. Eso no es backpatching de un `if` interno: el primero se refiere a vincular objetos/bibliotecas, el segundo a completar una dirección que el propio generador dejó pendiente.

**Checklist — tema 7**

- [ ] Ordeno preprocesar, compilar, ensamblar, enlazar, cargar y ejecutar y digo qué produce cada etapa.
- [ ] Explico macro, dos pasadas, símbolo, referencia adelantada, backpatching y relocalización con un salto o función externa.
- [ ] Distingo enlace estático/dinámico cuando el caso indica en qué momento se resuelve la biblioteca.
- [ ] Distingo las tareas de intérprete, desensamblador, linker, loader, debugger y profiler.
- [ ] Explico para qué sirven editor, IDE y gestor de versiones sin llamarlos fases del compilador.

## 8. Interior de un compilador y lectura de Fischer–LeBlanc — páginas 31–37, quiz 05

La entrada es texto; el **scanner** lee caracteres y devuelve **tokens**, unidades con categoría y a menudo un valor. Por ejemplo, en `suma := x+1`, `suma` y `x` son lexemas diferentes de la categoría `IDENTIFICADOR`; `1` es lexema de `ENTERO`. El **lexema** es el texto concreto; el token, la clase que el parser necesita. Una rutina como `GetToken()` avanza la posición, maneja blancos/comentarios y devuelve el próximo token. Muchas reglas eligen la coincidencia válida más larga, pero las prioridades entre patrones las define el scanner. El caso histórico de espacios ambiguos en FORTRAN advierte que *eliminar todos los espacios sin comprender las reglas* puede juntar o cambiar tokens. Un **generador de scanners** construye este componente a partir de patrones declarados.

El **parser** toma tokens y los organiza de acuerdo con una **gramática**: las **producciones** indican qué secuencias puede formar cada no terminal. En **descenso recursivo**, un procedimiento por construcción sintáctica llama a los demás y pide tokens al scanner. Puede formar un **AST** (árbol de sintaxis abstracta) que conserva operaciones y relaciones, sin cada paréntesis o separador, o ejecutar acciones sin mantener un árbol. Un árbol **decorado** añade atributos calculados, como tipos. El **analizador semántico** comprueba nombres declarados, ámbito y compatibilidad de operaciones; no es lo mismo que el parser. Una **tabla de símbolos** guarda atributos de variables, procedimientos, constantes o tipos; una **tabla de literales** registra valores constantes necesarios para emitir datos. La **IR** es una representación intermedia modificable, en memoria o en archivos temporales, que no tiene por qué ser un AST. [Capítulo 2 de Fischer y LeBlanc](../projects/Fischer-Cap2.pdf).

El **front end** se ocupa de entender el fuente y producir una representación válida; el **back end** elige instrucciones y ubicaciones del objetivo. La **optimización** cambia la representación conservando el comportamiento observable: por ejemplo, reemplazar `2+3` por `5` si el lenguaje lo permite. La **generación de código** emite ensamblador u objeto. No toda implementación sigue una cadena rígida de archivos: un **compilador de una pasada** puede emitir código durante el parsing; otros guardan AST, IR y **archivos temporales**. Un **error léxico** sería un carácter no permitido; un **sintáctico**, `x + ;`; un **semántico**, usar una variable no declarada aunque la forma sea gramatical. Un error de ejecución, como dividir por cero en un caso permitido por la sintaxis, exige analizar las reglas del lenguaje y el momento en que aparece; no lo llames automáticamente léxico.

**Flujo que debes narrar:** `caracteres → tokens → estructura sintáctica → comprobaciones semánticas → IR/acciones → optimización → instrucciones objetivo → objeto → enlace/carga → ejecución`. El enlace y la carga son pasos de la cadena de herramientas, no fases internas obligatorias de cada compilador. [Referencia de fases, LLVM](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html).

### Proyecto MICRO y pregunta del quiz 04

En el proyecto del repositorio, el scanner reconoce `read`, `write`, identificadores y puntuación; el parser procesa `READ(id_list);` y `WRITE(expr_list);`; las rutinas semánticas y de código generan ensamblador x86-64. `read(x)` prepara la dirección de la variable y llama a `scanf`; `write(E)` pasa el valor y llama a `printf`. Variables y temporales se reservan en `.bss`. Así, con entrada `4`, `read(x); write(x+1);` escribe `5`. La expresión condicional `(E1 | E2 | E3)` vale `E2` cuando `E1≠0` y `E3` cuando `E1=0`: un salto evita **ejecutar** la rama no elegida; ambas ramas producen su resultado en un mismo temporal. El proyecto genera ensamblador al recorrer la gramática, **sin AST ni IR separados**; el programa conductor usa GCC para ensamblar/enlazar y ejecutar. [Código y README de MICRO](../projects/project0/README.md).

**Checklist — tema 8**

- [ ] Dado `suma := x+1`, separo caracteres, lexemas, categorías de token y estructura de la expresión.
- [ ] Explico `GetToken()`, blancos/comentarios, coincidencia más larga, generador de scanner y la advertencia de FORTRAN.
- [ ] Distingo gramática, producción, parser recursivo, AST, árbol decorado y rutina semántica.
- [ ] Distingo tabla de símbolos, tabla de literales, IR y archivos temporales, con un dato que guardaría cada uno.
- [ ] Identifico errores léxicos, sintácticos y semánticos con ejemplos diferentes.
- [ ] Narro front end, optimización, generación de código, objeto, enlace y carga; explico qué significa una pasada.
- [ ] Trazo `read/write` y el condicional MICRO, incluidas las dos etiquetas, el temporal y la única rama ejecutada.

## 9. Hileras: construir y descomponer palabras — páginas 37–40 y quiz recordado

Un **alfabeto** `Σ` es un conjunto finito de símbolos: por ejemplo, `{E,C,I}` o `{0,1}`. Una **hilera** es una secuencia finita de ellos; el orden y las repeticiones importan. `ECCI` tiene longitud `|ECCI|=4`. La hilera vacía `ε` tiene longitud cero; **no** es el carácter impreso `ε` dentro del alfabeto, salvo que explícitamente se haya elegido ese símbolo como dato. Un **prefijo** empieza al comienzo, un **sufijo** termina al final y una **subhilera** aparece de forma contigua en alguna posición. Formalmente, `p` es prefijo de `w` si `w=px`; `s` es sufijo si `w=xs`; `u` es subhilera si `w=xuy`, para hileras auxiliares `x,y` quizá vacías.

| Longitud | Prefijo de `ECCI` | Sufijo de `ECCI` |
| ---: | --- | --- |
| 0 | `ε` | `ε` |
| 1 | `E` | `I` |
| 2 | `EC` | `CI` |
| 3 | `ECC` | `CCI` |
| 4 | `ECCI` | `ECCI` |

Así, `Pref(ECCI)={ε,E,EC,ECC,ECCI}` y `Suf(ECCI)={ε,I,CI,CCI,ECCI}`. `CC` es una **subhilera** pero no un prefijo ni un sufijo. Si piden prefijos o sufijos **propios**, se excluye la hilera entera; `ε` sigue siendo propio porque `ECCI` no es vacía. Esta fue una de las preguntas recordadas del quiz no aplicado; no conocemos las demás.

La **concatenación** `uv` agrega `v` al final de `u`: `EC·CI=ECCI`. Es **asociativa**, `(uv)z=u(vz)`, porque el orden final de símbolos es el mismo; `ε` es su **neutro**: `εw=wε=w`. No es **conmutativa** en general: `EC·I=ECI`, mientras `I·EC=IEC`. La **potencia** `wⁿ` concatena `n` copias de `w`; `w⁰=ε` y `w³=www`. El **reverso** `wᴿ` lee los símbolos en sentido inverso: `(ECCI)ᴿ=ICCE` y `(uv)ᴿ=vᴿuᴿ` porque se invierte también el orden de los bloques.

`Σ²` no es «dos símbolos elegidos»: es **el conjunto de todas las hileras de longitud dos**. Si `Σ={0,1}`, `Σ²={00,01,10,11}` y `Σ⁰={ε}`. `Σ*=Σ⁰∪Σ¹∪Σ²∪⋯` reúne todas las hileras finitas sobre `Σ`, incluida `ε`; `Σ+=Σ¹∪Σ²∪⋯` reúne las de longitud positiva. El asterisco recibe el nombre de **clausura de Kleene** por **Stephen Cole Kleene**. Aun cuando el alfabeto tenga dos símbolos, `Σ*` es infinito, pues no existe límite superior de longitud.

**Checklist — tema 9**

- [ ] Defino alfabeto, símbolo, hilera, longitud y `ε` y enumero `Σ⁰`, `Σ¹`, `Σ²`, `Σ*`, `Σ+` para `{0,1}`.
- [ ] Enumero exactamente prefijos y sufijos de `ECCI`, incluidos `ε` y la palabra completa; distingo los propios.
- [ ] Doy una subhilera que no es prefijo ni sufijo y justifico su descomposición `xuy`.
- [ ] Demuestro con una secuencia por qué concatenar es asociativo y doy un contraejemplo de conmutatividad.
- [ ] Calculo potencia y reverso de una hilera y explico la fórmula `(uv)ᴿ=vᴿuᴿ`.

## 10. Lenguajes: conjuntos de hileras y operaciones — páginas 41–44

Un **lenguaje formal** `L` sobre `Σ` es un **subconjunto de `Σ*`**. Puede ser finito, como `{0,01}`, o infinito, como las hileras binarias que acaban en `1`. No confundas tres objetos: `ε` es una hilera, `{ε}` es el lenguaje que contiene esa única hilera y `∅` es el lenguaje **sin miembros**. En particular, `{ε}` y `∅` no son iguales, aunque ninguno contenga una hilera de longitud positiva. Un **reconocedor** decide si una hilera pertenece a `L`; un **generador** produce hileras de `L` sin producir ajenas y, en el sentido matemático, debe poder llegar a cada miembro. Para un lenguaje infinito el generador no termina después de enumerarlos «todos».

**Operaciones de conjuntos.** La **unión** `L∪M` contiene las hileras de uno o ambos; la **intersección** `L∩M`, las que están en ambos; la **diferencia** `L\M`, las que están en `L` pero no en `M`. El **complemento** de `L` es `Σ*\L`: **debes declarar `Σ`**. Si `L={0}` y `Σ={0,1}`, el complemento contiene `ε,1,00,01,…`; con otro alfabeto sería otro conjunto. La unión e intersección son conmutativas, asociativas e idempotentes; `L∪∅=L` y `L∩Σ*=L`. `L\∅=L`, pero `∅\L=∅`: la diferencia **no es conmutativa** ni tiene un neutro bilateral en general. El **reverso de un lenguaje** es `Lᴿ={wᴿ:w∈L}`, no la inversión del orden en que alguien enumera elementos de un conjunto.

**Concatenación de lenguajes.** `LM={uv:u∈L,v∈M}`. Si `L={0,01}` y `M={1,ε}`, entonces `LM={01,0,011}`: `0·1=01`, `0·ε=0`, `01·1=011`, `01·ε=01`; la repetición de `01` se escribe una sola vez por tratarse de un conjunto. La concatenación es asociativa, **no conmutativa** ni **idempotente** en general: para `L={0}`, `LL={00}≠L`. Su neutro es **`{ε}`**, porque elegir la única hilera vacía no cambia a la otra; su absorbente es **`∅`**, pues no se puede elegir un miembro de un lenguaje vacío. Esto responde con precisión la expresión «elemento neutro» del quiz: **de hileras → `ε`; de lenguajes bajo concatenación → `{ε}`; de unión de lenguajes → `∅`; de intersección → `Σ*`**.

La **potencia de lenguaje** `Lⁿ` concatena `n` elecciones de `L`: `L⁰={ε}`, `L¹=L`, `L²=LL`. La **clausura** `L*=⋃ₙ₌₀∞Lⁿ` permite cero o más elecciones y **siempre** incluye `ε`; `L+=⋃ₙ₌₁∞Lⁿ` pide una o más elecciones. Aunque `L+` no incluye el caso de *cero* elecciones, **puede** contener `ε` si `ε∈L`; por ejemplo, para `L={ε,a}`, `ε∈L+`. Para `L=∅`, `L⁰={ε}`, `L*= {ε}` y `L+=∅`. Para `L={ab}`, `L*={ε,ab,abab,ababab,…}`. `Σ*` y `L*` usan la misma operación, aplicada respectivamente a símbolos individuales y miembros de un lenguaje.

**Checklist — tema 10**

- [ ] Distingo sin vacilar `ε`, `{ε}` y `∅`; explico por qué `∅*={ε}`.
- [ ] Calculo unión, intersección, diferencia y complemento en un ejemplo finito con `Σ` especificado.
- [ ] Señalo neutros de unión, intersección y concatenación y absorbente de concatenación, sin confundir diferencias izquierda/derecha.
- [ ] Enumero `LM`, `L²`, `L*` y `L+` de lenguajes pequeños, eliminando hileras repetidas.
- [ ] Explico reverso de lenguaje y doy contraejemplos de conmutatividad e idempotencia de concatenación.
- [ ] Distingo las funciones de reconocedor y generador para lenguajes finitos e infinitos.

## 11. DFA: definición, lectura, diseño y ejercicios — páginas 45–50 y hoja posterior

### 11.1 La quíntupla y la regla de aceptación

Un **autómata finito determinista** (DFA) es `M=(Q,Σ,δ,q₀,F)`. `Q` es un conjunto **finito** de estados; `Σ`, el alfabeto de entrada; `δ:Q×Σ→Q`, la **función total** de transición; `q₀∈Q`, el estado inicial; y `F⊆Q`, los estados de aceptación. «Determinista» significa que **para cada** par `(estado,símbolo)` hay **exactamente un** siguiente estado. Si el dibujo omite flechas hacia la situación de error, añade un **sumidero** de rechazo con lazos para todos los símbolos. El dibujo tiene una flecha de entrada a `q₀`, doble círculo para cada final y flechas rotuladas para `δ`; la **tabla** dice exactamente lo mismo, una fila por estado y una columna por símbolo. [Definición formal, MIT OCW](https://ocw.mit.edu/courses/6-045j-automata-computability-and-complexity-spring-2011/a8b9bb8d5d9c1f7a6b4a85056b8dcbde_MIT6_045JS11_lec03.pdf).

Para procesar una hilera `w=w₁…wₙ`, comienza en `r₀=q₀` y calcula `rᵢ₊₁=δ(rᵢ,wᵢ₊₁)` hasta consumirla **completa**. Se acepta solo si `rₙ∈F`; `L(M)` es el conjunto de todas las hileras aceptadas. La transición **extendida** sobre hileras se escribe `δ̂(q,ε)=q` y `δ̂(q,wa)=δ(δ̂(q,w),a)`. Leer `ε` significa **no leer símbolo**, por lo que `ε` se acepta exactamente si **`q₀` es final**; esto no introduce transiciones ε en el DFA. Puedes estar en un estado final a mitad del recorrido y terminar en otro no final: importa el estado **después del último símbolo**.

**Ejemplo mínimo.** Para binarias que terminan en `1`, `q0` significa «vacía o último `0`» y `q1` «último `1`»; `q0` inicial, `F={q1}`. Tabla:

| Estado | Leer `0` | Leer `1` | ¿Acepta? |
| --- | --- | --- | --- |
| `q0` | `q0` | `q1` | No |
| `q1` | `q0` | `q1` | Sí |

`δ̂(q0,101)=q1`, así que `101` acepta; `δ̂(q0,10)=q0`, así que `10` rechaza; `ε` rechaza. Para **no** terminar en `1`, las transiciones quedan iguales y `F={q0}`; ahora `ε` sí acepta, pues no termina en `1`. Esto es **complementar un DFA total**, es decir, sustituir `F` por `Q\F` sin tocar `δ`.

**Checklist — tema 11.1**

- [ ] Enuncio los cinco componentes con sus tipos (`δ:Q×Σ→Q`, `q₀∈Q`, `F⊆Q`).
- [ ] Detecto una celda faltante de tabla y la completo, si procede, con un sumidero total.
- [ ] Simulo una hilera completa, anoto cada estado y decido aceptación; hago el caso `ε`.
- [ ] Escribo las dos reglas de `δ̂`, explico que no son flechas ε y defino `L(M)`.
- [ ] Complemento el ejemplo «termina en `1`» y justifico por qué cambia `ε`.

### 11.2 Método de diseño que funciona en ejercicios difíciles

**Paso 1: fija el universo.** Escribe `Σ`, qué significa `ε` y qué se acepta. Si el enunciado habla de números, aclara si permite ceros iniciales o una hilera vacía. **Paso 2: busca la información mínima que el futuro necesita del pasado.** Para «termina en `01`» basta el sufijo relevante; para divisibilidad, basta el residuo; para paridades, dos bits de memoria. **Paso 3: convierte cada recuerdo en un estado con significado explícito.** Escribe una frase por estado antes de dibujar. **Paso 4: para cada estado y cada letra, actualiza ese recuerdo.** Construye una tabla total; no adivines flechas de un dibujo. **Paso 5: marca estados finales** según el enunciado, incluido `q₀` si debe aceptar `ε`. **Paso 6: verifica hileras cortas, positivas y negativas**, sobre todo donde se superponen patrones, hay ceros a la izquierda o se vuelve de un estado final a uno no final. Si dos condiciones deben mantenerse a la vez, usa estados que guarden el par de recuerdos y llega solo a los estados alcanzables.

**Checklist — tema 11.2**

- [ ] Antes de dibujar puedo decir qué «recuerda» cada estado y por qué eso basta para decidir cualquier continuación.
- [ ] Completo tabla para todo `Q×Σ`, marco inicial/final y pruebo `ε`.
- [ ] Busco contraejemplos cortos y superposiciones; corrijo flechas, no redefino informalmente el lenguaje.

### 11.3 Sufijos, subhileras prohibidas y extremos

Para «termina en `01`», tres recuerdos bastan: `q0` = no hay sufijo relevante, `q1` = termina en `0`, `q2` = termina en `01`. `q2` es final. Si desde `q2` llega `0`, queda un `0` nuevo y se vuelve a `q1`; si llega `1`, termina en `11` y se va a `q0`. Tabla completa:

| Estado | `0` | `1` | ¿Final? |
| --- | --- | --- | --- |
| `q0` inicial | `q1` | `q0` | No |
| `q1` | `q1` | `q2` | No |
| `q2` | `q1` | `q0` | Sí |

El texto manuscrito de la **página 48** parece decir «termina en `001`», pero **ese dibujo y esta tabla reconocen `01`**: `01` es aceptada y `001` también; para exigir `001` se necesitan recuerdos adicionales. Para «**no termina en `00`**», guarda cuántos `0` finales consecutivos hay, truncado en dos: `z0` (cero), `z1` (uno), `z2` (dos o más). Con `1` se vuelve a `z0` desde todos; con `0`, `z0→z1→z2→z2`. `z0,z1` son finales, `z2` no; `ε` acepta.

**El patrón más sutil del cuaderno es «no contiene `GAGA`».** Los estados `s0,s1,s2,s3` recuerdan el **sufijo más largo de lo ya leído que también es prefijo propio de `GAGA`**: respectivamente `ε`, `G`, `GA`, `GAG`. `bad` indica que `GAGA` apareció alguna vez y nunca puede «desaparecer» al añadir letras. `s0…s3` son finales; `bad` es sumidero de rechazo. El alfabeto es `{A,T,C,G}`:

| Estado | `A` | `T` | `C` | `G` | ¿Final? |
| --- | --- | --- | --- | --- | --- |
| `s0` (`ε`) | `s0` | `s0` | `s0` | `s1` | Sí |
| `s1` (`G`) | `s2` | `s0` | `s0` | `s1` | Sí |
| `s2` (`GA`) | `s0` | `s0` | `s0` | `s3` | Sí |
| `s3` (`GAG`) | `bad` | `s0` | `s0` | `s1` | Sí |
| `bad` | `bad` | `bad` | `bad` | `bad` | No |

**Por qué `s3` con `G` va a `s1`:** lo leído termina en `GAGG`; su sufijo `G` puede ser el principio de otra aparición de `GAGA`, aunque `GAGG` no complete todavía el patrón. **Pruebas:** `GAGA` termina en `bad` y rechaza; `GAGGAGA` también rechaza; `GAGG` termina en `s1` y acepta; `ε` acepta. Memorizar flechas sin el significado «sufijo = prefijo» impide resolver patrones superpuestos nuevos.

Para «**primero y último símbolos iguales**» sobre `{0,1}`, el estado inicial `start` no tiene primer símbolo aún. Tras el primer carácter, conserva **cuál fue** el primero y **cuál es** el último. Se alcanzan cuatro estados: `(primero 0,último 0)`, `(0,1)`, `(1,0)`, `(1,1)`; leer `a` cambia solo la segunda componente a `a`. Aceptan `(0,0)` y `(1,1)`. El enunciado no decide por sí solo el caso `ε`, que no tiene extremos: decide si `start` acepta según la convención indicada. Para «no coinciden», se cambian los estados finales entre las hileras no vacías; si se pide el **complemento formal** de un DFA total, también cambia la aceptación de `start`.

**Ejercicio de la página 50: ninguna `CC` y cada `A` inmediatamente precedida por `T`.** El dibujo del cuaderno quedó incompleto. La siguiente es una **solución elaborada para esta guía**, bajo la interpretación explícita «la letra inmediatamente anterior a cada `A` debe ser `T`». Un estado válido debe recordar si la última letra fue `T` o `C`; otro cubre el inicio o última `G/A`. `dead` registra cualquier violación:

| Estado | `A` | `T` | `C` | `G` | ¿Final? |
| --- | --- | --- | --- | --- | --- |
| `other` inicial: inicio, `G` o `A` | `dead` | `t` | `c` | `other` | Sí |
| `t`: última `T` | `other` | `t` | `c` | `other` | Sí |
| `c`: última `C` | `dead` | `t` | `dead` | `other` | Sí |
| `dead` | `dead` | `dead` | `dead` | `dead` | No |

**Pruebas:** `ε`, `T`, `TA`, `CTAG` aceptan; `A`, `GA`, `CA` rechazan por la `A`; `CC`, `TACC` rechazan por `CC`. Si «precedida por T» significara *alguna T anterior, aunque no inmediata*, el lenguaje sería otro y habría que cambiar el autómata: esa ambigüedad debe resolverse al fijar el enunciado, no esconderse en el diagrama.

**Checklist — tema 11.3**

- [ ] Construyo y pruebo DFA para terminar en `1`, terminar en `01`, no terminar en `00` y sus complementos pertinentes.
- [ ] Explico el conflicto `001`/`01` de la página 48 mediante la prueba con `01`.
- [ ] Obtengo la tabla `GAGA` desde los significados de estados y compruebo transiciones con superposición, incluida `GAGG`.
- [ ] Diseño estados para primer/último símbolo y decido explícitamente cómo tratar `ε`.
- [ ] Reproduzco o derivo la solución de `CC` y `A` tras `T`, y señalo la interpretación de «precedida».

### 11.4 Conteos, bases numéricas y producto de memorias

Si el lenguaje pide `|w|` **múltiplo de tres**, usa estados `r0,r1,r2` que representan `|w| mod 3`. **Toda** letra del alfabeto avanza `r0→r1→r2→r0`; acepta `r0`, por lo que `ε` cuenta como longitud cero divisible por tres. Para «longitud **no** múltiplo de cuatro», estados `r0,r1,r2,r3`, cualquier letra avanza en ciclo y aceptan `r1,r2,r3`; `r0` inicial rechaza. No es necesario crear un estado por cada longitud: solo por residuos que predicen el futuro.

Para números representados por dígitos, al añadir a la derecha un dígito `d` en **base `b`**, el valor nuevo es `n'=bn+d`. Si el valor anterior deja residuo `r` al dividir por `m`, el nuevo residuo es **`(br+d) mod m`**. Esto genera todas las flechas con aritmética, sin dibujar al azar. Para decimales **divisibles por 3**, `b=10`, `m=3`; como `10≡1 (mod 3)`, `r'=(r+d) mod 3`. Los dígitos se agrupan en `D0={0,3,6,9}`, `D1={1,4,7}`, `D2={2,5,8}`:

| Residuo `r` | Leer `D0` | Leer `D1` | Leer `D2` | ¿Final? |
| --- | --- | --- | --- | --- |
| `0` inicial | `0` | `1` | `2` | Sí bajo la convención `ε=0` de los apuntes |
| `1` | `1` | `2` | `0` | No |
| `2` | `2` | `0` | `1` | No |

**Ejemplo:** `12` produce `0→1→0`, por lo que acepta; `13` produce `0→1→1` y rechaza. El cuaderno adopta la **convención de ejercicio** de aceptar `ε` como representación de cero. En la notación habitual de números escritos, la hilera vacía no representa un numeral; si la consigna exigiera **al menos un dígito**, se necesitaría un estado inicial separado no aceptante o un control adicional. Los ceros iniciales tampoco alteran el residuo, pero su admisibilidad depende del enunciado.

En **base 3, no divisible por 5**, usa `b=3`, `m=5`, dígitos `{0,1,2}` y finales `{1,2,3,4}`. La tabla procede exclusivamente de `(3r+d) mod 5`:

| Residuo | `0` | `1` | `2` | ¿Final? |
| --- | --- | --- | --- | --- |
| `0` inicial | `0` | `1` | `2` | No |
| `1` | `3` | `4` | `0` | Sí |
| `2` | `1` | `2` | `3` | Sí |
| `3` | `4` | `0` | `1` | Sí |
| `4` | `2` | `3` | `4` | Sí |

**Ejemplo:** `12₃=5₁₀`: `0→1→0`, rechaza por ser divisible por cinco. `20₃=6₁₀`: `0→2→1`, acepta. Aquí `ε` rechaza; para numeral `0`, también rechaza, así que no surge conflicto de aceptación, aunque sigue siendo una cuestión de representación.

Para «**número par de `A` e impar de `B`**», las condiciones son independientes. Cada estado guarda un par `(paridadA,paridadB)`: inicialmente `(P,P)`; leer `A` cambia solo la primera componente y leer `B` solo la segunda. El único estado final es `(P,I)`. Hay **cuatro** combinaciones posibles, no una cantidad ilimitada de conteos. `B` acepta, `AB` rechaza porque hay una `A` impar, `AAB` acepta. Esto es un **producto de recuerdos**; para conjunción de dos DFAs generales, un estado puede guardar `(q₁,q₂)` y aceptar cuando ambos componentes son finales. Para disyunción, acepta cuando al menos uno lo es. No es preciso materializar estados producto inalcanzables.

**Checklist — tema 11.4**

- [ ] Construyo ciclos de longitud módulo 3 y no múltiplo de 4; decido `ε` a partir de residuo cero.
- [ ] Deduzco `n'=bn+d` y la transición `(br+d) mod m` para cualquier base y divisor pequeños.
- [ ] Completo tablas decimal módulo 3 y ternaria módulo 5 sin copiar flechas, y pruebo `12` y `12₃`.
- [ ] Declaro la convención sobre `ε`, cero y ceros iniciales en ejercicios numéricos.
- [ ] Dibujo los cuatro estados de paridad `(A,B)` y combino condiciones con producto, conjunción o disyunción.

## 12. Pinker, capítulo 1: *An Instinct to Acquire an Art*

**Pregunta rectora:** ¿por qué una persona llega a dominar una lengua sin que alguien le enseñe explícitamente todas sus reglas? **Steven Pinker** defiende que la capacidad de adquirir lenguaje es parte de la organización biológica humana, moldeada evolutivamente. «**Instinto**» no significa que nazcamos sabiendo español, ni que el entorno no importe: significa que existen capacidades de aprendizaje especializadas y que, al crecer en una comunidad lingüística, el niño construye una gramática a partir de la experiencia. «**Órgano mental**» es una analogía para una función cognitiva, no un órgano anatómico aislado. Pinker defiende una explicación de **adaptación por selección natural**; el origen exacto y los mecanismos de adquisición siguen siendo cuestiones de investigación, así que en examen conviene decir **«Pinker propone»** cuando se describe su tesis evolutiva. [Ficha del libro, autor](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

La **universalidad gramatical** es la observación de que las comunidades humanas conocidas poseen sistemas lingüísticos estructurados. No hay base lingüística para llamar «primitiva» a una lengua por falta de escritura, tecnología o prestigio social. La **productividad** consiste en producir y entender expresiones nuevas con recursos y reglas finitos; saber hablar no es repetir todas las frases memorizadas. El habla o las señas naturales surgen en la comunidad, mientras la **escritura** requiere una invención cultural y enseñanza particular. Estas son afirmaciones sobre capacidad lingüística humana, no sobre que todas las lenguas tengan idéntica gramática.

La **gramática mental** es el conocimiento implícito que permite hablar y comprender; puede ser diferente de las normas de un manual escolar. **Noam Chomsky** colocó en el centro las gramáticas **generativas**, reglas capaces de describir estructuras y una cantidad no acotada de expresiones. La **gramática universal (GU)**, en la tradición que Pinker presenta, es la hipótesis de predisposiciones o restricciones compartidas para adquirir gramáticas. **No es un idioma universal ni un diccionario genético.** El argumento de que ejemplos finitos llevan a reglas abstractas motiva estudiar esas restricciones, pero la composición exacta de la GU y cuánto aportan aprendizaje estadístico, predisposición e interacción es debatido. Evita afirmar «se ha probado un esquema genético de reglas concretas» como si el capítulo lo demostrara por completo.

Pinker critica el **SSSM** (*Standard Social Science Model*) cuando se interpreta como una **tabla rasa** que se moldea exclusivamente por cultura y experiencia. Su argumento: aprender a partir de un entorno presupone alguna organización del aprendiz. Rechazar una mente completamente vacía **no equivale** a negar la importancia de educación, exposición y comunidad. **Ejemplo conceptual:** si dos personas oyen una secuencia de palabras, necesitan capacidades para identificar regularidades; el contenido de la lengua particular que aprenderán depende de lo que oigan y de las interacciones disponibles.

**Checklist — lectura Pinker 1**

- [ ] Explico en dos pasos predisposición biológica y exposición necesaria, sin decir que un recién nacido conoce ya una lengua.
- [ ] Distingo hipótesis evolutiva de Pinker, «órgano mental» como analogía, y diferencia entre habla/señas y escritura.
- [ ] Justifico universalidad, complejidad y productividad sin equiparar «sin escritura» con «sin gramática».
- [ ] Diferencio gramática mental, norma escolar, gramática generativa y GU.
- [ ] Formulo la crítica al SSSM reconociendo que la cultura y la experiencia siguen importando.

## 13. Pinker, capítulo 2: *Chatterboxes*

### 13.1 Lenguas de contacto, señas, reglas y aprendizaje

Un **pidgin** suele comenzar como forma de contacto entre grupos que no comparten lengua; normalmente no empieza como lengua materna de una comunidad y puede presentar variación o menor desarrollo de ciertos recursos. Llamarlo «**sin gramática**» es demasiado fuerte: los hablantes crean convenciones. Un **criollo** es una lengua natural comunitaria desarrollada en un contexto de contacto, a menudo vinculada a transmisión a nuevos hablantes nativos. Pinker destaca el papel de **niños** en sistematizar patrones, pero no todos los criollos tienen una misma historia lineal `pidgin→niños→criollo`. **Derek Bickerton** se asocia con hipótesis de criollización discutidas en esta literatura. [Lectura desarrollada](../conceptos-lecturas.md#pidgin-criollo-y-papel-de-los-niños).

La **Lengua de Señas Nicaragüense** surgió en una comunidad de niños sordos que comenzaron a compartir sistemas de señas. El libro utiliza **LSN** e **ISN** para distinguir etapas o cohortes tempranas de ese desarrollo; no son dos sistemas sin conexión, ni fue simplemente «una jerga sin reglas» reemplazada de golpe. **Ann Senghas y Marie Coppola** estudiaron cómo generaciones posteriores sistematizaron recursos espaciales sobre una base comunicativa ya existente. La lección es que una comunidad de usuarios puede desarrollar convenciones y estructura a través de cohortes; las lenguas de señas son **lenguas naturales**, no códigos gestuales palabra por palabra de la lengua oral mayoritaria. [Investigación de Senghas y Coppola](https://siegler.tc.columbia.edu/wp-content/uploads/2020/08/Children_Creating_Language_How_Nicaraguan_Sign_Lan.pdf).

**Simon** era un niño sordo que aprendió ASL (lengua de señas estadounidense) de padres que usaban varios morfemas de forma inconsistente. **Jenny Singleton y Elissa Newport** observaron que el niño produjo varios patrones con mayor regularidad. Es evidencia de **regularización de entrada variable**, no de una «gramática perfecta» en todos los aspectos, ni de aprendizaje **sin** una fuente de señas. Un **morfema** es una unidad de forma y significado o función gramatical, como un marcador de pluralidad o una modificación en señas. [Estudio de Singleton y Newport](https://pubmed.ncbi.nlm.nih.gov/15342259/).

**BEV** (*Black English Vernacular*), llamado con frecuencia **AAVE**, es una variedad del inglés afroamericano. **William Labov** mostró que variedades socialmente estigmatizadas tienen **reglas sistemáticas**: por ejemplo, el uso de *be* habitual expresa un hábito y no es simplemente «omitir/poner palabras al azar». Una norma social de prestigio no es la medida de si una variedad posee gramática. BEV/AAVE **no es lo mismo que pidgin ni inglés estándar con errores**.

La **pobreza del estímulo** pregunta cómo un niño llega a ciertas generalizaciones estructurales cuando el material que recibe es finito, variable y no viene acompañado por una lista completa de reglas y contraejemplos. En una pregunta de inglés con varias formas de *is*, una regla que atiende a la **estructura** de la oración funciona donde la regla superficial «mueve el primer *is* visible» fallaría. Este argumento motiva hipótesis sobre la capacidad de aprender, pero **no especifica por sí solo** una GU concreta. **Motherese** es el habla dirigida a niños que modifica entonación o complejidad en algunos contextos; Pinker sostiene que esa forma especial de hablar **no es condición universal estricta**. Eso no significa que un niño pueda desarrollar una lengua completa sin **exposición e interacción**.

**Checklist — lectura Pinker 2A**

- [ ] Diferencio pidgin y criollo con trayectoria típica y excepción a la idea de «pidgin sin reglas».
- [ ] Relaciono Bickerton con hipótesis de criollización sin convertirlas en ley universal.
- [ ] Explico LSN/ISN como desarrollo entre cohortes y el aporte de Senghas y Coppola.
- [ ] Explico Simon, ASL, morfemas y el hallazgo de Singleton y Newport sin «gramática perfecta».
- [ ] Doy un ejemplo de regla de BEV/AAVE y el argumento de Labov contra el prejuicio lingüístico.
- [ ] Explico pobreza del estímulo con la diferencia entre secuencia superficial y estructura, y el alcance limitado de la conclusión.
- [ ] Distingo *motherese* de exposición lingüística necesaria.

### 13.2 Disociaciones: lenguaje, cerebro y genética

Una **disociación** muestra que dos capacidades no varían siempre juntas. Una **doble disociación** compara perfiles opuestos: por ejemplo, alguien con dificultades especialmente lingüísticas junto a otras habilidades relativamente conservadas, frente a otro perfil con ciertas habilidades verbales relativamente fuertes y dificultades en otros dominios. Eso respalda **especialización parcial**; no prueba que el lenguaje esté por completo aislado de cognición, movimiento o entorno.

En la **afasia de Broca**, una lesión adquirida puede producir habla lenta, poco fluida y dificultades gramaticales; la comprensión suele estar relativamente mejor preservada en algunos casos, **pero también puede afectarse**, especialmente con construcciones complejas. No equivale a «inteligencia lógica perfectamente intacta». **Myrna Gopnik** estudió dificultades heredables de habla y lenguaje en la **familia KE** —no una «familia K» genérica—, incluidas tareas morfológicas como formas gramaticales. Investigaciones posteriores vincularon el caso con **FOXP2** y también identificaron dificultades motoras del habla. **FOXP2 no es un único «gen de la gramática»**, y este caso no define todos los trastornos específicos/del desarrollo del lenguaje (**SLI/DLD**). [Estudio genético inicial](https://www.nature.com/articles/35097076).

En el **síndrome de Williams**, algunas capacidades verbales pueden ser **relativamente fuertes** frente a otras dificultades cognitivas, especialmente visoespaciales, con variación importante entre personas. **Ursula Bellugi** estudió esos perfiles. No significa que todos tengan «retraso severo» con «sintaxis perfecta». La causa genética generalmente es una deleción que abarca varios genes de **7q11.23, cromosoma 7**; una referencia antigua al cromosoma 11 en el libro quedó superada. [MedlinePlus Genetics](https://medlineplus.gov/genetics/condition/williams-syndrome/).

**Cómo responder sin perder el punto.** Presenta cada caso con la comparación que pretende ilustrar y una frase de límite: «Este patrón favorece la idea de componentes lingüísticos especializados, aunque el perfil no es puro ni demuestra independencia absoluta». Eso es más fuerte como explicación científica que afirmar resultados perfectos o exclusivos.

**Checklist — lectura Pinker 2B**

- [ ] Defino disociación/doble disociación y qué inferencia admite, sin declarar independencia total.
- [ ] Describo afasia de Broca sin reducirla a dificultad muscular ni afirmar comprensión siempre intacta.
- [ ] Distingo familia KE, Gopnik, morfología, FOXP2 y SLI/DLD, evitando el mito del «gen de la gramática».
- [ ] Describo Williams y Bellugi con «fortaleza relativa», variación individual y ubicación genética correcta 7q11.23.

## 14. Preguntas de quices y figuras: comprobar relaciones, no memorizar una lista aislada

Los **quices 01–05** se identificaron a partir de las imágenes; el último quiz **no se aplicó** y solo se recuerdan las preguntas sobre propiedades de DFA, neutros, prefijos y sufijos de `ECCI`. No hay base para inventar más preguntas. El [archivo de preguntas y respuestas](../documento.md) conserva los enunciados conocidos. La mayoría ya se resolvió en las secciones anteriores; estas conexiones completan el repaso.

**Quiz 01 — *amathia*.** En el uso que hizo la pregunta, *amathia* es ignorar una limitación propia mientras se cree falsamente que se sabe. Aplicación académica: antes de marcar «sé diseñar un DFA», prueba uno con una hilera que deba aceptar, una que deba rechazar y `ε`; si falla, identifica qué recuerdo faltaba en el estado. El mismo quiz preguntó McCarthy, *First Draft*, Wilkes, FORTRAN, *fetch*, LISP, Hopper, unidad alambrada y productividad/eficiencia, tratados en §§1–2.

**Quiz 02.** Preguntó Chomsky y GU (§12), Speedcoding (§1.2) y el programa de dieciséis bytes VOLE (§3). La trampa principal del programa es pretender guardar **toda** una suma de hasta `4080` en un registro de ocho bits. El resultado `A` se entiende módulo 256, mientras el promedio puede calcularse exactamente con subtotales.

**Quiz 03.** Pidió enlazado dinámico, relocalización y backpatching (§7); Zurich frente a ACK (§§5–6); y una secuencia de diagramas T (§5). Antes de trazar flechas, anota al lado de **cada herramienta** si es código fuente o ejecutable y dónde corre; con eso se ve qué paso es legal.

**Quiz 04.** Pidió pidgin, criollo, afasia de Broca, BEV y LSN (§13), y la implementación de E/S y condicional en MICRO (§8). Conviene poder pasar de la descripción abstracta «`read` lee» a la cadena scanner→parser→rutina semántica→generación de llamada a `scanf`.

**Quiz 05.** Solicitó un diagrama secuencial de fases (§8). Una respuesta sólida muestra análisis léxico, sintáctico y semántico, IR cuando el diseño la usa, optimización y generación de código; después distingue ensamblado, enlace y carga. Tabla de símbolos y diagnósticos pueden intervenir en varias fases.

**Quiz no aplicado.** Propiedades DFA (§11), `ε` como neutro de hileras y `{ε}` como neutro de lenguajes (§§9–10), y prefijos/sufijos de `ECCI` (§9). Las otras preguntas **no están disponibles**.

### Personas y aporte específico

| Figura | Relación que debes explicar |
| --- | --- |
| Mauchly y Eckert | ENIAC y participación en EDVAC; diferencia entre conexión física y programa almacenado. |
| Von Neumann | Informe *First Draft* sobre EDVAC, sin atribuirle en exclusiva todo el diseño. |
| Wilkes | EDSAC y microprogramación. |
| Roy Nutt | SAP, ejemplo histórico de ensamblador simbólico para IBM 704 en los apuntes. |
| Backus | Speedcoding, dirección del equipo FORTRAN y notación sintáctica BNF. |
| Hopper | A-0 y FLOW-MATIC, antecedente de COBOL. |
| McCarthy | LISP e investigación temprana en IA. |
| Naur | ALGOL y BNF. |
| Wirth | Pascal y transporte mediante P-code/P-machine. |
| Kleene | Operación de clausura `*` en lenguajes formales. |
| Patrick, Mock y Ryckman | Arquitectura narrada y equipos del monitor GM/NAA por lotes. |
| Fischer y LeBlanc | Capítulo didáctico sobre construir un compilador pequeño. |
| Tanenbaum, van Staveren, Keizer y Stevenson | Artículo de ACK y uso de EM para portabilidad. |
| Pinker y Chomsky | Tesis de capacidad lingüística especializada y discusión de GU, respectivamente. |
| Labov y Bickerton | Estudio de reglas en variedades estigmatizadas e hipótesis sobre criollos, respectivamente. |
| Senghas y Coppola | Cambios gramaticales entre cohortes de señantes nicaragüenses. |
| Singleton y Newport | Estudio de regularización lingüística en Simon. |
| Gopnik y Bellugi | Familia KE y perfiles lingüísticos del síndrome de Williams, respectivamente. |

**Un detalle de transporte de los apuntes:** el compilador inicial de Pascal se vincula históricamente a su entorno de desarrollo, entre ellos **CDC 6600** en el relato del curso. La motivación del kit es no exigir esa misma máquina en todo destino. En un diagrama T, una arquitectura o computadora concreta es **plataforma**, no un nombre alternativo del lenguaje Pascal.

**Checklist — tema 14**

- [ ] Contesto cada pregunta real de los quices 01–05 sin mezclar autor, herramienta y efecto.
- [ ] Explico *amathia* con una conducta verificable de estudio y el límite de los recuerdos del quiz no aplicado.
- [ ] Identifico a cada persona de la tabla por su contribución concreta, incluidas las colaboraciones colectivas.
- [ ] Distingo CDC 6600 como máquina de destino/entorno histórico de Pascal como lenguaje.

## 15. Prueba final de dominio: seis problemas con respuesta razonada

**A.** `Σ={0,1}`, `L={ε,01}`, `M={1}`. Calcula `LM`, `L²`, decide si `ε∈L+` y compara `∅*` con `Σ*`. **Respuesta:** `LM={1,011}`; `L²={ε,01,0101}`; `ε∈L+` porque ya está en `L`; `∅*={ε}`, mientras `Σ*` contiene todas las hileras binarias. Justificación: se concatenan **hileras elegidas**, y `ε` no añade caracteres.

**B.** ¿Acepta el DFA de `GAGA` `GAGGAGA`? **Respuesta:** no: `s0 --G→ s1 --A→ s2 --G→ s3 --G→ s1 --A→ s2 --G→ s3 --A→ bad`. La cuarta letra no lo invalida; inicia un nuevo posible `GAGA` que se completa al final.

**C.** En base 3, ¿`101₂` y `101₃` son la misma cantidad? ¿Aceptaría `101₃` el DFA «no divisible por cinco»? **Respuesta:** no son la misma cantidad: `101₂=5`, `101₃=10`; el segundo deja residuo 0 módulo 5 y **rechaza**. Traza `r0 --1→ r1 --0→ r3 --1→ r0`. La base determina el valor y las transiciones.

**D.** Si `M[B0]=FF` en VOLE, ¿qué hace `11B0` y qué sucede si `RA=01` antes de sumarlo? **Respuesta:** `R1←FF`; tras `5AA1`, `RA←(01+FF) mod 256=00`. La suma matemática `256` requiere nueve bits para conservarse completa.

**E.** Un compilador `COBOL→ARM` está escrito en Fortran y solo tienes su ejecutable para una máquina incompatible, sin fuente. ¿Puedes obtener un ejecutable local usando únicamente un traductor Fortran→C? **Respuesta:** no. El traductor opera sobre **fuente Fortran**, no reconstruye automáticamente la fuente de un binario incompatible. Además, emitir ARM no decide en qué plataforma corre el propio compilador.

**F.** `read(x); write((0 | x+1 | 7));` en MICRO con entrada `4`: ¿qué imprime y qué rama se ejecuta? **Respuesta:** imprime `7`; la condición `0` elige la tercera expresión y la rama `x+1` no se **evalúa durante la ejecución**, aunque su código haya sido generado al compilar.

**Checklist — cierre**

- [ ] Resuelvo A sin confundir objeto hilera y objeto conjunto.
- [ ] Resuelvo B justificando qué recuerda cada estado; no memorizo solo una ruta.
- [ ] Resuelvo C con `br+d` y distingo las bases.
- [ ] Resuelvo D traza y desbordamiento, sin declarar exacta una suma de 8 bits.
- [ ] Resuelvo E comprobando disponibilidad de fuente y plataforma de ejecución.
- [ ] Resuelvo F distinguiendo compilación de ejecución y valor de la condición.

## Fuentes del temario y alcance de la verificación

- [Apuntes 1–10](semana-1-clases-1-y-2.md), [11–19](paginas-11-19-continuacion.md), [20–28](paginas-20-28-continuacion.md), [29–38](paginas-29-38-continuacion.md), [39–43](paginas-39-43-continuacion.md), [44–50 y hoja posterior](paginas-44-50-continuacion.md). Estas transcripciones indican cuando las fotografías tienen cifras o flechas dudosas.
- [Lecturas desarrolladas y referencias específicas](../conceptos-lecturas.md), [preguntas de quices y respuestas](../documento.md), [Fischer–LeBlanc, capítulo 2](../projects/Fischer-Cap2.pdf), [Patrick](../readings/0101%20-%20Patrick.pdf), [ACK](../readings/ACK.pdf), [código MICRO](../projects/project0/README.md).
- Para la historia y nomenclatura, [Computer History Museum](https://www.computerhistory.org/) e [IBM: FORTRAN](https://www.ibm.com/history/fortran); para la definición de DFA, [MIT OCW](https://ocw.mit.edu/courses/6-045j-automata-computability-and-complexity-spring-2011/pages/lecture-notes/); para arquitectura ACK, el [artículo original](https://tack.sourceforge.net/olddocs/toolkit.html); para el monitor, [Patrick/RAND](https://www.rand.org/pubs/papers/P7316.html).
- Las afirmaciones de Pinker se distinguen de correcciones empíricas posteriores: [Senghas–Coppola](https://siegler.tc.columbia.edu/wp-content/uploads/2020/08/Children_Creating_Language_How_Nicaraguan_Sign_Lan.pdf), [Singleton–Newport](https://pubmed.ncbi.nlm.nih.gov/15342259/), [familia KE/FOXP2](https://www.nature.com/articles/35097076/) y [síndrome de Williams, MedlinePlus](https://medlineplus.gov/genetics/condition/williams-syndrome/).

**Límite honesto:** no se recuperaron las preguntas que nadie recuerda del quiz no aplicado; el texto `001`/dibujo `01` de la página 48 discrepan; el dibujo `CC`/`A` de la página 50 no daba una tabla terminada. El DFA de cuatro estados para esta última condición es una solución nueva y revisable con los ejemplos indicados.
