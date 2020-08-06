void debug_putc(char ch) {
    volatile int *serial = (volatile int *)0x3F201000;
    volatile int *flag = (volatile int *)0x3F201018;
    while ((*flag & (1 << 5)) != 0)
        ;
    (*serial) = ch;
}
void debug_puts(char *str) {
    for (int i = 0; str[i] != '\0'; i++) debug_putc(str[i]);
}

char serial_getch() {
    volatile int *serial = (volatile int *)0x3F201000;
    volatile int *flag = (volatile int *)0x3F201018;
    while ((*flag & (1 << 4)) != 0)
        ;
    return *serial;
}

void debug_put32(unsigned int v) {
    for (int i = 0; i < 4 * 2; i++) {
        int nibble = (v >> 32 - 4) & 0x0F;
        if (nibble < 10) {
            debug_putc(nibble + '0');
        } else {
            debug_putc(nibble + 'a' - 10);
        }
        v <<= 4;
    }
}
