

class Spuelung {

    int _Hauptventil;
    int _Drainventil;              // Variable die in meiner Klassen benutzt werden
    int _Pumpe;
    int _Uvclampe;
    int _Spuelventil;
    int _Niederdruckschalter;
    int _Hochdruckschalter;
    unsigned long _counter;
  public:

    Spuelung(int Hauptventil, int Drainventil, int Pumpe, int Spuelventil, int Uvclampe, int Niederdruckschalter, int Hochdruckschalter, int counter ) {           // Konstruktor

      _Hauptventil = Hauptventil;
      _Drainventil = Drainventil;
      _Pumpe = Pumpe;
      _Uvclampe = Uvclampe;
      _Spuelventil = Spuelventil;
      _Niederdruckschalter =  Niederdruckschalter;
      _Hochdruckschalter = Hochdruckschalter;
      _counter = counter;

      pinMode(_Hauptventil, OUTPUT);
      pinMode( _Drainventil, OUTPUT);
      pinMode(_Pumpe, OUTPUT);
      pinMode(_Uvclampe, OUTPUT);
      pinMode(_Spuelventil, OUTPUT);
      pinMode(_Niederdruckschalter, INPUT);
      pinMode(_Hochdruckschalter, INPUT);

    }

    void Spuelvorgang() {
      _counter = millis();
      _Niederdruckschalter = digitalRead(12);
      while (_Niederdruckschalter == HIGH) {

        digitalWrite (_Hauptventil, LOW); //Hauptventil auf
        digitalWrite (_Drainventil, HIGH); //Drainventil auf
        digitalWrite (_Pumpe, LOW); //Pumpe an
        digitalWrite (_Uvclampe, LOW); // Uvclampe an
        digitalWrite (_Spuelventil, HIGH); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
        Serial.println("OKAYYYY");
        delay(5000);





        _Niederdruckschalter = digitalRead(12);
        if (_Niederdruckschalter == LOW) {
          digitalWrite (_Hauptventil, LOW); //Hauptventil auf
          digitalWrite (_Drainventil, LOW); //Drainventil auf
          digitalWrite (_Pumpe, LOW); //Pumpe an
          digitalWrite (_Uvclampe, LOW); // Uvclampe an
          digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
          Serial.println("break condition aus Spülung N");
          break;
        }
        _Hochdruckschalter = digitalRead(13);
        if (_Hochdruckschalter == HIGH) {
          digitalWrite (_Hauptventil, HIGH); //Hauptventil auf
          digitalWrite (_Drainventil, HIGH); //Drainventil auf
          digitalWrite (_Pumpe, HIGH); //Pumpe an
          digitalWrite (_Uvclampe, HIGH); // Uvclampe an
          digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
          Serial.println("break condition aus Spülung H");
          delay(8000);
          break;
        }


        if (_counter > 5000) {
          Serial.println("Die Spülung hat genug lange gedauert");
          break;
        }

      }

    }


};
