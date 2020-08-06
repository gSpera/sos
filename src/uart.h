#ifndef H_UART
#define H_UART

typedef unsigned int uint32_t;

#ifdef __GNUC__
#define PACKED __attribute__((packed))
#else
#warning Not using GCC cannot define PACKED
#define PACKED
#endif

struct uart_pl011 {
    uint32_t data;    // 0x00
    uint32_t rsrecr;  // 0x04
    uint32_t padding0__[(0x18 - 0x4) / 4];
    uint32_t fr;  // 0x18
    uint32_t padding1__[(0x20 - 0x18) / 4];
    uint32_t ilpr;   // 0x20
    uint32_t ibrd;   // 0x24
    uint32_t fbrd;   // 0x28
    uint32_t lcrh;   // 0x2c
    uint32_t cr;     // 0x30
    uint32_t ifls;   // 0x34
    uint32_t imsc;   // 0x38
    uint32_t ris;    // 0x3c
    uint32_t mis;    // 0x40
    uint32_t icr;    // 0x44
    uint32_t dmacr;  // 0x48
    uint32_t padding2__[(0x80 - 0x2c) / 4];
    uint32_t itcr;  // 0x80
    uint32_t itip;  // 0x84
    uint32_t itop;  // 0x88
    uint32_t tdr;   // 0x8c
};

#endif