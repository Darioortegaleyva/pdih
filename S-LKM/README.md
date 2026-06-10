### Seminario 4: Módulos Cargables del Kernel (LKM)
**Autores:** Darío Ortega e Inés Prados

**Asignatura:** Periféricos y Dispositivos de Interfaz Humana (PDIH)

#### 1. Objetivos del Seminario
El objetivo principal de esta práctica ha sido estudiar el sistema de módulos cargables del kernel (LKM) de Linux. Hemos desarrollado un módulo sencillo en lenguaje C, procediendo a cargarlo y descargarlo dinámicamente en el kernel sin necesidad de reiniciar el sistema, verificando su comportamiento a través de los registros (logs).

#### 2. Preparación del Entorno (Vagrant)
Puesto que inyectar módulos en el kernel puede ser peligroso y provocar el bloqueo del sistema, hemos utilizado una máquina virtual (Vagrant con Ubuntu 22.04 LTS) como entorno seguro. 

Para poder compilar nuestro código contra el núcleo de Linux, preparamos el sistema instalando las cabeceras y las herramientas de construcción:
* `sudo apt-get install linux-headers-$(uname -r)`
* `sudo apt-get install build-essential`

#### 3. Código y Compilación
Hemos utilizado los archivos `hello.c` y `Makefile` proporcionados en la documentación del seminario. 

El archivo fuente en C utiliza la función `printk()` en lugar de las llamadas estándar de usuario para comunicarse con el espacio del núcleo. Al ejecutar el comando `make`, el código se ha compilado exitosamente, generando nuestro objeto de módulo `hello.ko`.

#### 4. Pruebas de Carga y Descarga del Módulo LKM
A continuación, detallamos las pruebas realizadas usando las herramientas del kernel:

* **Inserción:** Ejecutamos `sudo insmod hello.ko` para inyectar el módulo.
* **Comprobación:** Lanzamos `lsmod | grep hello` y el sistema nos devolvió `hello 16384 0`, confirmando la reserva de memoria.
* **Metadatos:** Al usar `modinfo hello.ko` verificamos la firma del módulo (Autor: Derek Molloy, Licencia: GPL, Versión 0.1).
* **Revisión del Log (Entrada):** Ejecutando `sudo dmesg | tail -n 5` observamos que la rutina de inicialización registró correctamente el mensaje: `[ 488.639084] EBB: Hello world from the BBB LKM!`.
* **Extracción:** Eliminamos el módulo de manera segura con `sudo rmmod hello`.
* **Revisión del Log (Salida):** Revisamos de nuevo el registro y confirmamos la ejecución de la rutina de limpieza: `[ 511.919901] EBB: Goodbye world from BBB LKM!`.

![Proceso de carga y descarga en la terminal](captura_terminal_lkm.png)

#### 5. Observaciones y Curiosidades
Durante el proceso de compilación con `make`, el sistema nos arrojó la siguiente advertencia:
`warning: the compiler differs from the one used to build the kernel`

**Análisis:** Esto ocurrió porque el kernel actual de la máquina virtual fue construido con la versión de `gcc` **11.4.0-1ubuntu1~22.04.2**, mientras que al instalar el paquete `build-essential` nosotros estábamos utilizando una subversión ligeramente más actualizada (**11.4.0-1ubuntu1~22.04.3**). Al tratarse de un parche de revisión menor, el compilador genera el objeto `.ko` correctamente y el módulo funciona a la perfección, pero es un excelente recordatorio de lo estricto que es el Kernel de Linux con las versiones de sus herramientas de construcción.
