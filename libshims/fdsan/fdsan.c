/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android/fdsan.h>

/*
 * libexynoscamera3 closes fence fds that are owned by a unique_fd, which makes
 * fdsan abort the camera provider. Only warn in the processes that load it.
 */
__attribute__((constructor)) static void shim_fdsan_init(void) {
    android_fdsan_set_error_level(ANDROID_FDSAN_ERROR_LEVEL_WARN_ONCE);
}
