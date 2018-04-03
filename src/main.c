#include <genesis.h>

// CONSTANTES
#define TILE_SIZE       16
#define SCAN_SUB_SIZE   10
#define SCREEN_SIZE_X   128
#define SCREEN_SIZE_Y   128

// PROTOTIPOS
static void joyEvent(u16 joy, u16 changed, u16 state);

// VARIABLES GLOBALES
u16 scan_x;
u16 scan_y;
u16 scan_step;
u16 draw_x;
u16 draw_y;


int main()
{
    // Inicializa, desactiva interrupts y luego reactiva. OJO! Ver en sample\sprites que desactiva los interrupts al dibujar el fondo
    SYS_disableInts();
    VDP_setScreenWidth320();
    SYS_enableInts();
    JOY_setEventHandler(joyEvent);

    while(TRUE)
    {
        VDP_waitVSync();
    }

    return 0;
}

static void joyEvent(u16 joy, u16 changed, u16 state)
{
    // START button state changed
    if (changed & BUTTON_START)
    {

    }
}
