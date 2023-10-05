#include <Arduino.h>

String html_foot() {
  return "</body></html>";
}

String html_css() {
  String html = "<style>";
  html += "form {margin-bottom: 50px; display: grid; grid-template: auto / 300px auto; grid-gap: 20px;} ";
  html += "input, button {padding: 1em 0.5em;} ";
  html += "form h1, form h2, form button {grid-column: 1/3;} ";
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
  html += "<label>SSID</label><input id=\"ss_id\" />";
  html += "<label>PASS</label><input id=\"ss_pass\" type=\"password\" />";
  html += "<label>API_URL</label><input id=\"api_url\" type=\"url\" />";
  html += "<button type=\"button\" onClick=\"send();\">Save</button>";
  html += "</form>";
  return html;
}

String html_current_connection(String new_ssid, String new_pass, String api_url) {
  String html = "<h2>Current Settings</h2>";
  html += "<label>SSID</label><span>" + new_ssid + "</span>";
  html += "<label>PASS</label><span data-msg=\""+ new_pass +"\" onClick=\"this.innerHTML = this.getAttribute('data-msg')\">***click to show***</span>";
  html += "<label>API_URL</label><span>" + api_url + "</span>";
  return html;
}

String html_head() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />";
  html += html_css();
  html += html_script();
  html += "</head>";
  html += "<body>";
  return html;
}
