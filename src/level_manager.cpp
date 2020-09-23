#include "level_manager.h"
#include <iostream>

LevelManager::LevelManager()
{

}

levels_t LevelManager::GetLevel(int score)
{
   levels_t level = LEVEL_1;

   if (score < 10)
   {
       level = LEVEL_1;
       //std::cout << "Level 1, Score = " << score << std::endl;
   }
   else if (score < 20)
   {
       level = LEVEL_2;
       //std::cout << "Level 2" << std::endl;
   }
   else if (score < 30)
   {
       level = LEVEL_3;
   }
   else if (score < 40)
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
    //levels_t  currentLevel =  GetLevel(score);
    return lookUpTable[level][variable];
}
