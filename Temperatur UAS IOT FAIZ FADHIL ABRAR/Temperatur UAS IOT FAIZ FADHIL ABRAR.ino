#define BLYNK_TEMPLATE_ID "TMPLjNdLtJOv"
#define BLYNK_DEVICE_NAME "Faiz"
#define BLYNK_AUTH_TOKEN "ao2mtXJYCOsU7JQezDikLFFM7SIxzG1F"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "UMBANTEN 2";
char pass[] = "UM@Banten2022";

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <DHT.h>

const char* ssid = "UMBANTEN 1";
const char* password = "UM@Banten2022";

const char* serverName = "http://192.168.4.86/iot/be.php";

String apiKeyValue = "tokenAPIku";

String sensorName = "DHT";
String lokasi = "Kampus";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(115200);

WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());

dht.begin();
}

void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
String suhu = "Suhu1: ";

Serial.print(suhu + t + " `C DHT");
if(WiFi.status()== WL_CONNECTED){
WiFiClient client;
HTTPClient http;
http.begin(client, serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
+ "&lokasi=" + lokasi + "&value1=" + String(h)
+ "&value2=" + String(t) + "&value3=0" + String(f) + "";
Serial.println("httpRequestData: ");
Serial.println(httpRequestData);
int httpResponseCode = http.POST(httpRequestData);
if (httpResponseCode>0) {
Serial.println("HTTP Response code: ");
Serial.println(httpResponseCode);
}
else {
Serial.println("Error code: ");
Serial.println(httpResponseCode);
}
http.end();
}
else {
Serial.println("WiFi Disconnected");
}
delay(5000);
}