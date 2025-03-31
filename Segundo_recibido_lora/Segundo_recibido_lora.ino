#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10);
LoRa_E32 e32ttl(&mySerial, 5, 7, 6);
void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  
  e32ttl.begin();
  Serial.println("Receptor LoRa E32 listo");
}
void loop() {
  if (e32ttl.available() > 1) {
    ResponseContainer rs = e32ttl.receiveMessage();
    // Filtra caracteres no ASCII
    String cleanMessage = "";
    for (unsigned int i = 0; i < rs.data.length(); i++) {
      if (isprint(rs.data.charAt(i))) {
        cleanMessage += rs.data.charAt(i);
      }
    } 
    Serial.println(cleanMessage);

    // Procesamiento del mensaje válido
    if (cleanMessage.startsWith("Temp:") && cleanMessage.indexOf("Pres:") != -1) {
      // ... tu código de procesamiento ...
    }
  }
}
