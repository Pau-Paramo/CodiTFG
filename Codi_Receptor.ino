#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRac.h>
#include <IRutils.h>

const uint16_t kRecvPin = 4; // 4, pin de connexió del receptor IR 
const uint32_t kBaudRate = 115200; // Velocitat de connexió eb sèrie
const uint16_t kCaptureBufferSize = 1024; //  Búffer

// Temps d'espera: retard en mil·lisegons per rebre diversos paquets de missatges
// Els protocols d'aire condicionat IR solen utilitzar un valor de 20-40 ms

#if DECODE_AC
const uint8_t kTimeout = 50; // Retard en mil·lisegons per rebre múltiples ràfagues de missatges
#else
const uint8_t kTimeout = 15;
#endif

const uint16_t kMinUnknownSize = 12; //La mida mínima de dades aleatòries desconegudes permet reduir el soroll

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;

void setup() {
#if defined(ESP8266)
  Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
#else
  Serial.begin(kBaudRate, SERIAL_8N1);
#endif
  while (!Serial)  
    delay(50);
  Serial.printf("\nEsperant un senyal IR per llegir, PIN: "
                "%d\n", kRecvPin);
#if DECODE_HASH
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif
  irrecv.enableIRIn();
}

void loop() {
  //Comprovació si hi ha un codi IR
  if (irrecv.decode(&results)) {
    // Marca temps
    uint32_t now = millis();
    Serial.printf("Timestamp : %06u.%03u\n", now / 1000, now % 1000);
    if (results.overflow)
      Serial.printf(
          "Avís: el codi IR supera la memòria intermèdia (>= %d). "
          "Els valors rebuts no són vàlids.\n",
          kCaptureBufferSize);
    Serial.println("Library : v" _IRREMOTEESP8266_VERSION_ "\n");
    Serial.print(resultToHumanReadableBasic(&results));

    String description = IRAcUtils::resultAcToString(&results);
    if (description.length()) Serial.println("Description: " + description);
    yield();
    
    Serial.println(resultToTimingInfo(&results));
    yield();
    
    Serial.println(resultToSourceCode(&results));
    Serial.println();
    yield();
  }
}
