Makefile:
	It automatically generates two executables: testLList and testMaxList.
	syntax: make all clean.

Executables:
	The first applies several tests to the class LList and generates an output file (output.txt)
	The former tests the maximum number of nodes created before crashing the program. It happened mostly after generating between 60 and 70 million nodes, than it crashed and displayed the result successfully.

Tests:
	This test file is designed to accept two integers as parameters: initial capacity and growth rate. Initial capacity sets the original size of the array, while the growth rate is the ratio of growth for the original array (e.g. 2 makes the array double, 3 makes it triple).
	syntax: testLList
	syntax: testMaxList INITIAL_CAPACITY GROWTH_RATE
	The higher both values are, the fastest the program will crash. But, interestingly, if the growth is too big, the OS kills the task without the proper exception throwing/handling occur. Another interesting observation is that higher values also results is less nodes created, because the contiguous space needed to allocate the new array grows too fast, making the system to throw the bad_alloc exception with too few nodes created.

Crashes:
	Crashes are due to the lack of contiguous space in the heap to create an array. While in the previous assignment, where only nodes were created, we are now demanding an enormous amount of memory to be contiguously allocated. The stack does not play any role in the crashes, since all memory is dynamically allocated in the heap and no exhaustive recursive functions were used.
	The same procedure of turning off window's virtual memory management occurred in order to allow the crash to happen. That limits the heap size to the amount of RAM memory available.

Reflections:
	One possible problem for this assignment is the usage of integers as indexes. If the virtual memory management was on, the system would crash that easily and would probably result in an integer overflow, causing unexpected behavior (int has 32 bits: max is 2,147,483,647). Using long long integer could solve this potential problem (long long has 64 bits: max = 9,223,372,036,854,775,807). But, for that to happen, massive amounts of contiguous memory would have to be available, which is very unlikely to happen.
	To avoid the massive RAM usage, we could use a different data structure to reduce the contiguos space restriction, or to break the array into smaller arrays and to keep track of them.
