#ifndef OTA_BOOTLOADER_H_
#define OTA_BOOTLOADER_H_

#include "contiki.h"
#include <stdint.h>


#define CERTIFICATE_MAX_SIZE 256
#define SIGNATURE_MAX_SIZE 64

void ota_bootloader_init(void);
void ota_bootloader_start(void);
void ota_bootloader_receive(uint8_t *data, uint16_t len);

int verify_certificate(const uint8_t *cert, uint16_t cert_len);
int verify_firmware_signature(const uint8_t *fw, uint16_t fw_len, const uint8_t *sig, uint16_t sig_len, const uint8_t *pubkey, uint16_t pubkey_len);

#endif /* OTA_BOOTLOADER_H_ */
