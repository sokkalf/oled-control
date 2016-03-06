//
// Created by sokkalf on 3/6/16.
//
#include "oled-control.h"
void test_display() {
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "In A.D. 2101");
    set_cursor_position(1, 2);
    i2c_write_bytes(DATA, "War was beginning.");
    sleep(5);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Captain:");
    set_cursor_position(4, 2);
    i2c_write_bytes(DATA, "What happen?");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Mechanic:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "Somebody set up us");
    set_cursor_position(0, 3);
    i2c_write_bytes(DATA, "the bomb");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Operator:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "We get signal.");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Captain:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "WHAT !");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Operator:");
    set_cursor_position(1, 2);
    i2c_write_bytes(DATA, "Main screen");
    set_cursor_position(1, 3);
    i2c_write_bytes(DATA, "turn on.");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Captain:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "It's you !!");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Cats:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "How are you");
    set_cursor_position(1, 3);
    i2c_write_bytes(DATA, "gentlemen !!");
    sleep(2);
    clear_display();
    set_cursor_position(2, 1);
    i2c_write_bytes(DATA, "Cats:");
    set_cursor_position(0, 2);
    i2c_write_bytes(DATA, "All your base are");
    set_cursor_position(1, 3);
    i2c_write_bytes(DATA, "belong to us.");
}

int main() {
    configure_display("/dev/i2c-1", 0x3c);
    init_display();
    test_display();
    return 0;
}