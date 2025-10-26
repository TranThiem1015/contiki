#include "ota-bootloader.h"
#include "contiki.h"
#include <stdio.h>
#include <string.h>

PROCESS(ota_bootloader_process, "OTA Bootloader Process");


#define CERTIFICATE_MAX_SIZE 256
#define SIGNATURE_MAX_SIZE 64

static uint8_t firmware_buffer[4096];
static uint16_t firmware_size = 0;
static uint8_t device_certificate[CERTIFICATE_MAX_SIZE];
static uint8_t firmware_signature[SIGNATURE_MAX_SIZE];
static uint8_t public_key[64]; // Example: ECDSA public key


void ota_bootloader_init(void) {
  firmware_size = 0;
  memset(firmware_buffer, 0, sizeof(firmware_buffer));
  memset(device_certificate, 0, sizeof(device_certificate));
  memset(firmware_signature, 0, sizeof(firmware_signature));
  memset(public_key, 0, sizeof(public_key));
  printf("[OTA] Bootloader initialized.\n");
}


#include "crypto/verify.h"


// Receive OTA data, including certificate and signature
void ota_bootloader_receive(uint8_t *data, uint16_t len) {
  // For demo: assume first CERTIFICATE_MAX_SIZE bytes are certificate,
  // next SIGNATURE_MAX_SIZE bytes are signature, rest is firmware
  if(firmware_size == 0 && len >= CERTIFICATE_MAX_SIZE + SIGNATURE_MAX_SIZE) {
    memcpy(device_certificate, data, CERTIFICATE_MAX_SIZE);
    memcpy(firmware_signature, data + CERTIFICATE_MAX_SIZE, SIGNATURE_MAX_SIZE);
    memcpy(firmware_buffer, data + CERTIFICATE_MAX_SIZE + SIGNATURE_MAX_SIZE, len - CERTIFICATE_MAX_SIZE - SIGNATURE_MAX_SIZE);
    firmware_size = len - CERTIFICATE_MAX_SIZE - SIGNATURE_MAX_SIZE;
    printf("[OTA] Received certificate, signature, and firmware (%u bytes).\n", firmware_size);
  } else if(firmware_size + len < sizeof(firmware_buffer)) {
    memcpy(&firmware_buffer[firmware_size], data, len);
    firmware_size += len;
    printf("[OTA] Received %u bytes, total %u bytes.\n", len, firmware_size);
  } else {
    printf("[OTA] Firmware buffer overflow!\n");
  }
}


void ota_bootloader_start(void) {
  printf("[OTA] Starting secure firmware update...\n");
  // Step 1: Verify certificate
  if(!verify_certificate(device_certificate, CERTIFICATE_MAX_SIZE)) {
    printf("[SECURE] Certificate verification failed!\n");
    return;
  }
  printf("[SECURE] Certificate valid.\n");
  // Step 2: Verify firmware signature
  if(!verify_firmware_signature(firmware_buffer, firmware_size, firmware_signature, SIGNATURE_MAX_SIZE, public_key, sizeof(public_key))) {
    printf("[SECURE] Firmware signature invalid!\n");
    return;
  }
  printf("[SECURE] Firmware signature valid.\n");
  // Step 3: Write firmware to flash and reboot
  printf("[OTA] Firmware update complete.\n");
}

PROCESS_THREAD(ota_bootloader_process, ev, data)
{
  PROCESS_BEGIN();
  ota_bootloader_init();
  while(1) {
    PROCESS_WAIT_EVENT();
    if(ev == PROCESS_EVENT_MSG) {
      ota_bootloader_receive((uint8_t *)data, 128); // Example: receive 128 bytes
    } else if(ev == PROCESS_EVENT_CONTINUE) {
      ota_bootloader_start();
    }
  }
  PROCESS_END();
}
