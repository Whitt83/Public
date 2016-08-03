import sys
import os
import subprocess
from subprocess import PIPE

p = subprocess.Popen(["cmake", "--version"], stdout=PIPE, bufsize=1)
foundCMake=0
with p.stdout:
	for line in iter(p.stdout.readline, b''):
		if ("cmake version 3.5" in line):
			foundCMake=1
p.wait()

if (foundCMake == 0):
	print "Could not execute CMake. Check that it is installed and on the system path"
	sys.exit(-1)
else:
	print "Invoking CMake on source tree..."


outputDirectory=os.getcwd() + "/build/"
print "Output files will be placed at " + outputDirectory
p = subprocess.Popen(["cmake", "-G", "CodeBlocks - Unix Makefiles", ".."], cwd=outputDirectory, stdout=PIPE, bufsize=1)
with p.stdout:
	for line in iter(p.stdout.readline, b''):
		print line,
p.wait()
