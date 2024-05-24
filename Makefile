CC := g++
CCFLAGS := -Wall -I/usr/include/ncurses
LDFLAGS := -L/usr/lib -lncurses

SRC_PATH := src
OBJ_PATH := obj

# target(entry point)와 target-specific dependency 정의
TARGET              := main main2
TARGET_DEPENDENCY   := main.cpp main2.cpp

SOURCES		:= $(filter-out $(addprefix $(SRC_PATH)/,$(TARGET_DEPENDENCY)), $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(SRC_PATH)/*.h*))
OBJECTS 	:= $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(filter-out %.h %.hpp,$(SOURCES)))
DEPENDENCY 	= $(OBJECTS)

# target-specific dependency 정의
main: DEPENDENCY += $(SRC_PATH)/main.cpp
main2: DEPENDENCY += $(SRC_PATH)/main2.cpp

.SECONDEXPANSION:

all : $(TARGET)

$(TARGET): $$(DEPENDENCY)
	$(CC) -o $@ $(filter %.c %.cpp %.o, $^) $(CCFLAGS) $(LDFLAGS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp $(wildcard $(SRC_PATH)/%.hpp)
	$(CC) -c $< -o $@ $(CCFLAGS)

# 의존성 목록 출력
list:
	@echo SOURCES: $(SOURCES)
	@echo EXCLUSION: $(TARGET_DEPENDENCY)
	@echo OBJECTS: $(OBJECTS)

# 깨끗하게 청소
clean:
	rm -rf $(OBJECTS) $(TARGET)
