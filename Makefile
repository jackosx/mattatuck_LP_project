libs = `pkg-config --libs opencv` -lopenalpr

program : main.o
	g++ main.o $(libs)
main.o:

clean:
	rm *~
