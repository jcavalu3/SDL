# Makefile for CPU project
CXX = g++ $(CFLAGS) $(OPTS) $(INC)
INC = -I include/
CFLAGS = -g -Wall 
LIBS = -lSDL -lSDL_image
OPTS =
DEBUG = 
OBJ = main.o dirt.o
LIBRARIES = 
BIN = game  

default: game

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: $(BIN)

game: $(COMPONENTS) $(LIBRARIES) $(OBJ)
	@echo "*****************************************************"
	@echo "*** Building $(BIN)"
	@echo "*****************************************************"
	$(CXX) $(CFLAGS) -o $(BIN) $(OBJ) $(LIBS)
	@echo

copy:
	mkdir -p ~/src/sysprog/game
	cp -av /var/public/sysprog/eoce/spring2013/game/* ~/src/sysprog/game/

help:
	@echo
	@echo "**************************[ EoCE Game ]*********************************"
	@echo "** CSCS2730 Systems Programming                  Spring 2013 Semester **"
	@echo "**                                                                    **"
	@echo "** This is the Makefile to handle many of the clerical tasks of the   **"
	@echo "** code. Please use one of the available options listed:              **"
	@echo "**                                                                    **"
	@echo "** make                     - build game binary                       **"
	@echo "**                                                                    **"
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "** make copy                - make a copy of the code to your dir     **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
	@echo

clean:
	rm -f *.o $(BIN) core
