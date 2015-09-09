#include "./base_test_screen.hpp"

#include "hx3d/math/random.hpp"
#include "hx3d/math/vector_utils.hpp"

#include "hx3d/core/events.hpp"

#include "hx3d/utils/timer.hpp"

#include "hx3d/audio/audio.hpp"
#include "hx3d/audio/music.hpp"
#include "hx3d/audio/display/waveform.hpp"
#include "hx3d/audio/display/spectrum.hpp"
#include "hx3d/audio/converters/s16_converter.hpp"

#include "hx3d/graphics/texture.hpp"
#include "hx3d/graphics/sprite.hpp"
#include "hx3d/graphics/image.hpp"

using namespace hx3d;

class Test7: public BaseTestScreen {
public:
  Test7():
    music("sounds/test.ogg"),
    spectrum(200, 20000, 16),
    text(Core::Assets()->get<Font>("default")),
    fps(Core::Assets()->get<Font>("default"))
  {
    batch.setShader(Core::Assets()->get<Shader>("base"));
    batch.setCamera(camera);

    waveform.initialize(256, 256);
    waveform.setRefreshDelay(16);
    spectrum.initialize(256, 256);
    spectrum.setRefreshDelay(16);

    box.setTexture(Core::Assets()->get<Texture>("box"));
    box.transform.scale = glm::vec3(0.25f);
    box.transform.position.x = Core::App()->getWidth() / 2;
    box.transform.position.y = Core::App()->getHeight() / 2;

    musicToggle = false;

    text.transform.position.x = 20;
    text.transform.position.y = 20;
    fps.transform.position.x = 20;
    fps.transform.position.y = Core::App()->getHeight() - 20;

    waveform.transform.position.x = Core::App()->getWidth() / 4;
    waveform.transform.position.y = Core::App()->getHeight() / 2;

    spectrum.transform.position.x = Core::App()->getWidth() / 2 + Core::App()->getWidth() / 4;
    spectrum.transform.position.y = Core::App()->getHeight() / 2;

    Core::AudioDevice()->registerEffect(audio::Audio::PostChannel, converter);
  }

  void update() {
    camera.update();

    text.setContent(format("Music played: %s", music.isPlaying() ? "On" : "Off"));
    fps.setContent(format("FPS: %2.2f", Core::App()->getFPS()));

    if (Core::Events()->isScreenJustTouched()) {
      if (!musicToggle)
        music.play();
      else
        music.stop();

      musicToggle = !musicToggle;
    }

    float bass = spectrum.getNormalizedBarValue(4);
    box.transform.scale = glm::vec3(0.5f + (bass > 0.5f ? 1.f : 0.f));

    if (converter.hasProcessed()) {
      waveform.update(converter.getS16Stream(), converter.getSampleSize());
      spectrum.update(converter.getS16Stream(), converter.getSampleSize());
    }
  }

  void render() {
    Framebuffer::clear(Color(0, 0, 0));

    batch.begin();

    batch.draw(waveform);
    batch.draw(spectrum);
    batch.draw(box);

    batch.draw(text);
    batch.draw(fps);

    batch.end();
  }

  void hide() {
    Core::AudioDevice()->clearEffects(audio::Audio::PostChannel);
  }

private:
  Ptr<Texture> texture;

  OrthographicCamera camera;
  audio::Music music;
  audio::Waveform waveform;
  audio::Spectrum spectrum;
  audio::S16Converter converter;

  gui::Text text;
  gui::Text fps;

  Sprite box;

  bool musicToggle;

  Batch batch;
};
