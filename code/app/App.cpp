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
    entityviewModel.reset();
    // 将View的通知函数注册到ViewModel上
    entityviewModel.add_notification(mainwin.get_notification());
    gameviewModel.add_notification(mainwin.get_notification());
    
    // Register App to listen to GameViewModel notifications
    gameviewModel.add_notification([this](PropertyID propertyId) {
        this->onGameViewModelNotification(propertyId);
    });
    
    // 让GameViewModel监听Entity_View_Model的通知，在死亡时增加计数
    entityviewModel.add_notification([this](PropertyID propertyId) {
        if (propertyId == PropertyID::PlayerDead) {
            // 直接增加死亡次数，不改变游戏状态
            this->gameviewModel.increment_death_count();
            // 然后调用game_over来改变状态
            this->gameviewModel.game_over();
        }
    });
    
    // 设置MainWindow的GameViewModel引用
    mainwin.set_game_view_model(&gameviewModel);
    
    // 设置GameWidget的地图数据
    mainwin.get_board().set_map(model->getGameMap().get());
    
    // 设置初始死亡次数显示
    mainwin.get_board().set_death_count(gameviewModel.get_death_count());
}

void App::onGameViewModelNotification(PropertyID propertyId)
{
    if (propertyId == PropertyID::Initialization) // Assuming you have a PropertyID::Initialization
    {
        entityviewModel.reset();
        // 更新死亡次数显示
        mainwin.get_board().set_death_count(gameviewModel.get_death_count());
    }
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
    mainwin.set_pass_all_levels_command(std::function<void()>(gameviewModel.getPassAllLevelsCommand())); // 新增：全部通关命令
}

int App::run(int argc, char** argv)
{
    mainwin.show(argc, argv);
    return Fl::run();
}