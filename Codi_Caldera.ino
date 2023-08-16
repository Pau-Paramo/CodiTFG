//ID, nom del dispositiu i token d'autorització
#define BLYNK_TEMPLATE_ID "TMPL5i2nQ5uZ9"
#define BLYNK_TEMPLATE_NAME "Caldera"
#define BLYNK_AUTH_TOKEN "DaQOqyauRiwBSLnFSQCxBCOMD3qRsT72"
#define BLYNK_PRINT Serial

//Inclusió de llibreries
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

//Credencials de WiFi
char ssid[] = "WiFi Blynk";
char pass[] = "Pwblynk33";

BlynkTimer timer;

//Variable de pin de connexió a botó
#define button1_pin 15

//Variable de pin de connexió a relé
#define relay1_pin 4

//estat inicial de relé
int relay1_state = 0;


//Relació pin virtual Blynk
#define button1_vpin    V1

//------------------------------------------------------------------------------
//Funció de connexió amb Blynk
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
}

//--------------------------------------------------------------------------
//Funció de modificació d'estat de pin
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}
//--------------------------------------------------------------------------

//Funció d'inicialització
void setup()
{
  // Debug console
  Serial.begin(115200);
  //--------------------------------------------------------------------
  pinMode(button1_pin, INPUT_PULLUP);
  //--------------------------------------------------------------------
  pinMode(relay1_pin, OUTPUT);
  //--------------------------------------------------------------------
  //Relés en OFF
  digitalWrite(relay1_pin, HIGH);
  //--------------------------------------------------------------------
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();
  listen_push_buttons();
}


void listen_push_buttons(){
    if(digitalRead(button1_pin) == LOW){
      delay(200);
      control_relay(1);
      Blynk.virtualWrite(button1_vpin, relay1_state); //actualització d'estat del botó
    }
}


void control_relay(int relay){
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
}