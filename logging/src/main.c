
#include <zephyr/kernel.h>
#include <zephyr/console/console.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(logging);

void log_waiting(void *arg1, void *arg2, void *arg3) {
	console_getline_init(); 

	while(1) {
		char *message = console_getline(); 
		LOG_INF("Mensagem recebida: %s", message); 
	}
}

K_THREAD_DEFINE(log_waiting_th, 512, log_waiting, NULL,
				NULL, NULL, 0, 0, 0);

int main(void)
{

	while(1) {
		LOG_INF("Aguardando mensagem..."); 
		k_msleep(1000); 
	}
	
	return 0;
}


