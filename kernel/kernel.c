#include "../drivers/screen.h"
#include "../libc/cast.h"

void main()
{
    clear_screen();
    int i = 0;
    for (i = 0; i < 25; i++) {
        char str[255];
        itoa(i+1, str);
        kprint_at(str, i, 0);
    }
    kprint("\nAnd with this text is a really long text. the kernel will scroll, and row 1 will disappear!");
}