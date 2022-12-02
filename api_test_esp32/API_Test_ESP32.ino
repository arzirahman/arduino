#include <WiFi.h>
#include <SocketIoClient.h>

const char* ssid = "422781";
const char* password = "181354003";

SocketIoClient socket;

void event(const char * payload, size_t length) {
  Serial.printf("got message: %s\n", payload);
}

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("Connected :)");
  Serial.println(" ");
  delay(1000);
  socket.on("event", event);
  socket.begin("192.168.43.51", 5002, "/socket.io/?transport=websocket");
}

void loop() {
  socket.loop();
}
