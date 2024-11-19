//*Projeto Irrigato* by Victor Calado

//Declarações

/*O Esp12-E trabalha com sinal 1 o tempo todo, então para desativar alguma porta,
 é necessário utilizar HIGH e LOW para ligar a porta novamente.
*/
#include <Arduino.h>

#define PIN_LED D4              // Define o pino para o LED
#define PIN_RELE D6             // Define o pino para o relé
#define TEMPO_ATIVO 2           // Tempo de ativação do relé (em segundos)
#define TEMPO_SEMANA 604800         // Tempo para teste (10 segundos, ajustável para 604800 segundos para uma semana)

unsigned long tempoFinal = 0;   // Momento exato de término da contagem
unsigned long ultimoPiscarLed = 0;  

const unsigned long INTERVALO_LED = 1;  // Intervalo para o LED piscar (em segundos)

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELE, OUTPUT);  
  digitalWrite(PIN_RELE, HIGH);  // Inicia o relé desligado
  digitalWrite(PIN_LED, HIGH);
  
  Serial.begin(9600); // Inicializa o monitor serial
  Serial.println("Sistema iniciado!");

  // Define o momento exato de término
  tempoFinal = millis() / 1000 + TEMPO_SEMANA;
}

void loop() {
  // Obtém o tempo atual em segundos
  unsigned long tempoAtual = millis() / 1000;

  // Calcula o tempo restante
  long tempoRestante = tempoFinal - tempoAtual;

  if (tempoRestante <= 0) {
    // Ativa o relé
    Serial.println("Relé ativado!");
    digitalWrite(PIN_RELE, LOW);

    // Aguarda o tempo configurado enquanto mantém o relé ativado
    delay(TEMPO_ATIVO * 1000);  // Converte segundos para milissegundos para o delay

    // Desativa o relé
    digitalWrite(PIN_RELE, HIGH);
    Serial.println("Relé desativado!");

    // Reinicia a contagem para outra semana
    tempoFinal = millis() / 1000 + TEMPO_SEMANA;

  } else {
    // Controle do LED enquanto aguarda o término
    if (tempoAtual - ultimoPiscarLed >= INTERVALO_LED) {
      // Alterna o estado do LED
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
      ultimoPiscarLed = tempoAtual;

      // Mostra o tempo restante no monitor serial
      Serial.print("Tempo restante para o relé: ");
      Serial.print(tempoRestante);
      Serial.println(" segundos");
    }
  }
}
