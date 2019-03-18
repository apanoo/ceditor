SRCS=math_test.cpp \

OBJS=$(SRCS:.cpp=.o)
.PHONY: g
g: bo 
	@clang++ -std=c++11 -I$(PWD) -I(PWD)/../core -o $(PWD)/../bin/unit_test $(OBJS)
	@rm *.o

.PHONY: bo
bo:
	@clang++ -std=c++11 -Wall -I$(PWD) -I$(PWD)/../core -c $(SRCS)