#ifndef PROPERTY_IDS_H
#define PROPERTY_IDS_H

enum class PropertyID {
    NoChange,           // 没有变化
    GameOver,         // 游戏结束（死亡）
    LevelComplete,     // 关卡完成
    PlayerPositionChanged,    // 位置发生变化

    // Player related
    PlayerStateChanged,
    PlayerDirectionChanged,
    
    // Game state
    GameStateChanged,
    LevelStateChanged,
    
    // Collision
    CollisionDetected,
    TriggerEntered,
    
    // UI
    UIStateChanged,
    ScoreChanged,
    
    // 调试相关
    DebugInfoChanged,       // 调试信息变化
    
    MapUpdated // Added for explicit map redraws
};

#endif
