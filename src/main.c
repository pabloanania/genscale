/*
TO DO:
* Version 128*160
*
*/

#include <genesis.h>
#include "KDebug.h"
#include "tools.h"
#include "timer.h"

// CONSTANTES
#define TILE_COLOR_QTY 16
#define TILE_SIZE_PX 8
#define SCAN_SHIFTING 1
#define SCREEN_SIZE_X 128
#define SCREEN_SIZE_Y 128
#define SCREEN_SIZE_X_TILES 16
#define SCREEN_SIZE_Y_TILES 16
//#define SCREEN_SIZE_X 256
//#define SCREEN_SIZE_Y 200
//#define SCREEN_SIZE_X_TILES 32
//#define SCREEN_SIZE_Y_TILES 25

// PROTOTIPOS
void mainLoop();
void input();
void clearStrip();
void scrollMap();
void drawScreen();
void drawStrip(u8 h_index_px, u16 *strip);
void loadTiles(u8 h_index_tile);

// VARIABLES GLOBALES
u16 img_orig[8][8] = {
    {5, 5, 5, 5, 5, 5, 5, 5},
    {5, 9, 2, 2, 2, 2, 2, 5},
    {5, 9, 9, 2, 2, 2, 2, 5},
    {5, 9, 9, 9, 2, 2, 2, 5},
    {5, 9, 9, 9, 9, 2, 2, 5},
    {5, 9, 9, 9, 9, 9, 2, 5},
    {5, 9, 9, 9, 9, 9, 9, 5},
    {5, 5, 5, 5, 5, 5, 5, 5}};
u32 tile_strip[SCREEN_SIZE_Y];
s16 planX = 0;
s16 planY = 0;

// VARIABLES GLOBALES DE PRUEBA

int main()
{
    // Inicializa, desactiva interrupts y luego reactiva. Siempre hay que desactivar interrupts al llamar a VDP
    SYS_disableInts();
    VDP_setScreenWidth256();
    SYS_enableInts();

    // Posiciona los tiles en donde corresponde
    VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL3, 0, 0, 0, TILE_USERINDEX), 0, 0, SCREEN_SIZE_X_TILES, SCREEN_SIZE_Y_TILES);

    while (TRUE)
    {
        mainLoop();

        VDP_waitVSync();
    }

    return 0;
}

void mainLoop()
{
    input();

    scrollMap();

    drawScreen();

    // Dibuja FPS
    VDP_showFPS(1);
}

void input()
{
    u16 value = JOY_readJoypad(JOY_1);

    if (value & BUTTON_UP)
        planY++;
    else if (value & BUTTON_DOWN)
        planY--;

    if (value & BUTTON_RIGHT)
        planX++;
    else if (value & BUTTON_LEFT)
        planX--;
}

void scrollMap()
{
    VDP_setHorizontalScroll(PLAN_B, planX);
    VDP_setVerticalScroll(PLAN_B, planY);
}

void clearStrip() {
	for (int i=0; i<SCREEN_SIZE_Y; i++)
		tile_strip[i] = 0;
}

//***** START MACRO GENERATED CODE *****

void drawScreen()
{
   clearStrip();
   drawStrip(0, img_orig[0]);
   drawStrip(1, img_orig[0]);
   drawStrip(2, img_orig[0]);
   drawStrip(3, img_orig[0]);
   drawStrip(4, img_orig[0]);
   drawStrip(5, img_orig[0]);
   drawStrip(6, img_orig[0]);
   drawStrip(7, img_orig[0]);
   loadTiles(0);
   clearStrip();

   drawStrip(0, img_orig[0]);
   drawStrip(1, img_orig[0]);
   drawStrip(2, img_orig[0]);
   drawStrip(3, img_orig[0]);
   drawStrip(4, img_orig[0]);
   drawStrip(5, img_orig[0]);
   drawStrip(6, img_orig[0]);
   drawStrip(7, img_orig[0]);
   loadTiles(1);
   clearStrip();

   drawStrip(0, img_orig[1]);
   drawStrip(1, img_orig[1]);
   drawStrip(2, img_orig[1]);
   drawStrip(3, img_orig[1]);
   drawStrip(4, img_orig[1]);
   drawStrip(5, img_orig[1]);
   drawStrip(6, img_orig[1]);
   drawStrip(7, img_orig[1]);
   loadTiles(2);
   clearStrip();

   drawStrip(0, img_orig[1]);
   drawStrip(1, img_orig[1]);
   drawStrip(2, img_orig[1]);
   drawStrip(3, img_orig[1]);
   drawStrip(4, img_orig[1]);
   drawStrip(5, img_orig[1]);
   drawStrip(6, img_orig[1]);
   drawStrip(7, img_orig[1]);
   loadTiles(3);
   clearStrip();

   drawStrip(0, img_orig[2]);
   drawStrip(1, img_orig[2]);
   drawStrip(2, img_orig[2]);
   drawStrip(3, img_orig[2]);
   drawStrip(4, img_orig[2]);
   drawStrip(5, img_orig[2]);
   drawStrip(6, img_orig[2]);
   drawStrip(7, img_orig[2]);
   loadTiles(4);
   clearStrip();

   drawStrip(0, img_orig[2]);
   drawStrip(1, img_orig[2]);
   drawStrip(2, img_orig[2]);
   drawStrip(3, img_orig[2]);
   drawStrip(4, img_orig[2]);
   drawStrip(5, img_orig[2]);
   drawStrip(6, img_orig[2]);
   drawStrip(7, img_orig[2]);
   loadTiles(5);
   clearStrip();

   drawStrip(0, img_orig[3]);
   drawStrip(1, img_orig[3]);
   drawStrip(2, img_orig[3]);
   drawStrip(3, img_orig[3]);
   drawStrip(4, img_orig[3]);
   drawStrip(5, img_orig[3]);
   drawStrip(6, img_orig[3]);
   drawStrip(7, img_orig[3]);
   loadTiles(6);
   clearStrip();

   drawStrip(0, img_orig[3]);
   drawStrip(1, img_orig[3]);
   drawStrip(2, img_orig[3]);
   drawStrip(3, img_orig[3]);
   drawStrip(4, img_orig[3]);
   drawStrip(5, img_orig[3]);
   drawStrip(6, img_orig[3]);
   drawStrip(7, img_orig[3]);
   loadTiles(7);
   clearStrip();

   drawStrip(0, img_orig[4]);
   drawStrip(1, img_orig[4]);
   drawStrip(2, img_orig[4]);
   drawStrip(3, img_orig[4]);
   drawStrip(4, img_orig[4]);
   drawStrip(5, img_orig[4]);
   drawStrip(6, img_orig[4]);
   drawStrip(7, img_orig[4]);
   loadTiles(8);
   clearStrip();

   drawStrip(0, img_orig[4]);
   drawStrip(1, img_orig[4]);
   drawStrip(2, img_orig[4]);
   drawStrip(3, img_orig[4]);
   drawStrip(4, img_orig[4]);
   drawStrip(5, img_orig[4]);
   drawStrip(6, img_orig[4]);
   drawStrip(7, img_orig[4]);
   loadTiles(9);
   clearStrip();

   drawStrip(0, img_orig[5]);
   drawStrip(1, img_orig[5]);
   drawStrip(2, img_orig[5]);
   drawStrip(3, img_orig[5]);
   drawStrip(4, img_orig[5]);
   drawStrip(5, img_orig[5]);
   drawStrip(6, img_orig[5]);
   drawStrip(7, img_orig[5]);
   loadTiles(10);
   clearStrip();

   drawStrip(0, img_orig[5]);
   drawStrip(1, img_orig[5]);
   drawStrip(2, img_orig[5]);
   drawStrip(3, img_orig[5]);
   drawStrip(4, img_orig[5]);
   drawStrip(5, img_orig[5]);
   drawStrip(6, img_orig[5]);
   drawStrip(7, img_orig[5]);
   loadTiles(11);
   clearStrip();

   drawStrip(0, img_orig[6]);
   drawStrip(1, img_orig[6]);
   drawStrip(2, img_orig[6]);
   drawStrip(3, img_orig[6]);
   drawStrip(4, img_orig[6]);
   drawStrip(5, img_orig[6]);
   drawStrip(6, img_orig[6]);
   drawStrip(7, img_orig[6]);
   loadTiles(12);
   clearStrip();

   drawStrip(0, img_orig[6]);
   drawStrip(1, img_orig[6]);
   drawStrip(2, img_orig[6]);
   drawStrip(3, img_orig[6]);
   drawStrip(4, img_orig[6]);
   drawStrip(5, img_orig[6]);
   drawStrip(6, img_orig[6]);
   drawStrip(7, img_orig[6]);
   loadTiles(13);
   clearStrip();

   drawStrip(0, img_orig[7]);
   drawStrip(1, img_orig[7]);
   drawStrip(2, img_orig[7]);
   drawStrip(3, img_orig[7]);
   drawStrip(4, img_orig[7]);
   drawStrip(5, img_orig[7]);
   drawStrip(6, img_orig[7]);
   drawStrip(7, img_orig[7]);
   loadTiles(14);
   clearStrip();

   drawStrip(0, img_orig[7]);
   drawStrip(1, img_orig[7]);
   drawStrip(2, img_orig[7]);
   drawStrip(3, img_orig[7]);
   drawStrip(4, img_orig[7]);
   drawStrip(5, img_orig[7]);
   drawStrip(6, img_orig[7]);
   drawStrip(7, img_orig[7]);
   loadTiles(15);
   clearStrip();

}

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

    tile_strip[0] <<= 4; tile_strip[0] += px0;
    tile_strip[1] <<= 4; tile_strip[1] += px0;
    tile_strip[2] <<= 4; tile_strip[2] += px0;
    tile_strip[3] <<= 4; tile_strip[3] += px0;
    tile_strip[4] <<= 4; tile_strip[4] += px0;
    tile_strip[5] <<= 4; tile_strip[5] += px0;
    tile_strip[6] <<= 4; tile_strip[6] += px0;
    tile_strip[7] <<= 4; tile_strip[7] += px0;
    tile_strip[8] <<= 4; tile_strip[8] += px0;
    tile_strip[9] <<= 4; tile_strip[9] += px0;
    tile_strip[10] <<= 4; tile_strip[10] += px0;
    tile_strip[11] <<= 4; tile_strip[11] += px0;
    tile_strip[12] <<= 4; tile_strip[12] += px0;
    tile_strip[13] <<= 4; tile_strip[13] += px0;
    tile_strip[14] <<= 4; tile_strip[14] += px0;
    tile_strip[15] <<= 4; tile_strip[15] += px0;
    tile_strip[16] <<= 4; tile_strip[16] += px1;
    tile_strip[17] <<= 4; tile_strip[17] += px1;
    tile_strip[18] <<= 4; tile_strip[18] += px1;
    tile_strip[19] <<= 4; tile_strip[19] += px1;
    tile_strip[20] <<= 4; tile_strip[20] += px1;
    tile_strip[21] <<= 4; tile_strip[21] += px1;
    tile_strip[22] <<= 4; tile_strip[22] += px1;
    tile_strip[23] <<= 4; tile_strip[23] += px1;
    tile_strip[24] <<= 4; tile_strip[24] += px1;
    tile_strip[25] <<= 4; tile_strip[25] += px1;
    tile_strip[26] <<= 4; tile_strip[26] += px1;
    tile_strip[27] <<= 4; tile_strip[27] += px1;
    tile_strip[28] <<= 4; tile_strip[28] += px1;
    tile_strip[29] <<= 4; tile_strip[29] += px1;
    tile_strip[30] <<= 4; tile_strip[30] += px1;
    tile_strip[31] <<= 4; tile_strip[31] += px1;
    tile_strip[32] <<= 4; tile_strip[32] += px2;
    tile_strip[33] <<= 4; tile_strip[33] += px2;
    tile_strip[34] <<= 4; tile_strip[34] += px2;
    tile_strip[35] <<= 4; tile_strip[35] += px2;
    tile_strip[36] <<= 4; tile_strip[36] += px2;
    tile_strip[37] <<= 4; tile_strip[37] += px2;
    tile_strip[38] <<= 4; tile_strip[38] += px2;
    tile_strip[39] <<= 4; tile_strip[39] += px2;
    tile_strip[40] <<= 4; tile_strip[40] += px2;
    tile_strip[41] <<= 4; tile_strip[41] += px2;
    tile_strip[42] <<= 4; tile_strip[42] += px2;
    tile_strip[43] <<= 4; tile_strip[43] += px2;
    tile_strip[44] <<= 4; tile_strip[44] += px2;
    tile_strip[45] <<= 4; tile_strip[45] += px2;
    tile_strip[46] <<= 4; tile_strip[46] += px2;
    tile_strip[47] <<= 4; tile_strip[47] += px2;
    tile_strip[48] <<= 4; tile_strip[48] += px3;
    tile_strip[49] <<= 4; tile_strip[49] += px3;
    tile_strip[50] <<= 4; tile_strip[50] += px3;
    tile_strip[51] <<= 4; tile_strip[51] += px3;
    tile_strip[52] <<= 4; tile_strip[52] += px3;
    tile_strip[53] <<= 4; tile_strip[53] += px3;
    tile_strip[54] <<= 4; tile_strip[54] += px3;
    tile_strip[55] <<= 4; tile_strip[55] += px3;
    tile_strip[56] <<= 4; tile_strip[56] += px3;
    tile_strip[57] <<= 4; tile_strip[57] += px3;
    tile_strip[58] <<= 4; tile_strip[58] += px3;
    tile_strip[59] <<= 4; tile_strip[59] += px3;
    tile_strip[60] <<= 4; tile_strip[60] += px3;
    tile_strip[61] <<= 4; tile_strip[61] += px3;
    tile_strip[62] <<= 4; tile_strip[62] += px3;
    tile_strip[63] <<= 4; tile_strip[63] += px3;
    tile_strip[64] <<= 4; tile_strip[64] += px4;
    tile_strip[65] <<= 4; tile_strip[65] += px4;
    tile_strip[66] <<= 4; tile_strip[66] += px4;
    tile_strip[67] <<= 4; tile_strip[67] += px4;
    tile_strip[68] <<= 4; tile_strip[68] += px4;
    tile_strip[69] <<= 4; tile_strip[69] += px4;
    tile_strip[70] <<= 4; tile_strip[70] += px4;
    tile_strip[71] <<= 4; tile_strip[71] += px4;
    tile_strip[72] <<= 4; tile_strip[72] += px4;
    tile_strip[73] <<= 4; tile_strip[73] += px4;
    tile_strip[74] <<= 4; tile_strip[74] += px4;
    tile_strip[75] <<= 4; tile_strip[75] += px4;
    tile_strip[76] <<= 4; tile_strip[76] += px4;
    tile_strip[77] <<= 4; tile_strip[77] += px4;
    tile_strip[78] <<= 4; tile_strip[78] += px4;
    tile_strip[79] <<= 4; tile_strip[79] += px4;
    tile_strip[80] <<= 4; tile_strip[80] += px5;
    tile_strip[81] <<= 4; tile_strip[81] += px5;
    tile_strip[82] <<= 4; tile_strip[82] += px5;
    tile_strip[83] <<= 4; tile_strip[83] += px5;
    tile_strip[84] <<= 4; tile_strip[84] += px5;
    tile_strip[85] <<= 4; tile_strip[85] += px5;
    tile_strip[86] <<= 4; tile_strip[86] += px5;
    tile_strip[87] <<= 4; tile_strip[87] += px5;
    tile_strip[88] <<= 4; tile_strip[88] += px5;
    tile_strip[89] <<= 4; tile_strip[89] += px5;
    tile_strip[90] <<= 4; tile_strip[90] += px5;
    tile_strip[91] <<= 4; tile_strip[91] += px5;
    tile_strip[92] <<= 4; tile_strip[92] += px5;
    tile_strip[93] <<= 4; tile_strip[93] += px5;
    tile_strip[94] <<= 4; tile_strip[94] += px5;
    tile_strip[95] <<= 4; tile_strip[95] += px5;
    tile_strip[96] <<= 4; tile_strip[96] += px6;
    tile_strip[97] <<= 4; tile_strip[97] += px6;
    tile_strip[98] <<= 4; tile_strip[98] += px6;
    tile_strip[99] <<= 4; tile_strip[99] += px6;
    tile_strip[100] <<= 4; tile_strip[100] += px6;
    tile_strip[101] <<= 4; tile_strip[101] += px6;
    tile_strip[102] <<= 4; tile_strip[102] += px6;
    tile_strip[103] <<= 4; tile_strip[103] += px6;
    tile_strip[104] <<= 4; tile_strip[104] += px6;
    tile_strip[105] <<= 4; tile_strip[105] += px6;
    tile_strip[106] <<= 4; tile_strip[106] += px6;
    tile_strip[107] <<= 4; tile_strip[107] += px6;
    tile_strip[108] <<= 4; tile_strip[108] += px6;
    tile_strip[109] <<= 4; tile_strip[109] += px6;
    tile_strip[110] <<= 4; tile_strip[110] += px6;
    tile_strip[111] <<= 4; tile_strip[111] += px6;
    tile_strip[112] <<= 4; tile_strip[112] += px7;
    tile_strip[113] <<= 4; tile_strip[113] += px7;
    tile_strip[114] <<= 4; tile_strip[114] += px7;
    tile_strip[115] <<= 4; tile_strip[115] += px7;
    tile_strip[116] <<= 4; tile_strip[116] += px7;
    tile_strip[117] <<= 4; tile_strip[117] += px7;
    tile_strip[118] <<= 4; tile_strip[118] += px7;
    tile_strip[119] <<= 4; tile_strip[119] += px7;
    tile_strip[120] <<= 4; tile_strip[120] += px7;
    tile_strip[121] <<= 4; tile_strip[121] += px7;
    tile_strip[122] <<= 4; tile_strip[122] += px7;
    tile_strip[123] <<= 4; tile_strip[123] += px7;
    tile_strip[124] <<= 4; tile_strip[124] += px7;
    tile_strip[125] <<= 4; tile_strip[125] += px7;
    tile_strip[126] <<= 4; tile_strip[126] += px7;
    tile_strip[127] <<= 4; tile_strip[127] += px7;
}

void loadTiles(u8 h_index_tile)
{
   VDP_loadTileData((const u32 *) (tile_strip + 0 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 0 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 1 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 1 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 2 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 2 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 3 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 3 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 4 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 4 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 5 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 5 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 6 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 6 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 7 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 7 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 8 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 8 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 9 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 9 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 10 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 10 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 11 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 11 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 12 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 12 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 13 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 13 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 14 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 14 * SCREEN_SIZE_X_TILES, 1, DMA);
   VDP_loadTileData((const u32 *) (tile_strip + 15 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 15 * SCREEN_SIZE_X_TILES, 1, DMA);
}

//***** END MACRO GENERATED CODE *****
