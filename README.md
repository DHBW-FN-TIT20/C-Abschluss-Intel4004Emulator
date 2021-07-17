# C-Abschluss-Intel4004Emulator

## Folder structure
Folder | Usage
------ | -----
[4001-ROM](4001-ROM) | source files for Intel4001 ROM module
[4002-RAM](4002-RAM) | source files for Intel4002 RAM module
[4004](4004) | source files for Intel4004 CPU and Intel4004Stack module
[UnitTest](UnitTest) | contains [unittest.cpp](UnitTest/unittest.cpp) and it's needed files
[docs](docs) | documentaion on Intel400x
[inc](inc) | source files for Intel400x
[not_in_use](not_in_use) | temp folder containing files that are currently unused
[src](src) | contains [main.cpp](src/main.cpp)

> Note: The unittest.cpp is only a temporary copy. The newest version can be found in the [C-Abschluss-Intel4004Emulator-UnitTest](https://github.com/DHBW-FN-TIT20/C-Abschluss-Intel4004Emulator-UnitTest) repository.

## Compile
### Windows:
* `g++ main.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o main.exe`
* `g++ unittest.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o unittest.exe`

### Linux:
* `g++ main.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o main.out`
* `g++ unittest.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o unittest.out`

> Note: In your main.cpp or unittest.cpp: only include \"4004/4004.h\" in order to implement the emulation

> Note: Your relative paths to the needed c/cpp files might be different if you are not using this project's structure or file naming

## Authors
* David Felder / [github](https://github.com/screetox) / [E-Mail](mailto:felder.david-it20@it.dhbw-ravensburg.de?cc=herkommer.flor-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Florian Herkommer / [github](https://github.com/Floqueboque) / [E-Mail](mailto:herkommer.flor-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Henry Schuler / [github](https://github.com/schuler-henry) / [E-Mail](mailto:schuler.henry-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;herkommer.flor-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Lea Silberzahn / [github](https://github.com/lealabert) / [E-Mail](mailto:silberzahn.lea-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;herkommer.flor-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
