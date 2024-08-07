//Implementação de três tarefas
TaskHandle_t tarefa1;
TaskHandle_t tarefa2;
TaskHandle_t tarefa3;

//Pinagem dos Leds
int ledVermelho = 32;//Pino GPIO 32
int ledAzul = 33;//Pino GPIO 33

//Pinagem VCC = 5V
//Pinagem GND = GND
//Pinagem TRIG e ECHO do Sensor HC-SR04
int trigPin = 26;//Pino GPIO 26
int echoPin = 27;//Pino GPIO27

void setup() {

  Serial.begin(115200);//Configurando a taxa de comunicação com Monitor Serial em bits p/ segundo

  //Pinos dos Leds
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  //Pinos TRIG e ECHO
  pinMode(trigPin, OUTPUT);//Para o Esp esse pino é uma saida e p/ o sensor é uma entrada
  pinMode(echoPin, INPUT);//Para o Esp esse pino é um entrada e p/ o sensor é uma saida

  //Criação das tarefas apartir da função xTaskCreatePinnedToCore()
  //xTaskCreatePinnedToCore(nome da função,"tarefa",tamanho da pilha, Parametros, prioridade, alteração manual, núcleo);
  xTaskCreatePinnedToCore(blinkVermelho, "tarefa1", 10000, NULL, 0, &tarefa1, 0);
  xTaskCreatePinnedToCore(blinkAzul, "tarefa2", 10000, NULL, 1, &tarefa2, 1);
  xTaskCreatePinnedToCore(sensorHC, "tarefa3", 10000, NULL, 2, &tarefa3, 1);
}

void loop() {
  if (Serial.available() > 0) {//Se tiver algo no Monitor Serial
    char c = Serial.read();//Função ler Monitor Serial

    if (c == 'a') {//Se no monitor Serial tiver algo que no caso é 'a'

      vTaskSuspend(tarefa1);//A tarefa1 "led vermelho" será interrompida

    } else if (c == 'b') {//Se no monitor Serial tiver algo que no caso é 'b'

      vTaskResume(tarefa1);//A tarefa1 "led vermelho" será reestabelecida
    }
  }
}
//Declarando função blink com uma função de chamada "void" com um ponteiro "*pvParameters"
void blinkVermelho(void *pvParameters) {

  for (;;) {//Definindo um Loop infinito
    digitalWrite(ledVermelho, HIGH);
    delay(100);//delay em que o led irá ficar aceso
    digitalWrite(ledVermelho, LOW);
    delay(100);//delay em que o led irá ficar apagado
  }
}
//Declarando função blink com uma função de chamada "void" com um ponteiro "*pvParameters"
void blinkAzul(void *pvParameters) {

  for (;;) {//Definindo um Loop infinito
    digitalWrite(ledAzul, HIGH);
    delay(500);//delay em que o led irá ficar aceso
    digitalWrite(ledAzul, LOW);
    delay(500);//delay em que o led irá ficar apagado
  }
  }

//Declarando função blink com uma função de chamada "void" com um ponteiro "*pvParameters"
void sensorHC(void *pvParameters) {

  for (;;) {//Definindo um Loop infinito

    //Função do SensorHC-SR04
    int distancia;
    digitalWrite(trigPin, LOW);//Comunicação em Cortada "LOW"
    delayMicroseconds(2);//Tempo de aguardar 2 microsegundos
    digitalWrite(trigPin, HIGH);//Começando a comunicação com Pino Trig em nivel alto "HIGH"
    delayMicroseconds(10);//Tempo de aguardar 10 microsegundos
    digitalWrite(trigPin, LOW);//Comunicação em Cortada "LOW"
    unsigned long tempoSom = pulseIn(echoPin, HIGH);//Variavel "unsigned long" para um valor com alta precisão, pulseIn(echoPin, HIGH) calcula o tempo do pino echo
    distancia = tempoSom / 58;//Calculo da distancia que é tempoSOM dividido por 58

    //Comandos para informar as informações no Monitor Serial
    Serial.print("Distancia:");
    Serial.print(distancia);
    Serial.println(" cm");

    delay(1000);//Delay de 1 segundo
  }
}
