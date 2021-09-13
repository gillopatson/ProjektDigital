//#include "Standby.h"


class Wasserentnahme {

    int _Hauptventil;
    int _Drainventil;
    int _Pumpe;
    int _Uvclampe;
    int _Spuelventil;
    int _Niederdruckschalter;
    int _Hochdruckschalter;
  public:

    Wasserentnahme(int Hauptventil, int Drainventil, int Pumpe, int Spuelventil, int Uvclampe,  int Niederdruckschalter, int Hochdruckschalter) {

      _Hauptventil = Hauptventil;
      _Drainventil = Drainventil;
      _Pumpe = Pumpe;
      _Uvclampe = Uvclampe;
      _Spuelventil = Spuelventil;
      _Niederdruckschalter =  Niederdruckschalter;
      _Hochdruckschalter = Hochdruckschalter;

      pinMode(_Hauptventil, OUTPUT);
      pinMode( _Drainventil, OUTPUT);
      pinMode(_Pumpe, OUTPUT);
      pinMode(_Uvclampe, OUTPUT);
      pinMode(_Spuelventil, OUTPUT);
      pinMode(_Niederdruckschalter , INPUT);
      pinMode(_Hochdruckschalter, INPUT);
    }

    void Entnahme() {
      
        digitalWrite (_Hauptventil, HIGH); //Hauptventil auf
        digitalWrite (_Drainventil, HIGH); //Drainventil auf
        digitalWrite (_Pumpe, HIGH); //Pumpe an
        digitalWrite (_Uvclampe, HIGH); // Uvclampe an
        digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
        delay(5000);
        Serial.println("START WASSERENTNAHME");



      _Niederdruckschalter = digitalRead(12);


      while (_Niederdruckschalter == HIGH) {
        _Niederdruckschalter = digitalRead(12);
        if (_Niederdruckschalter == LOW) {
          digitalWrite (_Hauptventil, LOW); //Hauptventil auf
          digitalWrite (_Drainventil, LOW); //Drainventil auf
          digitalWrite (_Pumpe, LOW); //Pumpe an
          digitalWrite (_Uvclampe, LOW); // Uvclampe an
          digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
          Serial.println("Wasserentnahme durch NDS HIGH abgebrochen");
          delay(5000);
          break;
        }
        _Hochdruckschalter = digitalRead(13);
        if (_Hochdruckschalter == LOW) {
//          digitalWrite (_Hauptventil, LOW); //Hauptventil auf
//          digitalWrite (_Drainventil, LOW); //Drainventil auf
//          digitalWrite (_Pumpe, LOW); //Pumpe an
//          digitalWrite (_Uvclampe, LOW); // Uvclampe an
//          digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
          Serial.println("Wasserentnahme durch HDS LOW abgebrochen");
          delay(5000);
          break;
        }

       

      }
    }
};
