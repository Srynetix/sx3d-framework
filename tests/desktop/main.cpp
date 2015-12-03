#include <gtest/gtest.h>

#include "hx3d/window/sdl2/sdl2_application.hpp"
#include "hx3d/window/application_config.hpp"

#include "tests/test_game.hpp"
#include "tests/tests.hpp"

using namespace hx3d;

TEST_F(Tests, Screens) {
  ApplicationConfig config;
  config.title = "Tests";

  SDL2Application app(Make<TestGame>(), config);
  app.start();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
