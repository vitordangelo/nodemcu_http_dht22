#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

const char* WLAN_SSID = "wll_vitor";
const char* WLAN_PASS = "248163264128256";
#define DHTPIN D2
#define DHTTYPE DHT22

WiFiClient clientWifi;

DHT dht(DHTPIN, DHTTYPE);
float humidty;
float temperature;

void setup() {
  Serial.begin(115200);
  delay(10);
  connectWifi();
}

void loop() {
  readTemperetureHumidity();
  HttpPost();
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
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = temperature;
  root["humidty"] = humidty;

  JsonObject& timestap = root.createNestedObject("timestap");
  timestap[".sv"] = "timestamp";  

  String dataJson;
  root.prettyPrintTo(dataJson);

  Serial.println(dataJson);

  HTTPClient http;
  
  if (!WiFi.status() == WL_CONNECTED ){
    connectWifi();
  }

  http.begin("https://fir-nodejs-dcdeb.firebaseio.com/dht22/.json", "B8:4F:40:70:0C:63:90:E0:07:E8:7D:BD:B4:11:D0:4A:EA:9C:90:F6");
  int httpCode = http.POST(dataJson);
  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println(payload);
  }

  http.end();
}

void readTemperetureHumidity() {
  humidty = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidty) || isnan(temperature) ){
    Serial.println("Falha na leitura!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(humidty);
  Serial.println(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" Celsius");

  delay(60000);
}
