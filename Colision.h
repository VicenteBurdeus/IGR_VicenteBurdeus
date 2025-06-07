#pragma once
#include <algorithm>
#include "codebase.h"
#undef min //<-- Evita errores de compilación causados por definiciones en codebase.h
#undef max //<-- Evita errores de compilación causados por definiciones en codebase.h
struct AABB {
    cb::Vec3 min;
    cb::Vec3 max;

    AABB(const cb::Vec3& a, const cb::Vec3& b) {
		min = cb::Vec3(
			std::min(a.x, b.x),
			std::min(a.y, b.y),
			std::min(a.z, b.z)
		);
		max = cb::Vec3(
			std::max(a.x, b.x),
			std::max(a.y, b.y),
			std::max(a.z, b.z)
		);
    }

    // Verifica si colisiona con otra AABB  
    bool colisionaCon(const AABB& otra) const {
        return (min.x <= otra.max.x && max.x >= otra.min.x) &&
            (min.y <= otra.max.y && max.y >= otra.min.y) &&
            (min.z <= otra.max.z && max.z >= otra.min.z);
    }
};
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))