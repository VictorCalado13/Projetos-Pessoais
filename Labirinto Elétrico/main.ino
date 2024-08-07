

int ledverde = 3;
int ledamarelo = 4;
int ledverm = 5;

int sirene = 13;

int reset = 2;

int buzzer = 7;
int arco = A0;

int leitura = 0;

int vida = 3;


int contatochegou = A1;

void setup()
{
  pinMode(ledverde, OUTPUT);
  pinMode(ledamarelo, OUTPUT);
  pinMode(ledverm, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(arco, INPUT);
  pinMode(sirene, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
  if (digitalRead(reset) == 1) {
    vida = 3;
  }
  
  leitura = analogRead(arco);
  Serial.print("Leitura: ");
  Serial.println(leitura);
  Serial.println(digitalRead(reset));
  delay(50);

  if (leitura > 100) {
    vida = vida - 1;
    delay(200);
    }

  if (vida == 3) {
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledamarelo, HIGH);
    digitalWrite(ledverm, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(sirene, LOW);
  }
  if (vida == 2) {
    digitalWrite(ledverde, LOW);
    digitalWrite(ledamarelo, HIGH);
    digitalWrite(ledverm, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(sirene, LOW);
  }
  if (vida == 1) {
    digitalWrite(ledverde, LOW);
    digitalWrite(ledamarelo, LOW);
    digitalWrite(ledverm, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(sirene, LOW);
  }
  if (vida <= 0) {
    digitalWrite(ledverde, LOW);
    digitalWrite(ledamarelo, LOW);
    digitalWrite(ledverm, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(sirene, HIGH);
  }

  Serial.print("Vida: ");
  Serial.println(vida);
  Serial.print(reset);
}
