# Acerca del proyecto

Para correr de manera local el proyecto se debe comentar la función run del archivo _*receivecandata.cpp*_ así como los 2 include que hay en este archivo. 
Lo mismo para el archivo *UDSCanData.cpp*.
Por otra parte, en el archivo *main.cpp* debe estar comentada la línea *qputenv("QT_QPA_PLATFORM", QByteArray("wayland-egl"));*.

Para el deploy se siguió las instrucciones del archivo _*C_CPP_Developerguide_BR*_. 

Para el desarrollo se contó con 2 kits, uno configurado como se detalla en el archivo mencionado anteriormente, y otro configurado para el computador de desarrollo.

Nota: para subir los archivos a la pantalla durante la configuración del kit fue necesario al utilizar el comando scp agregarle la flag *-O*, siendo entonces los argumentos *-O %{buildDir}/pantalla root@192.168.135.2:/opt/*.


# Acerca de la recepción de datos del bus CAN

Para recibir los datos provenientes del bus CAN desde el archivo *mainwindow.cpp* se conecta las señales provenientes del objeto _*CANData*_ hacia sus respectivos widgets encargados de actualizar la información de la pantalla.

Cada widget encargado de mostrar la información posee métodos denominados *nombreMensaje()* para recibir dicha conexión.

Por otra parte, se puede testear el parseo de los mensajes CAN J1939 a través del método presente en el archivo *mainwindow.cpp*.


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

Cuando se recibe un error se guarda en un archivo csv la información del error y se envía una señal al resto de componentes de la pantalla. 

Además, cuando se cargan los errores recibidos durante el historial del equipo para dejarlos a disposición de los demás componentes.

## receivecandata.cpp

Clase descendiente de QThread que se encarga de realizar la conexión con el bus CAN utilizando el protocolo J1939 a través del socket.

Envía una señal al thread principal de *mainwindow.cpp* cada vez que recibe un mensaje. 
Cada tipo de mensaje envía una señal distinta.
Cada objeto que maneja alguna interfaz tiene métodos para actualizar la interfaz en función del tipo de mensaje.

En este además se recibe la información de los errores provenientes del bus CAN mediante el protocolo UDS. 

*_Nota_*: No todos los valores recibidos tienen implementados sus factores de cálculo y offset. 
Tanto para los valores obtenidos por J1939 como UDS.
Tampoco tienen necesariamente su tipo de dato correcto (algunos debería ser float por ejemplo).

## UDSCanData.cpp

Clase descendiente de QThread que se encarga de la conexión UDS con el controlador.

En ella se piden los DIDs y se espera a recibirlos, para luego mandar la información raw al objeto de *candata.cpp*.

En este el método receiveUDSMessage es el que se encarga de interpretar el mensaje.

## Test

En el archivo _mainwindow.cpp_ se encuentran una serie de test para cada tipo de mensaje, en este se realiza un testing aleatorio para comprobar que efectivamente los mensajes son recibidos y parseados correctamente.

Por otra parte, existen funciones para testear la correcta conexión con la recepción de mensajes y su correspondiente cambio en la información.
Dichas funciones se denominan *assertNombreMensaje*.

# Panel de información avanzada

Pantalla secundaria en la cual se puede acceder a información más completa del estado del vehículo.

## adminpanel.cpp

Widget que maneja el panel de información avanzada, cambiando entre las 4 pestañas de equipos, batería, variables de proceso y errores.

En los siguientes 4 archivos se encuentran dichas pestañas. 

En todos además hay funciones para recibir cada una de las señales de los mensajes, denominadas *nombreMensaje*.
Estas se encargan de actualizar la información según el mensaje recibido.


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
En este se muestra una tabla en la que se muestran los errores recibidos por la pantalla.

Los errores mostrados en dicha tabla son todos los errores que ha recibido el equipo en su historia.
Para ello se leen los errores los cuales son guardados en un archivo csv, y se queda atento a las señales que se lanzan cuando se recibe un nuevo error.

En la tabla se puede filtrar por equipos o sortear por columnas.

# Testigos

Se definieron los siguientes testigos:

- SIM100
- DCDC 
- Inversor (EDS)
- BESS
- BTMS
- Temperatura
- Línea piloto (HVIL)
- Sensor
- Capó abierto
- E-stop
- Batería LV
- Batería HV
- ATS
- Motor
- Incendio
- Contactor principal
- Aislación

# Errores CAN

Tanto en los archivos de *receivecandata* como *sendcandata* se implementó el protocolo UDS, en el cual la pantalla le pide al controlador los errores que tiene en su pila.

Una vez recibidos se envía una señal al resto de componentes de la pantalla para notificar el nuevo error.
De esta manera se actualiza la tabla de errores,  dejando el log en un archivo (errors.csv).
También se debe agregar al área de notificaciones del panel principal (aún por decidir cual es la condición para que se quede aquí).
Por otra parte, también se debe prender (ya sea parpadeando o solo encendido) el testigo si corresponde según el tipo de error.
Aún no se definen los testigos a utilizar (a priori uno por cada equipo).

Para los testigos, estos solo se muestran cuando tienen una alerta asociada. Hay 1 por cada equipo y otros varios. 
Algunos se prender procedientes de los errores obtenidos por UDP y otros por variables de proceso.

## DTCCaneError.cpp

En este archivo se parsea y almacena la información de todos los tipos de errores dado el id correspondiente.

# Otros

## checkbox.cpp

Widget para simular el funcionamiento de un checkbox

## notificationswidget.cpp

Widget que se encarga de mostrar la información de las alertas en la pantalla principal.

## utils.cpp

Funciones varias para el manejo de bits y bytes.

## testigocontroller.cpp

Widget que se encarga de manejar los testigos activos y su correspondiente animación.

# USS (no implementado)

Los datos del uss recibidos a través del bus CAN deben ser ser procesados y mostrados en la pantalla de sensor, accesible desde la pantalla principal.
En dichos datos se debería recibir la información en la que se detalla el objeto más cercano, clasificado en 2 tipos: Punto y Línea, junto a la distancia respecto al sensor.

El diseño de esta interfaz (aún no implementada) se puede ver en figma.

# Links

- [Figma](https://www.figma.com/design/DZc9cLo1U9k7Mq8VNClsgY/Pantalla?node-id=234-214&t=iq6gBsp6CmiKzEhb-1)
- [SocketCan](https://www.kernel.org/doc/html/latest/networking/can.html)
- [Actualizar fecha y hora linux](https://unix.stackexchange.com/questions/79112/how-do-i-set-time-and-date-from-the-internet)
- [J1939](https://docs-kernel-org.translate.goog/networking/j1939.html?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc)
- [ISOTP](https://docs.kernel.org/6.11/networking/iso15765-2.html)
- [SocketCan y ISOTP](https://s3.eu-central-1.amazonaws.com/cancia-de/documents/proceedings/slides/hartkopp_slides_15icc.pdf)

# Íconos


