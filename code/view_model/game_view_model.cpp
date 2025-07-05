#include "game_view_model.h"

GameViewModel::GameViewModel()
    : m_game_state(GameState::Initialization)
    , m_death_count(0)
{
}

void GameViewModel::set_property_notify(PropertyNotification&& ntf)
{
    m_ntf = std::move(ntf);
}

void GameViewModel::start_game()
{
    if (m_game_state == GameState::Initialization)
    {
        m_game_state = GameState::Playing;
        reset_death_count();
        notify_state_changed();
    }
}

void GameViewModel::game_over()
{
    if (m_game_state == GameState::Playing)
    {
        m_game_state = GameState::Dead;
        notify_state_changed();
    }
}

void GameViewModel::complete_level()
{
    if (m_game_state == GameState::Playing)
    {
        m_game_state = GameState::Complete;
        notify_state_changed();
    }
}

void GameViewModel::reset_game()
{
    m_game_state = GameState::Initialization;
    notify_state_changed();
}

void GameViewModel::pass_all_levels()
{
    m_game_state = GameState::AllComplete;
    notify_state_changed();
}

void GameViewModel::notify_state_changed()
{
    switch (m_game_state)
    {
        case GameState::Playing:
            fire(PropertyID::PlayerPositionChanged);
            break;
        case GameState::Dead:
            fire(PropertyID::PlayerDead);
            break;
        case GameState::Complete:
            fire(PropertyID::LevelComplete);
            break;
        case GameState::Initialization:
            fire(PropertyID::Initialization);
            break;
        case GameState::AllComplete:
            fire(PropertyID::AllLevelComplete);
            break;
    }
}
