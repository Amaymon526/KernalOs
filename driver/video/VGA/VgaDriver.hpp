//
// Created by jeff on 25.09.25.
//

#ifndef VGADRIVER_H
#define VGADRIVER_H

namespace vga_driver {
    class VgaDriver {
    public:
        void putChar(int row, int col, char c, char color);
        void printString(int startRow, int startCol, const char* text, char color);
        void printCentered(const char* text, int row, char color);
        void clearScreen();

    private:
        void writeChar(int row, int col, char c, char color);
    };
}

#endif
