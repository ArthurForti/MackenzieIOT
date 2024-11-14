**Projeto de Irrigação Automática IoT - UNIVERSIDADE PRESBITERIANA MACKENZIE**

**Descrição do Projeto**
A água é essencial para a agricultura e processos relacionados ao crescimento e manutenção de plantas. Este projeto tem como objetivo desenvolver um sistema de irrigação automática controlado via IoT, que monitora a umidade do solo e, com base nesses dados, aciona uma bomba d'água para irrigação. A solução foi projetada para ser usada em ambientes industriais agrícolas e jardins que necessitam de monitoramento constante da umidade para otimizar o uso da água e garantir que as plantas estejam recebendo o nível de água adequado.

Para este projeto, foi implementado um sistema de comunicação com um broker MQTT, que permite monitoramento remoto do status da bomba e controle do sistema de irrigação, proporcionando uma solução eficiente e conectada.

**Objetivos do Projeto**
Monitorar a umidade do solo em tempo real.
Ligar e desligar automaticamente a bomba d'água com base na umidade do solo (sensor detecta solo seco ou úmido).
Enviar o estado da bomba (ligada/desligada) para um servidor MQTT.
Permitir que o estado da bomba seja monitorado remotamente através do protocolo MQTT.
Reconectar automaticamente ao broker MQTT em caso de perda de conexão.

**Funcionalidades**
Conexão à rede WiFi e ao broker MQTT.
Monitoramento contínuo da umidade do solo.
Controle automático da bomba de água com base nas leituras do sensor de umidade.
Publicação do estado da bomba em um tópico MQTT, acessível para monitoramento remoto.
Reconexão automática ao MQTT em caso de desconexão, garantindo estabilidade e continuidade.

**Materiais Utilizados**
Protoboard
Jumper wires
Arduino Uno (CH340)
ESP8266
Relé de 1 canal (5V) para controle da bomba
Sensor de umidade do solo
Mini bomba d'água (JT100)

**Diagrama**

![Imagem](https://github.com/user-attachments/assets/e88ca80a-660a-4d89-925a-313b3ea828a4)


**Fluxo de Operação**
O sensor de umidade do solo envia os dados ao Arduino.
O Arduino lê o valor do sensor e determina se o solo está seco (1) ou úmido (0).
Caso o solo esteja seco, o Arduino aciona o relé para ligar a bomba e envia uma mensagem pela porta serial ao ESP8266.
O ESP8266 publica o estado da bomba ("Ligada" ou "Desligada") no tópico MQTT configurado.
O sistema verifica periodicamente a conexão ao MQTT, reconectando-se automaticamente caso a conexão seja perdida.

**Tópico e Estrutura de Mensagens MQTT**
Tópico: *arthuresilviamackenzie*

**Estrutura de mensagem (JSON):**
`{
  "estado_bomba": "Ligada" ou "Desligada"
}`

**Licença**
Este projeto foi desenvolvido para fins acadêmicos na Universidade Presbiteriana Mackenzie e está aberto para melhorias e contribuições para futuras implementações e aprimoramentos.

**Contribuição**

Arthur Forti Bueno Torres (https://github.com/ArthurForti)

Sílvia Vitória Ribeiro (https://github.com/silviaribeiro)
