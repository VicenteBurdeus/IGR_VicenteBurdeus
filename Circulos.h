#pragma once
#include "codebase.h"
#include <vector>
#include <math.h>

vector <cb::Vec3> puntosTecho(cb::Vec3 P1, cb::Vec3 P2, float Radio, int down=1) {
	vector<cb::Vec3> puntos;
	//Encuantra el punto celtral entre P1 y P2 de la circunferencia de Radio Radio
	cb::Vec3 centro = (P1 + P2) * 0.5f;
	//calcula la y del centro de la cercunferencia que esta a radio de distancia de los 2 puntos

	
	centro.y += down * Radio; //down = 1 para abajo, down = -1 para arriba


	return puntos;
}

vector<cb::Vec3> puntosCirculoTecho() {
	cb::Vec3 centro = cb::Vec3(0, 0, -20);
	float radio = 40.0f;
	vector<cb::Vec3> puntos;
	const int n = 10;

	float x_objetivo = 10.0f;
	float y_objetivo = 5.0f;

	// Calcula centro.y para que (x_objetivo, y_objetivo) esté sobre la circunferencia
	centro.y = y_objetivo - sqrtf(radio * radio - x_objetivo * x_objetivo);

	// Ángulo mínimo en que y >= y_objetivo
	float sin_min = (y_objetivo - centro.y) / radio;
	float angle_min = asinf(sin_min);  // en radianes
	float angle_max = PI - angle_min;  // simétrico a la izquierda

	for (int i = 0; i <= n; ++i) {
		float t = (float)i / n;
		float angle = angle_min + (angle_max - angle_min) * t;

		float x = cosf(angle) * radio;
		float y = sinf(angle) * radio + centro.y;

		puntos.emplace_back(x, y, centro.z);
	}

	return puntos;
}
