#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* WLAN_SSID = "wll_vitor";
const char* WLAN_PASS = "248163264128256";

WiFiClient clientWifi;

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWifi();
}

void loop() {
  HttpPost();
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

void HttpGet() {
  HTTPClient http;
  
    if (!WiFi.status() == WL_CONNECTED ){
      connectWifi();
    }
  
    http.begin("https://fir-nodejs-dcdeb.firebaseio.com/users/-Kvo0Ku6qCW2dyA5kEzk.json", "B8:4F:40:70:0C:63:90:E0:07:E8:7D:BD:B4:11:D0:4A:EA:9C:90:F6");
    int httpCode = http.GET();
    Serial.println(httpCode);
  
    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);
    }
  
    http.end();
}

void HttpPost() {
  HTTPClient http;
  
    if (!WiFi.status() == WL_CONNECTED ){
      connectWifi();
    }
  
    http.begin("https://fir-nodejs-dcdeb.firebaseio.com/users/.json", "B8:4F:40:70:0C:63:90:E0:07:E8:7D:BD:B4:11:D0:4A:EA:9C:90:F6");
    int httpCode = http.POST("{ 'name': 'Goku' }");
    Serial.println(httpCode);
  
    if (httpCode == 200) {
      String payload = http.getString();
      Serial.println(payload);
    }
  
    http.end();
}

