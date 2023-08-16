//Credencials Blynk
#define BLYNK_TEMPLATE_ID "TMPLX9GgD_5O"
#define BLYNK_TEMPLATE_NAME "Detecció de pluja"
#define BLYNK_AUTH_TOKEN "hMjbyC5U-mM7YFpUIP361172H89MgV0w"

//Llibreries
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Variables
#define RAIN_SENSOR_PIN A0    //(Variable analògic)
#define RAIN_SENSOR_THRESHOLD 500

char ssid[] = "WiFi Blynk";
char pass[] = "PwBlynk33";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  int ValorSensor = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Valor sensor pluja: ");
  Serial.println(ValorSensor);

  if (ValorSensor < RAIN_SENSOR_THRESHOLD) {
    Blynk.logEvent("alerta.pluja");
  }

  Blynk.virtualWrite(V0, ValorSensor);

  Blynk.run();
  delay(1000);
}

