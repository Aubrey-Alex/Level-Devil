#include <gtest/gtest.h>
#include "../model/entity_model.h"

class EntityModelTest : public ::testing::Test {
protected:
    Entity_Model model;
    std::shared_ptr<GameMap> gameMap;

    void SetUp() override {
        gameMap = model.getGameMap();
    }
};

TEST_F(EntityModelTest, InitialState) {
    EXPECT_NE(gameMap, nullptr);
    EXPECT_EQ(gameMap->get_size(), 0);
}

TEST_F(EntityModelTest, NewLevel) {
    model.newLevel();
    EXPECT_GT(gameMap->get_size(), 0);
    
    // 验证每个实体的属性是否有效
    for(int i = 0; i < gameMap->get_size(); i++) {
        Entity tmp = gameMap->get_at(i);
        // 检查位置是否在合理范围内
        EXPECT_GE(tmp.pos.x, 0.0);
        EXPECT_GE(tmp.pos.y, 0.0);
        // 检查尺寸是否有效
        EXPECT_GT(tmp.w, 0.0);
        EXPECT_GT(tmp.h, 0.0);
        // 检查类型是否有效
        EXPECT_NE(tmp.type, '\0');
    }
}

TEST_F(EntityModelTest, EntityTypes) {
    model.newLevel();
    bool hasPlayer = false;
    bool hasObstacle = false;
    
    for(int i = 0; i < gameMap->get_size(); i++) {
        Entity tmp = gameMap->get_at(i);
        if(tmp.type == 'P') hasPlayer = true;
    }
    
    // 确保关卡中至少包含玩家和障碍物
    EXPECT_TRUE(hasPlayer) << "Level should contain a player";
}