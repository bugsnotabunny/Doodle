#include "Platform.hpp"

#include "AssetsLoad.hpp"

#include <limits>

namespace
{
  constexpr float SHIFT_ACC_MULT = 100;
  const sf::Texture TEXTURE = ddl::inputTexture("platform_shifting.png");
  const sf::Vector2f NO_SHIFT = { std::numeric_limits< float >::max(),
    std::numeric_limits< float >::max() };
}

ddl::ShiftingPlatform::ShiftingPlatform(const sf::Vector2f & pos, float shift):
  Platform(pos, TEXTURE),
  nextShift_(shift),
  shiftTo_(NO_SHIFT),
  movement_({ 0, 0 }, { { 0, 0 }, { shift * SHIFT_ACC_MULT, 0 } })
{}

void ddl::ShiftingPlatform::onPlayerLanding()
{
  shiftTo_ = { getPosition().x + nextShift_, getPosition().y };
  movement_.setAccelerationValue({ nextShift_ * SHIFT_ACC_MULT, 0 });
  nextShift_ *= -1;
}

void ddl::ShiftingPlatform::update(float deltaTime)
{
  const bool reachedLeft = shiftTo_.x > getPosition().x && movement_.getAcceleration().x < 0;
  const bool reachedRight = shiftTo_.x < getPosition().x && movement_.getAcceleration().x > 0;
  if (reachedLeft || reachedRight)
  {
    shiftTo_ = NO_SHIFT;
    movement_.setAccelerationValue({ 0, 0 });
    movement_.setSpeedValue({ 0, 0 });
  }
  movement_.update(deltaTime);

  move(movement_.getSpeed().getVec() * deltaTime);
}
