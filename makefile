default: server_prep user_prep
server_prep: server.o bat.o
	gcc -o server server.o bat.o
user_prep: user.o bat.o
	gcc -o user user.o bat.o
server.o: server.c bat.h
	gcc -c server.c
user.o: user.c bat.h
	gcc -c user.c
bat.o: bat.c bat.h
	gcc -c bat.c
clean:
	rm -f *o *~ run*
