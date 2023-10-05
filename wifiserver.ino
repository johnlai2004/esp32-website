/*
  Steps:
  1. Connect to the access point "ssid"
  2. Connect to http://192.168.4.1 to see an html form
*/
#include "server.h"

void setup() {

  Serial.begin(115200);

  access_point_start();

  server_start();

  Serial.println("Server started");
}

void loop() {
  server_handle_client();
}
