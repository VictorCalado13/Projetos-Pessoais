#include "BluetoothSerial.h" //Biblioteca Bluetooth ESP32

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char valorRecebido;//Variavel p/ receber valor da porta Serial Bluetooth

void setup() {
  Serial.begin(115200);//Configurando a taxa de comunicação com Monitor Serial em bits p/ segundo

  SerialBT.begin(ESP32); //Nome do Bluetooth
  Serial.printf("Dispositivo Visivel");

  pinMode(13, OUTPUT); //Pino GPIO 13

}

void loop() {
  valorRecebido =(char)SerialBT.read();//Valor recebido pela porta Serial Bluetooth

  if (Serial.available()) {
    SerialBT.write(Serial.read());

  }

  if (SerialBT.available()) {

    if (valorRecebido == '1')//Valor irá ser armazenado na Variavel "valorRecebido"

  {
    SerialBT.println("LED 1 ligado:");
    digitalWrite(13, HIGH);

  }

    if (valorRecebido == '2')//Valor irá ser armazenado na Variavel "valorRecebido"

  {
    SerialBT.println("LED 1 desligado:");
    digitalWrite(13, LOW);
  }

   }
  delay(50);//Atrasa o loop em 5o milisegundos p/ evitar processamento desnecessário

 }


