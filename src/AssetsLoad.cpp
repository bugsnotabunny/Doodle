#include "AssetsLoad.hpp"

#include <iostream>



namespace
{
  static const std::string assetsFolder = "bin/assets/";
  static const std::string spritesFolder = "sprites/";
  static const std::string fontsFolder = "fonts/";

  template <typename AssetT>
  AssetT inputAsset(const std::string& assetsFolder, const std::string& assetsSubFolder, const std::string& source)
  {
    static const char* const ASSETS_ERR = "Asset was not imported correctly";

    AssetT result;
    auto path = assetsFolder + assetsSubFolder + source;
    if(!result.loadFromFile(path))
    {
      throw std::ios_base::failure(ASSETS_ERR);
    }
    return result;
  }
}

sf::Texture ddl::inputTexture(const std::string& source)
{
  auto texture = inputAsset< sf::Texture >(assetsFolder, spritesFolder, source);
  texture.setSmooth(true);
  return texture;
}

sf::Font ddl::inputFont(const std::string& source)
{
  return inputAsset< sf::Font >(assetsFolder, fontsFolder, source);
}