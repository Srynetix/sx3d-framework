/*
    Sprite node.
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

#pragma once

#include "hx3d/ecs/node.hpp"

namespace hx3d {

namespace graphics {
  class Texture;
  class Sprite;
}

namespace ecs {

/**
@brief Simple sprite node.
*/
class SpriteNode: public Node {
public:
  /**
  @brief Create a sprite node using a texture

  @param name    Name
  @param texture Texture (Ptr)
  */
  SpriteNode(std::string name, const Pointer<graphics::Texture>& texture);

  virtual void draw(const Pointer<graphics::Batch>& batch) override;
  virtual void update(float delta) override;

protected:
  Pointer<graphics::Texture> _texture;
  Pointer<graphics::Sprite> _sprite;
};

} /* ecs */
} /* hx3d */
