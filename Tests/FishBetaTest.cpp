/**
 * @file FishBetaTest.cpp
 * @author James G
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <FishBeta.h>
#include <Aquarium.h>


/**
 * Test for construction of FishBeta object
 *
 * @return
 */
TEST(FishBetaTest, Construct)
{
    Aquarium aquarium;
    FishBeta betaFish(&aquarium);
}

