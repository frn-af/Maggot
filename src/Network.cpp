#include "Network.h"

#include <addons/TokenHelper.h>

static Network *instance = NULL;

Network::Network()
{
    instance = this;
}

void WiFiEventConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Connected to AP");
}

void WiFiEventDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Disconnected from AP");
}

void WiFiEventGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Got IP");
    Serial.println(WiFi.localIP());
}

void Network::init_wifi(const char *ssid, const char *password)
{
    WiFi.onEvent(WiFiEventConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(WiFiEventDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.onEvent(WiFiEventGotIP, ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.begin(ssid, password);
}

void Network::init_firebase(const char *api_key, const char *user_email, const char *user_password, const char *firebase_project_id)
{
    Serial.println("*** Firebase Client - Firestore ***");
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = api_key;
    /* Assign the user sign in credentials */
    auth.user.email = user_email;
    auth.user.password = user_password;
    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    // Limit the size of response payload to be collected in FirebaseData

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}
