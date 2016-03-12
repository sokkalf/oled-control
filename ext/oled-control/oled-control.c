#include <stdio.h>
#include <stdlib.h>
#include "oled-control.h"

const char* i2c_bus;
int i2c_bus_handle;
uint8_t oled_address;
int configured = FALSE;

int i2c_write_byte(uint8_t reg, uint8_t data) {
    char buf[2];
    buf[0] = reg;
    buf[1] = data;
    if(write(i2c_bus_handle, buf, 2) != 2) {
        fprintf(stderr, "Write to device failed\n");
        return FALSE;
    }
    return TRUE;
}

int i2c_write_bytes(uint8_t reg, const char* data) {
    return i2c_write_n_bytes(reg, data, strlen(data));
}

int i2c_write_n_bytes(uint8_t reg, const char* data, size_t length) {
    size_t len = sizeof(uint8_t) + length;
    char *buf = calloc(1, len);
    memcpy(&buf[0], &reg, 1);
    memcpy(&buf[1], data, length);

    if(write(i2c_bus_handle, buf, len) != len) {
        fprintf(stderr, "Write to device failed\n");
        free(buf);
        return FALSE;
    }
    free(buf);
    return TRUE;
}

int set_cursor_position(uint8_t col, uint8_t row) {
    if((col >= DISPLAY_MAX_COLS) || (row >= DISPLAY_MAX_ROWS))
        return FALSE;

    int line_offsets[] = {
            0x00,  // start of line 1
            0x20,
            0x40,
            0x60   // start of line 4
    };
    return i2c_write_byte(CMD, 0x80 | (col + line_offsets[row]));
}

int clear_display() {
    return i2c_write_byte(CMD, 0x01);
}

int set_contrast_level(uint8_t level) {
    return i2c_write_byte(CMD, 0x2A) &&
           i2c_write_byte(CMD, 0x79) &&
           i2c_write_byte(CMD, 0x81) &&
           i2c_write_byte(CMD, level) &&
           i2c_write_byte(CMD, 0x78) &&
           i2c_write_byte(CMD, 0x28);
}

int display_enable() {
    return i2c_write_byte(CMD, 0x0C);
}

int display_disable() {
    return i2c_write_byte(CMD, 0x08);
}

int send_cmd(uint8_t cmd) {
    return i2c_write_byte(CMD, 0x2A) &&
           i2c_write_byte(CMD, cmd) &&
           i2c_write_byte(CMD, 0x28);
}

int send_raw_cmd(uint8_t cmd) {
    return i2c_write_byte(CMD, cmd);
}

int configure_display(const char* bus, uint8_t address) {
    i2c_bus = bus;
    oled_address = address;
    if((i2c_bus_handle = open(i2c_bus, O_RDWR)) < 0) {
        return FALSE;
    }
    if (ioctl(i2c_bus_handle, I2C_SLAVE, oled_address) < 0) {
        return FALSE;
    }
    configured = TRUE;
    return configured;
}

int create_custom_character(uint8_t pos, uint8_t map[]) {
    pos &= 0x7;
    if(!i2c_write_byte(CMD, 0x40 | (pos << 3)))
        return FALSE;

    usleep(30);
    int result;
    for (int i=0; i<8; i++) {
        result = i2c_write_byte(DATA, map[i] >> 1);
        if(!result)
            break;
        usleep(40);
    }
    return result;
}

int init_display(uint8_t orientation) {
    if(!configured)
        return FALSE;

    return i2c_write_byte(CMD, 0x2a) && // **** Set "RE"=1<--->00101010B
    i2c_write_byte(CMD, 0x71) &&
    i2c_write_byte(CMD, 0x5c) &&
    i2c_write_byte(CMD, 0x28) &&
    i2c_write_byte(CMD, 0x08) && // display off
    i2c_write_byte(CMD, 0x2a) &&
    i2c_write_byte(CMD, 0x79) &&
    i2c_write_byte(CMD, 0xd5) &&
    i2c_write_byte(CMD, 0x70) &&
    i2c_write_byte(CMD, 0x78) &&
    i2c_write_byte(CMD, 0x09) && // this is a 4 line display. Set to 0x08 for a 2 line display.
    i2c_write_byte(CMD, 0x06) &&
    i2c_write_byte(CMD, 0x72) &&
    i2c_write_byte(DATA, 0x00) &&
    i2c_write_byte(CMD, 0x2a) &&
    i2c_write_byte(CMD, 0x79) &&
    i2c_write_byte(CMD, 0xda) &&
    i2c_write_byte(CMD, 0x10) &&
    i2c_write_byte(CMD, 0xdc) &&
    i2c_write_byte(CMD, 0x00) &&
    i2c_write_byte(CMD, 0x81) && // set contrast
    i2c_write_byte(CMD, 0x50) && // contrast level
    i2c_write_byte(CMD, 0xdb) &&
    i2c_write_byte(CMD, 0x30) &&
    i2c_write_byte(CMD, 0xdc) &&
    i2c_write_byte(CMD, 0x03) &&
    i2c_write_byte(CMD, 0x78) &&
    i2c_write_byte(CMD, 0x28) &&
    i2c_write_byte(CMD, 0x2a) &&
    i2c_write_byte(CMD, orientation) &&
    i2c_write_byte(CMD, 0x28) &&
    i2c_write_byte(CMD, 0x01) &&
    i2c_write_byte(CMD, 0x80) &&
    display_enable() &&
    !usleep(1000); // spec says to hold on for 0.1 secs before data
    // usleep returns 0, ergo FALSE, on success, so invert it
}


