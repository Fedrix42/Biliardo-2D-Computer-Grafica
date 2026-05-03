#include "physics.h"

double physics::elastic_collision::my_final_speed(double my_mass, double other_mass, double my_speed0, double other_speed0)
{
    double mdelta = my_mass - other_mass;
    double msum = my_mass + other_mass;
    if (msum == 0) {
        throw "Divide by zero exception";
    }
    return (mdelta / msum) * my_speed0 + ((2 * other_mass) / msum) * other_speed0;
}

double physics::constant_acceleration::space_by_time(double time, double acceleration, double speed0)
{
    return (speed0 * time) + 1 / 2 * acceleration * std::pow(time, 2.0);
}
