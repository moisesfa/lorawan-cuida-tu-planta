# inicio_bme280

Este programa lee los valores de un sensor BME280 usando la librería [Grove_BME280 de Seeedstudo](https://github.com/Seeed-Studio/Grove_BME280) alojado en la [documentación de cubecell](https://github.com/HelTecAutomation/CubeCell-Arduino/blob/master/libraries/Sensor_ThirdParty/examples/BME280/bme280_example/bme280_example.ino) y adaptado para [PlatformIO](https://platformio.org/). Yo solamente le he añadido un poco de color con el RGB de la placa.

La conexión eléctrica es muy simple: 

| CubeCell | Bme280 |
| -- | -- |
| VEXT | VIN |
| GND | GND |
| SCL | SCL |
| SDA | SDA |

![](/software/docs/20221008_bme280.jpg)

![](/software/docs/Result_bme280.PNG)