#include "simulations/sim_circumbinarytrojans.hpp"
#include "simulations/sim_lotofbody.hpp"
#include "simulations/sim_solarsystem.hpp"
#include "simulations/sim_threebody.hpp"

int main()
{
    SolarSystem()->Run();
    return 0;
}