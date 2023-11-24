/*
* Boilerplate code for connecting to Adafruit IO using a WiFi connection employing WPA2 enterprise authentication.
*
* Works with esp boards.
*/

#include <AdafruitIO_WiFi.h>
#include <esp_wpa2.h>

constexpr auto ADAFRUIT_USERNAME = "your_aio_username";
constexpr auto ADAFRUIT_KEY = "aio_xxxxxxxx";

constexpr auto WIFI_SSID = "your organisation's wifi ssid";
constexpr auto WIFI_USERNAME = "your wifi username";
constexpr auto WIFI_PASSWORD = "your wifi password";

AdafruitIO_WiFi io(ADAFRUIT_USERNAME, ADAFRUIT_KEY, WIFI_SSID, nullptr);

void setup()
{
    // Start a serial connection.
    Serial.begin(115200);

    // Wait until the serial connection is established.
    // Remove this line if you are running a headless configuration, such as when you're deploying your finished product.
    while (!Serial);

    // Enable wifi station mode (we are a client looking to connect to an access point)
    WiFi.enableSTA(true);

    // Set the wpa2 enterprise credentials to use.
    esp_wifi_sta_wpa2_ent_set_username((uint8_t*)WIFI_USERNAME, strlen(WIFI_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t*)WIFI_PASSWORD, strlen(WIFI_PASSWORD));

    // Tell esp to use wpa2 enterprise to authenticate the next connection.
    esp_wifi_sta_wpa2_ent_enable();

    Serial.println("Connecting to Adafruit IO");

    // Finally, connect to the wifi network and to adafruit io.
    io.connect();

    // Poll status until we're connected.
    while (io.status() < AIO_CONNECTED)
    {
        Serial.println(io.statusText());
        delay(500);
    }

    Serial.print("\nok! ");
    Serial.println(io.statusText());

    /*
     * You are now connected to Adafruit IO. 
     * AIO-related setup code should be put below, such as subscribing to feeds.
    */
}

void loop()
{
    /*
    * io.run(); is required for all sketches.
    * it should always be present at the top of your loop
    * function. it keeps the client connected to 
    * io.adafruit.com, and processes any incoming data.
    */
    io.run();
}