#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/rmt.h>
#include <stdbool.h>
#include "sdkconfig.h"

#include "defines.h"
#include "utility.h"
#include "rmt.h"

static char tag[] = "rmt_tests";
rmt_channel_t channelA, channelB; 

void initRmt(channelPulses_t channelPulses){
	ESP_LOGI(tag, ">> runRmt");
	/* PROBLEM: 
		- We can not install driver, if it has installed already
		- Let store current driver/channel statuses 
		- Possilbe channel status: installed/not installed, stored at channelIsntalled[]
		- channelIsntalled[0/1/2/3] mapped to RMT_CHANNEL_0/RMT_CHANNEL_1/RMT_CHANNEL_2/RMT_CHANNEL_3
	*/
	static bool channelIsntalled[4] = {false, false, false, false};
	
	gpio_num_t pinA, pinB;

	if(channelPulses == CHANNEL_1_AB){
		channelA = RMT_CHANNEL_0;
		channelB = RMT_CHANNEL_1;
		pinA = CHANNEL_1A_PIN;
		pinB = CHANNEL_1B_PIN;
	}else{
		channelA = RMT_CHANNEL_2;
		channelB = RMT_CHANNEL_3;
		pinA = CHANNEL_2A_PIN;
		pinB = CHANNEL_2B_PIN;
	}

	rmt_config_t config;
	config.rmt_mode = RMT_MODE_TX;
	// config.channel = channelA;
	config.channel = RMT_CHANNEL_0;
	// config.gpio_num = pinA;
	config.gpio_num = 21;
	config.mem_block_num = 1;
	config.tx_config.loop_en = 0;
	config.tx_config.carrier_en = 0;
	config.tx_config.idle_output_en = 1;
	config.tx_config.idle_level = 0;
	config.tx_config.carrier_duty_percent = 50;
	config.tx_config.carrier_freq_hz = 10000;
	config.tx_config.carrier_level = 1;
	config.clk_div = 1;

	printf(">>>> RMT-1 CH=%d %d %d\n", config.channel, channelIsntalled[config.channel], channelPulses);
	ESP_ERROR_CHECK(rmt_config(&config));
	// if(channelIsntalled[config.channel] == true){
	// 	ESP_ERROR_CHECK(rmt_driver_uninstall(config.channel));
	// }
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
	channelIsntalled[config.channel] = true;

	// config.channel = channelB;
	// config.gpio_num = pinB;
	config.channel = RMT_CHANNEL_1;
	config.gpio_num = 22;
	printf(">>>> RMT-2 CH=%d %d %d\n", config.channel, channelIsntalled[config.channel], channelPulses);
	ESP_ERROR_CHECK(rmt_config(&config));
	// if(channelIsntalled[config.channel] == true){
		// ESP_ERROR_CHECK(rmt_driver_uninstall(config.channel));
	// }
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
	channelIsntalled[config.channel] = true;
}
void runRmt(channelPulses_t channelPulses) {
	rmt_item32_t itemsA[5];
	itemsA[0].duration0 = 565;
	itemsA[0].level0 = 0;
	itemsA[0].duration1 = 525;
	itemsA[0].level1 = 0;
	itemsA[1].duration0 = 22;
	itemsA[1].level0 = 1;
	itemsA[1].duration1 = 22;
	itemsA[1].level1 = 0;
	itemsA[2].duration0 = 22;
	itemsA[2].level0 = 1;
	itemsA[2].duration1 = 22;
	itemsA[2].level1 = 0;
	itemsA[3].duration0 = 22;
	itemsA[3].level0 = 1;
	itemsA[3].duration1 = 22;
	itemsA[3].level1 = 0;
	itemsA[4].duration0 = 22;
	itemsA[4].level0 = 1;
	itemsA[4].duration1 = 22;
	itemsA[4].level1 = 0;


	rmt_item32_t itemsB[5];
	itemsB[0].duration0 = 22;
	itemsB[0].level0 = 1;
	itemsB[0].duration1 = 22;
	itemsB[0].level1 = 0;
	itemsB[1].duration0 = 22;
	itemsB[1].level0 = 1;
	itemsB[1].duration1 = 22;
	itemsB[1].level1 = 0;
	itemsB[2].duration0 = 22;
	itemsB[2].level0 = 1;
	itemsB[2].duration1 = 22;
	itemsB[2].level1 = 0;
	itemsB[3].duration0 = 22;
	itemsB[3].level0 = 1;
	itemsB[3].duration1 = 22;
	itemsB[3].level1 = 0;
	itemsB[4].duration0 = 22;
	itemsB[4].level0 = 0;
	itemsB[4].duration1 = 22;
	itemsB[4].level1 = 0;

	if(channelPulses == CHANNEL_1_AB){
		channelA = RMT_CHANNEL_0;
		channelB = RMT_CHANNEL_1;
	}else{
		channelA = RMT_CHANNEL_2;
		channelB = RMT_CHANNEL_3;
	}

	ESP_ERROR_CHECK(rmt_write_items(channelA, itemsA,
			5, /* Number of itemsA */
			0 /* NOT wait till done */));
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");

	ESP_ERROR_CHECK(rmt_write_items(channelB, itemsB,
			5, /* Number of itemsB */
			0 /* wait till done */));
}


