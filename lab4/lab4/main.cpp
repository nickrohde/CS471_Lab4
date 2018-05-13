#include "MasterInclude.hpp" // everything that could possibly be needed
#include "Driver.hpp"		 // Driver class


#define DEBUG 0

using namespace std;



/// <summary>Program entry point.</summary> 
/// <param name="argc">Number of command line arguments passed to main.</param>
/// <param name="argv">Array of string containing the name of a ini file to parse, or nothing.</param>
/// <returns>0 on successful execution, 1 otherwise.</returns>
int main(int argc, char ** argv)
{
	Driver* driver = nullptr;
	int i_exitCode = 1;

	if (!DEBUG && argc > 1) // ini file parameter is present
	{
		string s(argv[1]);
		driver = new Driver(s);
	} // end if
	else if (!DEBUG) // no ini file parameter
	{
		cout << "No ini parameter received. Attempting to open \"config.ini\" file." << endl;
		driver = new Driver("config.ini");
	} // end else (argc <= 1)
	
	if (DEBUG)
	{
		cout << "Debug mode. Starting with default values ..." << endl;
		driver = new Driver();
		i_exitCode = driver->run();
	} // end if

	try
	{
		if (driver->isValid())
		{
			i_exitCode = driver->run();
		} // end if
	} // end try
	catch (exception e)
	{
		delete driver;

		return EXIT_FAILURE;
	} // end catch

	delete driver;

	return i_exitCode;
} // end Main

