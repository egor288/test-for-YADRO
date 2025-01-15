all: VisitorController

MSG = ""
TARGET = Linux

ifeq ($(TARGET), Win)
	COMPILER = x86_64-w64-mingw32-g++
  	LDFLAGS = -lws2_32
  	OUTPUT = VisitorController.exe
else ifeq ($(TARGET), Linux)
	COMPILER = clang
  	OUTPUT = VisitorController
endif

VisitorController: src/*.cpp
	@$(COMPILER) -o $(OUTPUT) src/*.cpp $(LDFLAGS)

push:
	git add *.cpp *.h Makefile
	git commit -am "$(MSG)"
	git push
