

class Spuelung{
  
   int _Hauptventil;
  int _Drainventil;              // Variable die in meiner Klassen benutzt werden
  int _Pumpe;
  //int _Uvclampe;
  int _Spuelventil;
  
 public:

  Spuelung(int Hauptventil, int Drainventil, int Pumpe, int Spuelventil ){            // Konstruktor

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
  
 void Spuelvorgang(){
  
      digitalWrite (_Hauptventil, LOW); //Hauptventil auf
      digitalWrite (_Drainventil, HIGH); //Drainventil auf
      digitalWrite (_Pumpe, LOW); //Pumpe an
   // digitalWrite (_Uvclampe, LOW); // Uvclampe an
      digitalWrite (_Spuelventil, HIGH); //Spülventil = zu   // der Spüllventil wird eingekeitet wenn Druck = 3 Bar
      
       delay(2000);


delay(2000);


}

  
};
