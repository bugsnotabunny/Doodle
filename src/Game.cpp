#include "Game.hpp"

#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <functional>
#include <type_traits>

#include "Event.hpp"
#include "Player.hpp"

ddl::Game::Game(sf::RenderWindow& window, unsigned short wishedFPS, unsigned short updatesPerFrame):
  updatesFrequency_(1 / static_cast< float >(wishedFPS * updatesPerFrame)),
  updatesPerFrame_(updatesPerFrame),
  window_(window),
  updatables_(),
  renderables_(),
  clock_()
{
  updatables_.push_back(std::make_shared< IUpdatable >(clock_));
}

namespace
{
  using ddl::IRenderable;
  void iterThroughRenderables(std::deque< IRenderable& >& deq, sf::Window& window)
  {
    for (auto it = deq.begin(); it != deq.end(); ++it)
    {
      obj.render(window);
    }
  }

  using ddl::IUpdatable;
  void iterThroughUpdatables(std::deque< IUpdatable >& deq)
  {
    for (auto&& obj: deq)
    {
      obj.update();
    }
  }
}

void ddl::Game::run()
{
  const char* const GAME_ASSETS_ERR = "Some of game assets was not imported correctly";

  sf::Texture platformTexture;
  sf::Texture doodlerTexture;

  doodlerTexture.setSmooth(true);
  platformTexture.setSmooth(true);

  if(!doodlerTexture.loadFromFile("bin/assets/sprites/doodler.png"))
  {
    throw std::ios_base::failure(GAME_ASSETS_ERR);
  }

  if(!platformTexture.loadFromFile("bin/assets/sprites/platform.png"))
  {
    throw std::ios_base::failure(GAME_ASSETS_ERR);
  }

  std::shared_ptr< Player > doodler = instantiate(Player{sf::Sprite{doodlerTexture}});
  doodler->setScale(0.5, 0.5);
  doodler->setPosition(100, 100);

  Event frame;
  Event update;
  frame.subscribe(std::bind(iterThroughRenderables, std::ref(renderables_), std::ref(window_)));
  update.subscribe(std::bind(iterThroughUpdatables, std::ref(updatables_)));

  unsigned short updatesCount = 0;
  while(window_.isOpen())
  {
    sf::Event event;
    while (window_.pollEvent(event))
    {
      if ((event.type == sf::Event::Closed) ||
        ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
      {
        window_.close();
        break;
      }

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
      {
      }
    }

    if(clock_.getTimeFromUpdate().asSeconds() > updatesFrequency_)
    {
      update.invoke();
      ++updatesCount;
      if (updatesCount == updatesPerFrame_)
      {
        frame.invoke();
        updatesCount = 0;
      }
    }
  }
}