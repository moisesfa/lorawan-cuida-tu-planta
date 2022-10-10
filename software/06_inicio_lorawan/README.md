# inicio_lorawan
 
Este programa esta en los ejemplos de la documentación [LoRaWAN de cubecell](https://github.com/HelTecAutomation/CubeCell-Arduino/tree/master/libraries/LoRa/examples/LoRaWAN/). Permite enviar y recibir datos a través de LoRaWAN con solo cambiar esta parte del código por las appEui[], devEui[] y appKey[] de su nodo final:

````
/* OTAA para*/
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your appEui
uint8_t devEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your devEui
uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // your appKey
````

![](/software/docs/Result_lorawan.PNG)

![](/software/docs/Result_lorawan_tts.PNG)