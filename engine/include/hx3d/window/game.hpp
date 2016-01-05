/*
    Game management.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA


    TODO
    > Screen transitions using framebuffers
*/

#ifndef HX3D_WINDOW_GAME
#define HX3D_WINDOW_GAME

#include "hx3d/window/screen.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {
namespace window {

/**
@brief Game main class: multiple screens management
*/
class Game {
public:
  Game();

  /**
  @brief Initialize the game
  */
  virtual void create();

  /**
  @brief Render the current scren
  */
  virtual void render();

  /**
  @brief Update the current screen

  @param delta Delta time
  */
  virtual void update(float delta);

  /**
  @brief Resize the current screen

  @param width  New width
  @param height New height
  */
  virtual void resize(int width, int height);

  /**
  @brief Pause the current screen
  */
  virtual void pause();

  /**
  @brief Resume the current screen
  */
  virtual void resume();

  /**
  @brief Clean the current screen
  */
  virtual void dispose();

  /**
  @brief Stop the game.
  */
  virtual void stop();

  /**
  @brief Set the current screen.

  @param screen Screen (Ptr)
  */
  void setScreen(Ptr<Screen> screen);

  /**
  @brief Test if the game is running.

  @return True/False
  */
  bool isRunning();

private:
  bool _running;
  Ptr<Screen> _screen;
};

} /* window */
} /* hx3d */

#endif /* HX3D_WINDOW_GAME */
