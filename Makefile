## Makefile
CCJS=emcc
CC=clang++
BINDIR=bin
DEPBUILD=thirdparty/build
EXECJS=$(BINDIR)/index.js
EXEC=$(BINDIR)/apg
INC= -I$(PWD)/thirdparty/SDL2/include \
	 -I$(PWD)/thirdparty/glad/include \
	 -I$(PWD)/core
DYL= -lSDL2-2.0 \
	 -lglad
LIBS= -L$(PWD)/lib
# SRCS=cpp/main.cpp
SRCS=core/main.cpp \
	#  engine/engine.cpp \
	#  engine/window.cpp

# build cpp to js
.PHONY: build-js
build-js: cf
	$(CCJS) $(SRCS) -std=c++11 -s WASM=1 -s USE_SDL=2 -O3 -o $(EXECJS) -DEMSCRIPTEN $(INC)

OBJS=$(SRCS:.cpp=.o)
# build binary from *.o
# binary needs all *.o files from $(OBJS)
.PHONY: build-cpp
build-cpp: cf $(OBJS)
	$(CC) -std=c++11 -g -o $(EXEC) $(OBJS) ${DYL} ${LIBS}
	rm -rf $(PWD)/cpp/*.o

# auto build *.cpp to *.co one by one
.cpp.o:
	$(CC) -std=c++11 -g -o $@ -c $< -DMYLINUX ${INC}

.PHONY: clean
clean:
	rm -rf $(BINDIR)
	rm -rf $(DEPBUILD)

.PHONY: cf
cf:
	@if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi;

# build dependencies
.PHONY: dep
dep: cfd
	cd $(DEPBUILD) && cmake .. && make && cd -

.PHONY: cfd
cfd:
	@if [ ! -d $(DEPBUILD) ]; then mkdir -p $(DEPBUILD); fi;

.PHONY: run
run: build-cpp
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD)/lib && $(EXEC)

.PHONY: run-js
run-js: build-js build-wes
	$(PWD)/bin/wes

.PHONY: build-wes
build-wes:
	@cd $(PWD)/tools/wes && go build -o ../../bin/wes . && cd -

# install dependencies for ui
.PHONY: dep-ele
dep-ele:
	cd $(PWD)/ui && ELECTRON_MIRROR=https://npm.taobao.org/mirrors/electron/ npm i && cd -	

# run electron
.PHONY: run-ele
run-ele:
	cd $(PWD)/ui && yarn dev && cd -