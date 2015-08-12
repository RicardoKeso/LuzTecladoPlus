/*Created by RicardoKeso  - V1*/

#include <IO_Sensors_RKeso.h>

IO_Sensors_RKeso ssr;

const int ultrassomEcho = 2;
const int ultrassomPing = 3;
const int movPower = 5;
const int movData = 6;
const int saidaLed = 12;
const int sensorLuz = 3; //analogico

void setup(){
  Serial.begin(9600);
  pinMode(movPower, OUTPUT);
  pinMode(ultrassomPing, OUTPUT);
  pinMode(saidaLed, OUTPUT);
  
  pinMode(movData, INPUT);
  pinMode(ultrassomEcho, INPUT);
}

void loop(){   
  Luzteclado();
}

void Luzteclado(){
  if(ssr.SensorIluminacao(sensorLuz, 50)){
    if (ssr.SensorMovimento(movPower, movData)){
      ssr.LedPlaca(1, 0);
      int flagDistancia = ssr.SensorDistancia(ultrassomPing, ultrassomEcho, 90, 200);
      ssr.Rele(saidaRele, flagDistancia);
    }
  } else {
    ssr.Rele(saidaRele, 0);
  }
}
