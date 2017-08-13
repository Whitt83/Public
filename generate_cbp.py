import sys
import os
import subprocess
import getopt
from subprocess import PIPE

def main(argv):
    p = subprocess.Popen(["cmake", "--version"], stdout=PIPE, bufsize=1)
    found_cmake=0
    with p.stdout:
        for line in iter(p.stdout.readline, b''):
            if ("cmake version 3" in line):
                found_cmake=1
    p.wait()

    if (found_cmake == 0):
        print('Could not execute CMake. Check that it is installed and on the system path')
        sys.exit(-1)
    else:
        print('Invoking CMake on source tree...')

    # CMake was found.  What platform are we building for?

    try:
        opts, args = getopt.getopt(argv, "p:")
    except getopt.GetoptError:
        print('Invalid arguments')
        sys.exit(1)


    target_platform = 'x64linux'
    supported_platforms = { 'vocore2', 'x64linux'}
    for opt, arg in opts:
        if opt == '-p':
            target_platform = arg
            if target_platform in supported_platforms:
                print('Overriding default platform. Building for {0}'.format(target_platform))

            else:
                print('Invalid target platform:{0}. Supported Platforms: {1}'.format(target_platform, supported_platforms))
                sys.exit(1)

    # Select the toolchain file...
    repo_root = os.getcwd()
    toolchain_file = ""
    toolchain_args = ""
    host_platform = "x86_64-linux"
    if host_platform != target_platform:
        if target_platform == 'vocore2':
            os.environ["TOOLCHAIN"] = repo_root + "/build/vocore2/OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2"
            toolchain_file = "./tools/toolchains/toolchain-mips-linux-vocore2.cmake"


    output_directory = repo_root + "/build/" + target_platform
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    print('Output files will be placed at {0}'.format(output_directory))

    if toolchain_file != "":
        toolchain_args = "-DCMAKE_TOOLCHAIN_FILE=" + toolchain_file
        print('Using toolchain specified by: {0}'.format(toolchain_file))
    opened_process = subprocess.Popen(["cmake", toolchain_args, "-Dtarget_platform=" + target_platform, "-G", "CodeBlocks - Unix Makefiles", "../.."], cwd=output_directory, stdout=PIPE, bufsize=1)
    with opened_process.stdout:
        for line in iter(opened_process.stdout.readline, b''):
            print('{0}'.format(line))
    opened_process.wait()

if __name__ == "__main__":
    main(sys.argv[1:])
