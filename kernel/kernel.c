#include "../drivers/screen.h"

void main()
{
    clear_screen();
    kprint("OSDEV!");
    // kprint("First Cursor Test");
    // kprint_at("X", 15, 0);
    // kprint_at("Line Overflowing", 10, 72);
    // kprint_at("Line\nBreak", 5, 0);
    // kprint_at("What will happen if there is no more space?", 24, 60);
}