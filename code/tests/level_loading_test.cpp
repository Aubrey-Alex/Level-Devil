#include <gtest/gtest.h>
#include "../model/entity_model.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

using json = nlohmann::json;

class LevelLoadingTest : public ::testing::Test {
protected:
    Entity_Model model;
    std::shared_ptr<GameMap> gameMap;

    void SetUp() override {
        gameMap = model.getGameMap();
    }

    bool hasEntityType(char type) {
        for(int i = 0; i < gameMap->get_size(); i++) {
            if(gameMap->get_at(i).type == type) return true;
        }
        return false;
    }

    int countEntityType(char type) {
        int count = 0;
        for(int i = 0; i < gameMap->get_size(); i++) {
            if(gameMap->get_at(i).type == type) count++;
        }
        return count;
    }

    void loadLevelFile(int level) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path().parent_path() / "model" / ("level" + std::to_string(level) + ".json");
        model.loadMapFromJson(jsonPath.string());
        model.setCurrentLevel(level);
    }
};

TEST_F(LevelLoadingTest, LoadLevel1) {
    loadLevelFile(1);
    
    // Basic level requirements
    EXPECT_GT(gameMap->get_size(), 0) << "Level should have entities";
    EXPECT_TRUE(hasEntityType('P')) << "Level should have a player";
    EXPECT_TRUE(hasEntityType('W')) << "Level should have walls";
    EXPECT_EQ(countEntityType('P'), 1) << "Level should have exactly one player";
    EXPECT_TRUE(hasEntityType('D')) << "Level should have a door";
}

TEST_F(LevelLoadingTest, LoadLevel2) {
    loadLevelFile(2);
    
    // Level 2 specific requirements
    EXPECT_GT(gameMap->get_size(), 0);
    EXPECT_TRUE(hasEntityType('P'));
    EXPECT_TRUE(hasEntityType('W'));
}

TEST_F(LevelLoadingTest, LoadLevel3) {
    loadLevelFile(3);
    
    // Level 3 specific requirements
    EXPECT_GT(gameMap->get_size(), 0);
    EXPECT_TRUE(hasEntityType('P'));
    EXPECT_TRUE(hasEntityType('W'));
    EXPECT_TRUE(hasEntityType('U')) << "Level 3 should have invisible spikes";
}

TEST_F(LevelLoadingTest, LoadLevel4) {
    loadLevelFile(4);
    
    // Level 4 specific requirements
    EXPECT_GT(gameMap->get_size(), 0);
    EXPECT_TRUE(hasEntityType('P'));
    EXPECT_TRUE(hasEntityType('W'));
    EXPECT_TRUE(hasEntityType('S') || hasEntityType('U')) << "Level 4 should have spikes";
}

TEST_F(LevelLoadingTest, EntityPositions) {
    loadLevelFile(1);
    
    // Check that entities are within reasonable bounds
    for(int i = 0; i < gameMap->get_size(); i++) {
        Entity entity = gameMap->get_at(i);
        EXPECT_GE(entity.pos.x, 0) << "Entity X position should be non-negative";
        EXPECT_GE(entity.pos.y, 0) << "Entity Y position should be non-negative";
        EXPECT_GT(entity.w, 0) << "Entity width should be positive";
        EXPECT_GT(entity.h, 0) << "Entity height should be positive";
    }
}

TEST_F(LevelLoadingTest, LevelProgression) {
    // Test that we can progress through all levels
    for(int level = 1; level <= 4; level++) {
        EXPECT_NO_THROW(loadLevelFile(level)) 
            << "Should be able to load level " << level;
        
        // Basic validation for each level
        EXPECT_GT(gameMap->get_size(), 0);
        EXPECT_TRUE(hasEntityType('P'));
        EXPECT_TRUE(hasEntityType('W'));
        EXPECT_TRUE(hasEntityType('D'));
    }
} 