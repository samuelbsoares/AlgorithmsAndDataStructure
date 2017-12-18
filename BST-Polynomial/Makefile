DEBUG  = -g
VERSION = -std=c++11
CFLAGS = -pedantic -Wall -Wextra $(VERSION) $(DEBUG)
LFLAGS = -Wall $(VERSION) $(DEBUG)
CXX = g++

INCS = Polynomial.h

SRCS = Polynomial.cpp \
    testPolynomial.cpp \
    testPolynomialDiff.cpp

EXEC = testPolynomial \
    testPolynomialDiff

all: $(SRCS) $(EXEC)

%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

testPolynomial: testPolynomial.o Polynomial.o
	$(CXX) $(LFLAGS) testPolynomial.o Polynomial.o -o $@

testPolynomialDiff: testPolynomialDiff.o Polynomial.o
	$(CXX) $(LFLAGS) testPolynomialDiff.o Polynomial.o -o $@

# for Windows
clean:
	del *.o
	@echo clean done
   
# for UNIX / Linux 
remove:
	rm -f *.o  $(EXEC)
	@echo clean done
