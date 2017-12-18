-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
          TEST PLAN - README
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

This file contains all the inputs for the polynomials and the reason why tey were chosen.

All tests are expected to display the expected values for coefficient of a given term, the number of terms in the polynomial, the correct value for the expression for a given x, and the string representation of the polynomial. The lists of expected outputs and actual results are displayed in the files "output.txt", "output_diff.txt", "expected_output.txt" and "expected_output_diff.txt". The list of commands to generate the expected results can be found in "datat.txt".

Only special cases were described in this document. General case behaviour is exactly as described in the Assignment #6 description document.

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  Testing the expected values:
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Test Polynomial
./testPolynomial < datat.txt > output.txt
If running linux, the following commando should give no output:
diff output.txt expected_output.txt

Test Polynomial With Differentiation
./testPolynomialDiff < datat.txt > output_diff.txt
If running linux, the following commando should give no output:
diff output_diff.txt expected_output_diff.txt

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  Input values and their reasons
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
1)
3
1 1
2 2
3 3
3
1 1
-2 2
3 3

Result in a zero coefficient term (x^2) for the sum of a and b. This test checks if the program properly handles it in a new polynomial, removing the zero coefficient term from the resulting polynomial a+b.

2)
5
3 3
6 0
-8 1
1 7
4 4
3
2 6
-4 4
-9 1

Here a zero degree term is inserted and the sum of negative coefficients also take place.

3)
5
1 5
1 8
1 7
1 3
1 4
1
0 0

A term with zero coefficient and term is added.

4)
2
-2 5
2 5
5
2 9
2 7
2 5
-2 3
2 4

Instead of adding a zero-coefficient, zero-degree term, two terms of equal degree whose coefficients sum to zero were added. a should still be a zero-polynomial.

5)
4
8 5
-8 5
-1 3
1 3
1
0 0

Two zero polynomials were created. Degrees are expected to be -1 and coefficients, evaluations, derivatives, and string representations are expected to be 0.

6)
2
2 1
1 0
5
1 9
-2 9
2 5
-2 5
2 4

The second polynomial should result in its highest degree term having a coefficient -1, and should be properly represented as "-x^9". The first polynomial has two terms, one of degree one and another of degree zero to test if the derivative is properly working for these special cases.
