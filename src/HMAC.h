//
// Created by Adam Salih on 04.04.2022.
//

#ifndef HMAC_H
#define HMAC_H

#include <stdio.h>
#include <stdbool.h>

#ifdef BUILD_FOR_LIBRARY

#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/hmac.h>

#endif

#include "common/Constants.h"

char *hmac_digest(const char *password, const char *message);
bool hmac_verify(const char *password, const char *message, const char *digest);
void _hmac_digest(const char *password, const int password_len, const char *message, const int message_len, char **digest, int *digest_len);
bool _hmac_verify(const char *password, const int password_len, const char *message, const int message_len, const char *digest, const int digest_len);


#endif
