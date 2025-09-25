#include "VgaDriver.hpp"

namespace vga_driver {

void VgaDriver::writeChar(int row, int col, char c, char color) {
    volatile char* vga = (volatile char*)0xB8000;
    int index = (row * 80 + col) * 2;
    vga[index] = c;
    vga[index + 1] = color;
}


void VgaDriver::putChar(int row, int col, char c, char color) {
    writeChar(row, col, c, color);
}

void VgaDriver::printString(int startRow, int startCol, const char* text, char color) {
    int i = 0;
    while (text[i] != '\0') {
        writeChar(startRow, startCol + i, text[i], color);  // << + i !
        i++;
    }
}




}
