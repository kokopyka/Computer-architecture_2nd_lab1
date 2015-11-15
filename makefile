test:
	g++ -std=c++11 -o tests tests.cpp BigNumbers.cpp -lboost_unit_test_framework
	./tests
look:
	g++ -pg -std=c++11 main.cpp BigNumbers.cpp -o profiler
	gprof profiler | less
