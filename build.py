#!/usr/bin/env python

import sys
import os
import datetime
import platform
import subprocess
import shutil
from subprocess import Popen, PIPE

CHECKSUM_OUT = 'checksum.exe mk12.hex CRC32 SHA256'

iar_build_exe = "D:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0/common/bin/IarBuild.exe"
iar_source_file_hex = 'project/Debug/Exe/sc1086.hex'
target_path = 'user/output'

def get_exitcode_stdout_stderr(args):
    """
    Execute the external command and get its exitcode, stdout and stderr.
    """
    proc = Popen(args, stdout=PIPE, stderr=PIPE, shell=True)
    out, err = proc.communicate()
    exitcode = proc.returncode
    return exitcode, out, err

def cp_build_file(source, target):
    assert not os.path.isabs(source)

    try:
        shutil.copy(source, target)
    except IOError as e:
        print("Unable to copy file. %s" % e)
    except:
        print("Unexpected error:", sys.exc_info())

def iar_build():
    print("cc type = iar")
    exitcode, out, err = get_exitcode_stdout_stderr([iar_build_exe, "project/sc1086.ewp", "-build", "Debug", "-log", "all"])
    cp_build_file(iar_source_file_hex, target_path)

def sdcc_build():
    return

def build_select(para):
    if para == 'iar':
        iar_build()
    elif para == 'sdcc':
        sdcc_build()
    else:
        print("input parameter error!")

def checksum_hex_file():
    # 切换目录到
    os.chdir(target_path)
    # 输出文件需要的信息
    os.system(CHECKSUM_OUT)

def main_func(parameter):
    start = datetime.datetime.now()

    build_select(parameter)
    if parameter == 'i':
        print("\r\n")
        checksum_hex_file()

    end = datetime.datetime.now()
    print('run time: %s second' %(end - start))

if __name__ == "__main__":
    main_func(sys.argv[1])