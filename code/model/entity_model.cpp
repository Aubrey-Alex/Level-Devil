#include "entity_model.h"

void Entity_Model::loadMapFromJson(const std::string& filename) {
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
        auto wall = std::make_shared<Wall>(x, y, w, h);
        sp_GameMap->append(wall);
    }
    auto spikesJson = jsonData["entities"]["spikes"];
    for (const auto& spikeJson : spikesJson) {
        auto pos = spikeJson["position"];
        int x = pos["x"].get<int>();
        int y = pos["y"].get<int>();
        int d = pos["is_unvisible"].get<int>();
        auto spike = std::make_shared<Spike>(x, y, d);
        sp_GameMap->append(spike);
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
}

void Entity_Model::newLevel(int level) {
    if(level == 1) {
        std::filesystem::path currentFile = __FILE__;
        auto jsonPath = currentFile.parent_path() / "level1.json";
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