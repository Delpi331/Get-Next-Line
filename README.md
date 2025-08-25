# Get Next Line (42) — Lectura de líneas en C

**File reading utility in C that returns one line at a time from a file descriptor, managing internal buffers and memory safely.**

---

## 📌 Resumen

* **Lenguaje:** C (C99)
* **Funcionalidad:** lectura de un archivo **línea a línea**
* **Objetivo:** aprender manejo de memoria dinámica, buffers estáticos, y funciones de bajo nivel (`read`)
* **Restricciones:** no se pueden usar funciones estándar como `fgets`, se trabaja únicamente con **file descriptors**

---

## 🧠 ¿Por qué este proyecto?

Este proyecto de 42 enseña a:

* Usar **`read`** para acceder directamente a archivos y entradas estándar.
* Implementar un sistema de **buffer interno** que guarde los datos leídos hasta completar una línea.
* Trabajar con **memoria dinámica** y punteros para construir cadenas de manera incremental.
* Manejar casos límite: archivos vacíos, saltos de línea al final, o lectura desde stdin.

👉 Elegí este proyecto porque combina **gestión de memoria** con **sistemas de entrada/salida** y es base para futuros proyectos más complejos (ej: `pipex`, `minishell`).

---

## ⚙️ Funcionamiento de Get Next Line

1. Se lee un **bloque fijo** de datos con `read()` (tamaño `BUFFER_SIZE`).
2. Ese bloque se acumula en un **buffer estático** asociado al descriptor de archivo.
3. Cuando se encuentra un `\n` o el final de archivo, se devuelve la **línea completa**.
4. El resto del buffer (lo que está después del `\n`) se conserva para la siguiente llamada.
5. El proceso se repite hasta que no hay más datos.

---

## 🚀 Uso

### Compilación

```bash
make
```

### Ejemplo

```c
int fd = open("archivo.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## 🗂️ Estructura del proyecto

```
get_next_line/
├─ get_next_line.c       # Lógica principal: lectura e iteración
├─ get_next_line_utils.c # Funciones auxiliares (sfree, strnjoin, ft_strlen)
├─ get_next_line.h       # Prototipos y definiciones
├─ Makefile              # Reglas estándar (all, clean, fclean, re)
└─ README.md
```

---

## 🗂️ Explicación del código

### 📌 `get_next_line.c`

* **`clear_buffer()`** → Inicializa el buffer a `\0`, limpiándolo completamente.
* **`get_next_line()`** → Función principal:

  * Valida el descriptor y el `BUFFER_SIZE`.
  * Usa un **buffer estático** para guardar datos entre llamadas.
  * Revisa si ya había datos previos (línea incompleta en buffer).
  * Si encuentra un `\n`, construye la línea con ayuda de `strnjoin`.
  * En bucle, lee con `read()`, copia los caracteres y detiene la lectura cuando se encuentra un salto de línea o fin de archivo.
  * Devuelve un puntero a la línea construida dinámicamente.

📌 **Decisión clave:** El uso de un **buffer estático** permite retener información entre múltiples llamadas sin relecturas innecesarias.

---

### 📌 `get_next_line_utils.c`

* **`ft_strlen()`** → Calcula la longitud de una cadena.
* **`sfree()`** → Libera un puntero (`*a`) y lo sustituye por otro (`b`). Facilita la gestión de memoria.
* **`strnjoin()`** → Concatena dos cadenas (`s1` y `s2`) pero solo hasta `n` caracteres de `s2`. Esto permite construir la línea progresivamente sin desperdiciar memoria.

📌 **Decisión clave:** `sfree` simplifica la sustitución segura de cadenas dinámicas.

---

### 📌 `get_next_line.h`

* Contiene los **prototipos** de funciones y define el `BUFFER_SIZE`.
* Ajusta `BUFFER_SIZE` a 0 si se recibe negativo (prevención de errores).
* Incluye cabeceras estándar necesarias (`unistd.h`, `stdlib.h`, `stdio.h`).

---

### 📌 `Makefile`

* Define las reglas de compilación estándar:

  * `all`: compila la librería/ejecutable
  * `clean`: elimina objetos `.o`
  * `fclean`: elimina objetos y binarios
  * `re`: recompila desde cero

---

## 🧵 Posibles mejoras

* Manejar múltiples **file descriptors** en paralelo (cada uno con su propio buffer).
* Añadir control de errores más detallado (ej. diferenciar EOF de fallo en `read`).
* Mejorar eficiencia evitando limpiezas completas del buffer en cada ciclo.

---

## 🔐 Licencia

MIT — libre para usar y modificar.
