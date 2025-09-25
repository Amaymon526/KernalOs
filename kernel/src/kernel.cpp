#include "header/kernel.h"
#include "/home/jeff/CLionProjects/KernalOs/driver/video/VGA/VgaDriver.hpp" // is richtig oarsch


extern "C" void kernel_main() {
    vga_driver::VgaDriver vga;


  	vga.putChar(1, 0, 'H', 0x0F);

    vga.printString(2, 0, "Hello_ World!", 0x02);

    while (1) {
        asm("hlt");
    }
    while (1) { asm("hlt"); }
}
