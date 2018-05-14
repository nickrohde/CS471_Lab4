#pragma once

#ifndef _TEST_H
#define _TEST_H

#pragma region Includes:
	#include "MasterInclude.hpp"
	#include "Containers.hpp"	 // PSO/FF structs

#pragma endregion

#pragma region Defines:
	#define SHEKEL_OUTER_SIZE 30 // size of outer array used by shekel's foxholes
	#define SHEKEL_INNER_SIZE 10 // size of inner array used by shekel's foxholes
	#define NUMBER_FUNCTIONS  15 // number of cost function

#pragma endregion

#pragma region Typedefs:
	typedef std::function<double(const double*, const std::size_t)> FitnessFunction;
	typedef std::function < Results*(const std::size_t, const FitnessFunction&, const Population_Info&, const Bounds&, const PSO_Info&)> _PSO_;

#pragma endregion

/// <summary>Stores Testing info.</summary>
struct Test_Info
{
#pragma region General Test Info:
	std::size_t	ui_minDim,
				ui_maxDim,
				ui_deltaDim,
				ui_iterations,
				ui_numThreads;

	bool		b_storeData;

#pragma endregion

#pragma region Population Info:
	std::size_t ui_generations,
				ui_popSize;

#pragma endregion

#pragma region PSO Info:
	double		d_PSO_c1,
				d_PSO_c2,
				d_PSO_k;
#pragma endregion

#pragma region FF Info:
#pragma endregion

}; // end Struct Test_Info


/// <summary>Class that handles testing of the optimization strategies.</summary>
class Test
{
#pragma region Public:
public:
	#pragma region Constructors:
		/// <summary>Default constructor, sets all variables to a default.</summary>
		Test(void);

		/// <summary>Constructor taking 4 arguements.</summary>
		/// <param name="ui_dimMin">Starting dimension for tests (inclusive; must be positive integer and strictly smaller than <paramref name="ui_dimMax"/>).</param>
		/// <param name="ui_dimMax">Ending dimension for tests (inclusive; must be positive integer and strictly greater than <paramref name="ui_dimMin"/>).</param>
		/// <param name="ui_dimDelta">Dimension increase step size (must be positive integer).</param>
		/// <param name="b_storeData">Whether or not to generate data files.</param>
		/// <param name="ui_generations">Number of generations to run DE/GA.</param>
		Test(const Test_Info& TEST_INFO);
	#pragma endregion

	#pragma region Destructor:
		/// <summary>Destructor. Frees all dynamic memory beloging to this object.</summary>
		~Test(void);
	#pragma endregion

	#pragma region Test:
			template <typename F, typename ...Args>
			void runTest(F f, Args ...args)
			{
				double* dp_times = new double[((test_info.ui_maxDim - test_info.ui_minDim) / test_info.ui_deltaDim) + 1]; // stores times per iteration for each dimension
				Results** res = new Results*[test_info.ui_iterations];

				for (std::size_t i = 0; i < fitnessFunctions.size(); i++)
				{
					// reset times for new function
					for (std::size_t q = 0; q < ((test_info.ui_maxDim - test_info.ui_minDim) / test_info.ui_deltaDim) + 1; q++)
					{
						dp_times[q] = 0.0;
					} // end for 

					// run tests for all dimensions
					for (std::size_t j = test_info.ui_minDim; j <= test_info.ui_maxDim; j += test_info.ui_deltaDim)
					{
						Population_Info pop_info(test_info.ui_popSize, j, test_info.ui_generations);

						// test each dimension k times
						for (std::size_t k = 0; k < test_info.ui_iterations; k++)
						{
							res[k] = f(test_info.ui_numThreads, fitnessFunctions[i], pop_info, da_ranges[i], args...);
						} // end for k

						// write test data to file
						if (test_info.b_storeData)
						{
							dumpData(const_cast<const Results**>(res), test_info.ui_iterations, test_info.ui_numThreads, makeFileName(j, i));
						} // end if
						else // print solution to console
						{
							double d_solution = getDoubleMax();
							for (std::size_t v = 0; v < test_info.ui_iterations; v++)
							{
								for (std::size_t y = 0; y < test_info.ui_numThreads; y++)
								{
									if (res[v][y].d_bestValue < d_solution)
									{
										d_solution = res[v][y].d_bestValue;
									} // end if
								} // end for y
							} // end for v
							std::cout << "Best solution found for f" << (i + 1) << " in " << j << " dimensions: " << d_solution << std::endl;
						} // end else

						deleteResults(res, test_info.ui_iterations); // delete results from this test
					} // end for j

					writeTimes(dp_times, ((test_info.ui_maxDim - test_info.ui_minDim) / test_info.ui_deltaDim) + 1);
				} // end for i

				delete[] dp_times;
				delete[] res;
			} // end template runTest
	#pragma endregion

#pragma endregion

#pragma region Private:
private:
	#pragma region Private Constants:
		/// <summary>Number of iterations that the shekel's foxhole inner loop will execute.</summary>
		const std::size_t ui_SHEKEL_M = 10;

	#pragma endregion
	
	#pragma region Private Data Members:
		/// <summary>Array containing the bounds of all 15 cost functions.</summary>
		Bounds * da_ranges;

		Test_Info test_info;

		/// <summary>Used for timing tests.</summary>
		timePoint	compute_start,
					compute_end;
		duration	time_to_compute;

		/// <summary>Vector containing pointers to the cost functions.</summary>
		std::vector<FitnessFunction> fitnessFunctions;

	#pragma endregion

	#pragma region Private Methods:
		/// <summary>Generates the matrix for shekel's foxholes.</summary>
		/// <param name="da_A">A valid pointer to an array of 30 uninitialized double pointers.</param>
		/// <remarks>This function is only there to remove some code from the constructor, it is inline and will simply be placed in the constructor by the compiler.</remarks>
		void makeMatrix(double**& da_A);

		/// <summary>Generates the matrix containing the ranges for all cost functions.</summary>
		/// <param name="da_A">A valid pointer to an array of 15 uninitialized double pointers.</param>
		/// <remarks>This function is only there to remove some code from the constructor, it is inline and will simply be placed in the constructor by the compiler.</remarks>
		void makeRanges(Bounds*& da_ranges);


		void dumpData(const Results** res, const std::size_t ui_SIZE_OUTER, std::size_t ui_SIZE_INNNER, const std::string s_NAME);


		void writeTimes(const double* d_TIMES, const size_t ui_SIZE);


		void deleteResults(Results** res, const std::size_t ui_SIZE);


		/// <summary>Generates a file name. Name will be generated as "data_[<paramref name="ui_dim"/>]_f[<paramref name="i_functionNumber"/>]".</summary>
		/// <param name="ui_dim">Dimension to insert into the name.</param>
		/// <param name="i_functionNumber">Function number to insert into the name.</param>
		std::string makeFileName(std::size_t ui_dim, int i_functionNumber);

	#pragma endregion

#pragma endregion

}; // end Class Test

#endif // !_TEST_H
