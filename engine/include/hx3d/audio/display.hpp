/*
    Audio effect display.
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
*/

#ifndef HX3D_AUDIO_DISPLAY
#define HX3D_AUDIO_DISPLAY

#include <SDL2/SDL_types.h>

#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/timer.hpp"

namespace hx3d {
namespace audio {

class Display: public hx3d::Sprite {

public:
  /**
  Create an empty display with a refresh delay of 50.
  See @link#initialize to construct the texture.
  */
  Display();

  /**
  Create an empty display with a custom refresh delay.
  See @link#initialize to construct the texture.
  @param refreshDelay Refresh delay
  */
  Display(int refreshDelay);
  virtual ~Display();

  /**
  Initialize the display.
  @param width  Width
  @param height Height
  */
  void initialize(unsigned int width, unsigned int height);

  /**
  Set the refresh delay.
  @param refreshDelay Refresh delay
  */
  void setRefreshDelay(int refreshDelay);

  /**
  Update the display.
  @param stream Stream of amplitudes (between -32767 and 32767)
  @param length Length of the stream
  */
  virtual void update(Sint16* stream, int length) = 0;
  virtual void onInitialization();

  /* Not needed */
  void setTexture(Ptr<Texture>) = delete;
  void setTexture(Ptr<Framebuffer>) = delete;

protected:
  Image _image;
  Timer _timer;
  int _refreshDelay;
  bool _initialized;

  /**
  Draw white borders.
  */
  void drawBorders() {
    _image.setRect(0, 0, _image.getWidth(), 1, Color::White);
    _image.setRect(0, 0, 1, _image.getHeight(), Color::White);
    _image.setRect(_image.getWidth() - 1, 0, 1, _image.getHeight(), Color::White);
    _image.setRect(0, _image.getHeight() - 1, _image.getWidth(), 1, Color::White);
  }
};

} /* audio */
} /* hx3d */

#endif