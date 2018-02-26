#include <renderer.h>
#include <hb.h>
#include <string>

Renderer::Renderer() {
  std::string text("Nel blu dipinto di blu");

  hb_buffer_t* buffer = hb_buffer_create();
  hb_buffer_add_utf8(buffer, text.data(), text.length(), 0, text.length());
  hb_buffer_guess_segment_properties(buffer);
}
