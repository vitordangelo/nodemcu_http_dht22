#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <aJSON.h>

const char* WLAN_SSID = "wll_vitor";
const char* WLAN_PASS = "248163264128256";

WiFiClient clientWifi;

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWifi();
}

void loop() {
  HTTPClient http;

  if (!WiFi.status() == WL_CONNECTED ){
    connectWifi();
  }

  http.begin("https://jsonplaceholder.typicode.com/users/1");
  int httpCode = http.GET();
  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println(payload);
  }

  http.end();
  delay(5000);
}

void connectWifi() {
  Serial.println(); 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
}


