/**
 * periph.h
 * Defines various address bases for peripherals
 */
#ifndef AAA_PERIPH_H
#define AAA_PERIPH_H

#define PERIPH_BASE   0x20000000 /* base for all peripherals */
#define GPIO_BASE     (0x00200000 + PERIPH_BASE) /* base for GPIO */
#define GPIO_PUD      (0x00000094 + GPIO_BASE)
#define GPIO_PUDCLK0  (0x00000094 + GPIO_BASE)

#endif
