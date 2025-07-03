#include "object.h"

bool Player::checkCollision(double x, double y, char targetType, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != targetType) continue;
        // AABB碰撞检测
        bool collisionX = x + w > entity.pos.x && x < entity.pos.x + entity.w;
        bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
        
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

bool Player::checkCollisionUp(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'W') continue;
        bool collisionX = x + w > entity.pos.x && x < entity.pos.x + entity.w;
        bool collisionY = y < entity.pos.y + entity.h && y > entity.pos.y;
        
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

bool Player::checkCollisionDown(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'W') continue;
        bool collisionX = x + w > entity.pos.x && x < entity.pos.x + entity.w;
        bool collisionY = y + h > entity.pos.y && y + h < entity.pos.y + entity.h;
        
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

bool Player::checkCollisionLeft(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'W') continue;
        bool collisionX = x < entity.pos.x + entity.w && x > entity.pos.x;
        bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
        
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

bool Player::checkCollisionRight(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'W') continue;
        bool collisionX = x + w > entity.pos.x && x + w < entity.pos.x + entity.w;
        bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
        
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

PropertyID Player::update(std::shared_ptr<GameMap>& sp_GameMap) {
    // 处理水平移动
    if (leftActive) v_Horizontal = -HORIZONTAL_SPEED;
    else if (rightActive) v_Horizontal = HORIZONTAL_SPEED;
    else v_Horizontal = 0;

    // 应用重力
    if (!isGrounded) {
        v_Vertical += GRAVITY_ACCELERATION;
    }

    // 计算新位置
    double newX = pos.x + v_Horizontal;
    double newY = pos.y + v_Vertical;
    
    // 边界检查
    if(newX < 0 || newX + w > Weight || newY < 0 || newY + h > Height) {
        return PropertyID::PlayerDead;
    }

    // 检查碰到刺
    if (checkCollision(newX, newY, 'S', sp_GameMap)) {
        return PropertyID::PlayerDead;
    }

    // 检查碰到门
    if (checkCollision(newX, newY, 'D', sp_GameMap)) {
        return PropertyID::LevelComplete;
    }
    
    // 处理墙体碰撞
    if (v_Vertical < 0 && checkCollisionUp(newX, newY, sp_GameMap)) {
        v_Vertical = -v_Vertical;
        newY = pos.y;
    }
    
    isGrounded = checkCollisionDown(newX, newY, sp_GameMap);
    
    if (v_Vertical > 0 && checkCollisionDown(newX, newY, sp_GameMap)) {
        v_Vertical = 0;
        // 找到确切的地面位置
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type == 'W' && 
                newX + w > entity.pos.x && newX < entity.pos.x + entity.w &&
                newY + h > entity.pos.y && newY + h < entity.pos.y + entity.h) {
                    newY = entity.pos.y - h;
                    break;
                }
            }
            isGrounded = true;
        }
        
    if (v_Horizontal > 0 && checkCollisionRight(newX, newY, sp_GameMap)) {
        v_Horizontal = 0;
        newX = pos.x;
    }
    
    if (v_Horizontal < 0 && checkCollisionLeft(newX, newY, sp_GameMap)) {
        v_Horizontal = 0;
        newX = pos.x;
    }
    //显示隐藏的刺
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'U') continue;
        if(((newX + w  > entity.pos.x - spike_view) && (newX + w <entity.pos.x))|| ((newX < entity.pos.x + entity.w + spike_view) && (newX > entity.pos.x + entity.w))){
                entity.type = 'S';
                break;
        }
    }
    // 更新位置
    if (newX != pos.x || newY != pos.y) {
        pos.x = newX;
        pos.y = newY;
        return PropertyID::PlayerPositionChanged;
    }


    return PropertyID::NoChange;
}

