#ifndef RENDERER_H_
#define RENDERER_H_

#include <hb.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <string>

using std::vector;
using std::wstring;

#ifndef FONT_FEATURES_COUNT
#define FONT_FEATURES_COUNT 2
#endif

class Renderer {
public:
  Renderer();
  void LoadFont(const vector<uint8_t> &bytes);
  vector<vector<hb_codepoint_t>> LayoutLines(const vector<wstring> &lines);

private:
  FT_Library ft_library;
  FT_Face ft_face;
  hb_font_t* hb_font;
  hb_feature_t hb_features[FONT_FEATURES_COUNT];
};

#endif // RENDERER_H_
