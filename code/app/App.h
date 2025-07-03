#ifndef APP_H
#define APP_H

#include <FL/Fl.H>
#include <memory>
#include "../view/MainWindow.h"
#include "../model/entity_model.h"
#include "../view_model/entity_view_model.h"
#include "../view_model/game_view_model.h"

class App {
public:
    App();
    int run(int argc, char** argv);

private:
    std::shared_ptr<Entity_Model> model;
    Entity_View_Model entityviewModel;
    GameViewModel gameviewModel;
    MainWindow mainwin;

    void initializeCommands();
    void setupViewModel();
};
#endif