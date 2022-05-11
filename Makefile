BUILDDIR = .
SOURCEDIR = .
OBJS = $(SOURCEDIR)/Utility.cpp $(SOURCEDIR)/State.cpp $(SOURCEDIR)/Main.cpp $(SOURCEDIR)/Game.cpp $(SOURCEDIR)/PlayersSelectState.cpp $(SOURCEDIR)/SpeedSelectState.cpp $(SOURCEDIR)/InGameState.cpp $(SOURCEDIR)/GameOverState.cpp $(SOURCEDIR)/StateIdentifiers.hpp $(SOURCEDIR)/Paddle.cpp $(SOURCEDIR)/Ball.cpp $(SOURCEDIR)/Player.cpp $(SOURCEDIR)/HumanPlayer.cpp $(SOURCEDIR)/AIPlayer.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ_NAME = $(BUILDDIR)/main

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
