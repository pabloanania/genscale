#include <genesis.h>

// CONSTANTES
#define IMG_SIZE                16
#define TILE_SIZE_PX            8
#define SCAN_SUB_SIZE           10
#define SCREEN_SIZE_X           240
#define SCREEN_SIZE_Y           128
#define SCREEN_SIZE_X_TILES     30
#define SCREEN_SIZE_Y_TILES     16

// PROTOTIPOS
static void joyEvent(u16 joy, u16 changed, u16 state);
void fillScreen();

// VARIABLES GLOBALES
u16 scan_x;
u16 scan_y;
u16 scan_step;
u16 draw_x;
u16 draw_y;
u32 draw_tile[8];

// VARIABLES GLOBALES DE PRUEBA
u16 tile_id;
_Bool exit;

int main()
{
    // Inicializa, desactiva interrupts y luego reactiva. OJO! Ver en sample\sprites que desactiva los interrupts al dibujar el fondo
    SYS_disableInts();
    VDP_setScreenWidth256();
    JOY_setEventHandler(joyEvent);
    SYS_enableInts();

    while(TRUE)
    {
        fillScreen();
        VDP_showFPS(1);
        VDP_waitVSync();
    }

    return 0;
}

void fillScreen(){
    tile_id = 1;
    draw_x = 0;
    draw_y = 0;
    exit = FALSE;

    SYS_disableInts();
    while(!exit){
        // Redibuja el tile
        draw_tile[0] = 0x11111111;
        draw_tile[1] = 0x11000011;
        draw_tile[2] = 0x10100101;
        draw_tile[3] = 0x10011001;
        draw_tile[4] = 0x10011001;
        draw_tile[5] = 0x10100101;
        draw_tile[6] = 0x11000011;
        draw_tile[7] = 0x11111111;

        // Carga el tile en la posicion en VRAM
        VDP_loadTileData((const u32*) draw_tile, tile_id, 1, 1);

        // Escribe el tile en plano A en x e y correspondientes (medidos en tiles)
        VDP_setTileMapXY(PLAN_B, tile_id, draw_x, draw_y);

        draw_x +=1;
        if (draw_x > SCREEN_SIZE_X_TILES){
            draw_x = 0;
            draw_y += 1;
        }
            
        if (draw_y > SCREEN_SIZE_Y_TILES)
            exit = TRUE;

        tile_id+=1;
    }
    SYS_enableInts();
}

static void joyEvent(u16 joy, u16 changed, u16 state)
{
    if (changed & BUTTON_UP)
        scan_step+=1;

    if (changed & BUTTON_DOWN)
        scan_step-=1;
}
