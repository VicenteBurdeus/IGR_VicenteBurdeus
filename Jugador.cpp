#include "Jugador.h"
#include <cmath>
#include <GL/gl.h>    // para glRotatef
#include <GL/glu.h>   // para gluLookAt

Jugador::Jugador()
    : posX(0), posY(1.7f), posZ(0), yaw(0), pitch(0), roll(0), velocidad(1.0f), velocidadInclinacion(0.0f){
    
}

void Jugador::moverAdelante(float delta) {
    posX += delta * velocidad * sinf(radians(yaw));
    posZ += delta * velocidad * cosf(radians(yaw));
}

void Jugador::moverAtras(float delta) {
    moverAdelante(-delta);
}

void Jugador::moverDerecha(float delta) {
    float rad = radians(yaw - 90); // 90° a la izquierda del yaw
    posX += delta * velocidad * sinf(rad);
    posZ += delta * velocidad * cosf(rad);
}

void Jugador::moverIzquierda(float delta) {
    float rad = radians(yaw + 90); // 90° a la derecha del yaw
    posX += delta * velocidad * sinf(rad);
    posZ += delta * velocidad * cosf(rad);
}


void Jugador::transportar(float x, float y, float z) {
    transportar(x, y, z, yaw, pitch);
}

void Jugador::transportar(float x, float y, float z, float nuevoYaw, float nuevoPitch) {
    posX = x;
    posY = y;
    posZ = z;
    yaw = nuevoYaw;
    pitch = nuevoPitch;
}

void Jugador::girar(float vertical,float horizontal) {
    yaw += vertical;
	pitch += horizontal;
    if (yaw >= 360.0f) yaw -= 360.0f;
    else if (yaw < 0) yaw += 360.0f;
	if (pitch >= 89.0f) pitch = 89.0f;
	else if (pitch <= -89.0f) pitch = -89.0f;
}

void Jugador::inclinarIzquierda() {
    if (objetivoRoll == -10.0f) {
        objetivoRoll = 0.0f;
    }
    else {
        objetivoRoll = -10.0f;
    }
    velocidadInclinacion = (objetivoRoll - roll) / 0.25f;
}

void Jugador::inclinarDerecha() {
    if (objetivoRoll == 10.0f) {
        objetivoRoll = 0.0f;
    }
    else {
        objetivoRoll = 10.0f;
    }
    velocidadInclinacion = (objetivoRoll - roll) / 0.25f;
}


float Jugador::getRollRadians() const {
    return radians(roll);
}

float Jugador::getYawRadians() const {
    return radians(yaw);
}

float Jugador::getX() const { return posX; }
float Jugador::getY() const { return posY; }
float Jugador::getZ() const { return posZ; }

void Jugador::addVelocidad(float delta) {
	velocidad += delta;
	if (velocidad < 0.1f) velocidad = 0.1f; // Velocidad mínima
	if (velocidad > 10.0f) velocidad = 10.0f; // Velocidad máxima
}

void Jugador::aplicarCamara() const {
    float dirX = sinf(radians(yaw)) * cosf(radians(pitch));
    float dirY = sinf(radians(pitch));
    float dirZ = cosf(radians(yaw)) * cosf(radians(pitch));

    glRotatef(roll, 0, 0, 1);
    gluLookAt(posX, posY, posZ,
              posX + dirX, posY + dirY, posZ + dirZ,
              0, 1, 0);
}


float Jugador::radians(float grados) {
    return grados * (3.14159265359f / 180.0f);
}

void Jugador::actualizarInclinacion(float deltaTime) {
    if (fabs(objetivoRoll - roll) > 0.01f) {
        roll += velocidadInclinacion * deltaTime;

        // Limita para no pasarse del objetivo
        if ((velocidadInclinacion > 0 && roll > objetivoRoll) ||
            (velocidadInclinacion < 0 && roll < objetivoRoll)) {
            roll = objetivoRoll;
            velocidadInclinacion = 0.0f;
        }
    }
}

void Jugador::toggleAgacharse() {
    agachado = !agachado;
    altura_objetivo = agachado ? altura_agachado : altura_normal;
    velocidad = agachado ? velocidad_agachado : velocidad_normal;
}

void Jugador::actualizarAgacharse(float deltaTime) {
    // Solo actualiza si aún no estamos en la altura objetivo
    if (fabs(posY - altura_objetivo) > 0.01f) {
        float direccion = (altura_objetivo > posY) ? 1.0f : -1.0f;
        posY += direccion * velocidad_agachar * deltaTime;

        // Clamp final
        if ((direccion > 0 && posY > altura_objetivo) || (direccion < 0 && posY < altura_objetivo)) {
            posY = altura_objetivo;
        }
    }
}


void Jugador::iniciarSalto() {
    if (!saltando && !agachado) {
        saltando = true;
        salto_posY_inicial = posY;
        salto_tiempo = 0.0f;
    }
}

void Jugador::actualizarSalto(float deltaTime) {
    if (!saltando) return;

    salto_tiempo += deltaTime;
    if (salto_tiempo > salto_duracion) {
        // Fin del salto
        saltando = false;
        posY = agachado ? altura_agachado : altura_normal;
        return;
    }

    // Movimiento parabólico simple: y = -4h * (t/T - 0.5)^2 + h
    float t = salto_tiempo / salto_duracion;
    float altura_salto = -4.0f * salto_altura_max * (t - 0.5f) * (t - 0.5f) + salto_altura_max;

    posY = (agachado ? altura_agachado : altura_normal) + altura_salto;
}
