#include "Test.hpp"				// class header
#include "functions.hpp"		// cost functions


using namespace std;

#pragma region Public:
	#pragma region Constructors:
		Test::Test(void)
		{
			da_ranges = new Bounds[NUMBER_FUNCTIONS]; // array containing the bounds of each function

			// these two function only exist to make the constructor shorter
			makeRanges(da_ranges); // make array with ranges for functions

			fitnessFunctions = getAllCostFunctions(ui_SHEKEL_M); // vector containing the cost functions

			compute_start = compute_end = highRes_Clock::now();
		} // end Default Constructor


		Test::Test(const Test_Info& TEST_INFO)
		{
			test_info = TEST_INFO;

			compute_start = compute_end = highRes_Clock::now();

			da_ranges = new Bounds[NUMBER_FUNCTIONS]; // array containing the ranges for the RNG; [i][0] contains min, [i][1] contains max for function f_i

			// these two function only exist to make the constructor shorter
			makeRanges(da_ranges); // make matrix with ranges for functions

			fitnessFunctions = getAllCostFunctions(ui_SHEKEL_M); // vector containing the cost functions
		} // end Constructor 4

	#pragma endregion

	#pragma region Destructor:
		Test::~Test(void)
		{
			try
			{
				if (da_ranges != nullptr)
				{
					delete[] da_ranges;
				} // end if
			} // end try
			catch (exception e)
			{
				cout << "deleting ranges broke" << endl;
			} // end catch all
		} // end Destructor

	#pragma endregion

#pragma endregion

#pragma region Private:

inline void Test::makeRanges(Bounds*& da_ranges)
{
	da_ranges[0]  = Bounds(-512.0, 512.0);
	da_ranges[1]  = Bounds(-100.0, 100.0);
	da_ranges[2]  = Bounds(-100.0, 100.0);
	da_ranges[3]  = Bounds(-30.0,   30.0);
	da_ranges[4]  = Bounds(-500.0, 500.0);
	da_ranges[5]  = Bounds(-30.0,   30.0);
	da_ranges[6]  = Bounds(-30.0,   30.0);
	da_ranges[7]  = Bounds(-32.0,   32.0);
	da_ranges[8]  = Bounds(-32.0,   32.0);
	da_ranges[9]  = Bounds(-500.0, 500.0);
	da_ranges[10] = Bounds(-500.0, 500.0);
	da_ranges[11] = Bounds(-100.0, 100.0);
	da_ranges[12] = Bounds(   0.0,  _PI );
	da_ranges[13] = Bounds(- 30.0,  30.0);
	da_ranges[14] = Bounds(   0.0,  10.0);
} // end method makeRanges


void Test::dumpData(const Results** res, const std::size_t ui_SIZE_OUTER, std::size_t ui_SIZE_INNER, const std::string s_NAME)
{
	ofstream file(s_NAME, ios::app | ios::out);

	if (file.is_open() && !file.bad())
	{
		for (std::size_t i = 0; i < ui_SIZE_OUTER; i++)
		{
			for (size_t j = 0; j < ui_SIZE_INNER; j++)
			{
				file << res[i][j].d_bestValue;
				if (i + 1 < ui_SIZE_OUTER || j + 1 < ui_SIZE_INNER)
				{
					file << ", ";
				} // end if
			} // end for j			
		} // end for i
	} // end if

	file.close();
} // end method dumpData


void Test::writeTimes(const double * d_TIMES, const size_t ui_SIZE)
{
	if (d_TIMES != nullptr)
	{
		ofstream file("times.txt", ios::out | ios::app);

		if (file.is_open() && !file.bad())
		{
			for (std::size_t i = 0; i < ui_SIZE; i++)
			{
				file << d_TIMES[i];
				if (i + 1 < ui_SIZE)
				{
					file << ", ";
				} // end if
			} // end for
		} // end if
	} // end if
} // end method writeTimes


void Test::deleteResults(Results** res, const std::size_t ui_SIZE)
{
	if (res != nullptr)
	{
		for (std::size_t i = 0; i < ui_SIZE; i++)
		{
			if (res[i] != nullptr)
			{
				delete[] res[i];
			} // end if
		} // end for
	} // end if
} // end method deleteResults


string Test::makeFileName(size_t ui_dim, int i_functionNumber)
{
	stringstream name;

	name << "PSO_" << ui_dim << "_f" << (i_functionNumber + 1) << ".csv" ;

	return name.str();
} // end method makeFileName

#pragma endregion
