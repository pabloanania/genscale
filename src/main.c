#include <genesis.h>

// CONSTANTES
#define IMG_SIZE                16
#define TILE_SIZE_PX            8
#define SCAN_SUB_SIZE           10
#define SCREEN_SIZE_X           256
#define SCREEN_SIZE_Y           144
#define SCREEN_SIZE_X_TILES     32
#define SCREEN_SIZE_Y_TILES     18

// PROTOTIPOS
static void joyCallback(u16 joy, u16 changed, u16 state);
static void vIntCallback();
void drawTile();

// VARIABLES GLOBALES
u16 scan_x;
u16 scan_y;
u16 scan_step;
u16 draw_x;
u16 draw_y;
u32 draw_tile[8];
_Bool buttonAPressed = FALSE;
_Bool buttonBPressed = FALSE;
_Bool buttonCPressed = FALSE;
_Bool buttonStartPressed = FALSE;

// VARIABLES GLOBALES DE PRUEBA
u16 tile_id;
_Bool exit;

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
    tile_id = 0;
    draw_x = 0;
    draw_y = 0;
    exit = FALSE;

    while(!exit){
        // Redibuja el tile
        drawTile();

        // Carga el tile en la posicion en VRAM
        VDP_loadTileData((const u32*) draw_tile, TILE_USERINDEX+tile_id, 1, 0);

        // Avanza en X y en Y
        draw_x +=1;
        if (draw_x > SCREEN_SIZE_X_TILES){
            draw_x = 0;
            draw_y += 1;
        }
            
        if (draw_y > SCREEN_SIZE_Y_TILES)
            exit = TRUE;

        tile_id+=1;
    }

    // Escribe el tile en plano A en x e y correspondientes (medidos en tiles)
    //VDP_setTileMapXY(PLAN_B, tile_id, draw_x, draw_y);
    // Llena la screen con todos los tiles dibujados previamente
    VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_USERINDEX), 0, 0, SCREEN_SIZE_X_TILES, SCREEN_SIZE_Y_TILES);
    
    VDP_showFPS(1);
}

static void joyCallback(u16 joy, u16 changed, u16 state)
{
    if (changed & BUTTON_UP)
        scan_step+=1;

    if (changed & BUTTON_DOWN)
        scan_step-=1;
    
    if (changed & BUTTON_A)
        buttonAPressed=TRUE;
    else
        buttonAPressed=FALSE;
}

void drawTile(){
    if (!buttonAPressed && tile_id%2==0){
        draw_tile[0] = 0x11111111;
        draw_tile[1] = 0x11000011;
        draw_tile[2] = 0x10100101;
        draw_tile[3] = 0x10011001;
        draw_tile[4] = 0x10011001;
        draw_tile[5] = 0x10100101;
        draw_tile[6] = 0x11000011;
        draw_tile[7] = 0x11111111;
    }else if (!buttonAPressed && tile_id%2!=0){
        draw_tile[0] = 0x00000000;
        draw_tile[1] = 0x01111110;
        draw_tile[2] = 0x01111110;
        draw_tile[3] = 0x01111110;
        draw_tile[4] = 0x01111110;
        draw_tile[5] = 0x01111110;
        draw_tile[6] = 0x01111110;
        draw_tile[7] = 0x00000000; 
    }else if (buttonAPressed && tile_id%2==0){
        draw_tile[0] = 0x00000000;
        draw_tile[1] = 0x01111110;
        draw_tile[2] = 0x01111110;
        draw_tile[3] = 0x01111110;
        draw_tile[4] = 0x01111110;
        draw_tile[5] = 0x01111110;
        draw_tile[6] = 0x01111110;
        draw_tile[7] = 0x00000000; 
    }else if (buttonAPressed && tile_id%2!=0){
        draw_tile[0] = 0x11111111;
        draw_tile[1] = 0x11000011;
        draw_tile[2] = 0x10100101;
        draw_tile[3] = 0x10011001;
        draw_tile[4] = 0x10011001;
        draw_tile[5] = 0x10100101;
        draw_tile[6] = 0x11000011;
        draw_tile[7] = 0x11111111;
    }
}
