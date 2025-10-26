#include "../ota-bootloader.h"
#include <stdio.h>
#include "contiki.h"

PROCESS(ota_bootloader_test_process, "OTA Bootloader Test Process");
AUTOSTART_PROCESSES(&ota_bootloader_test_process);

PROCESS_THREAD(ota_bootloader_test_process, ev, data)
{
  PROCESS_BEGIN();
  printf("[OTA Bootloader Test] Initializing...\n");
  ota_bootloader_init();
  // Simulate receiving firmware data
  uint8_t test_data[256] = {0x55};
  ota_bootloader_receive(test_data, sizeof(test_data));
  // Simulate starting firmware update
  ota_bootloader_start();
  PROCESS_END();
}
