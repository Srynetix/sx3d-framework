## Configuration

# Audio
# -> SDL2
if (NOT DEFINED AUDIO_PROVIDER)
  set(AUDIO_PROVIDER "SDL2")
endif()

# Window
# -> Dummy
# -> SDL2
if (NOT DEFINED WINDOW_PROVIDER)
  set(WINDOW_PROVIDER "SDL2")
endif()

## Flags C++

set(
  NEEDED_CXX_FLAGS
  "-std=c++11\
  -fdiagnostics-color=always\
  -Wall\
  -g"
)

IF(NOT ANDROID)
  set(NEEDED_CXX_FLAGS "${NEEDED_CXX_FLAGS} -march=native")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NEEDED_CXX_FLAGS}")
