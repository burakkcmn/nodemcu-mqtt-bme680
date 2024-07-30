#include "BME680Sensor.h"
#include <Wire.h>

BME680Sensor::BME680Sensor() : bme() {}

// Hardware SPI constructor
BME680Sensor::BME680Sensor(int8_t cs) : bme(cs) {}

// Custom SPI constructor
BME680Sensor::BME680Sensor(int8_t cs, int8_t mosi, int8_t miso, int8_t sck)
    : bme(cs, mosi, miso, sck) {}

bool BME680Sensor::begin()
{
    if (!bme.begin())
    {
        return false;
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    return true;
}

void BME680Sensor::getReadings(float &temperature, float &humidity, float &pressure, float &gasResistance)
{
    unsigned long endTime = bme.beginReading();
    if (endTime == 0 || !bme.endReading())
    {
        return;
    }
    temperature = bme.temperature;
    pressure = bme.pressure / 100.0;
    humidity = bme.humidity;
    gasResistance = bme.gas_resistance / 1000.0;
}
