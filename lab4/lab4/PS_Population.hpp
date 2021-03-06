#pragma once

#ifndef _PSO_POP_H
#define _PSO_POP_H

#include "Population.hpp"

/// <summary>Population of particles for the particle swarm algorithm.</summary>
class PS_Population : public Population
{
#pragma region Public:
public:
	#pragma region Constructors:
		/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
		/// <param name="ui_SIZE">The size of the population.</param>
		/// <param name="ui_DIM">The size of each member of the population.</param>
		/// <param name="bounds">The min/max value that may be stored in a gene.</param>
		PS_Population(const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO);

		/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
		/// <param name="OTHER">The population to copy.</param>
		PS_Population(const PS_Population& OTHER);

		/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
		/// <param name="other">The population to copy.</param>
		PS_Population(PS_Population&& other) noexcept;
	
	#pragma endregion

	#pragma endregion

	#pragma region Operations:
		/// <summary>Updates the velocity of particle <paramref name="i"/>.</summary>
		/// <param name="i">The particle's ID.</param>
		void update(const std::size_t i);

		/// <summary>Updates the fitness of particle <paramref name="i"/>.</summary>
		/// <param name="i">The particle's ID.</param>
		void evaluate(const FitnessFunction& f, const std::size_t i);

	#pragma endregion

#pragma endregion

#pragma region Private:
private:
	#pragma region Private Data Members:
	/// <summary>Velocity matrix.</summary>
	std::vector<std::vector<double>> dp_velocity;

	/// <summary>Constant 1.</summary>
	double		 d_C1,
	/// <summary>Constant 2.</summary>
			 d_C2,
	/// <summary>Velocity matrix.</summary>
			 d_K;

	#pragma endregion

	#pragma region Private methods:
		///<summary>initializes the velocities of all particles to random values.</summary>
		void initializeVelocities(void);

	#pragma endregion

#pragma endregion

}; // end Class PS_Population







#endif // !_PSO_POP_H
