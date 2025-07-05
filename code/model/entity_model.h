#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H
#include "../common/notifier.h"
#include "object.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
#include <filesystem>

class Entity_Model {
private:
    std::shared_ptr<GameMap> sp_GameMap;
    int currentLevel = 1; // 当前关卡编号
public:
    int MovingSpikeCount = 0; // 记录当前关卡中移动刺的数量
    int deathCount = 0; // 死亡次数计数器
    
    Entity_Model(): sp_GameMap(std::make_shared<GameMap>()) {}
    int getCurrentLevel() const { return currentLevel; }
    void setCurrentLevel(int lv) { currentLevel = lv; }
    
    // 死亡次数相关方法
    int getDeathCount() const { return deathCount; }
    void incrementDeathCount() { deathCount++; }
    void resetDeathCount() { deathCount = 0; }

    std::shared_ptr<GameMap> getGameMap() { return sp_GameMap; }

    void loadMapFromJson(const std::string& filename);

    void newLevel();

    PropertyID update();
};
#endif