
from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    typedef struct {
        char *Espacios[8][8];
    } Tablero;

    extern int i;
    extern int j;
    extern char Cordenada[5];
    extern int Contador;
    extern char *Piezas[12];

    void Inicializar_tablero(Tablero *t);
    void Imprimir_tablero(Tablero *t);
    int convertir_coordenada_fila_en_indice(char valor);
    int convertir_coordenada_columna_en_indice(char valor);
    int Jugadores_turno();
    int Pedir_Coordenadas(char Cordenada[]);
    int Mover_pieza(Tablero *pieza, int Jugador, char *movida, size_t longitud_movida);
""")

ffibuilder.set_source(
    "_ajedrez",  # Nombre del módulo compilado
    '#include "funciones.h"\n#include "funciones.c"',
)

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
