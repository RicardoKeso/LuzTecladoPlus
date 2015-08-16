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
Sensor IR de reflexao;
Receptor IR com ControleRemoto;
fonte de carregador de celular 5v;
leds(para iluminar o teclado)
optoacoplador ou Rele 5v 1ch mais um Transistor c549c;
display de 1 dig e 7 seguimentos mais um Decoder CD4511 ou 74HC595;

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
  
transistor c549c: (not logico para o rele, SE UTILIZADO)
  COLETOR ligado no T2 do RELE e em T1 do r12k(1);
  T2 do r12k(1) ligado em +5;
  BASE ligada em T1 do r12k(2);
  T2 do r12k(2) ligado em D12;
  EMISSOR ligado em T1 do r150;
  T2 do r150 ligado em gnd.
  
rele: (o relê utilizado, é acionado com sinal lógico baixo, por isso o transistor)
  T1 ligado em +5;
  T2 ligado no COLETOR do transistor; 
  T3 ligado em GND.
  
optoacoplador: (SE UTILIZADO, no lugar do relê com transistor)
  ânodo ligado em D12;
  catodo ligado em T1 do r150;
  T2 do r150 ligado em GND;
  coletor ligado T1 r150;
  T2 r150 ligado em +5;
  emissor ligado em T1 do LedDoTeclado;
  T2 do LedDoTeclado ligado em GND;

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

display1dig:
  T1 ligado em T1 r150(1);
  T2 ligado em T1 r150(2);
  T4 ligado em T1 r150(3);
  T5 ligado em T1 r150(8); (não utilizado com CD4511)
  T6 ligado em T1 r150(4);
  T7 ligado em T1 r150(5);
  T9 ligado em T1 r150(6);
  T10 ligado em T1 r150(7);
  T3 ou T8 ligado em GND se CATODO, comum ou ligado em +5 se ANODO comum;

cd4511: (utiliza 4 portas)(se utilizar portas analógicas, antes converte-las para digitais)
  T1, T2, T6, T7 ligados em 15(A1), 16(A2), 17(A3), 14(A0) respectivamente;
  T3, T4, T16 ligados em +5;
  T5, T8 ligados em GND;
  T9 ligado em T2 r150(1) TDisplay 1;
  T10 ligado em T2 r150(2) TDisplay 2;
  T11 ligado em T2 r150(3) TDisplay 4;
  T12 ligado em T2 r150(4) TDisplay 6;
  T13 ligado em T2 r150(5) TDisplay 7;
  T14 ligado em T2 r150(7) TDisplay 9;
  T15 ligado em T2 r150(6) TDisplay 10;

74hc595: (utiliza 3 portas)(se utilizar portas analógicas, antes converte-las para digitais)
  T11, T12, T14 ligados em 15(A1), 14(A0), 16(A2) respectivamente;
  T10, T16 ligados em +5;
  T8, T13 ligados em GND;
  T1 ligado em T2 r150(4) TDisplay 6;
  T2 ligado em T2 r150(3) TDisplay 4;
  T3 ligado em T2 r150(2) TDisplay 2;
  T4 ligado em T2 r150(1) TDisplay 1;
  T5 ligado em T2 r150(7) TDisplay 9;
  T6 ligado em T2 r150(6) TDisplay 10;
  T7 ligado em T2 r150(8) TDisplay 5;
  T15 ligado em T2 r150(5) TDisplay 7;

/*
NOTAS:
 - usar led ou display para mostrar o status
 - Ha um conflito entre a funcao tone() e o IRremoteInt.h pois usam a mesma chamada de funcao timer2.
 - Para resolver este problema, utilizo a biblioteca NewTone chamando a função NewTone() no lugar de tone().
 - Para não utilizar o transistor, basta inverter os sinais de entrada do relê, e ligar o T2 do relê em D12.
 - O relê consome muita energia e pode afetar outros dispositivos ou sensores, como o LDR.
 - Para reduzir o consumo de energia, utilizo o optoacoplador.(Atenção com o limite de carga máxima do emissor!)
*/
