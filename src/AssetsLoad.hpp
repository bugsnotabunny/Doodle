#ifndef INPUT_TEXTURE_HPP
#define INPUT_TEXTURE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace ddl
{
  sf::Texture inputTexture(const std::string & source);
  sf::Font inputFont(const std::string & source);
}

#endif
