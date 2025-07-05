#include <gtest/gtest.h>
#include "../model/object.h"

class CollisionTest : public ::testing::Test {
protected:
    std::shared_ptr<GameMap> gameMap;
    std::shared_ptr<Player> player;

    void SetUp() override {
        gameMap = std::make_shared<GameMap>();
        player = std::make_shared<Player>(100, 100, 5.0);
        gameMap->append(player);
    }

    void addWall(double x, double y, double w, double h) {
        gameMap->append(std::make_shared<Wall>(x, y, w, h));
    }
};

TEST_F(CollisionTest, NoCollision) {
    // Wall far from player
    addWall(500, 500, 100, 100);
    
    EXPECT_FALSE(player->checkCollision(player->pos.x, player->pos.y, 'W', gameMap));
    EXPECT_FALSE(player->checkCollisionUp(player->pos.x, player->pos.y, gameMap));
    EXPECT_FALSE(player->checkCollisionDown(player->pos.x, player->pos.y, gameMap));
    EXPECT_FALSE(player->checkCollisionLeft(player->pos.x, player->pos.y, gameMap));
    EXPECT_FALSE(player->checkCollisionRight(player->pos.x, player->pos.y, gameMap));
}

TEST_F(CollisionTest, SpikeCollision) {
    // Add a spike
    gameMap->append(std::make_shared<MovingSpike>(
        player->pos.x + 20, player->pos.y, 
        player->pos.x, player->pos.x + 100, 
        5.0));
    
    EXPECT_TRUE(player->checkCollision(player->pos.x, player->pos.y, 'S', gameMap));
}

TEST_F(CollisionTest, DoorCollision) {
    // Add a door
    gameMap->append(std::make_shared<Door>(player->pos.x + 20, player->pos.y));
    
    EXPECT_TRUE(player->checkCollision(player->pos.x, player->pos.y, 'D', gameMap));
}