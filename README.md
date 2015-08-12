# LuzTeclado

/*
funcoes: 
1-pausar o circuito/sistema utilizado o RC ou o SReflexão
2-a luz do teclado so acende se esta funcao estiver ativa, 
  se a iluminação do ambiente estiver baixa, 
  se o sensor de movimento ativar o sensor ultrassom
  e se o ultrassom detectar a distancia minima especificada
  (fonte externa para ligar os leds atraves do optoacoplador)
3-acender a luz ambiente atraves do sensor de movimento utilizando rele
4-acender a luz ambinete atraves do RC utilizando rele
5-ligar cooler(vibracall(optoacoplador)) caso a temperatura se eleve (sensor LM35)
*/

COMPONENTES:
Arduino mini ou nano;
Light Dependent Resistor (LDR);
Sensor de movimento;
Sensor ultrassonico;
Rele 5v 1ch;
Sensor IR de reflexao;
Receptor IR
2x optoacoplador
fonte de carregador de celular 5v
leds

LIGAÇÃO DOS COMPONENTES:

fotosensor: 
  T1 em +5;
  T2 em A3 e em T1 do r12k;
  T2 do r12k em GND.
  
sensorDeMovimento: 
  GND em GND;
  DATA em T1 do r12k e em D6;
  VCC em T2 do r12k e em D5.
  
ultrassom: 
  VCC em +5;
  GND em GND;
  TRIG em D3;
  ECHO em D2.
  
transistor c549c: (not logico para o rele, caso necessário)
  COLETOR ligado no T2 do RELE e em T1 do r12k(1);
  T2 do r12k(1) ligado em +5;
  BASE ligada em T1 do r12k(2);
  T2 do r12k(2) ligado em D12;
  EMISSOR ligado em T1 do r150;
  T2 do r150 ligado em gnd.
  
rele: (O RELÊ QUE UTILIZO, É ACIONADO COM SINAL LÓGICO BAIXO)
  T1 ligado em +5;
  T2 ligado no COLETOR do transistor; 
  T3 ligado em GND.
  
sensorOpticoDeReflexao: 
  catodo do emissor e do receptor ligados em GND;
  anodo do emissor em T1 do r150;
  T2 do r150 +5;
  anodo do receptor em T1 do r12k e em D7;
  T2 do r12k em +5.
  
sensorIR_remoto:
  T1 em D11;
  T2 em GND;
  T3 em T1 r150;
  T2 r150 em +5.
  
buzzer:
  T+ em T1 r150;
  T2 r150 em D10;
  T- em GND;

/*
NOTAS:
 - usar led ou display para mostrar o status
 - Ha um conflito entre a funcao tone() e o IRremoteInt.h pois usam a mesma chamada de funcao timer2.
 - Para resolver este problema, utilizo a biblioteca NewTone chamando a função NewTone() no lugar de tone().
 - Para não utilizar o transistor, basta inverter os sinais de entrada do relê, e ligar o T2 do relê em D12.
 - O relê consome muita energia e pode afetar outros dispositivos ou sensores, como o LDR.
*/
