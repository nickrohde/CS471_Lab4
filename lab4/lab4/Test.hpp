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
	typedef std::function<double(const std::vector<double>*)> FitnessFunction;
	typedef std::function<void(const std::size_t, const FitnessFunction&, const Population_Info&, const Bounds&, Results*, const PSO_Info&)> _PSO_;
	typedef std::function<void(const std::size_t, const FitnessFunction&, const Population_Info&, const Bounds&, Results*, const FF_Info&)> _FFA_;

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

	std::string s_filePreFix;

#pragma endregion

#pragma region Population Info:
	std::size_t ui_generations,
				ui_popSize;

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

		/// <summary>Constructor taking a <see cref="Test_Info"/> object containing test settings.</summary>
		/// <param name="TEST_INFO">Structure containing all test settings.</param>
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

				Results** res = new Results*[test_info.ui_numThreads];

				auto threads = std::vector<std::thread>(test_info.ui_numThreads);

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
						if (i == 14 && j > 10) continue;

						Population_Info pop_info(test_info.ui_popSize, j, test_info.ui_generations);

						double d_solution = getDoubleMax();

						// spawn k threads to run a certain number of tests each
						for (std::size_t k = 0; k < test_info.ui_numThreads; k++)
						{
							res[k] = new Results[test_info.ui_iterations];
							threads[k] = std::thread(f, test_info.ui_iterations, fitnessFunctions[i], pop_info, da_ranges[i], res[k], args...);
						} // end for k

						// wait for all tests to end
						for (size_t k = 0; k < test_info.ui_numThreads; k++)
						{
							threads[k].join();
						} // end for

						// write test data to file
						if (test_info.b_storeData)
						{
							dumpData(const_cast<const Results**>(res), test_info.ui_numThreads, test_info.ui_iterations, makeFileName(j, i));
						} // end if

						for (std::size_t v = 0; v < test_info.ui_numThreads; v++)
						{
							for (std::size_t y = 0; y < test_info.ui_iterations; y++)
							{
								assert(res[v][y].d_time > 0);
								dp_times[(j / test_info.ui_deltaDim) - 1] += res[v][y].d_time;
								assert(dp_times[(j/ test_info.ui_deltaDim)-1] > 0);
								if (res[v][y].d_bestValue < d_solution)
								{
									d_solution = res[v][y].d_bestValue;
								} // end if
							} // end for y
						} // end for v
						std::cout << "Best solution found for f" << (i + 1) << " in " << j << " dimensions: " << d_solution;

						// for analysis, print how far it's away from global best
						if (optimalSolutions[i][(j / test_info.ui_deltaDim) - 1] != -1.0)
						{
							std::cout << "  --  " << ((d_solution / optimalSolutions[i][(j / test_info.ui_deltaDim) - 1]) * 100) << "%"<< std::endl;
						} // end if
						else
						{
							std::cout << "  --  no data" << std::endl;
						} // end else

						deleteResults(res, test_info.ui_numThreads); // delete results from this test
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

		std::vector<std::vector<double>> optimalSolutions;

		/// <summary>Stores test parameters.</summary>
		Test_Info test_info;

		/// <summary>Used for timing tests.</summary>
		timePoint	compute_start,
		/// <summary>Used for timing tests.</summary>
					compute_end;
		/// <summary>Used for timing tests.</summary>
		duration	time_to_compute;

		/// <summary>Vector containing pointers to the cost functions.</summary>
		std::vector<FitnessFunction> fitnessFunctions;

	#pragma endregion

	#pragma region Private Methods:
		/// <summary>Generates the matrix containing the ranges for all cost functions.</summary>
		/// <param name="da_A">A valid pointer to an array of 15 uninitialized double pointers.</param>
		/// <remarks>This function is only there to remove some code from the constructor, it is inline and will simply be placed in the constructor by the compiler.</remarks>
		void makeRanges(Bounds*& da_ranges);

		/// <summary>Writes the test data in the <paramref name="res"/> matrix into a file named <paramref name="s_NAME"/>.</summary>
		/// <param name="res">Results matrix.</param>
		/// <param name="ui_SIZE_OUTER">Size of outer array of <paramref name="res"/>.</param>
		/// <param name="ui_SIZE_INNNER">Size of inner array of <paramref name="res"/>.</param>
		/// <param name="s_NAME">Filename for results.</param>
		void dumpData(const Results** res, const std::size_t ui_SIZE_OUTER, std::size_t ui_SIZE_INNNER, const std::string s_NAME);

		/// <summary>Writes the executions times stored in the <paramref name="d_TIMES"/> vector into a file named "times.txt".</summary>
		/// <param name="d_TIMES">Vector with execution times.</param>
		/// <param name="ui_SIZE">Number of elements in <paramref name="d_TIMES"/>.</param>
		void writeTimes(const double* d_TIMES, const size_t ui_SIZE);

		/// <summary>Deletes the <paramref name="res"/> matrix.</summary>
		/// <param name="res">Matrix to delete.</param>
		/// <param name="ui_SIZE">Number of inner arrays in the <paramref name="res"/> matrix.</param>
		void deleteResults(Results** res, const std::size_t ui_SIZE);

		void setOptimalPoints();

		/// <summary>Generates a file name. Name will be generated as "[Strategy Name]_[<paramref name="ui_dim"/>]_f[<paramref name="i_functionNumber"/>]".</summary>
		/// <param name="ui_dim">Dimension to insert into the name.</param>
		/// <param name="ui_functionNumber">Function number to insert into the name.</param>
		std::string makeFileName(std::size_t ui_dim, std::size_t ui_functionNumber);

	#pragma endregion

#pragma endregion

}; // end Class Test

#endif // !_TEST_H
