#include <Arduino.h>
#include "WiFiHandler.h"
#include "MQTTClientManager.h"
#include "BME680Sensor.h"

WiFiHandler wifiHandler;
MQTTClientManager mqttClientManager;
BME680Sensor bme680Sensor;
// BME680Sensor bme680Sensor(BME_CS); // Hardware SPI
// BME680Sensor bme680Sensor(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // Custom SPI

unsigned long previousMillis = 0;
const long interval = 10000;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  wifiHandler.setup();
  mqttClientManager.setup();
  if (!bme680Sensor.begin())
  {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1)
      ;
  }

  wifiHandler.connect();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    float temperature, humidity, pressure, gasResistance;
    bme680Sensor.getReadings(temperature, humidity, pressure, gasResistance);

    Serial.printf("Temperature = %.2f ºC \n", temperature);
    Serial.printf("Humidity = %.2f %% \n", humidity);
    Serial.printf("Pressure = %.2f hPa \n", pressure);
    Serial.printf("Gas Resistance = %.2f KOhm \n", gasResistance);

    mqttClientManager.publishReadings(temperature, humidity, pressure, gasResistance);
  }
}
