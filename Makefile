CC := g++
CCFLAGS := -Wall

SRC_PATH := src
OBJ_PATH := obj

TARGET = snake

SOURCES	:= $(wildcard $(SRC_PATH)/*.cpp)
OBJECTS	:= $(SOURCES: $(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)
LIBS	:= -lncurses


main: $(OBJECTS)
	$(CC) -o $(TARGET) $^ $(CCFLAGS) $(LIBS)


$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

clean:
	rm -rf $(OBJECTS)