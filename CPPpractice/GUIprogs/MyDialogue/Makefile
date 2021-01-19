CXX = g++
CXXFLAGS = -g -Wall

run:
	./DialogueServer
clean:
	rm -f *.o DialogueServer

GUI.o: GUI.cpp GUI.h
	$(CXX) $(CXXFLAGS) -c GUI.cpp -o GUI.o

DialogueServer: main.cpp GUI.o
	$(CXX) $(CXXFLAGS) main.cpp -lfltk GUI.o -o DialogueServer