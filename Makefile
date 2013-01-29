dbs: main.o dbs.o 
	g++ -o dbs main.o dbs.o -libpp

main.o: main.c
	g++ -c main.c

dbs.o: dbs.c
	g++ -c dbs.c

clean:
	rm -f *.o dbs
