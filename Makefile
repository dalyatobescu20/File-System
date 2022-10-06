build: 
	gcc -Wall -g -o system system.c -std=gnu11

run:
	./system

clean:
	rm -rf system
