#include "contiki.h"
#include "ota-bootloader.h"
#include "utils/ota_utils.h"
#include <stdio.h>

PROCESS(ota_bootloader_main_process, "OTA Bootloader Main Process");
AUTOSTART_PROCESSES(&ota_bootloader_main_process);

PROCESS_THREAD(ota_bootloader_main_process, ev, data)
{
  PROCESS_BEGIN();
  ota_bootloader_utils_print("Main bootloader process started.");
  ota_bootloader_init();
  // Main loop for OTA bootloader
  while(1) {
    PROCESS_WAIT_EVENT();
    // Handle OTA events here
  }
  PROCESS_END();
}
