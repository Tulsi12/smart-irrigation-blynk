
//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLih7IRGfk"
#define BLYNK_DEVICE_NAME "motor"
#define BLYNK_AUTH_TOKEN "CACqSW4MjJnzpoM-vuohVuFKhMIg6kU9"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iPhone";//Enter your WIFI name
char pass[] = "Rubyruby";//Enter your WIFI password

//Get the button value
BLYNK_WRITE(V4) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
}
