#pragma once

#ifndef _POPULATION_H
#define _POPULATION_H

#include "MasterInclude.hpp"
#include "Containers.hpp"
#include "utility.hpp"

/// <summary>Make fitness function type a bit more readable.</summary>
typedef std::function<double(const double*, const std::size_t)> FitnessFunction;

///<summary>Abstract base class that stores the genetic information of a population.</summary>
class Population
{
#pragma region Public:
public:
	#pragma region Constructors:
		/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
		/// <param name="ui_SIZE">The size of the population.</param>
		/// <param name="ui_DIM">The size of each member of the population.</param>
		/// <param name="bounds">The min/max value that may be stored in a gene.</param>
		Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& bounds);

		/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
		/// <param name="other">The population to copy.</param>
		Population(const Population& other);

		/// <summary>Constructs a new population that is a copy of the population <paramref name="other"/>.</summary>
		/// <param name="other">The population to copy.</param>
		Population(Population&& other) noexcept;

	#pragma endregion

	#pragma region Destructor:
		/// <summary>Releases all dynamic memory owned by this object.</summary>
		~Population(void) { deleteContents(); }

	#pragma endregion

	#pragma region Operations:
		/// <summary>Sorts this population in ascending order if it isn't already sorted.</summary>
		void sort(void) noexcept;

		/// <summary>Evaluates the fitness of all members of the population using <paramref name="f"/>.</summary>
		/// <param name="f">The function to determine the fitness of an individual.</param>
		virtual void evaluateAll(const FitnessFunction& f) = 0;

	#pragma endregion

	#pragma region Accessors:
		/// <summary>Accessor for the size of the population.</summary>
		/// <returns>The size of this population.</returns>
		inline std::size_t size(void) const noexcept
		{
			if (isValid())
			{
				return ui_size;
			} // end if

			return 0;
		} // end method size

		/// <summary>Accessor for the best member of the population.</summary>
		/// <returns>Pointer to the start of the best member of the population.</returns>
		/// <exception name="std::runtime_error">Thrown if the memory allocation of the population or fitnesses failed.</exception>
		inline double* best(void)
		{
			if (isValid())
			{
				return dp_pop[ui_bestIndex];
			} // end if

			throw std::runtime_error("Memory allocation failed.");
		} // end method best

		/// <summary>Accessor for the best values for individual <paramref name="j"/>.</summary>
		/// <param name="j">Element to retrieve.</param>
		/// <returns>The best fitness value ever found by the <paramref name="j"/>th individual.</returns>
		/// <exception name="std::runtime_error">Thrown if the memory allocation of the population or fitnesses failed.</exception>
		inline double best(const std::size_t j)
		{
			return best()[j];
		} // end method best

		/// <summary>Accessor for the best member of the population.</summary>
		/// <returns>Pointer to the start of the best member of the population.</returns>
		/// <exception name="std::runtime_error">Thrown if the memory allocation of the population or fitnesses failed.</exception>
		inline double bestFitness(void)
		{
			if (isValid())
			{
				return fitnesses[ui_bestIndex].d_bestFitness;
			} // end if

			throw std::runtime_error("Memory allocation failed.");
		} // end method bestFitness

		/// <summary>Determines whether or not the dynamic memory is valid.</summary>
		/// <returns>True if all memory is properly instantiated, otherwise false.</returns>
		inline bool isValid(void) const noexcept 
		{
			return dp_pop != nullptr && fitnesses != nullptr;
		} // end method isValid

		/// <summary>Accessor for the <paramref name="i"/>th member of the population.</summary>
		/// <param name="i">Member to retrieve.</param>
		/// <returns>Pointer to the <paramref name="i"/>th member of the population.</returns>
		inline double* operator[](const std::size_t i)
		{
			if (isValid())
			{
				if (i < ui_size)
				{
					return dp_pop[i];
				} // end if

				throw std::out_of_range("Index was out of range!");
			} // end if	

			throw std::runtime_error("Memory allocation failed.");
		} // end operator[]

	#pragma endregion

#pragma endregion

#pragma region Protected:
protected:
	#pragma region Data Members:
		/// <summary>Stores whether or not the population is sorted.</summary>
		bool b_isSorted;

		/// <summary>The gene pool of this population.</summary>
		double** dp_pop;

		/// <summary>The fitnesses of population members.</summary>
		Fitness* fitnesses;

		/// <summary>Size of inner arrays of dp_pop and fitnesses.</summary>
		std::size_t ui_length,

		/// <summary>Size of outer array of dp_pop.</summary>
					ui_size,

		/// <summary>Index of the fittests individual.</summary>
					ui_bestIndex;

		/// <summary>Min/max value that a component of the gene can have.</summary>
		Bounds bounds;

	#pragma endregion

	#pragma region Methods:
		///<summary>Instantiates a new matrix with capacity <paramref name="ui_HEIGHT"/> X <paramref name="ui_WIDTH"/>.</summary>
		///<param name="p_arr">The pointer to the array being instantiate, may be <cref see="std::nullptr_t"/>.</param>
		///<param name="ui_HEIGHT">The height capacity.</param>
		///<param name="ui_WIDTH">The width capacity</param>
		void instantiate(double **& dp_arr, const std::size_t ui_HEIGHT, const std::size_t ui_WIDTH);

		///<summary>Sets the fitness of the individual with index <paramref name="j"/> to <paramref name="d_fitness"/></summary>
		///<param name="j">The individual's ID.</param>
		///<param name="d_fitness">The new fitness value.</param>
		void setFitness(const std::size_t j, const double d_fitness);

	#pragma endregion

#pragma endregion

#pragma region Private:
private:
	#pragma region Methods:
		///<summary>initializes a new population with <paramref name="ui_SIZE"/> members, each of length <paramref name="ui_DIM"/>.</summary>
		///<param name="ui_SIZE">Number of members to initialize.</param>
		///<param name="ui_DIM">Number of dimensions.</param>
		void initializePopulation(const std::size_t ui_SIZE, const std::size_t ui_DIM);	

		///<summary>Instantiates a new fitness array with capacity <paramref name="ui_LENGTH"/>.</summary>
		///<param name="p_arr">The pointer to the array being instantiate, may be <cref see="std::nullptr_t"/>.</param>
		///<param name="ui_LENGTH">The number of elements to instantiate.</param>
		void instantiate(Fitness*& p_arr, const std::size_t ui_LENGTH);

		///<summary>Deallocates this population's dynamic memory.</summary>
		void deleteContents(void) noexcept;

	#pragma endregion

#pragma endregion
}; // end Class Population

#endif