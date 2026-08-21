# Sistema de Controle de Presença de Alunos (IoT + Node-RED + MySQL)

Projeto desenvolvido para controle automatizado de presença utilizando simulação de dispositivo IoT (ESP32 via HTTP), orquestração de dados com Node-RED, persistência em MySQL e visualização em tempo real via Dashboard 2.0.

## 🚀 Arquitetura do Sistema
1. **ESP32 (PlatformIO):** Envia requisição HTTP POST com o RA do aluno em formato JSON (`{"ra": "1001"}`).
2. **Node-RED:** Recebe o payload, valida a existência do RA na tabela `alunos` e grava na tabela `presenca`.
3. **MySQL:** Banco de dados relacional que armazena os cadastros e os registros de entrada.
4. **Dashboard 2.0:** Painel em tempo real para monitoramento de indicadores (Total, Presentes, Ausentes) e tabela de últimas presenças.

## 🛠️ Tecnologias Utilizadas
* **Hardware/Emulação:** ESP32, PlatformIO, C++
* **Back-end:** Node-RED, Node.js, HTTP POST
* **Banco de Dados:** MySQL Server 8.0
* **Front-end:** Node-RED Dashboard 2.0 (`@flowfuse/node-red-dashboard`)

## 📌 Estrutura do Banco de Dados
```sql
CREATE DATABASE controle_presenca;
USE controle_presenca;

CREATE TABLE alunos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ra VARCHAR(20) UNIQUE NOT NULL,
    nome VARCHAR(100) NOT NULL,
    curso VARCHAR(50) NOT NULL
);

CREATE TABLE presenca (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ra VARCHAR(20) NOT NULL,
    datahora DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (ra) REFERENCES alunos(ra)
);