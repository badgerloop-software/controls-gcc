# Badgerloop Controls

*Contributors: Vaughn Kottler, Cooper Green*

**Development Platform:** [STM32 Nucleo 144 F767Zi](https://developer.mbed.org/platforms/ST-Nucleo-F767ZI/)

**Toolchain:** 
  * [GNU ARM Embedded (GCC)](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)
  * [Make](https://www.gnu.org/software/make/manual/make.html)
  * [Bash](https://www.gnu.org/software/bash/)

## Development Instructions

The ideal use of this project is to be able to edit source files and run `make install` which should automatically preprocess, compile, assemble and link the source into an ELF file that will be copied to a binary blob that gets flashed directly to the target device (typically ARM development board) using a number of scripts and utilities. A list of targets that are supported can be found below.

Without the hand-holding (and bottlenecking!!!) of a licensed IDE or Eclipse port it might be possible that changes to `Makefile` or `makefile.conf` will be necessary as development continues and this project matures. It is highly recommended to study these files to understand how the project is being built in the first place, here are some common cases where `Makefile` changes will be necessary:

  * A new source file is added
  * Support for a new board is being worked on
  * An additional argument passed to the toolchain is needed
  * A toolchain argument needs to be omitted
  * An additional target is being created

[Video tutorials](https://www.youtube.com/playlist?list=PLTPrK33wiSskApHw-Tc647bs5f7fbaD24) describing how this project was set up and demonstrating the workflow also exist.

**Documentation Repository:** [https://github.com/madison-embedded/documentation](https://github.com/madison-embedded/documentation)

## Make Targets

**clean**

  * Deletes build objects (all \*.o, \*.elf. \*.map, \*.bin and output.txt if it exists).

**install**

  * Runs `./$(PROC_DIR)/install.sh` which usually will be a Segger JLink command which connects to a [reflashed onboard JLink](https://www.youtube.com/watch?v=ezPou8W_Ntc) (i.e. STM32 Nucleos) or actual JLink and executes a script that flashes `$(PROJECT).bin` to the necessary physical address and exits.

**debug**

  * Essentially the same as **install** but instead of exiting *JLinkExe* will remain running (executable gets flashed). This works well with **dump** when doing debugging that requires stepping through instructions.

**dump**

  * Disassembles the project ELF file into *output.txt* and opens it in a new terminal where the default terminal is `gnome-terminal`.

