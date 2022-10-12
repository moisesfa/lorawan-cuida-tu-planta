#include <Arduino.h>
#include "LoRaWan_APP.h"

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
BME280 bme280;
BH1750 lightMeter;
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */

// Variables
uint16_t BatteryVoltage;
int16_t int_temp_bme280;
uint16_t int_humi_bme280;
uint16_t int_pres_bme280;
uint16_t int_alti_bme280;

// Variables sensor BH1750
uint16_t int_lux_bh1750;
// Variables sensors ads1115
int16_t int_adc0, int_adc1, int_adc2, int_adc3;

/*
 * set LoraWan_RGB to Active,the RGB active in loraWan
 * RGB red means sending;
 * RGB purple means joined done;
 * RGB blue means RxWindow1;
 * RGB yellow means RxWindow2;
 * RGB green means received done;
 */

/* OTAA para*/
uint8_t appEui[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};												 // your appEui
uint8_t devEui[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};												 // your devEui
uint8_t appKey[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // your appKey

/* ABP para*/
uint8_t nwkSKey[] = {0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda, 0x85};
uint8_t appSKey[] = {0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef, 0x67};
uint32_t devAddr = (uint32_t)0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = LORAWAN_CLASS;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 30 * 1000;

/*OTAA or ABP*/
bool overTheAirActivation = LORAWAN_NETMODE;

/*ADR enable*/
bool loraWanAdr = LORAWAN_ADR;

/* set LORAWAN_Net_Reserve ON, the node could save the network info to flash, when node reset not need to join again */
bool keepNet = LORAWAN_NET_RESERVE;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = LORAWAN_UPLINKMODE;

/* Application port */
uint8_t appPort = 2;
/*!
 * Number of trials to transmit the frame, if the LoRaMAC layer did not
 * receive an acknowledgment. The MAC performs a datarate adaptation,
 * according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
 * to the following table:
 *
 * Transmission nb | Data Rate
 * ----------------|-----------
 * 1 (first)       | DR
 * 2               | DR
 * 3               | max(DR-1,0)
 * 4               | max(DR-1,0)
 * 5               | max(DR-2,0)
 * 6               | max(DR-2,0)
 * 7               | max(DR-3,0)
 * 8               | max(DR-3,0)
 *
 * Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
 * the datarate, in case the LoRaMAC layer did not receive an acknowledgment
 */
uint8_t confirmedNbTrials = 4;

// Functions
void readBatteryVoltage()
{
	BatteryVoltage = getBatteryVoltage();
	Serial.println("");
	Serial.print("BatteryVoltage: ");
	Serial.println(BatteryVoltage);
}

void readSensorBME280(void)
{

	// Start bme280
	if (!bme280.init())
	{
		// debug
		Serial.println("Device error!");
	}

	// Read sensor BME280
	Serial.println("");
	Serial.println("DATOS BME280");
	
	float temp_bme280 = bme280.getTemperature(); 
	float humi_bme280 = bme280.getHumidity(); 
	float pres_bme280 = bme280.getPressure();
	float alti_bme280 = bme280.calcAltitude(pres_bme280);

	// get and print temperatures
	Serial.print("Temp: ");
	int_temp_bme280 = temp_bme280 * 100;
	Serial.print(temp_bme280);
	Serial.print(" C => ");
	Serial.print(int_temp_bme280);
	Serial.println(" ttn");

	// get and print humidity data
	Serial.print("Humidity: ");

	int_humi_bme280 = humi_bme280 * 100;
	Serial.print(humi_bme280);
	Serial.print(" % => ");
	Serial.print(int_humi_bme280);
	Serial.println(" ttn");

	// get and print atmospheric pressure data
	Serial.print("Pressure: ");
	int_pres_bme280 = pres_bme280 / 10;
	Serial.print(pres_bme280);
	Serial.print(" Pa => ");
	Serial.print(int_pres_bme280);
	Serial.println(" ttn");

	// get and print altitude data
	Serial.print("Altitude: ");
	int_alti_bme280 = alti_bme280 * 10;
	Serial.print(alti_bme280);
	Serial.print(" m => ");
	Serial.print(int_alti_bme280);
	Serial.println(" ttn");
}

void readSensorBH1750(void)
{

	// Sensor BH1750
	
	if (!lightMeter.begin()) {
    	Serial.println("Failed to initialize lightMeter.");
  	} else {
		Serial.println(F("lightMeter begin"));
	}

	float lux_bh1750 = lightMeter.readLightLevel(); 

	// get and print lux
	Serial.print("Light: ");
	int_lux_bh1750 = lux_bh1750;
	Serial.print(lux_bh1750);
	Serial.print(" lx => ");
	Serial.print(int_lux_bh1750);
	Serial.println(" ttn");

}

void readSensorAds1115(void)
{
	Serial.println("Getting single-ended readings from AIN0..3");
  	Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

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

	if (!ads.begin()) {
    	Serial.println("Failed to initialize ADS.");
  	} else {
		Serial.println(F("ADS1115 begin"));
	}

	/* Be sure to update this value based on the IC and the gain settings! */
	// float   multiplier = 3.0F;    /* ADS1015 @ +/- 6.144V gain (12-bit results) */
	//float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
	float volts0, volts1, volts2, volts3;

	int_adc0 = ads.readADC_SingleEnded(0);
	int_adc1 = ads.readADC_SingleEnded(1);
	int_adc2 = ads.readADC_SingleEnded(2);
	int_adc3 = ads.readADC_SingleEnded(3);

	Serial.print("AIN0: ");
	volts0 = ads.computeVolts(int_adc0);
	Serial.print(volts0);
	Serial.print(" => ");
	Serial.print(int_adc0);
	Serial.println(" ttn");

	Serial.print("AIN1: ");
	volts1 = ads.computeVolts(int_adc1);
	Serial.print(volts1);
	Serial.print(" => ");
	Serial.print(int_adc1);
	Serial.println(" ttn");
	
	Serial.print("AIN2: ");
	volts2 = ads.computeVolts(int_adc2);
	Serial.print(volts2);
	Serial.print(" => ");
	Serial.print(int_adc2);
	Serial.println(" ttn");

	Serial.print("AIN3: ");
	volts3 = ads.computeVolts(int_adc3);
	Serial.print(volts3);
	Serial.print(" => ");
	Serial.print(int_adc3);
	Serial.println(" ttn");

}

void readSensors()
{
	// Vext ON
	pinMode(Vext, OUTPUT);
	digitalWrite(Vext, LOW);
	delay(1000);
	// debug
	Serial.println("");
	Serial.println("Read sensors");

	readSensorBME280();
	readSensorBH1750();
	readSensorAds1115();

	// Necesario para que vuelva a funcionar despues del Sleep
	Wire.end();

	// Vext OFF
	digitalWrite(Vext, HIGH);
}

/* Prepares the payload of the frame */
static void prepareTxFrame(uint8_t port)
{
	/*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
	 *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
	 *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
	 *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
	 *for example, if use REGION_CN470,
	 *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
	 */
	readBatteryVoltage();
	readSensors();

	appDataSize = 20;
	// Battery
	appData[0] = (uint8_t)(BatteryVoltage >> 8);
	appData[1] = (uint8_t)BatteryVoltage;
	// Temperature bme280
	appData[2] = (uint8_t)(int_temp_bme280 >> 8);
	appData[3] = (uint8_t)int_temp_bme280;
	// Humidity bme280
	appData[4] = (uint8_t)(int_humi_bme280 >> 8);
	appData[5] = (uint8_t)int_humi_bme280;
	// Pressure bme280
	appData[6] = (uint8_t)(int_pres_bme280 >> 8);
	appData[7] = (uint8_t)int_pres_bme280;
	// Altitude bme280
	appData[8] = (uint8_t)(int_alti_bme280 >> 8);
	appData[9] = (uint8_t)int_alti_bme280;
	// Lux bh1750
	appData[10] = (uint8_t)(int_lux_bh1750 >> 8);
	appData[11] = (uint8_t)int_lux_bh1750;
	// Ads1115 
	appData[12] = (uint8_t)(int_adc0 >> 8);
	appData[13] = (uint8_t)int_adc0;
	appData[14] = (uint8_t)(int_adc1 >> 8);
	appData[15] = (uint8_t)int_adc1;
	appData[16] = (uint8_t)(int_adc2 >> 8);
	appData[17] = (uint8_t)int_adc2;
	appData[18] = (uint8_t)(int_adc3 >> 8);
	appData[19] = (uint8_t)int_adc3;

	
}

// downlink data handle function example
void downLinkDataHandle(McpsIndication_t *mcpsIndication)
{
	Serial.printf("+REV DATA:%s,RXSIZE %d,PORT %d\r\n", mcpsIndication->RxSlot ? "RXWIN2" : "RXWIN1", mcpsIndication->BufferSize, mcpsIndication->Port);
	Serial.print("+REV DATA:");
	for (uint8_t i = 0; i < mcpsIndication->BufferSize; i++)
	{
		Serial.printf("%02X", mcpsIndication->Buffer[i]);
	}
	Serial.println();
	uint32_t color = mcpsIndication->Buffer[0] << 16 | mcpsIndication->Buffer[1] << 8 | mcpsIndication->Buffer[2];
#if (LoraWan_RGB == 1)
	turnOnRGB(color, 5000);
	turnOffRGB();
#endif
}

void setup()
{
	Serial.begin(115200);
#if (AT_SUPPORT)
	enableAt();
#endif
	deviceState = DEVICE_STATE_INIT;
	LoRaWAN.ifskipjoin();
}

void loop()
{
	switch (deviceState)
	{
	case DEVICE_STATE_INIT:
	{
#if (LORAWAN_DEVEUI_AUTO)
		LoRaWAN.generateDeveuiByChipID();
#endif
#if (AT_SUPPORT)
		getDevParam();
#endif
		printDevParam();
		LoRaWAN.init(loraWanClass, loraWanRegion);
		deviceState = DEVICE_STATE_JOIN;
		break;
	}
	case DEVICE_STATE_JOIN:
	{
		LoRaWAN.join();
		break;
	}
	case DEVICE_STATE_SEND:
	{
		prepareTxFrame(appPort);
		LoRaWAN.send();
		deviceState = DEVICE_STATE_CYCLE;
		break;
	}
	case DEVICE_STATE_CYCLE:
	{
		// Schedule next packet transmission
		txDutyCycleTime = appTxDutyCycle + randr(0, APP_TX_DUTYCYCLE_RND);
		LoRaWAN.cycle(txDutyCycleTime);
		deviceState = DEVICE_STATE_SLEEP;
		break;
	}
	case DEVICE_STATE_SLEEP:
	{
		LoRaWAN.sleep();
		break;
	}
	default:
	{
		deviceState = DEVICE_STATE_INIT;
		break;
	}
	}
}