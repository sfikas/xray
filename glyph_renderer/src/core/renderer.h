#ifndef RENDERER_H_
#define RENDERER_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>

using std::vector;

class Renderer {
public:
  Renderer();
  void LoadFont(const vector<uint8_t> &bytes);

private:
  FT_Library ft_library;
  FT_Face ft_face;
};

#endif // RENDERER_H_
