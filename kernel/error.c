

#include <stdint.h>
#include "carl_error.h"
#include "sys.h"

// These must be provided by your bootloader or graphics subsystem
extern uint32_t* fb_addr;     // framebuffer base address
extern uint32_t  fb_width;    // screen width in pixels
extern uint32_t  fb_height;   // screen height in pixels
extern uint32_t  fb_pitch;    // bytes per row
extern uint32_t  fb_bpp;      // bits per pixel

// Simple pixel writer (ARGB)
static inline void gsod_putpixel(uint32_t x, uint32_t y, uint32_t color)
{
    uint32_t* row = (uint32_t*)((uint8_t*)fb_addr + y * fb_pitch);
    row[x] = color;
}

// Fill entire screen with green
static void gsod_fill_green(void)
{
    uint32_t green = 0xFF00FF00; // ARGB: opaque bright green

    for (uint32_t y = 0; y < fb_height; y++) {
        uint32_t* row = (uint32_t*)((uint8_t*)fb_addr + y * fb_pitch);
        for (uint32_t x = 0; x < fb_width; x++) {
            row[x] = green;
        }
    }
}

// Draw simple text using DebugPrint (top-left corner)
static void gsod_draw_text(const char* msg)
{
    // You can replace this with a real font renderer later.
    c_DebugPrint(":(\n");
    c_DebugPrint("Carl has found a problem and needs to recover from the damage.\n");
    c_DebugPrint("Reason: ");
    c_DebugPrint(msg);
    c_DebugPrint("\nSystem halted.\n");
}

void c_gsod(const char* message)
{
    // Paint the entire screen green
    gsod_fill_green();

    // Print text (serial/log/debug overlay)
    gsod_draw_text(message);

    // Halt the CPU forever
    for (;;) {
        __asm__ volatile ("hlt");
    }
}
