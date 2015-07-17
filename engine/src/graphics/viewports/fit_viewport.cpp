/*
    Fit viewport.
    Inspired by LibGDX fit viewport.
    Automatically fit the rendering in the screen.

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

#include "hx3d/graphics/viewports/fit_viewport.hpp"

#include <cmath>

#include "hx3d/utils/log.hpp"

namespace hx3d {

FitViewport::FitViewport(float worldWidth, float worldHeight, Ptr<Camera> camera) {
  _worldWidth = worldWidth;
  _worldHeight = worldHeight;
  _camera = camera;
}

void FitViewport::internalUpdate(bool centerCamera) {
  float tgtRatio = _screenHeight / _screenWidth;
  float srcRatio = _worldHeight / _worldWidth;
  float scale = tgtRatio > srcRatio ? _screenWidth / _worldWidth : _screenHeight / _worldHeight;

  int nx = std::floor(_worldWidth * scale);
  int ny = std::floor(_worldHeight * scale);

  _screenX = (_screenWidth - nx) / 2.f;
  _screenY = (_screenHeight - ny) / 2.f;
  _screenWidth = nx;
  _screenHeight = ny;

  apply(centerCamera);
}

}
