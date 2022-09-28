# LoRaWAN Cuida Tus Plantas

Pretendo desarrollar un nodo LoRaWAN para monitorizar las condiciones ambientales en las que crece una planta.

El cerebro será la placa de desarrollo [CubeCell](https://heltec.org/project/htcc-ab01/) del fabricante [Heltec Automation](https://heltec.org/). La placa, a día de hoy no se recomienda para diseños nuevos, algo que carece de importancia en este proyecto que pretende ser meramente educativo. También, pueden ser interesantes las modificaciones a la nueva versión en un futuro.

Se ha diseñado un circuito impreso para alimentar el circuito con una batería 18650 y poder conectar fácilmente los sensores i2c a usar. Vea la documentación [aquí](/hardware/README.md)

Temperatura, Humedad, Presión Atmosférica se obtendran con el sensor [BME280](https://www.luisllamas.es/sensor-ambiental-arduino-bme280/)

Para el nivel de luz, un sensor digital [BH1750](https://www.luisllamas.es/medir-cantidad-de-luxes-con-arduino-y-el-luxometro-bh1750/)

El sensor de humedad del suelo será un [higrómetro capacitivo](https://www.luisllamas.es/sensor-de-humedad-del-suelo-capacitivo-y-arduino/) para el que necesitaremos un conversor analógico digital (ADC) como el [ADS1115](https://www.luisllamas.es/entrada-analogica-adc-de-16-bits-con-arduino-y-ads1115/) ya que la CubeCell no dispone de entradas analógicas libres. Esto también nos dará la posibilidad de conectar hasta 4 sensores de humedad de suelo. 