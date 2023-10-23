# Define variables
CXX = g++
CXXFLAGS = -Wall -g

# Source files
SRCS = mytest.cpp satnet.h satnet.cpp driver.cpp

# Object files
OBJS = mytest.o satnet.o driver.o

# Target
TARGET = TestResults

# Build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Dependencies
mytest.o: mytest.cpp satnet.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

satnet.o: satnet.cpp satnet.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

driver.o: driver.cpp satnet.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

# Default target
all: $(TARGET)
