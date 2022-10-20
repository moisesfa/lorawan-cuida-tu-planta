# LoRaWAN Cuida Tu Planta

Pretendo desarrollar un nodo LoRaWAN para monitorizar las condiciones ambientales en las que crece una planta.

El cerebro será la placa de desarrollo [CubeCell](https://heltec.org/project/htcc-ab01/) del fabricante [Heltec Automation](https://heltec.org/). La placa a día de hoy (Septiembre de 20022), no se recomienda para diseños nuevos y le han puesto la etiqueta Phaseout. El fabricante recomienda una CubeCell-Dev-Board (V2) de la que todavía no hay documentación. Esto carece de importancia en este proyecto que pretende ser meramente educativo. También, pueden ser interesantes las modificaciones a la nueva versión en un futuro.
En Octubre de 2022 ya hay documentación de la versión 2 de la [CubeCell-Dev-Board](https://heltec.org/project/htcc-ab01-v2/). A falta de pruebas, parece que va a ser compatible con la placa diseñada.  

Se ha diseñado un circuito impreso para alimentar el circuito con una batería 18650 y poder conectar fácilmente los sensores i2c a usar. Vea la documentación [aquí](/hardware/README.md)

Temperatura, Humedad, Presión Atmosférica se obtendran con el sensor [BME280](https://www.luisllamas.es/sensor-ambiental-arduino-bme280/)

Para el nivel de luz, un sensor digital [BH1750](https://www.luisllamas.es/medir-cantidad-de-luxes-con-arduino-y-el-luxometro-bh1750/)

El sensor de humedad del suelo será un [higrómetro capacitivo](https://www.luisllamas.es/sensor-de-humedad-del-suelo-capacitivo-y-arduino/) para el que necesitaremos un conversor analógico digital (ADC) como el [ADS1115](https://www.luisllamas.es/entrada-analogica-adc-de-16-bits-con-arduino-y-ads1115/) ya que la CubeCell no dispone de entradas analógicas libres. Esto también nos dará la posibilidad de conectar hasta 4 sensores de humedad de suelo. 

![](/software/docs/Cuitupla.drawio2.png)

## Fases del proyecto 

- Lectura de los sensores con el puerto serie.
    - [BME280](/software/02_inicio_bme280/README.md)
    - [BH1750](/software/03_inicio_bh1750/README.md)
    - [Conversor analógico-digital para humedad del suelo](/software/04_inicio_ads1115/README.md)
    - [Lectura de todos los sensores](/software/05_sensores_todos/README.md)

- Envio de datos LoRaWAN
    - [Inicio con LoRaWAN](/software/06_inicio_lorawan/README.md)
    - [Lectura de los sensores a LoRaWAN](/software/07_sensores_lorawan/README.md)

## Resultado final

Para proteger el sensor de humedad del suelo he seguido estas [instrucciones](https://www.instructables.com/Waterproofing-a-Capacitance-Soil-Moisture-Sensor/)

El sensor de luminosidad se ha usado en este [formato de bola](https://a.aliexpress.com/_ExYB4vB) para una mejor colocación.

TODO: Foto Final