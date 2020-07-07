PLAYGROUND_SRC =  src/playground.cpp
PLAYGROUND_SRC += src/playground-mod.c

APP_SRC += src/object2d.hpp
APP_SRC += src/event_handlers.cpp
APP_SRC += src/sprite.hpp
APP_SRC += src/velo.hpp
APP_SRC += src/helpers.cpp
APP_SRC += src/object_manager.hpp
APP_SRC += src/land.hpp
APP_SRC += src/chicken.hpp
APP_SRC += src/obstacle.hpp

DEBUG_SRC = $(APP_SRC) src/main.cpp

OBJECT2D_SRC = src/object2d.test.cpp src/object2d.cpp
ANIMATION_SRC = src/animation.test.cpp src/animation.cpp
SPRITE_SRC = src/sprite.test.cpp src/sprite.cpp
OBJECT_MANAGER_SRC = src/object_manager.test.cpp src/object_manager.hpp src/helpers.cpp src/utils.cpp

CC = g++

INCLUDE_PATHS 	= 	-IC:/mingw_dev_lib/SDL2-2.0.12/i686-w64-mingw32/include/SDL2
INCLUDE_PATHS 	+= 	-IC:/mingw_dev_lib/SDL2_image-2.0.5/i686-w64-mingw32/include/SDL2
LIBRARY_PATHS 	= 	-LC:/mingw_dev_lib/SDL2-2.0.12/i686-w64-mingw32/lib
LIBRARY_PATHS 	+= 	-LC:/mingw_dev_lib/SDL2_image-2.0.5/i686-w64-mingw32/lib

# Source: http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php
# e.g. COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS 	= 	
LINKER_FLAGS 	= 	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
EXEC_NAME		= 	bin/run

debug: $(DEBUG_SRC)
	$(CC) $(DEBUG_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

# app: $(APP_SRC)
# 	$(CC) $(APP_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

test_object2d: $(OBJECT2D_SRC)
	$(CC) $(OBJECT2D_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_animation: $(ANIMATION_SRC)
	$(CC) $(ANIMATION_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_sprite: $(SPRITE_SRC)
	$(CC) $(SPRITE_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_object_manager: $(OBJECT_MANAGER_SRC)
	$(CC) $(OBJECT_MANAGER_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

play: $(PLAYGROUND_SRC)
	$(CC) $(PLAYGROUND_SRC) -o bin/play

play_sdl: 
	$(CC) $(PLAYGROUND_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/play