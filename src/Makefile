CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests.cpp

all: gcov_report

test: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

gcov_report: clean
	g++ -std=c++17 -Wall -Wextra -fprofile-arcs -ftest-coverage tests.cpp -o test -lgtest -lgcov

	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.out *.o *.gcda *.gcno *.info test main
	rm -rf report