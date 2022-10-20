# inicio_bh1750
 
Este programa lee los valores de un sensor BH1750 usando el programa alojado en la [documentación de cubecell](https://github.com/HelTecAutomation/CubeCell-Arduino/blob/master/libraries/SensorBasic/examples/BH1750/BH1750test/BH1750test.ino) y adaptado para [PlatformIO](https://platformio.org/). No es neceario añadir ninguna libreria. Yo solamente le he añadido un poco de color con el RGB de la placa.

La conexión eléctrica es muy simple: 

| CubeCell | Bh1750 |
| -- | -- |
| VEXT | VDD |
| GND | GND |
| SCL | SCL |
| SDA | SDA |


![](/software/docs/20221008_bh1750.jpg)

![](/software/docs/Result_bh1750.PNG)