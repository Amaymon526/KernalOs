#include "header/kernel.h"

extern "C" void kernel_main() {
    const char *msg = "Hello World from my kernel!";
    char *vga = (char*)0xb8000;  // VGA Text Mode Speicher
    int i = 0;
    while (msg[i] != '\0') {
        vga[i*2] = msg[i];      // Zeichen
        vga[i*2+1] = 0x07;      // Farbe (hellgrau auf schwarz)
        i++;
    }

    // CPU anhalten
    while (1) { asm("hlt"); }
}
