
OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
INCLUSIONS = Problema.hh Sesion.hh Curso.hh Usuario.hh Plataforma_material.hh Plataforma_usuarios.hh
OBJECTES = Problema.o Sesion.o Curso.o Usuario.o Plataforma_material.o Plataforma_usuarios.o program.o

program.exe: $(OBJECTES)
	g++ -o $@ $(OBJECTES)

%.o : %.cc
	g++ -c $< $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
	rm -f practica.tar
	rm -f *.hh.gch

practica.tar: $(INCLUSIONS) program.exe
	rm -f practica.tar
	tar -cvf $@ *.cc $(INCLUSIONS) Makefile
