/*
 * Program to interact with a user using standard input to process polynomials.
 * Commands supported are inputting two polynomials and calculating their sum
 * and then getting the coefficients of some terms, the degree of the polynomial
 * and evaluating the polynomial given a specific value for x.
 *
 * All the input from a user done to standard input (cin) and the output with 
 * both results and questions for the user are done to standard output (cout). 
 * Assignment #6, CPSC 2150, November 3, 2017
 * Author: Gladys Monagan (with material from Jian hua Pan)
 */
#include "Polynomial.h"
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::string;

// the commands allowed
enum Commands {INPUT, PRINT, NUMBER_OF_TERMS, EVALUATE, GET_COEFF, 
  RESET, QUIT, INVALID};

// output the commands available
void printCommandMenu() 
{
    cout << "\n ------------------ command list ----------------------\n";
    cout << "(i) - input the polynomials a and b and computer their sum\n";
    cout << "(p) - print the polynomials a and b and a + b\n";
    cout << "(n) - number of terms in the polynomials a and b and a+b\n";
    cout << "(e) - evaluate a, b and a + b at a specific x value\n";
    cout << "(c) - coefficient of a term when the term's degree is supplied\n";
    cout << "(r) - reset or restart the process with two new polynomials \n";
    cout << "(q) - quit the program altogether\n";
    cout << " --------------------------------------------------------\n"; 
}

// read from standard input a single word and check if the first
// letter corresponds to 'y' or 'Y' meaning that the answer is yes
// return true if the string read from cin starts with 'y' or 'Y', 
// false otherwise
// when notInteractive is true, the answer read is printed onto standard output
bool yesAnswer(bool notInteractive = false) 
{
   string answerStr;
   cin >> answerStr;
   if (notInteractive) cout << answerStr << "\n";
   return (answerStr[0] == 'Y' || answerStr[0] == 'y');
}

// output to standard output a polynomial with its label
// precondition:
//    the operator << has been overloaded for Polynomial
void printPolynomial(string label, const Polynomial& poly)
{
    cout << label << " = " << poly << "\n";
}

// output to standard output the polynomials a, b and their sum and
// subsequently output to standard output the degrees of the polynomials
// precondition:
//    aPoly, bPoly, sumPoly are bona fide polynomials (possibly the zero polynomial)
void printPolynomials(const Polynomial& aPoly, const Polynomial& bPoly, 
   const Polynomial& sumPoly, Polynomial& aDiffPoly, Polynomial& bDiffPoly,
   Polynomial& sumDiffPoly)
{
    printPolynomial("a", aPoly);
    printPolynomial("b", bPoly);
    printPolynomial("a+b", sumPoly);   
    cout << "degree of a =   " << aPoly.degree() << "\n";
    cout << "degree of b =   " << bPoly.degree() << "\n";
    cout << "degree of a+b = " << sumPoly.degree() << "\n";
    printPolynomial("a'", aDiffPoly);
    printPolynomial("b'", bDiffPoly);
    printPolynomial("(a+b)'", sumDiffPoly);
    cout << "degree of a' =   " << aDiffPoly.degree() << "\n";
    cout << "degree of b' =   " << bDiffPoly.degree() << "\n";
    cout << "degree of (a+b)' = " << sumDiffPoly.degree() << "\n";
}

// output to standard output the number of terms of the 
// polynomials a, b and their sum 
// precondition:
//    aPoly, bPoly, sumPoly are bona fide polynomials (possibly the zero polynomial)
void numberOfTerms(const Polynomial& aPoly, const Polynomial& bPoly, 
   const Polynomial& sumPoly, Polynomial& aDiffPoly, Polynomial& bDiffPoly,
   Polynomial& sumDiffPoly)
{
    cout << aPoly.numberOfTerms() << " term(s) in a = " << aPoly << "\n";
    cout << bPoly.numberOfTerms() << " term(s) in b = " << bPoly << "\n";
    cout << sumPoly.numberOfTerms() << " term(s) in sum = " << sumPoly << "\n";
    cout << aDiffPoly.numberOfTerms() << " term(s) in a' = " << aDiffPoly << "\n";
    cout << bDiffPoly.numberOfTerms() << " term(s) in b' = " << bDiffPoly << "\n";
    cout << sumDiffPoly.numberOfTerms() << " term(s) in sum' = " << sumDiffPoly << "\n";
}

// reads from standard input a command and obtains the first letter of that 
// command to match it to a corresponding value from the enum type Commands
// if notInteractive is true, the read command is echoed to standard output
// postcondition:
//    returns a command from Commands (including INVALID)
Commands getCommand(bool notInteractive)
{
   Commands command;
   cout << "\ninput a command: ";
   string commandStr;
   cin >> commandStr;
   if (notInteractive) cout << commandStr << "\n";  // echo what was read

   char cmd = commandStr[0];
   // if an upper case letter, translate to lower case
   if ('A' <= cmd && cmd <= 'Z') {
      cmd = (cmd - 'A') + 'a';
   }
   switch (cmd) {
      case 'i':
         command = INPUT;
         break;
      case 'p':
         command = PRINT;
         break;
      case 'e':
         command = EVALUATE;
         break;
      case 'c':
         command = GET_COEFF;
         break;
      case 'r':
         command = RESET;
         break;
      case 'n':
         command = NUMBER_OF_TERMS;
         break;
      case 'q':
         command = QUIT;
         break;
      default:
         command = INVALID;
         break;
   } 
   return command;
}

// get the standard input stream cin out of its fail state and clear the buffer
void cinReset()
{
   static const int MAX_CHARACTERS_IN_BUFFER = 250;
   cin.clear();
   cin.ignore(MAX_CHARACTERS_IN_BUFFER, '\n');
}

// read from standard input the info on the first polynomial 
// then read the info on the second polynomial and then compute their sum
// we are assuming error free input in that the number of terms corresponds to
// the "coefficient degree" pairs
// precondition:
//    aPoly, bPoly, sumPoly are the zero polynoials
//    the operator << has been defined for Polynomials
//    reading into a polynomial consists of
//        an integer n for the number of terms
//        coefficient degree pairs n times    
// postcondition: 
//    aPoly, bPoly, sumPoly are bona fide polynomials (with sumPoly being the
//    the sum of aPoly and bPoly)
//    the input stream cin is cleared in case of having read non-numeric input
void inputPolynomials(Polynomial& aPoly, Polynomial& bPoly, Polynomial& sumPoly,
		Polynomial& aDiffPoly, Polynomial& bDiffPoly, Polynomial& sumDiffPoly)
{
   // creates two polynomials by asking the user to enter values
   cout << "for polynomial a, enter # of terms, then enter \"coefficient degree\" pairs: \n";
   cin >> aPoly;
   cout << "for polynomial b, enter # of terms, then enter \"coefficient degree\" pairs: \n";
   cin >> bPoly;
   cinReset();
   sumPoly = aPoly + bPoly;
   aDiffPoly = aPoly.derive();
   bDiffPoly = bPoly.derive();
   sumDiffPoly = sumPoly.derive();
   printPolynomials(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly);
}

// output to standard output the coefficient with a preceeding blurb
void printDegree(string label, int coefficient, int degree)
{
   cout << "in " << label << ", " << coefficient;
   cout << " is the coefficient of the term of degree " << degree << "\n";
}

// read from standard input the degree of the term whose coefficients will
// be printed out for each of the three polynomials
// if notInteractive is true, the read degree is echoed to standard output
// postcondition:
//    the input stream cin is cleared in case of having read non-numeric input
void getCoeffs(const Polynomial& aPoly, const Polynomial& bPoly, 
   const Polynomial& sumPoly, Polynomial& aDiffPoly, Polynomial& bDiffPoly,
	Polynomial& sumDiffPoly, bool notInteractive)
{
   do
   {
      int degree;
      cout << "enter the degree of the term (in each polynomial) whose coefficient you want: ";
      cin >> degree;
      if (notInteractive) cout << degree << "\n";
      printDegree("a", aPoly.coeff(degree), degree);
      printDegree("b", bPoly.coeff(degree), degree);
      printDegree("a+b", sumPoly.coeff(degree), degree);
      printDegree("a'", aDiffPoly.coeff(degree), degree);
      printDegree("b'", bDiffPoly.coeff(degree), degree);
      printDegree("(a+b)'", sumDiffPoly.coeff(degree), degree);
      cout << "get the coefficient of another term? (y/n): ";
   } while (yesAnswer(notInteractive));
   cinReset();
}

// read from standard input the value of x to use in evaluating the polynomials
// evalute a, b and a + b with the given value of x and output the results
// if notInteractive is true, the value read is echoed to standard output
// postcondition:
//    the input stream cin is cleared in case of having read non-numeric input
void evalPolys(const Polynomial& aPoly, const Polynomial& bPoly, 
   const Polynomial& sumPoly, Polynomial& aDiffPoly, Polynomial& bDiffPoly,
	Polynomial& sumDiffPoly, bool notInteractive)
{
   do
   {
      double x;
      cout << "enter the value of x: ";
      cin >> x;
      if (notInteractive) cout << x << "\n";
      cout << "when x = " << x << "\n";
      cout << "a = " << aPoly << " = " << aPoly.evaluate(x) << "\n";
      cout << "b = " << bPoly << " = " << bPoly.evaluate(x) << "\n";
      cout << "a+b = " << sumPoly << " = " << sumPoly.evaluate(x) << "\n";
      cout << "a' = " << aDiffPoly << " = " << aDiffPoly.evaluate(x) << "\n";
      cout << "b' = " << bDiffPoly << " = " << bDiffPoly.evaluate(x) << "\n";
      cout << "(a+b)' = " << sumDiffPoly << " = " << sumDiffPoly.evaluate(x) << "\n";
      cout << "evaluate for another value of x? (y/n) : ";
   } while (yesAnswer(notInteractive));
   cinReset();
}

// process the command 
//   read into aPoly, bPoly and computes sumPoly
//   print aPoly, bPoly and sumPoly
//   evaluate aPoly, bPoly and sumPoly asking the user for the value of x
//   get the coefficients of terms in aPoly, bPoly and sumPoly 
//   get the number of terms in aPoly, bPoly and sumPoly
//   print to standard output if an error was made
// postcondition:
//   return true when the command is RESET or QUIT, returns false otherwise
// 
bool processCommand(Commands command, bool notInteractive,
   Polynomial& aPoly, Polynomial& bPoly, Polynomial& sumPoly,
   Polynomial& aDiffPoly, Polynomial& bDiffPoly, Polynomial& sumDiffPoly)
{   
   bool doneProcessing = false;
   switch (command)
   {
      case INPUT:
         // use the overloaded operator << of Polynomial to enter info
         inputPolynomials(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly);
         break;
      case PRINT:
         // print the three polynomials
         printPolynomials(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly);
         break;
      case EVALUATE:
         // ask the user for the values of x and evaluate the polynomials
         evalPolys(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly, notInteractive);
         break;
      case GET_COEFF:
         // ask the user for the degree of the term whose coefficient will be returned
         getCoeffs(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly, notInteractive);
         break;
      case NUMBER_OF_TERMS:
         // output the number of terms of each polynomial
         numberOfTerms(aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly);
         break;
      case RESET:
         // restart the process eliminating the current two polynomials and sum
         doneProcessing = true;
         break;
      case QUIT:
         // the task is done
         doneProcessing = true;
         break;
      case INVALID:
         cout << "invalid command, please input again!\n";
         break;
      default:
         std::cerr << "**** ERROR in the switch of processCommand ***\n";
         break;
   }
   return doneProcessing;
}

// check if the session is interactive to know whether to echo what is
// read and to know whether the menu command should be printed
// for each pair of polynomials read, do the operations given in the command
// finish once the command is quit
int main()
{
   cout << "Is the session interactive? (y/n) : ";
   bool notInteractive = !yesAnswer();
   Commands cmd;
   do
   {
      if (!notInteractive) printCommandMenu();

      // process two polynomials and their sum at a time 
      bool doneWithThesePolys = false;
      Polynomial aPoly, bPoly, sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly;
      do
      {
         cmd = getCommand(notInteractive);
         doneWithThesePolys = processCommand(cmd, notInteractive, aPoly, bPoly,
        		 sumPoly, aDiffPoly, bDiffPoly, sumDiffPoly);
      } while (!doneWithThesePolys);
      // calls the destructors
      
   } while (cmd != QUIT); 
   return 0;
}
