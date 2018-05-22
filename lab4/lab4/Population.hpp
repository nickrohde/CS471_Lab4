#pragma once

#ifndef _POPULATION_H
#define _POPULATION_H

#include "MasterInclude.hpp"
#include "Containers.hpp"
#include "utility.hpp"

/// <summary>Make fitness function type a bit more readable.</summary>
typedef std::function<double(const std::vector<double>*)> FitnessFunction;

///<summary>Abstract base class that stores the genetic information of a population.</summary>
class Population
{
#pragma region Public:
public:
	#pragma region Constructors:
		/// <summary>Constructs a new population with <paramref name="ui_SIZE"/> members, each of size <paramref name="ui_DIM"/>.</summary>
		/// <param name="ui_SIZE">The size of the population.</param>
		/// <param name="ui_DIM">The size of each member of the population.</param>
		/// <param name="BOUNDS">The min/max value that may be stored in a gene.</param>
		Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& BOUNDS);

		/// <summary>Constructs a new population that is a copy of the population <paramref name="OTHER"/>.</summary>
		/// <param name="OTHER">The population to copy.</param>
		Population(const Population& OTHER);

		/// <summary>Moves the population <paramref name="other"/> into a new population object.</summary>
		/// <param name="other">The population to copy.</param>
		Population(Population&& other) noexcept;

	#pragma endregion

	#pragma region Operations:
		/// <summary>Sorts this population in ascending order if it isn't already sorted.</summary>
		void sort(void) noexcept;

		/// <summary>Evaluates the fitness of all members of the population using <paramref name="f"/>.</summary>
		/// <param name="F">The function to determine the fitness of an individual.</param>
		void evaluateAll(const FitnessFunction& F);

	#pragma endregion

	#pragma region Accessors:
		/// <summary>Accessor for the size of the population.</summary>
		/// <returns>The size of this population.</returns>
		inline std::size_t size(void) const noexcept
		{
				return ui_size;
		} // end method size

		/// <summary>Accessor for the best member of the population.</summary>
		/// <returns>Pointer to the start of the best member of the population.</returns>
		inline std::vector<double>& best(void) noexcept
		{
			return dp_pop[ui_bestIndex];
		} // end method best

		/// <summary>Accessor for the best values for individual <paramref name="j"/>.</summary>
		/// <param name="j">Element to retrieve.</param>
		/// <returns>The best fitness value ever found by the <paramref name="j"/>th individual.</returns>
		/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is out of bounds.</exception>
		inline double best(const std::size_t j)
		{
			if (j < ui_length)
			{
				return best()[j];
			} // end if

			throw std::out_of_range("Index was out of range!");
		} // end method best

		/// <summary>Accessor for the best member of the population.</summary>
		/// <returns>Fitness of the fittest member of the population.</returns>
		inline double bestFitness(void) noexcept
		{
			if (b_fitnessValid)
			{
				return fitnesses[ui_bestIndex].d_bestFitness;
			} // end if
			else
			{
				return getDoubleMax();
			} // end else
		} // end method bestFitness

		/// <summary>Accessor for the worst member of the population.</summary>
		/// <returns>Fitness of the least fit member of the population.</returns>
		inline double worstFitness(void) noexcept
		{
			if (b_fitnessValid)
			{
				return fitnesses[ui_worstIndex].d_bestFitness;
			} // end if
			else
			{
				#ifdef min // to make the line below work as Windows.h macro min hides the numeric::limits member min
					#undef min 
				#endif
				return std::numeric_limits<double>::min();
				#ifndef min // undo the undef
					#define min(a,b) (a < b) ? (a) : (b)
				#endif
			} // end else

		} // end method worstFitness

		/// <summary>Accessor for the fitness of individual <paramref name="i"/>.</summary>
		/// <param name="i">Element to retrieve.</param>
		/// <returns>The fitness value of individual <paramref name="i"/>.</returns>
		/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is out of bounds.</exception>
		inline double fitness(const std::size_t i) const 
		{
			if (i < ui_size)
			{
				return fitnesses[i].d_currentfitness;
			} // end if

			throw std::out_of_range("Index was out of range!");
		} // end method fitness

	#pragma endregion

	#pragma region Operators:
		/// <summary>Copies the population <paramref name="OTHER"/> into this population.</summary>
		/// <param name="OTHER">Population to copy.</param>
		/// <returns>This object.</returns>
		Population& operator=(const Population& OTHER);

		/// <summary>Moves the population <paramref name="OTHER"/> into this population.</summary>
		/// <param name="OTHER">Population to move.</param>
		/// <returns>This object.</returns>
		Population& operator=(Population&& other) noexcept;

		/// <summary>Accessor for the <paramref name="i"/>th member of the population.</summary>
		/// <param name="i">Member to retrieve.</param>
		/// <returns>Pointer to the <paramref name="i"/>th member of the population.</returns>
		/// <exception name="std::out_of_range">Thrown if <paramref name="i"/> is out of bounds.</exception>
		inline std::vector<double>& operator[](const std::size_t i)
		{
			if (i < ui_size)
			{
				return dp_pop[i];
			} // end if

			throw std::out_of_range("Index was out of range!");
		} // end operator[]

	#pragma endregion

#pragma endregion

#pragma region Protected:
protected:
	#pragma region Data Members:
		/// <summary>Stores whether or not the population is sorted.</summary>
		bool b_isSorted,
			 b_fitnessValid;

		/// <summary>The gene pool of this population.</summary>
		std::vector<std::vector<double>> dp_pop;

		/// <summary>The fitnesses of population members.</summary>
		std::vector<Fitness> fitnesses;

		/// <summary>Size of inner arrays of dp_pop and fitnesses.</summary>
		std::size_t ui_length,

		/// <summary>Size of outer array of dp_pop.</summary>
					ui_size,

		/// <summary>Index of the fittests individual.</summary>
					ui_bestIndex,

		/// <summary>Index of the least fit individual.</summary>
					ui_worstIndex;

		/// <summary>Min/max value that a component of the gene can have.</summary>
		Bounds bounds;

	#pragma endregion

	#pragma region Methods:
		///<summary>Instantiates a new matrix with capacity <paramref name="ui_HEIGHT"/> X <paramref name="ui_WIDTH"/>.</summary>
		///<param name="p_arr">The pointer to the array being instantiate, may be <cref see="std::nullptr_t"/>.</param>
		///<param name="ui_HEIGHT">The height capacity.</param>
		///<param name="ui_WIDTH">The width capacity</param>
		void instantiate(std::vector<std::vector<double>>& p_arr, const std::size_t ui_HEIGHT, const std::size_t ui_WIDTH);

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

	#pragma endregion

#pragma endregion
}; // end Class Population

#endif