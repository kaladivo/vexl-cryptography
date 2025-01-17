//
// Created by Adam Salih on 29.03.2022.
//

#include "Tools.h"

void _print_time(double time_in_ms) {
    if (time_in_ms < 1000) {
        printf("%.4f ms", time_in_ms);
    } else if (time_in_ms < 60*1000) {
        printf("%.4f s", time_in_ms/1000);
    } else {
        printf("%.4f m", time_in_ms/60000);
    }
}

void log_asymetric_performance_header() {
    printf(ANSI_COLOR_GREEN "Curve\t\t\tTotal time\t\tKeypair time\t\tEncryption time\t\tDecryption time\t\tSigning time\t\tVerification time\n" ANSI_COLOR_RESET);
}

void log_asymetric_performance(char *curveName, clock_t key_gen_start, clock_t encryption_start, clock_t decryption_start, clock_t ecdsa_sign_start, clock_t ecdsa_verify_start, clock_t end) {
    printf(ANSI_COLOR_GREEN "%s\t\t", curveName);

    double key_gen_time_in_ms = ((double)(encryption_start - key_gen_start) / CLOCKS_PER_SEC) * 1000;
    double encryption_time_in_ms = ((double)(decryption_start - encryption_start) / CLOCKS_PER_SEC) * 1000;
    double decryption_time_in_ms = ((double)(ecdsa_sign_start - decryption_start) / CLOCKS_PER_SEC) * 1000;
    double signing_time_in_ms = ((double)(ecdsa_verify_start - ecdsa_sign_start) / CLOCKS_PER_SEC) * 1000;
    double verification_time_in_ms = ((double)(end - ecdsa_verify_start) / CLOCKS_PER_SEC) * 1000;
    double total_time_in_ms = ((double)(end - encryption_start) / CLOCKS_PER_SEC) * 1000;

    _print_time(total_time_in_ms);
    printf("\t\t");
    _print_time(key_gen_time_in_ms);
    printf("\t\t");
    _print_time(encryption_time_in_ms);
    printf("\t\t");
    _print_time(decryption_time_in_ms);
    printf("\t\t");
    _print_time(signing_time_in_ms);
    printf("\t\t");
    _print_time(verification_time_in_ms);
    printf("\n" ANSI_COLOR_RESET);
}

void log_symetric_performance(clock_t encryption_start, clock_t decryption_start, clock_t sign_start, clock_t verify_start, clock_t end) {
    printf(ANSI_COLOR_GREEN);

    double encryption_time_in_ms = ((double)(decryption_start - encryption_start) / CLOCKS_PER_SEC) * 1000;
    double decryption_time_in_ms = ((double)(sign_start - decryption_start) / CLOCKS_PER_SEC) * 1000;
    double signing_time_in_ms = ((double)(verify_start - sign_start) / CLOCKS_PER_SEC) * 1000;
    double verification_time_in_ms = ((double)(end - verify_start) / CLOCKS_PER_SEC) * 1000;
    double total_time_in_ms = ((double)(end - encryption_start) / CLOCKS_PER_SEC) * 1000;

    printf("AES encryption:\t\t");
    _print_time(encryption_time_in_ms);
    printf("\n");

    printf("AES decryption:\t\t");
    _print_time(decryption_time_in_ms);
    printf("\n");

    printf("HMAC digest:\t\t");
    _print_time(signing_time_in_ms);
    printf("\n");

    printf("HMAC verification:\t");
    _print_time(verification_time_in_ms);
    printf("\n");

    printf("Total time:\t\t");
    _print_time(total_time_in_ms);
    printf("\n" ANSI_COLOR_RESET);
}

void log_message(const char *message, ...) {
    printf("\n➡️ ");
    va_list argptr;
    va_start(argptr, message);
    vfprintf(stdout, message, argptr);
    va_end(argptr);
    printf("\n");
}

void log_progress(const char *message, ...) {
    printf("\33[2K\r");
    printf("ℹ️ ");
    va_list argptr;
    va_start(argptr, message);
    vfprintf(stdout, message, argptr);
    va_end(argptr);
}

void log_progress_end() {
    printf("\33[2K\r");
}

void log_success(const char *message, ...) {
    printf(ANSI_COLOR_GREEN "✅ ");
    va_list argptr;
    va_start(argptr, message);
    vfprintf(stdout, message, argptr);
    va_end(argptr);
    printf("\n" ANSI_COLOR_RESET);
}

void log_error(const char *message, ...) {
    printf(ANSI_COLOR_RED "🔥 ");
    va_list argptr;
    va_start(argptr, message);
    vfprintf(stdout, message, argptr);
    va_end(argptr);
    printf("\n" ANSI_COLOR_RESET);
}

bool assert_equals(const char *str1, const char *str2, const char *message) {
    if (strcmp(str1, str2) != 0) {
        log_error("Assertion error: These two values do not equal\n\tstr1: %s\n\tstr2: %s", str1, str2);
        return false;
    }
    log_success(message);
    return true;
}

bool assert_not_equals(const char *str1, const char *str2, const char *message) {
    if (str1 == NULL || str2 == NULL) {
        if (str1 == str2) {
            log_error("Assertion error: These two values equals\n\tstr1: %s\n\tstr2: %s", str1, str2);
            return false;
        }
        log_success(message);
        return true;
    }
    if (strcmp(str1, str2) == 0) {
        log_error("Assertion error: These two values equals\n\tstr1: %s\n\tstr2: %s", str1, str2);
        return false;
    }
    log_success(message);
    return true;
}

bool assert_true(int val, const char *message) {
    if (!val) {
        log_error("Assertion error: expression is not evaluated as true");
        return false;
    }
    log_success(message);
    return true;
}

bool assert_not_null(const void *ptr, const char *message) {
    if (ptr == NULL) {
        log_error("Assertion error: Pointer is NULL");
        return false;
    }
    log_success(message);
    return true;
}

bool assert_null(const void *ptr, const char *message) {
    if (ptr != NULL) {
        log_error("Assertion error: Pointer is not NULL");
        return false;
    }
    log_success(message);
    return true;
}
