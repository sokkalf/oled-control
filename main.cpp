#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

const char* i2c_bus;
int i2c_bus_handle;
uint8_t oled_address;
bool configured = false;

bool i2c_write_byte(uint8_t reg, uint8_t data) {
    char buf[2];
    buf[0] = reg;
    buf[1] = data;
    if(write(i2c_bus_handle, buf, 2) != 2) {
        cout << "Write to device failed\n";
        return false;
    }
    return true;
}

bool configure_display(const char* bus, uint8_t address) {
    i2c_bus = bus;
    oled_address = address;
    if((i2c_bus_handle = open(i2c_bus, O_RDWR)) < 0) {
        return false;
    } else {
        cout << "Bus access OK\n";
    }
    if (ioctl(i2c_bus_handle, I2C_SLAVE, oled_address) < 0) {
        return false;
    } else {
        cout << "Device access OK\n";
    }
    configured = true;
    return configured;
}

bool init_display() {
    i2c_write_byte(0x80, 0x2a); // **** Set "RE"=1<--->00101010B
    i2c_write_byte(0x80, 0x71);
    i2c_write_byte(0x80, 0x5c);
    i2c_write_byte(0x80, 0x28);
    i2c_write_byte(0x80, 0x08);
    i2c_write_byte(0x80, 0x2a);
    i2c_write_byte(0x80, 0x79);
    i2c_write_byte(0x80, 0xd5);
    i2c_write_byte(0x80, 0x70);
    i2c_write_byte(0x80, 0x78);
    i2c_write_byte(0x80, 0x08);
    i2c_write_byte(0x80, 0x06);
    i2c_write_byte(0x80, 0x2a);
    i2c_write_byte(0x80, 0x79);
    i2c_write_byte(0x80, 0x72);
    i2c_write_byte(0x80, 0x00);
    i2c_write_byte(0x80, 0xda);
    i2c_write_byte(0x80, 0x10);
    i2c_write_byte(0x80, 0x81);
    i2c_write_byte(0x80, 0x50);
    i2c_write_byte(0x80, 0xdb);
    i2c_write_byte(0x80, 0x30);
    i2c_write_byte(0x80, 0xdc);
    i2c_write_byte(0x80, 0x03);
    i2c_write_byte(0x80, 0x78);
    i2c_write_byte(0x80, 0x28);
    i2c_write_byte(0x80, 0x2a);
    i2c_write_byte(0x80, 0x06);
    i2c_write_byte(0x80, 0x08);
    i2c_write_byte(0x80, 0x28);
    i2c_write_byte(0x80, 0x01);
    i2c_write_byte(0x80, 0x80);
    i2c_write_byte(0x80, 0x0c);
}

int main() {
    configure_display("/dev/i2c-1", 0x3c);
    init_display();
    i2c_write_byte(0x40, '?');
    return 0;
}