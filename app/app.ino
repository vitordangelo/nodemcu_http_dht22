#include <DHT.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* WLAN_SSID = "V2Tech";
const char* WLAN_PASS = "v2techwifi";
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

void HttpPost() {
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = temperature;
  root["humidity"] = humidty;

  String dataJson;
  root.prettyPrintTo(dataJson);

  Serial.println(dataJson);

  HTTPClient http;
  
  if (!WiFi.status() == WL_CONNECTED ){
    connectWifi();
  }

  http.begin("http://35.199.102.99:8300/api/v1/log");
  http.addHeader("Content-Type", "application/json");

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
