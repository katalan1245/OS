#include "keyboard.h"
#include "screen.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../libc/string.h"
#include "../libc/unused.h"
#include "../kernel/kernel.h"

static char key_buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs)
{
    uint8 scancode = port_byte_in(KEYBOARD_DATA_PORT);

    if (scancode > SC_MAX)
        return;
    if (scancode == BACKSPACE_SC)
    {
        if(key_buffer[0] == '\0')
            return;
        backspace(key_buffer);
        kprint_backspace();
    }
    else if (scancode == ENTER_SC)
    {
        kprint("\n");
        user_input(key_buffer); /* kernel controlled function */
        key_buffer[0] = '\0';
    }
    else
    {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard()
{
    add_interrupt_handler(IRQ1, keyboard_callback);
}
