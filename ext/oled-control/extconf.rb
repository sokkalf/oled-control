require 'mkmf'

have_library('i2c-dev')

create_makefile('oled-control/oled_control')
