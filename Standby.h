

class Standby{
  
  int _Hauptventil;
  int _Drainventil;
  int _Pumpe;
  int _Uvclampe;
  int _Spuelventil;

  public:

  Standby(int Hauptventil, int Drainventil, int Pumpe, int Spuelventil, int Uvclampe){  // Konstruktor von der Class

_Hauptventil = Hauptventil;
_Drainventil = Drainventil;
_Pumpe = Pumpe;
_Uvclampe = Uvclampe;
_Spuelventil = Spuelventil;

pinMode(_Hauptventil, OUTPUT);
pinMode( _Drainventil, OUTPUT);
pinMode(_Pumpe, OUTPUT);
pinMode(_Uvclampe, OUTPUT); 
pinMode(_Spuelventil, OUTPUT);
  }

  void StandbyModus(){

     digitalWrite (_Hauptventil, LOW);
     digitalWrite (_Drainventil, LOW); 
     digitalWrite (_Pumpe, LOW); //Pumpe an
   digitalWrite (_Uvclampe, LOW); // Uvclampe an
     digitalWrite (_Spuelventil, LOW); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
    
    }

 };
