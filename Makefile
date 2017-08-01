libs = `pkg-config --libs opencv` -lopenalpr -std=c++0x -pthread
objects = main.o src/db.o src/server.o

program : $(objects)
	g++ $(objects) $(libs) -o run 
main.o: src/db.h src/server.h
db.o: db.h
server.o: server.h

clean:
	rm $(objects)
	rm *~
	rm src/*~
