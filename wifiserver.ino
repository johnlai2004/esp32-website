/*
  
  Steps:
  1. Connect to the access point "ssid"
  2. Connect to http://192.168.4.1 to see an html form
*/
#include "config.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <WiFiAP.h>
#include <ArduinoJson.h>

// Set these to your desired credentials.
const char *ssid = SSID_NAME;
const char *password = SSID_PASS;

String new_ssid = "";
String new_pass = "";
String api_url = "";

WebServer server(80);

StaticJsonDocument<250> jsonDocument;
String html_head() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />";
  html += html_css();
  html += html_script();
  html += "</head>";
  html += "<body>";
  return html;
}
String html_foot() {
  return "</body></html>";
}
String html_css() {
  String html = "<style>";
  html += "form {margin-bottom: 50px; display: grid; grid-template: auto / 300px auto; grid-gap: 20px;} ";
  html += "input {padding: 1em 0.25em;} ";
  html += "form :is(h1, h2, button) {grid-column: 1/3;} ";
  html += "</style>";
  return html;
}
String html_script() {
  String html = "<script type=\"text/javascript\">";
  html += "function send() {";
  html += "fetch('/connect',{";
  html += "  'headers':{'Content-Type':'application/json','Accept':'application/json'},";
  html += "  'method':'post',";
  html += "  'body':JSON.stringify({'ss_id': document.getElementById('ss_id').value,'ss_pass':document.getElementById('ss_pass').value,'api_url':document.getElementById('api_url').value})";
  html += "})";
  html += ".then(r=>r.text())";
  html += ".then(r=>{document.getElementById('current').innerHTML = r;});";
  html +="}</script>";
  return html;
}

String html_form() {
  String html = "<form>";
  html += "<h1>Connect with:</h1>";
  html += "<label>SSID</label><input id=\"ss_id\" value=\"" +new_ssid+ "\"/>";
  html += "<label>PASS</label><input id=\"ss_pass\" type=\"password\" value=\"" +new_pass+ "\"/>";
  html += "<label>API_URL</label><input id=\"api_url\" value=\"" +api_url+ "\"/>";
  html += "<button type=\"button\" onClick=\"send();\">Save</button>";
  html += "</form>";
  return html;
}

String html_current_connection() {
  String html = "<h2>Current Settings</h2>";
  html += "<label>SSID</label><span>" + new_ssid + "</span>";
  html += "<label>SSPASS</label><span data-msg=\""+ new_pass +"\" onClick=\"this.innerHTML = this.getAttribute('data-msg')\">***click to show***</span>";
  html += "<label>API</label><span>" + api_url + "</span>";
  return html;
}


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

  server.send(200, "text/html", html_current_connection());
}

void handle_home() {
  
  String html = html_head();
  html += html_form();
  html += "<form id=\"current\">" + html_current_connection() + "</form>";
  html += html_foot();
  
  server.send(200,"text/html",html);
}

void setup_routes() {     
  server.on("/", handle_home);
  server.on("/connect", HTTP_POST, handle_connect);
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  setup_routes();
  
  server.begin();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
