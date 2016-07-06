/*
    Configuration management.
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

namespace hx3d {

template <class T, class... Keys>
T Configuration::get(const std::string& key, Keys... keys) {
  auto node = _getNode(_root, key, keys...);
  return node.template as<T>();
}

template <class T>
T Configuration::get(const std::string& key) {
  return _root[key].as<T>();
}

template <class... Keys>
YAML::Node Configuration::_getNode(YAML::Node& node, const std::string& key, Keys... keys) {
  auto next = _getNode(node, key);
  return _getNode(next, keys...);
}

} /* hx3d */
