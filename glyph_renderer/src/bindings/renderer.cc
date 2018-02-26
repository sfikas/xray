#include <auto-wrap.h>
#include <renderer.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(Renderer) {
  emscripten::class_<Renderer>("Renderer")
    .constructor<>()
    .function("loadFont", WRAP(&Renderer::LoadFont))
    .function("layoutLines", WRAP(&Renderer::LayoutLines));
}
