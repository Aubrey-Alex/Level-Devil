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
    Entity_Model(): sp_GameMap(std::make_shared<GameMap>()) {}
    int getCurrentLevel() const { return currentLevel; }
    void setCurrentLevel(int lv) { currentLevel = lv; }

    std::shared_ptr<GameMap> getGameMap() { return sp_GameMap; }

    void loadMapFromJson(const std::string& filename);

    void newLevel();

    PropertyID update();
};
#endif