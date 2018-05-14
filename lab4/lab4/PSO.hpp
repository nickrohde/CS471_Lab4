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
/// <param name="res">Out parameter.</param>
Results* _PSO(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO);


/// <summary>Optimizes <paramref name="f"/> using <paramref name="NUM_THREADS"/> particle swarms.</summary>
/// <param name="NUM_THREADS">Number of particle swarms to run in parallel.</param>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the particle population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="PSO_INFO">PSO specific info.</param>
/// <returns>A pointer to a <see cref="Results"/> array of size <paramref name="NUM_THREADS"/> containg the test results.</returns>
void PSO(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const PSO_Info& PSO_INFO);






#endif