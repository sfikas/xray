#include <renderer.h>
#include <hb.h>
#include <hb-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <assert.h>
#include <vector>
#include <string>

using std::vector;
using std::wstring;

Renderer::Renderer() {
  FT_Init_FreeType(&this->ft_library);
  this->ft_face = nullptr;
  hb_feature_from_string("calt=1\0", -1, &this->hb_features[0]);
  hb_feature_from_string("liga=1\0", -1, &this->hb_features[1]);
}

void Renderer::LoadFont(const vector<uint8_t> &bytes) {
  FT_Error status_code = FT_New_Memory_Face(this->ft_library, bytes.data(), bytes.size(), 0, &this->ft_face);
  assert(status_code == 0);
  this->hb_font = hb_ft_font_create_referenced(this->ft_face);
}

vector<vector<hb_codepoint_t>> Renderer::LayoutLines(const vector<wstring> &lines) {
  hb_buffer_t* buffer = hb_buffer_create();

  vector<vector<hb_codepoint_t>> laid_out_lines(lines.size());
  for (size_t i = 0; i < lines.size(); i++) {
    hb_buffer_reset(buffer);

    auto line = lines[i];
    for (size_t j = 0; j < line.length(); j++) {
      hb_buffer_add(buffer, line[j], j);
    }

    hb_buffer_guess_segment_properties(buffer);
    hb_buffer_set_cluster_level(buffer, HB_BUFFER_CLUSTER_LEVEL_MONOTONE_GRAPHEMES);
    hb_shape(this->hb_font, buffer, this->hb_features, FONT_FEATURES_COUNT);

    size_t length;
    hb_glyph_info_t* glyph_infos = hb_buffer_get_glyph_infos(buffer, &length);

    vector<hb_codepoint_t> laid_out_line(length);
    for (size_t j = 0; j < length; j++) {
      laid_out_line[j] = glyph_infos[j].codepoint;
    }

    laid_out_lines[i] = laid_out_line;
  }

  return laid_out_lines;
}
