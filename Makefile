## Makefile
CCJS=em++
CC=g++
BINDIR=bin
DEPBUILD=$(PWD)/thirdparty/build
EXECJS=$(BINDIR)/wgl.js
EXEC=$(BINDIR)/apg
INC= -I$(PWD)/thirdparty/SDL2/include \
	 -I$(PWD)/thirdparty/glad/include \
	 -I$(PWD)/thirdparty/glm \
	 -I$(PWD)/thirdparty/catch/include \
	 -I$(PWD)/thirdparty/freetype/include \
	 -I$(PWD)/thirdparty/spdlog/include \
	 -I$(PWD)/thirdparty/freetype-gl \
	 -I$(PWD)/thirdparty/imgui-docking \
	 -I$(PWD)/core \
	 -I$(PWD)
DYL= -lSDL2-2.0 \
	 -lglad \
	 -lspdlog
DYLCommon= -lglm_shared \
		   -lfreetype \
		   -lfreetype-gl
LIBS= -L$(PWD)/lib
# SRCS=cpp/main.cpp
SRCS= editor/main-docking.cpp \
	editor/imgui_demo.cpp \
	editor/plot/implot.cpp \
	editor/plot/implot_items.cpp \
	core/logger/log.cpp \
	core/2d/gui/imgui_impl_opengl3.cpp \
	core/2d/gui/imgui_impl_sdl.cpp \
	thirdparty/imgui-docking/imgui.cpp \
	thirdparty/imgui-docking/imgui_draw.cpp \
	thirdparty/imgui-docking/imgui_widgets.cpp

GLMP=$(PWD)/thirdparty/glm
SDLP=$(PWD)/thirdparty/SDL2
FREETYPE=$(PWD)/thirdparty/freetype

# build cpp to js
.PHONY: build-js
build-js: cf
	$(CCJS) $(SRCS) -std=c++11 -s WASM=1 -s USE_SDL=2 -O3 --preload-file assets -o $(EXECJS) -DEMSCRIPTEN $(INC) $(LIBS)

OBJS=$(SRCS:.cpp=.o)
# build binary from *.o
# binary needs all *.o files from $(OBJS)
.PHONY: build-internal
build-internal: cf $(OBJS)
	$(CC) -std=c++11 -g -o $(EXEC) $(OBJS) $(DYL) $(LIBS) $(DYLCommon) ${INC}

.PHONY: build-cpp
build-cpp:
	@rm -rf core/*.o
	@make build-internal

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
	cd $(DEPBUILD) && cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ && make && cd -

.PHONY: cfd
cfd:
	@if [ ! -d $(DEPBUILD) ]; then mkdir -p $(DEPBUILD); fi;
	@if [ ! -f $(GLMP)/CMakeLists.txt ]; then rm -rf $(GLMP) && git submodule init && git submodule update; fi;
	@if [ ! -f $(SDLP)/CMakeLists.txt ]; then rm -rf $(SDLP) && git submodule init && git submodule update; fi;
	@if [ ! -f $(FREETYPE)/CMakeLists.txt ]; then rm -rf $(FREETYPE) && git submodule init && git submodule update; fi;

.PHONY: run
run: build-cpp
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD)/lib && $(PWD)/$(EXEC)

.PHONY: run-js
run-js: build-js build-wes
	cp toolchains/web/index-imgui.html $(BINDIR)/index.html
	cp toolchains/web/favicon.ico $(BINDIR)/favicon.ico
	$(PWD)/bin/wes

.PHONY: start-js
start-js:
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

# ================== unit test================= # 
TSRCS=$(PWD)/test/math_test.cpp \

TOBJS=$(TSRCS:.cpp=.o)
.PHONY: test
test: $(TOBJS)
	@$(CC) -std=c++11 -I$(PWD)/test $(INC) -o $(PWD)/bin/unit_test $(TOBJS)
	@rm $(PWD)/test/*.o
	@$(PWD)/bin/unit_test
