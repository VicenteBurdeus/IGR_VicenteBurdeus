#include "Jugador.h"
#include <cmath>

using namespace cb;

Jugador::Jugador()
    : posX(0), posY(1.7f), posZ(0), yaw(0), pitch(0), roll(0), velocidad(1.0f), velocidadInclinacion(0.0f){ 
}


AABB Jugador::getAABB() const {
    const float radio = 0.3f;
    return {
        Vec3(posX - radio, posY,     posZ - radio),
        Vec3(posX + radio, posY + 1.7f, posZ + radio)
    };
}

void Jugador::intentarMover(float dx, float dz, float delta, const Entorno& entorno) {
    float nuevoX = posX + dx * delta * velocidad;
    float nuevoZ = posZ + dz * delta * velocidad;

	if (noclip) {
		// Modo noclip, simplemente actualizar posición
		posX = nuevoX;
		posZ = nuevoZ;
		return;
	}

    AABB nuevaBox = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    if (!entorno.hayColision(nuevaBox)) {
        // Movimiento sin colisión, actualizar posición
        posX = nuevoX;
        posZ = nuevoZ;
        return;
    }

    // Intentar mover solo en X
    nuevoX = posX + dx * delta * velocidad;
    nuevoZ = posZ;  // sin cambio en Z

    AABB boxX = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    if (!entorno.hayColision(boxX)) {
        posX = nuevoX;
        return;
    }

    // Intentar mover solo en Z
    nuevoX = posX;  // sin cambio en X
    nuevoZ = posZ + dz * delta * velocidad;

    AABB boxZ = {
        Vec3(nuevoX - 0.3f, posY, nuevoZ - 0.3f),
        Vec3(nuevoX + 0.3f, posY + 1.7f, nuevoZ + 0.3f)
    };

    if (!entorno.hayColision(boxZ)) {
        posZ = nuevoZ;
    }

    // Si llegamos aquí, colisiona en todos los intentos y no se mueve.
}


void Jugador::moverAdelante(float delta, const Entorno& entorno) {
    float dx = sinf(radians(yaw));
    float dz = cosf(radians(yaw));
    intentarMover(dx, dz, delta, entorno);
}

void Jugador::moverAtras(float delta, const Entorno& entorno) {
    moverAdelante(-delta, entorno);
}

void Jugador::moverDerecha(float delta, const Entorno& entorno) {
    float rad = radians(yaw - 90);
    intentarMover(sinf(rad), cosf(rad), delta, entorno);
}

void Jugador::moverIzquierda(float delta, const Entorno& entorno) {
    float rad = radians(yaw + 90);
    intentarMover(sinf(rad), cosf(rad), delta, entorno);
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


float Jugador::getRoll() const {
    return roll;
}

float Jugador::getYaw() const {
    return yaw;
}

float Jugador::getPitch() const {
	return pitch;
}

float Jugador::getSpeed() const {
	return velocidad;
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
