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

static VALUE init(VALUE self, VALUE i2cbus, VALUE i2caddress, VALUE orientation) {
    const char *bus = RSTRING_PTR(i2cbus);
    uint8_t a = NUM2UINT(i2caddress);
    uint8_t o = NUM2UINT(orientation);

    if(!configure_display(bus, a))
        rb_raise(rb_eRuntimeError, "can't detect display! Bus/address wrong?");

    if(!init_display(o))
        rb_raise(rb_eRuntimeError, "failure initializing display");

    return Qtrue;
}

static VALUE clear(VALUE self) {
    if(!clear_display())
        rb_raise(rb_eRuntimeError, "failure clearing display");

    return Qtrue;
}

static VALUE enable(VALUE self) {
    if(!display_enable()) {
        rb_raise(rb_eRuntimeError, "error enabling display");
    }

    return Qtrue;
}

static VALUE disable(VALUE self) {
    if(!display_disable()) {
        rb_raise(rb_eRuntimeError, "error disabling display");
    }

    return Qtrue;
}

static VALUE create_character(VALUE self, VALUE position, VALUE chardata) {
    uint8_t data[8];
    Check_Type(chardata, T_ARRAY);
    Check_Type(position, T_FIXNUM);

    uint8_t pos = NUM2UINT(position);
    int len = RARRAY_LEN(chardata);
    if((len > 8) || (len < 8)) {
        rb_raise(rb_eRuntimeError, "error: array must be exactly of size 8");
        return Qnil;
    } else {
        for(int i=0; i<8; i++)
            data[i] = rb_ary_entry(chardata, i);
    }
    if(!create_custom_character(pos, data)) {
        rb_raise(rb_eRuntimeError, "error creating custom character");
        return Qnil;
    }
    return Qtrue;
}

static VALUE send_command(VALUE self, VALUE command) {
    uint8_t  cmd = NUM2UINT(command);
    if(!send_cmd(cmd)) {
        rb_raise(rb_eRuntimeError, "error sending command");
    }

    return Qtrue;
}

static VALUE send_raw_command(VALUE self, VALUE command) {
    uint8_t  cmd = NUM2UINT(command);
    if(!send_raw_cmd(cmd)) {
        rb_raise(rb_eRuntimeError, "error sending raw command");
    }

    return Qtrue;
}

static VALUE set_contrast(VALUE self, VALUE level) {
    uint8_t val = NUM2UINT(level);
    if(!set_contrast_level(val)) {
        rb_raise(rb_eRuntimeError, "error setting contrast");
    }
    return Qtrue;
}

void Init_oled_control(void) {
    VALUE klass = rb_define_class("OLED", rb_cObject);

    rb_define_method(klass, "set_cursor", set_cursor, 2);
    rb_define_method(klass, "clear", clear, 0);
    rb_define_method(klass, "set_contrast", set_contrast, 1);
    rb_define_method(klass, "enable", enable, 0);
    rb_define_method(klass, "disable", disable, 0);
    rb_define_method(klass, "create_character", create_character, 2);
    rb_define_protected_method(klass, "send_command", send_command, 1);
    rb_define_protected_method(klass, "send_raw_command", send_raw_command, 1);
    rb_define_protected_method(klass, "write_string", write_string, 1);
    rb_define_protected_method(klass, "init", init, 3);
}