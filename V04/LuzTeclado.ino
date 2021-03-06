/*Created by RicardoKeso  - V4*/

#include <IO_Sensors_RKeso.h>
#include <IRremote.h>
#include <NewTone.h>

const int ultrassomEcho = 2;
const int ultrassomPing = 3;
const int movPower = 5;
const int movData = 6;
const int sensorReflex = 7;
const int buzzer = 10;
const int sensorIRremoto = 11;
const int saidaLed = 12;
const int sensorLuz = 3; //analogico

bool paused = false;
IO_Sensors_RKeso ssr;
IRrecv irrecv(sensorIRremoto);  
decode_results results;

void setup(){
  ssr.Buzzer(buzzer, 2000, 10, 3);
  Serial.begin(9600);
  pinMode(movPower, OUTPUT);
  pinMode(ultrassomPing, OUTPUT);
  pinMode(saidaLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  irrecv.enableIRIn();
  
  pinMode(movData, INPUT);
  pinMode(ultrassomEcho, INPUT);
  pinMode(sensorReflex, INPUT);
}

void loop(){  
 
  if(!digitalRead(sensorReflex)){
    paused = !paused;
    ssr.Buzzer(buzzer, 2000, 20, 1);
    while(!digitalRead(sensorReflex)){}
  }
    
  if(irrecv.decode(&results)){
    paused = !paused;
    ssr.Buzzer(buzzer, 2000, 20, 1);
    irrecv.resume();
  }
  
  if(paused){ 
    //ssr.LedPlaca(5, 495);
    //colocar outro metodo de status, sem dalay
    ssr.LedPlaca(0, 0);
  } else {
    LuzTeclado();
  }
}

void LuzTeclado(){
  if(ssr.SensorIluminacao(sensorLuz, 50)){
    if (ssr.SensorMovimento(movPower, movData)){
      ssr.LedPlaca(1, 0);
      int flagDistancia = ssr.SensorDistancia(ultrassomPing, ultrassomEcho, 90, 200);
      digitalWrite(saidaLed, flagDistancia);
    }
  } else {
    digitalWrite(saidaLed, LOW);
  }
}
