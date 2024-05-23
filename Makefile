CC := g++
CCFLAGS := -Wall -I/usr/include/ncurses
LDFLAGS := -L/usr/lib -lncurses

SRC_PATH := src
OBJ_PATH := obj

# target(entry point)와 target-specific dependency 정의
TARGET              := main
TARGET_DEPENDENCY   := main.cpp

# target-specific
SOURCES     := $(filter-out $(SRC_PATH)/$(TARGET_DEPENDENCY), $(wildcard $(SRC_PATH)/*.cpp))
OBJECTS     := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SOURCES))
ALL_OBJECTS := $(OBJ_PATH)/main.o $(OBJECTS)

# main 타겟과 의존성 정의
$(TARGET): $(ALL_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# .cpp 파일에서 .o 파일을 생성하는 규칙
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ $(CCFLAGS)

# 의존성 목록 출력
list:
	@echo SOURCES: $(SOURCES)
	@echo EXCLUSION: $(TARGET_DEPENDENCY)
	@echo OBJECTS: $(OBJECTS)

# 깨끗하게 청소
clean:
	rm -rf $(OBJ_PATH)/*.o $(TARGET)
