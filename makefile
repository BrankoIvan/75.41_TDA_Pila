CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = main.c pila.c pruebas_alumno.c testing.c
HFILES = pila.h testing.h
EXEC_S = pruebas
PADRON = 102479

build: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

zip:
	zip $(PADRON).zip $(CFILES) $(HFILES)
	
runtime: build
	time ./$(EXEC_S)

clean:
	rm -f *.o $(EXEC_S)

entregar: build
	$(MAKE) run; test $$? -eq 0
	$(MAKE) valgrind; test $$? -eq 0
	$(MAKE) clean
	zip $(PADRON).zip $(CFILES) $(HFILES)
	@echo "Perfecto, no falla ni pierde memoria"
	@echo "El zip esta listo para entregar"

