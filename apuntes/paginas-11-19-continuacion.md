# Apuntes de Compiladores: continuación, páginas 11–19

Continúa [la transcripción de las páginas 1–10](semana-1-clases-1-y-2.md). Las imágenes recibidas en este lote contienen de nuevo la **página 10** (`10768.jpg`), ya incorporada en el archivo anterior; aquí se transcriben únicamente las **páginas manuscritas 11–19**. En particular, `10777.jpg` corresponde a la página 18 y `10776.jpg` a la página 19. Se conserva la redacción de los apuntes, con puntuación y saltos de línea adaptados a Markdown. No se han verificado las afirmaciones como hechos externos.

## Semana I — Clase II (continuación)

### Página 11 — Lenguaje máquina y ensamblador (`10769.jpg`)

#### Lenguaje máquina

**Relación.** Constituye otra capa sobre la microprogramación y se define que arquitectura = lenguaje máquina.

**Propósito.** Programar en esta capa requiere menos esfuerzo y es más sencillo que en microprogramación.

**Funcionamiento.** Programa en RAM, la memoria principal de acceso aleatorio donde se mantienen programas y datos en ejecución; se inicializa el *program counter* y se da la orden de ejecución.

**Requisito.** Se deben conocer los códigos de operación; se deben conocer los modos de direccionamiento donde se encuentran operandos.

#### Ensamblador

**Problema.** Todavía resulta difícil y se necesita una capa adicional de ayuda en lenguaje máquina.

**Características:**

- Permite mnemónicos.
- Nombres simbólicos.
- Facilita la programación.
- Aumenta productividad sin reducir eficiencia.

### Página 12 — Lenguajes de alto nivel; productividad y eficiencia (`10770.jpg`)

#### Lenguajes de alto nivel

**Propósito.** Se agrega otra capa pues los previos son muy poco flexibles con muchos detalles.

**Características:**

- Son independientes del hardware.
- Proporcionan portabilidad.
- Mayor abstracción.
- Permiten solo pensar en el lenguaje.

#### Productividad y eficiencia

Varía según métodos y afecta el trabajo realizado.

## Semana II — Clase III (17-08-26)

### Página 13 — Lenguaje máquina y máquina VOLE (`10771.jpg`)

#### Máquina VOLE

**Características anotadas:**

- Direcciones entre `0x0` y `0xF`.
- Se muestran con 4 bits, `2^4` registros.
- RAM es de 256 y PC es de 8 bits.
- Cada instrucción mide 2 bytes, 16 bits.
- El código de operación (*codop*) cubre 4 bits y los otros 12 bits en tres argumentos.
- *Instruction Register* de 16 bits, 2 bytes.
- *Program Counter* de 8 bits, 1 byte.
- Se puede simular usando SimpSim.
- El ciclo *fetch* carga de RAM siguiendo PC: 2 bytes cada vez y PC crece en 2.

**Esquema dibujado.** CPU con PC e IR conectada a RAM. Tabla de memoria:

| Dirección | Contenido |
| --- | --- |
| `00` | `20` |
| `01` | `C0` |
| `02` | `30` |
| `…` | `…` |

**Ejemplo:**

| Instrucción | PC después de traerla | IR | Efecto escrito en el cuaderno |
| --- | --- | --- | --- |
| `20C0` | `02` | `20C0` | «Almacena C0 en el registro 0». |
| `3004` | `04` | `3004` | «Almacena r0 en el registro 04» [tal como aparece; verificar si «04» se refiere a una dirección de memoria]. |

### Página 14 — Uso típico y análisis de una máquina dedicada (`10772.jpg`)

#### Uso típico de máquina dedicada

**Cadena del diagrama:** FORTRAN → ensamblador → lenguaje máquina → programa ejecutable → resultado real.

**Relación/procedimiento:**

1. Configura tableros de control.
2. Colocar FORTRAN en lector de tarjetas y *bootear* computadora.
3. Leer desde fuente lectora y configurar pasadas.
4. Sin errores, compilador perfora programa en equivalente en ensamblador.
5. Colocar ensamblador en lectora de tarjetas y *bootear* computadora.
6. Colocar ensamblador generado por compilador en lectora de tarjetas y ver pasadas.
7. Ensamblador perfora lenguaje máquina de programa.
8. Colocar lenguaje máquina en lector y *bootear*. Programa corre.
9. Recolectar listados de impresora.

#### Analizando máquina dedicada

**Características.** Distinguidas en ventajas y desventajas.

**Ventajas:**

- Control del programador es mayor.
- Pocos expertos.
- Fácil establecer responsabilidades y controles.

**Desventajas:**

- Mucho trabajo repetido.
- Sin estándares y programadores conocen todo el hardware como deber.
- Ineficiente.

### Página 15 — Mejorando la máquina dedicada; sistemas operativos primitivos (`10773.jpg`)

**Tarea escrita en rojo:** «Leer *General Motors* de Patrick enviado por correo».

#### Mejorando máquina dedicada

**Idea.** Se crea la labor de operador de computadoras y los programadores dejan de generar todo por su cuenta.

Ahora se recolectan y factorizan pasos. Se usan configuraciones estándar. Aparecen operaciones *batch*. La productividad y el *throughput* aumentan.

**Pregunta.** ¿Se necesitan operadores?

Dado que el trabajo era mecánico, se buscó reemplazar a los operadores y se crea software: sistemas operativos.

#### Sistemas operativos primitivos

**Características:**

- Muchos compiladores (ej.: FORTRAN).
- Menos fallas de hardware.
- Los programas debían poderse distinguir en lenguajes y segmentos de trabajo. Para ello se crearon JCL: *Job Control Language* → interfaz usuario con S. O.; antecesores de *shell languages*.

### Página 16 — Entrada y salida primitivas; sistema operativo como máquina virtual (`10774.jpg`)

*La cabecera de esta página dice «Semana 2 — Clase 2», aunque las páginas contiguas están rotuladas «Clase 3»; se conserva la numeración manuscrita sin decidir cuál cabecera es correcta.*

#### Entrada y salida primitivas

**Características:**

- Arquitectura von Neumann sugiere espacio para E/S.
- Antes cada programador escribía rutinas de E/S.
- Eran compartidas entre programadores hasta que se crearon librerías.

**Idea.** Todos necesitaban E/S, por lo que siempre se necesitaban en memoria y se buscan alojar en el sistema operativo. Los programas empiezan a llamar al S. O. para funciones de E/S.

**Definición.** *Device drivers* → operaciones de E/S del S. O.

Bajo estas condiciones se propuso que el S. O. proporcione servicios a los programas y se nombran *system calls*.

**Tipos de máquinas en el apunte:**

- Real → se ve y existe.
- Transparente → no se ve y existe.
- Virtual → no existe y se ve.
- Máquinas: dispositivos que efectúan labores.

#### Sistema operativo como máquina virtual

**Definición.** Máquina que vemos pero no existe. Las capas se redefinen para acoplarse. El S. O. remueve la dificultad con hardware.

**Cadena dibujada:** SO → ensamblador → lenguaje de alto nivel → *apps*.

### Página 17 — Máquinas y lenguajes (`10775.jpg`)

**Contexto.** Existen máquinas reales y máquinas virtuales que se alojan.

**Definiciones:**

- Programa → texto formado por símbolos que describe y prescribe funciones para realizarse en máquinas.
- Lenguaje de programación → un sistema de notación que permite describir cómputos.

**Relación.** Se menciona que hay una equivalencia entre lenguaje y máquina.

**Pregunta.** ¿Qué es crear una máquina virtual?

Lograr que otra máquina pueda usar y comunicarse con otra. Cada máquina virtual se crea sobre la anterior. `M_i → M_(i−1)`, donde el problema es mapear `L_i` en `L_(i−1)`.

- **Traducción:** convertir `L_i` en `L_(i−1)` y se ejecuta una sola vez.
- **Interpretación:** tomar instrucción de `M_i`, simular ejecución en `M_(i−1)`. Se interpreta de nuevo cada vez.

**Compilador (texto en rojo).** Software que traduce lenguaje escrito en el lenguaje de una máquina virtual a otro equivalente de otra máquina virtual.

### Página 18 — Lenguajes y compiladores: diagramas T (`10777.jpg`)

**Contexto.** Existen tres lenguajes asociados a un compilador:

- **Lenguaje fuente:** entrada que es traducida.
- **Lenguaje objeto:** salida traducida.
- **Lenguaje implementación:** compilador.

El diagrama T dibujado identifica **source** a la izquierda, **target** a la derecha y **host** debajo del compilador.

**Ejemplo.** GCC → *GNU Compiler Collection*. Escrito por Richard Stallman.

**Operaciones.** Se pueden combinar para representar procesos de traducción complejos. Los diagramas representan, de forma esquemática:

```text
T(S → T; host H) + T(T → W; host H) = T(S → W; host H)
```

Se pueden concatenar indefinidamente con el mismo proceso.

**Ejemplo anotado.** Un diagrama T con «Ensamblador IBM 704» como fuente, «[Ensamblador / lenguaje] máquina IBM 704» a la derecha [rótulo superpuesto en la fotografía] y «Lenguaje máquina IBM 704» como *host*. Al lado figura «Caso típico» y «Ejemplos F2C y GCC». Abajo: «Incluir ejemplo con 2 compiladores».

### Página 19 — SAP y lenguaje de implementación (`10776.jpg`)

**Fecha y cabecera.** `20/08/26`, «Semana 2 — Clase 4».

#### Symbolic Assembly Program (SAP)

**Contexto.** IBM 704 escrito por Roy Nutt en lenguaje máquina, hecho en 1956. Influencia todos los ensambladores del futuro.

#### Lenguaje de implementación

**Contexto.** Históricamente escribir compiladores son proyectos difíciles.

**Ejemplo.** Se pueden encadenar pese a que el *source* y el *target* sean distintos.

La página dibuja una composición de varios diagramas T con letras `A`, `B`, `C`, `D`, `E` para ilustrar ese encadenamiento. Los rótulos y la disposición de algunos diagramas se solapan; se mantiene la idea expresada por el texto sin asignar a cada letra una función no inequívoca.

**Ejemplo real (rótulos en diagramas T):**

| Fuente | Objeto | Implementación / *host* dibujado |
| --- | --- | --- |
| Pascal | x86 | FORTRAN |
| FORTRAN | x86 | C |
| C | x86 | x86 |

Texto final: «Se pueden hacer compiladores de FORTRAN y Pascal que corren en x86 además de brindar x86» [la última expresión aparece así en el manuscrito].

---

**Estado de la secuencia:** páginas **1–19** transcritas; en este archivo se añadieron las páginas **11–19**. La imagen repetida de la página 10 no se duplicó. Las notas de duda identifican trazos o rótulos ambiguos, no correcciones del contenido de clase.
