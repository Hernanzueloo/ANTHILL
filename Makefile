########################################################################################################
#
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
#
#-------------------------------------------------------------------------------------------------------
# Compilacion durante desarrollo:
# 	%gcc -ansi -pedantic -Wall -o nombre_prog prog.c
# 
# Compilacion para test/depuracion:
#	%gcc -ansi -pedantic -Wall -g -o prog prog.c
# 	valgrind --leak-check=full --track-origins=yes ./prog arg1 ...
# 	ddd ./prog
#	
#	Use --track-origins=yes to see where uninitialised values come from
#
# Compilacion final:
#	%gcc -ansi -pedantic -Wall -O3 -o prog prog.c
#
# -O3 Eficiencia, pero da unos warnings que a veces se pueden omitir
# -g Allows the compiler to collect debugging information
#
# -D Defines preprocessor Macros			#-DNDEBUG turns of asserts mandated by the C standards
# -I se usa para indicar donde se encuentran los ficheros cabeceras (.h), puedes poner más de una -I
# -L indica el directorio donde se encuentra las biblioteca adicionales, puedes poner más de una -L
#-------------------------------------------------------------------------------------------------------
##########################################################################################################


## AUTORES: DAVID BRENCHLEY URIOL - JAVIER SAN ANDRES - DIEGO RODRÍGUEZ - ALEJANDRO GARCÍA

GAME_NAME=ANTHILL

BIN_PATH= ./bin
INC_PATH= ./include
LIB_PATH= ./lib
OBJ_PATH= ./obj
SRC_PATH= ./src || ./tests

VPATH = %.h $(INC_PATH): %.c $(SRC_PATH): %.o $(OBJ_PATH): %.a $(LIB_PATH) #Automatically adds directories in which to look for dependencies
IFLAGS=-I$(INC_PATH)
LDFLAGS=-L$(LIB_PATH)

CC=gcc 
CFLAGS = -std=c17 -pedantic -Wall -g #-DDEBUG 
#CFLAGS = -Wall -g -DNDEBUG #-O3 

LIBS= -lscreen  

Executives = $(GAME_NAME)
OBJECTS = game_loop.o game_management.o graphic_engine.o game.o rule.o object.o player.o enemy.o space.o command.o set.o inventory.o link.o dialogue.o
DIR_OBJECTS= $(patsubst %.o,$(OBJ_PATH)/%.o, $(OBJECTS))

Tests = game_test space_test set_test enemy_test inventory_test player_test object_test link_test command_test game_management_test rule_test dialogue_test
dir_Tests=$(patsubst %,$(BIN_PATH)/%, $(Tests))
TEST_OBJECTS = space_test.o set_tests.o enemy_test.o inventory_test.o link_test.o player_test.o object_test.o game_test.o command_test.o game_management_test.o dialogue_test.o

game_test_objs = game_test.o game.o game_management.o object.o player.o enemy.o space.o command.o set.o inventory.o link.o dialogue.o rule.o
dir_game_test_objs= $(patsubst %.o,$(OBJ_PATH)/%.o, $(game_test_objs))

game_management_test_objs = game_management_test.o game_management.o game.o object.o player.o enemy.o space.o inventory.o set.o dialogue.o command.o link.o rule.o
dir_game_management_test_objs= $(patsubst %.o,$(OBJ_PATH)/%.o, $(game_management_test_objs))

.PHONY: all tests clear clean run run_log runv run_tests run_space_test run_set_test run_enemy_test run_inventory_test run_player_test run_object_test run_command_test run_game_management_test run_link_test run_game_test

## EXECUTIVES CREATION ##
#----------------------------------------------------------------------------------------------------------------------------

all: $(Executives)

tests: $(Tests)


#----------------------------------------------------------------------------------------------------------------------------

#--GAME--
$(GAME_NAME): $(OBJECTS) libscreen.a
	@echo
	@echo ---------CREATING anthill----------------
	$(CC)  -o $@ $(DIR_OBJECTS) $(LDFLAGS) $(LIBS)
	@echo -----------------------------------------


#--LIBSCREEN CREATION--
libscreen.a: libscreen.c libscreen.h
	@echo ---------CREATING libscreen----------------
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(LIB_PATH)/libscreen.o
	ar rcs $(LIB_PATH)/libscreen.a $(LIB_PATH)/libscreen.o
	rm $(LIB_PATH)/libscreen.o


#--TESTS--
game_test: $(game_test_objs)
	@echo
	@echo ---------CREATING game_test--------------
	$(CC) -o $(BIN_PATH)/$@ $(dir_game_test_objs) 
	@echo -----------------------------------------
space_test: space_test.o space.o set.o
	@echo
	@echo ---------CREATING space_test--------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/space_test.o $(OBJ_PATH)/space.o $(OBJ_PATH)/set.o
	@echo -----------------------------------------
set_test: set_test.o set.o
	@echo
	@echo ---------CREATING set_test---------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/set_test.o $(OBJ_PATH)/set.o
	@echo -----------------------------------------
enemy_test: enemy_test.o enemy.o
	@echo
	@echo ---------CREATING enemy_test-------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/enemy_test.o $(OBJ_PATH)/enemy.o
	@echo -----------------------------------------
inventory_test: inventory_test.o inventory.o set.o
	@echo
	@echo -------CREATING inventory_test-----------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/inventory_test.o $(OBJ_PATH)/inventory.o $(OBJ_PATH)/set.o
	@echo -----------------------------------------
link_test: link_test.o link.o
	@echo
	@echo ----------CREATING link_test-------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/link_test.o $(OBJ_PATH)/link.o
	@echo -----------------------------------------
player_test: player_test.o player.o inventory.o set.o
	@echo
	@echo ---------CREATING player_test-------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/player_test.o $(OBJ_PATH)/player.o $(OBJ_PATH)/inventory.o $(OBJ_PATH)/set.o
	@echo ----------------------------------------
object_test: object_test.o object.o
	@echo
	@echo ----------CREATING object_test-------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/object_test.o $(OBJ_PATH)/object.o
	@echo -----------------------------------------
command_test: command_test.o command.o
	@echo
	@echo ----------CREATING command_test-------------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/command_test.o $(OBJ_PATH)/command.o
	@echo -----------------------------------------

game_management_test: $(game_management_test_objs)
	@echo
	@echo ---------CREATING game_management_test----------
	$(CC) -o $(BIN_PATH)/$@ $(dir_game_management_test_objs) 
	@echo -----------------------------------------

rule_test: rule_test.o rule.o
	@echo
	@echo ---------CREATING rule_test----------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/rule_test.o $(OBJ_PATH)/rule.o
	@echo -----------------------------------------

dialogue_test: dialogue_test.o dialogue.o
	@echo
	@echo ---------CREATING dialogue_test----------
	$(CC) -o $(BIN_PATH)/$@ $(OBJ_PATH)/dialogue_test.o $(OBJ_PATH)/dialogue.o
	@echo -----------------------------------------
#----------------------------------------------------------------------------------------------------------------------------



## OBJECTS CREATION ##
#----------------------------------------------------------------------------------------------------------------------------

#----GAME MODULES-----
game_loop.o: game_loop.c graphic_engine.h game.h dialogue.h command.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

game_management.o: game_management.c game_management.h game.h rule.h space.h dialogue.h command.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

graphic_engine.o: graphic_engine.c graphic_engine.h  libscreen.h game.h space.h command.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

game.o: game.c game.h rule.h game_management.h object.h player.h space.h command.h set.h dialogue.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

object.o: object.c object.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

player.o: player.c player.h types.h inventory.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

enemy.o: enemy.c enemy.h  types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

space.o: space.c space.h set.h types.h 
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

set.o: set.c set.h  types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

inventory.o: inventory.c inventory.h set.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

link.o: link.c link.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

command.o: command.c command.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

rule.o: rule.c rule.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

dialogue.o: dialogue.c dialogue.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@
	
#----TEST MODULES-----

game_test.o: game_test.c game_test.h game.h game_management.h object.h player.h space.h command.h set.h dialogue.h types.h test.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

space_test.o: space_test.c space_test.h test.h space.h set.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

set_test.o: set_test.c set_test.h set.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

enemy_test.o: enemy_test.c enemy_test.h enemy.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

inventory_test.o: inventory_test.c  inventory_test.h  inventory.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

link_test.o: link_test.c  link_test.h  link.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

player_test.o: player_test.c player_test.h player.h inventory.h set.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

object_test.o: object_test.c object_test.h object.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

command_test.o: command_test.c command_test.h command.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

game_management_test.o: game_management_test.c game_management_test.h game_management.h game.h dialogue.h object.h player.h enemy.h space.h command.h link.h set.h inventory.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

rule_test.o: rule_test.c rule_test.h rule.h test.h types.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@

dialogue_test.o: dialogue_test.c dialogue_test.h dialogue.h types.h test.h
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ_PATH)/$@
#---------------------------------------------------------------------------------------------------------------------------


### RUN COMMANDS ###

## RUN ejercicio 1 ##
#------------------------------------------------------------------------------------------------------------------------------

#ANTHILL
run:
	./$(Executives) anthillGame.dat

run_debug:
	./$(Executives) anthillGame.dat 2> error.log

run_log:
	./$(Executives) anthillGame.dat -l "fchdatos.log"

run_tut:
	./$(Executives) anthillTut.dat

run_tut_log:
	./$(Executives) anthillTut.dat -l "fchdatosTut.log"



runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(Executives) anthillGame.dat

runv_log:
	valgrind --leak-check=full ./$(Executives) anthillGame.dat -l "fchdatos.log"


#TESTS
run_tests: run_game_test run_space_test run_set_test run_enemy_test run_inventory_test run_player_test run_object_test run_link_test run_command_test run_game_management_test run_rule_test dialogue_test

run_testsv: run_game_testv run_space_testv run_set_testv run_enemy_testv run_inventory_testv run_player_testv run_object_testv run_link_testv run_command_testv run_game_management_testv run_rule_testv dialogue_testv

run_game_test:
	$(BIN_PATH)/game_test
	
run_game_testv:
	valgrind --leak-check=full $(BIN_PATH)/game_test

run_space_test: 
	$(BIN_PATH)/space_test
run_space_testv: 
	valgrind --leak-check=full $(BIN_PATH)/space_test

run_set_test:
	$(BIN_PATH)/set_test
run_set_testv:
	valgrind --leak-check=full $(BIN_PATH)/set_test

run_enemy_test:
	$(BIN_PATH)/enemy_test
run_enemy_testv:
	valgrind --leak-check=full $(BIN_PATH)/enemy_test

run_inventory_test:
	$(BIN_PATH)//inventory_test
run_inventory_testv:
	valgrind --leak-check=full $(BIN_PATH)//inventory_test

run_player_test:
	$(BIN_PATH)/player_test
run_player_testv:
	valgrind --leak-check=full $(BIN_PATH)/player_test

run_object_test:
	$(BIN_PATH)//object_test
run_object_testv:
	valgrind --leak-check=full $(BIN_PATH)//object_test

run_link_test:
	$(BIN_PATH)/link_test
run_link_testv:
	valgrind --leak-check=full $(BIN_PATH)/link_test

run_command_test:
	$(BIN_PATH)/command_test
run_command_testv:
	valgrind --leak-check=full $(BIN_PATH)/command_test

run_game_management_test:
	$(BIN_PATH)/game_management_test
run_game_management_testv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s $(BIN_PATH)/game_management_test

run_rule_test:
	$(BIN_PATH)/rule_test
run_rule_testv:
	valgrind --leak-check=full $(BIN_PATH)/rule_test

run_game_rules_test:
	$(BIN_PATH)/game_rules_test
run_game_rules_testv:
	valgrind --leak-check=full $(BIN_PATH)/game_rules_test

run_dialogue_test:
	$(BIN_PATH)/dialogue_test
run_dialogue_testv:
	valgrind --leak-check=full $(BIN_PATH)/dialogue_test

## DOX GENERATION AND CLEANING ##
#-----------------------------------------------------------------------------------------------------------------------------

dox:
	doxygen doxyfile

#------------------------------------------------------------------------------------------------------------------------------

clean: 
	rm -v $(Executives) $(dir_Tests) $(OBJ_PATH)/*.o

clear_test:
	rm -v $(dir_Tests)

clear:
	rm -v $(Executives)

clean_dox:
	rm -rf doc/html doc/latex

clean_lib:
	rm -v $(LIB_PATH)/*.a
