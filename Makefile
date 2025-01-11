CC             := @gcc
CXX            := @g++
LIB_SRCS       := $(shell find . -name "*.cpp")
LIB_OBJS       := $(LIB_SRCS:%.cpp=%.o)
LIB_FLAGS			 := -Wl,-rpath=./
LIBS =  -lfmt -lspdlog -lcfmt
CFMTLIB  = libcfmt.so

all: $(CFMTLIB) test

$(CFMTLIB): $(LIB_OBJS)
	$(CXX) -shared -o $@ $^

# Could also use -fPIC, see http://stackoverflow.com/questions/3544035/what-is-the-difference-between-fpic-and-fpic-gcc-parameters
./%.o: ./%.cpp
	$(CXX) -fpic -c $< -o $@

test: test.c
	$(CC) -g -L./ $< -o $@ $(LIB_FLAGS) $(LIBS)


clean:
	rm -f *.o $(CFMTLIB) test


