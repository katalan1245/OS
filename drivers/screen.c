#include "screen.h"
#include "ports.h"

/* declaration of private functions */
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char character, int row, int col, char attribute_byte);
int get_offset(int row, int col);
int get_offset_row(int offset);
int get_offset_col(int offset);

/***********************************************************************************************
 * Public Kernel API functions                                                                 *
 ***********************************************************************************************/

/**
 * kernel print function 
 * print the message on tspecific location
 */
void kprint_at(char *message, int row, int col)
{
    int offset;
    if (row >= 0 && col >= 0)
    {
        offset = get_offset(row, col);
    }
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i])
    {
        offset = print_char(message[i++], row, col, generate_text_color(BLACK, WHITE));
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

/**
 * kernel print function
 * print the message on the cursor location
 */
void kprint(char *message)
{
    kprint_at(message, -1, -1);
}

/**
 * clear the screen
 */
void clear_screen()
{
    int i, j;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            print_char(' ', i, j, generate_text_color(BLACK, WHITE));
        }
    }
    set_cursor_offset(get_offset(0, 0));
}

/**
 * high 4-bits are for the background color
 * low 4-bits are for the foreground color
 */
unsigned char generate_text_color(int background_color, int foreground_color) {
    return (background_color << 4) + foreground_color;
}

/**
 * print char function, directly accessing video graphics array in memory
 * if col and row are negative, print at the current cursor location
 * if attr is zero print white on black as default
 * set the video cursor to the returned offset
 */
int print_char(char character, int row, int col, char attribute_byte)
{
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    if (!attribute_byte)
    {
        attribute_byte = generate_text_color(WHITE, BLACK);
    }

    /* if coordinates greater than the max value print red E at the end of the screen*/
    if (row >= MAX_ROWS || col >= MAX_COLS)
    {
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
        vidmem[2 * (MAX_COLS) * (MAX_ROWS)-1] = generate_text_color(WHITE, RED);
        return get_offset(row, col);
    }

    int offset;
    if (row >= 0 && col >= 0)
    {
        offset = get_offset(row, col);
    }
    else
    {
        offset = get_cursor_offset();
    }

    if (character == '\n')
    {
        int rows = offset / (2 * MAX_COLS);
        offset = get_offset(rows, 79);
    }
    else
    {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }
    offset += 2;
    //offset = handle_scrolling(offset);
    set_cursor_offset(offset);
    return offset;
}

/* Use the VGA ports to get the current cursor position
 * 1. Ask for high byte of the cursor offset (data 14)
 * 2. Ask for low byte (data 15)
 */
int get_cursor_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* high byte */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* character cell size is 2 bytes */
}

/**
 * similar to get_cursor_offset, however this time we will write the data
 */
void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

/**
 * get the memory offset by row, col of the vga array
 */
int get_offset(int row, int col) { return 2 * (row * MAX_COLS + col); }

/**
 * get the offset row
 */
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }

/**
 * get the offset col
 */
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }