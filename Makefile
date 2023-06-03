GXX_FLAGS = -Wall  -Wextra -Wpedantic -Werror
INCLUDE_DIRS = -Isrc
RUN_SOURCES = $(shell find src -name "*.cpp")
RUN_SOURCES_WINDOWS = $(cd src && dir src /b /s "*.cpp" cd && ../)

EXECUTABLE_RUN = sudoku_gen

compile_main:
	@g++ -o $(EXECUTABLE_RUN) $(INCLUDE_DIRS) $(GXX_FLAGS) \
	$(RUN_SOURCES) \
	main.cpp

compile_main_windows:
	@g++ -o $(EXECUTABLE_RUN) $(INCLUDE_DIRS) $(GXX_FLAGS) \
	$(RUN_SOURCES_WINDOWS) \
	main.cpp

run: compile_main
	@./$(EXECUTABLE_RUN)

clear:
	@rm -rf $(EXECUTABLE_RUN)