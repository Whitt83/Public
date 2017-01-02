import tarfile
import os
import sys
import getopt

def main(argv):
	sys.path.append('./tools/')
	from prep_vocore2_x64linux import prep_vocore2_x64linux 
	from prep_x64linux_x64linux import prep_x64linux_x64linux 

	targetPlatform = 'x86_64-linux'

	try:
		opts, args = getopt.getopt(argv, "p:")
	except getopt.GetoptError:
		print "Invalid arguments"
		sys.exit(1)


	supportedPlatforms = { 'vocore2', 'x86_64-linux'}
	for opt, arg in opts:
		if opt == '-p':
			targetPlatform = arg
			if targetPlatform in supportedPlatforms:
				print "Overriding default platform. Preparing for " + targetPlatform
			else:
				print "Invalid target platform:" + targetPlatform + ". Supported Platforms:" + str(supportedPlatforms)
				sys.exit(1)


	#For now, host platform is always linux.
	#TODO support Windows...

	repoRoot = os.getcwd()

	if targetPlatform == "vocore2":
		prep_vocore2_x64linux(repoRoot)
	elif targetPlatform == "x64linux":
		prep_x64linux_x64linux(repoRoot)

if __name__ == "__main__":
	main(sys.argv[1:])

