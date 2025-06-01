struct AABB {  
   cb::Vec3 min;  
   cb::Vec3 max;  

   AABB(const cb::Vec3& min_, const cb::Vec3& max_) {  
       min = min_;  
       max = max_;  
   }  

   // Verifica si colisiona con otra AABB  
   bool colisionaCon(const AABB& otra) const {  
       return (min.x <= otra.max.x && max.x >= otra.min.x) &&  
              (min.y <= otra.max.y && max.y >= otra.min.y) &&  
              (min.z <= otra.max.z && max.z >= otra.min.z);  
   }  
};
