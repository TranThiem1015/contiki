#include "contiki.h"
#include "ota-bootloader.h"
#include <stdio.h>

PROCESS(ota_test_process, "OTA Test Process");
AUTOSTART_PROCESSES(&ota_test_process);

PROCESS_THREAD(ota_test_process, ev, data)
{
  PROCESS_BEGIN();
  printf("[OTA Test] Starting OTA test process...\n");
  ota_bootloader_init();
  // Simulate receiving firmware data
  uint8_t test_data[128] = {0xAA};
  ota_bootloader_receive(test_data, sizeof(test_data));
  // Simulate starting firmware update
  ota_bootloader_start();
  PROCESS_END();
}
