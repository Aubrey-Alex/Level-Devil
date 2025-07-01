#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <memory>
#include "property_ids.h"
#include "Entity.h"

class GameMap {
public:
    GameMap() noexcept {}
    GameMap(const GameMap&) = delete;
    ~GameMap() noexcept {}

    GameMap& operator=(const GameMap&) = delete;

    void clear() noexcept {
        m_entities.clear();
    }

    size_t get_size() const noexcept {
        return m_entities.size();
    }

    const Entity& get_at(size_t idx) const noexcept {
        return *m_entities[idx];
    }
    Entity& get_at(size_t idx) noexcept {
        return *m_entities[idx];
    }

    void set_size(size_t size) {
        m_entities.resize(size);
    }

    void append(std::shared_ptr<Entity> v) {
        m_entities.push_back(v);
        rep(i, v->pos.x, v->pos.x+v->w-1) rep(j, v->pos.y, v->pos.y+v->h-1) mp[i][j]=v->type;
    }
    void insert(size_t idx, std::shared_ptr<Entity> v) {
        m_entities.insert(m_entities.begin() + idx, v);
    }
    void remove(size_t idx) noexcept {
        m_entities.erase(m_entities.begin() + idx);
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif