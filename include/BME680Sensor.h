#ifndef BME680_SENSOR_H
#define BME680_SENSOR_H

#include <Adafruit_BME680.h>

#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15

class BME680Sensor
{
public:
    BME680Sensor();          // I2C constructor
    BME680Sensor(int8_t cs); // Hardware SPI constructor
    BME680Sensor(int8_t cs, int8_t mosi, int8_t miso, int8_t sck);
    bool begin();
    void getReadings(float &temperature, float &humidity, float &pressure, float &gasResistance);

private:
    Adafruit_BME680 bme;
};

#endif
