/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <openssl/stack.h>

extern "C" void* sk_delete(OPENSSL_STACK* stack, int where);

TEST(StackDelete, RemovesAndReturnsSelectedElement) {
    int first = 1;
    int middle = 2;
    int last = 3;
    OPENSSL_STACK* stack = OPENSSL_sk_new_null();
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(OPENSSL_sk_push(stack, &first), 0u);
    ASSERT_NE(OPENSSL_sk_push(stack, &middle), 0u);
    ASSERT_NE(OPENSSL_sk_push(stack, &last), 0u);

    EXPECT_EQ(sk_delete(stack, 1), &middle);
    EXPECT_EQ(OPENSSL_sk_num(stack), 2u);
    EXPECT_EQ(OPENSSL_sk_value(stack, 0), &first);
    EXPECT_EQ(OPENSSL_sk_value(stack, 1), &last);
    OPENSSL_sk_free(stack);
}

TEST(StackDelete, NegativeIndexDoesNotModifyStack) {
    int value = 1;
    OPENSSL_STACK* stack = OPENSSL_sk_new_null();
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(OPENSSL_sk_push(stack, &value), 0u);
    EXPECT_EQ(sk_delete(stack, -1), nullptr);
    EXPECT_EQ(OPENSSL_sk_num(stack), 1u);
    EXPECT_EQ(OPENSSL_sk_value(stack, 0), &value);
    OPENSSL_sk_free(stack);
}

TEST(StackDelete, OutOfBoundsIndexDoesNotModifyStack) {
    int value = 1;
    OPENSSL_STACK* stack = OPENSSL_sk_new_null();
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(OPENSSL_sk_push(stack, &value), 0u);
    EXPECT_EQ(sk_delete(stack, 1), nullptr);
    EXPECT_EQ(sk_delete(stack, 2147483647), nullptr);
    EXPECT_EQ(OPENSSL_sk_num(stack), 1u);
    OPENSSL_sk_free(stack);
}

TEST(StackDelete, NullStackReturnsNull) {
    EXPECT_EQ(sk_delete(nullptr, 0), nullptr);
    EXPECT_EQ(sk_delete(nullptr, -1), nullptr);
}
