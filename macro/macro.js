const fs = require('fs');

const TILE_COLOR_QTY = 16;
const TILE_SIZE_PX = 8;
const SCAN_SHIFTING = 1;
const SCREEN_SIZE_X = 128;
const SCREEN_SIZE_Y = 128;
const SCREEN_SIZE_X_TILES = 16;
const SCREEN_SIZE_Y_TILES = 16;
const PX_MULTIPLIER = 16;

var codeGen = "";

// MACRO para drawScreen
drawScreenCode = `
void drawScreen()
{
   clearStrip();
`;

var k = 0;
var l = 0;
for (var i = 0; i < SCREEN_SIZE_X_TILES; i++) {
    for (var j = 0; j < TILE_SIZE_PX; j++) {
        drawScreenCode +=
            `   drawStrip(` + j + `, img_orig[` + l + `]);\n`;

        k++;

        if (k == PX_MULTIPLIER) {
            l++;
            k = 0;
        }

    }

    drawScreenCode +=
        `   loadTiles(` + i + `);\n`;
    drawScreenCode +=
        `   clearStrip();\n\n`;
}

drawScreenCode += "}\n";

// MACRO para drawStrip
var drawStripCode = `
void drawStrip(u8 h_index_px, u16 *strip)
{
    u8 px0 = strip[0];
    u8 px1 = strip[1];
    u8 px2 = strip[2];
    u8 px3 = strip[3];
    u8 px4 = strip[4];
    u8 px5 = strip[5];
    u8 px6 = strip[6];
    u8 px7 = strip[7];
    
`;

var k = 0;
var l = 0;
for (var i = 0; i < SCREEN_SIZE_Y; i++) {
    drawStripCode +=
        `    tile_strip[` + i + `] <<= 4; tile_strip[` + i + `] += px` + l + `;\n`;

    k++;

    if (k == PX_MULTIPLIER) {
        l++;
        k = 0;
    }
}

drawStripCode += "}\n";

// MACRO para loadTiles
var loadTilesCode = `
void loadTiles(u8 h_index_tile)
{
`;

for (var i = 0; i < SCREEN_SIZE_Y_TILES; i++) {
    loadTilesCode +=
        `   VDP_loadTileData((const u32 *) (tile_strip + ` + i + ` * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + ` + i + ` * SCREEN_SIZE_X_TILES, 1, DMA);\n`;
}

loadTilesCode += "}\n";

// Merge a los outputs
codeGen = "//***** START MACRO GENERATED CODE *****\n" + drawScreenCode + drawStripCode + loadTilesCode + "\n//***** END MACRO GENERATED CODE *****";

fs.writeFileSync('./macro.c', codeGen);