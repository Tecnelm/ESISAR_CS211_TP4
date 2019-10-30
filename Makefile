main:main.o fonctions.o
	gcc -o $@ $^

test: maintest.o fonctions.o tests.o
	gcc -o $@ $^
maintest.o: main.c fonctions.h tests.h
	gcc -DTEST -c $< -o $@
main.o: main.c fonctions.h
	gcc -c $<
fonctions.o: fonctions.c fonctions.h
	gcc -c $<
tests.o: tests.c tests.h fonctions.h
	gcc -c $<
clean:
	rm -rf *.o main test