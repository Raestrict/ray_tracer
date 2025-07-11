# Makefile for ray_tracer
#.RECIPEPREFIX := >

CFLAGS := $(shell /opt/homebrew/bin/sdl2-config --cflags)
LDFLAGS := $(shell /opt/homebrew/bin/sdl2-config --libs)

ray_tracer: main.c
	gcc $(CFLAGS) main.c -o $@ $(LDFLAGS)
