#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <memory>
#include <vector>
#include "../common/game_map.h"
#include "../common/Entity.h"
#include "../common/property_ids.h"

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
#define GRAVITY_ACCELERATION 1200.0 / fps / fps
#define JUMP_SPEED -400.0 / fps
#define HORIZONTAL_SPEED 200.0 / fps

private:
    double v_Vertical, v_Horizontal;
    bool isGrounded;
    bool leftActive;
    bool rightActive;

public:
    Player(double x, double y) : Entity(x, y) {
        // printf("Player Pos = %.2lf %.2lf\n", x, y);
        v_Horizontal = v_Vertical = 0;
        isGrounded = true;
        leftActive = false;
        rightActive = false;
        w = size_w;
        h = size_h;
        type = 'P';
    }

    void MoveLeft() {
        leftActive = true;
    }

    void MoveRight() {
        rightActive = true;
    }

    void Jump() {
        if(!isGrounded) return;
        isGrounded = false;
        v_Vertical = JUMP_SPEED;
    }

    void Stop() {
        leftActive = false;
        rightActive = false;
    }

    // 检查与其他实体的碰撞
    bool checkCollision(double x, double y, char targetType, std::shared_ptr<GameMap>& sp_GameMap);

    // 获取特定方向的碰撞
    bool checkCollisionUp(double x, double y, std::shared_ptr<GameMap>& sp_GameMap);

    bool checkCollisionDown(double x, double y, std::shared_ptr<GameMap>& sp_GameMap);

    bool checkCollisionLeft(double x, double y, std::shared_ptr<GameMap>& sp_GameMap);

    bool checkCollisionRight(double x, double y, std::shared_ptr<GameMap>& sp_GameMap);

    PropertyID update(std::shared_ptr<GameMap>& sp_GameMap);
};
#endif