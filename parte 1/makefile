# Caio Alves Fiorotti
# Matheus Meier Schreiber
# Vinicius Cole de Amorim

all: clean compile run

compile: macaco gorila
	@ gcc -pthread -o prog *.o main.c

run:
	@ ./prog

macaco:
	@ gcc -c macaco.c

gorila:
	@ gcc -c gorila.c

clean:
	@ rm -rf *.o prog
