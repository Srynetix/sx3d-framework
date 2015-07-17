/*
    Framebuffer.
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

#ifndef HX3D_GRAPHICS_FRAMEBUFFER
#define HX3D_GRAPHICS_FRAMEBUFFER

#include "hx3d/graphics/gl.hpp"

#include "hx3d/utils/ptr.hpp"

namespace hx3d {

class Texture;
class FrameBuffer {

public:
  /**
  Create a framebuffer.

  @param width  Width
  @param height Height
  */
  FrameBuffer(unsigned int width, unsigned int height);

  /**
  Get the framebuffer color buffer.
  @return Texture (Ptr)
  */
  Ptr<Texture> getColorBuffer();

  /////////////////

  /**
  Fetch the default framebuffer of the application.
  */
  static void fetchDefaultFrameBuffer();

  /**
  Use the framebuffer as current framebuffer.
  @param buf Framebuffer (Ptr)
  */
  static void use(Ptr<FrameBuffer> buf);

  /**
  Use the default framebuffer.
  */
  static void useDefault();

private:
  unsigned int _width;
  unsigned int _height;

  GLuint _id;
  Ptr<Texture> _colorBuffer;
  GLuint _depthBuffer;

  static GLint _defaultID;

  /**
  Create an empty framebuffer.
  */
  void create();

  /**
  Create a render buffer.

  @param id     Buffer id
  @param format Buffer format
  */
  void createRenderBuffer(GLuint& id, GLenum format);
};

} /* hx3d */

#endif
