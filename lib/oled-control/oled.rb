require 'oled-control/oled_control'

class OLED
  def initialize(i2c_bus = '/dev/i2c-1', i2c_address = 0x3c)
    # the OLED display defines its own weird character set
    @character_conversion = {
        0xE5 => 0xAF, # å
        0xC5 => 0xAE, # Å
        0xF8 => 0xAC, # ø
        0xD8 => 0xAB, # Ø
        0xE6 => 0xBD, # æ
        0xC6 => 0xBC, # Æ
        0xD6 => 0x5C, # Ö
        0xF6 => 0x7C, # ö
    }
    self.init(i2c_bus, i2c_address)
  end

  def write(str)
    iso_string = str.encode('iso-8859-1')
    encoded_string = []
    iso_string.each_byte{|b| encoded_string << (@character_conversion[b.ord].nil? ? b.ord : @character_conversion[b.ord]) }
    self.write_string(encoded_string.pack("c*"))
  end
end
