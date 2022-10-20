# inicio_ads1115
 
Este programa lee los valores de un sensor analógico que será un sensor de humedad del suelo, usando el programa alojado en la [documentación de cubecell](https://github.com/HelTecAutomation/CubeCell-Arduino/blob/master/libraries/Sensor_ThirdParty/examples/ADS1X15/singleended/singleended.ino) y adaptado para [PlatformIO](https://platformio.org/). Funciona con la librería de [Adafruit_ADS1x15](https://github.com/adafruit/Adafruit_ADS1X15). Yo solamente le he añadido un poco de color con el RGB de la placa. 

La conexión eléctrica es muy simple: 

| CubeCell | Ads1115 |
| -- | -- |
| VEXT | VDD |
| GND | GND |
| SCL | SCL |
| SDA | SDA |
  
En A0, A1, A2, A3 se conectan las señales analógicas de los sensores de humedad de suelo.

![](/software/docs/20221008_ads1115.jpg)

![](/software/docs/Result_ads1115.PNG)