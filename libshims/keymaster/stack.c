/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <openssl/stack.h>

void* sk_delete(OPENSSL_STACK* stack, int where) {
    if (where < 0) return NULL;
    return OPENSSL_sk_delete(stack, (size_t)where);
}
