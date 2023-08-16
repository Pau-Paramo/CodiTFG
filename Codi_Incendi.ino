#define BLYNK_TEMPLATE_ID "TMPL9Efi0t2B"
#define BLYNK_TEMPLATE_NAME "Alerta d'incendis"
#define BLYNK_AUTH_TOKEN "zVvOkRdha4GrmMmQcxeSwfjklfgdjhyVgsJTl7jF"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Blynk"; 
char pass[] = "Pwblynk33"; 
 

BlynkTimer timer;
int flag=0; 
void Sensor(){ 
   int BotoPressionat = digitalRead(D1);
  if (BotoPressionat==0 && flag==0) {
    Serial.println("Foc a acasa");  
    Blynk.logEvent("alerta_foc","Foc detectat");
    
    flag=1;
  }
  else if (BotoPressionat==1)
  {
    flag=0;
    
  }
 
}

void setup(){
  pinMode(D1, INPUT);
 
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, Sensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
