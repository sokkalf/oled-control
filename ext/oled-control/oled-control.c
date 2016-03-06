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
    int len = sizeof(reg) + strlen(data);
    void *buf = calloc(1, len);
    memcpy(buf, &reg, 1);
    strcat((char*)buf, data);
    if(write(i2c_bus_handle, buf, len) != len) {
        fprintf(stderr, "Write to device failed\n");
        free(buf);
        return FALSE;
    }
    free(buf);
    return TRUE;
}

int set_cursor_position(uint8_t col, uint8_t row) {
    if((col > DISPLAY_MAX_COLS) || (row > DISPLAY_MAX_ROWS))
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

int init_display() {
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
    i2c_write_byte(CMD, 0x06) &&
    i2c_write_byte(CMD, 0x28) &&
    i2c_write_byte(CMD, 0x01) &&
    i2c_write_byte(CMD, 0x80) &&
    i2c_write_byte(CMD, 0x0c) &&
    !usleep(1000); // spec says to hold on for 0.1 secs before data
    // usleep returns 0, ergo FALSE, on success, so invert it
}

