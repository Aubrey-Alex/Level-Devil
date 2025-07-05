#ifndef __ENTITY_VIEW_MODEL_H__
#define __ENTITY_VIEW_MODEL_H__

#include "../model/entity_model.h"
#include "../common/notifier.h"
#include <functional>

class Entity_View_Model: public PropertyNotifier {
private:
    std::shared_ptr<Entity_Model> sp_Entity_Model;
    bool m_moveLeftActive = false;
    bool m_moveRightActive = false;
    bool m_jumpRequested = false;
public:
    Entity_View_Model(std::shared_ptr<Entity_Model> model): sp_Entity_Model(std::move(model)) {
        // sp_Entity_Model->newLevel(1);
    }
    void reset(){
        // if (sp_Entity_Model && sp_Entity_Model->getGameMap() && sp_Entity_Model->getGameMap()->get_size() > 0) { // Check if model and map exist and are not empty
        //     sp_Entity_Model->getGameMap()->clear(); // Assuming your GameMap class has a clear() method
        // }
        sp_Entity_Model->newLevel();
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
    std::function<void()> getNextStepCommand() {
        return [this]() { this->update(); };
    }
    void update();
};
#endif