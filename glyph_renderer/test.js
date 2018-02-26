const fs = require('fs')
const { Renderer } = require("./glyph_renderer");

const renderer = new Renderer();
renderer.loadFont(fs.readFileSync("/Library/Fonts/Arial.ttf"));

console.time('renderer.layoutLines')
const laidOutLines = renderer.layoutLines([
  "23",
  "abcd"
]);
console.timeEnd('renderer.layoutLines')

console.log("Result:", laidOutLines)
