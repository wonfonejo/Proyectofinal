#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funciones.h"

int i = 0;
int j = 0;
char Cordenada[5];
int Contador = 0;
char *Piezas[12] = {"PB", "PN", "CB", "CN", "AB", "AN", "TB", "TN", "DB", "DN", "RB", "RN"};


void Inicializar_tablero(Tablero *t)
{

    // Llenar el tablero con piezas o vacíos
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((i == 1)) // Peones blancos
            {
                t->Espacios[i][j] = Piezas[0];
            }
            else if ((i == 6)) // Peones Negros
            {
                t->Espacios[i][j] = Piezas[1];
            }
            else if ((i == 0 && j == 1) || (i == 0 && j == 6)) // Caballos Blancos
            {
                t->Espacios[i][j] = Piezas[2];
            }
            else if (((i == 7 && j == 1) || (i == 7 && j == 6))) // Caballos Negros
            {
                t->Espacios[i][j] = Piezas[3];
            }
            else if ((i == 0 && j == 2) || (i == 0 && j == 5)) // Alfin Blanco
            {
                t->Espacios[i][j] = Piezas[4];
            }
            else if ((i == 7 && j == 2) || (i == 7 && j == 5)) // Alfin Negro
            {
                t->Espacios[i][j] = Piezas[5];
            }
            else if ((i == 0 && j == 0) || (i == 0 && j == 7)) // Torres Blanca
            {
                t->Espacios[i][j] = Piezas[6];
            }

            else if ((i == 7 && j == 0) || (i == 7 && j == 7)) // Torres
            {
                t->Espacios[i][j] = Piezas[7];
            }
            else if ((i == 0 && j == 3)) // Dama Blanca
            {
                t->Espacios[i][j] = Piezas[8];
            }
            else if ((i == 7 && j == 3)) // Dama Negra
            {
                t->Espacios[i][j] = Piezas[9];
            }

            else if ((i == 0 && j == 4)) // Rey Blanco
            {
                t->Espacios[i][j] = Piezas[10];
            }
            else if ((i == 7 && j == 4)) // Rey Negro
            {
                t->Espacios[i][j] = Piezas[11];
            }

            else
            {
                t->Espacios[i][j] = "  "; // Espacio Blanco
            }
        }
    }
}

void Imprimir_tablero(Tablero *t)
{
    
    printf("\n       A    B    C    D    E    F    G    H  \n");
    for (i = 0; i < 8; i++)
    {
        printf("%3d", i + 1);

        printf("  ");

        for (j = 0; j < 8; j++)
        {

            printf("| %s ", t->Espacios[i][j]);
        }
        printf("|");
        printf("\n");
    }
}



int convertir_coordenada_fila_en_indice(char valor)
{
    int indice = -1;
    switch (valor)
    {
    case 'a':
        indice = 0;
        break;
    case 'b':
        indice = 1;
        break;
    case 'c':
        indice = 2;
        break;
    case 'd':
        indice = 3;
        break;
    case 'e':
        indice = 4;
        break;
    case 'f':
        indice = 5;
        break;
    case 'g':
        indice = 6;
        break;
    case 'h':
        indice = 7;
        break;
    }
    return indice;
}

int convertir_coordenada_columna_en_indice(char valor)
{

    if (valor >= '1' && valor <= '8')
    {
        return valor - '1'; 
    }
    return -1; 
}

int Jugadores_turno()
{

    Contador++;
    
    if ((Contador % 2)==0)
    {
    
        return 2;
    }
    else
    {
    
        return 1;
    }
    
    

    
}

int Pedir_Coordenadas(char Cordenada[])
{
    printf("Que piezas quiere mover digita la cordenada (formato ajedrez: a1a2) \n");
    printf("Ingrese movimiento: ");
    scanf("%4s", Cordenada);
    return 1;

}

int Mover_pieza(Tablero *pieza,int Jugador, char *movida ,size_t longitud_movida)
{
    
    

    if (strlen(movida) != longitud_movida)
    {
        printf("Formato incorrecto Debe ser exactamente 4 caracteres como a1a2\n");
        return 0;
    }

    char FilaCordenada1 = movida[0];
    int ColumnaCordenada1 = movida[1];
    char FilaCordenada2 = movida[2];
    int ColumnaCordenada2 = movida[3];

  
    int posicion_2 = convertir_coordenada_fila_en_indice(FilaCordenada1);
    int posicion_1 = convertir_coordenada_columna_en_indice(ColumnaCordenada1);

    int nueva2 = convertir_coordenada_fila_en_indice(FilaCordenada2);
    int nueva1 = convertir_coordenada_columna_en_indice(ColumnaCordenada2);

    if (posicion_1 == -1 || posicion_2 == -1 || nueva1 == -1 || nueva2 == -1)
    {
        printf("Coordenadas Erroneas \n");
        return 0;
    }

    char *valor = pieza->Espacios[posicion_1][posicion_2];
    char *valor2 = pieza->Espacios[nueva1][nueva2];


    if (nueva1 >= 0 && nueva1 < 8 && nueva2 >= 0 && nueva2 < 8)
    {

        if ((strcmp(valor, "PB") == 0) && (Jugador == 1 )) // Peon Blanco
        {
            if (posicion_1 == 1)
            {
                if ((nueva1 == posicion_1 + 2 && nueva2 == posicion_2) || (nueva1 == posicion_1 + 1 && nueva2 == posicion_2))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                if ((strcmp(valor2, "  ") == 0))
                {

                    if ((nueva1 == posicion_1 + 1 && nueva2 == posicion_2))
                    {
                        pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                        pieza->Espacios[posicion_1][posicion_2] = "  ";
                        return 1;
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
                else
                {

                    if ((((nueva1 == posicion_1 + 1) && (nueva2 == posicion_2 + 1)) || ((nueva1 == posicion_1 + 1) && (nueva2 == posicion_2 - 1))))
                    {
                        pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                        pieza->Espacios[posicion_1][posicion_2] = "  ";
                        return 1;
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
            }
        }
        else if ((strcmp(valor, "PN") == 0) && (Jugador ==2 )) // Peon Negro
        {
            if (posicion_1 == 6)
            {
                if ((nueva1 == posicion_1 - 2 && nueva2 == posicion_2) || (nueva1 == posicion_1 - 1 && nueva2 == posicion_2))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                if ((strcmp(valor2, "  ") == 0))
                {

                    if ((nueva1 == posicion_1 - 1 && nueva2 == posicion_2))
                    {
                        pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                        pieza->Espacios[posicion_1][posicion_2] = "  ";
                        return 1;
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
                else
                {

                    if ((((nueva1 == posicion_1 - 1) && (nueva2 == posicion_2 - 1)) || ((nueva1 == posicion_1 - 1) && (nueva2 == posicion_2 + 1))))
                    {
                        pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                        pieza->Espacios[posicion_1][posicion_2] = "  ";
                        return 1;
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
            }
        }
        else if ((strcmp(valor, "CB") == 0) && (Jugador == 1 )) // Caballo Blanco
        {
            if ((strcmp(valor2, "  ") == 0))
            {
                if (((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 + 2)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 + 2)))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else if (valor2[1] == 'N')
            {
                if (((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 + 2)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 + 2)))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                printf("Digite una posicion Correcta para moverla \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "CN") == 0) && (Jugador == 2 ))
        {
            if ((strcmp(valor2, "  ") == 0))
            {
                if (((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 + 2)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 + 2)))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else if (valor2[1] == 'B')
            {
                if (((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 - 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 - 1) && (posicion_2 == nueva2 + 2)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 - 2)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 - 1)) || ((posicion_1 == nueva1 + 2) && (posicion_2 == nueva2 + 1)) || ((posicion_1 == nueva1 + 1) && (posicion_2 == nueva2 + 2)))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                printf("Digite una posicion Correcta para moverla \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "AB") == 0) && (Jugador == 1 ))
        {
            // Verificar que el movimiento sea diagonal
            if (abs(nueva1 - posicion_1) == abs(nueva2 - posicion_2))
            {
                int paso_i = (nueva1 > posicion_1) ? 1 : -1;
                int paso_j = (nueva2 > posicion_2) ? 1 : -1;
                int i, j;
                int camino_limpio = 1;

                // Verificar que no haya piezas en el camino
                for (i = posicion_1 + paso_i, j = posicion_2 + paso_j; i != nueva1; i += paso_i, j += paso_j)
                {
                    if (strcmp(pieza->Espacios[i][j], "  ") != 0)
                    {
                        camino_limpio = 0;
                        break;
                    }
                }

                if (camino_limpio && (strcmp(valor2, "  ") == 0 || valor2[1] == 'N'))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                printf("El alfil solo se mueve en diagonal\n");
                return 0;
            }
        }
        else if ((strcmp(valor, "AN") == 0) && (Jugador == 2 ))
        {
            // Verificar que el movimiento sea diagonal
            if (abs(nueva1 - posicion_1) == abs(nueva2 - posicion_2))
            {
                int paso_i = (nueva1 > posicion_1) ? 1 : -1;
                int paso_j = (nueva2 > posicion_2) ? 1 : -1;
                int i, j;
                int camino_limpio = 1;

                // Verificar que no haya piezas en el camino
                for (i = posicion_1 + paso_i, j = posicion_2 + paso_j; i != nueva1; i += paso_i, j += paso_j)
                {
                    if (strcmp(pieza->Espacios[i][j], "  ") != 0)
                    {
                        camino_limpio = 0;
                        break;
                    }
                }

                if (camino_limpio && (strcmp(valor2, "  ") == 0 || valor2[1] == 'B'))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                printf("El alfil solo se mueve en diagonal\n");
                return 0;
            }
        }
        else if ((strcmp(valor, "TB") == 0) && (Jugador == 1 ))
        {

            if (posicion_1 == nueva1 || posicion_2 == nueva2)
            {
                if (posicion_2 == nueva2)
                {
                    int camino_tapado1 = 0;
                    int pasoi = (nueva1 > posicion_1) ? 1 : -1;
                    for (i = posicion_1 + pasoi; i != nueva1; i += pasoi)
                    {
                        if (strcmp(pieza->Espacios[i][posicion_2], "  ") != 0)
                        {
                            camino_tapado1 = 1;
                            break;
                        }
                    }

                    if (camino_tapado1 == 0)
                    {
                        if (valor2[1] == 'N' && valor[1] == 'B')
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else if (strcmp(valor2, "  ") == 0)
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
                else
                {
                    int camino_tapado = 0;
                    int pasoj = (nueva2 > posicion_2) ? 1 : -1;
                    for (j = posicion_2 + pasoj; j != nueva2; j += pasoj)
                    {
                        if (strcmp(pieza->Espacios[posicion_1][j], "  ") != 0)
                        {
                            camino_tapado = 1;
                            break;
                        }
                    }
                    if (camino_tapado == 0)
                    {
                        if (valor2[1] == 'N')
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else if (strcmp(valor2, "  ") == 0)
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
            }
            else
            {
                printf("Digite una posicion Correcta para moverla \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "TN") == 0) && (Jugador == 2 ))
        {
            if (posicion_1 == nueva1 || posicion_2 == nueva2)
            {
                if (posicion_2 == nueva2)
                {
                    int camino_tapado1 = 0;
                    int pasoi = (nueva1 > posicion_1) ? 1 : -1;
                    for (i = posicion_1 + pasoi; i != nueva1; i += pasoi)
                    {
                        if (strcmp(pieza->Espacios[i][posicion_2], "  ") != 0)
                        {
                            camino_tapado1 = 1;
                            break;
                        }
                    }

                    if (camino_tapado1 == 0)
                    {
                        if (valor2[1] == 'B' && valor[1] == 'N')
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else if (strcmp(valor2, "  ") == 0)
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
                else
                {
                    int camino_tapado = 0;
                    int pasoj = (nueva2 > posicion_2) ? 1 : -1;
                    for (j = posicion_2 + pasoj; j != nueva2; j += pasoj)
                    {
                        if (strcmp(pieza->Espacios[posicion_1][j], "  ") != 0)
                        {
                            camino_tapado = 1;
                            break;
                        }
                    }
                    if (camino_tapado == 0)
                    {
                        if (valor2[1] == 'B')
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else if (strcmp(valor2, "  ") == 0)
                        {
                            pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                            pieza->Espacios[posicion_1][posicion_2] = "  ";
                            return 1;
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        printf("Digite una posicion Correcta para moverla \n");
                        return 0;
                    }
                }
            }
            else
            {
                printf("Digite una posicion Correcta para moverla \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "DB") == 0) && (Jugador == 1 ))
        {
            // Movimiento ALfil

            if (abs(nueva1 - posicion_1) == abs(nueva2 - posicion_2))
            {
                int paso_i = (nueva1 > posicion_1) ? 1 : -1;
                int paso_j = (nueva2 > posicion_2) ? 1 : -1;
                int i, j;
                int camino_limpio = 1;

                // Verificar que no haya piezas en el camino
                for (i = posicion_1 + paso_i, j = posicion_2 + paso_j; i != nueva1; i += paso_i, j += paso_j)
                {
                    if (strcmp(pieza->Espacios[i][j], "  ") != 0)
                    {
                        camino_limpio = 0;
                        break;
                    }
                }

                if (camino_limpio && (strcmp(valor2, "  ") == 0 || valor2[1] == 'N'))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else if (posicion_1 == nueva1 || posicion_2 == nueva2) // Movimiento Torre
            {

                if (posicion_1 == nueva1 || posicion_2 == nueva2)
                {
                    if (posicion_2 == nueva2)
                    {
                        int camino_tapado1 = 0;
                        int pasoi = (nueva1 > posicion_1) ? 1 : -1;
                        for (i = posicion_1 + pasoi; i != nueva1; i += pasoi)
                        {
                            if (strcmp(pieza->Espacios[i][posicion_2], "  ") != 0)
                            {
                                camino_tapado1 = 1;
                                break;
                            }
                        }

                        if (camino_tapado1 == 0)
                        {
                            if (valor2[1] == 'N' && valor[1] == 'B')
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else if (strcmp(valor2, "  ") == 0)
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else
                            {
                                printf("Digite una posicion Correcta para moverla \n");
                                return 0;
                            }
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        int camino_tapado = 0;
                        int pasoj = (nueva2 > posicion_2) ? 1 : -1;
                        for (j = posicion_2 + pasoj; j != nueva2; j += pasoj)
                        {
                            if (strcmp(pieza->Espacios[posicion_1][j], "  ") != 0)
                            {
                                camino_tapado = 1;
                                break;
                            }
                        }
                        if (camino_tapado == 0)
                        {
                            if (valor2[1] == 'N')
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else if (strcmp(valor2, "  ") == 0)
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else
                            {
                                printf("Digite una posicion Correcta para moverla \n");
                                return 0;
                            }
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
        }
        else if ((strcmp(valor, "DN") == 0) && (Jugador == 2 ))
        {

            // Movimiento ALfil

            if (abs(nueva1 - posicion_1) == abs(nueva2 - posicion_2))
            {
                int paso_i = (nueva1 > posicion_1) ? 1 : -1;
                int paso_j = (nueva2 > posicion_2) ? 1 : -1;
                int i, j;
                int camino_limpio = 1;

                // Verificar que no haya piezas en el camino
                for (i = posicion_1 + paso_i, j = posicion_2 + paso_j; i != nueva1; i += paso_i, j += paso_j)
                {
                    if (strcmp(pieza->Espacios[i][j], "  ") != 0)
                    {
                        camino_limpio = 0;
                        break;
                    }
                }

                if (camino_limpio && (strcmp(valor2, "  ") == 0 || valor2[1] == 'B'))
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else if (posicion_1 == nueva1 || posicion_2 == nueva2) // Movimiento Torre
            {

                if (posicion_1 == nueva1 || posicion_2 == nueva2)
                {
                    if (posicion_2 == nueva2)
                    {
                        int camino_tapado1 = 0;
                        int pasoi = (nueva1 > posicion_1) ? 1 : -1;
                        for (i = posicion_1 + pasoi; i != nueva1; i += pasoi)
                        {
                            if (strcmp(pieza->Espacios[i][posicion_2], "  ") != 0)
                            {
                                camino_tapado1 = 1;
                                break;
                            }
                        }

                        if (camino_tapado1 == 0)
                        {
                            if (valor2[1] == 'B' && valor[1] == 'N')
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else if (strcmp(valor2, "  ") == 0)
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else
                            {
                                printf("Digite una posicion Correcta para moverla \n");
                                return 0;
                            }
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                    else
                    {
                        int camino_tapado = 0;
                        int pasoj = (nueva2 > posicion_2) ? 1 : -1;
                        for (j = posicion_2 + pasoj; j != nueva2; j += pasoj)
                        {
                            if (strcmp(pieza->Espacios[posicion_1][j], "  ") != 0)
                            {
                                camino_tapado = 1;
                                break;
                            }
                        }
                        if (camino_tapado == 0)
                        {
                            if (valor2[1] == 'B')
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else if (strcmp(valor2, "  ") == 0)
                            {
                                pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                                pieza->Espacios[posicion_1][posicion_2] = "  ";
                                return 1;
                            }
                            else
                            {
                                printf("Digite una posicion Correcta para moverla \n");
                                return 0;
                            }
                        }
                        else
                        {
                            printf("Digite una posicion Correcta para moverla \n");
                            return 0;
                        }
                    }
                }
                else
                {
                    printf("Digite una posicion Correcta para moverla \n");
                    return 0;
                }
            }
            else
            {
                printf("Digite una posicion Correcta para moverla \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "RB") == 0) && (Jugador == 1 ))
        {
            if ((posicion_1 == nueva1 - 1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 - 1 && posicion_2 == nueva2) || (posicion_1 == nueva1 - 1 && posicion_2 == nueva2 + 1) || (posicion_1 == nueva1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 && posicion_2 == nueva2 + 1) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2 + 1))
            {
                if (strcmp(valor2, "  ") == 0)
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else if (valor2[1] == 'N')
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Eliga correctamente una pieza \n");
                    return 0;
                }
            }
            else
            {
                printf("Eliga correctamente una pieza \n");
                return 0;
            }
        }
        else if ((strcmp(valor, "RN") == 0) && (Jugador == 2 ))
        {
            if ((posicion_1 == nueva1 - 1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 - 1 && posicion_2 == nueva2) || (posicion_1 == nueva1 - 1 && posicion_2 == nueva2 + 1) || (posicion_1 == nueva1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 && posicion_2 == nueva2 + 1) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2 - 1) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2) || (posicion_1 == nueva1 + 1 && posicion_2 == nueva2 + 1))
            {
                if (strcmp(valor2, "  ") == 0)
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else if (valor2[1] == 'B')
                {
                    pieza->Espacios[nueva1][nueva2] = pieza->Espacios[posicion_1][posicion_2];
                    pieza->Espacios[posicion_1][posicion_2] = "  ";
                    return 1;
                }
                else
                {
                    printf("Eliga correctamente una pieza \n");
                    return 0;
                }
            }
            else
            {
                printf("Eliga correctamente una pieza \n");
                return 0;
            }
        }
        else
        {
           if (Jugador==1 && valor[1]== 'N')
            {
                printf("El jugador uno solo puede mover piezas blancas \n");
                return 0;
            }
            else if (Jugador==2 && valor[1]== 'B')
            {    
                printf("El jugador dos solo puede mover piezas Negras \n");
                return 0;
            }
            else
            {
                printf("Tiene que eligir correctamente una pieza \n");
                return 0;
            }
        }
    }
    else
    {
       
        printf("Tiene que eligir correctamente los valores dentro el tablero \n");
        return 0;
    }

    return 0;
}
