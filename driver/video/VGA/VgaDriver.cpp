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
        writeChar(startRow, startCol + i, text[i], color);
        i++;
    }
}

void VgaDriver::clearScreen() {
    volatile char* vga = (volatile char*)0xB8000;

    for (int row = 0; row < 25; row++) {
        for (int col = 0; col < 80; col++) {
            int index = (row * 80 + col) * 2;
            vga[index] = ' ';

        }
    }

}
    void VgaDriver::printCentered(const char* text, int row, char color) {
    int length = 0;
    while (text[length] != '\0') {
        length++;
    }

    // Startspalte berechnen
    int startCol = (80 - length) / 2;

    // Text ausgeben
    int i = 0;
    while (text[i] != '\0') {
        writeChar(row, startCol + i, text[i], color);
        i++;
    }
}




}
