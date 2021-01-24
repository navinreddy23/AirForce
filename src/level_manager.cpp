#include "level_manager.h"

LevelManager::LevelManager()
{

}

levels_t LevelManager::GetLevel(int score)
{
   levels_t level = LEVEL_1;

   if (score < 5)
   {
       level = LEVEL_1;
   }
   else if (score < 25)
   {
       level = LEVEL_2;
   }
   else if (score < 40)
   {
       level = LEVEL_3;
   }
   else if (score < 60)
   {
       level = LEVEL_4;
   }
   else
   {
       level = LEVEL_5;
   }

   return level;
}

float LevelManager::GetValue(variables_t variable, levels_t level)
{
    return _lookUpTable[level][variable];
}
