PLAYGROUND_SRC =  src/playground.cpp
PLAYGROUND_SRC += src/playground-mod.c

MY_LIB_SRC = C:/my_lib/my_lib.c

SRC += src/object2d.hpp
SRC += src/sprite.hpp
SRC += src/helpers.hpp
SRC += src/chicken.hpp
SRC += src/structs.hpp
SRC += src/scrollable.hpp
SRC += src/game.hpp

APP_SRC = src/main.cpp
DEBUG_SRC = $(MY_LIB_SRC) src/debug.cpp

TEST_SRC = src/test.test.cpp
FRAME_SRC = src/frame.test.cpp
OBJECT2D_SRC = src/object2d.test.cpp
ANIMATION_SRC = src/animation.test.cpp src/animation.cpp
SPRITE_SRC = src/sprite.test.cpp
SPAWNER_SRC = src/spawner.test.cpp
ANIMATION_SRC = src/animation.hpp src/animation.test.cpp
UTILS_SRC = src/utils.test.cpp
RANDOM_OBJECT_SRC = src/random_object.test.cpp
RANDOM_SPIKE_SRC = src/random_spike.test.cpp
VULTURE_SRC = src/vulture.test.cpp
BIRD_SRC = src/bird.test.cpp
TIMER_SRC = src/timer.test.cpp

CC = g++

INCLUDE_PATHS 	= 	-IC:/mingw_dev_lib/SDL2-2.0.12/i686-w64-mingw32/include/SDL2
INCLUDE_PATHS 	+= 	-IC:/mingw_dev_lib/SDL2_image-2.0.5/i686-w64-mingw32/include/SDL2
INCLUDE_PATHS 	+= 	-IC:/my_lib

LIBRARY_PATHS 	= 	-LC:/mingw_dev_lib/SDL2-2.0.12/i686-w64-mingw32/lib
LIBRARY_PATHS 	+= 	-LC:/mingw_dev_lib/SDL2_image-2.0.5/i686-w64-mingw32/lib

# Source: http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php
# e.g. COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS 	= 	
LINKER_FLAGS 	= 	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image
EXEC_NAME		= 	bin/run

app: $(APP_SRC)
	$(CC) $(APP_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

debug: $(DEBUG_SRC)
	$(CC) $(DEBUG_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/debug

test_frame: $(FRAME_SRC)
	$(CC) $(FRAME_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_object2d: $(OBJECT2D_SRC)
	$(CC) $(OBJECT2D_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_animation: $(ANIMATION_SRC)
	$(CC) $(ANIMATION_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_sprite: $(SPRITE_SRC)
	$(CC) $(SPRITE_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_spawner: $(SPAWNER_SRC)
	$(CC) $(SPAWNER_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_random_object: $(RANDOM_OBJECT_SRC)
	$(CC) $(RANDOM_OBJECT_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_random_spike: $(RANDOM_SPIKE_SRC)
	$(CC) $(RANDOM_SPIKE_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_vulture: $(VULTURE_SRC)
	$(CC) $(VULTURE_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_bird: $(BIRD_SRC)
	$(CC) $(BIRD_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_timer: $(TIMER_SRC)
	$(CC) $(TIMER_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_test: $(TEST_SRC)
	$(CC) $(TEST_SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o bin/test

test_utils: $(UTILS_SRC)
	$(CC) $(UTILS_SRC) -o bin/test

playground: $(PLAYGROUND_SRC)
	$(CC) $(PLAYGROUND_SRC) -o bin/playground

