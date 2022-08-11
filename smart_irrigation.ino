#define BLYNK_TEMPLATE_ID "TMPL8LWnEg-O"
#define BLYNK_DEVICE_NAME "smartfarming"
#define BLYNK_AUTH_TOKEN "M_UfEtwYY-Nskde-FZkuwFYmHLusC9pj"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

int sensorpin = A0;
int sensorvalue = 0;
int outputvalue = 0;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "redmi";  // type your wifi name
char pass[] = "redmi123";  // type your wifi password


BlynkTimer timer;


#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define ONE_WIRE_BUS D6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Get the button value
BLYNK_WRITE(V4) {
  digitalWrite(D0, param.asInt());
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V3, temp);  //V3 is for Temperature
  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print("    Humidity : ");
  Serial.println(h);
}
void setup()
{
  pinMode(D0, OUTPUT);
  pinMode(D5, OUTPUT);
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);

}

void loop()
{

  sensorvalue = analogRead(sensorpin);
  outputvalue = map(sensorvalue, 0, 1023, 0, 100); //100,0 pottupaaru
  delay(100);

  if (outputvalue > 60)
  {
    Serial.println("water your plant");
    Serial.print(outputvalue);
    Blynk.notify("water your plant");
    Blynk.logEvent("notice");
    delay(100);
  }
  else if (outputvalue < 45)
  {
    Serial.println("soil is wet enough to water");
    Serial.print(outputvalue);
    Blynk.logEvent("notice","soil is wet enough to water");// notification
    Blynk.notify("soil is wet enough to water");
    delay(100);
  }
  Blynk.virtualWrite(V2, outputvalue);
  Blynk.run();
  timer.run();
}
