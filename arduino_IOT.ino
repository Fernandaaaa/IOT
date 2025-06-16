const int pinoSensor = 2;
const int pinoRele = 7;    
const unsigned long tempoAcionamentoBomba = 500;

enum Estado { Aguardando, BombaLigada, EsperandoRetirada };
Estado estadoAtual = Aguardando;

unsigned long tempoAnterior = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Dispenser inicializado. Aguardando...");
  pinMode(pinoSensor, INPUT);
  pinMode(pinoRele, OUTPUT);
  digitalWrite(pinoRele, HIGH);
}

void loop() {
  switch (estadoAtual) {
    case Aguardando:
      if (digitalRead(pinoSensor) == LOW) {
        Serial.println("Mão detectada. Ligando a bomba...");
        digitalWrite(pinoRele, LOW);
        tempoAnterior = millis();
        estadoAtual = BombaLigada;
      }
      break;

    case BombaLigada:
      if (millis() - tempoAnterior >= tempoAcionamentoBomba) {
        Serial.println("Bomba desligada. Aguardando a retirada da mão...");
        digitalWrite(pinoRele, HIGH);
        estadoAtual = EsperandoRetirada;
      }
      break;

    case EsperandoRetirada:
      if (digitalRead(pinoSensor) == HIGH) {
        Serial.println("Mão retirada. Sistema pronto novamente.");
        estadoAtual = Aguardando;
      }
      break;
  }
}