#ifndef PHYSICS_H
#define PHYSICS_H
#include <cmath>

/*
Definiamo le equazioni e le strutture che ci servono per modellare un urto
elastico e il moto delle palline.

*/
namespace physics {
namespace elastic_collision {
    double my_final_speed(double my_mass, double other_mass, double my_speed0, double other_speed0);

} // namespace elastic_collision
namespace constant_acceleration {
    double space_by_time(double time, double acceleration, double speed0);
}
} // namespace physics

#endif