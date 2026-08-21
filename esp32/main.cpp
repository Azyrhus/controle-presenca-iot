#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Configurações da rede Wi-Fi (substitua pelas suas credenciais)
const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_SUA_REDE";

// URL do servidor Node-RED
// Substitua "192.168.X.X" pelo IP local do seu computador na rede
const char* serverUrl = "http://192.168.1.100:1880/presenca";

// Pino do botão físico (BOOT button padrão do ESP32)
const int pinoBotao = 0; 
int ultimoEstadoBotao = HIGH;

// Função para enviar o registro de presença via HTTP POST
void enviarPresenca(String raAluno) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    Serial.println("\n[HTTP] Iniciando conexão com o Node-RED...");
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Cria o objeto JSON
    StaticJsonDocument<200> doc;
    doc["ra"] = raAluno;

    String jsonBuffer;
    serializeJson(doc, jsonBuffer);

    Serial.print("[HTTP] Enviando JSON: ");
    Serial.println(jsonBuffer);

    // Envia o HTTP POST
    int httpResponseCode = http.POST(jsonBuffer);

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.printf("[HTTP] Código de resposta: %d\n", httpResponseCode);
      Serial.printf("[HTTP] Resposta do servidor: %s\n", payload.c_str());
    } else {
      Serial.printf("[HTTP] Falha na requisição. Erro: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[WiFi] Desconectado! Não foi possível enviar a presença.");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinoBotao, INPUT_PULLUP);

  // Conexão com o Wi-Fi
  Serial.println();
  Serial.print("Conectando à rede Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado com sucesso!");
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Leitura do botão físico (aciona envio ao pressionar)
  int estadoBotao = digitalRead(pinoBotao);

  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    delay(50); // Debounce
    Serial.println("\n[AÇÃO] Botão pressionado!");
    
    // Dispara a chamada do aluno com RA 1001
    enviarPresenca("1001");
  }

  ultimoEstadoBotao = estadoBotao;
  delay(10);
}