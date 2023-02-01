#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <type_traits>
#include <map>
#include <functional>

#include "Player.hpp"
#include "GameData.hpp"
#include "PlatformsPool.hpp"
#include "InputTexture.hpp"

void ddl::run(sf::RenderWindow& window, unsigned short wishedFPS)
{
  sf::View view(sf::FloatRect(0.f, -600, gameWidth, gameHeight));
  window.setView(view);

  GameData data;
  PlatformsPool platforms = PlatformsPool::produce();
  Player doodler{sf::Vector2f{gameWidth / 2, 0}};

  doodler.jump();

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
      case sf::Event::KeyReleased:
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
          doodler.setMoveDirection(Stop);
          break;
        default:
          break;
        }
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          doodler.setMoveDirection(Left);
          break;
        case sf::Keyboard::Right:
          doodler.setMoveDirection(Right);
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
    }

    const float updatesFrequency = 1 / static_cast< float >(wishedFPS);
    const float deltaTime = updateClock.getElapsedTime().asSeconds();
    if(deltaTime > updatesFrequency)
    {
      data.update(deltaTime);
      platforms.update(deltaTime);
      doodler.update(deltaTime);

      view.move(0, -0);

      auto intersectionStatus = platforms.anyIntersections(doodler);
      if (intersectionStatus.hasIntersected)
      {
        doodler.jump();
        if (intersectionStatus.isInNewBank)
        {
          platforms.onNewBankVisit();
        }
      }

      window.clear();
      data.render(window);
      doodler.render(window);
      platforms.render(window);
      window.display();

      updateClock.restart();
    }
  }
}