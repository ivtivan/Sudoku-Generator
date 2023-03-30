GXX_FLAGS = -Wall  -Wextra -Wpedantic -Werror
INCLUDE_DIRS = -Isrc
RUN_SOURCES = $(shell find src -name "*.cpp")

EXECUTABLE_RUN = sudoku_gen

compile_main:
	@g++ -o $(EXECUTABLE_RUN) $(INCLUDE_DIRS) $(GXX_FsLAGS)\
	$(RUN_SOURCES) \
	main.cpp

run: compile_main
	@./$(EXECUTABLE_RUN)

clear:
	@rm -rf $(EXECUTABLE_RUN)