#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR
#include <time.h>
#include <stdint.h>

#define BUTTON_A 5 

int main() {
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    connect_to_wifi("DUKA", "amizade2014");

    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    mqtt_setup("bitdog1", "192.168.1.5", "aluno", "senha123");
    // Mensagem original a ser enviada
    const char *mensagem = "26.5";
    sleep_ms(3000);
    // Loop principal do programa
    int n=0;

    while (true) {
        if(gpio_get(BUTTON_A)==0){
            char buffer[256];
            sprintf(buffer, "{\"valor\":%s,\"ts\":%lu}", mensagem, n);
            uint8_t criptografada[256];// Criptografa a mensagem usando XOR com chave 42
            xor_encrypt((uint8_t *)buffer, criptografada, strlen(buffer), 42); // Publica a mensagem original (não criptografada)
         // Alternativa: Publica a mensagem criptografada (atualmente comentada)
            mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(buffer));
            n++;
        // Aguarda 5 segundos antes da próxima publicação
            sleep_ms(5000);
        }
        else{
            mqtt_comm_subscribe("escola/sala1/temperatura");
            sleep_ms(5000);
        }
    }
    return 0;
}

/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "26.6"
 */