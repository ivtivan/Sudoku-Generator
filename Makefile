GXX_FLAGS = -Wall  -Wextra -Wpedantic -Werror

INCLUDE_DIRS = -Isrc
RUN_SOURCES = $(shell find src -name "*.cpp")
RUN_SOURCES_WINDOWS = $(shell cd src && dir src /b /s "*.cpp" && cd ..)
EXECUTABLE_RUN = sudoku_gen

GTEST_DIR = ../gtest
TESTS = ..
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

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
	@rm -rf $(EXECUTABLE_RUN) $(TESTS) gtest.a gtest_main.a *.o

clear_windows:
	@del $(EXECUTABLE_RUN).exe

# modeled from gtest repo
all_tests : $(TESTS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^