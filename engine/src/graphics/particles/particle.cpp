/*
    Particle.
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

#include "hx3d/graphics/particles/particle.hpp"

#include "hx3d/math/interpolation.hpp"

namespace hx3d {

Particle::Particle() {
  reset();
}

void Particle::reset() {
  life = baseLife = 0.f;
  dead = false;
  color = Color::White;
}

void Particle::setTexture(Ptr<Texture> texture) {
  sprite.setTexture(texture);
}

void Particle::update(float delta) {
  life -= delta;

  if (life <= 0.f) {
    dead = true;
    return;
  }

  else {
    float percentage = life / baseLife;
    color.a = math::interpolate(0, 255, percentage, math::Interpolation::Linear);
    sprite.setTint(color);

    position.x -= velocity.x * delta;
    position.y -= velocity.y * delta;

    velocity.x -= gravity.x * delta;
    velocity.y -= gravity.y * delta;
  }
}

void Particle::draw(Batch& batch) {
  sprite.transform.position = position;
  sprite.transform.size = size;

  batch.draw(sprite);
}

} /* hx3d */
