#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
LoRa_E32 e32ttl(&mySerial, 5, 7, 6); // M0, M1, AUX

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(50);

  e32ttl.begin();
  Serial.println("Receptor LoRa E32 listo");
}

void loop() {
  if (e32ttl.available() > 1) {
    ResponseContainer rs = e32ttl.receiveMessage();
    
    // Filtrar caracteres no ASCII
    String cleanMessage = "";
    for (unsigned int i = 0; i < rs.data.length(); i++) {
      if (isprint(rs.data.charAt(i))) {
        cleanMessage += rs.data.charAt(i);
      }
    }

    // Imprimir mensaje recibido en el monitor serie
    Serial.println("Mensaje recibido:");
    Serial.println(cleanMessage);
    Serial.println("---------------------");
  }
}
