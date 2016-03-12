//
// Created by sokkalf on 3/6/16.
//

#ifndef OLED_CONTROL_OLED_CONTROL_H
#define OLED_CONTROL_OLED_CONTROL_H

#include <stddef.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define CMD 0x80
#define DATA 0x40

#define DISPLAY_MAX_ROWS 4
#define DISPLAY_MAX_COLS 20

int i2c_write_byte(uint8_t reg, uint8_t data);
int i2c_write_bytes(uint8_t reg, const char* data);
int set_cursor_position(uint8_t col, uint8_t row);
int clear_display();
int set_contrast_level(uint8_t level);
int display_enable();
int display_disable();
int send_cmd(uint8_t cmd);
int send_raw_cmd(uint8_t cmd);
int create_custom_character(uint8_t pos, uint8_t map[]);
int configure_display(const char* bus, uint8_t address);
int init_display(uint8_t orientation);

#endif //OLED_CONTROL_OLED_CONTROL_H
