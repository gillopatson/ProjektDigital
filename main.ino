 /*Kleine Eklärung über die Rolle der Variablen anzahlWasserEntnahmeDurchführung,  anazahlSpuelungNachWasserentnahme, c, holidayController und  spuelungNachWasserentnahmeController
  * Die Variablen anzahlWasserEntnahmeDurchführung und  anazahlSpuelungNachWasserentnahme dienen zur Überprüfung ob man die Wasserennahme und Spülung nach Wasserentnahme durchgeführt wurden.
 *  Wenn eine von diesen beiden Variablen inkrementiert wurden, dann weißt man dass die ensprechende Vorgänge durchgeführt wurden.
 *  Wenn anzahlWasserEntnahmeDurchführung und anazahlSpuelungNachWasserentnahme nicht inkrementiert wurden (holidayController = anzahlWasserEntnahmeDurchführung +  anazahlSpuelungNachWasserentnahme = 0) und das System seit fünf Tagen in Standby Modus ist(Holiday), dann soll die Spülung stattfinden.
 *  Wenn anzahlWasserEntnahmeDurchführung und anazahlSpuelungNachWasserentnahme inkrementiert wurden (holidayController = anzahlWasserEntnahmeDurchführung +  anazahlSpuelungNachWasserentnahme != 0 ) und die Zeit zwischen das 
 *  Ende der Wasserentnahme und die danach länge des Standby größer funf Tagen, dann soll die Spülung stattfinden
 *  Die Variable  spuelungNachWasserentnahmeController link die Wasserentnahme und der danach spüllvorang. Manchmal geht das System nach der HolidaySpülung im programm Teil der Spülung nach Wasserentnahme. Um die
 *  beiden zu unterscheiden benutzt man die Link Variable  spuelungNachWasserentnahmeController. Wenn  spuelungNachWasserentnahmeController inkrementiert wurde, weißt man dass, eine Wasserentnahme durchgeführt wurde, dann kann die Spülung nach Wasserentnahme durchgeführt 
 *  werden.
 *  
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
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

unsigned long  timeStartWasserEntnahme;
unsigned long timeAfterWasserEntnahme;                           
unsigned long truutime1;
unsigned long truutime2;
unsigned long truutime3;
unsigned long HollidayTime1;                                    // timeStartWasserEntnahme
unsigned long HollidayTime2 = 0;

int anzahlWasserEntnahmeDurchfuehrung = 0;
int  anazahlSpuelungNachWasserentnahme = 0;
int spuelungNachWasserentnahmeController = 0;
int c = 0;
int holidayController, e;

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

    holidayController = anzahlWasserEntnahmeDurchfuehrung +  anazahlSpuelungNachWasserentnahme ;     // Überprüfung für Urlaubschaltung
    // Einfügen von der neuen Funktion
    if (holidayController == 0 & HollidayTime1 - HollidayTime2 > 7000 )  // Überprüfung wie lange die Urlaubszeit gedauert hat und dass in dieser Zeit keine Wasserentnahme und Spülung nach Wasserentnahme durchgeführt wurde
    {
      Serial.println("5 Tagen Urlaub, Spülung durchführen");

      spuelung.Spuelvorgang(); // Wenn lange nicht da war, wird der Spuelvorgang durchgeführt
      HollidayTime2 = millis();
      anzahlWasserEntnahmeDurchfuehrung = 0;
       anazahlSpuelungNachWasserentnahme = 0;

    //  break;
    }

    else
    {
       Hochdruckschalter = digitalRead(13);  

      if (holidayController != 0 & HollidayTime1 - timeAfterWasserEntnahme > 7000 & Hochdruckschalter == LOW)         // Hier wurde eine Wasserentnehme durchgeführt, man überprüft die Zeit seitdem die Wasserentnahme zum letzten mal durchgeführt wurde             
      {
        Serial.println("9 Tagen Urlaub, Spülung durchführen");

        spuelung.Spuelvorgang(); // Wenn lange nicht da war, wird der Spuelvorgang durchgeführt
        
        HollidayTime2 = millis();
        anzahlWasserEntnahmeDurchfuehrung = 0;
         anazahlSpuelungNachWasserentnahme = 0;

       // break;
      }

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
       spuelungNachWasserentnahmeController =  spuelungNachWasserentnahmeController + 1;
            anzahlWasserEntnahmeDurchfuehrung = anzahlWasserEntnahmeDurchfuehrung + 1;
      truutime1 = millis();
      Hochdruckschalter = digitalRead(13);
      wasserentnahme.Entnahme();           // Wasserentnahme wird gestartet
      //Serial.println("Wasserentnahmen");
      //delay(3000);
      
      Niederdruckschalter = digitalRead(12);
      if (Niederdruckschalter == LOW) {
        Serial.println("break condition zum abbruch weil niederdruckschalter aus");
        break;
      }
      
      Hochdruckschalter = digitalRead(13);
      if (Hochdruckschalter == LOW)  // Bedingung zum Abbruch der Schleife
      {
        Serial.println("Nach der Wasserentnahme ist Hochdruckschalter LOW, Wasserentnahme beendet");
        timeAfterWasserEntnahme = millis();
        break;
      }
      timeAfterWasserEntnahme = millis();
    }

     Niederdruckschalter = digitalRead(12);
    if (Niederdruckschalter == LOW) {
      Serial.println("Am Ausgang von der Wasserentnahme hatten wir NDS LOW");
      break;
    }



    Serial.println(truutime2);
    if (timeAfterWasserEntnahme -  timeStartWasserEntnahme > 5000 &  spuelungNachWasserentnahmeController!= 0)       // Überprüfung ob Wasserentnahme genug lange durchgeführt wurde 
    { 

       spuelungNachWasserentnahmeController = 0;
       Serial.println("Die bedingung für Spülung hat geklappt");
       anazahlSpuelungNachWasserentnahme =  anazahlSpuelungNachWasserentnahme + 1;
      while (Hochdruckschalter == LOW)
      { // Die Wasseerentnahme wurde genug lange durchgeführt
        if (Niederdruckschalter == LOW) {
          Serial.println("Die Wasserentnahme wurde genug lange durchgeführt und jetzt wollen wir spülung durchführen aber NDS ist LOW");
          break;
        }
        Hochdruckschalter = digitalRead(13);
        spuelung.Spuelvorgang();                // Startet man den Spüllvorgang
         Serial.println(" es war Spüllvorgang nach Wasserentnahme");
         
        Niederdruckschalter = digitalRead(12);
        if (Niederdruckschalter == LOW) {
          Serial.println("Am Ausgang von der Spülung  hatten wir NDS LOW");
          break;
        }

        Hochdruckschalter = digitalRead(13);
        if (Hochdruckschalter == HIGH)
        {
          Serial.println("Der Hochschalter wurde während der Spülung aktiviert");
        }

       
        delay(3000);
       Hochdruckschalter = digitalRead(13);
        truutime3 = millis();
        if (truutime3 - timeAfterWasserEntnahme > 3000 & Hochdruckschalter == LOW)
        { // Nach 30 Sekunden Spüllen , in StandbyModus gehen
          standby.StandbyModus();
          Serial.println("Nach wasserentnahme und Spülung geht man in StandBY");
          delay(5000);
          break;
        }
        break;
      }
    }

    else
    {
      standby.StandbyModus();  // Wurde die Wasserentnahme nicht genug lange durchgeführt dann geht man in den Standbymodus
      Serial.println("Wasserentnahme nicht genug lange durchgeführt oder nur UrlaubSpülung durchgeführt, standBy");
    }

  }

  Serial.println("Niederdruckschalter auf LOW");
   standby.StandbyModus();
  delay(5000);
}
