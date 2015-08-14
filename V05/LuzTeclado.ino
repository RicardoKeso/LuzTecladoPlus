/*Created by RicardoKeso  - V5*/

#include <IO_Sensors_RKeso.h>
#include <NewTone.h>
#include <IRremote.h>

const int ultrassomEcho = 2;
const int ultrassomPing = 3;
const int movPower = 5;
const int movData = 6;
const int sensorReflex = 7;
const int buzzer = 10;
const int sensorIRremoto = 11;
const int saidaLed = 12;
const int sensorLuz = 5; //analogico 5
const int displayA = 14; //analogico 0
const int displayB = 15; //analogico 1
const int displayC = 16; //analogico 2
const int displayD = 17; //analogico 3

IO_Sensors_RKeso ssr;
IRrecv irrecv(sensorIRremoto);  
decode_results results;

bool paused = false;
bool flagMov = false;
int funcaoAtiva = 0;
int funcaoAtivaOld = 0;

void setup(){
  ssr.Buzzer(buzzer, 2000, 10, 3);
  Serial.begin(9600);
  pinMode(movPower, OUTPUT);
  pinMode(ultrassomPing, OUTPUT);
  pinMode(saidaLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(displayA, OUTPUT);
  pinMode(displayB, OUTPUT);
  pinMode(displayC, OUTPUT);
  pinMode(displayD, OUTPUT);
  
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
    Serial.println(ssr.SensorIRRemote(results));
    ssr.CD4511(displayA, displayB, displayC, displayD, ssr.SensorIRRemote(results));
    ssr.Buzzer(buzzer, 2000, 20, 1);
    irrecv.resume();
  }
  
  /*if(irrecv.decode(&results)){
      funcaoAtivaOld = funcaoAtiva;
      funcaoAtiva = ssr.SensorIRRemote(results);
      ssr.Buzzer(buzzer, 2000, 20, 1);
      if(funcaoAtiva == 1){
        paused = !paused;
      }
  }*/

  if(paused){
    //AlertaMovimento();
    ssr.LedPlaca(0, 0);
  } else {
    LuzTeclado();
  }

  /*switch (funcaoAtiva) {
    case 1:
      if(paused){        
        //ssr.LedPlaca(5, 495);
        ssr.LedPlaca(0, 0);
      } else {
        funcaoAtiva = funcaoAtivaOld;
      }
      break;
    case 2:
      AlertaMovimento();
      break;
    default:
      LuzTeclado();
  }*/
}

void AlertaMovimento(){
  if (ssr.SensorMovimento(movPower, movData)){
//    ssr.Buzzer(buzzer, 2200, 50, 1);
      ssr.Buzzer(buzzer, 2200, 10, 1);
  }
}

void LuzTeclado(){
  if(!ssr.SensorIluminacao(sensorLuz, 50)){
//    if(1){
    if (ssr.SensorMovimento(movPower, movData)){
      ssr.LedPlaca(1, 0);
      int flagDistancia = ssr.SensorDistancia(ultrassomPing, ultrassomEcho, 90, 200);
      digitalWrite(saidaLed, flagDistancia);
    }
  } else {
    digitalWrite(saidaLed, LOW);
  }
}
