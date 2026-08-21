
#include <zephyr/kernel.h>
#include <zephyr/console/console.h>
#include <zephyr/logging/log.h>
#include <string.h>

#define BUFFER_SIZE 20

LOG_MODULE_REGISTER(logging);

K_MSGQ_DEFINE(my_msgq, sizeof(char), BUFFER_SIZE, 1);

void listen(void *rec, void *arg2, void *arg3) {
	console_getline_init();

	while(1) {
		char *message = console_getline(); 
		
		for (int i = 0; i < strlen(message) && i <= BUFFER_SIZE - 1; i++) {
			k_msgq_put(&my_msgq, message + i, K_NO_WAIT); 
		}

		char temp; 
		k_msgq_peek(&my_msgq, &temp); 

		if (temp != '\0') {
			char end = '\0'; 
			k_msgq_put(&my_msgq, &end, K_NO_WAIT); 
		}
	}
}

void show_message(void *arg1, void *arg2, void *arg3) {
	char buffer[BUFFER_SIZE];

	while(1) {
		int idx = 0;

		do {
			k_msgq_get(&my_msgq, buffer + idx, K_FOREVER);  
		} while(buffer[idx++] != '\0'); 
 
		LOG_INF("Mensagem recebida: %s", buffer); 
	}
} 

int main(void)
{
	while(1) {
		LOG_INF("Aguardando mensagem..."); 
		k_msleep(1000); 
	}
	
	return 0;
}

K_THREAD_DEFINE(show_message_th, 2048, show_message, NULL,
				NULL, NULL, 0, 0, 0);

K_THREAD_DEFINE(listen_th, 2048, listen, NULL,
				NULL, NULL, 1, 0, 0);


