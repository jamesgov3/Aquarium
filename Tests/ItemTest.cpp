/**
 * @file ItemTest.cpp
 * @author James Gove
 */

#include <pch.h>
#include <string>
#include "gtest/gtest.h"
#include <Item.h>
#include <Aquarium.h>

/// Fish filename
const std::wstring FishBetaImageName = L"images/beta.png";

/**
 * Mock class for testing the Item class.
 */
class ItemMock : public Item {
public:
    ItemMock(Aquarium *aquarium) : Item(aquarium, FishBetaImageName) {}

    void Draw(wxDC *dc) override {}
};

/**
 * Test constructor for creating an Item
 * @return
 */
TEST(ItemTest, Construct)
{
    Aquarium aquarium;
    ItemMock item(&aquarium);
}

/**
 * Test each Item class Getter and Setter functions
 * @return
 */
TEST(ItemTest, GettersSetters)
{
    Aquarium aquarium;
    ItemMock item(&aquarium);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test again with different values
    item.SetLocation(-100, -52);
    ASSERT_NEAR(-100, item.GetX(), 0.0001);
    ASSERT_NEAR(-52, item.GetY(), 0.0001);
}

/**
 * Test HitTest function return value for various locations
 *
 * @return
 */
TEST(ItemTest, HitTest)
{
	// Create a fish to test
	Aquarium aquarium;
	ItemMock fish(&aquarium);

	// Give fish a location
	// Always make numbers different in case of mixup
	fish.SetLocation(100, 200);

	// Center of fish should be true
	ASSERT_TRUE(fish.HitTest(100, 200));

	// Left side
	ASSERT_FALSE(fish.HitTest(10, 200));

	// Right side
	ASSERT_FALSE(fish.HitTest(200, 200));

	// Above
	ASSERT_FALSE(fish.HitTest(100, 0));

	// Below
	ASSERT_FALSE(fish.HitTest(100, 300));

	// On transparent pixel
	ASSERT_FALSE(fish.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));
}

