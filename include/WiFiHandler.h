#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <ESP8266WiFi.h>
#include <Ticker.h>

class WiFiHandler
{
public:
    WiFiHandler();
    void setup();
    void connect();

private:
    void onConnect(const WiFiEventStationModeGotIP &event);
    void onDisconnect(const WiFiEventStationModeDisconnected &event);
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;
    Ticker wifiReconnectTimer;
};

#endif
