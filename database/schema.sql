CREATE DATABASE IF NOT EXISTS controle_presenca;
USE controle_presenca;

CREATE TABLE IF NOT EXISTS alunos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ra VARCHAR(20) UNIQUE NOT NULL,
    nome VARCHAR(100) NOT NULL,
    curso VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS presenca (
    id INT AUTO_INCREMENT PRIMARY KEY,
    ra VARCHAR(20) NOT NULL,
    datahora DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (ra) REFERENCES alunos(ra)
);

INSERT INTO alunos (ra, nome, curso) VALUES 
('1001', 'Ana Silva', 'DSM'),
('1002', 'Carlos Lima', 'DSM'),
('1003', 'Maria Souza', 'ADS'),
('1004', 'Pedro Santos', 'GTI');