#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

const char* ssid = "Ahri";
const char* password = "TaliyahS2";

// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const char *topic = "arthuresilviamackenzie";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// Variáveis
bool mqttStatus = false;
String estadoBombaAtual = "";

// Objetos
WiFiClient espClient;
PubSubClient client(espClient);

bool connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado com o IP: ");
  Serial.println(WiFi.localIP());

  mqttStatus = connectMQTT();
}

void loop() {
  if (Serial.available() > 0) {
    String leituraSerial = Serial.readStringUntil('\n');
    Serial.print("Leitura recebida: ");
    Serial.println(leituraSerial);

    leituraSerial.trim();

    if (leituraSerial == "Bomba ligada: Solo seco!") {
      estadoBombaAtual = "Ligada";
    } else if (leituraSerial == "Bomba desligada: Solo úmido.") {
      estadoBombaAtual = "Desligada";
    } else {
      Serial.println("Dados inválidos recebidos, ignorando.");
      return;
    }

    DynamicJsonDocument doc(256);
    doc["estado_bomba"] = estadoBombaAtual;
    String estadoJson;
    serializeJson(doc, estadoJson);

    static String ultimoEstado = "";
    if (estadoBombaAtual != ultimoEstado && mqttStatus) {
      if (client.publish(topic, estadoJson.c_str())) {
        Serial.print("Publicado no MQTT: ");
        Serial.println(estadoJson);
        ultimoEstado = estadoBombaAtual;
      } else {
        Serial.println("Falha ao publicar no MQTT.");
      }
    }
  }

  if (mqttStatus) {
    client.loop();
  }
}

bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  do {
    String client_id = "ArthureSil";
    client_id += String(WiFi.macAddress());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conexão MQTT bem-sucedida");
      DynamicJsonDocument initDoc(256);
      initDoc["estado"] = "inicializado";
      String initJson;
      serializeJson(initDoc, initJson);
      client.publish(topic, initJson.c_str());
    } else {
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }
    tentativa++;
  } while (!client.connected() && tentativa < 5);

  if (client.connected()) {
    client.subscribe(topic);
    return true;
  } else {
    Serial.println("Não foi possível conectar ao MQTT");
    return false;
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}
