#ifndef JUGADOR_H
#define JUGADOR_H

#include<codebase.h>
#include "Entorno.h"

class Jugador {
private:
    float posX, posY, posZ;
    float yaw, pitch;
    float roll;
    float objetivoRoll = 0.0f;
    float velocidadInclinacion = 0.0f;

    bool agachado = false;
    float altura_normal = 1.8f;
    float altura_agachado = 0.7f;
    float altura_objetivo = 1.8f; 
    float velocidad_agachado = 0.5f;
    float velocidad_normal = 1.0f;
    float velocidad = velocidad_normal;
    float velocidad_agachar = 2.0f;

    bool saltando = false;
    float salto_posY_inicial = 0.0f;
    float salto_tiempo = 0.0f;
    const float salto_duracion = 1.0f;
    const float salto_altura_max = 1.0f;

public:

    bool noclip = false;
    bool tercera_persona = false;

    Jugador();

    void moverAdelante(float delta, const Entorno& entorno);
    void moverAtras(float delta, const Entorno& entorno);
    void moverDerecha(float delta, const Entorno& entorno);
    void moverIzquierda(float delta, const Entorno& entorno);

    void transportar(float x, float y, float z);
    void transportar(float x, float y, float z, float nuevoYaw, float nuevoPitch);
	void addPosicion(cb::Vec3 pos);


    void girar(float grados, float horizontal);
    void inclinarIzquierda();
    void inclinarDerecha();

    float getRoll() const;
    float getYaw() const;
	float getPitch() const;

    float getSpeed() const;


    float getX() const;
    float getY() const;
    float getZ() const;

    void addVelocidad(float delta);

    void aplicarCamara() const;
    void actualizarInclinacion(float deltaTime);

	void toggleAgacharse();
	void actualizarAgacharse(float deltaTime);
	void iniciarSalto();
    void actualizarSalto(float deltaTime);

    void intentarMover(float dx, float dz, float delta, const Entorno& entorno);

    AABB getAABB() const;

	void togleLight();
	void updateLight();

	void toggleTerceraPersona();

	void renderizarPersonaje();

private:
    static float radians(float grados);
};

#endif
