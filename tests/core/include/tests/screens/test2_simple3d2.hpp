#include "./base_test_screen.hpp"

#include "hx3d/graphics/cameras/perspective_camera.hpp"

#include "hx3d/graphics/meshes/cube.hpp"
#include "hx3d/graphics/meshes/star.hpp"

using namespace hx3d;

class Test2: public BaseTestScreen {
public:
  Test2():
    camera(0.1f, 100.f),
    sprite(Core::Assets()->get<Texture>("box"))
  {
    camera.translate(glm::vec3(0.f, 0.f, -5.f));
    camera.rotate(180.f, glm::vec3(0, 1, 0));

    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    angle = 0.f;
  }

  void update() {
    camera.rotateAround(glm::vec3(0.f, 0.f, 0.f), 1.f, glm::vec3(0, 1, 0));
    camera.update();
  }

  void render() {

    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    sprite.transform.size = glm::vec3(0.25f);

    sprite.transform.position.z = -1.5f;
    for (int j = 0; j < 12; ++j) {
      sprite.transform.position.y = 1.5f - (0.25f * j);

      for (int i = 0; i < 12; ++i) {
        sprite.transform.position.x = -1.5f + (0.25f * i);
        sprite.transform.position.y *= std::cos(glm::radians(angle * 5));
        sprite.transform.rotation.x = std::tan(glm::radians(angle * 2));
        sprite.transform.rotation.y = (j + i) * 2 + glm::radians(angle);
        batch.draw(sprite);
      }
    }

    sprite.transform.position.z = 1.5f;
    for (int j = 0; j < 12; ++j) {
      sprite.transform.position.y = 1.5f - (0.25f * j);

      for (int i = 0; i < 12; ++i) {
        sprite.transform.position.x = -1.5f + (0.25f * i);
        sprite.transform.position.y *= std::cos(glm::radians(angle * 5));
        sprite.transform.rotation.x = std::tan(glm::radians(angle * 2));
        sprite.transform.rotation.y = (j + i) * 2 + glm::radians(angle);
        batch.draw(sprite);
      }
    }

    star.transform.size = glm::vec3(0.3f);
    star.transform.position.x = 0;
    star.transform.position.y = 0;
    star.transform.position.z = 0;
    star.transform.rotation.x = std::sin(glm::radians(angle * 10));
    star.transform.rotation.y = glm::radians(angle * 2);
    batch.draw(star);

    star.transform.size = glm::vec3(0.1f);
    star.transform.rotation.y = glm::radians(-angle * 4);

    star.transform.position.x = -0.75f;
    batch.draw(star);

    star.transform.position.x = 0.f;
    star.transform.position.z = -0.75f;
    batch.draw(star);

    star.transform.position.x = 0.75f;
    star.transform.position.z = 0.f;
    batch.draw(star);

    star.transform.position.x = 0;
    star.transform.position.z = 0.75f;
    batch.draw(star);

    star.transform.position.y = 0.75f;
    star.transform.position.z = 0;
    batch.draw(star);

    star.transform.position.y = -0.75f;
    batch.draw(star);

    angle += 0.5f;
    if (angle > 360.f) {
      angle -= 360.f;
    }

    batch.end();
  }

private:
  hx3d::PerspectiveCamera camera;

  hx3d::Batch batch;

  hx3d::mesh::Cube cube;
  hx3d::mesh::Star star;
  hx3d::Sprite sprite;

  float angle;
};