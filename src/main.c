/*
TO DO:
* Los tiles a lo horizontal deben calcularse como corresponde
*/

#include <genesis.h>
#include "KDebug.h"
#include "tools.h"
#include "timer.h"

// CONSTANTES
#define IMG_SIZE_SIDE 8
#define TILE_COLOR_QTY 16
#define TILE_SIZE_PX 8
#define SCAN_SHIFTING 1
#define SCREEN_SIZE_X 32
#define SCREEN_SIZE_Y 32
#define SCREEN_SIZE_X_TILES 4
#define SCREEN_SIZE_Y_TILES 4
//#define SCREEN_SIZE_X 256
//#define SCREEN_SIZE_Y 200
//#define SCREEN_SIZE_X_TILES 32
//#define SCREEN_SIZE_Y_TILES 25

// PROTOTIPOS
void mainLoop();
void input();
void clearStrip();
void scrollMap();
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

    clearStrip();

    drawStrip(0, img_orig[0]);
    drawStrip(1, img_orig[0]);
    drawStrip(2, img_orig[0]);
    drawStrip(3, img_orig[0]);
    drawStrip(4, img_orig[1]);
    drawStrip(5, img_orig[1]);
    drawStrip(6, img_orig[1]);
    drawStrip(7, img_orig[1]);

    loadTiles(0);
    clearStrip();

    drawStrip(0, img_orig[2]);
    drawStrip(1, img_orig[2]);
    drawStrip(2, img_orig[2]);
    drawStrip(3, img_orig[2]);
    drawStrip(4, img_orig[3]);
    drawStrip(5, img_orig[3]);
    drawStrip(6, img_orig[3]);
    drawStrip(7, img_orig[3]);

    loadTiles(1);
    clearStrip();

    drawStrip(0, img_orig[4]);
    drawStrip(1, img_orig[4]);
    drawStrip(2, img_orig[4]);
    drawStrip(3, img_orig[4]);
    drawStrip(4, img_orig[5]);
    drawStrip(5, img_orig[5]);
    drawStrip(6, img_orig[5]);
    drawStrip(7, img_orig[5]);

    loadTiles(2);
    clearStrip();

    drawStrip(0, img_orig[6]);
    drawStrip(1, img_orig[6]);
    drawStrip(2, img_orig[6]);
    drawStrip(3, img_orig[6]);
    drawStrip(4, img_orig[7]);
    drawStrip(5, img_orig[7]);
    drawStrip(6, img_orig[7]);
    drawStrip(7, img_orig[7]);

    loadTiles(3);
    clearStrip();

    // Dibuja datos
    //uintToStr(scan_step, integerConverter, 5);
    //VDP_drawTextBG(PLAN_A, integerConverter, 1, 0);

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

void drawStrip(u8 h_index_px, u16 *strip)
{
    // TEST: Esto agilizaria el procesamiento?
    u8 px0 = strip[0];
    u8 px1 = strip[1];
    u8 px2 = strip[2];
    u8 px3 = strip[3];
    u8 px4 = strip[4];
    u8 px5 = strip[5];
    u8 px6 = strip[6];
    u8 px7 = strip[7];

    // *** MACRO: DIBUJA STRIP ***
    tile_strip[0] <<= 4;
    tile_strip[0] += px0;
    tile_strip[1] <<= 4;
    tile_strip[1] += px0;
    tile_strip[2] <<= 4;
    tile_strip[2] += px0;
    tile_strip[3] <<= 4;
    tile_strip[3] += px0;
    tile_strip[4] <<= 4;
    tile_strip[4] += px1;
    tile_strip[5] <<= 4;
    tile_strip[5] += px1;
    tile_strip[6] <<= 4;
    tile_strip[6] += px1;
    tile_strip[7] <<= 4;
    tile_strip[7] += px1;

    tile_strip[8] <<= 4;
    tile_strip[8] += px2;
    tile_strip[9] <<= 4;
    tile_strip[9] += px2;
    tile_strip[10] <<= 4;
    tile_strip[10] += px2;
    tile_strip[11] <<= 4;
    tile_strip[11] += px2;
    tile_strip[12] <<= 4;
    tile_strip[12] += px3;
    tile_strip[13] <<= 4;
    tile_strip[13] += px3;
    tile_strip[14] <<= 4;
    tile_strip[14] += px3;
    tile_strip[15] <<= 4;
    tile_strip[15] += px3;

    tile_strip[16] <<= 4;
    tile_strip[16] += px4;
    tile_strip[17] <<= 4;
    tile_strip[17] += px4;
    tile_strip[18] <<= 4;
    tile_strip[18] += px4;
    tile_strip[19] <<= 4;
    tile_strip[19] += px4;
    tile_strip[20] <<= 4;
    tile_strip[20] += px5;
    tile_strip[21] <<= 4;
    tile_strip[21] += px5;
    tile_strip[22] <<= 4;
    tile_strip[22] += px5;
    tile_strip[23] <<= 4;
    tile_strip[23] += px5;

    tile_strip[24] <<= 4;
    tile_strip[24] += px6;
    tile_strip[25] <<= 4;
    tile_strip[25] += px6;
    tile_strip[26] <<= 4;
    tile_strip[26] += px6;
    tile_strip[27] <<= 4;
    tile_strip[27] += px6;
    tile_strip[28] <<= 4;
    tile_strip[28] += px7;
    tile_strip[29] <<= 4;
    tile_strip[29] += px7;
    tile_strip[30] <<= 4;
    tile_strip[30] += px7;
    tile_strip[31] <<= 4;
    tile_strip[31] += px7;
}

void loadTiles(u8 h_index_tile)
{
    // *** MACRO: CARGA EN VDP ***
    VDP_loadTileData((const u32 *) tile_strip, TILE_USERINDEX + h_index_tile, 1, DMA);
    VDP_loadTileData((const u32 *) (tile_strip + TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + SCREEN_SIZE_X_TILES, 1, DMA);
    VDP_loadTileData((const u32 *) (tile_strip + 2 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 2 * SCREEN_SIZE_X_TILES, 1, DMA);
    VDP_loadTileData((const u32 *) (tile_strip + 3 * TILE_SIZE_PX), TILE_USERINDEX + h_index_tile + 3 * SCREEN_SIZE_X_TILES, 1, DMA);
}
