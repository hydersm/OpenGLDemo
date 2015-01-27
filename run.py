import os
import sys
import subprocess

if(sys.argv[1] == '-h' or sys.argv[1] == '--help'):
	help = """Use this python script to easily run built programs. Use syntax:
			python run.py [flavor] [module.programName]"""
	print help
else:
	flavor = sys.argv[1]
	fileName = sys.argv[2]
	filePath = 'build/' + flavor + '/bin/' + fileName
	absFilePath = os.path.abspath(filePath)

	print 'linking libsfml-window'
	p = subprocess.Popen(['install_name_tool', '-add_rpath', '@executable_path/../../../libs/lib', filePath])
	p.wait()

	print 'running program: ' + fileName
	p = subprocess.Popen(filePath)
	p.wait()

