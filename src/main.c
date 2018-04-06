#include <genesis.h>

// CONSTANTES
#define IMG_SIZE_SIDE           16
#define IMG_SIZE_TOTAL_PX       256
#define TILE_COLOR_QTY          16
#define TILE_SIZE_PX            8
#define SCAN_SUB_SIZE           10
#define SCREEN_SIZE_X           256
#define SCREEN_SIZE_Y           144
#define SCREEN_SIZE_X_TILES     32
#define SCREEN_SIZE_Y_TILES     18

// PROTOTIPOS
static void joyCallback(u16 joy, u16 changed, u16 state);
static void vIntCallback();
void drawCanvas();
void drawTile();
void getPixelFromImg();

// VARIABLES GLOBALES
u16 scan_x;
u16 scan_y;
u16 scan_step;
u16 draw_x_tile;
u16 draw_y_tile;
u32 draw_tile[8];
_Bool buttonAPressed = FALSE;
_Bool buttonBPressed = FALSE;
_Bool buttonCPressed = FALSE;
_Bool buttonStartPressed = FALSE;
unsigned char img_orig[256] = {
    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    5,5,2,2,2,2,2,2,2,2,2,2,2,2,5,5,
    5,2,5,2,2,2,2,2,2,2,2,2,2,5,5,5,
    5,2,2,5,2,2,2,2,2,2,2,2,5,5,5,5,
    5,2,2,2,5,2,2,2,2,2,2,5,5,5,5,5,
    5,2,2,2,2,5,2,2,2,2,5,5,5,5,5,5,
    5,2,2,2,2,2,5,2,2,5,5,5,5,5,5,5,
    5,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,
    5,5,5,5,5,5,5,5,2,2,2,2,2,2,2,5,
    5,5,5,5,5,5,5,2,2,5,2,2,2,2,2,5,
    5,5,5,5,5,5,2,2,2,2,5,2,2,2,2,5,
    5,5,5,5,5,2,2,2,2,2,2,5,2,2,2,5,
    5,5,5,5,2,2,2,2,2,2,2,2,5,2,2,5,
    5,5,5,2,2,2,2,2,2,2,2,2,2,5,2,5,
    5,5,2,2,2,2,2,2,2,2,2,2,2,2,5,5,
    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};

// VARIABLES GLOBALES DE PRUEBA
u16 tile_id;
u16 aux;
u16 aux_x;
u16 aux_y;
char integerConverter[5];
char img_pixel;
_Bool exit;
_Bool tile_draw_exit;

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
    VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL1, 0, 0, 1, TILE_USERINDEX), 0, 0, SCREEN_SIZE_X_TILES, SCREEN_SIZE_Y_TILES);

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
    else
        buttonAPressed=FALSE;
}

void drawCanvas(){
    tile_id = 0;
    draw_x_tile = 0;
    draw_y_tile = 0;
    exit = FALSE;
    tile_draw_exit = FALSE;

    while(!exit){
        drawTile();

        // Avanza en X y en Y
        draw_x_tile += 1;
        if (draw_x_tile > SCREEN_SIZE_X_TILES){
            draw_x_tile = 0;
            draw_y_tile += 1;
        }
            
        if (draw_y_tile > SCREEN_SIZE_Y_TILES)
            exit = TRUE;

        tile_id += 1;
    }
}

void drawTile(){
    tile_draw_exit = FALSE;
    scan_x = 0;
    scan_y = 0;

    while(!tile_draw_exit){
        getPixelFromImg();

        draw_tile[scan_y] += TILE_COLOR_QTY * scan_x + img_pixel;

        scan_x += 1;
        if (scan_x >= TILE_SIZE_PX){
            scan_x = 0;
            scan_y += 1;
        }

        if (scan_y >= TILE_SIZE_PX)
            tile_draw_exit = TRUE;
    }

    VDP_loadTileData((const u32*) draw_tile, TILE_USERINDEX+tile_id, 1, 0);
}

void getPixelFromImg(){
    aux_x = scan_x * scan_step / SCAN_SUB_SIZE;
    aux_y = scan_y * scan_step / SCAN_SUB_SIZE;
    aux = aux_x + aux_y * IMG_SIZE_SIDE;
    img_pixel = '0';
    
    if (aux < IMG_SIZE_TOTAL_PX)
        img_pixel = img_orig[aux];
}
