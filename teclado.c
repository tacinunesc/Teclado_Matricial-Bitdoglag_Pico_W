#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// ------------------- Definições -------------------
#define LINHAS 4
#define COLUNAS 4

const uint pinos_linha[LINHAS] = {4, 8, 9, 16};      // GPIOs das linhas
const uint pinos_coluna[COLUNAS] = {17, 18, 19, 20};    // GPIOs das colunas

// Mapeamento tradicional do teclado 4x4
char teclas[LINHAS][COLUNAS] = {
    {'D', 'C', 'B', 'A'},
    {'#', '9', '6', '3'},
    {'0', '8', '5', '2'},
    {'*', '7', '4', '1'}
};

// LEDs
#define LED_VERMELHO 13
#define LED_VERDE    11
#define LED_AZUL     12

// ------------------- Funções -------------------

// Configura GPIOs para teclado e LEDs
void configurar_hardware() {
    // Linhas como entrada com pull-up
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(pinos_linha[i]);
        gpio_set_dir(pinos_linha[i], GPIO_IN);
        gpio_pull_up(pinos_linha[i]);
    }

    // Colunas como saída em nível alto
    for (int j = 0; j < COLUNAS; j++) {
        gpio_init(pinos_coluna[j]);
        gpio_set_dir(pinos_coluna[j], GPIO_OUT);
        gpio_put(pinos_coluna[j], 1);
    }

    // LEDs como saída
    gpio_init(LED_VERMELHO); gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);     gpio_set_dir(LED_AZUL, GPIO_OUT);
}

// Escaneia o teclado e retorna a tecla pressionada (ou 0)
char ler_teclado() {
    for (int col = 0; col < COLUNAS; col++) {
        gpio_put(pinos_coluna[col], 0); // Coluna ativada

        for (int lin = 0; lin < LINHAS; lin++) {
            if (!gpio_get(pinos_linha[lin])) { // Tecla pressionada
                while (!gpio_get(pinos_linha[lin])); // Aguarda soltar
                gpio_put(pinos_coluna[col], 1); // Restaura coluna
                return teclas[lin][col]; // Retorna a tecla correta
            }
        }

        gpio_put(pinos_coluna[col], 1); // Restaura coluna
    }
    return 0;
}

// Acende o LED com base na tecla
void acionar_led_por_tecla(char tecla) {
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);

    if (tecla == '1' || tecla == '2' || tecla == '3' || tecla == 'A' || tecla == '*' || tecla == 'D') {
        gpio_put(LED_VERMELHO, 1);
    } else if (tecla == '4' || tecla == '5' || tecla == '6' || tecla == 'B' || tecla == '0') {
        gpio_put(LED_VERDE, 1);
    } else if (tecla == '7' || tecla == '8' || tecla == '9' || tecla == 'C'|| tecla == '#') {
        gpio_put(LED_AZUL, 1);
    }
}

// ------------------- Função Principal -------------------

int main() {
    stdio_init_all();          // Inicializa a UART (para printf)
    configurar_hardware();     // Prepara pinos

    printf("Sistema iniciado. Pressione uma tecla...\n");

    while (true) {
        char tecla = ler_teclado();

        if (tecla) {
            printf("Tecla detectada: [%c]\n", tecla);
            acionar_led_por_tecla(tecla);
        }

        sleep_ms(100); // Pequeno atraso para estabilidade
    }

    return 0;
}
