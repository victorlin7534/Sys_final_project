server: server.o
	gcc -o server server.o
user: user.o 
	gcc -o user user.o
server.o: server.c bat.h
	gcc -c server.c
user.o: user.c bat.h
	gcc -c user.c
bat.o: bat.c bat.h
	gcc -c bat.c
run:
	./run
clean:
	rm -f *o *~ run*
