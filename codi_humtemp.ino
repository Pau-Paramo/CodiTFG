//Tech Trends Shameer

#define BLYNK_TEMPLATE_ID "TMPLIAjddf20T5"
#define BLYNK_DEVICE_NAME "Temperatura i humitat"
#define BLYNK_AUTH_TOKEN "122RywymdfdddgGfMd1jkZ0STNhRQecR12ayq"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "WiFi Blynk";
char pass[] = "Pwblynk33"; 

BlynkTimer timer;


#define DHTPIN 4 //Connexió al pin 4
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);


void Sensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // lectura de mesures

  if (isnan(h) || isnan(t)) {
    Serial.println("Lectura de sensor fallida");
    return;
  }

    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperatura : ");
    Serial.print(t);
    Serial.print("    Humitat : ");
    Serial.println(h);
}
void setup()
{   
  
  Serial.begin(115200);
  

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, Sensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
