# ESP8266 BME680 Sensor MQTT Publisher

This project demonstrates how to use an ESP8266 to read data from a BME680 sensor and publish it to an MQTT broker. The project is structured to be modular and easy to understand.

## Project Structure
```
├── include
│ ├── WiFiHandler.h
│ ├── BME680Sensor.h
│ └── MQTTClientManager.h
├── src
│ ├── WiFiHandler.cpp
│ ├── BME680Sensor.cpp
│ ├── MQTTClientManager.cpp
│ └── main.cpp
├── platformio.ini
└── README.md
```

## Components Used

- ESP8266
- BME680 Sensor
- MQTT Broker (e.g., Mosquitto on a Raspberry Pi)

## Libraries Used

- `ESP8266WiFi.h`
- `Ticker.h`
- `AsyncMqttClient.h`
- `Wire.h`
- `SPI.h`
- `Adafruit_Sensor.h`
- `Adafruit_BME680.h`

## Wiring

Ensure the BME680 sensor is connected to the ESP8266 appropriately. For I2C, connect:
- `VIN` to `3.3V`
- `GND` to `GND`
- `SCL` to `D1`
- `SDA` to `D2`

For SPI, refer to the specific pin definitions in `BME680Sensor.h`.

## Setup

1. **Clone the repository:**

   ```bash
   git clone https://github.com/burakkcmn/nodemcu-mqtt-bme680.git
   cd nodemcu-mqtt-bme680
   ```

2. Open the project with PlatformIO:

    If you haven't already, install PlatformIO in your preferred IDE (e.g., VSCode).

3. Configure WiFi and MQTT:

    Update the WiFi SSID, password, and MQTT broker details in WiFiManager.h and MQTTClientManager.h.

4. Upload the code:

    Connect your ESP8266 to your computer and upload the code using PlatformIO.

## Usage
Once uploaded, the ESP8266 will:

1. Connect to the specified WiFi network.
2. Connect to the MQTT broker.
3. Read data from the BME680 sensor every 10 seconds.
4. Publish the temperature, humidity, pressure, and gas resistance readings to the MQTT broker.

You can subscribe to the following MQTT topics to receive the sensor data:

- esp/bme680/temperature
- esp/bme680/humidity
- esp/bme680/pressure
- esp/bme680/gas

## Example Output
    
```plaintext
Temperature = 25.30 ºC 
Humidity = 40.50 % 
Pressure = 1013.20 hPa 
Gas Resistance = 0.82 KOhm 
Publishing on topic esp/bme680/temperature at QoS 1, packetId: 1 Message: 25.30 
Publishing on topic esp/bme680/humidity at QoS 1, packetId 2: Message: 40.50 
Publishing on topic esp/bme680/pressure at QoS 1, packetId 3: Message: 1013.20 
Publishing on topic esp/bme680/gas at QoS 1, packetId 4: Message: 0.82 
```

## Troubleshooting
- Ensure the BME680 sensor is wired correctly.
- Double-check the WiFi credentials and MQTT broker details.
- Use a serial monitor to debug any connection issues.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project is based on tutorials by Rui Santos & Sara Santos - [Random Nerd Tutorials](https://RandomNerdTutorials.com/)