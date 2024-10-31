* Entorno de trabajo para la prácticas de AOC

Las prácticas de la asignatura de Arquitectura y Organización de Computadores están pensadas para realizarse con unos compiladores concretos de C++. En concreto, vamos a utilizar compiladores de C++ modernos capaces de optimizar eficazmente programas para su ejecución en los procesadores actuales utilizando la versión actual del estándar del lenguaje y de OpenMP.

Es importante utilizar las versiones indicadas de los compiladores a la hora de realizar las prácticas para obtener resultados correctos y evitar problemas de compatibilidad. Aunque normalmente se podrá utilizar versiones más nuevas que las indicadas en este documento, los resultados obtenidos en ese caso pueden ser inesperados.

A la hora de la explicación y la realización de las prácticas se supondrá siempre un entorno Linux actualizado (por ejemplo: una versión actual de Fedora, Debian, Ubuntu o cualquier distribución similar). Asimismo, se supondrá siempre que el ordenador utilizado soporta el ISA x86-64. No se permite el uso de máquinas virtuales (como QEMU, KVM, VirtualBox o similares) para la realización de las prácticas.

Aunque los compiladores utilizados (y casi todo el software adicional necesario) están disponibles para los sistemas operativos Windows y Mac OS X en las respectivas páginas WEB de cada compilador, la instalación correcta de estos programas no es trivial y puede generar problemas, en especial si se quiere asegurar el uso de versiones correctas y evitar interferencias entre los tres compiladores y otras versiones de los mismos que también puedan estar presentes previamente en el sistema.

En particular, el compilador ICC que usamos ya no está soportado por Intel y necesita las librerías de una versión antigua de GCC.

Por todo lo anterior, se asume que estas prácticas se realizan en un entorno Linux actualizado y que se usa la imagen docker generada por el script aoc-docker-image. Cualquier problema causado por el uso de un entorno diferente es responsabilidad únicamente del alumno.

Usaremos principalmente el GCC versión 13.2.1 y el ICC versión 2021.3.1, y además mostraremos en algunos casos los resultados obtenidos también por Clang 16.0.6:

 - GCC (https://gcc.gnu.org/) es el compilador de GNU, que es capaz de generar código optimizado para prácticamente cualquier ISA y que está incluido en todas las distribuciones de Linux.  

 - ICC es el compilador de Intel, el cual se puede descargar de la página web de la compañía (https://software.intel.com/content/www/us/en/develop/tools/oneapi/all-toolkits.html). Usaremos la versión «clásica» de ICC, aunque esta versión está va a dejar de ser soportada por Intel, que va a basar las nuevas versiones de su compilador en Clang. 

 - Clang es el compilador de C y C++ basado en LLVM (https://llvm.org/). Este compilador se orginó en la Universidad de Illinois y es actualmente muy usado. Es el compilador principal utilizado por Apple y, como se ha mencionado, Intel ha comenzado a usarlo como base para las nuevas versiones de su compilador.

Los tres compiladores soportan el estándar actual de C++ (C++20) y, como ya se ha mencionado, están disponibles en la mayoría de los sistemas operativos. Todos ellos son capaces de compilar más lenguajes además de C++ (notablemente C y Fortran, pero también Rust o Go).

* Uso del script aoc-docker-image

Para facilitar el acceso a las versiones adecuadas de los compiladores y algunos otros programas que se utilizarán durante las prácticas, se ha preparado un script de Bash que genera una imagen Docker que se puede utilizar, si se desea, para realizar las prácticas. El script, llamado aoc-docker-image, automatiza la descarga de la imagen y su posterior ejecución de forma correcta.

El script requiere, lógicamente, tener instalado previamente Docker. Para ello, es suficiente con seguir las instrucciones disponibles en https://docs.docker.com/engine/install/ . En el caso de Linux, obsérvese que el procedimiento es diferente según la distribución utilizada. El script también funciona con podman, que está incluido en los repositorios de la mayoría de las distribuciones. Por ejemplo, en Fedora es suficiente con «dnf install podman-docker» para instalar todo lo necesario.

Una vez que esté instalado Docker y se haya comprobado que funciona (usando por ejemplo el comando «docker run -it hello-world»), se puede usar el script aoc-docker-image.

** Uso de aoc-docker-image

Si ejecutamos el script sin ningún argumento, nos mostrará un resumen de esta documentación. Normalmente usaremos siempre al menos un argumento, que será el comando que se quiera ejecutar dentro del contenedor.

Normalmente el uso de Docker en Linux requiere de privilegios de root, por lo que se debe usar sudo para ejecutar el script. Alternativamente, es posible otorgar permisos para usar Docker a cualquier usuario añadiéndolo al grupo correspondiente (por ejemplo, con un comando similar a «usermod nombre_usuario -a -G docker»).

La primera vez que ejecutemos el script, debemos usar el parámetro --download para descargar una imagen previamente construida por los profesores de la asignatura. Esta operación descargará todo el software necesario y es necesario realizarla solo una vez. Por ejemplo, si estamos en el directorio del script, podemos escribir «sudo ./aoc-docker-image --download». Este proceso puede tardar un cierto tiempo (según sea la velocidad de la conexión a Internet y del ordenador). Alternativamente, se puede usar el parámetro --build para generar la imagen a partir de los ficheros fuente, pero esta opción a veces da problemas con las librerías instaladas en el ordenador.

Una vez descargada (o construida) la imagen, podemos ejecutarla mediante el script. El script espera como argumentos el comando a ejecutar dentro del contenedor. El comando puede ser «bash», lo cual nos permitirá crear un shell en el contenedor desde el que podemos ejecutar varios comandos.

Por defecto, el contenedor tendrá acceso a los ficheros del directorio actual desde el que lo ejecutemos (y a todos sus subdirectorios). Por tanto, normalmente lo ejecutaremos desde un directorio donde estén presentes los ficheros de la práctica que se esté realizando. Por ejemplo, si hemos descargado los materiales de la práctica 1 en el directorio /home/nombre_usuario/datos/aoc/practicas/AOC-prac1-materiales, y tenemos el script en /home/nombre_usuario/datos/aoc/practicas/aoc-docker-image, los siguientes comandos nos permitirían compilar y ejecutar varios programas dentro del contenedor:

  $ cd /home/nombre_usuario/datos/aoc/practicas/AOC-prac1-materiales
  $ sudo /home/nombre_usuario/datos/aoc/practicas/aoc-docker-image/aoc-docker-image bash
  # cd peak-performance
  # make all
  # ./peak-freq-gcc
  # ./peak-flops-icc
  
Donde las líneas que comienzan con $ indican que el comando se ejecuta como usuario normal, y las que comienzan con # indican que el comando se ejecuta como root dentro del contenedor. No se muestra la salida de los comandos.

Debido a limitaciones de seguridad, el script puede no funcionar si se ejecuta sin privilegios suficientes en determinados directorios. En particular, no funciona si se ejecuta en el directorio «/home/alumno/» en los laboratorios de la Facultad de Informática (por lo que debe ejecutarse siempre en algún subdirectorio). Además, dependiendo de la configuración local, el script puede necesitar ligeras modificaciones para usarse sin privilegios de root (e.g., eliminación de la opción --privileged).

Se aconseja definir un alias (o hacer un pequeño script o función de bash) para ejecutar el script aoc-docker-image desde cualquier directorio. Por ejemplo con un comando similar a «alias a="sudo /home/nombre_usuario/datos/aoc/practicas/aoc-docker-image"». De esta forma, podremos ejecutar cómodamente la mayoría de los comandos casi como si estuviéramos trabajando sin Docker. Por ejemplo, escribiendo «a make all» y «a ./peak-freq-gcc» en el directorio de la práctica 1 compilaríamos todos los programas incluidos en los materiales y ejecutaríamos uno de ellos.

Obsérvese que los programas que se ejecutan en el contenedor lo hacen como root, por lo que los ficheros creados tendrán a root como propietario. Esto se puede cambiar posteriormente si se desea con el comando «chown».
