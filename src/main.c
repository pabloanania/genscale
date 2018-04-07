#include <genesis.h>

// CONSTANTES
#define IMG_SIZE_SIDE           8
#define TILE_COLOR_QTY          16
#define TILE_SIZE_PX            8
#define SCAN_SHIFTING           1
#define SCREEN_SIZE_X           128
#define SCREEN_SIZE_Y           72
#define SCREEN_SIZE_X_TILES     16
#define SCREEN_SIZE_Y_TILES     9

// PROTOTIPOS
static void joyCallback(u16 joy, u16 changed, u16 state);
static void vIntCallback();
void drawCanvas();
void drawTileLine();
void getPixelFromImg();

// VARIABLES GLOBALES
u16 scan_x;
u16 scan_y;
u16 scan_step;
u16 draw_x_px;
u16 draw_y_px;
u16 draw_x_tile;
u16 draw_y_tile;
u16 current_tile_x;
u16 current_tile_y;
u32 tile_line_buffer[SCREEN_SIZE_X_TILES][TILE_SIZE_PX];
_Bool buttonAPressed = FALSE;
_Bool buttonBPressed = FALSE;
_Bool buttonCPressed = FALSE;
_Bool buttonStartPressed = FALSE;
u16 img_orig[8][8] = {
    {5,5,5,5,5,5,5,5},
    {5,9,2,2,2,2,2,5},
    {5,9,9,2,2,2,2,5},
    {5,9,9,9,2,2,2,5},
    {5,9,9,9,9,2,2,5},
    {5,9,9,9,9,9,2,5},
    {5,9,9,9,9,9,9,5},
    {5,5,5,5,5,5,5,5}
};

// VARIABLES GLOBALES DE PRUEBA
u16 tile_id;
u16 aux;
u16 aux_x;
u16 aux_y;
char integerConverter[5];
u8 img_pixel;
_Bool exit;
_Bool tile_line_exit;

int main()
{
    // Inicializa, desactiva interrupts y luego reactiva. Siempre hay que desactivar interrupts al llamar a VDP
    SYS_disableInts();
    VDP_setScreenWidth256();
    JOY_setEventHandler(&joyCallback);
    SYS_setVIntCallback(&vIntCallback);
    SYS_enableInts();

    while(TRUE)
    {
        VDP_waitVSync();
    }

    return 0;
}

static void vIntCallback(){
    drawCanvas();

    // Llena la screen con todos los tiles dibujados previamente
    VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL3, 0, 0, 0, TILE_USERINDEX), 0, 0, SCREEN_SIZE_X_TILES, SCREEN_SIZE_Y_TILES);

    uintToStr(scan_step, integerConverter, 5);
    VDP_drawTextBG(PLAN_A, integerConverter, 1, 0);
    VDP_showFPS(1);
}

static void joyCallback(u16 joy, u16 changed, u16 state)
{
    if (state & BUTTON_UP)
        scan_step+=1;

    if (state & BUTTON_DOWN)
        scan_step-=1;
    
    if (state & BUTTON_A)
        buttonAPressed=TRUE;
}

void drawCanvas(){
    tile_id = 0;
    draw_x_tile = 0;
    draw_y_tile = 0;
    draw_x_px = 0;
    draw_y_px = 0;
    exit = FALSE;

    while(!exit){
        drawTileLine();

        // Avanza en Y
        draw_y_tile += 1;
        tile_id += SCREEN_SIZE_X_TILES;
        if (draw_y_tile > SCREEN_SIZE_Y_TILES)
            exit = TRUE;
    }
}

void drawTileLine(){
    current_tile_x = 0;
    current_tile_y = 0;
    tile_line_exit = FALSE;

    while (!tile_line_exit){
        if (!buttonAPressed)
            tile_line_buffer[draw_x_tile][current_tile_y] = 0x12345678;
        else
            tile_line_buffer[draw_x_tile][current_tile_y] = 0x87654321;
        
        // Avanza en X de a un tile, Y de a un reglon de px
        draw_x_tile += 1;
        if (draw_x_tile == SCREEN_SIZE_X_TILES){
            draw_x_tile = 0;
            current_tile_y +=1;
        }

        if (current_tile_y == TILE_SIZE_PX)
            tile_line_exit = TRUE;
    }

    VDP_loadTileData((const u32*) tile_line_buffer, TILE_USERINDEX+tile_id, SCREEN_SIZE_X_TILES, 0);
}
