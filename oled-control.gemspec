Gem::Specification.new do |s|
  s.name = 'oled-control'
  s.version = '0.0.1'
  s.date = '2016-03-06'
  s.summary = 'Control OLED i2c display'
  s.authors = ['Christian Lønaas']
  s.email = 'christian.lonaas@discombobulator.org'
  s.files = Dir.glob('lib/**/*.rb') +
            Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions = ['ext/oled-control/extconf.rb']
 end
