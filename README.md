# Teclado Matricial com Pico W (BitDogLab)
![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20Pico-purple.svg)
![Sensor](https://img.shields.io/badge/Teclado-Matricail-yellow.svg)

Este projeto demonstra como montar e programar um teclado matricial conectado a um Raspberry Pi Pico W, usando a biblioteca/estrutura do BitDogLab.

## 🛠️ Estrutura do projeto
- teclado.c – Programa principal em C que faz leitura do teclado matricial e exibe no console/porta serial as teclas pressionadas
- CMakeLists.txt – Configuração do build usando o Pico SDK
  
## 🔌 Requisitos
Hardware:

- Raspberry Pi Pico W
- Teclado matricial (4×4)
- Adaptador

Software:

- CMake ≥ 3.13
- Pico SDK (via submódulo ou variável PICO_SDK_PATH)
- Toolchain ARM / GCC para RP2040
- Biblioteca hardware/gpio (já incluída no Pico SDK)

## ⚙️ Como usar
1- clone o repositorio

2- Deploy no Pico W
 - Segure o botão BOOTSEL do Pico W e conecte-o ao PC
 - Clique no botão run no Vscode ou arraste o arquivo .u2 para dentro do disco removível que aparecer
 - O Pico irá reiniciar executando o firmware
   
3- Testar a aplicação

   Ao pressionar teclas no teclado matricial, os caracteres/padrões correspondentes serão enviados e exibidos no terminal.
   
  - Se as teclas '1' || '2' || '3' || 'A' || '*' || 'D' forem pressionadas o LED vermelho será ativado
  -  Se as teclas '4' || '5' || '6' || 'B' || '0' forem pressionadas o LED verde será ativado
  -   Se as teclas '7' || '8' || '9' || 'C' || '#' forem pressionadas o LED azul será ativado
