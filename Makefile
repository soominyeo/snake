CC := g++
CCFLAGS := -Wall

SRC_PATH := src
OBJ_PATH := obj

# target(entry point)와 target-specific dependency 정의
TARGET 				:= main
TARGET_DEPENDENCY 	:= main.cpp

# target-specific
SOURCES		:= $(filter-out $(addprefix $(SRC_PATH)/,$(TARGET_DEPENDENCY)), $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(SRC_PATH)/*.h*))
OBJECTS 	:= $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(filter-out %.h %.hpp,$(SOURCES)))
DEPENDENCY 	= $(OBJECTS)
LIBS		:= -lncurses

# target-specific dependency 정의
main: DEPENDENCY += $(SRC_PATH)/main.cpp

.SECONDEXPANSION:

all : $(TARGET)

$(TARGET): $$(DEPENDENCY)
	$(CC) -o $@ $(filter %.c %.cpp %.o, $^) $(CCFLAGS) $(LIBS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp $(wildcard $(SRC_PATH)/%.hpp)
	$(CC) -c $< -o $@ $(CCFLAGS) $(LIBS) 

list:
	@echo SOURCES: $(SOURCES)
	@echo EXCLUSION: $(TARGET_DEPENDENCY)
	@echo OBJECTS: $(OBJECTS)

clean:
	rm -rf $(OBJECTS)