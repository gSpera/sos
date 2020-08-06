void serial_printch(char ch) {
    volatile int *serial = (volatile int *)0x3F201000;
    volatile int *flag = (volatile int *)0x3F201018;
    while ((*flag & (1 << 5)) != 0)
        ;
    (*serial) = ch;
}
void serial_printstr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) serial_printch(str[i]);
}

char serial_getch() {
    volatile int *serial = (volatile int *)0x3F201000;
    volatile int *flag = (volatile int *)0x3F201018;
    while ((*flag & (1 << 4)) != 0)
        ;
    return *serial;
}

int read_int32() {
    int value = 0;
    for (int i = 0; i < 4 * 2; i++) {
        char ch;
        int v;
    get_char:
        ch = serial_getch();
        switch (ch) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                v = ch - '0';
                value = value << 4 | v;
                break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                v = ch - 'A' + 10;
                value = value << 4 | v;
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                v = ch - 'a' + 10;
                value = value << 4 | v;
                break;
            default:
                goto get_char;
        }
    }

    return value;
}

void serial_print_int32(int v) {
    for (int i = 0; i < 4 * 2; i++) {
        int nibble = (v >> 32 - 4) & 0x0F;
        if (nibble < 10) {
            serial_printch(nibble + '0');
        } else {
            serial_printch(nibble + 'a' - 10);
        }
        v <<= 4;
    }
}

void r() {
    volatile int *a = (volatile int *)read_int32();
    a = (volatile int *)((int)a & ~0x0F);
    serial_print_int32((int)a);
    serial_printstr(": ");
    serial_print_int32(*a);
}

void serial_getbuff(char *buff, int size) {
    int i;
    for (i = 0; i < size; i++) {
        buff[i] = serial_getch();
        if (buff[i] == '\n') break;
    }
    buff[i] = 0;
}

int cmpstrspace(char *a, char *b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0') return 0;
    }

    return 1;
}

void kernel_main(int r0, int r1, char *r2) {
    serial_printstr("Kernel Main\n");
    serial_printstr("Write: ");
    serial_printstr("r0: ");
    serial_print_int32(r0);
    serial_printch('\n');
    serial_printstr("r1: ");
    serial_print_int32(r1);
    serial_printch('\n');
    serial_printstr("r2: ");
    serial_print_int32((int)r2);
    serial_printch('\n');
    for (int i = 0; r2[i] != '\0'; i++) {
        serial_print_int32(i);
        serial_printstr(": ");
        serial_print_int32((int)r2);
        serial_printch('\n');
    }
    char cmd[64];
    for (int i = 0;; i++) {
        serial_printstr("SuperShell: ");
        serial_getbuff(cmd, 64);
        if (cmpstrspace("r", cmd, 1)) {
            serial_printstr("\nRead\n");
            r();
        } else {
            serial_printstr("Unkown command");
        }
        serial_printch('\n');
    }
}
