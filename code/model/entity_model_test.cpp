#include "entity_model.h"

int main() {
    Entity_Model EM;
    std::shared_ptr<GameMap> sp_GameMap = EM.getGameMap();
    EM.newLevel(1);
    for(int i=0; i<sp_GameMap->get_size(); i++) {
        Entity tmp = sp_GameMap->get_at(i);
        printf("%c %.2lf %.2lf %.2lf %.2lf\n", tmp.type, tmp.pos.x, tmp.pos.y, tmp.w, tmp.h);
    }
    return 0;
}