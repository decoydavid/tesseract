# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"SDL2-2.0.3/include" -I"vmmlib-release-1.6.0/include" 
Release_Include_Path=-I"SDL2-2.0.3/include" -I"vmmlib-release-1.6.0/include"

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Release_Libraries=-l bcm2835 -l rt

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD 
Release_Preprocessor_Definitions=-D GCC_BUILD 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -g
Release_Compiler_Flags=-O2 -g

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Release 

# Builds the Release configuration...
.PHONY: Release
Release: gccRelease/abBitmap.o gccRelease/abFont.o gccRelease/abGenerator.o gccRelease/abLattice.o gccRelease/abMain.o gccRelease/abTextGenerator.o gccRelease/abWaveGenerator.o gccRelease/stdafx.o 
	g++ gccRelease/abBitmap.o gccRelease/abFont.o gccRelease/abGenerator.o gccRelease/abLattice.o gccRelease/abMain.o gccRelease/abTextGenerator.o gccRelease/abWaveGenerator.o gccRelease/stdafx.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/afrikaburn_2017.exe

# Compiles file abBitmap.cpp for the Release configuration...
-include gccRelease/abBitmap.d
gccRelease/abBitmap.o: abBitmap.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abBitmap.cpp $(Release_Include_Path) -o gccRelease/abBitmap.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abBitmap.cpp $(Release_Include_Path) > gccRelease/abBitmap.d

# Compiles file abFont.cpp for the Release configuration...
-include gccRelease/abFont.d
gccRelease/abFont.o: abFont.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abFont.cpp $(Release_Include_Path) -o gccRelease/abFont.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abFont.cpp $(Release_Include_Path) > gccRelease/abFont.d

# Compiles file abGenerator.cpp for the Release configuration...
-include gccRelease/abGenerator.d
gccRelease/abGenerator.o: abGenerator.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abGenerator.cpp $(Release_Include_Path) -o gccRelease/abGenerator.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abGenerator.cpp $(Release_Include_Path) > gccRelease/abGenerator.d

# Compiles file abLattice.cpp for the Release configuration...
-include gccRelease/abLattice.d
gccRelease/abLattice.o: abLattice.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abLattice.cpp $(Release_Include_Path) -o gccRelease/abLattice.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abLattice.cpp $(Release_Include_Path) > gccRelease/abLattice.d

# Compiles file abMain.cpp for the Release configuration...
-include gccRelease/abMain.d
gccRelease/abMain.o: abMain.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abMain.cpp $(Release_Include_Path) -o gccRelease/abMain.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abMain.cpp $(Release_Include_Path) > gccRelease/abMain.d

# Compiles file abTextGenerator.cpp for the Release configuration...
-include gccRelease/abTextGenerator.d
gccRelease/abTextGenerator.o: abTextGenerator.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abTextGenerator.cpp $(Release_Include_Path) -o gccRelease/abTextGenerator.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abTextGenerator.cpp $(Release_Include_Path) > gccRelease/abTextGenerator.d

# Compiles file abWaveGenerator.cpp for the Release configuration...
-include gccRelease/abWaveGenerator.d
gccRelease/abWaveGenerator.o: abWaveGenerator.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c abWaveGenerator.cpp $(Release_Include_Path) -o gccRelease/abWaveGenerator.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM abWaveGenerator.cpp $(Release_Include_Path) > gccRelease/abWaveGenerator.d

# Compiles file stdafx.cpp for the Release configuration...
-include gccRelease/stdafx.d
gccRelease/stdafx.o: stdafx.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c stdafx.cpp $(Release_Include_Path) -o gccRelease/stdafx.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM stdafx.cpp $(Release_Include_Path) > gccRelease/stdafx.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug/source
	mkdir -p gccRelease/source

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f gccDebug/*.a
	rm -f gccDebug/*.so
	rm -f gccDebug/*.dll
	rm -f gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f gccRelease/*.a
	rm -f gccRelease/*.so
	rm -f gccRelease/*.dll
	rm -f gccRelease/*.exe
