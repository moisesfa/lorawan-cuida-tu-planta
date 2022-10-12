#include <Arduino.h>

// I2C
#include <Wire.h>

// Handle led rgb
#include "CubeCell_NeoPixel.h"
// Sensor BME280
#include "Seeed_BME280.h"
// Sensor BH1750
#include <BH1750.h>
// Converter ADS1115
#include <Adafruit_ADS1X15.h>

// Objects 
CubeCell_NeoPixel pixels(1, RGB, NEO_GRB + NEO_KHZ800);
BME280 bme280;
BH1750 lightMeter;
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
   
// Variables sensor BME280
float pressure, temperature, humidity;
// Variables sensor BH1750
float lux;
// Variables sensors ads1115
int16_t adc0, adc1, adc2, adc3;


// Variables to change the color of the led
int r = 0,g = 0,b = 0;

// function declaration
void changeColorRGB (void);
void readSensorBME280(void);
void readSensorBH1750(void);
void readSensorAds1115(void);


void setup() {
  // put your setup code here, to run once:
   pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  
  delay(500);

  // Sensor BME280
  Serial.begin(115200);
  if(!bme280.init()){
    Serial.println("Device error!");
  }

  // Sensor BH1750
  lightMeter.begin();
  Serial.println(F("BH1750 begin"));

  ads.begin();
  Serial.println(F("ADS1115 begin"));

}


void loop() {
  // put your main code here, to run repeatedly:

  readSensorBME280();
  readSensorBH1750();
  readSensorAds1115();

  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();   // Send the updated pixel colors to the hardware.
  
  delay(1000);
  changeColorRGB();

}

void changeColorRGB (void){
  r = random(0,255);
  g = random(0,255);
  b = random(0,255);
}

void readSensorBME280(void){

  temperature = bme280.getTemperature();
  humidity = bme280.getHumidity();
  pressure = bme280.getPressure();
  
  //print temperature data
  Serial.print("Temp: ");
  Serial.print(temperature);
  
  //print humidity data
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  
  //print atmospheric pressure data
  Serial.print(" Pressure: ");
  Serial.print(pressure);
  
  //print altitude data
  Serial.print(" Altitude: ");
  Serial.println(bme280.calcAltitude(pressure));
  
}

void readSensorBH1750(void){
  
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

}

void readSensorAds1115(void){
  /* Be sure to update this value based on the IC and the gain settings! */
  //float   multiplier = 3.0F;    /* ADS1015 @ +/- 6.144V gain (12-bit results) */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.print(adc0 * multiplier);
  Serial.print(" AIN1: "); Serial.print(adc1 * multiplier);
  Serial.print(" AIN2: "); Serial.print(adc2 * multiplier);
  Serial.print(" AIN3: "); Serial.print(adc3 * multiplier);
  Serial.println(" ");

}