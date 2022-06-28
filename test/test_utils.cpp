#include <unity.h>
#include <Arduino.h>
#include "../src/utils.h"

void setUp(void) {

}

void tearDown(void) {

}

void test_triangle_modulo(void) {
    uint16_t scale = 256;
    TEST_ASSERT_EQUAL_INT16(0, triangle_modulo(0, scale));
    TEST_ASSERT_EQUAL_INT16(128, triangle_modulo(128, scale));
    TEST_ASSERT_EQUAL_INT16(255, triangle_modulo(255, scale));
    TEST_ASSERT_EQUAL_INT16(255, triangle_modulo(256, scale));
    TEST_ASSERT_EQUAL_INT16(127, triangle_modulo(384, scale));
    TEST_ASSERT_EQUAL_INT16(1, triangle_modulo(510, scale));
    TEST_ASSERT_EQUAL_INT16(0, triangle_modulo(511, scale));
    TEST_ASSERT_EQUAL_INT16(0, triangle_modulo(512, scale));
    TEST_ASSERT_EQUAL_INT16(1, triangle_modulo(513, scale));
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_triangle_modulo);
    return UNITY_END();
}

void setup() {
    delay(2000);
    runUnityTests();
}

void loop() {
}
