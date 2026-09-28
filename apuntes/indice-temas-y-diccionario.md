# Compiladores: temas y diccionario de conceptos

**Alcance comprobado:** páginas manuscritas 1–50 y una hoja posterior sin número visible; quices 01–05 y las dos preguntas recordadas del quiz no aplicado; lecturas de Pinker, capítulos 1–2, Fischer y LeBlanc, capítulo 2, Robert L. Patrick y el artículo sobre ACK. Se incluyen el funcionamiento y los ejercicios de **ensamblador VOLE**, pero no la lectura separada de VOLE. Se excluyen los **NDAs** y el capítulo 3 de Pinker, según las indicaciones del curso. Esta lista describe el material reunido, no afirma que se hayan recuperado preguntas del quiz que nunca se aplicó.

## Lista de temas abarcados

1. **Historia de la computación y los lenguajes:** ENIAC, EDVAC, EDSAC, IBM 701/704, programa almacenado, microprogramación; Mauchly, Eckert, von Neumann, Wilkes, Backus, Hopper, McCarthy, Naur y Wirth.
2. **Lenguajes y estilos:** código máquina, ensamblador, lenguajes de alto nivel, FORTRAN, LISP, COBOL, ALGOL, Pascal; productividad frente a eficiencia.
3. **Arquitectura y ejecución:** CPU, unidad de control alambrada y microprogramada, ciclo de búsqueda–decodificación–ejecución, registros, memoria, instrucciones, RISC/CISC y máquinas de cero a tres direcciones.
4. **Máquina VOLE y problemas de ensamblador:** memoria y registros, PC/IR, instrucción de dos bytes, codificación hexadecimal, cargas, almacenamiento, aritmética, operaciones bit a bit, rotación, saltos, parada, lazo, acarreo y promedio de dieciséis bytes.
5. **Operación histórica de computadoras:** máquina dedicada, lotes, monitor GM/NAA del IBM 704, tarjetas de control, E/S, drivers, llamadas al sistema y sistema operativo como máquina virtual.
6. **Traducción y portabilidad:** compilador, ensamblador, intérprete, fuente/objeto, máquina anfitriona/destino, compilación cruzada, diagramas T, arranque de compiladores, Pascal-P y Zurich Compiler Kit.
7. **ACK y representación intermedia:** Amsterdam Compiler Kit, EM, front ends, back ends, máquina de pila, portabilidad y optimización local/global.
8. **Herramientas de la cadena de desarrollo:** preprocesador, macro, desensamblador, ensamblador de dos pasadas, enlazador, enlazado dinámico, relocalización, backpatching, cargador, depurador, profiler, editor, IDE y versiones.
9. **Fases del compilador:** análisis léxico, sintáctico y semántico; tokens, lexemas, parser de descenso recursivo, tabla de símbolos y literales, AST/IR, optimización, generación de código y diagnóstico de errores.
10. **Proyecto MICRO:** `read`, `write`, listas de expresiones, generación de ensamblador x86-64 y expresión condicional `(E1 | E2 | E3)` con evaluación de una sola rama.
11. **Hileras y alfabetos:** alfabeto, longitud, hilera vacía, prefijos, sufijos, subhileras, concatenación, potencias, reverso, `Σⁿ`, `Σ*` y `Σ+`.
12. **Lenguajes formales y operaciones:** subconjuntos de `Σ*`, vacío frente a `{ε}`, unión, intersección, diferencia, complemento, reverso, concatenación, potencias, `L*` y `L+`.
13. **DFA y técnicas de construcción:** quíntupla, transición total y extendida, recorrido y aceptación, tabla/diagrama, complemento, estado sumidero, seguimiento de sufijos, patrones prohibidos, primeros/últimos símbolos, residuos, longitud modular y paridades combinadas.
14. **Lenguaje humano en Pinker:** capacidad lingüística, gramática mental/universal, productividad, SSSM, pidgin y criollo, LSN/ISN, Simon, BEV/AAVE, pobreza del estímulo, *motherese*, doble disociación, afasia, familia KE/FOXP2 y síndrome de Williams.
15. **Conceptos transversales de quices:** *amathia*, Speedcoding, contrastes entre Zurich y ACK, composición de traductores con diagramas T, `ε` como neutro y prefijos/sufijos de `ECCI`.

## Diccionario

Las definiciones son de estudio: una misma palabra puede tener un sentido más preciso según la arquitectura o el lenguaje. `w` representa una hilera, `L` un lenguaje y `Σ` un alfabeto finito.

### A. Historia, personas y lenguajes

| Concepto | Definición y relación con el curso |
| --- | --- |
| ENIAC | Computadora electrónica temprana construida por el equipo de Mauchly y Eckert; su programación original no usaba la organización moderna de programa almacenado. |
| John Mauchly y J. Presper Eckert | Dirigieron el proyecto ENIAC y participaron en la concepción de EDVAC. |
| EDVAC | Proyecto de computadora que puso en el centro el almacenamiento de instrucciones y datos en memoria. |
| John von Neumann | Autor del *First Draft of a Report on the EDVAC*, exposición influyente de la organización de programa almacenado; no fue el único artífice del diseño. |
| *First Draft* | Informe de 1945 sobre EDVAC, referencia histórica para entender memoria, instrucciones y unidad de control. |
| Programa almacenado | Organización en que las instrucciones se representan en memoria y la CPU las recupera durante la ejecución. |
| EDSAC | Computadora de Cambridge dirigida por Maurice Wilkes que ejecutó programas almacenados en 1949. |
| Maurice Wilkes | Director de EDSAC y proponente de la microprogramación para implementar el control del procesador. |
| IBM 701 | Primera computadora electrónica científica de IBM, usada en el entorno en que Backus desarrolló Speedcoding. |
| IBM 704 | Computadora de IBM vinculada al FORTRAN inicial y al monitor por lotes estudiado por Patrick. |
| John Backus | Dirigió el equipo de FORTRAN y participó en Speedcoding; también se asocia con la notación BNF. |
| Speedcoding | Sistema interpretativo del IBM 701 para facilitar cálculos numéricos a costa de más tiempo y memoria; no era FORTRAN. |
| FORTRAN | Lenguaje de alto nivel orientado originalmente al cálculo científico, desarrollado por el equipo de Backus; su nombre deriva de *Formula Translation*. |
| Grace Hopper | Pionera de A-0 y FLOW-MATIC, influyentes en la historia de compiladores y COBOL; COBOL fue un esfuerzo colectivo. |
| A-0 y FLOW-MATIC | Sistemas vinculados a Hopper: el primero a traducción/programación temprana y el segundo a lenguajes de orientación comercial. |
| COBOL | Lenguaje de alto nivel para procesamiento de datos comerciales y administrativos. |
| John McCarthy | Impulsó la investigación en inteligencia artificial y creó LISP. |
| LISP | Lenguaje para procesamiento simbólico y listas, históricamente asociado con la investigación de IA. |
| Recolección de basura | Recuperación automática de memoria que ya no es alcanzable por el programa, asociada a implementaciones tempranas de LISP. |
| Peter Naur | Participó en ALGOL y en la formulación de su sintaxis; la N de BNF se interpreta como *Naur*. |
| ALGOL | Familia de lenguajes algorítmicos influyente en estructura de bloques y descripción formal de sintaxis. |
| BNF | Notación de Backus–Naur para escribir producciones gramaticales de manera compacta. |
| Niklaus Wirth | Diseñador de Pascal y figura central en su implementación y difusión. |
| Pascal | Lenguaje diseñado por Wirth, usado en el curso para estudiar compiladores transportables y P-code. |
| Stephen Cole Kleene | Matemático cuyo nombre lleva la clausura `*`, operación que permite repetir cero o más veces. |
| Lenguaje máquina | Secuencia de instrucciones codificadas según una arquitectura concreta y ejecutables por su CPU. |
| Lenguaje ensamblador | Notación simbólica de bajo nivel para instrucciones y direcciones de una arquitectura. |
| Lenguaje de alto nivel | Notación más alejada de los detalles de la máquina que expresa algoritmos mediante abstracciones del lenguaje. |
| Productividad del programador | Cantidad de software útil que se puede escribir y mantener con un esfuerzo dado. |
| Eficiencia de ejecución | Tiempo, memoria u otros recursos consumidos por un programa cuando corre. |

### B. Máquina, sistemas y VOLE

| Concepto | Definición y relación con el curso |
| --- | --- |
| CPU | Procesador que recupera, decodifica y ejecuta instrucciones con registros, unidad de control y operaciones de datos. |
| Unidad de control | Parte de la CPU que coordina las señales y pasos necesarios para ejecutar instrucciones. |
| Control alambrado | Control implementado mediante circuitos lógicos fijos. |
| Control microprogramado | Control que implementa instrucciones mediante secuencias de microinstrucciones internas. |
| Microinstrucción | Paso de control interno usado por una unidad microprogramada; no es una instrucción ordinaria del programa fuente. |
| Ciclo de instrucción | Secuencia de búsqueda (*fetch*), decodificación y ejecución, con actualización del contador de programa según corresponda. |
| PC | Contador de programa: registra la dirección de la próxima instrucción que se debe buscar. |
| IR | Registro que contiene la instrucción corriente durante su decodificación o ejecución. |
| Registro | Almacenamiento pequeño y rápido dentro del procesador para datos, direcciones o estado. |
| RISC y CISC | Dos enfoques de diseño del conjunto de instrucciones: uno favorece instrucciones simples y regulares; el otro admite instrucciones relativamente complejas. |
| Máquina multinivel | Forma de entender hardware, microarquitectura, lenguaje máquina, sistema operativo y lenguajes de nivel superior como capas de abstracción. |
| Máquina de pila / cero direcciones | Arquitectura en que los operandos de una operación suelen tomarse de la pila, por lo que la instrucción aritmética no tiene que nombrarlos. |
| Máquina de una, dos o tres direcciones | Clasificación por el número de operandos o destinos explícitos de las instrucciones; influye en la generación de código. |
| VOLE | Máquina didáctica con 16 registros de un byte, memoria de 256 bytes y palabras de instrucción de dos bytes. |
| Byte, nibble y hexadecimal | Un byte contiene ocho bits; un dígito hexadecimal representa cuatro bits y dos dígitos expresan un byte VOLE. |
| Código de operación (*opcode*) | Campo de una instrucción que determina la operación; los demás campos identifican registros, direcciones o datos. |
| Carga y almacenamiento | Operaciones que llevan un valor a un registro o lo escriben en memoria, respectivamente. |
| Dirección frente a contenido | `B0` puede ser la dirección de una celda mientras `M[B0]` es el byte almacenado allí; confundirlos cambia el programa. |
| Salto condicional | Instrucción que cambia el PC solo cuando se cumple una condición. |
| Lazo | Repetición controlada por una condición o contador y un salto hacia instrucciones anteriores. |
| Suma modular y acarreo | En un registro de ocho bits la suma conserva solo el resultado módulo 256; el valor total puede necesitar más bits o un acarreo separado. |
| Rotación y máscara | La rotación reubica bits y una operación AND con una máscara conserva únicamente ciertas posiciones. |
| Cociente y residuo por 16 | Para un byte `x`, se cumple `x=16q+r`, `q=⌊x/16⌋` y `r=x mod 16`; la partición sirve para promediar 16 bytes sin perder información por desbordamiento. |
| Código automodificable | Programa que escribe en bytes de sus propias instrucciones, como el ejercicio VOLE que cambia la dirección de una carga. |
| Máquina dedicada | Entorno temprano en que una tarea ocupaba el equipo y la transición entre trabajos exigía intervención manual. |
| Procesamiento por lotes | Ejecución sucesiva de trabajos reunidos previamente, con menor intervención entre uno y otro. |
| Monitor GM/NAA | Sistema supervisor del IBM 704 que coordinó trabajos por lotes y etapas de entrada, cálculo y salida. |
| Robert L. Patrick, Owen Mock y George Ryckman | Patrick explicó la arquitectura del monitor; Mock y Ryckman dirigieron equipos que participaron en su implementación. |
| Tarjeta de control / JCL | Medio o lenguaje que identifica trabajos y comunica opciones de ejecución al monitor o sistema por lotes. |
| Driver de dispositivo | Software que presenta al sistema operaciones para controlar una clase de dispositivo de E/S. |
| Llamada al sistema | Petición de un programa a los servicios del sistema operativo, por ejemplo para E/S. |
| Máquina virtual del sistema operativo | Abstracción que ofrece servicios por encima de los detalles directos del hardware. |

### C. Traductores, portabilidad y herramientas

| Concepto | Definición y relación con el curso |
| --- | --- |
| Traductor | Programa que transforma una representación de entrada en otra conservando el significado relevante. |
| Compilador | Traductor de un lenguaje fuente a un lenguaje objetivo, que puede emitir IR, ensamblador o código de máquina según el diseño. |
| Intérprete | Sistema que ejecuta o simula las operaciones de un programa sin requerir que todo se traduzca antes a un ejecutable nativo. |
| Ensamblador | Traductor de instrucciones simbólicas a código máquina u objeto. |
| Desensamblador | Herramienta que convierte bytes de código máquina a una representación ensamblador aproximada. |
| Lenguaje fuente, objetivo e implementación | Respectivamente, lenguaje de entrada, lenguaje de salida y lenguaje en que está escrito el traductor. |
| Máquina anfitriona y destino | Plataforma en que corre el compilador y plataforma para la cual produce código; pueden diferir. |
| Diagrama T | Dibujo que rotula entrada y salida del traductor arriba y su implementación o plataforma de ejecución en el pie. |
| Compilador cruzado | Compilador que corre en una plataforma y genera código para otra. |
| *Bootstrapping* | Construcción o transporte de un compilador mediante herramientas existentes, a menudo hasta poder compilar una versión escrita en su propio lenguaje. |
| MIPS y ARM | Familias de arquitecturas usadas como ejemplos de destinos de generación de código; una no ejecuta directamente binarios de la otra. |
| Zurich Compiler Kit / Pascal-P | Enfoque de portabilidad del compilador de Pascal mediante P-code y una máquina P implementable en varios equipos. |
| P-code y P-machine | Código intermedio y máquina abstracta de pila asociados con el transporte de Pascal. |
| ACK | *Amsterdam Compiler Kit*: conjunto de frentes, representación intermedia EM y posteriores para varios lenguajes y máquinas. |
| EM | Código intermedio de pila de ACK que separa la traducción del lenguaje fuente de la máquina objetivo. |
| UNCOL | Idea de un lenguaje intermedio común para reducir la necesidad de construir un traductor específico por cada pareja fuente–destino. |
| *Front end* | Parte que reconoce un lenguaje fuente y produce una representación aprovechable por las etapas posteriores. |
| *Back end* | Parte que transforma una representación intermedia en instrucciones para una arquitectura de destino. |
| Optimizador *peephole* | Transformación local de una secuencia corta de instrucciones mediante patrones equivalentes. |
| Optimizador global | Transformación que razona sobre regiones amplias del programa, como bloques, procedimientos o bucles. |
| Preprocesador y macro | El preprocesador transforma el texto antes de compilar; una macro define sustituciones o expansiones del texto según las reglas del sistema. |
| Ensamblador de dos pasadas | Primero identifica símbolos y direcciones y después emite código resolviendo referencias conocidas. |
| Referencia adelantada y *backpatching* | Referencia a un destino todavía desconocido y técnica de completar después su posición o dirección. |
| Enlazador (*linker*) | Combina archivos objeto y bibliotecas, resuelve símbolos y aplica relocalizaciones para formar una salida enlazada. |
| Enlazado dinámico | Resolución de referencias a bibliotecas compartidas al cargar o durante la ejecución. |
| Tabla de relocalización | Datos que indican posiciones de un objeto que deberán ajustarse al asignar direcciones definitivas. |
| Cargador (*loader*) | Componente que prepara en memoria el programa y sus dependencias para ejecutarlo. |
| Depurador (*debugger*) | Herramienta que permite inspeccionar y controlar un programa durante su ejecución para investigar fallos. |
| *Profiler* | Herramienta que mide dónde se consume tiempo u otros recursos en la ejecución. |
| Editor, IDE y gestor de versiones | Herramientas para escribir código, integrar tareas de desarrollo y conservar/coordinar cambios del proyecto. |

### D. Construcción de compiladores y proyecto MICRO

| Concepto | Definición y relación con el curso |
| --- | --- |
| Análisis léxico / *scanner* | Convierte caracteres en tokens reconocidos, como identificadores, números y operadores. |
| Token y lexema | Token es la categoría reconocida y lexema es el texto concreto que la produjo; `123` puede ser lexema de `ENTERO`. |
| `GetToken()` | Operación conceptual del escáner que entrega al parser el próximo token y sus datos asociados. |
| Generador de escáneres | Herramienta que construye un analizador léxico a partir de patrones o reglas de tokens. |
| Análisis sintáctico / *parser* | Comprueba la organización de tokens frente a una gramática y crea estructura o dispara acciones. |
| Descenso recursivo | Técnica de parsing con procedimientos que implementan reglas de la gramática y se llaman entre sí. |
| Gramática y producción | La gramática fija formas sintácticas; una producción indica cómo puede expandirse un símbolo no terminal. |
| Análisis semántico | Revisa restricciones de significado estático, como declaración, ámbito, tipos y operaciones válidas. |
| Tabla de símbolos | Estructura que asocia nombres con atributos útiles como tipo, ámbito, posición o dirección. |
| Tabla de literales | Registro de constantes literales y la información necesaria para representarlas o reutilizarlas. |
| AST | Árbol de sintaxis abstracta que conserva la estructura relevante del programa omitiendo detalles sintácticos innecesarios. |
| IR / código intermedio | Representación interna del programa que facilita análisis, optimización o traducción a diversos destinos. |
| Optimización | Transformación que busca mejorar una métrica conservando el comportamiento observable que el lenguaje exige. |
| Generación de código | Elección y emisión de instrucciones, registros y ubicaciones para la máquina destino. |
| Código objeto | Resultado ensamblado que puede contener instrucciones, símbolos y relocalizaciones antes del enlace definitivo. |
| Una pasada y archivos temporales | Un compilador de una pasada recorre esencialmente una vez la entrada; otros diseños conservan representaciones o resultados intermedios entre etapas. |
| Error léxico, sintáctico y semántico | Respectivamente: carácter o token no reconocible, combinación que viola la gramática y construcción formalmente válida que incumple reglas de significado. |
| MICRO | Proyecto didáctico del repositorio cuyo parser y generador emiten ensamblador x86-64 mientras procesan el programa, sin AST/IR separado. |
| `read` y `write` en MICRO | Construcciones de E/S traducidas a llamadas `scanf` y `printf` con argumentos y almacenamiento preparados por el código generado. |
| Condicional `(E1 | E2 | E3)` | Expresión MICRO que evalúa `E2` si `E1≠0`, o `E3` si `E1=0`, ejecutando solamente la rama elegida. |

### E. Hileras y lenguajes formales

| Concepto | Definición y relación con el curso |
| --- | --- |
| Alfabeto `Σ` | Conjunto finito de símbolos a partir de los cuales se forman hileras. |
| Hilera y longitud `|w|` | Secuencia finita de símbolos de `Σ` y número de símbolos que contiene. |
| Hilera vacía `ε` | Única hilera de longitud cero y elemento neutro de concatenar hileras: `εw=wε=w`. |
| Prefijo y sufijo | `p` es prefijo de `w` si `w=px`; `s` es sufijo si `w=xs`, con alguna hilera `x`. |
| Prefijo/sufijo propio | Prefijo o sufijo distinto de la hilera completa; en una hilera no vacía puede incluir `ε`. |
| Subhilera | Secuencia consecutiva interna de `w`: existe `x,y` tales que `w=xuy`. |
| Concatenación de hileras | `uv` es la secuencia formada por los símbolos de `u` seguidos por los de `v`; es asociativa pero no conmutativa en general. |
| Potencia `wⁿ` | Concatenación de `n` copias de `w`, con `w⁰=ε`. |
| Reverso `wᴿ` | Hilera con los símbolos de `w` en orden inverso; `(uv)ᴿ=vᴿuᴿ`. |
| `Σⁿ` | Conjunto de todas las hileras de longitud exactamente `n` sobre `Σ`, con `Σ⁰={ε}`. |
| `Σ*` y `Σ+` | `Σ*=⋃ₙ₌₀∞Σⁿ` contiene todas las hileras finitas incluida `ε`; `Σ+=⋃ₙ₌₁∞Σⁿ` excluye `ε`. |
| Lenguaje formal `L` | Cualquier subconjunto de `Σ*`, finito o infinito, definido sobre un alfabeto. |
| Lenguaje vacío `∅` frente a `{ε}` | `∅` no contiene ninguna hilera; `{ε}` contiene una hilera, la vacía; ambos son distintos de `ε`. |
| Unión e intersección | `L∪M` reúne miembros de ambos y `L∩M` conserva los comunes; `∅` es neutro de unión y `Σ*` de intersección. |
| Diferencia y complemento | `L\M` conserva miembros de `L` que no están en `M`; el complemento de `L` es `Σ*\L`, relativo al alfabeto escogido. |
| Reverso `Lᴿ` | `{wᴿ : w∈L}`, lenguaje que invierte individualmente las hileras de `L`. |
| Concatenación `LM` | `{uv : u∈L, v∈M}`; es asociativa, tiene neutro `{ε}` y absorbente `∅`, pero no es conmutativa en general. |
| Potencia `Lⁿ` | Concatenación de `n` elecciones de `L`; `L⁰={ε}` aunque `L=∅`. |
| Clausura `L*` y positiva `L+` | `L*=⋃ₙ₌₀∞Lⁿ` permite cero o más factores y siempre contiene `ε`; `L+=⋃ₙ₌₁∞Lⁿ` exige al menos uno, aunque también puede contener `ε` si `ε∈L`. |
| Reconocedor y generador | El reconocedor decide pertenencia de una hilera a `L`; el generador produce precisamente las hileras de `L`. |
| Prefijos/sufijos de `ECCI` | `Pref={ε,E,EC,ECC,ECCI}` y `Suf={ε,I,CI,CCI,ECCI}`. |

### F. DFA: definición, lógica y patrones de ejercicios

| Concepto | Definición y relación con el curso |
| --- | --- |
| DFA | Autómata finito determinista `M=(Q,Σ,δ,q₀,F)` que lee un símbolo a la vez y acepta según el estado donde termina. |
| `Q`, `Σ`, `δ`, `q₀`, `F` | Respectivamente, conjunto finito de estados, alfabeto, función total `Q×Σ→Q`, estado inicial de `Q` y conjunto de estados finales `F⊆Q`. |
| Determinismo y totalidad | Para cada estado y cada símbolo del alfabeto existe **exactamente un** estado siguiente. |
| Transición extendida `δ̂` | Aplicación de `δ` a hileras: `δ̂(q,ε)=q` y `δ̂(q,wa)=δ(δ̂(q,w),a)`. |
| Aceptación y `L(M)` | `M` acepta `w` si `δ̂(q₀,w)∈F`; `L(M)` es el conjunto de todas las hileras que acepta. |
| Aceptación de `ε` | Se cumple exactamente cuando `q₀∈F`; `δ̂(q,ε)=q` no introduce una transición ε. |
| Tabla y diagrama de transiciones | Dos representaciones de la misma función: fila estado/columna símbolo/valor siguiente, o flechas etiquetadas entre nodos. |
| Estado sumidero | Estado al que se envían entradas irrecuperablemente inválidas y que vuelve a sí mismo para todos los símbolos. |
| Complemento de DFA | Con `Q`, `Σ`, `δ` y `q₀` intactos y función total, sustituir `F` por `Q\F` reconoce `Σ*\L(M)`. |
| Seguimiento de sufijo | Estados que recuerdan el sufijo más largo de lo leído que también es prefijo de un patrón buscado, como `GAGA`. |
| Subhilera prohibida `GAGA` | Se aceptan los estados que aún no han completado `GAGA`; al completarla se entra en un sumidero de rechazo. |
| Condición `CC` y `A` precedida por `T` | Problema de combinar memoria de un `C` previo con el requisito para cada `A`; los bosquejos de la página 50 quedaron incompletos y no constituyen una tabla resuelta. |
| Condición de extremos | Para decidir si primer y último símbolo coinciden, los estados recuerdan el primero y el último; `ε` exige convención explícita. |
| Longitud módulo `k` | DFA con `k` estados que indican `|w| mod k`; cada símbolo avanza un residuo y `F` selecciona los deseados. |
| Número en base `b` módulo `m` | Si el prefijo tiene residuo `r` y llega dígito `d`, el siguiente estado es `(br+d) mod m`. |
| Divisibilidad decimal por 3 | Tres estados para residuos `0,1,2`; al leer `d`, `(10r+d) mod 3=(r+d) mod 3`. |
| Base 3 no divisible por 5 | Cinco estados de residuo `r`; con `d∈{0,1,2}` se actualiza a `(3r+d) mod 5` y se aceptan `1,2,3,4`. |
| Paridad de dos símbolos | Producto de dos recuerdos binarios: estados `(par/impar de A, par/impar de B)`; leer cada letra conmuta su componente. |
| Producto de DFA | Estados pares `(q₁,q₂)` que simulan dos condiciones a la vez; los finales dependen de si se pide conjunción, disyunción u otra combinación. |
| Guía de diseño | Precisar `Σ` y `ε`; decidir qué memoria finita del prefijo leído basta; crear estados; completar todas las transiciones; marcar `F`; probar casos positivos, negativos y bordes. |

### G. Pinker: adquisición y diversidad lingüística

| Concepto | Definición y relación con el curso |
| --- | --- |
| Capacidad lingüística como instinto | Tesis de Pinker de que la aptitud humana para adquirir lenguaje tiene bases biológicas y se desarrolla con exposición social; no implica nacer sabiendo una lengua particular. |
| «Órgano mental» | Analogía de especialización funcional de la mente para lenguaje, no nombre de un órgano cerebral anatómico aislado. |
| Universalidad y productividad | Las comunidades poseen lenguas estructuradas y sus hablantes pueden comprender o producir oraciones nuevas mediante recursos finitos. |
| Gramática mental | Conocimiento implícito de patrones para formar e interpretar expresiones, distinto de la norma escolar. |
| Noam Chomsky y gramática universal | Chomsky impulsó gramáticas generativas y la hipótesis de restricciones compartidas de la facultad humana de adquirir lenguas; sus formulaciones concretas son debatidas. |
| SSSM / tabla rasa | Modelo criticado por Pinker cuando supone que la mente se moldea enteramente por el entorno sin capacidades especializadas. |
| Pidgin | Variedad de contacto desarrollada entre grupos sin idioma común que normalmente no comienza como lengua nativa de una comunidad. |
| Criollo (*creole*) | Lengua natural comunitaria surgida en contexto de contacto; no equivale a pidgin carente de reglas. |
| Derek Bickerton | Lingüista asociado a hipótesis sobre formación de criollos citadas en la discusión de Pinker. |
| LSN / ISN | Etiquetas históricas de cohortes o etapas tempranas de la lengua de señas nicaragüense, con mayor sistematización observada entre generaciones. |
| Ann Senghas y Marie Coppola | Investigaron cambios gramaticales entre cohortes de señantes nicaragüenses. |
| Caso Simon | Niño sordo que sistematizó varios patrones morfológicos de ASL a partir de modelos parentales inconsistentes; no demuestra aprendizaje sin exposición. |
| Jenny Singleton y Elissa Newport | Investigadoras del caso Simon y de la regularización de morfología en ASL. |
| BEV / AAVE y William Labov | Variedad del inglés afroamericano estudiada por Labov que tiene reglas sistemáticas, aunque pueda ser estigmatizada socialmente. |
| Pobreza del estímulo | Argumento de que la entrada disponible no basta para explicar algunas generalizaciones si se supone aprendizaje solo de secuencias superficiales. |
| *Motherese* | Habla dirigida a niños con adaptaciones frecuentes; su forma especial no es requisito universal estricto, aunque sí importa la exposición lingüística. |
| Disociación y doble disociación | Perfiles donde dos capacidades varían separadamente, y comparación de perfiles opuestos que respalda componentes parcialmente distintos. |
| Afasia de Broca | Trastorno adquirido que suele afectar fluidez y producción gramatical, a veces también la comprensión compleja. |
| Familia KE, Myrna Gopnik y FOXP2 | Caso familiar con dificultades hereditarias de habla y lenguaje estudiado por Gopnik; la investigación posterior vinculó el cuadro con FOXP2, sin reducirlo a un «gen de la gramática». |
| Síndrome de Williams y Ursula Bellugi | Condición genética, generalmente por deleción 7q11.23, cuyo perfil lingüístico puede ser relativamente fuerte frente a ciertas dificultades cognitivas; Bellugi investigó esos perfiles. |

### H. Resto del quiz y precisión de estudio

| Concepto | Definición y relación con el curso |
| --- | --- |
| *Amathia* | En el quiz, ignorancia acompañada de seguridad injustificada de saber, que impide reconocer y revisar lagunas propias. |
| Fischer y LeBlanc, capítulo 2 | Compilador pequeño que muestra el recorrido completo: caracteres, tokens, parser, acciones semánticas y código. |
| Lectura de Patrick | Historia del monitor GM/NAA para IBM 704 y su relación con operación por lotes, E/S y herramientas de traducción. |
| Lectura de Tanenbaum y colaboradores | Explicación de ACK, EM, frentes/posteriores reutilizables y optimización. |

## Fuentes y notas de exactitud

- [Apuntes, páginas 1–10](semana-1-clases-1-y-2.md), [11–19](paginas-11-19-continuacion.md), [20–28](paginas-20-28-continuacion.md), [29–38](paginas-29-38-continuacion.md), [39–43](paginas-39-43-continuacion.md) y [44–50 más hoja posterior](paginas-44-50-continuacion.md).
- [Conceptos desarrollados de las lecturas](../conceptos-lecturas.md) y [quices resueltos](../documento.md); esos archivos enlazan las obras, artículos, código MICRO y referencias primarias pertinentes.
- La forma correcta es **FORTRAN = Formula Translation**, no «Formal Translation»; [IBM](https://www.ibm.com/history/fortran). Hopper influyó en COBOL mediante FLOW-MATIC y comités, sin ser su creadora única; [Computer History Museum](https://www.computerhistory.org/timeline/1959/).
- Para operaciones formales, distinguir siempre `ε` (hilera), `{ε}` (lenguaje unitario) y `∅` (lenguaje vacío). El complemento es relativo a `Σ*`; un DFA debe definir todas sus transiciones. [MIT OCW: autómatas finitos](https://ocw.mit.edu/courses/6-045j-automata-computability-and-complexity-spring-2011/pages/lecture-notes/).
- En los apuntes, el texto del ejemplo de la página 48 parece decir «termina en `001`», pero el diagrama representa «termina en `01`»; en la página 50, el ejercicio de `CC` y `A` no tiene tabla de transiciones completa. No se presentan esos dibujos como soluciones verificadas.
