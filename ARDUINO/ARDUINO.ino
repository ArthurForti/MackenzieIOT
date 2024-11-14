const int sensorUmidadePin = 2;
const int relePin = 8;           

void setup() {
  pinMode(relePin, OUTPUT);
  pinMode(sensorUmidadePin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  int valorUmidade = digitalRead(sensorUmidadePin);
  Serial.print("Leitura do sensor de umidade: ");
  Serial.println(valorUmidade);

  if (valorUmidade == 1) {
    digitalWrite(relePin, LOW);
    Serial.println("Bomba ligada: Solo seco!");
  } else {
    digitalWrite(relePin, HIGH);
    Serial.println("Bomba desligada: Solo úmido.");
  }

  delay(5000);
}