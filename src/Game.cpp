#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <chrono>
#include <thread>
#include <iostream>
#include <type_traits>
#include <map>
#include <functional>

#include "Player.hpp"
#include "PlatformsPool.hpp"
#include "AssetsLoad.hpp"
#include "Movement.hpp"

namespace
{
  const sf::Font MERCHANT_COPY = ddl::inputFont("merchant_copy.ttf");
  const float VIEW_MOVE_SPEED = -500;
  const float VIEW_MOVE_OFFSET = 100;
}

void ddl::run(sf::RenderWindow & window, unsigned short wishedFPS)
{
  sf::View view(sf::FloatRect(0.f, -600, gameWidth, gameHeight));
  window.setView(view);

  sf::Text scoreText;
  scoreText.setFont(MERCHANT_COPY);
  scoreText.setCharacterSize(100);
  scoreText.setStyle(sf::Text::Regular);

  PlatformsPool platforms = PlatformsPool::produce();
  Player doodler{ sf::Vector2f{ static_cast< float >(gameWidth) / 2, 0 } };

  doodler.jump();

  sf::Clock updateClock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      // TODO: redo with std::map later maybe
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
          doodler.setMoveDirection(Direction::Stop);
          break;
        default:
          break;
        }
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
          doodler.setMoveDirection(Direction::Left);
          break;
        case sf::Keyboard::Right:
          doodler.setMoveDirection(Direction::Right);
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
    std::this_thread::sleep_for(
     std::chrono::milliseconds(static_cast< uint32_t >(updatesFrequency * 1000)));
    const float deltaTime = updateClock.getElapsedTime().asSeconds();

    platforms.update(deltaTime);
    doodler.update(deltaTime);
    auto intersection = platforms.intersection(doodler);
    if (intersection.intersection.has_value())
    {
      auto && plat = intersection.intersection.value().get();
      if (plat.isLandable())
      {
        doodler.jump();
        intersection.intersection.value().get().onPlayerLanding();
      }
      if (intersection.isInNewBank)
      {
        platforms.onNewBankVisit();
        const size_t score = platforms.getNewBankVisitsCount();
        scoreText.setString(std::to_string(score));
      }
    }

    if (view.getCenter().y + VIEW_MOVE_OFFSET > doodler.getPosition().y)
    {
      view.move(0, VIEW_MOVE_SPEED * deltaTime);
      scoreText.move(0, VIEW_MOVE_SPEED * deltaTime);
      window.setView(view);
    }

    window.clear();
    doodler.render(window);
    platforms.render(window);
    window.draw(scoreText);
    window.display();
    updateClock.restart();
  }
}
