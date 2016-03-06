# oled-control
Ruby Gem for SSD1311 based 20x4 OLED display from [wide.hk](http://www.wide.hk).
Should theoretically work for 20x2 and 16x2 as well, with some modifications.

## Usage
```ruby
require 'oled-control/oled'

oled = OLED.new
oled.clear # clear display
oled.set_cursor(0, 1) # set cursor position to column 0, row 1
oled.write('Hello, world!')
```

The library defaults to I2C-bus `/dev/i2c-1` and I2C device address `0x3C`
If you require another bus/address, you can use
```ruby
OLED.new('/dev/i2c-2', 0x45)
```

### Character set
To utilize the various supported characters (I use the ROM A set on the SSD1311), the library will first do a conversion to ISO-8859-1, and then do character replacement to make the characters match up.

See the `@character_conversion` variable in [this file](../master/lib/oled-control/oled.rb) and the [SSD1311 datasheet](http://www.midascomponents.co.uk/pdf/ssd1311.pdf) for reference.
