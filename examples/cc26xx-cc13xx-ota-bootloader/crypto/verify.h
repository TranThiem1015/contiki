#ifndef VERIFY_H_
#define VERIFY_H_

#include <stdint.h>

int verify_certificate(const uint8_t *cert, uint16_t cert_len);
int verify_firmware_signature(const uint8_t *fw, uint16_t fw_len, const uint8_t *sig, uint16_t sig_len, const uint8_t *pubkey, uint16_t pubkey_len);

#endif /* VERIFY_H_ */
