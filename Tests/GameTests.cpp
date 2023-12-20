/**
 * @file GameTests.cpp
 * @author Joshua Costantino
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <Digit.h>
#include <StopWatch.h>


using namespace std;

const unsigned int RandomSeed = 1238197374;

/// Item filename
const std::wstring ItemImage = L"sparty-1.png";

class GameTests : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/game";
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


    void TestMockItems(wxString filename)
    {

        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure 3 declarations
        ASSERT_TRUE(regex_search(xml, wregex(L"<level><declarations.*<item.*<item.*<item.*</declarations>")));
        // Ensure 3 items
        ASSERT_TRUE(regex_search(xml, wregex(L"<game/><items.*<item.*<item.*item.*</items.*</level>")));

        // test declarations
        ASSERT_TRUE(regex_search(xml, wregex(L"item id=\"i404\" col=\"0\" row=\"0\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"item id=\"i505\" col=\"2\" row=\"3\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"item id=\"i606\" col=\"15\" row=\"8\"")));

    }

};

TEST_F(GameTests, Construct){
    Game game;
}


TEST_F(GameTests, Clear)
{
    Game game;

    std::shared_ptr<Item> testDig = std::make_shared<Digit>(&game, ItemImage, "0", 48, 48, wxEmptyString, 0);

    testDig->SetLocation(0, 0);

    game.SetDeclaration("0", testDig);

    game.InitDeclaration("0", 0 , 0);

    ASSERT_TRUE(game.HitTest(0, 0));

    game.Clear();

    ASSERT_FALSE(game.HitTest(0, 0));

}


TEST_F(GameTests, Load) {

    Game game;

    game.Load(L"levels/level1.xml");

    // Test that game height and width are loaded correctly
    ASSERT_EQ(game.GetHeight(), 15);
    ASSERT_EQ(game.GetWidth(), 20);

    // Test that tile height and width are loaded correctly
    ASSERT_EQ(game.GetTileHeight(), 48);
    ASSERT_EQ(game.GetTileWidth(), 48);

    // test that solution is loaded correctly
    ASSERT_EQ(game.GetSolution(), L"7 3 1 4 6 5 8 0 2 2 6 5 0 7 8 1 3 4 8 4 0 3 2 1 7 5 6 3 0 2 1 4 7 5 6 8 4 1 8 6 5 3 0 2 7 5 7 6 8 0 2 3 4 1 1 5 7 2 3 4 6 8 0 0 8 4 5 1 6 2 7 3 6 2 3 7 8 0 4 1 5");

    // Test that item widths and heights are loading
    auto decTest = game.GetDeclaration("i600")->GetWidth();
    ASSERT_EQ(decTest, 960);
    decTest = game.GetDeclaration("i600")->GetHeight();
    ASSERT_EQ(decTest, 720);

}
TEST_F(GameTests, Load2) {

    Game game;

    game.Load(L"levels/level2.xml");

    // Test that game height and width are loaded correctly
    ASSERT_EQ(game.GetHeight(), 20);
    ASSERT_EQ(game.GetWidth(), 30);

    // Test that tile height and width are loaded correctly
    ASSERT_EQ(game.GetTileHeight(), 48);
    ASSERT_EQ(game.GetTileWidth(), 48);

    // test that solution is loaded correctly
    ASSERT_EQ(game.GetSolution(), L"5 2 6 7 0 3 4 1 8 3 4 0 2 8 1 5 7 6 8 1 7 5 4 6 0 3 2 2 0 3 4 1 7 8 6 5 4 5 8 6 3 0 7 2 1 7 6 1 8 5 2 3 0 4 1 7 4 3 6 5 2 8 0 6 3 5 0 2 8 1 4 7 0 8 2 1 7 4 6 5 3");

    // Test that item widths and heights are loading
    auto decTest = game.GetDeclaration("i245")->GetWidth();
    ASSERT_EQ(decTest, 528);
    decTest = game.GetDeclaration("i245")->GetHeight();
    ASSERT_EQ(decTest, 528);

}


