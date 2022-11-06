#include "InputTexture.hpp"

#include <iostream>

sf::Texture ddl::inputTexture(const std::string& source)
{
  static const char* const TEXTURES_ERR = "Texture was not imported correctly";

  static const std::string assetsFolder = "bin/assets/";
  static const std::string spritesFolder = "sprites/";

  sf::Texture result;
  result.setSmooth(true);
  auto path = assetsFolder + spritesFolder + source;
  if(!result.loadFromFile(path))
  {
    throw std::ios_base::failure(TEXTURES_ERR);
  }
  return result;
}