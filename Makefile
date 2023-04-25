build_run_main:
	g++ -std=c++14 -Werror -Wuninitialized -o bin/main src/*.cpp && ./bin/main
