# Acerca del proyecto

Para correr de manera local el proyecto se debe comentar la función run del archivo _*receivecandata.cpp*_ así como los 2 include que hay en este archivo. Por otra parte, en el archivo *main.cpp* debe estar comentada la línea *qputenv("QT_QPA_PLATFORM", QByteArray("wayland-egl"));*.

Para el deploy se siguió las instrucciones del archivo _*C_CPP_Developerguide_BR*_. 

Nota: para subir los archivos durante la configuración del kit fue necesario al utilizar el comando scp agregarle la flag *-O*, siendo entonces los argumentos *-O %{buildDir}/pantalla root@192.168.135.2:/opt/*.

# Acerca de la recepción de datos del bus CAN

Para recibir los datos provenientes del bus CAN desde el archivo *mainwindow.cpp* se conecta las señales provenientes del objeto _*CANData*_ hacia sus respectivos encargados de actualizar la información de la pantalla.

Cada widget encargado de mostrar la información posee métodos denominados *nombreMensaje()* para recibir dicha conexión.

Por otra parte, se puede testear el parseo de los mensajes CAN a través del método presente en el archivo *mainwindow.cpp*.


## Tipos de mensajes

Según lo descrito en el archivo *Protocolo ZeMaq Bus CAN 2.xlsx* los tipos de mensaje son:

- message1
- message2
- message3
- message4
- message5
- message6
- message7
- bess1
- bess2
- bess3
- bess4
- bess5

## candata.cpp

Clase utilizada para almacenar los datos provenientes del bus CAN así como recibir y parsear los mensajes.

Desde este se envían señales por cada uno de los tipos de mensaje según el mensaje recibido por la conexión del socket.

Cuenta con los métodos clone y equal utilizados con propósitos de testing.

## receivecandata.cpp

Clase descendiente de QThread que se encarga de realizar la conexión con el bus CAN a través del socket.

Envía una señal al thread principal de *mainwindow.cpp* cada vez que recibe un mensaje.


# Panel de información avanzada

Pantalla secundaria en la cual se puede acceder a información más completa del estado del vehículo.

## adminpanel.cpp

Widget que maneja el panel de información avanzada, cambiando entre las 4 pestañas de equipos, batería, variables de proceso y errores.

En los siguientes 4 archivos se encuentran dichas pestañas. 

En todos además hay funciones para recibir cada una de las señales de los mensajes, denominadas *nombreMensaje*.
Estas se encargan de actualizar la información según el mensaje recibido.

Por otra parte, existen funciones para testear la correcta conexión con la recepción de mensajes y su correspondiente cambio en la información.
Dichas funciones se denominan *assertNombreMensaje*.

### batterypanel.cpp

Widget que maneja la información de la batería en el panel de información avanzada. 
Este panel cuenta con 3 tabs, uno con información general, otro con información del voltaje de las celdas y otro con las temperaturas.

### enginewidget.cpp

Widget que maneja la información de los equipos en el panel de información avanzada. 
En este se presenta la información del motor, las resistencias, dcdc1, dcdc2 y dc.

### processvarswidget.cpp

Widget que maneja la información de las variables de proceso en el panel de información avanzada. 

### errorspanel.cpp

Widget que maneja la información de los errores recibidos en el panel de información avanzada. 


# Otros

## checkbox.cpp

Widget para simular el funcionamiento de un checkbox

## notificationswidget.cpp

Widget que se encarga de mostrar la información de las alertas en la pantalla principal.

## utils.cpp

Funciones varias para el manejo de bits y bytes.

