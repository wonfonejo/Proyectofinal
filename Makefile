
.PHONY: all run clean

all:
	gcc -o libfunciones.dll funciones.c -shared -pipe

run: 
	python juego.py

clean:
	rm -f *.dll *.o
