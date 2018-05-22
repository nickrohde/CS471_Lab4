#pragma once

#ifndef _FF_POP_H
#define _FF_POP_H

#define NORMAL_MEAN 5
#define NORMAL_STD 2


#include "MasterInclude.hpp"
#include "Population.hpp"
#include "Containers.hpp"

/// <summary>Population of fireflies for the firefly algorithm.</summary>
class FF_Population : public Population
{
#pragma region Public:
public:
	#pragma region Constructors:
		/// <summary>Constructs a new firefly population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
		/// <param name="POP_INFO">General Info about the population.</param>
		/// <param name="BOUNDS">The min/max value that may be stored in a gene.</param>
		/// <param name="FF_INFO">Firefly constants.</param>
		FF_Population(const Population_Info& POP_INFO, const Bounds& BOUNDS, const FF_Info& FF_INFO);

		/// <summary>Constructs a new firefly population that is a copy of the firefly population <paramref name="OTHER"/>.</summary>
		/// <param name="OTHER">The population to copy.</param>
		FF_Population(const FF_Population& OTHER);

		/// <summary>Moves the firefly population <paramref name="other"/> into a new firefly population object.</summary>
		/// <param name="other">The population to copy.</param>
		FF_Population(FF_Population&& other) noexcept;

	#pragma endregion

	#pragma region Destructor:
		/// <summary>Releases all dynamic memory owned by this object.</summary>
		~FF_Population(void) noexcept { /* do nothing destructor */ }

	#pragma endregion

	#pragma region Operations:
		/// <summary>Moves firefly <paramref name="k"/> towards firefly <paramref name="j"/>.</summary>
		/// <param name="j">Target firefly.</param>
		/// <param name="k">Firefly moving towards <paramref name="j"/>.</param>
		/// <param name="d_BETA">Beta value for fireflies <paramref name="j"/> and <paramref name="k"/>.</param>
		/// <exception name="std::runtime_error">Thrown if the memory allocation of the population or fitnesses failed.</exception>
		void shiftTowards(const std::size_t j, const std::size_t k, const double d_BETA);

		/// <summary>Determines the euclidean distance between fireflies <paramref name="k"/> and <paramref name="j"/>.</summary>
		/// <param name="j">First firefly.</param>
		/// <param name="k">Second firefly.</param>
		/// <returns>The euclidean distance between fireflies <paramref name="k"/> and <paramref name="j"/> or beta_null if they are in the same location.</returns>
		/// <exception name="std::out_of_range">Thrown if <paramref name="j"/> or <paramref name="k"/> is out of bounds.</exception>
		/// <exception name="std::runtime_error">Thrown if the memory allocation of the population or fitnesses failed.</exception>
		double distance(const std::size_t j, const std::size_t k);

		/// <summary>Determines the light intensity of <paramref name="k"/> at the distance <paramref name="d_DIST"/>.</summary>
		/// <param name="j">The firefly.</param>
		/// <param name="d_DIST">Distance to other firefly.</param>
		/// <returns>The light intensity of firefly <paramref name="j"/> as experienced from distance <paramref name="d_DIST"/>.</returns>
		inline double intensity(const std::size_t j, const double d_DIST) noexcept { return (((worstFitness() - fitness(j)) * d_intensity) / exp(gamma() * pow(d_DIST, 2))); }

	#pragma endregion

	#pragma region Accessors:
		/// <summary>Getter for the alpha value.</summary>
		/// <returns>The values of alpha.</returns>
		inline double alpha(void) noexcept { return d_alpha; }

		/// <summary>Determines the attractiveness at the distance <paramref name="d_DIST"/>.</summary>
		/// <param name="d_DIST">Distance to other firefly.</param>
		/// <returns>The attractiveness at distance <paramref name="d_DIST"/>.</returns>
		inline double beta(const double d_DIST) noexcept 
		{ 
			return (d_beta / exp(gamma() * pow(d_DIST,2))) + 0.2; 
		}

		/// <summary>Getter for the gamma value.</summary>
		/// <returns>Value of gamma.</returns>
		inline double gamma(void) noexcept { return d_gamma; }

	#pragma endregion

	#pragma region Operators:
		/// <summary>Copies the firefly population <paramref name="OTHER"/> into this population.</summary>
		/// <param name="OTHER">Firefly population to copy.</param>
		/// <returns>This object.</returns>
		FF_Population& operator=(const FF_Population& OTHER);

		/// <summary>Moves the firefly population <paramref name="OTHER"/> into this population.</summary>
		/// <param name="other">Firefly population to move.</param>
		/// <returns>This object.</returns>
		FF_Population& operator=(FF_Population&& other) noexcept;

	#pragma endregion

#pragma endregion

#pragma region Private:
private:
	#pragma region Private Data Members:
	double	d_alpha,
			d_beta,
			d_gamma,
			d_intensity;
	#pragma endregion

#pragma endregion
}; // end Class FF_Population
#endif // !_FF_POP_H

