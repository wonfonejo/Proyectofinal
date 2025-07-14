from cffi import FFI
import ollama

client = ollama.Client()
model = "llama2"

ffi = FFI()

ffi.cdef("""
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

# cargando libreria

C = ffi.dlopen("libfunciones.dll") 



tablero = ffi.new("Tablero *") # Creando una variable tablero
C.Inicializar_tablero(tablero) # usando funciones de c
C.Imprimir_tablero(tablero)



tablero_py = [["--" for _ in range(8)] for _ in range(8)] # creacion tablero python inicializando
 
def actualizar_tablero_py(): #version del tablero para python
    for i in range(8):
        for j in range(8):
            pieza_temporal = tablero.Espacios[i][j] #adquiere los valores del tablero de C 
            if pieza_temporal == ffi.NULL:
                tablero_py[i][j] = "--"
            else:
                pieza = ffi.string(pieza_temporal).decode('utf-8') # convierte los valores del tablero de C a strings en python 
                tablero_py[i][j] = pieza


def tablero_a_string(): # funcion que ollama va a leer
    filas = []
    letras_col = list("abcdefgh")
    for i in range(8):
        fila = f"{i+1} " + "-".join(tablero_py[i])
        filas.append(fila)
    filas.append("  " + " ".join(letras_col))
    return "\n".join(filas)


jugador = C.Jugadores_turno()

while True:
    print(f"Turno del Jugador {jugador}")
    opcion = input("Elegi la opcion: 1-Mover pieza, 2-Reiniciar, 3-Salir, 4-Ollama ")

    if opcion == "1":
        coordenada_py = input("Ingrese la coordenada (ej: a3a2): ")
        coordenada_c = ffi.new("char[]", coordenada_py.encode('utf-8')) # convertir la entrada de python a C

        if C.Mover_pieza(tablero, jugador, coordenada_c, 4):
            jugador = C.Jugadores_turno()
            actualizar_tablero_py()
        C.Imprimir_tablero(tablero)

    elif opcion == "2":
        C.Inicializar_tablero(tablero)
        actualizar_tablero_py()
        C.Imprimir_tablero(tablero)

    elif opcion == "3":
        print("Saliendo del juego...")
        break

    elif opcion == "4":
        actualizar_tablero_py()
        tablero_para_ollama = tablero_a_string()
        print(tablero_para_ollama)
        prompt = f" este es el tablero de ajedrez-> \n \n {tablero_para_ollama} \n \n puedes decirme como esta configurado la piezas van con su nombre y su color ademas puedes darme una buena jugada con el formato a2a3 para el jugador {jugador} el cual jugador 1 es equipo blanca y el 2 equipo negro"

        response = client.generate(model=model, prompt=prompt)
        print("Respuesta de Ollama:")
        print(response['response'])


    else:
        print("Opcion incorrecta")
