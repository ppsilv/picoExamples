
   Para se usar a instrução <set> do pio assembler as configurações necessárias são:
   

   1 - Informar para a pio qual o primeiro gpio e a quantidade subsequente que vai 
       ser usado.
       No exemplo abaixo vamos usar 3 gpios a partir do gpio 0, para isso precisamos
       usar a função sm_config_set_set_pins do SDK, sua definição é:
       sm_config_set_set_pins( Ponteiro para a State Machine usada, Número da GPIO, Quantidade de GPIO);

       sm_config_set_set_pins(&c, pin(GPIO 0), 3);
       Nesse caso:
                  * primeiro paramêtro  &c é o ponteiro para uma State Machine     
                  * segundo paramêtro pin é o número da primeira GPIO que vamos usar.
                  * terceiro paramêtro é o total de GPIO que vamos usar.
       Nesse caso vamos ter um led no pino 1 (GPIO 0), outro led no pino 2(GPIO 1) e um último led no
       pino 3(GPIO 2) do rppico.           

       Obs.: (GPIO 0) está sendo posto ao lado de pin somente para reforçar qual o dado que está
             sendo passado no paramêtro. 

   2 - Iniciar todos os GPIOs usados no projeto. 
       pio_gpio_init(pio, pin(GPIO 0));
       pio_gpio_init(pio, pin(GPIO 0)+1);
       pio_gpio_init(pio, pin(GPIO 0)+2);

       Obs.: (GPIO 0) está sendo posto ao lado de pin somente para reforçar qual o dado que está
             sendo passado no paramêtro. 

   3 - Configurar o sentido de todas as portas GPIOs envolvidas no processo. 
       pio_sm_set_consecutive_pindirs(pio, sm, pin(GPIO 0), 1, true);
       pio_sm_set_consecutive_pindirs(pio, sm, pin(GPIO 0)+1, 1, true);
       pio_sm_set_consecutive_pindirs(pio, sm, pin(GPIO 0)+2, 1, true);

       Obs.: (GPIO 0) está sendo posto ao lado de pin somente para reforçar qual o dado que está
             sendo passado no paramêtro. 

   4 - Inicia a pio com todos os dados anteriormente configurados. E a partir desse ponto 
       a pio já está executando o código dela e os leds estarão piscando.

       pio_sm_init(pio, sm, offset, &c);
