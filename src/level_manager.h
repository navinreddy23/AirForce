#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

typedef enum
{
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    MAX_LEVELS
} levels_t;

typedef enum
{
    BULLET_SPEED,
    ENEMY_SPEED_X,
    ENEMY_SPEED_Y,
    ENEMY_COUNT,
    MEDAL_COUNT,
    BULLET_SPWAWN_MIN,
    BULLET_SPAWN_MAX,
    ENEMY_SPAWN_MIN,
    ENEMY_SPAWN_MAX,
    MAX_VARIABLES
} variables_t;

class LevelManager
{
public:
    LevelManager();

protected:
    levels_t GetLevel(int);
    float GetValue(variables_t variable, levels_t);

private:

    float _lookUpTable[MAX_LEVELS][MAX_VARIABLES] =
    {
        0.6, 0.050,  0.050, 1, 1, 1000, 3000, 1500, 3000,
        0.7, 0.100,  0.100, 2, 1,  800, 2500, 1200, 2500,
        0.8, 0.125,  0.125, 2, 2,  600, 2000, 1200, 2500,
        0.9, 0.150,  0.150, 2, 2,  400, 1500, 1200, 2500,
        1.0, 0.175,  0.175, 2, 3,  200, 1000, 1000, 2000,
    };
};

#endif // LEVELMANAGER_H
