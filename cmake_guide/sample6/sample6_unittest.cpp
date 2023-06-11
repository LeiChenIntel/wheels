#include "Calculations.h"
#include "gtest/gtest.h"

const float esplion = 1e-6;

TEST(Calculations, add) {
    EXPECT_LE(add(1.2, 3.4) - (1.2 + 3.4), esplion);
}

TEST(Calculations, sub) {
    EXPECT_LE(subtract(1.2, 3.4) - (1.2 - 3.4), esplion);
}

TEST(Calculations, mul) {
    EXPECT_LE(multiple(1.2, 3.4) - 1.2 * 3.4, esplion);
}

TEST(Calculations, div) {
    EXPECT_LE(divide(1.2, 3.4) - 1.2 / 3.4, esplion);
}
