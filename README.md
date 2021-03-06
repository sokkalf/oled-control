# oled-control
[![Gem Version](https://badge.fury.io/rb/oled-control.svg)](https://badge.fury.io/rb/oled-control)

Ruby Gem for SSD1311 based 20x4 OLED display from [wide.hk](http://www.wide.hk).
Should theoretically work for 20x2 and 16x2 as well, with some modifications.

## Usage
Add to your Gemfile:
`gem 'oled-control'`, and `bundle install`

#### Example code
```ruby
require 'oled-control/oled'

oled = OLED.new
oled.clear # clear display
oled.set_cursor(0, 0) # set cursor position to column 0, row 0
oled.write('Hello, world!')
```
![hello world](../master/doc/helloworld.jpg)

Should you be so unlucky as to mount the display upside-down, do not despair!
Just `oled.flip` to turn things around again.


#### Configure I2C bus and address
The library defaults to I2C-bus `/dev/i2c-1` and I2C device address `0x3C`
If you require another bus/address, you can use
```ruby
OLED.new('/dev/i2c-2', 0x45)
```

## Character set
To utilize the various supported characters (I use the ROM A set on the SSD1311), the library will first do a conversion to ISO-8859-1, and then do character replacement to make the characters match up.

See the `@character_conversion` variable in [this file](../master/lib/oled-control/oled.rb) and the [SSD1311 datasheet](http://www.midascomponents.co.uk/pdf/ssd1311.pdf) for reference.

### Custom characters
It is possible to create eight custom characters numbered from 0 to 7. Example:
```ruby
oled.create_character(0, [0b11000,
                          0b11100,
                          0b11110,
                          0b11111,
                          0b11110,
                          0b11100,
                          0b11000,
                          0b00000])
                             
oled.write("My custom char: \x00")
```

## Testing without ruby
Checkout the repository `git clone https://github.com/sokkalf/oled-control.git`

Make a `build` directory, `cd build`, and `cmake ..`
Makefiles should be generated.

You can now run
`make` to build the test program, and
`./oled_control` to run it.

It will play back a bit of text from [Zero Wing](https://en.wikipedia.org/wiki/All_your_base_are_belong_to_us)
