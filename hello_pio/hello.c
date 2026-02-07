/*
    Autor.: Paulo da Silva (pgordao)
    Data..: 25/01/2025
    Versão: 2504
    Descrição: 
    Esse programa configura um ou mais pinos GPIO em uma maquina de estado da PIO,
    com isso podemos escrever no TX FIFO da máquina de estado e a PIO lê esse dado
    e o coloca no(os) pino(s) configurados para recebe-lo(s).
    A maquina de estado fica parada no modo de leitura do TX FIFO quando ele estiver vazio. 

    Esse programa foi totalmente baseado no programa hello.pio
    que consta nos exemplos do Raspiberry Pi Pico. 
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hello.pio.h"      // Esse arquivo é auto gerado.

#undef PIO_PIN 

#define PIO_PIN 0

// Check the pin is compatible with the platform
#if PIO_PIN >= NUM_BANK0_GPIOS
#error ERRO: o número do pino tem que ser menor ou igual a 26
#endif

int main() {
    PIO pio;
    uint sm;
    uint offset;
    uint counter=0;

    // Busca uma state machine vazia dentre as disponíveis.
    // Observe que as variáveis pipo sm e offset foram passadas como ponteiros
    // permitindo assim que a função altere seus valores para que possamos
    // usar a máquina de estado.
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&hello_program, &pio, &sm, &offset, PIO_PIN, 1, true);
    // Somente valida o retorno se é um dos possíveis.
    hard_assert(success);

    // Chama a função hello_program_init definida no hello.pio, para configurar e iniciar o programa.
    hello_program_init(pio, sm, offset, PIO_PIN);

    // Nesse ponto a máquina de estado está executando suas tarefas, e a primeira
    // é ler o TX FIFO que nesse momento não tem nada assim ela está parada na instrução pull
    // do nosso program hello.pio, quando enviarmos dados que nesse caso é um contador de 0 a 255
    // o valor do contador aparecerá nos pinos configurados, nesse caso no GPIO0 a GPIO7
    while (getchar_timeout_us(0) == PICO_ERROR_TIMEOUT) {
        // Escreve o valor no TX FIFO
        pio_sm_put_blocking(pio, sm, counter++);
        sleep_ms(500);
    }

    // O programa nunca chegará até aqui.
    // Estas função libera recursos e descarrega o programa.
    // Essa é a forma correta de terminar algo com a PIO
    //pio_remove_program_and_unclaim_sm(&hello_program, pio, sm, offset);

}
