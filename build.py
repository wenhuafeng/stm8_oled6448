#!/usr/bin/env python

import sys
import os
import datetime
import platform
import subprocess
import shutil
from subprocess import Popen, PIPE

CHECKSUM_OUT = "checksum.exe sc1086.bin CRC32"

# IAR path
iar_build_exe = "D:/Program Files (x86)/IAR Systems/Embedded Workbench 8.0/common/bin/IarBuild.exe"
iar_build_log = "cat ./project/build_log.txt"

# output files path
iar_source_file_hex = "project/Debug/Exe/sc1086.hex"
iar_source_file_bin = "project/Debug/Exe/sc1086.bin"
target_path = "user/output"

# openocd define
stlink_config_file = "user/openocd/stlink-dap.cfg"
chip_config_file = "user/openocd/stm8l.cfg"
program_cmd = "\"init; load_image user/output/sc1086.bin 0x8000; verify; reset; shutdown\""

# STVP_CmdLine.exe define
stvp_cmd_Line           = "D:/Program Files (x86)/STMicroelectronics/st_toolset/stvp/STVP_CmdLine.exe"
stvp_cmd_Line_rm_log    = "rm ./Result.log"
stvp_cmd_Line_print_log = "cat ./Result.log"

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
    get_exitcode_stdout_stderr([iar_build_exe, "project/sc1086.ewp", "-build", "Debug", "-log", "info", ">", "project/build_log.txt"])
    os.system(iar_build_log)
    cp_build_file(iar_source_file_bin, target_path)

def sdcc_build():
    return

def stlink_download():
    host_os = platform.system()
    print("host os: %s" % host_os)

    if host_os == 'Windows':
        #cmd = 'STVP_CmdLine -BoardName=ST-LINK -ProgMode=SWIM -Tool_ID=0 -Device=STM8L051x3 -log -verbose -progress -no_loop -FileProg=./user/output/sc1086.hex'
        #subprocess.Popen(cmd)
        os.system(stvp_cmd_Line_rm_log)
        get_exitcode_stdout_stderr([stvp_cmd_Line, "-BoardName=ST-LINK", "-ProgMode=SWIM", "-Tool_ID=0", "-Device=STM8L051x3", "-log", "-verbose", "-progress", "-no_loop", "-FileProg=./user/output/sc1086.hex"])
        os.system(stvp_cmd_Line_print_log)
    else:
        print("unsupport platform")
        sys.exit(2)

def build_select(para):
    if para == 'iar':
        iar_build()
    elif para == 'sdcc':
        sdcc_build()
    elif para == 'stlink':
        stlink_download()
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
    if parameter == 'iar' or parameter == 'sdcc':
        print("\r\n")
        checksum_hex_file()

    end = datetime.datetime.now()
    print('run time: %s second' %(end - start))

if __name__ == "__main__":
    main_func(sys.argv[1])