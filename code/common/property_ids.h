#ifndef PROPERTY_IDS_H
#define PROPERTY_IDS_H

enum class PropertyID {
    NoChange,           // 没有变化
    PlayerDead,         // 死亡
    LevelComplete,     // 关卡完成
    PlayerPositionChanged,    // 位置发生变化
    Initialization    // 初始化界面
};

#endif
