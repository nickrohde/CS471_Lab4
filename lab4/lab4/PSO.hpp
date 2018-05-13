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
void _PSO(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO, Results* res);


/// <summary>Optimizes <paramref name="f"/> using <paramref name="NUM_THREADS"/> particle swarms.</summary>
/// <param name="NUM_THREADS">Number of particle swarms to run in parallel.</param>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the particle population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="PSO_INFO">PSO specific info.</param>
/// <returns>A pointer to a <see cref="Results"/> array of size <paramref name="NUM_THREADS"/> containg the test results.</returns>
Results* PSO(const std::size_t NUM_THREADS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO);






#endif