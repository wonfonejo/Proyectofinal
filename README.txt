Este proyecto conecta un motor de ajedrez escrito en C con un modelo de lenguaje (LLM) utilizando Python, CFFI y Ollama.

Esta es una version descartada que quiso seguir lo requerido principalmente por el proyecto, pero la version no pudo conseguir movimientos correctos de la interpretación de LLM del tablero en el sistema de coordenadas requerido de forma completa. Se incluye en el proyecto como intento descartado.
Requisitos

- Python 3.8 o superior
- Compilador C GCC 
- [Ollama](https://ollama.com/) instalado localmente
- Modelo `llama2` descargado con Ollama
- pip

Pasos para ejecutar el codigo


1-Descargar los archivos del repositorio

2-Instalar las dependencies requeridas. En la terminal los siguientes comandos:

pip install -r ollama
pip install -r cffi

paso 3- Compilar el modulo c usando CFFI: siguiente comando en la terminal en la carpeta donde esten guardados los archivos: 

python build_ajedrez.py

4-Ejecutar el programa en la terminal con:

python mcp_ajedrez.py



