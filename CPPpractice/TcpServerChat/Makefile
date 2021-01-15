CXX = g++
CXXFLAGS = -g -Wall

run:
	./Chat
clean:
	rm -f *.o Chat

FdHandler.o: FdHandler.cpp FdHandler.h
	$(CXX) $(CXXFLAGS) -c FdHandler.cpp -o FdHandler.o

EventSelector.o: EventSelector.cpp EventSelector.h
	$(CXX) $(CXXFLAGS) -c EventSelector.cpp -o EventSelector.o
	
ChatServer.o: ChatServer.cpp ChatServer.h
	$(CXX) $(CXXFLAGS) -c ChatServer.cpp -o ChatServer.o

Chat: main.cpp FdHandler.o EventSelector.o ChatServer.o
	$(CXX) $(CXXFLAGS) main.cpp FdHandler.o EventSelector.o ChatServer.o -o Chat