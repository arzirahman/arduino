#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Padepokan79_bootcamp";
const char* password = "Majubersama2020";

String serverName = "http://iot.himace.tech/esp32/a0";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println(" ");
  delay(1000);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){
    //send data to server
    httpPOST(1200);
    //get data from server
    String data = httpGET();
    Serial.println(data);
  }
  else{
    Serial.println("WiFi Disconnected!!!");
  }
  delay(1000);
}

String httpGET(){
  String serverPath = serverName, payload;
  http.begin(client, serverPath.c_str());
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return payload;
}

void httpPOST(int data){
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"a0\":" + String(data) + "}");
  if (httpResponseCode>0) {
    if(httpResponseCode == 200){
      Serial.println("Response Status: OK");
    }
    else{
      Serial.print("Response Status: ");
      Serial.println(httpResponseCode);
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
