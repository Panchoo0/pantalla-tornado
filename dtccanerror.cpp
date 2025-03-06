#include "dtccanerror.h"
#include <QDebug>
#include <utils.h>

DTCCanError::DTCCanError(int code, QString category, QString equipment, QString description, QDateTime date, bool lightIndicator) {
    this->code = code;
    this->category = category;
    this->equipment = equipment;
    this->description = description;
    this->date = date;
    this->lightIndicator = lightIndicator;
}

// Constructor que dado un id retorna toda la información de dicho error
DTCCanError DTCCanError::fromInt(int id) {
    QString category;
    QString description;
    QString equipment;
    QDateTime date = QDateTime::currentDateTime();
    bool lightIndicator = false;

    switch (id) {

    case 0xD000:
        equipment = "DCDC1";
        category = "Batería LV";
        description = "Voltaje en bus LV excede \numbral definido";
        lightIndicator = true;
        break;

    case 0xD001:
        equipment = "DCDC1";
        category = "Batería LV";
        description = "Bajovoltaje en batería \nauxiliar";
        lightIndicator = true;
        break;

    case 0xD002:
        equipment = "DCDC1";
        category = "Batería HV";
        description = "Sobrevoltaje en banco de \nbaterías";
        lightIndicator = true;
        break;

    case 0xD003:
        equipment = "DCDC1";
        category = "Batería HV";
        description = "Bajovoltaje en banco de \nbaterías";
        lightIndicator = true;
        break;

    case 0xD004:
        equipment = "DCDC1";
        category = "Corriente \nLV";
        description = "Sobrecorriente en bus LV";
        lightIndicator = true;
        break;

    case 0xD005:
        equipment = "DCDC1";
        category = "Corriente \nLV";
        description = "Corriente que entra al DCDC \nmuy alta";
        lightIndicator = true;
        break;

    case 0xD006:
        equipment = "DCDC1";
        category = "Voltaje LV";
        description = "Voltaje en bus LV excede 32 V";
        lightIndicator = true;
        break;

    case 0xD007:
        equipment = "DCDC1";
        category = "\nTemperatura";
        description = "Temperatura interna sobre \n85°C";
        lightIndicator = false;
        break;

    case 0xD008:
        equipment = "DCDC1";
        category = "\nTemperatura";
        description = "Temperatura de transistor de \npotencia sobre 130°C";
        lightIndicator = false;
        break;

    case 0xD009:
        equipment = "DCDC1";
        category = "Hardware";
        description = "Falla de hardware ocurre";
        lightIndicator = false;
        break;

    case 0xD00A:
        equipment = "DCDC1";
        category = "Bus LV";
        description = "Voltaje en bus LV baja de 1 \nsúbitamente";
        lightIndicator = true;
        break;

    case 0xD00B:
        equipment = "DCDC1";
        category = "Entrada";
        description = "La señal de choque está en low: \nevento de volcamiento";
        lightIndicator = true;
        break;

    case 0xD00C:
        equipment = "DCDC1";
        category = "\nComunicacion";
        description = "Señal CAN de NM se demoró más de \n1 segundo en llegar";
        lightIndicator = false;
        break;

    case 0xD00D:
        equipment = "DCDC1";
        category = "\nComunicacion";
        description = "Se solicitó por CAN \ntransicionar a estado prohibido";
        lightIndicator = false;
        break;

    case 0xD00E:
        equipment = "DCDC1";
        category = "\nComunicacion";
        description = "Hay en el bus un DTC con formato \nSAE J2012";
        lightIndicator = false;
        break;

    case 0xD100:
        equipment = "DCDC2";
        category = "Batería LV";
        description = "Voltaje en bus LV excede \numbral definido";
        lightIndicator = true;
        break;

    case 0xD101:
        equipment = "DCDC2";
        category = "Batería LV";
        description = "Bajovoltaje en batería \nauxiliar";
        lightIndicator = true;
        break;

    case 0xD102:
        equipment = "DCDC2";
        category = "Batería HV";
        description = "Sobrevoltaje en banco de \nbaterías";
        lightIndicator = true;
        break;

    case 0xD103:
        equipment = "DCDC2";
        category = "Batería HV";
        description = "Bajovoltaje en banco de \nbaterías";
        lightIndicator = true;
        break;

    case 0xD104:
        equipment = "DCDC2";
        category = "Corriente \nLV";
        description = "Sobrecorriente en bus LV";
        lightIndicator = true;
        break;

    case 0xD105:
        equipment = "DCDC2";
        category = "Corriente \nLV";
        description = "Corriente que entra al DCDC \nmuy alta";
        lightIndicator = true;
        break;

    case 0xD106:
        equipment = "DCDC2";
        category = "Voltaje LV";
        description = "Voltaje en bus LV excede 32 V";
        lightIndicator = true;
        break;

    case 0xD107:
        equipment = "DCDC2";
        category = "\nTemperatura";
        description = "Temperatura interna sobre \n85°C";
        lightIndicator = true;
        break;

    case 0xD108:
        equipment = "DCDC2";
        category = "\nTemperatura";
        description = "Temperatura de transistor de \npotencia sobre 130°C";
        lightIndicator = true;
        break;

    case 0xD109:
        equipment = "DCDC2";
        category = "Hardware";
        description = "Falla de hardware ocurre";
        lightIndicator = true;
        break;

    case 0xD10A:
        equipment = "DCDC2";
        category = "Bus LV";
        description = "Voltaje en bus LV baja de 1V \nsúbitamente";
        lightIndicator = true;
        break;

    case 0xD10B:
        equipment = "DCDC2";
        category = "Input";
        description = "La señal de choque está en low: \nevento de volcamiento";
        lightIndicator = true;
        break;

    case 0xD10C:
        equipment = "DCDC2";
        category = "Comm";
        description = "Señal CAN de NM se demoró más de \n1 segundo en llegar";
        lightIndicator = false;
        break;

    case 0xD10D:
        equipment = "DCDC2";
        category = "Comm";
        description = "Se solicitó por CAN \ntransicionar a estado prohibido";
        lightIndicator = false;
        break;

    case 0xD10E:
        equipment = "DCDC2";
        category = "Comm";
        description = "Hay en el bus un DTC con formato \nSAE J2012";
        lightIndicator = false;
        break;

    case 0xD200:
        equipment = "SIM100";
        category = "Hardware";
        description = "Conexión rota entre SIM100 a \nnegativo de batería HV";
        lightIndicator = false;
        break;

    case 0xD201:
        equipment = "SIM100";
        category = "Hardware";
        description = "Conexión rota entre SIM100 a \npositivo de batería HV";
        lightIndicator = false;
        break;

    case 0xD202:
        equipment = "SIM100";
        category = "Hardware";
        description = "Conexión al chassis rota";
        lightIndicator = false;
        break;

    case 0xD203:
        equipment = "SIM100";
        category = "Hardware";
        description = "Conexión VX1 y VX2 invertidas";
        lightIndicator = false;
        break;

    case 0xD204:
        equipment = "SIM100";
        category = "Batería HV";
        description = "Voltaje de excitación fuera \nde rango (0 o muy grande)";
        lightIndicator = false;
        break;

    case 0xD205:
        equipment = "SIM100";
        category = "Batería HV";
        description = "Voltaje de alimentación LV \nfuera de rango";
        lightIndicator = false;
        break;

    case 0xD206:
        equipment = "SIM100";
        category = "Hardware";
        description = "Cualquier error de hardware \nse detectó: solicitar flags de \nerror";
        lightIndicator = false;
        break;

    case 0xD207:
        equipment = "SIM100";
        category = "Batería HV";
        description = "Battery Voltage (HV) > \nMax__working_voltage. Ocurre también si aún no se \ndefine el voltaje máximo de \noperación";
        lightIndicator = false;
        break;

    case 0xD208:
        equipment = "SIM100";
        category = "Comm";
        description = "Incertidumbre > 5%";
        lightIndicator = false;
        break;

    case 0xD209:
        equipment = "SIM100";
        category = "Aislación";
        description = "Resistencia de aislación < \n500 Ohm / V";
        lightIndicator = true;
        break;

    case 0xD20A:
        equipment = "SIM100";
        category = "Aislación";
        description = "Resistencia de aislación < \n100 Ohm / V";
        lightIndicator = true;
        break;

    case 0xD20B:
        equipment = "SIM100";
        category = "Batería HV";
        description = "Battery Voltage (LV) < \nMin_battery_working_voltage (22V)";
        lightIndicator = false;
        break;

    case 0xD300:
        equipment = "EDS";
        category = "Voltaje HV";
        description = "Se excedió el umbral máximo \npara voltaje de bus HV";
        lightIndicator = true;
        break;

    case 0xD301:
        equipment = "EDS";
        category = "Voltaje HV";
        description = "Se excedió por debajo el \nvoltaje mínimo de bus HV";
        lightIndicator = true;
        break;

    case 0xD302:
        equipment = "EDS";
        category = "Monitoreo \nHV";
        description = "Se detectó inconsistencia en \nlas mediciones del bus HV : la \nfiabilidad del monitoreo no se puede \nasegurar";
        lightIndicator = true;
        break;

    case 0xD303:
        equipment = "EDS";
        category = "Voltaje HV";
        description = "Se excedió el penúltimo \numbral máximo de voltaje de bus HV";
        lightIndicator = true;
        break;

    case 0xD304:
        equipment = "EDS";
        category = "Voltaje DC";
        description = "Se excedió el primer umbral \npara voltaje máximo de bus HV";
        lightIndicator = true;
        break;

    case 0xD305:
        equipment = "EDS";
        category = "Voltaje DC";
        description = "Se excedió  por debajo el \numbral mínimo 2 para bus HV";
        lightIndicator = true;
        break;

    case 0xD306:
        equipment = "EDS";
        category = "Voltaje DC";
        description = "Se excedió el primer umbral \npara voltaje mínimo de bus HV";
        lightIndicator = true;
        break;

    case 0xD307:
        equipment = "EDS";
        category = "Corriente \nDC";
        description = "Cortocircuito en bus DC HV o en \nfases del motor";
        lightIndicator = true;
        break;

    case 0xD308:
        equipment = "EDS";
        category = "Corriente \nDC";
        description = "Corriente en los \ntransistores de potnecia excedió el peak \nmáximo permitido ";
        lightIndicator = true;
        break;

    case 0xD309:
        equipment = "EDS";
        category = "Corriente \nDC";
        description = "Corriente suministrada al \nmotor superó el valor límite \nparametrizado";
        lightIndicator = true;
        break;

    case 0xD30A:
        equipment = "EDS";
        category = "Velocidad";
        description = "El feedback de velocidad \nalcanzó un valor alto impermisible";
        lightIndicator = true;
        break;

    case 0xD30B:
        equipment = "EDS";
        category = "Velocidad";
        description = "El tiempo de frenado, luego de \napagar o por un evento de error, \nsuperó el timeout parametrizado";
        lightIndicator = true;
        break;

    case 0xD30C:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Si alguna señal del encoder \n(sin o cos) sale de su rango se \ngenera este error. Para encoders \ndigitales, si hay un error de checksum";
        lightIndicator = true;
        break;

    case 0xD30D:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Si se almacena alguna \nadvertencia en el encoder.";
        lightIndicator = true;
        break;

    case 0xD30E:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = " Posibles múltiples fuentes \nde falla relacionadas a la \ninterfaz de comunicación del encoder ";
        lightIndicator = true;
        break;

    case 0xD30F:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Señales del encoder 1 son \nincorrectas. Como hay un encoder 2 \nredundante no hay error pero sí una \nadvertencia. Es posible operar sin un \nencoder";
        lightIndicator = true;
        break;

    case 0xD310:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Se activó una función de \nmonitoreo del encoder o la diferencia \nentre la posición del canal 1 del \nencoder y el canal 2 del encoder excede \nel umbral de monitoreo.";
        lightIndicator = true;
        break;

    case 0xD311:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Se detectaron senales \ninconsistentes del segundo encoder del motor";
        lightIndicator = true;
        break;

    case 0xD312:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "La salida de frecuencia del \ncontrolador es mayor a 599 Hz. Velocidad \ndel motor muy alta";
        lightIndicator = false;
        break;

    case 0xD313:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "La velocidad del eje del motor \nes muy baja (menor a 100 rpm)";
        lightIndicator = false;
        break;

    case 0xD314:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Error grave durante la \ninicializacion del encoder: reemplazar \nhardware";
        lightIndicator = true;
        break;

    case 0xD315:
        equipment = "EDS";
        category = "Setpoint";
        description = "Luego de reaccionar a un \nerror, el EDS no puede llegar a torque \n0 luego del tiempo máximo \nparametrizado";
        lightIndicator = false;
        break;

    case 0xD316:
        equipment = "EDS";
        category = "Valor de \nsetpoint";
        description = "El valor comandado hacia el \nEDS de velocidad es superior al \nvalor límite";
        lightIndicator = true;
        break;

    case 0xD317:
        equipment = "EDS";
        category = "Valor de \nsetpoint";
        description = "El torque se encuentra \nlimitado, ya sea por temperatura, \nvelocidad y/o voltaje";
        lightIndicator = false;
        break;

    case 0xD318:
        equipment = "EDS";
        category = "Valor de \nsetpoint";
        description = "El EDS está limitando el \ncomando de velocidad al límite \nparametrizado ";
        lightIndicator = true;
        break;

    case 0xD319:
        equipment = "EDS";
        category = "Valor de \nsetpoint";
        description = "Error del lazo de control. \nDeben ocurrir simultáneamente \nque: El valor efectivo del torque \nestá en su límite, el valor \nefectivo del torque y la velocidad \nactual tienen signos opuestos, la \nvelocidad del eje es mayor a 20 rpm, la \naceleración y la desviación de control \ntienen signos opuestos.";
        lightIndicator = true;
        break;

    case 0xD31A:
        equipment = "EDS";
        category = "Límite de \ntorque";
        description = "Error durante la \ndeterminación segura del torque aplicado. \n15 posibles razones revisar";
        lightIndicator = false;
        break;

    case 0xD31B:
        equipment = "EDS";
        category = "Límite de \ntorque";
        description = "El torque se ha limitado a 0 por \nalguna razón. Por ejemplo, proteger \npartes mecánicas en ciertos eventos";
        lightIndicator = false;
        break;

    case 0xD31C:
        equipment = "EDS";
        category = "Firmware";
        description = "El firmware subido al EDS no se \nactualizó como debía";
        lightIndicator = true;
        break;

    case 0xD31D:
        equipment = "EDS";
        category = "Firmware";
        description = "El firmware no es compatible \ncon el equipo";
        lightIndicator = true;
        break;

    case 0xD31E:
        equipment = "EDS";
        category = "Firmware";
        description = "La sección de potencia del EDS \nno es compatible con el firmware";
        lightIndicator = true;
        break;

    case 0xD31F:
        equipment = "EDS";
        category = "Firmware";
        description = "Se activaron mas funciones \nque lo que el paquete de funciones \nvendido permite. Garantia perdida";
        lightIndicator = true;
        break;

    case 0xD320:
        equipment = "EDS";
        category = "Firmware";
        description = "Se uso una combinacion de \nmodulos y firmware invalida. \nContactar a servicio";
        lightIndicator = true;
        break;

    case 0xD321:
        equipment = "EDS";
        category = "Firmware";
        description = "Se uso una combinacion de \ncircuiteria y firmware invalida. \nContactar a servicio";
        lightIndicator = true;
        break;

    case 0xD322:
        equipment = "EDS";
        category = "Firmware";
        description = "Se uso una combinacion de \nhardware y firmware invalida. \nContactar a servicio";
        lightIndicator = true;
        break;

    case 0xD323:
        equipment = "EDS";
        category = "Error de \nejecución";
        description = "Error grave de ejecución del \nprograma del EDS. Se requiere \ndiagnóstico detallado (ver \nobservación).";
        lightIndicator = true;
        break;

    case 0xD324:
        equipment = "EDS";
        category = "Error de \nejecución";
        description = "El watchdog de un EDS \nconfigurado en modo PLC se activa";
        lightIndicator = false;
        break;

    case 0xD325:
        equipment = "EDS";
        category = "\nDiagnóstico";
        description = "El EDS detectó que por lo menos \nun criterio de conexión se violó \n(Timeout de mensajes, problemas con \ncontadores o CRCs)";
        lightIndicator = true;
        break;

    case 0xD326:
        equipment = "EDS";
        category = "\nDiagnóstico";
        description = "El EDS no pudo procesar \nmensajes de diagnóstico, \nprobablemente por haber demasiados \nmensajes en muy poco tiempo.";
        lightIndicator = true;
        break;

    case 0xD327:
        equipment = "EDS";
        category = "\nDiagnóstico";
        description = "El EDS no pudo procesar \nmensajes de diagnóstico, \nprobablemente por haber demasiados \nmensajes en muy poco tiempo.";
        lightIndicator = true;
        break;

    case 0xD328:
        equipment = "EDS";
        category = "\nDiagnóstico";
        description = "La comunicación CAN falló \nluego del comisionamiento";
        lightIndicator = true;
        break;

    case 0xD329:
        equipment = "EDS";
        category = "\nDiagnóstico";
        description = "NA . Válido solo para conexión \nEthernet en vez de CAN";
        lightIndicator = false;
        break;

    case 0xD32A:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "En la reaccion mejor posible \ndesaceleracion, se supero el delay maximo para \napagar la maquina";
        lightIndicator = true;
        break;

    case 0xD32B:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "Temperatura llegó al límite \nabsoluto. Carga termal también superó \nel máximo. El torque pasa a 0 para \nprevenir la destrucción del equipo";
        lightIndicator = true;
        break;

    case 0xD32C:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "La carga termal del equipo \nsuperó el primer umbral";
        lightIndicator = true;
        break;

    case 0xD32D:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "La carga termal superó el 100% \ndel modelo térmico. ";
        lightIndicator = true;
        break;

    case 0xD32E:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "El dispositivo superó un \ntiempo timeout con su temperatura \nmuy alta. ";
        lightIndicator = true;
        break;

    case 0xD32F:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "La temperatura del \ndispositivo superó el primer umbral. En un \ntimeout se genera el F2018";
        lightIndicator = true;
        break;

    case 0xD330:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "Sensor en el controlador \ndefectuoso: reemplazar seccion de \npotencia o el controlador completo";
        lightIndicator = true;
        break;

    case 0xD331:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "Error en el calculo del modelo \nde temperatura. Actualizar \nfirmware o cambiar equipo";
        lightIndicator = true;
        break;

    case 0xD332:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "Temperatura del motor superó \nel valor límite";
        lightIndicator = true;
        break;

    case 0xD333:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "Monitoreo de la temperatura \ndel motor falló por alguna razón \n(sensor malo o cable cortado)";
        lightIndicator = true;
        break;

    case 0xD334:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "La temperatura del motor \nsuperó el primer umbral o la carga \ntermal del motor superó el primer \numbral";
        lightIndicator = true;
        break;

    case 0xD335:
        equipment = "EDS";
        category = "Sensor de \nTemperatura";
        description = "Temperatura de motor \ninferior al limite de lectura de 0°C";
        lightIndicator = false;
        break;

    case 0xD336:
        equipment = "EDS";
        category = "Corriente \nMotor";
        description = "Sobrecarga de motor por \ncorriente transiente muy alta. ";
        lightIndicator = true;
        break;

    case 0xD337:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "Motor excedio su limite de \ntemperatura. Maquina se desacelero \nautomaticamente a 0";
        lightIndicator = true;
        break;

    case 0xD338:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Durante parada de emergencia \no equivalente, el EDS no se ha \ndetenido en el tiempo parametrizado";
        lightIndicator = true;
        break;

    case 0xD339:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se comandó por CAN al EDS pasar \na un modo de operación no \npermitido";
        lightIndicator = false;
        break;

    case 0xD33A:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se intentó pasar a control de \nmotor sin que el controlador \nestuviera listo (condiciones de \noperación no cumplidas (como bus HV sin \nvoltaje), STO está activado, parada de \nemergencia está activada)";
        lightIndicator = false;
        break;

    case 0xD33B:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Es un aviso para dar a entender \nque se aplicó el STO durante la \nconducción ";
        lightIndicator = true;
        break;

    case 0xD33C:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "HV Discharge se activó \ndurante control de motor";
        lightIndicator = true;
        break;

    case 0xD33D:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se intentó pasar a control de \nmotor estando en STO";
        lightIndicator = true;
        break;

    case 0xD33E:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "En la transición a un estado \nseguro (como por parada de \nemergencia), el EDS no pudo llegar a la nueva \nvelocidad target dentro del tiempo \nmáximo de transición parametrizado";
        lightIndicator = true;
        break;

    case 0xD33F:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se intentó apagar al EDS por \nCAN ero no están las condiciones \npara ello (como estado de control \nde motor o voltaje DC muy alto)";
        lightIndicator = false;
        break;

    case 0xD340:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "EDS no se puede apagar";
        lightIndicator = false;
        break;

    case 0xD341:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se aplico HV discharge por un \npin y por CAN a la vez o con poco \ndesfase";
        lightIndicator = false;
        break;

    case 0xD342:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "El hardware de la sección de \ncontrol está defectuoso. Un \ningeniero de servicio de Rexroth debe \nreparar el EDS)";
        lightIndicator = true;
        break;

    case 0xD343:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "Fallaron múltiples tramas en \nel módulo interno opcional o en \nlas tarjetas opcionales \nexternas.";
        lightIndicator = true;
        break;

    case 0xD344:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "Fallaron múltiples tramas \nentre el módulo de comunicación y la \nsección de control del EDS";
        lightIndicator = true;
        break;

    case 0xD345:
        equipment = "EDS";
        category = "Corriente \ndel motor";
        description = "La suma de corrientes de las 3 \nfases del motor no es 0. Ello implica \nuna falla a tierra en las fases del \nmotor.";
        lightIndicator = true;
        break;

    case 0xD346:
        equipment = "EDS";
        category = "Corriente \ndel motor";
        description = "La variación de corriente \nrespecto de su referencia es muy grande \n(trimming no funciona bien)";
        lightIndicator = true;
        break;

    case 0xD347:
        equipment = "EDS";
        category = "\nCortocircuito";
        description = "En por lo menos una fase, la \ncorriente es 0 durante la operación";
        lightIndicator = true;
        break;

    case 0xD348:
        equipment = "EDS";
        category = "Voltaje LV ";
        description = "Voltaje en el bus LV demasiado \nalto";
        lightIndicator = false;
        break;

    case 0xD349:
        equipment = "EDS";
        category = "Voltaje LV";
        description = "Voltaje en el bus LV demasiado \nbajo";
        lightIndicator = true;
        break;

    case 0xD34A:
        equipment = "EDS";
        category = "Voltaje LV";
        description = "Voltaje en el bus LV bajo. \nPrimer umbral";
        lightIndicator = true;
        break;

    case 0xD34B:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Se detectó un parámetro \ninválido asociado a la sección de \npotencia o tiene un valor inadmisible";
        lightIndicator = true;
        break;

    case 0xD34C:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Ocurrió un error en la placa \nasociada a la sección de potencia";
        lightIndicator = true;
        break;

    case 0xD34D:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Se detectó un imbalance en las \ncapacitancias del bus DC interno. Apagar y \nencender";
        lightIndicator = true;
        break;

    case 0xD34E:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Se detectó un error en los \ncircuitos de interrupción. Apagar y \nencender";
        lightIndicator = true;
        break;

    case 0xD34F:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Se detecto un error en la \nseccion de potencia al inicializar el \nequipo";
        lightIndicator = true;
        break;

    case 0xD350:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Advertencia no fatal \ngenérica";
        lightIndicator = false;
        break;

    case 0xD351:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Advertencia E3 genérica";
        lightIndicator = false;
        break;

    case 0xD352:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Advertencia E4 genérica";
        lightIndicator = false;
        break;

    case 0xD353:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Advertencia fatal genérica";
        lightIndicator = false;
        break;

    case 0xD354:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error no fatal genérico";
        lightIndicator = false;
        break;

    case 0xD355:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error no fatal asociado a la \ntecnología de seguridad genérico";
        lightIndicator = false;
        break;

    case 0xD356:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error de interfase genérico";
        lightIndicator = false;
        break;

    case 0xD357:
        equipment = "EDS";
        category = "Parada de \nEmergencia";
        description = "Se gatillo parada de \nemergencia";
        lightIndicator = true;
        break;

    case 0xD358:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error de categoría F6 \ngenérico";
        lightIndicator = true;
        break;

    case 0xD359:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error asociado a la \ntecnología de seguridad genérico";
        lightIndicator = true;
        break;

    case 0xD35A:
        equipment = "EDS";
        category = "Otras EDS";
        description = "Error fatal generico";
        lightIndicator = true;
        break;

    case 0xD35B:
        equipment = "EDS";
        category = "Firmware";
        description = "Error al acceder a la memoria \nde la sección de control";
        lightIndicator = false;
        break;

    case 0xD35C:
        equipment = "EDS";
        category = "Control del \nEDS";
        description = "Se detecto un error en la \nseccion de control al inicializar el \nequipo";
        lightIndicator = true;
        break;

    case 0xD35D:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "No se puede determinar el \noffset de conmutación";
        lightIndicator = true;
        break;

    case 0xD35E:
        equipment = "EDS";
        category = "HV \nDischarge";
        description = "HV Discharge se activo pero \nvoltaje no ha bajado de 60V en 5 \nsegundos";
        lightIndicator = true;
        break;

    case 0xD35F:
        equipment = "EDS";
        category = "Sección de \npotencia";
        description = "Error interno en la placa \nprincipal de voltaje detectado. \nContactar a soporte tecnico";
        lightIndicator = true;
        break;

    case 0xD360:
        equipment = "EDS";
        category = "Sensor de \nVelocidad";
        description = "Fallo en la calibracion del \noffset de conmutacion";
        lightIndicator = true;
        break;

    case 0xD362:
        equipment = "EDS";
        category = "\nTemperatura";
        description = "El sensor de temperatura del \nrefrigerante leyo bajo del minimo o sobre el \nmaximo";
        lightIndicator = false;
        break;

    case 0xD363:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "Se activo limite de \naceleracion durante la operacion";
        lightIndicator = false;
        break;

    case 0xD364:
        equipment = "EDS";
        category = "Batería LV";
        description = "El voltaje del EDS es muy bajo o \nmuy alto";
        lightIndicator = true;
        break;

    case 0xD365:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "En SafeMotion el umbral de \nvelocidad se excedio";
        lightIndicator = true;
        break;

    case 0xD366:
        equipment = "EDS";
        category = "Modo de \noperación";
        description = "En SafeMotion, la velocidad \nmaxima se excedio";
        lightIndicator = true;
        break;

    case 0xD367:
        equipment = "EDS";
        category = "Firmware";
        description = "El watchdog del EDS se activa. \nReiniciar maquina. Si error persiste \nreemplazar inversor";
        lightIndicator = true;
        break;

    case 0xD368:
        equipment = "EDS";
        category = "SafeMotion";
        description = "Si se parametriza el inversor \ncon proteccion contra reinicio, \nse gatilla este error al sentir \nun punto de start y de reinicio \ncon bajo desfase";
        lightIndicator = false;
        break;

    case 0xD369:
        equipment = "EDS";
        category = "SafeMotion";
        description = "Si se parametrizan entradas \nredundantes, se gatilla este error si no son \niguales";
        lightIndicator = false;
        break;

    case 0xD36A:
        equipment = "EDS";
        category = "Hardware";
        description = "Error de hardware en las \nentradas locales. Reemplazar \ninversor";
        lightIndicator = true;
        break;

    case 0xD36B:
        equipment = "EDS";
        category = "Batería LV";
        description = "Se aplico un voltaje mayor a \n36V en una entrada local. ";
        lightIndicator = true;
        break;

    case 0xD36C:
        equipment = "EDS";
        category = "Batería LV";
        description = "Luego de un sobrevoltaje se \napagan las entradas. Si persiste \nlectura, reemplazar controlador";
        lightIndicator = true;
        break;

    case 0xD36D:
        equipment = "EDS";
        category = "SafeMotion";
        description = "Si estan configurados, la \nsafety technology monitorea si se \npueden cambiar las salidas. Si no se \npuede se gatilla este error";
        lightIndicator = true;
        break;

    case 0xD36E:
        equipment = "EDS";
        category = "Parada de \nEmergencia";
        description = "Se gatillo parada de \nemergencia";
        lightIndicator = true;
        break;

    case 0xD400:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo de alguna \ncelda es alto";
        lightIndicator = true;
        break;

    case 0xD401:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo de alguna \ncelda es muy alto";
        lightIndicator = true;
        break;

    case 0xD402:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo de alguna \ncelda es extremo";
        lightIndicator = true;
        break;

    case 0xD403:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo de alguna \ncelda es bajo";
        lightIndicator = true;
        break;

    case 0xD404:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo de alguna \ncelda es muy bajo";
        lightIndicator = true;
        break;

    case 0xD405:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo de alguna \ncelda es extremo";
        lightIndicator = true;
        break;

    case 0xD406:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Celda excesivamente \ndescargada";
        lightIndicator = true;
        break;

    case 0xD407:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo del sistema es \nalto";
        lightIndicator = true;
        break;

    case 0xD408:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo del sistema es \nmuy alto";
        lightIndicator = true;
        break;

    case 0xD409:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje máximo del sistema es \nextremo";
        lightIndicator = true;
        break;

    case 0xD40A:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo del sistema es \nbajo";
        lightIndicator = true;
        break;

    case 0xD40B:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo del sistema es \nmuy bajo";
        lightIndicator = true;
        break;

    case 0xD40C:
        equipment = "BESS";
        category = "Voltaje DC \nHV";
        description = "Voltaje mínimo del sistema es \nextremo";
        lightIndicator = true;
        break;

    case 0xD40D:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Temperatura máxima de alguna \ncelda es alta";
        lightIndicator = true;
        break;

    case 0xD40E:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Temperatura máxima de alguna \ncelda es muy alta";
        lightIndicator = true;
        break;

    case 0xD40F:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Temperatura máximo de alguna \ncelda es extrema";
        lightIndicator = true;
        break;

    case 0xD410:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Temperatura mínima de alguna \ncelda es muy baja";
        lightIndicator = true;
        break;

    case 0xD411:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Diferencia de temperatura \nentre celdas es alta";
        lightIndicator = true;
        break;

    case 0xD412:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Diferencia de temperatura \nentre celdas es muy alta";
        lightIndicator = true;
        break;

    case 0xD413:
        equipment = "BESS";
        category = "\nTemperatura";
        description = "Diferencia de temperatura \nentre celdas es extrema";
        lightIndicator = true;
        break;

    case 0xD414:
        equipment = "BESS";
        category = "Incendio";
        description = "Evento de incendio";
        lightIndicator = true;
        break;

    case 0xD415:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \ndescarga es alta";
        lightIndicator = true;
        break;

    case 0xD416:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \ndescarga es muy alta";
        lightIndicator = true;
        break;

    case 0xD417:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \ndescarga es extrema";
        lightIndicator = true;
        break;

    case 0xD418:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \nrescarga es alta";
        lightIndicator = true;
        break;

    case 0xD419:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \nrescarga es muy alta";
        lightIndicator = true;
        break;

    case 0xD41A:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Sobrecorriente en pulso de \nrescarga es extrema";
        lightIndicator = true;
        break;

    case 0xD41B:
        equipment = "BESS";
        category = "Sensor";
        description = "Falla en sensor de corriente";
        lightIndicator = true;
        break;

    case 0xD41C:
        equipment = "BESS";
        category = "Voltaje DC \nLV";
        description = "Voltaje de alimentación LV \nfuera de rango";
        lightIndicator = true;
        break;

    case 0xD41D:
        equipment = "BESS";
        category = "SOC";
        description = "Diferencia de SOC entre \nceldas es muy grande";
        lightIndicator = true;
        break;

    case 0xD41E:
        equipment = "BESS";
        category = "SOC";
        description = "Salto repentino de SOC";
        lightIndicator = true;
        break;

    case 0xD41F:
        equipment = "BESS";
        category = "SOC";
        description = "El nivel de SOC es bajo";
        lightIndicator = true;
        break;

    case 0xD420:
        equipment = "BESS";
        category = "SOC";
        description = "El nivel de SOC es muy bajo";
        lightIndicator = true;
        break;

    case 0xD421:
        equipment = "BESS";
        category = "SOC";
        description = "El nivel de SOC es \nextremadamente bajo";
        lightIndicator = true;
        break;

    case 0xD422:
        equipment = "BESS";
        category = "BTMS";
        description = "Falla en el BTMS";
        lightIndicator = true;
        break;

    case 0xD423:
        equipment = "BESS";
        category = "TMS";
        description = "Falla en el circuito de \ncalentamiento";
        lightIndicator = true;
        break;

    case 0xD424:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Alarma de autoprotección a \nalguna condición extrema";
        lightIndicator = true;
        break;

    case 0xD425:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Falla en el circuito \nprincipal de precarga";
        lightIndicator = true;
        break;

    case 0xD426:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Falla en el circuito auxiliar \nde precarga";
        lightIndicator = true;
        break;

    case 0xD427:
        equipment = "BESS";
        category = "Aislación";
        description = "Nivel de aislación baja";
        lightIndicator = true;
        break;

    case 0xD428:
        equipment = "BESS";
        category = "Aislación";
        description = "Nivel de aislación muy baja";
        lightIndicator = true;
        break;

    case 0xD429:
        equipment = "BESS";
        category = "Aislación";
        description = "Nivel de aislación \nextremadamente baja";
        lightIndicator = true;
        break;

    case 0xD42A:
        equipment = "BESS";
        category = "Aislación";
        description = "Nivel de aislación baja \ndurante carga ";
        lightIndicator = true;
        break;

    case 0xD42B:
        equipment = "BESS";
        category = "Comm";
        description = "Comunicación CAN perdida";
        lightIndicator = true;
        break;

    case 0xD42C:
        equipment = "BESS";
        category = "Comm";
        description = "Falla en la comunicación \ninterna del BMS";
        lightIndicator = true;
        break;

    case 0xD42D:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Falla en el DCDC del BMS";
        lightIndicator = true;
        break;

    case 0xD42E:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Rama desconectada";
        lightIndicator = true;
        break;

    case 0xD42F:
        equipment = "BESS";
        category = "HVIL";
        description = "Falla de HVIL";
        lightIndicator = true;
        break;

    case 0xD430:
        equipment = "BESS";
        category = "TMS";
        description = "Relé de calentamiento o TMS no \nse puede cerrar";
        lightIndicator = true;
        break;

    case 0xD431:
        equipment = "BESS";
        category = "TMS";
        description = "Relé de calentamiento o TMS no \nse puede abrir";
        lightIndicator = true;
        break;

    case 0xD432:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor principal \npositivo no se puede cerrar";
        lightIndicator = true;
        break;

    case 0xD433:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor principal \npositivo no se puede abrir";
        lightIndicator = true;
        break;

    case 0xD434:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor principal \nnegativo no se puede cerrar";
        lightIndicator = true;
        break;

    case 0xD435:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor principal \nnegativo no se puede abrir";
        lightIndicator = true;
        break;

    case 0xD436:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC A \npositivo no se puede cerrar";
        lightIndicator = true;
        break;

    case 0xD437:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC A \npositivo no se puede abrir";
        lightIndicator = true;
        break;

    case 0xD438:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC A \nnegativo no se puede cerrar";
        lightIndicator = true;
        break;

    case 0xD439:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC A \nnegativo no se puede abrir";
        lightIndicator = true;
        break;

    case 0xD43A:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC B \npositivo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD43B:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC B \npositivo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD43C:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC B \nnegativo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD43D:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga DC B \nnegativo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD43E:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga AC \npositivo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD43F:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga AC \npositivo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD440:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga AC \nnegativo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD441:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga AC \nnegativo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD442:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga de \npantógrafo positivo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD443:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga de \npantógrafo positivo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD444:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga de \npantógrafo negativo no se puede cerrar";
        lightIndicator = false;
        break;

    case 0xD445:
        equipment = "BESS";
        category = "Relé / \nContactor";
        description = "Contactor de carga de \npantógrafo negativo no se puede abrir";
        lightIndicator = false;
        break;

    case 0xD446:
        equipment = "BESS";
        category = "Pistola / \nenchufe de carga";
        description = "Conexión de la pistola de \ncarga anormal";
        lightIndicator = true;
        break;

    case 0xD447:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Incompatibilidad en el \nsistema BMS";
        lightIndicator = false;
        break;

    case 0xD448:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente de descarga \ndemasiado alta durante proceso de carga";
        lightIndicator = true;
        break;

    case 0xD449:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente de carga demasiado \nalta";
        lightIndicator = true;
        break;

    case 0xD44A:
        equipment = "BESS";
        category = "Pistola / \nenchufe de carga";
        description = "Falla en el enchufe de carga: \nNTC";
        lightIndicator = true;
        break;

    case 0xD44B:
        equipment = "BESS";
        category = "Pistola / \nenchufe de carga";
        description = "Falla en el enchufe de carga: \nTemperatura alta";
        lightIndicator = false;
        break;

    case 0xD44C:
        equipment = "BESS";
        category = "Pistola / \nenchufe de carga";
        description = "Falla en el enchufe de carga: \nTemperatura alta";
        lightIndicator = true;
        break;

    case 0xD44D:
        equipment = "BESS";
        category = "Pistola / \nenchufe de carga";
        description = "Falla en el bloqueo \nelectrónico del enchufe";
        lightIndicator = true;
        break;

    case 0xD44E:
        equipment = "BESS";
        category = "Sensor";
        description = "Falla en el detector o alarma \nde incendios";
        lightIndicator = true;
        break;

    case 0xD44F:
        equipment = "BESS";
        category = "Sistema \nBESS";
        description = "Consistencia de celdas es \npobre";
        lightIndicator = true;
        break;

    case 0xD450:
        equipment = "BESS";
        category = "SOC";
        description = "SOC es muy alto";
        lightIndicator = true;
        break;

    case 0xD451:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \nrecarga es alta";
        lightIndicator = true;
        break;

    case 0xD452:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \nrecarga es muy alta";
        lightIndicator = true;
        break;

    case 0xD453:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \nrecarga es extremadamente alta";
        lightIndicator = true;
        break;

    case 0xD454:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \ndescarga es alta";
        lightIndicator = true;
        break;

    case 0xD455:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \ndescarga es muy alta";
        lightIndicator = true;
        break;

    case 0xD456:
        equipment = "BESS";
        category = "\nSobrecorriente";
        description = "Corriente continua de \ndescarga es extremadamente alta";
        lightIndicator = true;
        break;

    case 0xD500:
        equipment = "BTMS";
        category = "Comm";
        description = "Comunicación CAN perdida";
        lightIndicator = true;
        break;

    case 0xD501:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error gravísimo del PTC 1";
        lightIndicator = false;
        break;

    case 0xD502:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error gravísimo del PTC 2";
        lightIndicator = false;
        break;

    case 0xD503:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error gravísimo del PTC 3";
        lightIndicator = false;
        break;

    case 0xD504:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error gravísimo del PTC 4";
        lightIndicator = false;
        break;

    case 0xD505:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error del PTC 1";
        lightIndicator = false;
        break;

    case 0xD506:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error del PTC 2";
        lightIndicator = false;
        break;

    case 0xD507:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error del PTC 3";
        lightIndicator = false;
        break;

    case 0xD508:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error del PTC 4";
        lightIndicator = false;
        break;

    case 0xD509:
        equipment = "BTMS";
        category = "BTMS";
        description = "Múltiples razones. \nSobrevoltaje, sobrecorriente, error de \nprecarga dle compresor, falla del \ncontrolador";
        lightIndicator = false;
        break;

    case 0xD50A:
        equipment = "BTMS";
        category = "BTMS";
        description = "Error en el ventilador de \ncondensación: circuito abierto o corto \ncircuito";
        lightIndicator = false;
        break;

    case 0xD50B:
        equipment = "BTMS";
        category = "BTMS";
        description = "Presión en el compresor es muy \nalta o muy baja o sensor de presión \nbaja está cortocircuitado o \nabierto o presión del sistema muy alta";
        lightIndicator = false;
        break;

    case 0xD50C:
        equipment = "BTMS";
        category = "BTMS";
        description = "Presión en el compresor es muy \nalta o muy baja o sensor de presión \nbaja está cortocircuitado o \nabierto o presión del sistema muy baja";
        lightIndicator = false;
        break;

    case 0xD50D:
        equipment = "BTMS";
        category = "Sensor de \nTemperatura";
        description = "Sensor de temperatura de \nentrada de refrigerante en error: \ncorto circuito o circuito abierto.";
        lightIndicator = false;
        break;

    case 0xD50E:
        equipment = "BTMS";
        category = "Sensor de \nTemperatura";
        description = "Sensor de temperatura de \nsalida de refrigerante en error: \ncorto circuito o circuito abierto.";
        lightIndicator = false;
        break;

    case 0xD50F:
        equipment = "BTMS";
        category = "Bomba de \nagua";
        description = "La bomba de agua no está \nconectada, tiene sobrecorriente, \nsobrevoltaje o corto circuito.";
        lightIndicator = false;
        break;

    case 0xD510:
        equipment = "BTMS";
        category = "Sensor";
        description = "Sensor de nivel de líquido en \nerror. Cortocircuitado o circuito \nabierto";
        lightIndicator = false;
        break;

    case 0xD511:
        equipment = "BTMS";
        category = "Sensor";
        description = "Sensor de salida PTC de \nlíquido en error. Cortocircuitado o \ncircuito abierto";
        lightIndicator = false;
        break;

    case 0xD512:
        equipment = "BTMS";
        category = "Precarga";
        description = "Error grave en sistema de \nprecarga de alto voltaje";
        lightIndicator = false;
        break;

    case 0xD513:
        equipment = "BTMS";
        category = "Relé / \nContactor";
        description = "Error grave en el relé K2 del \nBTMS";
        lightIndicator = false;
        break;

    case 0xD514:
        equipment = "BTMS";
        category = "DCDC";
        description = "Error grave en el DCDC del BTMS";
        lightIndicator = false;
        break;

    case 0xD515:
        equipment = "BTMS";
        category = "BTMS";
        description = "Módulo 1 del BTMS tiene nivel 1 \nde error (el más grave)";
        lightIndicator = false;
        break;

    case 0xD516:
        equipment = "BTMS";
        category = "BTMS";
        description = "Módulo 1 del BTMS tiene nivel 2 \nde error ";
        lightIndicator = false;
        break;

    case 0xD517:
        equipment = "BTMS";
        category = "Comm";
        description = "Módulo 1 del BTMS perdió \ncomunicación";
        lightIndicator = false;
        break;

    case 0xD518:
        equipment = "BTMS";
        category = "BTMS";
        description = "Módulo 2 del BTMS tiene nivel 2 \nde error ";
        lightIndicator = false;
        break;

    case 0xD519:
        equipment = "BTMS";
        category = "Comm";
        description = "Módulo 2 del BTMS perdió \ncomunicación";
        lightIndicator = false;
        break;

    case 0xD51A:
        equipment = "BTMS";
        category = "Comm";
        description = "Módulo 2 del TMS perdió \ncomunicación";
        lightIndicator = false;
        break;

    case 0xD51B:
        equipment = "BTMS";
        category = "Voltaje DC \nLV";
        description = "Voltaje LV de alimentación \nmenor a 18V o mayor a 32V";
        lightIndicator = false;
        break;

    case 0xD51C:
        equipment = "BTMS";
        category = "Relé / \nContactor";
        description = "Contactor del circuito de \nalto voltaje \"pegado\"";
        lightIndicator = false;
        break;

    case 0xD51D:
        equipment = "BTMS";
        category = "Sensor";
        description = "Error en el sensor de salida de \naire: circuito abierto o corto \ncircuito.";
        lightIndicator = false;
        break;

    case 0xD51E:
        equipment = "BTMS";
        category = "DCDC";
        description = "Error en el DCDC del BTMS";
        lightIndicator = false;
        break;

    case 0xD600:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "Temperatura en la PDU es alta";
        lightIndicator = true;
        break;

    case 0xD601:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "Temperatura en la PDU es muy \nalta";
        lightIndicator = true;
        break;

    case 0xD602:
        equipment = "EMIX";
        category = "HVIL";
        description = "Anormalidad detectada en \ncircuito HVIL de los DCDC";
        lightIndicator = true;
        break;

    case 0xD603:
        equipment = "EMIX";
        category = "HVIL";
        description = "Anormalidad detectada en \ncircuito HVIL del EDS";
        lightIndicator = true;
        break;

    case 0xD604:
        equipment = "EMIX";
        category = "HVIL";
        description = "Anormalidad detectada en \ncircuito HVIL del OBC";
        lightIndicator = true;
        break;

    case 0xD605:
        equipment = "EMIX";
        category = "HVIL";
        description = "Anormalidad detectada en \ncircuito HVIL de la PDU";
        lightIndicator = true;
        break;

    case 0xD606:
        equipment = "EMIX";
        category = "Hardware";
        description = "RC lleva más de 24 horas \nencendido";
        lightIndicator = false;
        break;

    case 0xD607:
        equipment = "EMIX";
        category = "Sensor";
        description = "Inconsistencia en señal 1 del \npedal del acelerador detectada";
        lightIndicator = true;
        break;

    case 0xD608:
        equipment = "EMIX";
        category = "Sensor";
        description = "Inconsistencia en señal 2 del \npedal del acelerador detectada";
        lightIndicator = true;
        break;

    case 0xD609:
        equipment = "EMIX";
        category = "Sensor";
        description = "Señal inconsistente sensor \nde inclinación 1";
        lightIndicator = true;
        break;

    case 0xD60A:
        equipment = "EMIX";
        category = "Sensor";
        description = "Señal inconsistente sensor \nde inclinación 2";
        lightIndicator = true;
        break;

    case 0xD60B:
        equipment = "EMIX";
        category = "Sensor";
        description = "Volcamiento detectado";
        lightIndicator = true;
        break;

    case 0xD60C:
        equipment = "EMIX";
        category = "Puerta de \nbanco/capó abierta";
        description = "La puerta del capó está \nabierta";
        lightIndicator = true;
        break;

    case 0xD60D:
        equipment = "EMIX";
        category = "Input";
        description = "Estado de la llave actual es \nprohibido (HV High y Motor ON High)";
        lightIndicator = false;
        break;

    case 0xD60E:
        equipment = "EMIX";
        category = "Parada de \nEmergencia";
        description = "Parada de emergencia \nactivada";
        lightIndicator = true;
        break;

    case 0xD60F:
        equipment = "EMIX";
        category = "Flags";
        description = "HV Off is Needed seteada en \nTRUE ";
        lightIndicator = false;
        break;

    case 0xD610:
        equipment = "EMIX";
        category = "Flags";
        description = "Flag de derateo activada: \nTemperatura de equipo mayor a 60°C";
        lightIndicator = false;
        break;

    case 0xD611:
        equipment = "EMIX";
        category = "BMS";
        description = "BESS solicitó apagar el alto \nvoltaje";
        lightIndicator = true;
        break;

    case 0xD612:
        equipment = "EMIX";
        category = "Voltaje DC \nLV";
        description = "Voltaje DC LV alto (>= 30 V)";
        lightIndicator = true;
        break;

    case 0xD613:
        equipment = "EMIX";
        category = "Voltaje DC \nLV";
        description = "Voltaje DC LV muy alto (>=31,5 \nV)";
        lightIndicator = true;
        break;

    case 0xD614:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "OBC en exceso de temperatura";
        lightIndicator = true;
        break;

    case 0xD615:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "EDS en exceso de temperatura";
        lightIndicator = true;
        break;

    case 0xD616:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "DCDC1 en exceso de \ntemperatura";
        lightIndicator = true;
        break;

    case 0xD617:
        equipment = "EMIX";
        category = "\nTemperatura";
        description = "DCDC2 en exceso de \ntemperatura";
        lightIndicator = true;
        break;

    case 0xD618:
        equipment = "EMIX";
        category = "Bomba ATS";
        description = "Fault output de la bomba del \nATS en estado de falla";
        lightIndicator = true;
        break;

    case 0xD619:
        equipment = "EMIX";
        category = "Ventilador \nATS";
        description = "Fault output del ventilador \ndel ATS en estado de falla";
        lightIndicator = true;
        break;

    case 0xD61A:
        equipment = "EMIX";
        category = "EDS";
        description = "Inversor en estado de falla";
        lightIndicator = true;
        break;

    case 0xD61B:
        equipment = "EMIX";
        category = "EDS";
        description = "Inversor no ha podido limpiar \nsu estado de falla";
        lightIndicator = true;
        break;

    case 0xD61C:
        equipment = "EMIX";
        category = "Input";
        description = "Luego de mandar la llave a \nshutdown, cambió de posición a otra \nantes de apagar (transición \nprohibida)";
        lightIndicator = true;
        break;

    case 0xD61D:
        equipment = "EMIX";
        category = "DCDC";
        description = "Diferencia de potencia \nsuministrada entre DCDC1 y DCDC2 muy grande";
        lightIndicator = false;
        break;

    case 0xD61E:
        equipment = "EMIX";
        category = "Incendio";
        description = "Código de error de BESS \ncorresponde a incendio";
        lightIndicator = true;
        break;

    case 0xD61F:
        equipment = "EMIX";
        category = "Incendio";
        description = "Código de estatus de BESS \ncorresponde a incendio";
        lightIndicator = true;
        break;

    case 0xD620:
        equipment = "EMIX";
        category = "Incendio";
        description = "Temperatura del módulo 1  \ngrande";
        lightIndicator = false;
        break;

    case 0xD621:
        equipment = "EMIX";
        category = "Incendio";
        description = "Temperatura del módulo 2  \ngrande";
        lightIndicator = false;
        break;

    case 0xD622:
        equipment = "EMIX";
        category = "Incendio";
        description = "Temperatura del módulo 3  \ngrande";
        lightIndicator = false;
        break;

    case 0xD623:
        equipment = "EMIX";
        category = "Incendio";
        description = "Temperatura del módulo 4  \ngrande";
        lightIndicator = false;
        break;

    case 0xD624:
        equipment = "EMIX";
        category = "\nSobrecorriente";
        description = "Corriente consumida \ninversor + refrigeración en HV supera \nlímite actual";
        lightIndicator = true;
        break;

    case 0xD625:
        equipment = "EMIX";
        category = "Transición \nde estado";
        description = "Se intentó pasar a MOTOR_ON \ncon un nivel de falla 6 \n(transición prohibida)";
        lightIndicator = false;
        break;

    case 0xD626:
        equipment = "EMIX";
        category = "Carga AC";
        description = "OBC cargando y batería está \ncompletamente cargada";
        lightIndicator = true;
        break;

    case 0xD627:
        equipment = "EMIX";
        category = "Operación";
        description = "Operador no está en cabina";
        lightIndicator = false;
        break;

    case 0xD628:
        equipment = "EMIX";
        category = "Relé / \nContactor";
        description = "Contactor PDU no cambió su \nestado";
        lightIndicator = true;
        break;

    case 0xD629:
        equipment = "EMIX";
        category = "Relé / \nContactor";
        description = "Contactor PDU - no cambió su \nestado";
        lightIndicator = false;
        break;

    case 0xD62A:
        equipment = "EMIX";
        category = "SOC";
        description = "SOC bajo";
        lightIndicator = true;
        break;

    case 0xD62B:
        equipment = "EMIX";
        category = "Aislación";
        description = "Sensor de aislacion ha \narrojado muchas veces que no tiene \nmedidas nuevas o que hay una alta \nincertidumbre";
        lightIndicator = true;
        break;

    case 0xD62C:
        equipment = "EMIX";
        category = "Aislación";
        description = "Monitoreo de aislación de \nbaterías y SIM100 desactivada";
        lightIndicator = true;
        break;

    case 0xD62D:
        equipment = "EMIX";
        category = "Modo de \noperación";
        description = "BMS dejó de transmitir con el \nIGN encendido";
        lightIndicator = true;
        break;

    case 0xD62E:
        equipment = "EMIX";
        category = "Modo de \noperación";
        description = "BMS no se pudo reencender con \nreacción D62D";
        lightIndicator = true;
        break;

    case 0xD62F:
        equipment = "EMIX";
        category = "Sensor de \nTemperatura";
        description = "Termistor LV de la PDU \ndesconectado o fuera de rango";
        lightIndicator = true;
        break;

    case 0xD630:
        equipment = "EMIX";
        category = "Sensor de \nTemperatura";
        description = "Termistor HV de la PDU \ndesconectado o fuera de rango";
        lightIndicator = true;
        break;


    default:
        break;
    }

    return DTCCanError(
        id,
        category,
        equipment,
        description,
        date,
        lightIndicator
    );
}
