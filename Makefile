CXX = clang++

CXXFLAGS = -std=c++20 -Wall

SRC = solution.cpp
TARGET = solution
OUTPUT = result.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OUTPUT)
