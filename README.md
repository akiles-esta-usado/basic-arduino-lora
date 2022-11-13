# Arduino + GPS + LoRA


## Dependencias de las bibliotecas

Para evitar conflictos con los pines, se recomienda enlistar cuales son usados y con que periféricos.

| Biblioteca | Periféricos | Pines |
|--|--|--|
| lora.h | Shield LoRA | ? |
| gps.h | GPS externo | 5V, GND, D3, D4 |
| utils.h | Led principal | LED_BUILTIN (13) |


## PlatformIO

Entorno de programación compatible con una gran cantidad de placas de desarrollo.

Extensión: https://platformio.org/install/ide?install=vscode


## Archivo .env

Este archivo es privado, define el entorno de cada participante sin interferir en el de los demás.

Reemplazar `src_dir` con el subproyecto específico.

~~~ ini
[platformio]
src_dir = src/app
~~~