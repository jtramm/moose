/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef AUXWAREHOUSE_H
#define AUXWAREHOUSE_H

#include <vector>
#include <map>
#include <string>
#include <list>

#include "AuxKernel.h"


/**
 * Typedef to hide implementation details
 */
typedef std::vector<AuxKernel *>::iterator AuxKernelIterator;


/**
 * Warehouse for storing auxiliary kernels
 *
 * Used inside auxiliary system to store aux. kernels
 */
class AuxWarehouse
{
public:
  AuxWarehouse();
  virtual ~AuxWarehouse();

  // Setup /////
  void initialSetup();
  void timestepSetup();
  void residualSetup();
  void jacobianSetup();

  AuxKernelIterator activeNodalAuxKernelsBegin();
  AuxKernelIterator activeNodalAuxKernelsEnd();

  AuxKernelIterator activeElementAuxKernelsBegin();
  AuxKernelIterator activeElementAuxKernelsEnd();

  AuxKernelIterator activeAuxBCsBegin(unsigned int boundary_id);
  AuxKernelIterator activeAuxBCsEnd(unsigned int boundary_id);

  AuxKernelIterator activeBlockNodalAuxKernelsBegin(unsigned int block);
  AuxKernelIterator activeBlockNodalAuxKernelsEnd(unsigned int block);

  AuxKernelIterator activeBlockElementAuxKernelsBegin(unsigned int block);
  AuxKernelIterator activeBlockElementAuxKernelsEnd(unsigned int block);

  AuxKernelIterator allAuxKernelsBegin();
  AuxKernelIterator allAuxKernelsEnd();

  std::list<AuxKernel *> getActiveNodalKernels();
  std::list<AuxKernel *> getActiveElementKernels();

  void setActiveNodalKernels(std::list<AuxKernel *> &auxs);
  void setActiveElementKernels(std::list<AuxKernel *> &auxs);

  /**
   * Adds a boundary condition
   * @param aux Boundary condition being added
   */
  void addBC(AuxKernel *aux);

  /**
   * Adds a boundary condition aux kernel
   * @param boundary_id Boundary ID this kernel works on
   * @param aux BC kernel being added
   */
  void addActiveBC(unsigned int boundary_id, AuxKernel *aux);

  /**
   * Adds an auxiliary kernel
   * @param aux Kernel being added
   * @param block_ids Set of subdomain this kernel is active on
   */
  void addAuxKernel(AuxKernel *aux, std::set<subdomain_id_type> block_ids);

protected:
  std::vector<AuxKernel *> _active_nodal_aux_kernels;
  std::vector<AuxKernel *> _active_element_aux_kernels;

  std::vector<AuxKernel *> _aux_bcs;
  std::map<unsigned int, std::vector<AuxKernel *> > _active_bcs;
  std::map<unsigned int, std::vector<AuxKernel *> > _active_block_nodal_aux_kernels;
  std::map<unsigned int, std::vector<AuxKernel *> > _active_block_element_aux_kernels;

  std::vector<AuxKernel *> _all_aux_kernels;                                                    /// all aux kernels
};

#endif // AUXWAREHOUSE_H
