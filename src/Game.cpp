#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <type_traits>
#include <map>
#include <functional>

#include "Player.hpp"
#include "GameData.hpp"

namespace
{
  const sf::Vector2f gravity = {0, 1000};
  const float horizontalAccelerationBase = 1000;
}

void ddl::run(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame)
{
  GameData data;
  GameTextures textures = loadTextures();

  std::shared_ptr< Player > doodler = data.instantiate(Player{sf::Sprite{textures.doodler}});
  doodler->setScale(0.5, 0.5);
  doodler->setPosition(100, 100);
  doodler->move(200, 100);

  using AccelerationT = Acceleration< LimitedVector< float >, sf::Vector2f >;
  std::shared_ptr< AccelerationT > lrPlayerAcceleration = data.instantiate(AccelerationT{doodler->speed, {0, 0}});
  std::shared_ptr< AccelerationT > gravityPlayerAcceleration = data.instantiate(AccelerationT{doodler->speed, gravity});
  bool accelerateLeft = false;
  bool accelerateRight = false;

  sf::Clock updateClock;
  while(window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      // ! redo with std::map later maybe
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          accelerateLeft = true;
          break;
        case sf::Keyboard::Right:
          accelerateRight = true;
          break;
        default:
          break;
        }
        break;
      case sf::Event::KeyReleased:
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          accelerateLeft = false;
          break;
        case sf::Keyboard::Right:
          accelerateRight = false;
          break;
        default:
          break;
        }
      default:
        break;
      }
    }

    const float updatesFrequency = 1 / static_cast< float >(wishedFPS * updatesPerFrame);
    const float deltaTime = updateClock.getElapsedTime().asSeconds();
    if(deltaTime > updatesFrequency)
    {
      lrPlayerAcceleration->acceleration.x = horizontalAccelerationBase * (static_cast< char >(accelerateRight) - accelerateLeft);
      for(auto&& item: data.updatables)
      {
        item.lock()->update(deltaTime);
      }

      if (doodler->getPosition().y > 400)
      {
        doodler->jump();
      }

      window.clear();
      for(auto&& item: data.renderables)
      {
        item.lock()->render(window);
      }
      window.display();
      updateClock.restart();
    }
  }
}