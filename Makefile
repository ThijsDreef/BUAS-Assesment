CC=g++
SOURCE=Source/
BUILD=build/
EXE=exe/
TARGET=run.exe
OPTIMALIZATIONLEVEL=-O3
#lazy multiple directories solution
objects =  $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*/*.cpp))
objects += $(patsubst $(SOURCE)%.cpp,$(BUILD)%.o, $(wildcard $(SOURCE)*/*/*/*/*.cpp))


#again lazy multiple directories solution
TOINCLUDE =  $(sort $(dir $(wildcard headers/)))

#warning make files make you lazy
#warning dont write lazy code
INCLUDE = $(sort -I$(TOINCLUDE))

LDFLAGS=$(subst co,-Ico, $(INCLUDE))




$(EXE) : $(objects)
	$(CC) $(OPTIMALIZATIONLEVEL) -std=c++11 -Wall -o $(EXE)$(TARGET) $(objects) $(LDFLAGS) -Llibs/ -lglew32 -lgdi32 -lopengl32  -m64
$(BUILD)%.o : $(SOURCE)%.cpp
	$(CC)$(LDFLAGS) $(OPTIMALIZATIONLEVEL) -std=c++11 -Wall -c $< -o $@ -m64 

$(BUILD):

$(EXE):

init :
	md build
	robocopy source build /e /xf * >nul

clean:
	rmdir build /S /Q
