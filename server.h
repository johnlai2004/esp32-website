#include <Arduino.h>

#ifndef SERVER_FUNCTIONS
#define SERVER_FUNCTIONS
void access_point_start();
const char* get_ssid();
const char* get_pass();
String get_api_url();
bool ssid_exists();
void handle_connect();
void handle_home();
void server_start();
void server_end();
void server_handle_client();
#endif // SERVER_FUNCTIONS
