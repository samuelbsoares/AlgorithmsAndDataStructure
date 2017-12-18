DEBUG  = -g
VERSION = -std=c++11
CFLAGS = -pedantic -Wall -Wextra $(VERSION) $(DEBUG)
LFLAGS = -Wall $(VERSION) $(DEBUG)
CXX = g++

INCS = HashTable.h

SRCS = HashTable.cpp \
    TestHashTable.cpp

EXEC = TestHashTable

all: $(SRCS) $(EXEC)

%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

TestHashTable: TestHashTable.o HashTable.o
	$(CXX) $(LFLAGS) TestHashTable.o HashTable.o -o $@

# for Windows
clean:
	del *.o
	@echo clean done

# for UNIX / Linux 
remove:
	rm -f *.o  $(EXEC)
	@echo clean done
