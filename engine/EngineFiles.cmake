set(
  COMMON_FILES

  "${ENGINE_SRC}/audio/audio.cpp"
  "${ENGINE_SRC}/audio/music.cpp"

  "${ENGINE_SRC}/core/application.cpp"
  "${ENGINE_SRC}/core/application_config.cpp"
  "${ENGINE_SRC}/core/game.cpp"
  "${ENGINE_SRC}/core/core.cpp"
  "${ENGINE_SRC}/core/events.cpp"
  "${ENGINE_SRC}/core/screen.cpp"

  "${ENGINE_SRC}/utils/bitset.cpp"
  "${ENGINE_SRC}/utils/log.cpp"
  "${ENGINE_SRC}/utils/chronometer.cpp"
  "${ENGINE_SRC}/utils/timer.cpp"
  "${ENGINE_SRC}/utils/string.cpp"
  "${ENGINE_SRC}/utils/file.cpp"
  "${ENGINE_SRC}/utils/matrix_queue.cpp"
  "${ENGINE_SRC}/utils/resource.cpp"
  "${ENGINE_SRC}/utils/callback_timer.cpp"

  "${ENGINE_SRC}/math/function.cpp"
  "${ENGINE_SRC}/math/vector_utils.cpp"
  "${ENGINE_SRC}/math/number_utils.cpp"
  "${ENGINE_SRC}/math/random.cpp"

  "${ENGINE_SRC}/graphics/color.cpp"
  "${ENGINE_SRC}/graphics/image.cpp"
  "${ENGINE_SRC}/graphics/sprite.cpp"
  "${ENGINE_SRC}/graphics/shader.cpp"
  "${ENGINE_SRC}/graphics/mesh.cpp"
  "${ENGINE_SRC}/graphics/font.cpp"
  "${ENGINE_SRC}/graphics/texture.cpp"
  "${ENGINE_SRC}/graphics/texture_region.cpp"
  "${ENGINE_SRC}/graphics/batch.cpp"
  "${ENGINE_SRC}/graphics/framebuffer.cpp"
  "${ENGINE_SRC}/graphics/viewport.cpp"
  "${ENGINE_SRC}/graphics/camera.cpp"

  "${ENGINE_SRC}/graphics/viewports/fit_viewport.cpp"
  "${ENGINE_SRC}/graphics/cameras/perspective_camera.cpp"
  "${ENGINE_SRC}/graphics/cameras/orthographic_camera.cpp"
  "${ENGINE_SRC}/graphics/meshes/cube.cpp"
  "${ENGINE_SRC}/graphics/meshes/star.cpp"
  "${ENGINE_SRC}/graphics/meshes/origin.cpp"
  "${ENGINE_SRC}/graphics/utils/attribute_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/index_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/multi_array_buffer.cpp"
  "${ENGINE_SRC}/graphics/utils/transform.cpp"
  "${ENGINE_SRC}/graphics/utils/vbo.cpp"

  "${ENGINE_SRC}/gui/system.cpp"
  "${ENGINE_SRC}/gui/widget.cpp"
  "${ENGINE_SRC}/gui/text.cpp"
  "${ENGINE_SRC}/gui/button.cpp"

  "${ENGINE_SRC}/net/net.cpp"

  "${ENGINE_SRC}/physics/2d/collision_matrix.cpp"
  "${ENGINE_SRC}/physics/2d/body_def.cpp"
  "${ENGINE_SRC}/physics/2d/debug_draw.cpp"

  "${ENGINE_SRC}/ecs/base/id_base.cpp"
  "${ENGINE_SRC}/ecs/component.cpp"
  "${ENGINE_SRC}/ecs/entity.cpp"
)