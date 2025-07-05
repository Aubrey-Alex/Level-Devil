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

class Wall : public Entity {
private:
    int visible_dis;
public:
    Wall(double x, double y, double width, double height, int d = -1): Entity(x, y) {
        w = width, h = height;
        visible_dis = d;
        type = 'W';
    }
    int get_visible_dis() const { return visible_dis; }
    PropertyID update(std::shared_ptr<GameMap>& sp_GameMap);
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
    double spike_view;

public:
    Player(double x, double y, double v) : Entity(x, y) {
        // printf("Player Pos = %.2lf %.2lf\n", x, y);
        v_Horizontal = v_Vertical = 0;
        spike_view = v;
        isGrounded = true;
        leftActive = false;
        rightActive = false;
        w = size_w;
        h = size_h;
        type = 'P';
    }
    void set_spike_view(double v){
        spike_view = v;
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

class MovingSpike : public Entity {
private:
    int visible_dis;
    double speed;
    double left_bound, right_bound;
    bool moving_right;
public:
    MovingSpike(double x, double y, double left, double right, double spd, int d = -1)
        : Entity(x, y), visible_dis(d), speed(spd), left_bound(left), right_bound(right), moving_right(true)
    {
        w = 54, h = 13, type = (visible_dis == -1) ? 'S' : 'U';
    }
    void update(double player_x);
    int get_visible_dis() const { return visible_dis; }
};
#endif