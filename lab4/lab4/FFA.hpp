#pragma once

#ifndef _FFA_H
#define _FFA_H

#include "MasterInclude.hpp"
#include "Containers.hpp"
#include "FF_Population.hpp"


/// <summary>Optimizes <paramref name="f"/> using the firefly algorithm.</summary>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the firefly population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="FF_INFO">Firefly algorithm specific info.</param>
/// <returns>A pointer to a <see cref="Results"/> containg the test results.</returns>
Results* _FFA(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const FF_Info& FF_INFO);


/// <summary>Wrapper function for threading the firefly algorithm.</summary>
/// <param name="NUM_THREADS">Number of particle swarms to run in parallel.</param>
/// <param name="f">Function to optimize.</param>
/// <param name="POP_INFO">Info pertaining to the firefly population.</param>
/// <param name="BOUNDS">The problem bounds of <paramref name="f"/>.</param>
/// <param name="res">Out parameter.</param>
/// <param name="FF_INFO">Firefly algorithm specific info.</param>
void FFA(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const FF_Info& FF_INFO);


#endif // !_FFA_H
