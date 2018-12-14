CC=g++
SOURCE=core/source/
BUILD=build/
EXE=exe/
TARGET=run.exe
OPTIMALIZATIONLEVEL=
#lazy multiple directories solution
objects =  $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*/*/*.cpp))


#again lazy multiple directories solution
TOINCLUDE =  $(sort $(dir $(wildcard core/headers/)))

#warning make files make you lazy
#warning dont write lazy code
INCLUDE = $(sort $(TOINCLUDE))

LDFLAGS=$(subst co,-Ico, $(INCLUDE))




$(EXE) : $(objects)
	$(CC) $(OPTIMALIZATIONLEVEL) -std=c++11 -Wall -g -o $(EXE)$(TARGET) $(objects) $(LDFLAGS) -Lcore/libs/ -lglew32 -lgdi32 -lopengl32  -m64
$(BUILD)%.o : $(SOURCE)%.cpp
	$(CC)$(LDFLAGS) $(OPTIMALIZATIONLEVEL) -std=c++11 -Wall -g -c $< -o $@ -m64 

$(BUILD):

$(EXE):

init :
	md build
	robocopy core/source build /e /xf * >nul

clean:
	rmdir build /S /Q
