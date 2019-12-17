#include <genesis.h>

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
static void joyCallback(u16 joy, u16 changed, u16 state);
static void vIntCallback();
void drawStrip(u8 h_index);
void scrollMap();

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
u8 tile_strip[TILE_SIZE_PX][SCREEN_SIZE_Y];
s16 planX = 0;
s16 planY = 0;

// VARIABLES GLOBALES DE PRUEBA

int main()
{
    // Inicializa, desactiva interrupts y luego reactiva. Siempre hay que desactivar interrupts al llamar a VDP
    SYS_disableInts();
    VDP_setScreenWidth256();
    JOY_setEventHandler(&joyCallback);
    SYS_setVIntCallback(&vIntCallback);
    SYS_enableInts();

    // Posiciona los tiles en donde corresponde
    VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL3, 0, 0, 0, TILE_USERINDEX), 0, 0, SCREEN_SIZE_X_TILES, SCREEN_SIZE_Y_TILES);

    while (TRUE)
    {
        VDP_waitVSync();
    }

    return 0;
}

static void vIntCallback()
{
    scrollMap();

    drawStrip(0);

    // Dibuja datos
    //uintToStr(scan_step, integerConverter, 5);
    //VDP_drawTextBG(PLAN_A, integerConverter, 1, 0);

    // Dibuja FPS
    VDP_showFPS(1);
}

static void joyCallback(u16 joy, u16 changed, u16 state)
{
    if (state & BUTTON_UP)
        planY = planY + 1;

    if (state & BUTTON_DOWN)
        planY = planY - 1;

    if (state & BUTTON_LEFT)
        planX = planX - 1;

    if (state & BUTTON_RIGHT)
        planX = planX + 1;
}

void scrollMap()
{
    VDP_setHorizontalScroll(PLAN_B, planX);
    VDP_setVerticalScroll(PLAN_B, planY);
}

void drawStrip(u8 h_index)
{
    // TEST: Esto agilizaria el procesamiento?
    u8 px0 = img_orig[h_index][0];
    u8 px1 = img_orig[h_index][1];
    u8 px2 = img_orig[h_index][2];
    u8 px3 = img_orig[h_index][3];
    u8 px4 = img_orig[h_index][4];
    u8 px5 = img_orig[h_index][5];
    u8 px6 = img_orig[h_index][6];
    u8 px7 = img_orig[h_index][7];

    // *** MACRO: DIBUJA STRIP ***
    tile_strip[h_index][0] = px0;
    tile_strip[h_index][1] = px0;
    tile_strip[h_index][2] = px0;
    tile_strip[h_index][3] = px0;
    tile_strip[h_index][4] = px0;
    tile_strip[h_index][5] = px0;
    tile_strip[h_index][6] = px0;
    tile_strip[h_index][7] = px0;

    tile_strip[h_index][8] = px2;
    tile_strip[h_index][9] = px2;
    tile_strip[h_index][10] = px2;
    tile_strip[h_index][11] = px2;
    tile_strip[h_index][12] = px2;
    tile_strip[h_index][13] = px2;
    tile_strip[h_index][14] = px2;
    tile_strip[h_index][15] = px2;

    tile_strip[h_index][16] = px4;
    tile_strip[h_index][17] = px4;
    tile_strip[h_index][18] = px4;
    tile_strip[h_index][19] = px4;
    tile_strip[h_index][20] = px4;
    tile_strip[h_index][21] = px4;
    tile_strip[h_index][22] = px4;
    tile_strip[h_index][23] = px4;

    tile_strip[h_index][24] = px6;
    tile_strip[h_index][25] = px6;
    tile_strip[h_index][26] = px6;
    tile_strip[h_index][27] = px6;
    tile_strip[h_index][28] = px6;
    tile_strip[h_index][29] = px6;
    tile_strip[h_index][30] = px6;
    tile_strip[h_index][31] = px6;

    // *** MACRO: CARGA EN VDP ***
    VDP_loadTileData((const u32 *)tile_strip[0][0], TILE_USERINDEX, 1, DMA);
    VDP_loadTileData((const u32 *)tile_strip[0][TILE_SIZE_PX], TILE_USERINDEX + SCREEN_SIZE_X_TILES, 1, DMA);
    VDP_loadTileData((const u32 *)tile_strip[0][2 * TILE_SIZE_PX], TILE_USERINDEX + 2 * SCREEN_SIZE_X_TILES, 1, DMA);
    VDP_loadTileData((const u32 *)tile_strip[0][3 * TILE_SIZE_PX], TILE_USERINDEX + 3 * SCREEN_SIZE_X_TILES, 1, DMA);
}