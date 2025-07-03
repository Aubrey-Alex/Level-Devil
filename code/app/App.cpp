#include "App.h"

App::App()
    : model(std::make_shared<Entity_Model>())
    , entityviewModel(model)
    , mainwin(800, 400, "Level Devil")
{
    setupViewModel();
    initializeCommands();
}

void App::setupViewModel()
{
    // 将View的通知函数注册到ViewModel上
    entityviewModel.add_notification(mainwin.get_notification());
    gameviewModel.add_notification(mainwin.get_notification());
    
    // 设置GameWidget的地图数据
    mainwin.get_board().set_map(model->getGameMap().get());
}

void App::initializeCommands()
{
    // 设置移动命令
    mainwin.set_start_move_left_command(std::function<void()>(entityviewModel.getMoveLeftCommand()));
    mainwin.set_start_move_right_command(std::function<void()>(entityviewModel.getMoveRightCommand()));
    mainwin.set_stop_move_command(std::function<void()>(entityviewModel.getStopMoveCommand()));
    mainwin.set_jump_command(std::function<void()>(entityviewModel.getJumpCommand()));
    
    // 设置更新命令
    mainwin.set_next_step_command(std::function<void()>(entityviewModel.getNextStepCommand()));

    // 设置游戏状态命令
    mainwin.set_start_game_command(std::function<void()>(gameviewModel.getStartGameCommand()));
    mainwin.set_game_over_command(std::function<void()>(gameviewModel.getGameOverCommand()));
    mainwin.set_complete_level_command(std::function<void()>(gameviewModel.getCompleteLevelCommand()));
    mainwin.set_reset_game_command(std::function<void()>(gameviewModel.getResetGameCommand()));
}

int App::run(int argc, char** argv)
{
    mainwin.show(argc, argv);
    return Fl::run();
}