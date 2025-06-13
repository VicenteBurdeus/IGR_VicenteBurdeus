#ifndef GEAR_H
#define GEAR_H
#pragma once
#include <iostream>
#include <codebase.h>

class Gear
{	
private:
	float R_externo;	//Radio externo
	float R_interno;	//Radio interno
	float R_primitivo;	//Radio primitivo
	int dientes;		//Numero de dientes
	float modulo;		//Modulo de los dientes
	float anguloGiro;	//angulo de giro inicial
	float ancho;		//Profundiad 3D
	cb::Vec3 posicion;	//Posicion del engranaje
	cb::Vec3 color;			//Color del engranaje
	GLuint toothList;	//Lista de un solo diente
	GLuint gearList;		//Lista del engranaje completo
	GLuint inerFill;		//Relleno interior
	GLuint outerFill;	//Relleno exterior
	float RPM;			//Revoluciones por minuto

	void CreateSingleToothList();
	void CreateGearList();
	void CreateFill();

public:
	Gear(float R_externo, float R_interno, float R_primitivo, int dientes, float modulo, float ancho,cb::Vec3 posicion , cb::Vec3 color);
	void setRPM(float RPM);
	void setRotation(float anguloGiro);
	void Draw(float tiempo_transcurrido);
	~Gear() {};
};

#endif
