#include "MQTTClientManager.h"
#include <Ticker.h>
#include <ESP8266WiFi.h>

#define MQTT_HOST IPAddress(192, 168, 1, 100)
#define MQTT_PORT 1883

#define MQTT_PUB_TEMP "esp/bme680/temperature"
#define MQTT_PUB_HUM "esp/bme680/humidity"
#define MQTT_PUB_PRES "esp/bme680/pressure"
#define MQTT_PUB_GAS "esp/bme680/gas"

Ticker mqttReconnectTimer;

MQTTClientManager::MQTTClientManager() : mqttClient() {}

void MQTTClientManager::setup()
{
    mqttClient.onConnect([this](bool sessionPresent)
                         { onConnect(sessionPresent); });
    mqttClient.onDisconnect([this](AsyncMqttClientDisconnectReason reason)
                            { onDisconnect(reason); });
    mqttClient.onSubscribe([this](uint16_t packetId, uint8_t qos)
                           { onMqttSubscribe(packetId, qos); });
    mqttClient.onUnsubscribe([this](uint16_t packetId)
                             { onMqttUnsubscribe(packetId); });
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCredentials("REPlACE_WITH_YOUR_USER", "REPLACE_WITH_YOUR_PASSWORD");
}

void MQTTClientManager::connect()
{
    mqttClient.connect();
}

void MQTTClientManager::onConnect(bool sessionPresent)
{
    Serial.println("Connected to MQTT.");
    Serial.print("Session present: ");
    Serial.println(sessionPresent);
}

void MQTTClientManager::onDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Disconnected from MQTT.");
    mqttReconnectTimer.once(2, [this]()
                            { connect(); });
}

void MQTTClientManager::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("Subscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
    Serial.print("  qos: ");
    Serial.println(qos);
}

void MQTTClientManager::onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}

void MQTTClientManager::publishReadings(float temperature, float humidity, float pressure, float gasResistance)
{
    mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(temperature).c_str());
    mqttClient.publish(MQTT_PUB_HUM, 1, true, String(humidity).c_str());
    mqttClient.publish(MQTT_PUB_PRES, 1, true, String(pressure).c_str());
    mqttClient.publish(MQTT_PUB_GAS, 1, true, String(gasResistance).c_str());
}
