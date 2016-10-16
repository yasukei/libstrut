TESTS = libstrut_test

SRCDIR=../src

OBJECTS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))

CXXFLAGS+= -std=c++11
LDFLAGS+= -L$(SRCDIR) -lstrut
CPPFLAGS+= -I$(GTEST_DIR)/include

all: $(TESTS)

test: all
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(SRCDIR) ./$(TESTS)

clean:
	rm -f $(TESTS) $(OBJECTS) gtest.a gtest_main.a

$(TESTS) : $(OBJECTS) gtest_main.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

#FORCE:
#.PHONY: FORCE

#sample1.o : $(USER_DIR)/sample1.cc $(USER_DIR)/sample1.h $(GTEST_HEADERS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.cc
#
#sample1_unittest.o : $(USER_DIR)/sample1_unittest.cc \
#                     $(USER_DIR)/sample1.h $(GTEST_HEADERS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1_unittest.cc
#
#sample1_unittest : sample1.o sample1_unittest.o gtest_main.a
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

include gtest.mk
