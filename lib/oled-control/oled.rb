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
        0xF1 => 0x7D, # ñ
        0xD1 => 0x5D, # Ñ
        0xE4 => 0x7B, # ä
        0xC4 => 0x5B, # Ä
        0xFC => 0x7E, # ü
        0xDC => 0x5E, # Ü
        0xE9 => 0xA5, # é
        0xC9 => 0xBF, # É
        0xED => 0xE8, # í
        0xCD => 0xE3, # Í
        0xDF => 0xBE, # ß
        0xE1 => 0xE7, # á
        0xC1 => 0xE2, # Á
        0xEA => 0xC7, # ê
        0xCA => 0xC6, # Ê
        0x40 => 0xA0, # @
        0xA4 => 0x24, # ¤
        0x24 => 0xA2, # $
        0xA3 => 0xA1, # £
        0xFA => 0xEA, # ú
        0xDA => 0xE5, # Ú
        # unsupported characters are mapped to closest match
        0xEF => 0x69, # ï -> i
        0xCF => 0x49, # Ï -> I
        0xEB => 0x65, # ë -> e
        0xCB => 0x45, # Ë -> E
        0xE3 => 0x61, # ã -> a
        0xC3 => 0x41, # Ã -> A
    }
    self.init(i2c_bus, i2c_address)
  end

  def clear_row(row)
    set_cursor(0, row)
    write(" "*20)
  end

  def write(str)
    iso_string = str.encode('iso-8859-1')
    encoded_string = []
    iso_string.each_byte{|b| encoded_string << (@character_conversion[b.ord].nil? ? b.ord : @character_conversion[b.ord]) }
    self.write_string(encoded_string.pack("c*"))
  end
end
