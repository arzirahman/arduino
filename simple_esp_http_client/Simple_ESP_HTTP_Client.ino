#include <Arduino_JSON.h>
#include <Himace.h>

Himace himace;

void setup() {
  Serial.begin(115200);
  himace.setWifi("422781", "181354003");
  himace.wifiConnect();
  himace.setServerName("http://192.168.43.51:5001");
  himace.setToken("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6Img1ZGMwYWMwNTE2MGUiLCJyb2xlIjoidXNlciIsImlhdCI6MTY2NjE2ODY2OX0.1jea8Datrp9Yu0Lo3Wild7IL2NvyCOA8Iy-VX3To5sA");
  himace.reconnect(true);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  himace.setString("suhu","12.65");
  delay(1000);
}
