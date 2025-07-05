#include "entity_model.h"

void Entity_Model::loadMapFromJson(const std::string& filename) {
    sp_GameMap->clear(); // Clear the existing map before loading a new one
    std::ifstream file(filename);
    nlohmann::json jsonData;
    file >> jsonData;
    
    auto wallsJson = jsonData["entities"]["walls"];
    for (const auto& wallJson : wallsJson) {
        auto pos = wallJson["position"];
        auto size = wallJson["size"];
        int x = pos["x"].get<int>();
        int y = pos["y"].get<int>();
        int w = size["width"].get<int>();
        int h = size["height"].get<int>();
        int visible_dis = -1;
        if (wallJson.contains("visible_dis")) {
            visible_dis = wallJson["visible_dis"].get<int>();
        }
        auto wall = std::make_shared<Wall>(x, y, w, h, visible_dis);
        sp_GameMap->append(wall);
    }
    auto playerJson = jsonData["entities"]["player"]; {
        auto pos = playerJson["position"];
        int x = pos["x"].get<int>();
        int y = pos["y"].get<int>();
        int v = pos["v"].get<int>();
        auto player = std::make_shared<Player>(x, y, v);
        sp_GameMap->append(player);
    }
    auto doorJson = jsonData["entities"]["door"]; {
        auto pos = doorJson["position"];
        int x = pos["x"].get<int>();
        int y = pos["y"].get<int>();
        auto door = std::make_shared<Door>(x, y);
        sp_GameMap->append(door);
    }
    auto movingspikesJson = jsonData["entities"].contains("moving_spikes") ? jsonData["entities"]["moving_spikes"] : nlohmann::json::array();
    for (const auto& mspikeJson : movingspikesJson) {
        auto pos = mspikeJson["position"];
        int x = pos["x"].get<int>();
        int y = pos["y"].get<int>();
        double left = mspikeJson["left_bound"].get<double>();
        double right = mspikeJson["right_bound"].get<double>();
        double speed = mspikeJson["speed"].get<double>();
        int visible_dis = -1;
        if (mspikeJson.contains("visible_dis")) {
            visible_dis = mspikeJson["visible_dis"].get<int>();
        }
        auto mspike = std::make_shared<MovingSpike>(x, y, left, right, speed, visible_dis);
        sp_GameMap->append(mspike);
    }
}

void Entity_Model::newLevel() {
    printf("Loading level %d\n", currentLevel); // 调试信息
    if(currentLevel == 1) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level1.json";
        printf("Loading file: %s\n", jsonPath.string().c_str()); // 调试信息
        loadMapFromJson(jsonPath.string());
    }
    else if(currentLevel == 2) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level2.json";
        printf("Loading file: %s\n", jsonPath.string().c_str()); // 调试信息
        loadMapFromJson(jsonPath.string());
    }
    else if(currentLevel == 3) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level3.json";
        printf("Loading file: %s\n", jsonPath.string().c_str()); // 调试信息
        loadMapFromJson(jsonPath.string());
    }
    else if(currentLevel == 4) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level4.json";
        printf("Loading file: %s\n", jsonPath.string().c_str()); // 调试信息
        loadMapFromJson(jsonPath.string());
    }
    else if(currentLevel == 3) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level3.json";
        loadMapFromJson(jsonPath.string());
    }
    else if(currentLevel == 4) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level4.json";
        loadMapFromJson(jsonPath.string());
    }
}

PropertyID Entity_Model::update() {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type == 'P') {
            auto* player = static_cast<Player*>(&entity);
            PropertyID result = player->update(sp_GameMap);//game state
            return result;
        }
    }
    return PropertyID::NoChange;
}