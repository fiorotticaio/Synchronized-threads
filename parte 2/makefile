# Caio Alves Fiorotti
# Matheus Meier Schreiber
# Vinicius Cole de Amorim

all: clean compile run

compile: monitor
	@ gcc -pthread -o prog *.o Funcionarios.c

run:
	@ ./prog

monitor:
	@ gcc -c MonitorBanheiro.c

clean:
	@ rm -rf *.o prog
