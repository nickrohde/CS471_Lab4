#pragma once


#ifndef __PSO_H
#define __PSO_H

#include "PS_Population.hpp"
#include "Containers.hpp"


/// <summary>Optimizes <paramref name="f"/> using a particle swarm.</summary>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the particle population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="PSO_INFO">PSO specific info.</param>
/// <returns>A pointer to a <see cref="Results"/> containg the test results.</returns>
Results* _PSO(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO);


/// <summary>Wrapper function for threading PSO.</summary>
/// <param name="NUM_THREADS">Number of particle swarms to run in parallel.</param>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the particle population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="res">Out parameter.</param>
/// <param name="PSO_INFO">PSO specific info.</param>
void PSO(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const PSO_Info& PSO_INFO);






#endif