#ifndef PROPERTY_IDS_H
#define PROPERTY_IDS_H

enum class PropertyID {
    // Player related
    PlayerPositionChanged,
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
