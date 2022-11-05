#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <functional>
#include <type_traits>

#include "Event.hpp"
#include "Player.hpp"
#include "GameClock.hpp"

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

  const std::string assetsFolder = "bin/assets";

  sf::Texture inputTexture(const std::string& source)
  {
    const char* const TEXTURES_ERR = "Texture was not imported correctly";

    sf::Texture result;
    result.setSmooth(true);
    if(!result.loadFromFile(assetsFolder + source))
    {
      throw std::ios_base::failure(TEXTURES_ERR);
    }
    return result;
  }
}

void ddl::run(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame)
{
  GameData data;

  sf::Texture doodlerTexture = inputTexture("bin/assets/sprites/doodler.png");
  sf::Texture platformTexture = inputTexture("bin/assets/sprites/platform.png");

  std::shared_ptr< Player > doodler = data.instantiate(Player{sf::Sprite{doodlerTexture}});
  doodler->setScale(0.5, 0.5);
  doodler->setPosition(100, 100);

  const float updatesFrequency = 1 / static_cast< float >(wishedFPS * updatesPerFrame);

  Event frame;
  frame.subscribe(iterThroughRenderables{data.renderables, window});
  Event update;
  update.subscribe(iterThroughUpdatables{data.updatables});

  std::shared_ptr< GameClock > clock = data.instantiate(GameClock{});
  unsigned short updatesCount = 0;
  while(window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if ((event.type == sf::Event::Closed) ||
        ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
      {
        window.close();
        break;
      }

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
      {
      }
    }

    if(clock->getTimeFromUpdate().asSeconds() > updatesFrequency)
    {
      update.invoke();
      ++updatesCount;
      if (updatesCount == updatesPerFrame)
      {
        frame.invoke();
        updatesCount = 0;
      }
    }
  }
}