#ifndef ENTITY_VIEW_MODEL_H
#define ENTITY_VIEW_MODEL_H
#include "../model/entity_model.h"
#include "../common/frame.h"
#include "../common/commands.h"
#include <functional>
class Entity_View_Model: public IViewModel {
private:
    std::shared_ptr<Entity_Model> sp_Entity_Model;
    bool m_moveLeftActive = false;
    bool m_moveRightActive = false;
    bool m_jumpRequested = false;
public:
    Entity_View_Model(std::shared_ptr<Entity_Model> model): sp_Entity_Model(std::move(model)) {
        sp_Entity_Model->newLevel(1);
    }
    void startMoveLeft() {
        m_moveLeftActive = true;
    }
    void startMoveRight() {
        m_moveRightActive = true;
    }
    void stopMove() {
        m_moveLeftActive = false;
        m_moveRightActive = false;
    }
    void jump() {
        m_jumpRequested = true;
    } 
    std::function<void()> getMoveLeftCommand() {
        return [this]() { this->startMoveLeft(); };
    }
    std::function<void()> getMoveRightCommand() {
        return [this]() { this->startMoveRight(); };
    }
    std::function<void()> getStopMoveCommand() {
        return [this]() { this->stopMove(); };
    }
    std::function<void()> getJumpCommand() {
        return [this]() { this->jump(); };
    }
    void update(float deltaTime) override {
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
            else if(m_moveRightActive) player->MoveRight();
            else if(m_jumpRequested) player->Jump(), m_jumpRequested = 0;
            else player->Stop();
            int state = sp_Entity_Model->update(deltaTime);
            if(state == 0) fire(PropertyID::PlayerPositionChanged);
            else if(state == 1) {
                fire(PropertyID::LevelStateChanged);
                exit(0);
            }
            else if(state == -1) {
                fire(PropertyID::GameStateChanged);
                exit(0);
            }
        }
    }
};
#endif