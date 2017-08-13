import os
import tarfile

TOOLCHAIN_FILE = "OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64"
def prep_vocore2_x64linux(repo_root):
    if not os.path.exists(repo_root + "/build/vocore2/"):
        os.makedirs(repo_root + "/build/vocore2/")


    #WRT Toolchain

    output_directory = repo_root + "/build/vocore2/" + TOOLCHAIN_FILE
    if os.path.exists(output_directory):
        print('Toolchain exists.  Not redeploying.')
    else:
        # We do not make the directory because the tar extraction will
        tar = tarfile.open(repo_root + "/deps/" + TOOLCHAIN_FILE + ".tar.bz2")
        tar.extractall(repo_root + "/build/vocore2/")
        tar.close()

