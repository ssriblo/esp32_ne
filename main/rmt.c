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

void initRmt(){
	ESP_LOGI(tag, ">> runRmt");

	rmt_config_t config;
	config.rmt_mode = RMT_MODE_TX;
	config.channel = RMT_CHANNEL_0;
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

	ESP_ERROR_CHECK(rmt_config(&config));
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
	config.channel = RMT_CHANNEL_1;
	config.gpio_num = 22;
	ESP_ERROR_CHECK(rmt_config(&config));
	ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
}
void runRmt() {
	rmt_item32_t items_0[5];
	items_0[0].duration0 = 390;
	items_0[0].level0 = 0;
	items_0[0].duration1 = 350;
	items_0[0].level1 = 0;
	items_0[1].duration0 = 13;
	items_0[1].level0 = 1;
	items_0[1].duration1 = 33;
	items_0[1].level1 = 0;
	items_0[2].duration0 = 13;
	items_0[2].level0 = 1;
	items_0[2].duration1 = 33;
	items_0[2].level1 = 0;
	items_0[3].duration0 = 13;
	items_0[3].level0 = 1;
	items_0[3].duration1 = 33;
	items_0[3].level1 = 0;
	items_0[4].duration0 = 13;
	items_0[4].level0 = 1;
	items_0[4].duration1 = 33;
	items_0[4].level1 = 0;


	rmt_item32_t items_1[5];
	items_1[0].duration0 = 22;
	items_1[0].level0 = 1;
	items_1[0].duration1 = 22;
	items_1[0].level1 = 0;
	items_1[1].duration0 = 22;
	items_1[1].level0 = 1;
	items_1[1].duration1 = 22;
	items_1[1].level1 = 0;
	items_1[2].duration0 = 22;
	items_1[2].level0 = 1;
	items_1[2].duration1 = 22;
	items_1[2].level1 = 0;
	items_1[3].duration0 = 22;
	items_1[3].level0 = 1;
	items_1[3].duration1 = 22;
	items_1[3].level1 = 0;
	items_1[4].duration0 = 22;
	items_1[4].level0 = 0;
	items_1[4].duration1 = 22;
	items_1[4].level1 = 0;

	ESP_ERROR_CHECK(rmt_write_items(RMT_CHANNEL_0, items_0,
			5, /* Number of items_0 */
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

	ESP_ERROR_CHECK(rmt_write_items(RMT_CHANNEL_1, items_1,
			5, /* Number of items_1 */
			0 /* wait till done */));
}


