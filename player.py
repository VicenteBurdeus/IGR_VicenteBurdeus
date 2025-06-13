import sys
import pygame

pygame.init()
pygame.mixer.init()

if len(sys.argv) < 2:
    print("Uso: python player.py <archivo>")
    sys.exit(1)

archivo = sys.argv[1]

try:
    pygame.mixer.music.load(archivo)
    pygame.mixer.music.set_volume(0.3)  # volumen al 30%
    pygame.mixer.music.play()
    print("Reproduciendo", archivo)

    # Espera mientras suena
    while pygame.mixer.music.get_busy():
        pygame.time.Clock().tick(10)

except Exception as e:
    print("Error:", e)