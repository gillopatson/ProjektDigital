//
//#include "Wasserentnahme.h"
//#include "Standby.h"
//#include "Spuelung.h"
//
//const byte interruptDesaktivierungPin = 2;
//
//int Hochdruckschalter = 13;
//int Sign = 12;
//int Signalisierung = 11;
//int Spuelventil = 5;
//int Drainventil = 7;
//int Pumpe = 9;
//int Uvclampe = 8;
//int Hauptventil = 6;
//unsigned long truutime1;
//unsigned long truutime2;
//int Niederdruckschalter = 12;
//
//Wasserentnahme wasserentnahme( Hauptventil, Drainventil,  Pumpe , Uvclampe, Spuelventil );  // Kontruktor
//Standby standby(Hauptventil, Drainventil,  Pumpe , Uvclampe, Spuelventil);
//Spuelung spuelung(Hauptventil, Drainventil,  Pumpe , Uvclampe, Spuelventil);
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(Hochdruckschalter , INPUT);
//  pinMode(Niederdruckschalter, INPUT);
//  pinMode(Signalisierung, OUTPUT);
//
//  attachInterrupt(digitalPinToInterrupt(interruptDesaktivierungPin), ISR_DesaktivierungAnlange, RISING); // Interrupt damit man zum StandbyModus geht
//
//}
//
//
//void loop() {
//
//
//
//
//  delay(1000);
//
//  switch (Niederdruckschalter) {
//    case HIGH:
//      if (Hochdruckschalter  == HIGH) {                    // Überprüfung ob der Hochdruckschalter gedrückt wurde
//        Serial.println("Hochdruckschalter eingechaltet");
//
//        //digitalWrite(Signalisierung, HIGH);   // Signalisierung zur Wasserentnahme
//
//        wasserentnahme.Entnahme();           // Wasserentnahme wird gestartet
//        Serial.println("Wasserentnahme");
//        truutime1 = millis(); //start
//        delay(1);
//        digitalWrite(Signalisierung, HIGH);   // Signalisierung zur Wasserentnahme
//
//        //Serial.println("Signalisierung zur Wasserentnahme ausgeschaltet");
//
//        Signalisierung =  digitalRead(11);
//
//        if (truutime1 > 1) {          // Überprüfung ob Wasserentnahme genug lange durchgeführt wurde
//          spuelung.Spuelvorgang();
//          Serial.println("Spüllvorgang startet");
//
//
//          for (int x = 0; x < 1; x++) {
//            // delay(2000);
//            if (Signalisierung == HIGH) {
//              Serial.println("Hochdruckchalter wieder geschaltet beim Spüllvorgang");
//              wasserentnahme.Entnahme();
//              Serial.println("Wasserentnahme beim Spüllvorgang eingeschaltet");
//
//              break;
//            }
//          }
//
//        }
//
//        else {
//          standby.StandbyModus();  // Wurde die Wasserentnahme nicht genug lange durchgeführt dann geht man auf dem Standbymodus
//          Serial.println("Wasserentnahme nicht genug lange durchgeführt, standBy");
//        }
//
//      }
//
//      else {
//        standby.StandbyModus();   // Wurde der Hochdruckschalter nicht gedrückt dann geht man auf dem Standbymodus
//        Serial.println("StandbyModus wegen Hochdruckschalter");
//      }
//
//      break;
//
//    case LOW:
//      standby.StandbyModus();
//      Serial.println("StandbyModus wegen Niederdruckschalter");
//      break;
//
//  }
//
//
//}
//
//
//
//
//
//
//
//
//
//void ISR_DesaktivierungAnlange() {   // Interrupt für das Standbymodus(der kann überall aufgerufen werden)
//  Serial.println("Durchführung der Interrupt zum ");
//  digitalWrite (Hauptventil, LOW); //Hauptventil auf
//  digitalWrite (Drainventil, LOW); //Drainventil auf
//  digitalWrite (Pumpe, LOW); //Pumpe an
//  digitalWrite (Uvclampe, LOW); // Uvclampe an
//  digitalWrite (Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
//  digitalWrite(Signalisierung, LOW);
//
//
//}
//
//
//
//
//

#include "Wasserentnahme.h"
#include "Standby.h"
#include "Spuelung.h"


//const byte interruptDesaktivierungPin = 2;

int Niederdruckschalter = 12;
int Hochdruckschalter = 13;
int Spuelventil = 3;
int Drainventil = 4;
int Pumpe = 6;
//int Uvclampe = 5;
int Hauptventil = 5;

unsigned long truutime1;
unsigned long truutime2;


Wasserentnahme wasserentnahme( Hauptventil, Drainventil,  Pumpe , Spuelventil );  // Kontruktor
Standby standby(Hauptventil, Drainventil,  Pumpe , Spuelventil);
Spuelung spuelung(Hauptventil, Drainventil,  Pumpe , Spuelventil);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(Hochdruckschalter , INPUT);
  pinMode(Niederdruckschalter, INPUT);


}

void loop() {
  
  Niederdruckschalter = digitalRead(12);   // Niederdruckschalter wird am Pin 12 gelesen
  Hochdruckschalter = digitalRead(13);    // Hochdruchschalter wird am Pin 13 gelesen

  delay(1000);
truutime1 = millis();


  if(Niederdruckschalter == LOW) {  // Zur überprüfung ob der Niederdruckschalter HIGH oder LOW ist
                        // Niederdruckschalter ist HIGH

      Serial.println("Niederdruckschalter HIGH");

      while (Hochdruckschalter == HIGH)
        {
           Hochdruckschalter = digitalRead(13); 
          wasserentnahme.Entnahme();           // Wasserentnahme wird gestartet
                  Serial.println("Wasserentnahme");
                  delay(50);
          if (Hochdruckschalter == LOW)  // Bedingung zum Abbruch der Schleife
          {              
          Serial.println("Hochdruckschalter LOW");
          break;
          }
        }



//      for (int x = 0; x < 10; x++)        //Hier müsste die Wasserentnahme zuerst gestartet werden. Der Wasserentnahme Zustand wird dann mit der "for" schleife aufrechterhalten bis zur abbrechbedingung.
//      {                // For Schleife für Durchführung der Wasserentnahme
//        Hochdruckschalter = digitalRead(13); //es fehlt eine zuordnung des gelesenen Zustandes. so wird nur der pin gelesen ohne auszuführende funktion 
//        delay(2000);
//        if (Hochdruckschalter == LOW) 
//          {               // Bedingung zum Abbruch der Schleife
//          Serial.println("Hochdruckschalter LOW");
//          break;
//          }
//        wasserentnahme.Entnahme();           // Wasserentnahme wird gestartet
//        Serial.println("Wasserentnahme");
//
//      }
  truutime2 = millis();
      Serial.println("Wasserentnahme beendet");
    
      if (truutime2-truutime1 > 2000) 
      {                       // Überprüfung ob Wasserentnahme genug lange durchgeführt wurde
      
        while (Hochdruckschalter == LOW) 
        {        // Die Wasseerentnahme wurde genug lange durchgeführt
           Hochdruckschalter = digitalRead(13); 
          spuelung.Spuelvorgang();                // Startet man den Spüllvorgang
          Serial.println("Spüllvorgang startet");
          if (truutime2 > 3000) 
          {      // Nach 30 Sekunden Spüllen , in StandbyModus gehen
            standby.StandbyModus();
            Serial.println("Standbay nach Spüllung");
            break;
          }
          break;
        }
      }

      else 
      {
        standby.StandbyModus();  // Wurde die Wasserentnahme nicht genug lange durchgeführt dann geht man auf dem Standbymodus
        Serial.println("Wasserentnahme nicht genug lange durchgeführt, standBy");
      }

   
  }

    else{     // Niederdruckschalter LOW, man geht auf standbymodus

      standby.StandbyModus();
       Serial.println("Niederdruckschalter aus, standBy");
  }



}
