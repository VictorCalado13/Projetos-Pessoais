// Define os pinos de utilização do Driver L298.
const int motorA1  = 9;    // Pin  5 of L293.
const int motorA2  = 3;    // Pin  6 of L293.
const int motorB1  = 11;   // Pin 10 of L293.
const int motorB2  = 10;   // Pin 9 of L293.
 
const int BTState = 2;    // Define o Pino 2 como o pino de comunicação do Bluetooth.
 
// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;   // Define velocidade padrão 0 < x < 255.
char state;
 
void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(BTState, INPUT);
 
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  Serial.println("-- USINAINFO --");
  Serial.println("Carrinho Arduino controlado por Smartphone");
}
 
void loop() {
  // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }
 
  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }
 
  // Altera a velocidade de acordo com valores especificados.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }
 
  if (state != 'S') {
    Serial.println(state);
  }
 
  // Se o estado recebido for igual a 'B', o carro se movimenta para Esquerda.
  if (state == 'B') {
    Serial.println(state);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);                        //CERTO
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }
 
 
  else if (state == 'F') { // Se o estado recebido for igual a 'F', o carro se movimenta para Direita.
    Serial.println(state);
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);                                 //CERTO
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }
 
  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para Frente.
    Serial.println(state);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);                                //CERTO
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para Tras.
    Serial.println(state);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);                                    //CERTO 
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    Serial.println(state);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);                                     //CERTO
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }
 
}