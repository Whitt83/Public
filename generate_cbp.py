import sys
import os
import subprocess
import getopt
from subprocess import PIPE

def main(argv):
	p = subprocess.Popen(["cmake", "--version"], stdout=PIPE, bufsize=1)
	foundCMake=0
	with p.stdout:
		for line in iter(p.stdout.readline, b''):
			if ("cmake version 3" in line):
				foundCMake=1
	p.wait()

	if (foundCMake == 0):
		print "Could not execute CMake. Check that it is installed and on the system path"
		sys.exit(-1)
	else:
		print "Invoking CMake on source tree..."

	# CMake was found.  What platform are we building for?

	try:
		opts, args = getopt.getopt(argv, "p:")
	except getopt.GetoptError:
		print "Invalid arguments"
		sys.exit(1)


	targetPlatform = 'x86_64-linux'
	supportedPlatforms = { 'vocore2', 'x86_64-linux'}
	for opt, arg in opts:
		if opt == '-p':
			targetPlatform = arg
			if targetPlatform in supportedPlatforms:
				print "Overriding default platform. Building for " + targetPlatform

			else:
				print "Invalid target platform:" + targetPlatform + ". Supported Platforms:" + str(supportedPlatforms)
				sys.exit(1)
		
	# Select the toolchain file...
	repoRoot = os.getcwd()
	toolchainFile = ""
	toolchainArgs = ""
	hostPlatform = "x86_64-linux"
	if hostPlatform != targetPlatform:
		if targetPlatform == 'vocore2':
			os.environ["TOOLCHAIN"] = repoRoot + "/build/vocore2/OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2"
			toolchainFile = "./tools/toolchains/toolchain-mips-linux-vocore2.cmake"


	outputDirectory=os.getcwd() + "/build/" + targetPlatform
	if not os.path.exists(outputDirectory):
		os.makedirs(outputDirectory)
	print "Output files will be placed at " + outputDirectory

	if toolchainFile != "":
		toolchainArgs = "-DCMAKE_TOOLCHAIN_FILE=" + toolchainFile
		print "Using toolchain specified by: " + toolchainFile
	p = subprocess.Popen(["cmake", toolchainArgs, "-DTARGETPLATFORM=" + targetPlatform, "-G", "CodeBlocks - Unix Makefiles", "../.."], cwd=outputDirectory, stdout=PIPE, bufsize=1)
	with p.stdout:
		for line in iter(p.stdout.readline, b''):
			print line,
	p.wait()

if __name__ == "__main__":
	main(sys.argv[1:])
