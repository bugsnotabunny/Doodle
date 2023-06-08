#include "Platform.hpp"

#include "AssetsLoad.hpp"

namespace
{
  const sf::Texture TEXTURE_OK = ddl::inputTexture("platform_breaking_ok.png");
  const sf::Texture TEXTURE_BROKEN = ddl::inputTexture("platform_breaking_broken.png");
}

ddl::BreakingPlatform::BreakingPlatform(const sf::Vector2f & pos):
  Platform(pos, TEXTURE_OK),
  isBroken_(false)
{}

void ddl::BreakingPlatform::onPlayerLanding()
{
  isBroken_ = true;
  setTexture(TEXTURE_BROKEN);
}

bool ddl::BreakingPlatform::isLandable() const
{
  return !isBroken_;
}
