
import os
import tarfile

toolchainFile = "OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64"
def prep_vocore2_x64linux(repoRoot):
	if not os.path.exists(repoRoot + "/build/vocore2/"):
		os.makedirs(repoRoot + "/build/vocore2/")


	#WRT Toolchain

	outputDirectory = repoRoot + "/build/vocore2/" + toolchainFile
	if os.path.exists(outputDirectory):
		print "Toolchain exists.  Not redeploying."
	else:
		# We do not make the directory because the tar extraction will
		tar = tarfile.open(repoRoot + "/deps/" + toolchainFile + ".tar.bz2")
		tar.extractall(repoRoot + "/build/vocore2/")
		


