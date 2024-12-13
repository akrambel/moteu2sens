#define BLYNK_TEMPLATE_ID "TMPL2Mb2k2S1H"
#define BLYNK_TEMPLATE_NAME "TP"
#define BLYNK_AUTH_TOKEN "b_piDT_QxCelhx0XatJZK-FD259DEW9t"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TP-LINK_41EEBC";  
char pass[] = "LINA@2024@";  

bool relay0State = false; // État du relais D0
bool relay1State = false; // État du relais D1

BLYNK_WRITE(V0) { // Bouton pour activer le relais D0
  int buttonState = param.asInt(); // Récupère l'état du bouton
  if (buttonState == 1 && !relay1State) { // Active D0 uniquement si D1 est inactif
    relay0State = true;
    digitalWrite(D0, HIGH);
  }
}

BLYNK_WRITE(V1) { // Bouton pour activer le relais D1
  int buttonState = param.asInt(); // Récupère l'état du bouton
  if (buttonState == 1 && !relay0State) { // Active D1 uniquement si D0 est inactif
    relay1State = true;
    digitalWrite(D1, HIGH);
  }
}

BLYNK_WRITE(V2) { // Bouton pour arrêter les relais
  int buttonState = param.asInt(); // Récupère l'état du bouton
  if (buttonState == 1) { // Si le bouton est pressé
    relay0State = false;
    relay1State = false;
    digitalWrite(D0, LOW); // Désactive D0
    digitalWrite(D1, LOW); // Désactive D1
  }
}

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);

  digitalWrite(D0, LOW); // Assurez-vous que les relais sont désactivés au démarrage
  digitalWrite(D1, LOW);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}
