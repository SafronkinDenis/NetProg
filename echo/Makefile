CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = echo_client

all: $(TARGET)

$(TARGET): client.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) client.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
