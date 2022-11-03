#ifndef GEN_INIT
#define GEN_INIT

//#include "utils.h"
#include "aes.h"
#include "DES.h"
#include "ecdh.h"

// Common to all algorithms
int _areKeysGenerated = 0;
unsigned char* gen_msg = "DEADBEEF";

// Over air message buffer size
//  There may be a difference between
//  the non-whitespace size
//  of an incoming message
//  versus the outgoing one. The buffer
//  size should be the same, however.
#if defined(ENC_NONE)
    #define OA_BUFFER_SIZE 16
#elif defined(ENC_AES)
    #define OA_BUFFER_SIZE 16
#elif defined(ENC_DES)
    #define OA_BUFFER_SIZE 16
#elif defined(ENC_ECC)
    #define OA_BUFFER_SIZE ECC_PUB_KEY_SIZE
#endif

/*======================== DES ========================*/
unsigned char des_key[8] = { 0x01, 0x02, 0x03, 0x04,
                             0x05, 0x06, 0x07, 0x08 };
key_set key_sets[17];

void generate_des_keys() {
    generate_sub_keys(des_key, key_sets);
    _areKeysGenerated = 1;
}
void des_encrypt(unsigned char* msg, unsigned char* output) {
    if (_areKeysGenerated == 0) {
        generate_des_keys();
    }
    
    process_message(msg, output, key_sets, ENCRYPTION_MODE);
}
void des_decrypt(unsigned char* msg, unsigned char* output) {
    if (_areKeysGenerated == 0) {
        generate_des_keys();
    }
    
    process_message(msg, output, key_sets, DECRYPTION_MODE);
}

/*======================== AES ========================*/
uint8_t aes_key[] =   { 0x53, 0x43, 0x60, 0xBE,
                        0x1A, 0xAA, 0x72, 0xB1,
                        0x97, 0x23, 0xC1, 0xD2,
                        0x7A, 0x01, 0x23, 0xC4 };

uint8_t aes_iv[] = { 0xA1, 0xB0, 0x0B, 0x1A, 
                     0xC1, 0xA2, 0x2A, 0x1C,
                     0xC9, 0xA3, 0x3A, 0x9C,
                     0xA4, 0xC4, 0x4C, 0x4A };
                     
struct AES_ctx aes_ctx;
void generate_aes_context() {
    AES_init_ctx_iv(&aes_ctx, aes_key, aes_iv);
    _areKeysGenerated = 1;
}
void aes_encrypt(unsigned char* msg, unsigned char* output) { /* Message should always be 16 bytes long */
    if (_areKeysGenerated == 0) {
        generate_aes_context();
    }
    
    AES_CBC_encrypt_buffer(&aes_ctx, (uint8_t*) msg, 16);
    
    for (int i = 0; i < 16; i++) {
        output[i] = msg[i];
    }
}
void aes_decrypt(unsigned char* msg, unsigned char* output) {
    if (_areKeysGenerated == 0) {
        generate_aes_context();
    }
    
    AES_CBC_decrypt_buffer(&aes_ctx, (uint8_t*) msg, 16);
    
    for (int i = 0; i < 16; i++) {
        output[i] = msg[i];
    }
}

/*======================== ECC ========================*/
typedef struct
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
} prng_t;

// Public, Private, and Secret keys
static uint8_t pubTrans[ECC_PUB_KEY_SIZE];
static uint8_t prvTrans[ECC_PRV_KEY_SIZE];
static uint8_t secTrans[ECC_PUB_KEY_SIZE];
static uint8_t pubRec[ECC_PUB_KEY_SIZE];
static uint8_t prvRec[ECC_PRV_KEY_SIZE];
static uint8_t secRec[ECC_PUB_KEY_SIZE];
  
static prng_t prng_ctx;

static uint32_t prng_rotate(uint32_t x, uint32_t k)
{
  return (x << k) | (x >> (32 - k)); 
}

static uint32_t prng_next(void)
{
  uint32_t e = prng_ctx.a - prng_rotate(prng_ctx.b, 27); 
  prng_ctx.a = prng_ctx.b ^ prng_rotate(prng_ctx.c, 17); 
  prng_ctx.b = prng_ctx.c + prng_ctx.d;
  prng_ctx.c = prng_ctx.d + e; 
  prng_ctx.d = e + prng_ctx.a;
  return prng_ctx.d;
}

static void prng_init(uint32_t seed)
{
  uint32_t i;
  prng_ctx.a = 0xf1ea5eed;
  prng_ctx.b = prng_ctx.c = prng_ctx.d = seed;

  for (i = 0; i < 31; ++i) 
  {
    (void) prng_next();
  }
}

static void init_trans_keys() {
    for (int i = 0; i < ECC_PRV_KEY_SIZE; ++i)
    {
        prvTrans[i] = prng_next();
    }
    ecdh_generate_keys(pubTrans, prvTrans);
}

static void init_rec_keys() {
    for (int i = 0; i < ECC_PRV_KEY_SIZE; ++i) {
        prvRec[i] = prng_next();
    }
    ecdh_generate_keys(pubRec, prvRec);
}

// The message is the public key (Rec) when the message is
//  coming from the receiver at the start of the cycle
void ecc_encrypt(unsigned char* msg, unsigned char* output) {
    // Force a reset of the pseudo
    //  rng for testing
    prng_init((0xbad ^ 0xc0ffee ^ 42) | 0xcafebabe | 666);
    
    // Generate our public key and send
    //  it to the receiver
    init_trans_keys();
    for (int i = 0; i < ECC_PUB_KEY_SIZE; i++) {
        output[i] = pubTrans[i];
    }
}

// The message is the public key (Trans) when the message is
//  coming from the transmitter at the end of the cycle
void ecc_decrypt(unsigned char* msg, unsigned char* output) {
    // Force a reset of the pseudo
    //  rng for testing
    prng_init((0xbad ^ 0xc0ffee ^ 42) | 0xcafebabe | 666);
    
    // Generate our public key and send
    //  it to the transmitter
    init_rec_keys();
    for (int i = 0; i < ECC_PUB_KEY_SIZE; i++) {
        output[i] = pubRec[i];
    }
}

void none_encrypt(unsigned char* msg, unsigned char* output) {
    strcpy(output, msg);
}

void none_decrypt(unsigned char* msg, unsigned char* output) {
    strcpy(output, msg);
}

// Use to encrypt outgoing wireless message
void Encrypt(unsigned char* msg, unsigned char* output) {
#if defined(ENC_NONE)
    none_encrypt(msg, output);
#elif defined(ENC_AES)
    aes_encrypt(msg, output);
#elif defined(ENC_DES)
    des_encrypt(msg, output);
#elif defined(ENC_ECC)
    ecc_encrypt(msg, output);
#endif
}

// Use to decrypt incoming wireless message
void Decrypt(unsigned char* cipher, unsigned char* output) {
#if defined(ENC_NONE)
    none_decrypt(cipher, output);
#elif defined(ENC_AES)
    aes_decrypt(cipher, output);
#elif defined(ENC_DES) 
    des_decrypt(cipher, output);
#elif defined(ENC_ECC) 
    ecc_decrypt(cipher, output);
#endif
}

#endif
