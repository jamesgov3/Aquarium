/**
 * @file AquariumTest.cpp
 * @author James Gove
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filename.h>
#include <memory>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <Aquarium.h>
#include <FishBeta.h>
#include <FishBubbles.h>
#include <FishSparty.h>
#include <DecorCastle.h>


using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     *  Populate an aquarium with three Beta fish
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    /**
     * Test to ensure an aquarium .aqua file has fish items documented.
     */
    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        // Ensure the speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"44\\.8964\" speedy=\"0\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"46\\.8677\" speedy=\"0\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"46\\.8932\" speedy=\"0\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
    }

    /**
     * Populate an aquarium with all supported item types
     */
    void PopulateAllTypes(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBubbles>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(200, 300);

        auto fish3 = make_shared<FishSparty>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(300, 400);

        auto decor1 = make_shared<DecorCastle>(aquarium);
        aquarium->Add(decor1);
        decor1->SetLocation(400, 500);
    }

    /**
     * Test to ensure an aquarium .aqua file contains all type nodes
     */
    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure four items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

        // Ensure correct positions
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"200\" y=\"300\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"300\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"500\"")));

        // Ensure the speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"44\\.8964\" speedy=\"0\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"93\\.7355\" speedy=\"0\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* speedx=\"16\\.8932\" speedy=\"0\"")));

        // Ensure all types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"bubbles\"/><item.* type=\"sparty\"/><item.* type=\"castle\"/></aqua>")));
    }
};

/**
 * Test for successful construction of an Aquarium object.
 *
 * @return
 */
TEST_F(AquariumTest, Construct)
{
    Aquarium aquarium;
}

/**
 * Test for successful aquarium HitTest execution
 *
 * @return
 */
TEST_F(AquariumTest, HitTest)
{
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
        L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
        L"Testing fish at 100, 200";
}

/**
 * Test hit detection outside of existing fish coords
 * @return
 */
TEST_F(AquariumTest, HitTestOffImg)
{
    Aquarium aquarium;

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    fish1->SetLocation(100, 200);

    // HitTest should return nullptr when clicking where no image exists
    ASSERT_TRUE(aquarium.HitTest(300, 400) == nullptr) <<
        L"Testing vacant coordinate in populated aquarium";
}

/**
 * Test hit detection on stacked fish
 * @return
 */
TEST_F(AquariumTest, HitTestTopImg)
{
    Aquarium aquarium;

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);

    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);

    // This should stack two fish on top of each other
    // The last fish set should be on top
    fish1->SetLocation(100, 200);
    fish2->SetLocation(100, 200);

    ASSERT_EQ(aquarium.HitTest(100, 200), fish2) <<
        L"Testing Hit on stacked fish";
}

/**
 * Test save function handling
 * @return
 */
TEST_F(AquariumTest, Save) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    //
    // Test all types save in new aquarium
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
}

/**
 * Test that aquarium.Clear function clears all items
 * @return
 */
TEST_F(AquariumTest, Clear)
{
    // Create path for temp files
    auto path = TempPath();

    Aquarium aquarium;

    //
    // Populate aquarium
    //
    PopulateAllTypes(&aquarium);

    //
    // Clear aquarium and save to file
    //
    aquarium.Clear();
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);
}

TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create aquariums
    Aquarium aquarium;
    Aquarium aquarium2;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);

    aquarium2.Load(file3);
    aquarium2.Save(file3);
    TestAllTypes(file3);
}

