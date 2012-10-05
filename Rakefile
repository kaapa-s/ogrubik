require 'rake'
require 'rake/clean'

NAME = 'ogrubik'

CPP = 'g++'
CFLAGS = '`pkg-config --cflags OGRE gtkmm-2.4` -fpermissive' 
LDFLAGS = '`pkg-config --libs OGRE gtkmm-2.4` -lX11 -lboost_system' 

unless File.exists? 'kcube-1.0.zip'
	sh "wget http://www.randelshofer.ch/cubetwister/files/kcube-1.0.zip -q"
end
unless File.exists? 'src/kcube'
	sh "7z x kcube-1.0.zip"
	sh "mv KCube1.0 src/kcube"
	puts "downcasing src/kcube directory"
	Dir.glob('src/kcube/*').each { |f| File.rename(f, f.downcase) }
	sh "patch -p0 < kcube.patch"
end

TABLES = FileList['*.mtb','*.ptb']
SOURCES = FileList['src/**/*.cpp']
OBJECTS = SOURCES.ext('o')

CLEAN.include(OBJECTS)
CLOBBER.include(NAME, TABLES, 'Ogre.log', 'ogre.cfg', 'kcube-1.0.zip', 'KCube1.0', 'src/kcube')

task :default => [NAME]

rule '.o' => '.cpp' do |t|
	sh "#{CPP} #{CFLAGS} -o #{t.name} -c #{t.source}"
end

file NAME => OBJECTS do
	sh "#{CPP} #{CFLAGS} #{OBJECTS} -o #{NAME} #{LDFLAGS}"
end
