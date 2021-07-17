# C-Abschluss-Intel4004Emulator
This is an emulation of the Intel4004 from 1971, including Intel4001 (ROM), Intel4002 (RAM) and Intel4004 (CPU), which are part of the MCS-4 family.<br>
This project was realized as part of an examination at the university [DHBW Friedrichshafen](https://www.ravensburg.dhbw.de/startseite).

## Folder Structure
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

> Note: The main.cpp is an example on how to instantiate an Intel4004 object, as well as accessing it's sub-modules Intel4001, Intel4002 and Intel4004Stack. It further includes a function, that outputs the current state of the processor to the terminal (`functionPrintProcessorState()`).

## Compile
### Windows:
```powershell
g++ main.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o main.exe
```
```powershell
g++ unittest.cpp ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp ..\inc\intelhex.c -o unittest.exe
```

### Linux:
```bash
g++ main.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o main.out
```
```bash
g++ unittest.cpp ../4001-ROM/4001.cpp ../4002-RAM/4002.cpp ../4004/4004.cpp ../4004/4004_stack.cpp ../inc/intelhex.c -o unittest.out
```

> Note: In your main.cpp or unittest.cpp: only include \"4004/4004.h\" in order to implement the emulation

> Note: Your relative paths to the needed c/cpp files might be different if you are not using this project's structure or file naming

## Authors
* David Felder / [github](https://github.com/screetox) / [E-Mail](mailto:felder.david-it20@it.dhbw-ravensburg.de?cc=herkommer.flor-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Florian Herkommer / [github](https://github.com/Floqueboque) / [E-Mail](mailto:herkommer.flor-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Henry Schuler / [github](https://github.com/schuler-henry) / [E-Mail](mailto:schuler.henry-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;herkommer.flor-it20@it.dhbw-ravensburg.de;silberzahn.lea-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
* Lea Silberzahn / [github](https://github.com/lealabert) / [E-Mail](mailto:silberzahn.lea-it20@it.dhbw-ravensburg.de?cc=felder.david-it20@it.dhbw-ravensburg.de;herkommer.flor-it20@it.dhbw-ravensburg.de;schuler.henry-it20@it.dhbw-ravensburg.de&amp;subject=[GitHub]%20C%20Intel4004%20Emulator)
