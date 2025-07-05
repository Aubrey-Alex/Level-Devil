#include "object.h"
#include <cmath> // 添加此行以支持fabs
#define eps 2

bool Player::checkCollision(double x, double y, char targetType, std::shared_ptr<GameMap>& sp_GameMap) {
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != targetType) continue;
        if (entity.type == 'U') {
            // 如果是隐藏的刺，检查是否在可视范围内
            if (spike_view < 0 || (x + w > entity.pos.x - spike_view && x < entity.pos.x + entity.w + spike_view)) {
                continue;
            }
        }
        if (entity.type == 'H') continue;
        // AABB碰撞检测
        bool collisionX = x + w > entity.pos.x && x < entity.pos.x + entity.w;
        bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
        if (collisionX && collisionY) {
            return true;
        }
    }
    return false;
}

// 以GameWidget的显示为准，碰撞体积与渲染一致
bool Player::checkCollisionLeft(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
    // stickman头顶到脚底全部参与碰撞
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
        
    if (v_Horizontal > 0 && checkCollisionRight(newX, newY, sp_GameMap)) {
        v_Horizontal = 0;
        // 微调人物位置到墙体左侧
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type == 'W') {
                if (pos.y + h > entity.pos.y && pos.y < entity.pos.y + entity.h) {
                    if (pos.x + w <= entity.pos.x + eps && newX + w > entity.pos.x) {
                        newX = entity.pos.x - w - 0.1; // 贴着墙体左侧
                        break;
                    }
                }
            }
        }
    }

    if (v_Horizontal < 0 && checkCollisionLeft(newX, newY, sp_GameMap)) {
        v_Horizontal = 0;
        // 微调人物位置到墙体右侧
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type == 'W') {
                if (pos.y + h > entity.pos.y && pos.y < entity.pos.y + entity.h) {
                    if (pos.x >= entity.pos.x + entity.w - eps && newX < entity.pos.x + entity.w) {
                        newX = entity.pos.x + entity.w + 0.1; // 贴着墙体右侧
                        break;
                    }
                }
            }
        }
    }

    isGrounded = checkCollisionDown(newX, newY, sp_GameMap);
    if (v_Vertical > 0 && checkCollisionDown(newX, newY, sp_GameMap)) {
        v_Vertical = 0;
        // 找到确切的地面位置
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type == 'W' && 
                newX + w> entity.pos.x && newX < entity.pos.x + entity.w &&
                newY + h > entity.pos.y && newY + h < entity.pos.y + entity.h) {
                    newY = entity.pos.y - h;
                    break;
                }
            }
            isGrounded = true;
        }
    // 显示隐藏的刺：player的x坐标超过刺的visible_dis时出现
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'U') continue;
        if (pos.x > static_cast<Spike*>(&entity)->get_visible_dis()) {
            entity.type = 'S';
        }
    }

    // 墙体靠近后隐藏逻辑：player的x坐标超过visible_dis时隐藏，且一旦隐藏不会再恢复
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        if (entity.type != 'W' && entity.type != 'H') continue;
        Wall* wallPtr = static_cast<Wall*>(&entity);
        if (!wallPtr) continue;
        int wall_dis = wallPtr->get_visible_dis();
        if (wall_dis == -1) {
            // 永久显示墙体，始终为'W'
            if (entity.type != 'W') entity.type = 'W';
            continue;
        }
        // player的x坐标超过visible_dis时隐藏，且一旦隐藏不会再恢复
        if (pos.x > wall_dis) {
            if (entity.type == 'W') entity.type = 'H'; // 靠近后隐藏
        }
        // 不再有 else 分支，不会恢复为'W'
    }

    // 移动刺的更新：每一帧都更新位置（只要已经出现type=='S'）
    double player_x = pos.x;
    for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
        auto& entity = sp_GameMap->get_at(i);
        MovingSpike* mspike = static_cast<MovingSpike*>(&entity);
        if (mspike) {
            mspike->update(player_x);
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

void MovingSpike::update(double player_x) {
    // 靠近出现：player的x坐标超过visible_dis时出现
    if (type == 'U' && visible_dis != -1) {
        if (player_x > visible_dis) {
            type = 'S';
        }
    }
    // 只要type=='S'，每帧都移动
    if (type == 'S') {
        pos.x -= speed;
        if ((speed > 0 && pos.x + w < 0) || (speed < 0 && pos.x > Weight)) {
            type = 'X'; // 'X' 表示不再渲染和判定
        }
    }
}