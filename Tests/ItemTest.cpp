/**
 * @file ItemTest.cpp
 * @author joshc
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <StopWatch.h>
/// Item filename
const std::wstring ItemImage = L"sparty-1.png";

class TestApp : public wxApp{
public:
    virtual bool OnInit(){
        wxApp::OnInit();
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(TestApp);
/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, ItemImage, "i404", 0, 0, wxEmptyString) {}

};

class GameTest : public ::testing::Test{
protected:
    Game game;
    void SetUp() override{
        game.InitializeTimer();
        game.GetStopWatch().Start(100);
    }

};
TEST(StopWatchTest, StopWatch)
{
    StopWatch TestWatch(0);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "0:00");
}


TEST(ItemTest, Construct)
{
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, SetLocation)
{
    Game game;
    ItemMock item(&game);

    item.SetLocation(0, 0);
    ASSERT_EQ(0, item.GetCol());
    ASSERT_EQ(0, item.GetRow());

    item.SetLocation(17, 23);
    ASSERT_EQ(17, item.GetCol());
    ASSERT_EQ(23, item.GetRow());
}
TEST(ItemTest, HitTest) {
    // Create a fish to test
    Game game;
    ItemMock item(&game);

    // Give it a location
    // Always make the numbers different, in case they are mixed up
    item.SetLocation(100, 200);

    // Center of the item should be a true
    ASSERT_TRUE(item.HitTest(100, 200));

    // Left of the item
    ASSERT_FALSE(item.HitTest(10, 200));

    // Right of the item
    ASSERT_FALSE(item.HitTest(200, 200));

    // Above the item
    ASSERT_FALSE(item.HitTest(100, 0));

    // Below the item
    ASSERT_FALSE(item.HitTest(100, 300));


}

TEST_F(GameTest, TimerInitialiazation){
    ASSERT_GE(game.GetStopWatch().Time(), 0);
    ASSERT_GE(game.GetStopWatch2().Time(), 0);
}