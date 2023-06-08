#include "Platform.hpp"

#include <map>
#include <limits>

#include "Game.hpp"
#include "AssetsLoad.hpp"

namespace
{
  const sf::Texture TEXTURE = ddl::inputTexture("platform.png");
}

void ddl::Platform::update(float)
{}

ddl::Platform::Platform(const sf::Vector2f & pos):
  RenderableObject(sf::Sprite{ TEXTURE })
{
  setPosition(pos);
}

void ddl::Platform::onPlayerLanding()
{}

std::shared_ptr< ddl::Platform > ddl::Platform::produce(const sf::Vector2f & pos)
{
  return std::make_shared< Platform >(pos);
}

ddl::Platform::Platform(const sf::Vector2f & pos, const sf::Texture & texture):
  RenderableObject(sf::Sprite{ texture })
{
  setPosition(pos);
}

bool ddl::Platform::isLandable() const
{
  return true;
}
