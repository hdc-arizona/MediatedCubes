CXXFLAGS  = -Wall -Wextra -pedantic -Weffc++ -Werror
CXXFLAGS += -std=c++14
CXXFLAGS += -Isrc
LDLIBS  = -lcrypto++ -ltcmalloc # -lpython2.7 -lboost_python

SRC      = $(wildcard src/*.cpp)
HEADERS  = $(wildcard src/*.h)
OBJ      = $(patsubst %.cpp,%.o,$(SRC))

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(patsubst %.cpp,%.o,$(TEST_SRC))
TEST    = test/main_test

DEPENDS  = $(patsubst src/%,.src.%.d,$(SRC))
DEPENDS += $(patsubst src/%,.src.%.d,$(HEADERS))
DEPENDS += $(patsubst test/%,.test.%.d,$(TEST_SRC))

TARGET   = 

PROGS    = $(patsubst %.cpp,%,$(wildcard bin/*.cpp))

all: $(DEPENDS) $(TARGET) $(PROGS) test


debug: CXXFLAGS += -g -p
debug: all


fast: CXXFLAGS += -O2 -DNDEBUG
fast: all


$(OBJ) : Makefile


$(TARGET): CXXFLAGS += -fPIC -shared
$(TARGET):
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


.PHONY: test
test: $(TEST)
	./$(TEST)
$(TEST): $(TEST_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(PROGS): $(OBJ)

.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJ) $(TEST) $(TEST_OBJ) $(DEPENDS) $(PROGS)


.src.%.d: src/%
	$(CXX) $(CXXFLAGS) -MM $^ > $@
.test.%.d: test/%
	$(CXX) $(CXXFLAGS) -MM $^ > $@


ifneq ($(findstring clean, $(MAKECMDGOALS)),clean)
-include $(DEPENDS)
endif
