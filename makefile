all:
	gcc -c myFile.c
	gcc -c fs.c
	gcc main.c myFile.o fs.o -o fs