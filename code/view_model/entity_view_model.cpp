#include "entity_view_model.h"
#include "../common/property_ids.h"

void Entity_View_Model::update() {
    auto gameMap = sp_Entity_Model->getGameMap();
    Player* player = nullptr;
    Spike* spike = nullptr;
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
                sp_Entity_Model->setCurrentLevel(sp_Entity_Model->getCurrentLevel() + 1);
                if (sp_Entity_Model->getCurrentLevel() > 2) {
                    fire(PropertyID::AllLevelComplete);
                } else {
                    fire(PropertyID::LevelComplete);
                }
                break;
            case PropertyID::PlayerDead:
                fire(PropertyID::PlayerDead);
                break;
            case PropertyID::NoChange:
                break;
            default:
                break;
        }
    }
}