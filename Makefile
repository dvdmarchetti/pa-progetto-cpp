VPATH=./src:./include
INCLUDES=-I./include
TARGET=main.exe

$(TARGET): main.o
	g++ $^ -o $(TARGET)

main.o: main.cpp
	g++ $< -c $(INCLUDES)

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
