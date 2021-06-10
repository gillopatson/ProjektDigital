


class Wasserentnahme{

  int _Hauptventil;
  int _Drainventil;
  int _Pumpe;
 // int _Uvclampe;
  int _Spuelventil;

  public:

  Wasserentnahme(int Hauptventil, int Drainventil, int Pumpe, int Spuelventil){

_Hauptventil = Hauptventil;
_Drainventil = Drainventil;
_Pumpe = Pumpe;
//_Uvclampe = Uvclampe;
_Spuelventil = Spuelventil;

pinMode(_Hauptventil, OUTPUT);
pinMode( _Drainventil, OUTPUT);
pinMode(_Pumpe, OUTPUT);
//pinMode(_Uvclampe, OUTPUT); 
pinMode(_Spuelventil, OUTPUT);
  }

void Entnahme(){
         digitalWrite (_Hauptventil, HIGH); //Hauptventil auf
         digitalWrite (_Drainventil, HIGH); //Drainventil auf
         digitalWrite (_Pumpe, HIGH); //Pumpe an
      // digitalWrite (_Uvclampe, HIGH); // Uvclampe an
         digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
}

  
};
