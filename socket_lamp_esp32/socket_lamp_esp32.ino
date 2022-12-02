#include <WiFi.h>
#include <WiFiMulti.h>
#include <Arduino_JSON.h>
#include <WebSocketsClient_Generic.h>
#include <SocketIOclient_Generic.h>

WiFiMulti       WiFiMulti;
SocketIOclient  socketIO;

char ssid[] = "Padepokan79_core";
char pass[] = "Majubersama2020";
int LED_PIN = 16;

void socketIOEvent(const socketIOmessageType_t& type, uint8_t * payload, const size_t& length)
{
  switch (type) 
  {
    case sIOtype_DISCONNECT:
      Serial.println("Socket Disconnected");
      break;
      
    case sIOtype_CONNECT:
      socketIO.send(sIOtype_CONNECT, "/");
      Serial.println("Socket Connected");
      break;
      
    case sIOtype_EVENT:
      parseData((char*) payload);
      break;

    case sIOtype_ERROR:
      Serial.print("[IOc] Get error: ");
      Serial.println(length);
      break;

    default:
      break;
  }
}

void parseData(char* payload){
  Serial.println(payload);
  JSONVar parsed = JSON.parse(payload);
  digitalWrite(LED_PIN, (bool)parsed[1]["value"]);
}

void setup()
{
  Serial.begin(115200);
  WiFiMulti.addAP(ssid, pass);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  socketIO.begin("iot.harmy.tech", 80);
  socketIO.onEvent(socketIOEvent);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() 
{
  socketIO.loop();
}
