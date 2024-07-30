#ifndef MQTT_CLIENT_MANAGER_H
#define MQTT_CLIENT_MANAGER_H

#include <AsyncMqttClient.h>

class MQTTClientManager
{
public:
    MQTTClientManager();
    void setup();
    void connect();
    void publishReadings(float temperature, float humidity, float pressure, float gasResistance);

private:
    AsyncMqttClient mqttClient;
    void onConnect(bool sessionPresent);
    void onDisconnect(AsyncMqttClientDisconnectReason reason);
    void onMqttSubscribe(uint16_t packetId, uint8_t qos);
    void onMqttUnsubscribe(uint16_t packetId);
};

#endif
