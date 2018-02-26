#include <renderer.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <assert.h>

using std::vector;

Renderer::Renderer() {
  FT_Init_FreeType(&this->ft_library);
}

void Renderer::LoadFont(const std::vector<uint8_t> &bytes) {
  FT_Open_Args font_open_args;
  font_open_args.flags = FT_OPEN_MEMORY;
  font_open_args.memory_base = bytes.data();
  font_open_args.memory_size = bytes.size();

  FT_Error status_code = FT_Open_Face(this->ft_library, &font_open_args, 0, &this->ft_face);
  assert(status_code == 0);
}
