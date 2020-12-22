
#include <ArduinoJson.h>

StaticJsonDocument<100> doc;

bool getJsonIfAvailable();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) continue;
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  getJsonIfAvailable();
  delay(30);
}

bool getJsonIfAvailable(){
  if(Serial.available()){
    String json ="";
    char c = '\0';
    while(c != '\n'){
      c = Serial.read();
      json += c;
    }
    Serial.print(json);
    
    DeserializationError error = deserializeJson(doc, json);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    if(!doc["D2"].isNull()){
      bool val = doc["D2"];
      digitalWrite(2, val?HIGH:LOW);
    }
    if(!doc["D3"].isNull()){
      bool val = doc["D3"];
      digitalWrite(3, val?HIGH:LOW);
    }
    if(!doc["D4"].isNull()){
      bool val = doc["D4"];
      digitalWrite(4, val?HIGH:LOW);
    }
    return true;
  }else{
    return false;
  }
}
