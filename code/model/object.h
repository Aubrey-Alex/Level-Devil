#ifndef OBJECT_H
#define OBJECT_H
#include <memory>
#include <vector>
#include "../common/game_map.h"
#include "../common/Entity.h"

class Door : public Entity {
public:
    Door(double x, double y): Entity(x, y) {
        w = 40, h = 40, type = 'D';
    }
};

class Spike : public Entity {
public:
    Spike(double x, double y): Entity(x, y) {
        w = 54, h = 13, type = 'S';
    }
};

class Wall : public Entity {
public:
    Wall(double x, double y, double width, double height): Entity(x, y) {
        w = width, h = height, type = 'W';
    }
};

class Player : public Entity {
#define size_w 26
#define size_h 38
#define fps 60
#define GRAVITY_ACCELERATION 200.0 / fps / fps
#define JUMP_SPEED -200.0 / fps
#define HORIZONTAL_SPEED 80.0 / fps

private:
    double v_Vertical, v_Horizontal;
    bool isGrounded;
    int moveDirection; // -1 左, 0 停止, 1 右

public:
    Player(double x, double y) : Entity(x, y) {
        // printf("Player Pos = %.2lf %.2lf\n", x, y);
        v_Horizontal = v_Vertical = 0;
        isGrounded = true;
        moveDirection = 0;
        w = size_w;
        h = size_h;
        type = 'P';
    }

    void MoveLeft() {
        moveDirection = -1;
    }

    void MoveRight() {
        moveDirection = 1;
    }

    void Jump() {
        if(!isGrounded) return;
        isGrounded = false;
        v_Vertical = JUMP_SPEED;
    }

    void Stop() {
        moveDirection = 0;
    }

    // 检查与其他实体的碰撞
    bool checkCollision(double x, double y, char targetType, std::shared_ptr<GameMap>& sp_GameMap) {
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

    // 获取特定方向的碰撞
    bool checkCollisionUp(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
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

    bool checkCollisionDown(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type != 'W') continue;
            bool collisionX = x + w > entity.pos.x && x < entity.pos.x + entity.w;
            bool collisionY = y + h >= entity.pos.y && y + h <= entity.pos.y + entity.h;
            
            if (collisionX && collisionY) {
                return true;
            }
        }
        return false;
    }

    bool checkCollisionLeft(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type != 'W') continue;
            bool collisionX = x <= entity.pos.x + entity.w && x >= entity.pos.x;
            bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
            
            if (collisionX && collisionY) {
                return true;
            }
        }
        return false;
    }

    bool checkCollisionRight(double x, double y, std::shared_ptr<GameMap>& sp_GameMap) {
        for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
            auto& entity = sp_GameMap->get_at(i);
            if (entity.type != 'W') continue;
            bool collisionX = x + w >= entity.pos.x && x + w <= entity.pos.x + entity.w;
            bool collisionY = y + h > entity.pos.y && y < entity.pos.y + entity.h;
            
            if (collisionX && collisionY) {
                return true;
            }
        }
        return false;
    }

    int update(std::shared_ptr<GameMap>& sp_GameMap) {
        // printf("Player Pos = %.2lf %.2lf -> ", pos.x, pos.y);
        // 处理水平移动
        v_Horizontal = 1.0 * moveDirection * HORIZONTAL_SPEED;

        // 应用重力
        if (!isGrounded) {
            v_Vertical += 1.0 * GRAVITY_ACCELERATION;
        }

        // 计算新位置
        double newX = pos.x + v_Horizontal;
        double newY = pos.y + v_Vertical;

        // 边界检查
        if(newX < 0 || newX + w > Weight || newY < 0 || newY + h > Height) {
            return -1;
        }

        // 检查碰撞
        if (checkCollision(newX, newY, 'S', sp_GameMap)) {
            return -1; // 碰到尖刺，死亡
        }

        if (checkCollision(newX, newY, 'D', sp_GameMap)) {
            return 1; // 到达门，通关
        }

        // 处理墙体碰撞
        if (v_Vertical < 0 && checkCollisionUp(newX, newY, sp_GameMap)) {
            v_Vertical = -v_Vertical;
            newY = pos.y;
        }

        isGrounded = checkCollisionDown(newX, newY + 1, sp_GameMap); // 检查下方是否有地面
        // printf("isGrounded: %d %.2lf %.2lf\n", isGrounded, newX, newY);

        if (isGrounded) {
            v_Vertical = 0;
            // 找到确切的地面位置
            for (size_t i = 0; i < sp_GameMap->get_size(); ++i) {
                auto& entity = sp_GameMap->get_at(i);
                if (entity.type == 'W' && 
                    newX + w > entity.pos.x && newX < entity.pos.x + entity.w &&
                    newY + h >= entity.pos.y && newY + h < entity.pos.y + entity.h) {
                    newY = entity.pos.y - h;
                    break;
                }
            }
            // printf("%.2lf %.2lf\n", newX, newY);exit(0);
        }
        else v_Vertical += GRAVITY_ACCELERATION;

        if (v_Horizontal > 0 && checkCollisionRight(newX, newY, sp_GameMap)) {
            v_Horizontal = 0;
            newX = pos.x; // 保持原来的X坐标
        }

        if (v_Horizontal < 0 && checkCollisionLeft(newX, newY, sp_GameMap)) {
            v_Horizontal = 0;
            newX = pos.x; // 保持原来的X坐标
        }

        // 更新位置
        pos.x = newX;
        pos.y = newY;

        return 0;
    }
};
#endif