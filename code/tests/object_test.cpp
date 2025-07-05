#include <gtest/gtest.h>
#include "../model/object.h"

class ObjectTest : public ::testing::Test {
protected:
    std::shared_ptr<GameMap> gameMap;

    void SetUp() override {
        gameMap = std::make_shared<GameMap>();
    }

    void addEntity(std::shared_ptr<Entity> entity) {
        gameMap->append(entity);
    }
};

TEST_F(ObjectTest, PlayerInitialization) {
    Player player(100, 200, 5.0);
    EXPECT_EQ(player.pos.x, 100);
    EXPECT_EQ(player.pos.y, 200);
    EXPECT_EQ(player.type, 'P');
    EXPECT_EQ(player.w, size_w);
    EXPECT_EQ(player.h, size_h);
}

TEST_F(ObjectTest, PlayerMovement) {
    auto player = std::make_shared<Player>(100, 200, 5.0);
    addEntity(player);
    
    // Test horizontal movement
    player->MoveRight();
    auto result = player->update(gameMap);
    EXPECT_GT(player->pos.x, 100) << "Player should move right";
    
    player->Stop();
    double lastX = player->pos.x;
    result = player->update(gameMap);
    EXPECT_EQ(player->pos.x, lastX) << "Player should stop when no movement keys are pressed";
    
    player->MoveLeft();
    result = player->update(gameMap);
    EXPECT_LT(player->pos.x, lastX) << "Player should move left";
}

TEST_F(ObjectTest, PlayerJump) {
    auto player = std::make_shared<Player>(100, 200, 5.0);
    addEntity(player);
    double initialY = player->pos.y;
    
    player->Jump();
    auto result = player->update(gameMap);
    EXPECT_LT(player->pos.y, initialY) << "Player should move up when jumping";
    
    // Let gravity act for several frames
    for(int i = 0; i < 60; i++) {
        result = player->update(gameMap);
    }
    EXPECT_GT(player->pos.y, initialY) << "Player should fall due to gravity";
}

TEST_F(ObjectTest, WallProperties) {
    auto wall = std::make_shared<Wall>(50, 50, 100, 200, 5);
    addEntity(wall);
    EXPECT_EQ(wall->pos.x, 50);
    EXPECT_EQ(wall->pos.y, 50);
    EXPECT_EQ(wall->w, 100);
    EXPECT_EQ(wall->h, 200);
    EXPECT_EQ(wall->type, 'W');
    EXPECT_EQ(wall->get_visible_dis(), 5);
}

TEST_F(ObjectTest, DoorInitialization) {
    auto door = std::make_shared<Door>(300, 400);
    addEntity(door);
    EXPECT_EQ(door->pos.x, 300);
    EXPECT_EQ(door->pos.y, 400);
    EXPECT_EQ(door->type, 'D');
    EXPECT_EQ(door->w, 40);
    EXPECT_EQ(door->h, 40);
} 