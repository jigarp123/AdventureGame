SRC = items.c rooms.c adventure.c
OBJ = items.o rooms.o adventure.o
PROG = adventure

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)
$(OBJ): $(SRC)
