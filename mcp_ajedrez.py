import _ajedrez
from _ajedrez import ffi
import ollama
import re
import io
import sys


tablero = ffi.new("Tablero *")
_ajedrez.lib.Inicializar_tablero(tablero)


def capturar_tablero():
    old_stdout = sys.stdout
    sys.stdout = buffer = io.StringIO()
    _ajedrez.lib.Imprimir_tablero(tablero)
    sys.stdout = old_stdout
    return buffer.getvalue()


def mostrar_tablero():
    print("\nEstado actual del tablero:")
    _ajedrez.lib.Imprimir_tablero(tablero)
    print("\n")

def extraer_movimiento(respuesta):
    respuesta = respuesta.strip().lower()
    respuesta = re.sub(r'[^a-h1-8]', '', respuesta)
    if re.fullmatch(r"[a-h][1-8][a-h][1-8]", respuesta):
        if respuesta[0:2] != respuesta[2:4]:
            return respuesta
    return None

jugador_actual = 1
max_turnos = 50
turno = 0
ultimo_movimiento_llm = None
ultimo_resultado_llm = None
movimientos_invalidos_llm = set()

while turno < max_turnos:
    mostrar_tablero()
    print(f"Turno del jugador {jugador_actual}")

    movimiento = None

    if jugador_actual == 1:
        movimiento = input("Ingresa tu movimiento (formato a2a3): ").strip().lower()
        if not re.fullmatch(r"[a-h][1-8][a-h][1-8]", movimiento) or movimiento[0:2] == movimiento[2:4]:
            print("Formato inválido o sin desplazamiento. Intenta de nuevo.\n")
            continue
    else:
        tablero_texto = capturar_tablero()
        resumen_llm = ""
        if ultimo_movimiento_llm:
            resumen_llm = f"\nÚltimo intento: {ultimo_movimiento_llm} → {ultimo_resultado_llm}\n"

        prompt = f"""
Estás jugando una partida de ajedrez controlada por funciones en lenguaje C.
Las reglas son estrictamente determinadas por el código; pueden diferir del ajedrez real.
No tienes acceso a reglas externas ni conocimiento ajeno al código.

TAREA:
- Realiza un movimiento válido para el jugador 2 (negras).
- RESPONDE solo con 4 caracteres exactos: coordenada inicial y final. Ejemplo: "e7e6". Por favor no repitas indefinidamente el ejemplo, interpretalo como la forma en que tienes que modelar tus movimientos segun el tablero.
- No uses comillas, espacios, ni ningún texto adicional.
- Si escribís más de 4 caracteres o un formato inválido, se rechaza el turno.

Estado actual del tablero:
{tablero_texto}
{resumen_llm}
Tu movimiento:
"""

        print(f"\n🧠 Modelo generando jugada...\n")
        respuesta = ollama.generate(
            model="llama2",
            prompt=prompt
        )["response"].strip()

        print("Respuesta del modelo:")
        print(respuesta)

        movimiento = extraer_movimiento(respuesta)
        ultimo_movimiento_llm = respuesta

        if not movimiento or movimiento in movimientos_invalidos_llm:
            print("❌ Movimiento inválido o repetido. Se salta el turno.\n")
            ultimo_resultado_llm = "rechazado"
            movimientos_invalidos_llm.add(respuesta)
            jugador_actual = 1
            turno += 1
            continue

        print(f"🤖 Modelo eligió mover: {movimiento}")

    c_movimiento = ffi.new("char[]", movimiento.encode('utf-8'))
    valido = _ajedrez.lib.Mover_pieza(tablero, jugador_actual, c_movimiento, 4)

    if valido:
        ultimo_resultado_llm = "aceptado"
        jugador_actual = 1 if jugador_actual == 2 else 2
        turno += 1
    else:
        print("❌ Movimiento inválido según la lógica en C.\n")
        if jugador_actual == 2:
            print("⚠️ El modelo falló. Se volverá a intentar en su siguiente turno.\n")
            ultimo_resultado_llm = "rechazado (no permitido por C)"
            movimientos_invalidos_llm.add(movimiento)
        else:
            print("⚠️ Jugador 1 hizo un movimiento inválido. Reintenta.\n")

print("\nFin del juego o máximo de turnos alcanzado.")
