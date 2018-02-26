#include <emscripten/bind.h>
#include <renderer.h>

EMSCRIPTEN_BINDINGS(Renderer) {
  emscripten::class_<Renderer>("Renderer").constructor<>();
}
