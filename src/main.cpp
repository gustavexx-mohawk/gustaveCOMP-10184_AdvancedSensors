
/* Statement of Authorship COMP-10184-01: I Gustavo Jose Marcano, 000812644 certify
that this material is my original work. No other person's work has been used without 
due acknowledgement. I have not made my work available to anyone else. */

// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
DeviceAddress device;

bool printSuccessFlag = true;
bool printErrorFlag = true;
int processDelay = 4500;

// Print function to print the device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("");
    // zero pad the address if necessary
    if (deviceAddress[i] < 16)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println("");
}

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  delay(processDelay);
  DS18B20.requestTemperatures();
if (DS18B20.getTempCByIndex(0) != -127.00 )
  {
    Serial.println("\nTemperature Application");
    DS18B20.getAddress(device, 0); // Because is only one sensor, get zero index
    Serial.print("Found DS18B20 sensor with address: ");
    printAddress(device);
    printSuccessFlag = false;
    processDelay = 5000;
  }
}

void loop()
{
  String message = "";
  float fTemp;

  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();

  // fetch the temperature.  We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);

  if (fTemp != -127.00 /*String(DS18B20.isConnected(device)==1)*/)
  {
    processDelay = 5000;

    if (fTemp < 10)
      message = "Cold!";
    else if (fTemp >= 10 && fTemp < 15)
      message = "Cool";
    else if (fTemp >= 15 && fTemp < 25)
      message = "Perfect";
    else if (fTemp >= 25 && fTemp < 30)
      message = "Warm";
    else if (fTemp >= 30 && fTemp < 35)
      message = "Hot";
    else if (fTemp >= 35)
      message = "Too hot";
    // print the temp to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + " °. C or " + message);
  }
  else
  {
    processDelay = 4500;
    delay(processDelay);
    if (printErrorFlag)
    {
      Serial.println("Temperature Application");
      Serial.println("No DS18B20 sensors are installed");
      printErrorFlag = false;
      return;
    }
  }
}
