DEBUG  = -g
VERSION = -std=c++11
CFLAGS = -pedantic -Wall -Wextra $(VERSION) $(DEBUG)
LFLAGS = -Wall $(VERSION) $(DEBUG)
CXX = g++

INCS = LList.h 
SRCS = LList.cpp TestLList.cpp TestMaxList.cpp
EXEC = TestLList TestMaxList

all: $(SRCS) $(EXEC)

LList.o: LList.cpp LList.h
	g++ $(CFLAGS) -c $< -o $@

TestLList.o: TestLList.cpp LList.h
	g++ $(CFLAGS) -c $< -o $@

TestMaxList.o: TestMaxList.cpp LList.h
	g++ $(CFLAGS) -c $< -o $@

TestLList: TestLList.o LList.o
	$(CXX) $(LFLAGS) TestLList.o LList.o -o $@

TestMaxList: TestMaxList.o LList.o
	$(CXX) $(LFLAGS) TestMaxList.o LList.o -o $@

# for Windows
clean:
	del *.o
	@echo clean done
   
# for UNIX / Linux 
remove:
	\rm -f *.o  $(EXEC)
	@echo clean done
