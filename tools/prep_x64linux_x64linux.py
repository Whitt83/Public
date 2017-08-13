import tarfile
import zipfile
import os


def prep_x64linux_x64linux(repo_root):
    """ Prepapres dependencies for Linux compilation """

    if not os.path.exists(repo_root + "/build/x64linux/"):
        os.makedirs(repo_root + "/build/x64linux/")

    #Open NN
    output_directory = repo_root + "/build/x64linux/OpenNN-master"
    if os.path.exists(output_directory):
        print('OpenNN exists.  Not redeploying.')
    else:
        # We do not make the directory because the tar extraction will
        zip_file_path = repo_root + "/deps/OpenNN-master.zip"
        print('Extracting zip at {0}'.format(zip_file_path))
        zip = zipfile.ZipFile(zip_file_path)
        zip.extractall(repo_root + "/build/x64linux/")
        zip.close()
