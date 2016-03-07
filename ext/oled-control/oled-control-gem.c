//
// Created by sokkalf on 3/6/16.
//

#include "oled-control.h"
#include <ruby.h>


static VALUE set_cursor(VALUE self, VALUE col, VALUE row) {
    uint8_t c = NUM2UINT(col);
    uint8_t r = NUM2UINT(row);

    if(!set_cursor_position(c, r))
        rb_raise(rb_eRuntimeError, "unable to set cursor position");

    return Qtrue;
}

static VALUE write_string(VALUE self, VALUE str) {
    const char *s = RSTRING_PTR(str);
    if(!i2c_write_bytes(DATA, s))
        rb_raise(rb_eRuntimeError, "unable to write string to display");

    return Qtrue;
}

static VALUE init(VALUE self, VALUE i2cbus, VALUE i2caddress) {
    const char *bus = RSTRING_PTR(i2cbus);
    uint8_t a = NUM2UINT(i2caddress);

    if(!configure_display(bus, a))
        rb_raise(rb_eRuntimeError, "can't detect display! Bus/address wrong?");

    if(!init_display())
        rb_raise(rb_eRuntimeError, "failure initializing display");

    return Qtrue;
}

static VALUE clear(VALUE self) {
    if(!clear_display())
        rb_raise(rb_eRuntimeError, "failure clearing display");

    return Qtrue;
}

void Init_oled_control(void) {
    VALUE klass = rb_define_class("OLED", rb_cObject);

    rb_define_method(klass, "set_cursor", set_cursor, 2);
    rb_define_method(klass, "clear", clear, 0);
    rb_define_protected_method(klass, "write_string", write_string, 1);
    rb_define_protected_method(klass, "init", init, 2);
}