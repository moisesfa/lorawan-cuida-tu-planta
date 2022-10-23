#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
// Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

#include "CubeCell_NeoPixel.h"
CubeCell_NeoPixel pixels(1, RGB, NEO_GRB + NEO_KHZ800);
uint8_t i=0;


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW); //set vext to high
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  
  delay(500);
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;
  
  // Calibrating soil moisture sensor
  // Adc values range 16 bits 0-65535 unsigned o −32768-32767 signed.
  // Adc value dry = 15400
  // Adc value wet = 7100

  int8_t percentHum0, percentHum1, percentHum2, percentHum3;

  float volts0, volts1, volts2, volts3;

  /* Be sure to update this value based on the IC and the gain settings! */
  //float   multiplier = 3.0F;    /* ADS1015 @ +/- 6.144V gain (12-bit results) */
  //float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);
  
  // Calibrating soil moisture sensor
  // Adc values range 16 bits 0-65535 unsigned o −32768-32767 signed.
  // Adc value dry = 15400
  // Adc value wet = 7100
  // Map
  //sensorValue = map(sensorvalue,valuedry,valuewet,0,100)
  percentHum0 = map(adc0, 15400,7100,0,100);

  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("Vols0: "); Serial.println(volts0);
  Serial.print("Percent Humidity: "); Serial.print(percentHum0); Serial.println(" %");
  Serial.println(" ");
  
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("Volts1: "); Serial.println(volts1);
  Serial.println(" ");
  
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("Volts2: "); Serial.println(volts2);
  Serial.println(" ");

  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.print("Volts3: "); Serial.println(volts3);
  Serial.println(" ");
  
  pixels.setPixelColor(0, pixels.Color(i, 0, i));
  pixels.show();   // Send the updated pixel colors to the hardware.

  delay(1000);

  i+=10;
  if (i>100) i =0;

}