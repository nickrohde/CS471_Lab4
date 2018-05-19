#pragma once

#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "MasterInclude.hpp"
#include "utility.hpp"

/// <summary>Stores an individual's fitness value.</summary>
struct Fitness
{
	Fitness(void) { d_currentfitness = d_bestFitness = getDoubleMax(); }

	Fitness(double cur, double best) { d_bestFitness = best; d_currentfitness = cur; }

	Fitness(const Fitness& OTHER) { (*this) = OTHER; }

	void operator=(const Fitness& OTHER) { d_currentfitness = OTHER.d_currentfitness; d_bestFitness = OTHER.d_bestFitness; }

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
	Population_Info(void) { ui_size = ui_dim = ui_generations = 0; }

	Population_Info(std::size_t size, std::size_t dim, std::size_t gen) { ui_size = size; ui_dim = dim; ui_generations = gen; }

	Population_Info(const Population_Info& OTHER) { (*this) = OTHER; }

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
	Results(void) { d_bestValue = d_time = getDoubleMax(); }

	Results(double best, double time) { d_bestValue = best; d_time = time; }

	Results(const Results& OTHER) { d_bestValue = OTHER.d_bestValue; d_time = OTHER.d_time; }

	void operator=(const Results& OTHER) { d_bestValue = OTHER.d_bestValue; d_time = OTHER.d_time; }

	/// <summary>Best value found during test.</summary>
	double	d_bestValue,
	/// <summary>Average time for test.</summary>
			d_time;

}; // end Struct results_t


/// <summary>Stores PSO constants.</summary>
struct PSO_Info
{
	PSO_Info(void) { C1 = C2 = K = 0.0; }

	PSO_Info(double c1, double c2, double k) { C1 = c1; C2 = c2; K = k; }

	double C1, C2, K;
}; // end Struct PSO_Info


struct FF_Info
{
	FF_Info(void) {}
	FF_Info(double a, double b, double g, double i) { alpha = a; beta = b; gamma = g; intensity = i; }
	FF_Info(const FF_Info& OTHER) { (*this) = OTHER; }

	double alpha, beta, gamma, intensity;
};


#endif // !_CONTAINER_H
