/*
  Steps:
  1. Connect to the access point "ssid"
  2. Connect to http://192.168.4.1 to see an html form
*/
#include "config.h"
#include "server.h"
#include "html.h"

#include <WebServer.h>
#include <ArduinoJson.h>

String new_ssid = "";
String new_pass = "";
String api_url = "";

WebServer server(80);

StaticJsonDocument<250> jsonDocument;

void handle_connect() {
  Serial.println("Connecting");
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);
  new_ssid = jsonDocument["ss_id"].as<String>();
  new_pass = jsonDocument["ss_pass"].as<String>();
  api_url = jsonDocument["api_url"].as<String>();
  Serial.println(new_ssid);
  Serial.println(new_pass);
  Serial.println(api_url);

  server.send(200, "text/html", html_current_connection(new_ssid, new_pass, api_url));
}

void handle_home() {
  
  String html = html_head();
  html += html_form();
  html += "<form id=\"current\">" + html_current_connection(new_ssid, new_pass, api_url) + "</form>";
  html += html_foot();
  
  server.send(200,"text/html",html);
}

void server_start() {
  server.on("/", handle_home);
  server.on("/connect", HTTP_POST, handle_connect);
  server.begin();
}

void setup() {

  Serial.begin(115200);

  access_point_start();

  server_start();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
