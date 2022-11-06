#include "GameData.hpp"

#include "InputTexture.hpp"

ddl::GameTextures ddl::loadTextures()
{
  GameTextures result;
  result.doodler = inputTexture("doodler.png");
  result.platform = inputTexture("platform.png");
  return result;
}