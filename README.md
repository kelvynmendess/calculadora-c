# Calculadora em C

Calculadora de terminal desenvolvida em linguagem C com persistência de histórico em arquivo.

## Funcionalidades

- Soma, subtração, multiplicação e divisão
- Validação de entradas inválidas (letras, caracteres especiais)
- Proteção contra divisão por zero
- Histórico de operações salvo em arquivo `.txt` com data e hora
- Limpeza do histórico
- Compatível com Windows, Linux e macOS

## Como compilar e rodar

**No Windows (MinGW/GCC):**
```bash
gcc calculadora.c -o calculadora.exe
./calculadora.exe
```

**No Linux/macOS:**
```bash
gcc calculadora.c -o calculadora
./calculadora
```

## O que aprendi neste projeto

- Manipulação de arquivos em C (`fopen`, `fprintf`, `fgets`)
- Validação e limpeza de buffer de entrada com `scanf`
- Uso de macros para compatibilidade multiplataforma (`#ifdef _WIN32`)
- Modularização do código em funções com responsabilidades separadas
- Registro de data e hora com a biblioteca `<time.h>`

## Tecnologias

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
