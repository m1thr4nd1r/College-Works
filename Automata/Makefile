.SUFFIXES: .cpp .cxx .h

# flags for C++ compiler:
CFLAGS = -O2 -g -Wall

OBJFILES = Estado.o Automato.o main.o

#=====================================

all: trabFormais

trabFormais: $(OBJFILES)
	g++ $(CFLAGS) $(OBJFILES) -o trabFormais

.cpp.o:	$*.h
	g++ -o $*.o -c $*.cpp

clean:
	rm -f *.o trabFormais
