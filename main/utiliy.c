#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/adc.h"
#include "esp_timer.h"
#include <rom/ets_sys.h>

///////////////////////////////////////////////////////////////////////////////
// Helper function takes tick into nanoseconds
// https://github.com/eerimoq/simba/issues/155
static int sys_port_get_time_into_tick()
{
    // get clock count
    // http://sub.nanona.fi/esp8266/timing-and-ticks.html
    uint32_t ccount;
    __asm__ __volatile__("esync; rsr %0,ccount":"=a" (ccount));
    // get nanos
    // from https://github.com/adafruit/ESP8266-Arduino/blob/50122289a3ecb7cddcba34db9ec9ec8b4d7e7442/hardware/esp8266com/esp8266/cores/esp8266/Esp.h#L129
    // system_get_cpu_freq() returns 80 or 160; unit MHz
    ccount /= ets_get_cpu_frequency(); // (freq_MHz*1000000) Hz = 1/second // Get the real CPU ticks per us to the ets.
    
    return ccount;
}

