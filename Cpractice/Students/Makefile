СС = gcc
CFLAGS = -g -Wall

run:
	./students
clean:
	rm -f *.o students

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c -o list.o

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c -o student.o

students: students.c list.o student.o
	$(CC) $(CFLAGS) students.c list.o student.o -o students