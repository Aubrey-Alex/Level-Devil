#include "App.h"

App::App()
    : model(std::make_shared<Entity_Model>())
    , viewModel(model)
    , mainwin(800, 400, "Level Devil")
{
    setupViewModel();
    initializeCommands();
}

void App::setupViewModel()
{
    // 将View的通知函数注册到ViewModel上
    viewModel.add_notification(mainwin.get_notification());
    
    // 设置GameWidget的地图数据
    mainwin.get_board().set_map(model->getGameMap().get());
}

void App::initializeCommands()
{
    // 设置移动命令
    mainwin.set_start_move_left_command(StartMoveLeftCommand(viewModel.getMoveLeftCommand()));
    mainwin.set_start_move_right_command(StartMoveRightCommand(viewModel.getMoveRightCommand()));
    mainwin.set_stop_move_command(StopMoveCommand(viewModel.getStopMoveCommand()));
    mainwin.set_jump_command(JumpCommand(viewModel.getJumpCommand()));

    // 设置更新命令
    mainwin.set_next_step_command([this](float deltaTime) {
        viewModel.update(deltaTime);
    });
}

int App::run(int argc, char** argv)
{
    mainwin.show(argc, argv);
    return Fl::run();
}