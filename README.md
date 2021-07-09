# C-Abschluss-Intel4004Emulator

## Folder structure
Folder | Usage
------ | -----
4001-ROM | source files for Intel4001 ROM module
4002-RAM | source files for Intel4002 RAM module
4004 | source files for Intel4004 module
docs | documentaion on Intel400x
inc | source files for Intel400x
not_in_use | temp folder containing files that are currently unused
src | contains main.cpp

## Execute
Windows:
* g++ main.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o main.exe
* g++ unittest.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o unittest.exe
Linux:
* g++ main.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o main.out
* g++ unittest.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o unittest.out

## Authors
* David Felder / [github](https://github.com/screetox)
* Florian Herkommer / [github](https://github.com/Floqueboque)
* Henry Schuler / [github](https://github.com/schuler-henry)
* Lea Silberzahn / [github](https://github.com/lealabert)
