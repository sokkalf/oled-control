require 'mkmf'

have_library('i2c-dev')

$CFLAGS += " -std=c99"

create_makefile('oled-control/oled_control')
