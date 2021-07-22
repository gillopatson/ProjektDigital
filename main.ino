#include "Wasserentnahme.h"
#include "Standby.h"
#include "Spuelung.h"
#include "ArduinoTimer.h"

//const byte interruptDesaktivierungPin = 2;

int Niederdruckschalter = 12;
int Hochdruckschalter = 13;
int Spuelventil = 3;
int Drainventil = 4;
int Pumpe = 6;
int Uvclampe = 7;
int Hauptventil = 5;
int counter;
ArduinoTimer Timer1;

unsigned long truutime1;
unsigned long truutime2;
unsigned long HollidayTime1;
unsigned long HollidayTime2 = 0;

Wasserentnahme wasserentnahme( Hauptventil, Drainventil,  Pumpe , Spuelventil, Uvclampe, Niederdruckschalter, Hochdruckschalter );  // Objekt vom Konstruktor Wasserentnahme
Standby standby(Hauptventil, Drainventil,  Pumpe , Spuelventil, Uvclampe);  // Objekt vo Konstruktor Standby
Spuelung spuelung(Hauptventil, Drainventil,  Pumpe , Spuelventil, Uvclampe, Niederdruckschalter, Hochdruckschalter, counter);  // Objekt vom Konstruktor Spuelung


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(Hochdruckschalter , INPUT);
  pinMode(Niederdruckschalter, INPUT);
}

void loop() {

  Niederdruckschalter = digitalRead(12);   // Niederdruckschalter wird am Pin 12 gelesen
  Hochdruckschalter = digitalRead(13);    // Hochdruchschalter wird am Pin 13 gelesen
  delay(500);   // Kurze delay zeit damit man den Wert von Schalter lesen kann

    
  while (Niederdruckschalter == HIGH) { // Zur überprüfung ob der Niederdruckschalter HIGH oder LOW ist
    
 HollidayTime1 = millis();  // HollidayTimer für die Messung ob man zu lange den Filter nicht benutzt hat
 
    // Einfügen von der neuen Funktion
    if (HollidayTime1 - HollidayTime2 > 400000 )  // Differenzzeit zur Messung der Urlaubzeit
    {
      Serial.println("more than 400s Urlaub has passed");
      spuelung.Spuelvorgang(); // Wenn lange nicht da war, wird der Spuelvorgang durchgeführt
      break;
    }


    // Einfügen von der neuen Funktion

    Niederdruckschalter = digitalRead(12);

    if (Niederdruckschalter == LOW) {
      Serial.println("break condition zum abbruch weil niederdruckschalter aus");
      break;
    }

    Serial.println("Niederdruckschalter HIGH");
    Hochdruckschalter = digitalRead(13);
   
    while (Hochdruckschalter == HIGH)
    {
      truutime1 = millis();
      Hochdruckschalter = digitalRead(13);
      wasserentnahme.Entnahme();           // Wasserentnahme wird gestartet
      Serial.println("Wasserentnahmen");
      //delay(3000);
      Niederdruckschalter = digitalRead(12);

      if (Niederdruckschalter == LOW) {
        Serial.println("break condition zum abbruch weil niederdruckschalter aus");
        break;
      }
      if (Hochdruckschalter == LOW)  // Bedingung zum Abbruch der Schleife
      {
        Serial.println("Hochdruckschalter LOW, Wasserentnahme beendet");
        break;
      }

    }

    truutime2 = millis();
    Serial.println(truutime2);
    if (truutime2 - truutime1 > 1000)
    { // Überprüfung ob Wasserentnahme genug lange durchgeführt wurde

      while (Hochdruckschalter == LOW)
      { // Die Wasseerentnahme wurde genug lange durchgeführt
        if (Niederdruckschalter == LOW) {
          Serial.println("break condition zum abbruch weil niederdruckschalter aus");
          break;
        }
        Hochdruckschalter = digitalRead(13);
        spuelung.Spuelvorgang();                // Startet man den Spüllvorgang
        Serial.println("Spüllvorgang startet");
        delay(10000);
        Niederdruckschalter = digitalRead(12);

        if (truutime2 > 3000)
        { // Nach 30 Sekunden Spüllen , in StandbyModus gehen
          standby.StandbyModus();
          Serial.println("Standbay nach Spüllung");
          delay(5000);
          break;
        }
        break;
      }
    }

    else
    {
      standby.StandbyModus();  // Wurde die Wasserentnahme nicht genug lange durchgeführt dann geht man in den Standbymodus
      Serial.println("Wasserentnahme nicht genug lange durchgeführt, standBy");
    }
   
  }

  Serial.println("Niederdruckschalter auf LOW");
}
