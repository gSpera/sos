PERIPHERAL_BASE = 0x3F000000
PERIPHERAL_UART = PERIPHERAL_BASE + 0x201000
PERIPHERAL_UART_DR = PERIPHERAL_UART + 0x0

PERIPHERAL_AUX_UART_DATA = PERIPHERAL_BASE + 0x215040

.section .init
.global _start

.extern init_vector_table
_start:
    mov sp, #0x8000
    @ Initialize Vector Table
    bl init_vector_table
    bl kernel_start

    mov r0, #'X'
    bl write_hex
halt: b halt

.section .text
write_hex:
    push {lr}
    push {r0}
    lsr r0, #4
    bl write_nibble
    pop {r0}
    bl write_nibble
    pop {pc}

write_nibble:
    push {lr}
    and r0, #0xF
    cmp r0, #10
    addLT r0, #'0'
    addGE r0, #'A'-10
    bl serial_printch
    pop {pc}

serial_printch:
    ldr r1, =#PERIPHERAL_UART_DR
    str r0, [r1]
    bx lr
