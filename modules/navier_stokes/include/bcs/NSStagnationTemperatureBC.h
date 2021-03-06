#ifndef NSSTAGNATIONTEMPERATUREBC_H
#define NSSTAGNATIONTEMPERATUREBC_H

#include "NSStagnationBC.h"

// Forward Declarations
class NSStagnationTemperatureBC;


// Specialization required of all user-level Moose objects
template<>
InputParameters validParams<NSStagnationTemperatureBC>();


/**
 * This Dirichlet condition imposes the condition T_0 = T_0_desired,
 * where T_0 is the stagnation temperature, defined as:
 * T_0 = T * (1 + (gam-1)/2 * M^2)
 */
class NSStagnationTemperatureBC : public NSStagnationBC
{
public:
  // Constructor
  NSStagnationTemperatureBC(const std::string & name, InputParameters parameters);

  // Destructor, better be virtual
  virtual ~NSStagnationTemperatureBC(){}

protected:

  // NodalBC's can (currently) only specialize the computeQpResidual function,
  // the computeQpJacobian() function automatically assembles a "1" onto the main
  // diagonal for this DoF.
  virtual Real computeQpResidual();

  // Required paramters
  Real _desired_stagnation_temperature;
};


#endif // NSSTAGNATIONTEMPERATUREBC_H
