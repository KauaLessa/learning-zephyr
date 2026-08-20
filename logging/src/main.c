
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <string.h>
#include <zephyr/console/console.h>
#include <zephyr/logging/log.h>
#include <zephyr/console/console.h>

LOG_MODULE_REGISTER(logging);


int main(void)
{
	console_getline_init(); 
	
	while (1) {
		LOG_INF("Aguardando mensagem para ser enviada...\n");
		char* message = console_getline(); 
		LOG_INF("%s", message); 
		LOG_INF("Mensagem enviada"); 
		k_msleep(1000); 
	}
	return 0;
}
