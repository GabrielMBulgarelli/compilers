# Conceptos desarrollados de las lecturas — Compiladores

Guía de estudio de las lecturas trabajadas en el curso. Se incluyen los capítulos **1 y 2** de *The Language Instinct* (Pinker), el capítulo 2 de *Crafting a Compiler with C* (Fischer y LeBlanc), el artículo histórico de Patrick y el artículo sobre ACK. **El capítulo 3 de Pinker queda fuera del examen.** Este archivo desarrolla ideas y conexiones; las afirmaciones históricas del libro de Pinker se identifican como tales cuando la investigación posterior las ha precisado.

## 1. Pinker, *The Language Instinct*, capítulo 1: «An Instinct to Acquire an Art»

### Lenguaje como instinto biológico y «órgano mental»

Pinker propone que la capacidad humana para **adquirir una lengua** es una especialización de la mente y el cerebro desarrollada por evolución, comparable en ese sentido a otras capacidades biológicas. «Instinto» no significa que un bebé nazca hablando español o inglés: la lengua particular depende de la comunidad y de la exposición a ella. «Órgano mental» es una analogía funcional, no un órgano anatómico aislado. La tesis distingue la adquisición ordinaria del habla y las señas del aprendizaje deliberado de la escritura, una tecnología cultural que exige enseñanza y práctica. La selección natural es la explicación evolutiva que defiende Pinker para la capacidad, aunque los detalles de su origen siguen siendo materia de investigación. [Pinker, cap. 1](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

**Para explicarlo en un examen:** una predisposición biológica hace posible aprender reglas; el entorno proporciona los ejemplos y determina cuál lengua se aprende. Biología y experiencia intervienen a la vez.

### Universalidad, complejidad y productividad

Todas las sociedades humanas conocidas usan sistemas lingüísticos estructurados; la ausencia de escritura o de una tradición escolar no implica ausencia de gramática. Calificar una lengua natural de «primitiva» confunde el poder social de sus hablantes con su estructura lingüística. Una persona combina un vocabulario finito y reglas para producir y entender **oraciones nuevas**: esta productividad muestra que hablar no consiste en repetir una lista memorizada. Las convenciones particulares difieren mucho entre lenguas, pero su capacidad expresiva y su carácter reglado son generales. [Pinker, caps. 1–2](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

### Gramática mental y gramática universal de Chomsky

La **gramática mental** es el conocimiento, normalmente implícito, que permite decidir cómo formar e interpretar expresiones de la lengua que uno conoce; no equivale a un manual escolar de «hablar correctamente». La **gramática universal (GU)**, en el marco de Chomsky que presenta Pinker, designa principios o restricciones de la capacidad humana para adquirir gramáticas, no una lengua mundial ni un diccionario heredado. El argumento del aprendizaje pregunta cómo el niño infiere estructuras abstractas a partir de ejemplos finitos y variables. El contenido exacto de la GU y el peso relativo de predisposiciones, interacción y aprendizaje estadístico son debatidos; no hay que presentar una versión específica como demostrada por un solo caso. [Pinker, cap. 1](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

### Crítica al «Modelo Estándar de las Ciencias Sociales» (SSSM)

Pinker contrasta su explicación con la idea de una mente **totalmente moldeada por la cultura**, sin mecanismos cognitivos especializados. Su objeción es que aprender cualquier cosa presupone capacidades y restricciones del aprendiz. Esto no elimina la influencia de la cultura ni implica que toda conducta sea genética. La lectura introduce esta crítica en el capítulo 1; la desarrolla más extensamente después, fuera del alcance señalado aquí. [Pinker, cap. 1](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

## 2. Pinker, capítulo 2: «Chatterboxes»

### Pidgin, criollo y papel de los niños

Un **pidgin** suele surgir como medio de comunicación entre hablantes sin lengua compartida; en sus primeras etapas tiene recursos menos estabilizados y menor extensión funcional. Un **criollo (creole)** es una lengua natural nativa y estructurada desarrollada en una comunidad a partir de ese contacto. Pinker emplea ejemplos de criollización para destacar que niños expuestos a sistemas variables pueden **regularizar patrones** y ampliar recursos gramaticales. «Pidgin sin gramática» es una simplificación: estos sistemas tienen convenciones, y el paso histórico a una lengua criolla no es idéntico en todos los casos ni tiene que ocurrir de golpe. **Clave:** complejidad y regularidad pueden emerger entre cohortes de hablantes. [Pinker, cap. 2](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

### Lengua de Señas Nicaragüense: LSN e ISN

Pinker usa **LSN** para el sistema temprano compartido por una primera cohorte de niños sordos nicaragüenses y **ISN** para la variedad más estructurada de cohortes posteriores; su descripción sirve para explicar la emergencia intergeneracional de una lengua de señas. No conviene memorizarlo como dos lenguas ajenas entre sí: son etiquetas históricas de etapas/cohortes de la **Lengua de Señas Nicaragüense** (también NSL en inglés). Las investigaciones de Senghas y Coppola observaron una mayor sistematización de recursos gramaticales espaciales en generaciones posteriores. La primera cohorte ya había organizado parte del material gestual; la siguiente elaboró sobre esa base. **Distinción útil:** gestos individuales de hogar → sistema compartido inicial → convenciones y gramática más sistemáticas a través de cohortes. [Senghas y Coppola, investigación original](https://siegler.tc.columbia.edu/wp-content/uploads/2020/08/Children_Creating_Language_How_Nicaraguan_Sign_Lan.pdf).

### Simon y la regularización de una entrada inconsistente

**Simon** era un niño sordo que aprendía lengua de señas estadounidense (ASL) de sus padres sordos, quienes habían aprendido ASL después de los quince años y usaban ciertos morfemas de manera inconsistente. A los siete años, Simon produjo varios de esos patrones morfológicos con mayor regularidad que sus padres y, para la mayoría de los morfemas examinados, con resultados comparables a los de otros niños con modelos nativos. La conclusión pertinente es que un niño puede organizar reglas **a partir de datos ruidosos**; el estudio no prueba que su gramática fuera «perfecta» en todos los aspectos ni que pudiera aprender sin entrada lingüística. [Singleton y Newport, 2004](https://pubmed.ncbi.nlm.nih.gov/15342259/).

### BEV/AAVE y la diferencia entre regla y prestigio

Pinker retoma el trabajo de **William Labov** sobre el llamado *Black English Vernacular* (BEV; hoy suele hablarse de *African American Vernacular English*, AAVE). Es una variedad con patrones gramaticales propios, no inglés estándar ejecutado «con errores». Por ejemplo, el **be habitual** expresa que algo ocurre habitualmente, una distinción que no equivale a borrar arbitrariamente el verbo estándar. Una variedad lingüística puede estar estigmatizada socialmente y, sin embargo, tener reglas productivas y precisas. **Pregunta típica:** juzgar una oración de AAVE con las reglas del inglés estándar describe una diferencia dialectal; no demuestra falta de lógica. [Pinker, cap. 2](https://stevenpinker.com/pinker/publications/language-instinct-19942007); [Labov, «The Logic of Nonstandard English»](https://eric.ed.gov/?id=ED029271).

### Pobreza del estímulo, estructura y *motherese*

La **pobreza del estímulo** es el argumento de que las entradas observadas por un niño no explican por sí solas ciertas generalizaciones gramaticales si se supone que aprende solo repitiendo o contando secuencias superficiales. En preguntas inglesas, por ejemplo, la regla adecuada atiende a la **estructura de la cláusula** y no simplemente al primer *is* que aparezca de izquierda a derecha. El argumento motiva hipótesis sobre restricciones del aprendizaje; por sí solo no especifica ni demuestra una GU concreta. *Motherese* o **habla dirigida al niño** son adaptaciones frecuentes del habla adulta; Pinker subraya que esa forma especial de hablar no es un requisito universal estricto. **Esto no significa que la exposición a una lengua ni la interacción social sean prescindibles.** [Pinker, cap. 2](https://stevenpinker.com/pinker/publications/language-instinct-19942007).

### Disociaciones entre lenguaje y otras capacidades

Una **disociación** muestra que dos capacidades no siempre cambian juntas; una **doble disociación** compara perfiles opuestos y respalda que intervienen componentes diferenciables. En esta lectura:

| Caso | Hallazgo relevante | Precisión para no exagerar |
| --- | --- | --- |
| Afasia de Broca | Una lesión cerebral puede causar habla poco fluida y dificultades gramaticales, con ciertas capacidades no lingüísticas relativamente conservadas. | La comprensión de construcciones complejas también puede verse afectada; no equivale a inteligencia global perfectamente intacta. |
| Familia KE estudiada por Myrna Gopnik | En varios familiares aparece un trastorno heredable del habla y el lenguaje, junto con dificultades en tareas morfológicas. | La investigación posterior vinculó esta familia con **FOXP2** y también describió dificultades motoras del habla: no existe aquí una prueba de un único «gen de la gramática», ni todos los trastornos del desarrollo del lenguaje tienen la misma causa. |
| Síndrome de Williams | Algunas habilidades verbales pueden ser **relativamente fuertes** frente a otras dificultades cognitivas, sobre todo visoespaciales. | Los perfiles individuales son variables; no implica lenguaje perfecto ni que todas las personas tengan «retraso severo». |

El patrón apoya una **especialización parcial** de capacidades lingüísticas, no una separación absoluta entre lenguaje, cognición y entorno. Hay además una **corrección histórica importante**: el libro de Pinker atribuye provisionalmente Williams a un gen del **cromosoma 11**; hoy se sabe que generalmente se debe a una **deleción en 7q11.23, cromosoma 7**, que afecta a varios genes. [Pinker, cap. 2](https://stevenpinker.com/pinker/publications/language-instinct-19942007); [NIDCD, afasia](https://www.nidcd.nih.gov/es/espanol/afasia); [Lai y cols., FOXP2](https://www.nature.com/articles/35097076); [MedlinePlus, Williams](https://medlineplus.gov/genetics/condition/williams-syndrome/).

## 3. Fischer y LeBlanc, *Crafting a Compiler with C*, capítulo 2: compilador sencillo

**Pregunta central:** ¿cómo convierte un compilador un programa fuente sencillo en instrucciones ejecutables? El capítulo presenta un compilador pequeño para que el flujo completo sea visible antes de profundizar en cada etapa. En el repositorio del curso está [Fischer-Cap2.pdf](projects/Fischer-Cap2.pdf); la referencia bibliográfica al capítulo como «A simple compiler» puede comprobarse en [Purdue, lecturas de compiladores](https://engineering.purdue.edu/~milind/ece573/2011fall/project/step1/step1.html).

- **Análisis léxico (*scanner*):** lee caracteres y agrupa unidades como identificadores, números, palabras reservadas y símbolos; por ejemplo, `suma := x + 1` se reconoce como identificador, asignación, identificador, suma y entero. Debe distinguir el contenido textual de cada token de su categoría.
- **Análisis sintáctico (*parser*):** comprueba que el orden de los tokens sigue una gramática y organiza expresiones y sentencias según sus producciones. En un **descenso recursivo**, procedimientos correspondientes a no terminales consumen tokens y llaman a otros procedimientos; una regla como `expr → term {(+|−) term}` permite iterar sobre sumas y restas.
- **Acciones semánticas:** hacen que reconocer una construcción tenga efecto: comprobar el significado o tipo permitido, registrar identificadores o preparar instrucciones. La sintaxis válida por sí sola no garantiza que una operación tenga sentido.
- **Tabla de símbolos:** relaciona nombres del programa con datos necesarios para compilarlos, como ubicación o tipo; ayuda a detectar usos incorrectos y a generar accesos a los objetos correspondientes.
- **Generación de código:** traduce las construcciones reconocidas a operaciones de una máquina objetivo. Al compilar una expresión, el orden de evaluación y el lugar donde se guarda el resultado importan; la salida puede ser ensamblador o una representación intermedia según el diseño.
- **Compilador de una pasada:** procesa el programa siguiendo esencialmente un recorrido de entrada y puede emitir código durante el análisis, si la gramática y las dependencias del lenguaje permiten resolver las decisiones a tiempo. No todos los compiladores operan así.

**Recorrido que conviene poder explicar:** caracteres → tokens → estructura sintáctica → comprobaciones y acciones semánticas → código; ante un error, precisar **en cuál etapa** se detecta. Una entrada con símbolo desconocido es problema léxico; un `+` sin operando, sintáctico; una operación no permitida para los tipos presentes, semántico. El ejemplo del capítulo es didáctico: no representa toda la arquitectura de un compilador industrial.

## 4. Robert L. Patrick, «General Motors/North American Monitor for the IBM 704 Computer»

Este artículo de **1987** narra trabajo de mediados de los **años cincuenta** sobre el monitor del IBM 704. El problema era operativo: ejecutar trabajos manualmente y dejar intervalos ociosos desperdiciaba tiempo de una máquina costosa. La solución de General Motors Research y North American Aviation organizó **lotes** de trabajos y normalizó la operación. [Patrick, RAND P-7316](https://www.rand.org/pubs/papers/P7316.html); [relato de Patrick conservado por Software Preservation Group](https://softwarepreservation.computerhistory.org/os/gm.html).

| Concepto | Función en el sistema histórico |
| --- | --- |
| *Monitor* | Programa supervisor que coordina la ejecución y pasa de un trabajo al siguiente sin exigir que un programador vuelva a preparar manualmente la máquina. |
| Procesamiento por lotes (*batch*) | Agrupa trabajos de distintos usuarios para ejecutarlos sucesivamente, aumentando la utilización del IBM 704. |
| Fase de traducción de entrada | Convierte tarjetas y datos de entrada a una forma preparada para la fase de cálculo; el sistema podía integrar ensamblado y, más adelante, FORTRAN. |
| Fase de cálculo | Ejecuta cada trabajo bajo el control del monitor y registra resultados y datos de contabilidad. |
| Fase de traducción de salida | Convierte la salida del lote a una forma entregable a los usuarios. |
| Tarjetas de control | Señalan identidad, opciones y límites de un trabajo: antecedente de los lenguajes de control de trabajos. |

**Relación con Compiladores:** un compilador o un ensamblador puede ser una de las herramientas ejecutadas para preparar un trabajo, mientras que el monitor administra la **secuencia de trabajos y la entrada/salida**. La lectura muestra por qué compilar programas y operar computadoras eran problemas conectados pero distintos. **Figura histórica:** Robert L. Patrick propuso la arquitectura; Owen Mock dirigió el equipo de North American Aviation y George Ryckman el de GM que la implementó. No atribuir a una sola persona toda la implementación. [Patrick y colaboradores, relato](https://softwarepreservation.computerhistory.org/os/gm.html).

## 5. Tanenbaum, van Staveren, Keizer y Stevenson, «A Practical Tool Kit for Making Portable Compilers» (ACK)

El **Amsterdam Compiler Kit (ACK)** organiza compiladores mediante una representación intermedia común, **EM**, para evitar rehacer toda la traducción por cada combinación de lenguaje y máquina. Si hay **N** lenguajes fuente y **M** arquitecturas destino, el ideal arquitectónico es desarrollar aproximadamente **N front ends + M back ends**, más la infraestructura compartida, en lugar de **N × M compiladores independientes**. Esa cuenta describe la reutilización de componentes, no el costo total exacto: bibliotecas, compatibilidad y adaptación de cada plataforma aún requieren trabajo. [Artículo original de ACK](https://tack.sourceforge.net/olddocs/toolkit.html).

| Componente | Qué recibe y qué produce |
| --- | --- |
| Preprocesador | Transforma texto fuente antes de compilarlo: macros, inclusiones y compilación condicional. |
| *Front end* | Lee un lenguaje fuente concreto y emite **EM**; el artículo menciona Pascal, C y Plain. |
| **EM** | Lenguaje intermedio de una máquina abstracta basada en **pila**; desacopla lenguajes fuente y máquinas destino. |
| Optimizador local (*peephole*) | Reescribe secuencias cortas de EM mediante patrones, por ejemplo carga de `x`, carga de `1`, suma y almacenamiento de `x` → incremento de `x`. |
| Optimizador global | Analiza regiones más amplias, como bloques, procedimientos y bucles. |
| *Back end* | Traduce EM a ensamblador específico de la arquitectura elegida mediante tablas de correspondencia. |
| Optimizador destino y ensamblador/enlazador | Afinan el ensamblador de la máquina, producen objetos y unen las rutinas requeridas. |
| Intérprete EM y pruebas | Permiten ejecutar o depurar el código intermedio y comprobar los componentes de una nueva implementación. |

**Ejemplo de seguimiento:** para `K := I + 7`, el artículo muestra conceptualmente `LOL I; LOC 7; ADI 2; STL K`: cargar `I`, apilar `7`, sumar enteros de dos bytes y almacenar el resultado en `K`. El **front end** decide esa secuencia EM por la semántica del programa; el **back end** elige instrucciones reales de la CPU destino. EM se parece a P-code por la máquina de pila, pero ACK busca servir a varios lenguajes y arquitecturas. La propuesta recupera la idea de **UNCOL**, un lenguaje intermedio común. **Distinción de examen:** optimizar EM favorece cambios independientes de la máquina; optimizar ensamblador aprovecha instrucciones y modos de direccionamiento de una máquina particular. [Artículo original, secciones «Front Ends», «Peephole Optimizer» y «Back End»](https://tack.sourceforge.net/olddocs/toolkit.html).

## 6. Relación entre las lecturas y nombres que conviene distinguir

| Persona o concepto | Aporte y relación |
| --- | --- |
| Steven Pinker | Defiende la capacidad lingüística como especialización biológica y reúne ejemplos de adquisición en los capítulos 1–2. |
| Noam Chomsky | Propone investigar la gramática mental y las restricciones generales de la adquisición; Pinker retoma la noción de GU. |
| William Labov | Documenta la estructura de variedades no estándar, clave para separar prejuicio social y regla gramatical. |
| Derek Bickerton | Asociado a hipótesis sobre formación de criollos discutidas por Pinker; no equivale a afirmar que todos surgieron del mismo modo. |
| Ann Senghas y Marie Coppola | Investigaron cambios gramaticales entre cohortes en la lengua de señas nicaragüense. |
| Jenny Singleton y Elissa Newport | Estudiaron la regularización de la morfología de ASL en el caso de Simon. |
| Myrna Gopnik | Estudió la familia KE y sus dificultades lingüísticas; trabajos genéticos posteriores identificaron FOXP2. |
| Ursula Bellugi | Investigó el perfil cognitivo y lingüístico en el síndrome de Williams. |
| Charles N. Fischer y Richard J. LeBlanc | Presentan un compilador sencillo como recorrido concreto de sus fases. |
| Robert L. Patrick, Owen Mock y George Ryckman | Arquitectura y equipos del monitor por lotes GM/NAA del IBM 704. |
| Andrew S. Tanenbaum y coautores | Explican ACK: *front ends*, EM y *back ends* para portabilidad. |

**Conexión conceptual — analogía, no identidad:** la gramática natural que estudia Pinker se **adquiere** en una comunidad; la gramática formal de un lenguaje de programación se **especifica** para que un compilador reconozca y traduzca programas. Ambas permiten hablar de reglas y estructuras, pero un niño y un parser no aprenden ni operan del mismo modo. Fischer enseña cómo traducir una lengua de programación concreta; ACK muestra cómo reutilizar traducciones entre varias lenguas y máquinas; Patrick explica el entorno histórico en que herramientas de traducción se integraban en lotes de cómputo.

## Fuentes de la lectura y verificación

1. Steven Pinker, *The Language Instinct*, capítulos 1 y 2; [ficha del autor](https://stevenpinker.com/pinker/publications/language-instinct-19942007). El capítulo 3 no se incluye.
2. Fischer y LeBlanc, *Crafting a Compiler with C*, capítulo 2: [PDF del curso](projects/Fischer-Cap2.pdf); [referencia independiente del título y alcance del capítulo](https://engineering.purdue.edu/~milind/ece573/2011fall/project/step1/step1.html).
3. Robert L. Patrick, [*General Motors/North American Monitor for the IBM 704 Computer*](https://www.rand.org/pubs/papers/P7316.html), RAND, 1987; [copia en el repositorio](readings/0101%20-%20Patrick.pdf).
4. A. S. Tanenbaum y cols., [*A Practical Tool Kit for Making Portable Compilers*](https://tack.sourceforge.net/olddocs/toolkit.html); [copia en el repositorio](readings/ACK.pdf).
5. Investigación primaria para verificar o matizar ejemplos de Pinker: [Senghas y Coppola, lengua de señas nicaragüense](https://siegler.tc.columbia.edu/wp-content/uploads/2020/08/Children_Creating_Language_How_Nicaraguan_Sign_Lan.pdf); [Singleton y Newport, Simon](https://pubmed.ncbi.nlm.nih.gov/15342259/); [Lai y cols., FOXP2 en la familia KE](https://www.nature.com/articles/35097076); [MedlinePlus Genetics, síndrome de Williams](https://medlineplus.gov/genetics/condition/williams-syndrome/).

**Alcance:** este documento resume conceptos de esas lecturas, no sustituye los ejercicios de DFA, hileras o ensamblador de los apuntes y quices. No desarrolla la lectura separada de VOLE ni los temas de NFA; el capítulo 3 de Pinker tampoco forma parte del temario indicado.
