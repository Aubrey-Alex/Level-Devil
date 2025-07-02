#ifndef APP_H
#define APP_H

#include <FL/Fl.H>
#include <memory>
#include "../View/MainWindow.h"
#include "../Model/entity_model.h"
#include "../ViewModel/entity_view_model.h"
#include "../common/commands.h"

class App {
public:
    App();
    int run(int argc, char** argv);

private:
    std::shared_ptr<Entity_Model> model;
    Entity_View_Model viewModel;
    MainWindow mainwin;

    void initializeCommands();
    void setupViewModel();
};
#endif
