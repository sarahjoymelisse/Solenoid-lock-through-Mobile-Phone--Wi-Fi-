#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
int relay1 = D2; // GPIO13
void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.flush();
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ZTEH108N_96F20", "ItsAnaColiFam19");
  Serial.println("Connect");

}
void loop() {

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    Serial.println("C");
    HTTPClient http;
    http.begin("http://locker.x10host.com/in.php"); //HTTP
    int httpCode = http.GET();
    if (httpCode > 0) {
      //      if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(" ************************************************************* ");
      Serial.println(payload[0]);

      if (payload[0] == '1') {
        digitalWrite(relay1, LOW);
      }
      else {
        digitalWrite(relay1, HIGH);
      }

    }
    http.end();  //Close connection
    //    ultra();
    //    HTTPClient http2;
    //    String dataline2 = "id=4&status=" + String(distance);
    //    http2.begin("http://lock.x10host.com/move.php?");
    //    http2.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //    int httpCode2 = http2.POST(dataline2);
    //    String payload2 = http2.getString();    //Get the response payload
    //    Serial.println(httpCode2);   //Print HTTP return code
    //    Serial.println(payload2);    //Print request response payload
    //    http2.end();  //Close connection
  }
  else {
    Serial.println("Not Connected");
  }
  delay(1000);
}
