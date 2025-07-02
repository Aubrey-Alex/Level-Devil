#include "entity_view_model.h"
#include "../common/property_ids.h"

void Entity_View_Model::update() {
    auto gameMap = sp_Entity_Model->getGameMap();
    Player* player = nullptr;
    for (size_t i = 0; i < gameMap->get_size(); i++) {
        auto& entity = gameMap->get_at(i);
        if (entity.type == 'P') {
            player = static_cast<Player*>(&entity);
            break;
        }
    }
    if (player) {
        if (m_moveLeftActive) player->MoveLeft();
        if (m_moveRightActive) player->MoveRight();
        if (m_jumpRequested) {
            player->Jump(); 
            m_jumpRequested = false;
        }
        if (!m_moveLeftActive && !m_moveRightActive) player->Stop();
        
        PropertyID state = sp_Entity_Model->update();
        switch(state) {
            case PropertyID::PlayerPositionChanged:
                fire(PropertyID::PlayerPositionChanged);
                break;
            case PropertyID::LevelComplete:
                fire(PropertyID::LevelStateChanged);
                break;
            case PropertyID::GameOver:
                fire(PropertyID::GameStateChanged);
                break;
            case PropertyID::NoChange:
                break;
        }
    }
}