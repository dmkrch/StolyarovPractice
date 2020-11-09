list.o: list.c list.h
	gcc -g -Wall -c list.c -o list.o

student.o: student.c student.h
	gcc -g -Wall -c student.c -o student.o

students: students.c list.o student.o
	gcc -g -Wall students.c list.o student.o -o students
