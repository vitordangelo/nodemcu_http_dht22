#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
}

void loop() {
  delay(3000);
  createJson();
}

void createJson() {
   // https://bblanchon.github.io/ArduinoJson/assistant/
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject& root = jsonBuffer.createObject();
 
   root["sensor"] = "gps";
   root["time"] = 1351824120;
 
   JsonArray& data = root.createNestedArray("data");
   data.add(48.756080);
   data.add(2.302038);
 
   //root.printTo(Serial);
   //root.prettyPrintTo(Serial);
   String dataJson;
   root.prettyPrintTo(dataJson);
   Serial.println(dataJson);
}


