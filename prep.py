import os
import sys
import getopt
from tools.prep_vocore2_x64linux import prep_vocore2_x64linux
from tools.prep_x64linux_x64linux import prep_x64linux_x64linux

def main(argv):
    """ Top of prep.py -- will go through child directories and build dependencies"""

    target_platform = 'x64linux'

    try:
        opts, dummy = getopt.getopt(argv, "p:")
    except getopt.GetoptError:
        print('Invalid arguments')
        sys.exit(1)

    supported_platforms = {'vocore2', 'x64linux'}
    for opt, arg in opts:
        if opt == '-p':
            target_platform = arg
            if target_platform in supported_platforms:
                print('Overriding default platform. Preparing for {0}'.format(target_platform))
            else:
                print('Invalid target platform: "{0}". Supported Platforms:"{1}"'.format(
                    target_platform, supported_platforms))
                sys.exit(1)


    #For now, host platform is always linux.
    #TODO support Windows...

    repo_root = os.getcwd()

    if target_platform == "vocore2":
        prep_vocore2_x64linux(repo_root)
    elif target_platform == "x64linux":
        prep_x64linux_x64linux(repo_root)

if __name__ == "__main__":
    main(sys.argv[1:])
