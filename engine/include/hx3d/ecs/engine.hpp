/*
    Entity Component System: Base Engine.
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

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/bitset.hpp"

#include <map>
#include <typeindex>
#include <functional>
#include <vector>

namespace hx3d {
namespace ecs {

class Component;
class Entity;
class System;

/**
@brief Manages entity in a world.
*/
class Engine {

public:
  Engine();

  // ENTITY ///////////////////////

  /**
  @brief Create a new entity with the last entity id available.

  @return Entity (Ptr)
  */
  Pointer<Entity> createEntity();

  /**
  @brief Affect an ID to a uninitialized entity.

  @param entity Entity (Ptr)
  */
  void registerEntity(const Pointer<Entity>& entity);

  /**
  @brief Mark the entity for deletion from the engine.

  The deletion is delayed until the next update.

  @param entity Entity (Ptr)
  */
  void removeEntity(const Pointer<Entity>& entity);

  // COMPONENTS /////////////////////

  /**
  @brief Get the component for an entity.

  @param entity Entity (Ptr)

  @return Component
  */
  template <class T>
  Pointer<T> getComponent(const Pointer<Entity>& entity);

  /**
  @brief Add a component for an entity.

  @param entity     Entity (Ptr)
  @param component  Component (Ptr)
  */
  template <class T>
  void addComponent(const Pointer<Entity>& entity, const Pointer<Component>& component);

  /**
  @brief Create a component for an entity with variable args.

  @param entity Entity (Ptr)
  @param args   Arguments
  */
  template <class T, class... Args>
  void createComponent(const Pointer<Entity>& entity, Args... args);

  // SYSTEM /////////////////////////

  /**
  @brief Add a system to the engine.

  @param sys  System (Ptr)
  */
  template <class T>
  void addSystem(const Pointer<System>& sys);

  /**
  @brief Create a system into the engine.

  @param args Arguments
  */
  template <class T, class... Args>
  void createSystem(Args... args);

  // UTILS //////////////////////////

  /**
  @brief Get the number of components for an entity.

  @param entity Entity (Ptr)

  @return Number of components
  */
  unsigned int getComponentSize(const Pointer<Entity>& entity);

  /**
  @brief Get the number of entities.

  @return Number of entities
  */
  unsigned int getEntityCount();

  /**
  @brief Get the bits corresponding to the entity components.

  @param entity Entity (Ptr)

  @return Entity components bits
  */
  unsigned int getBits(const Pointer<Entity>& entity);

  /**
  @brief Register a callback for a certain component type when it's added.

  @param callback Callback function
  */
  template <class T>
  void registerComponentAdded(std::function<void(const Pointer<Component>&, const Pointer<Entity>&)> callback);

  /**
  @brief Register a callback for a certain component type when it's removed.

  @param callback Callback function
  */
  template <class T>
  void registerComponentRemoved(std::function<void(const Pointer<Component>&, const Pointer<Entity>&)> callback);

  /**
  @brief Update the engine.

  @param delta Delta time
  */
  void update(const float delta);

  /**
  @brief Remove everything from the engine.
  */
  void clear();

private:
  /// @brief Entities
  std::map<unsigned int, Pointer<Entity>> _entities;
  /// @brief Components
  std::map<unsigned int, std::map<std::type_index, Pointer<Component>>> _components;
  /// @brief Bits
  std::map<unsigned int, Bitset> _bits;

  /// @brief Systems
  std::map<std::type_index, Pointer<System>> _systems;
  /// @brief On component added callbacks
  std::map<std::type_index, std::function<void(Pointer<Component>, Pointer<Entity>)>> _onComponentAdded;
  /// @brief On component removed callbacks
  std::map<std::type_index, std::function<void(Pointer<Component>, Pointer<Entity>)>> _onComponentRemoved;

  /// @brief Entities to remove
  std::vector<unsigned int> _toRemove;

  /**
  @brief Remove all entities and their components.
  */
  void cleanEntities();

  /**
  @brief Get the last entity id available.

  @return Last id available
  */
  unsigned int lastEntityAvailable();

  /**
  @brief Add a component to an entity (internal).

  @param entityId   Entity ID
  @param component  Component (Ptr)
  */
  template <class T>
  void addInternalComponent(const unsigned int entityId, const Pointer<Component>& component);

  /**
  @brief Remove all components for an entity.

  @param entityId   Entity id
  */
  void removeComponents(const unsigned int entityId);
};

} /* ecs */
} /* hx3d */

#include "hx3d/ecs/_inline/engine.inl.hpp"
