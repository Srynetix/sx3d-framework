#include "hx3d/window/sdl2/sdl2_application.hpp"
#include "hx3d/window/application_config.hpp"

#include "tests/test_game.hpp"

using namespace hx3d;

int main(int argc, char** argv) {
  ApplicationConfig config;
  config.title = "Tests";

  SDL2Application app(Make<TestGame>(), config);
  app.start();

  return 0;
}
