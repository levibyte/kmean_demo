PROGNAME:=kmean-demo
SRCS:=$(wildcard *.cpp) 

INCS:=
FLAGS:=-Wno-narrowing

LIBS+=-lBox2D ./deps/linux/SDL2/libSDL2.a -L ./deps/linux/SDL2_image-2.0.3 -lSDL2_image -L ./deps/linux/SDL2_ttf/libSDL2_ttf.so -lSDL2_ttf -ldl -lrt -pthread 
INCLS+=$(INCS) -I ./deps/linux/SDL2/include -I ./deps/linux/SDL2_image-2.0.3/include -I ./deps/linux/SDL2_ttf/include
OUT=$(PROGNAME).bin

default:
	clear
	rm -f ./bin/$(OUT)  
	mkdir -p ./bin
	g++ -std=c++11 $(SRCS) $(FLAGS) $(INCLS) $(LIBS) -o ./bin/$(OUT)
