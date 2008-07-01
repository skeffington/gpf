require 'fileutils'
require 'yaml'
require 'scripts/include/misc'

ls_Version = nil
File.open('version.txt', 'r') { |lk_File| ls_Version = lk_File.read.strip }

if ls_Version == nil
	puts 'Internal error: Unable to determine GPF version.'
	exit 1
end

puts "Creating release for GPF #{ls_Version}..."

ls_Platform = determinePlatform()
ls_Make = {'windows' => 'nmake', 'linux' => 'make', 'mac' => 'make'}
ls_QMake = {'windows' => 'qmake', 'linux' => 'qmake', 'mac' => 'qmake -spec macx-g++'}
ls_BinaryExtension = {'windows' => '.exe', 'linux' => '', 'mac' => ''}

ls_DestDir = "gpf-#{ls_Version}-#{ls_Platform}"
FileUtils.rmtree(ls_DestDir)
FileUtils.mkpath(ls_DestDir)
FileUtils.rm_rf(ls_DestDir + '.tar')
FileUtils.rm_rf(ls_DestDir + '.tar.bz2')
FileUtils.rm_rf(ls_DestDir + '.zip')

puts 'Building GPF executables...'

FileUtils.rmtree(File::join('obj'))
lk_Projects = ['gpfbatch', 'gpfd', 'gpfdump', 'gpfindex', 'gpfquery']
lk_Projects.each { |ls_Project| system("cd projects/#{ls_Project} && #{ls_QMake[ls_Platform]} && #{ls_Make[ls_Platform]} release && cd ../../") }

puts 'Collecting GPF executables...'

lk_Projects.each { |ls_Project| FileUtils.cp(ls_Project + ls_BinaryExtension[ls_Platform], ls_DestDir) }

if (ls_Platform == 'windows')
	lk_Projects.each { |ls_Project| FileUtils.cp(ls_Project + '.exe.manifest', ls_DestDir) }
	FileUtils.cp('C:/Qt/4.3.4/bin/QtCore4.dll', ls_DestDir)
	FileUtils.cp('C:/Qt/4.3.4/bin/QtNetwork4.dll', ls_DestDir)
	FileUtils.cp('C:/Programme/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/msvcp90.dll', ls_DestDir)
	FileUtils.cp('C:/Programme/Microsoft Visual Studio 9.0/VC/redist/x86/Microsoft.VC90.CRT/msvcr90.dll', ls_DestDir)
end

if (ls_Platform == 'windows')
	puts 'Building ZIP package...'
	
	system("helpers/7z/7za.exe a -r #{ls_DestDir}.zip #{ls_DestDir}")
else
	puts 'Builing bzip2 package...'
	system("tar cvf #{ls_DestDir}.tar #{ls_DestDir}")
	system("bzip2 -z #{ls_DestDir}.tar")
end

FileUtils.rmtree(ls_DestDir)
FileUtils.rmtree(File::join('obj'))
lk_Projects.each { |ls_Project| FileUtils::rm_rf(ls_Project + ls_BinaryExtension[ls_Platform]) }
lk_Projects.each { |ls_Project| FileUtils.rm_rf(ls_Project + '.exe.manifest') } if (ls_Platform == 'windows')
