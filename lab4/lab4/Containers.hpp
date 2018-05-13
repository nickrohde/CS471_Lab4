#pragma once

#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "MasterInclude.hpp"
#include "utility.hpp"

/// <summary>Stores an individual's fitness value.</summary>
struct Fitness
{
	///<summary>Current fitness value.</summary>
	double d_currentfitness,
	///<summary>Best ever fitness value.</summary>
		   d_bestFitness;

}; // end Struct Fitness


/// <summary>Stores the problem bounds.</summary>
struct Bounds
{
	/// <summary>Default constructor, zeros all members.</summary>
	Bounds(void) noexcept { d_min = d_max = 0.0; }

	/// <summary>Creates a bounds structure with the given upper and lower bounds.</summary>
	/// <param name="min">Lower bound.</param>
	/// <param name="max">Upper bound.</param>
	Bounds(const double min, const double max) noexcept { d_min = min; d_max = max; }

	/// <summary>Copy constructor.</summary>
	/// <param name="OTHER">The Bounds to copy into this.</param>
	Bounds(const Bounds & OTHER) noexcept { (*this) = OTHER; }

	/// <summary>Copy assignment.</summary>
	/// <param name="OTHER">The Bounds to copy into this.</param>
	void operator=(const Bounds & OTHER) noexcept { d_min = OTHER.d_min; d_max = OTHER.d_max; }

	/// <summary>Lower bound.</summary>
	double	d_min, 
	/// <summary>Upper bound.</summary>
			d_max;
}; // end Struct Bounds


/// <summary>Stores the population information.</summary>
struct Population_Info
{
	/// <summary>Size of the population.</summary>
	std::size_t ui_size,

	/// <summary>Gene length for population members.</summary>
				ui_dim,

	/// <summary>Number of generations to run.</summary>
				ui_generations;
}; // end Struct Population Info


/// <summary>Stores results.</summary>
struct Results
{
	/// <summary>Best value found during test.</summary>
	double	d_bestValue,
	/// <summary>Average time for test.</summary>
			d_time;

}; // end Struct results_t


/// <summary>Stores PSO constants.</summary>
struct PSO_Info
{
	double C1, C2, K;
}; // end Struct PSO_Info


#endif // !_CONTAINER_H
