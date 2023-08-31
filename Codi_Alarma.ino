//Blynk
#define BLYNK_TEMPLATE_ID "TMPL5a0RuV_TE"
#define BLYNK_TEMPLATE_NAME "AC"
#define BLYNK_AUTH_TOKEN "yy8KjJk-cgwrlOULz5ipBaeAnHM-2dmC"

//Llibreries
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial       
#include <BlynkSimpleEsp8266.h>
char auth[] = "Your Auth Key";

//Credencials WiFi
char ssid[] = "WiFi Blynk";
char pass[] = "Pwblynk33";


#define pirPin 5                // Entrada PIR
int pirValue;                   // Variable per guardar valor del PIR
int pinValue;                   //Variable per llegir valor del PIR

BLYNK_WRITE(V0)
{
 pinValue = param.asInt();    
} 

void setup()
  {
    Serial.begin(115200);
    delay(10);
    Blynk.begin(auth, ssid, pass);
    pinMode(pirPin, INPUT);
  }

void loop()
  {
     if (pinValue == HIGH)    
      {
        getPirValue();
      }
    Blynk.run();
  }

void getPirValue(void)        //Notifiacions
  {
   pirValue = digitalRead(pirPin);
    if (pirValue) 
     { 
       Serial.println("Motion detected");
       Blynk.notify("Motion detected");  
     }
  }

