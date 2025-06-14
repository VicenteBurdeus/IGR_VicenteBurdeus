from PIL import Image
import tkinter as tk
from tkinter import filedialog, messagebox
import os

def calcular_color_promedio(imagen):
    imagen = imagen.convert("RGB")
    pixeles = list(imagen.getdata())
    n = len(pixeles)

    suma_r = sum(p[0] for p in pixeles)
    suma_g = sum(p[1] for p in pixeles)
    suma_b = sum(p[2] for p in pixeles)

    promedio = (suma_r // n, suma_g // n, suma_b // n)
    return promedio

def mostrar_resultado_popup(color_rgb, root):
    r, g, b = color_rgb
    hex_color = f"#{r:02x}{g:02x}{b:02x}"
    gl_color = f"glColor3f({r/255:.2f}, {g/255:.2f}, {b/255:.2f})"

    mensaje = (
        f"Color promedio:\n"
        f"RGB: ({r}, {g}, {b})\n"
        f"HEX: {hex_color}\n"
        f"OpenGL: {gl_color}"
    )

    # Ventana emergente con el color como fondo
    ventana = tk.Toplevel(root)
    ventana.title("Color promedio")
    ventana.geometry("300x200")
    ventana.configure(bg=hex_color)

    etiqueta = tk.Label(ventana, text=mensaje, bg=hex_color, fg="white", font=("Arial", 12), justify="left")
    etiqueta.pack(expand=True, padx=10, pady=10)

def main():
    root = tk.Tk()
    root.withdraw()

    ruta_imagen = filedialog.askopenfilename(
        title="Selecciona una imagen",
        filetypes=[("Imágenes", "*.png *.jpg *.jpeg *.bmp")]
    )

    if not ruta_imagen:
        messagebox.showwarning("Aviso", "No se seleccionó ninguna imagen.")
        return

    imagen = Image.open(ruta_imagen)
    color_promedio = calcular_color_promedio(imagen)
    root.deiconify()  # Asegura que root siga activo aunque esté oculto
    mostrar_resultado_popup(color_promedio, root)
    root.mainloop()   # Mantiene el programa activo para mostrar el popup

if __name__ == "__main__":
    main()
