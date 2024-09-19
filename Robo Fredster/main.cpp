#include <Arduino.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

/*
Por padrão, o Dabble defini as pinos de comunicação como a (3 RX e 2 TX), se quiser
especificar pinos diferentes é necessário incluir no código:

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(5, 7);  // RX, TX
...
*/

//Definindo portas da ponte H
int  A_1A = 5; // Controle de Direção Motor A
int  A_1B = 6; // Controle de Velocidade Motor A via PWM
int  B_1A = 8; // Controle de Direção Motor B
int  B_1B = 9; // Controle de Velocidade Motor A via PWM

// Declaração das funções
void Frente();
void Atras();
void Esquerda();
void Direita();
void Parado();    

void setup() {
//Definindo os pinos como Saida
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);                                                                    
  pinMode(B_1B, OUTPUT);
  
  Serial.begin(250000);      
  Dabble.begin(9600);
}

void loop() { 
  Dabble.processInput();          
  Serial.print ("KeyPressed: ");
  Parado();

//Frente   
if(GamePad.isUpPressed()){
 Serial.print("UP");
 Frente();

}

//Atras
else if(GamePad.isDownPressed()){

 Serial.print("DOWN");
 Atras();

}

//Esquerda
else if(GamePad.isLeftPressed()){

 Serial.print("Left");
 Esquerda(); 

}

//Direita
else if(GamePad.isRightPressed()) {

 Serial.print("Right");
 Direita(); 

}

//Parado
  else{

 Parado();

  }   
}

void Frente() {
  digitalWrite(A_1A,LOW);  //Atrás
  digitalWrite(A_1B,HIGH); //Frente
  digitalWrite(B_1A,LOW);  //Atrás
  digitalWrite(B_1B,HIGH); //Frente
}
      
void Atras() {
  digitalWrite(A_1A,HIGH);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,HIGH);
  digitalWrite(B_1B,LOW);
}
      
void Esquerda() {
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,HIGH);
  digitalWrite(B_1A,HIGH);
  digitalWrite(B_1B,LOW);    
}
      
void Direita() {
  digitalWrite(A_1A,HIGH);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,HIGH);  
}
      
void Parado() {
  digitalWrite(A_1A,LOW);
  digitalWrite(A_1B,LOW);
  digitalWrite(B_1A,LOW);
  digitalWrite(B_1B,LOW);  
}


