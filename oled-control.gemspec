Gem::Specification.new do |s|
  s.name = 'oled-control'
  s.version = '0.1.1'
  s.date = '2016-03-10'
  s.summary = 'Control OLED i2c display'
  s.description = 'Ruby Gem for SSD1311 based 20x4 OLED display'
  s.authors = ['Christian Lønaas']
  s.licenses= ['MIT']
  s.email = 'christian.lonaas@discombobulator.org'
  s.homepage = 'https://github.com/sokkalf/oled-control'
  s.files = Dir.glob('lib/**/*.rb') +
            Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions = ['ext/oled-control/extconf.rb']
 end
