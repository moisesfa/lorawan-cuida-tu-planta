# sensores_lorawan
 
Este programa lee los todos los sensores y envía la información a LoRaWAN con solo cambiar esta parte del código por las appEui[], devEui[] y appKey[] de su nodo final:

````
/* OTAA para*/
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your appEui
uint8_t devEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your devEui
uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your appKey
````

Practicamente todo se basa en la [documentación de Heltec Automation](https://github.com/HelTecAutomation/CubeCell-Arduino/tree/master/libraries/LoRa/examples/LoRaWAN).

El ciclo de trabajo de la aplicación es el siguiente:

1. Se une con la aplicación LoRaWAN.
2. Lee y envía los datos a LoRaWAN.
3. Se duerme durante un tiempo appTxDutyCycle = 30 * 1000; (30 segundos para pruebas).
4. Se despierta, lee los sensores y vuelve a enviar los datos.
5. Los pasos 3 y 4 se repiten hasta que la batería se agota o se resetea el dispositivo.


Ejemplo en The Things Stack: 

![Ejemplo en The Things Stack](/software/docs/Result_lorawan_tts_sensores.PNG)
