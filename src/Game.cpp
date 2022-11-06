#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <type_traits>
#include <map>
#include <functional>

#include "Event.hpp"
#include "Player.hpp"
#include "GameClock.hpp"
#include "GameData.hpp"
#include "GlobalConstants.hpp"

namespace
{
  class iterThroughRenderables
  {
  public:
    iterThroughRenderables(ddl::GameData::Renderables& storage, sf::RenderWindow& window):
      storage_(storage),
      window_(window)
    {}

    void operator()()
    {
      for(auto&& item: storage_)
      {
        item.lock()->render(window_);
      }
    }
  private:
    ddl::GameData::Renderables& storage_;
    sf::RenderWindow& window_;
  };

  class iterThroughUpdatables
  {
  public:
    iterThroughUpdatables(ddl::GameData::Updatables& storage):
      storage_(storage)
    {}

    void operator()()
    {
      for(auto&& item: storage_)
      {
        item.lock()->update();
      }
    }
  private:
    ddl::GameData::Updatables& storage_;
  };
}

void ddl::run(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame)
{
  GameData data;
  GameTextures textures = loadTextures();

  std::shared_ptr< Player > doodler = data.instantiate(Player{sf::Sprite{textures.doodler}});
  doodler->setScale(0.5, 0.5);
  doodler->setPosition(100, 100);
  doodler->move(200, 100);

  Event frame;
  frame.subscribe(iterThroughRenderables{data.renderables, window});
  Event update;
  update.subscribe(iterThroughUpdatables{data.updatables});

  std::shared_ptr< GameClock > clock = data.instantiate(GameClock{});

  using AccelerationT = Acceleration< LimitedVector< float >, sf::Vector2f >;
  std::shared_ptr< AccelerationT > lrPlayerAcceleration = data.instantiate(AccelerationT{doodler->speed, {0, 0}});
  std::shared_ptr< AccelerationT > gravityPlayerAcceleration = data.instantiate(AccelerationT{doodler->speed, {0, gravity}});
  bool accelerateLeft = false;
  bool accelerateRight = false;

  unsigned short updatesCount = 0;
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
    if(clock->getTimeFromUpdate().asSeconds() > updatesFrequency)
    {
      lrPlayerAcceleration->acceleration.x = 5 * (static_cast< char >(accelerateRight) - accelerateLeft);
      update.invoke();
      ++updatesCount;
      if (doodler->getPosition().y > 400)
      {
        doodler->jump();
      }
      if (updatesCount == updatesPerFrame)
      {
        window.clear();
        frame.invoke();
        window.display();
        updatesCount = 0;
      }
    }
  }
}