/*
    GUI text.
    Render text.

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

#include "hx3d/gui/text.hpp"

#include "hx3d/graphics/font.hpp"

#include "hx3d/utils/log.hpp"

namespace hx3d {
namespace gui {

Text::Text():
  Text(nullptr) {}

Text::Text(Ptr<Font> font):
  Text(nullptr, font) {}

Text::Text(Ptr<Widget> parent, Ptr<Font> font):
  Widget(parent), _font(font), _content("") {
    init();
}

void Text::init() {
  setTint(Color(255, 255, 255));
  transform.size = glm::vec3(1);
}

void Text::setFont(Ptr<Font> font) {
  _font = font;
}

void Text::setContent(std::string content) {
  _content = content;
}

Ptr<Font> Text::getFont() {
  return _font;
}

void Text::draw(Ptr<Shader> shader) {

  std::wstring wtext(_content.begin(), _content.end());
  glm::vec2 pen(0, 0);

  for (unsigned int i = 0; i < _content.size(); ++i) {
    texture_glyph_t *glyph = texture_font_get_glyph(_font->font, _content[i]);
    if (glyph != nullptr) {
      float kerning = 0.f;
      if (i > 0) {
        kerning = texture_glyph_get_kerning(glyph, _content[i-1]);
      }

      pen.x += transform.size.x * kerning;
      float x0 = pen.x + transform.size.x * glyph->offset_x;
      float y0 = pen.y + transform.size.y * glyph->offset_y;
      float x1 = x0 + transform.size.x * glyph->width;
      float y1 = y0 - transform.size.y * glyph->height;
      float s0 = glyph->s0;
      float t0 = glyph->t0;
      float s1 = glyph->s1;
      float t1 = glyph->t1;

      setAttribute("Position", std::vector<float> {
        x0, y0, 0,
        x0, y1, 0,
        x1, y1, 0,
        x1, y0, 0
      });

      setAttribute("Texture", std::vector<float> {
        s0, t0,
        s0, t1,
        s1, t1,
        s1, t0
      });

      uploadAll();

      Mesh::draw(shader);

      pen.x += transform.size.x * glyph->advance_x;
    }
  }
}

void Text::functionDraw(Ptr<Shader> shader, math::Function function) {
  std::wstring wtext(_content.begin(), _content.end());
  glm::vec2 pen(0, 0);

  function.reset();

  for (unsigned int i = 0; i < _content.size(); ++i) {
    texture_glyph_t *glyph = texture_font_get_glyph(_font->font, _content[i]);
    if (glyph != nullptr) {
      float kerning = 0.f;
      if (i > 0) {
        kerning = texture_glyph_get_kerning(glyph, _content[i-1]);
      }

      pen += function.sample();
      pen.x += kerning;

      float x0 = pen.x + glyph->offset_x;
      float y0 = pen.y + glyph->offset_y;
      float x1 = x0 + glyph->width;
      float y1 = y0 - glyph->height;
      float s0 = glyph->s0;
      float t0 = glyph->t0;
      float s1 = glyph->s1;
      float t1 = glyph->t1;

      setAttribute("Position", std::vector<float> {
        x0, y0, 0,
        x0, y1, 0,
        x1, y1, 0,
        x1, y0, 0
      });

      setAttribute("Texture", std::vector<float> {
        s0, t0,
        s0, t1,
        s1, t1,
        s1, t0
      });

      uploadAll();

      Mesh::draw(shader);

      pen.x += glyph->advance_x;
      function.step();
    }
  }
}

} /* gui */
} /* hx3d */
