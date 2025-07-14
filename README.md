# Proyectofinal
# Descripción

Este proyecto consiste en un juego de ajedrez realizado en C, que se integró a un modelo de lenguaje (LLM), todo esto utilizando a Python como un puente entre la LLM y nuestro código, ya Python es capaz de interactuar con la LLM y mediante CFFI es capaz de interactuar con el código en C, todo esto usando una MCP que funciona como organizador de todas estas partes. 

# Requisitos. 
Los elementos necesarios para poder utilizar este proyecto son: 
-C: Código base donde se encuentra toda la lógica del juego. 
-Python: Interfaz entre la LLM y C.
-CFFI: Conexión de Python con C. 
-Ollama: Plataforma que permite ejecutar la LLM llama2. 
-MCP: Mecanismo de control de procesos. 

# Instalación. 
* Paso 1: 
Descargar todos los archivos necesarios del programa:
-Makefile.
-funciones.c
-funciones.h
-juego.py
-linfunciones.dll

* Paso 2: 
Asegurarse de tener las herramientas básicas necesarias de cada lenguaje, en este caso, el CFFI. Para Windows puede ser útil usar “pip install cffi”.  
En el caso de Linux, primero instala los paquetes necesarios para compilar extensiones en C, puede ser útil “sudo apt install build-essential python3-dev” luego instala cffi con “pip install cffi” o “pip3 install cffi”.

* Paso 3:
Instalar la LLM, para esto si estás en Windows busca en tu navegador https://ollama.com/ luego puedes verificar que esté instalado con “ollama --version” y por último descarga y corre llama2 con “ollama run llama2”.
Para Linux sigue los mismos pasos, puedes cambiar el primer paso y hacerlo directamente desde la terminal usando “curl -fsSL https://ollama.com/install.sh | sh”

* Paso 4: 

Proyecto Final-Plataformas.
