DEBUG  = -g
VERSION = -std=c++11
CFLAGS = -pedantic -Wall -Wextra $(VERSION) $(DEBUG)
LFLAGS = -Wall $(VERSION) $(DEBUG)

INCS = Stack.h
SRCS = Stack.cpp\
	TestStack.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = TestStack

all: $(SRCS) $(EXEC)

# To make an object from source
#.cpp.o: 
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o $@

# for Windows
clean:
	del *.o $(EXEC).exe
	@echo clean done
