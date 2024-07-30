#include "WiFiHandler.h"

#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

WiFiHandler::WiFiHandler() {}

void WiFiHandler::setup()
{
    wifiConnectHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP &event)
                                                 { onConnect(event); });
    wifiDisconnectHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected &event)
                                                           { onDisconnect(event); });
}

void WiFiHandler::connect()
{
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void WiFiHandler::onConnect(const WiFiEventStationModeGotIP &event)
{
    Serial.println("Connected to Wi-Fi.");
    // MQTT bağlantısını buradan başlatın
}

void WiFiHandler::onDisconnect(const WiFiEventStationModeDisconnected &event)
{
    Serial.println("Disconnected from Wi-Fi.");
    wifiReconnectTimer.once(2, [this]()
                            { connect(); });
}
