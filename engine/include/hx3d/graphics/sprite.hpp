/*
    Sprite.
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

#ifndef HX3D_GRAPHICS_SPRITE
#define HX3D_GRAPHICS_SPRITE

#include "hx3d/graphics/mesh.hpp"
#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/frame_buffer.hpp"

namespace hx3d {

class Sprite: public Mesh {

public:

  /**
  Create a sprite without texture.
  You must set it after with @link#setTexture.
  */
  Sprite();

  /**
  Create a sprite from a texture.
  @param texture Texture (Ptr)
  */
  Sprite(Ptr<Texture> texture);

  /**
  Create a sprite from a framebuffer color buffer.
  @param buffer Framebuffer (Ptr)
  */
  Sprite(Ptr<FrameBuffer> buffer);

  /**
  Set the sprite texture.
  @param texture Texture (Ptr)
  */
  void setTexture(Ptr<Texture> texture);

  /**
  Set the sprite texture from a framebuffer color buffer.
  @param buffer Framebuffer (Ptr)
  */
  void setTexture(Ptr<FrameBuffer> buffer);

  virtual void draw(Ptr<Shader> shader) override;

private:
  Ptr<Texture> _texture;
};

} /* hx3d */

#endif
