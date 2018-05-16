#include "Driver.hpp"				// class header
#include "IniParser/IniParser.hpp"	// IniParser class
#include "PSO.hpp"

#pragma message("DRIVER")

#define _DEBUG 1

using namespace std;


void Driver::presentMenu(void)
{
	cout << "1 - Particle Swarm" << endl;
	cout << "2 - Firefly Algorithm" << endl;
	cout << "3 - Parse new settings" << endl;
	cout << "Q - Quit" << endl;
} // end method presentMenu


char Driver::getChoice(void)
{
	char c = 0x00;
	bool first = true;

	do
	{
		if (!first)
		{
			cout << "Invalid input! Try again." << endl;
		} // end if
		first = false;

		presentMenu();

		cout << "Enter choice: ";
		cin >> c;

		if (cin.fail()) // error check
		{
			clearInput();
			continue;
		} // end if

		c = static_cast<char>(tolower(static_cast<char>(c)));

	} while (c != '1' && c != '2' && c != '3' && c != 'q');

	return c;
} // end method getChoice


char Driver::askUserYesNo(void)
{
	char c = 0x0;
	bool first = true;

	do
	{
		if (!first)
		{
			cout << "Invalid input! Try again." << endl;
		} // end if
		first = false;

		cout << "Enter choice (Y/N): ";
		cin >> c;

		if (cin.fail()) // error check
		{
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
			continue;
		} // end if

		c = static_cast<char>(tolower(static_cast<char>(c)));

	} while (c != 'y' && c != 'n');

	return c;
} // end method askUserYesNo


void Driver::initialize(const std::string  s_fileName)
{
	IniParser* parser = new IniParser(s_fileName);

	try
	{
		// extract data from .ini file
		test_info.ui_minDim = parser->getKeyAs<size_t>("DIM", "min");   // smallest dimension to test
		test_info.ui_maxDim = parser->getKeyAs<size_t>("DIM", "max");   // largest dimension to test
		test_info.ui_deltaDim = parser->getKeyAs<size_t>("DIM", "delta"); // dimension increase

		test_info.ui_iterations = parser->getKeyAs<size_t>("TEST", "num_test_itrs");
		test_info.b_storeData = parser->getKeyAs<bool>("TEST", "store_data");
		test_info.ui_numThreads = parser->getKeyAs<size_t>("TEST", "num_threads");

		test_info.ui_generations = parser->getKeyAs<size_t>("POP", "generations");
		test_info.ui_popSize = parser->getKeyAs<size_t>("POP", "size");

		test_info.d_PSO_c1 = parser->getKeyAs<double>("PSO", "c1");
		test_info.d_PSO_c2 = parser->getKeyAs<double>("PSO", "c2");
		test_info.d_PSO_k = parser->getKeyAs<double>("PSO", "c3");
		
	} // end try
	catch (invalid_argument e)
	{
		delete parser;
		throw e; // handled above
	} // end catch
	catch (exception e)
	{
		cout << "ERROR! " << e.what() << endl << "Exiting..." << endl;
		delete parser;
		exit(EXIT_FAILURE);
	} // end catch all

	b_invalid = false;

	delete parser;
} // end method initialize


bool Driver::isValid(void)
{
	return !b_invalid;
} // end method isValid


Driver::Driver(void)
{
	// initialize variables
	compute_start = highRes_Clock::now(),
	compute_end = highRes_Clock::now();
	time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	b_invalid = true;
} // end Default Constructor


Driver::Driver(string s_fileName) : Driver()
{
	// attempt to parse .ini file
	ifstream file(s_fileName.c_str(), ios::in);

	if (file.is_open() && !file.bad())
	{
		file.close();

		for (;;)
		{
			try
			{
				initialize(s_fileName); // try to parse file
				break;
			} // end try
			catch (invalid_argument e) // parsing failed
			{
				cout << "A required field was not found the file!" << endl;
				cout << e.what() << endl << endl;
				cout << "Try different file?" << endl;
				clearInput();
				char c = askUserYesNo();

				if (c == 'n') // user wants to quit
				{
					return; 
				} // end if

				s_fileName = askUserForFileName(); // get new filename to try again

				if (b_stop) // user can elect to stop trying in askUserForFileName
				{
					return; // quit the program
				} // end if
			} // end catch
		} // end forever
	} // end if
	else
	{
		file.close();

		for (;;)
		{
			cout << "The file \"" << s_fileName << "\" could not be opened." << endl;
			cout << "Try different file?" << endl;
			clearInput();
			char c = askUserYesNo();

			if (c == 'n')
			{
				return; // the object is in an invalid state
			} // end if

			s_fileName = askUserForFileName();

			if (b_stop)
			{
				return; // the object is in an invalid state
			} // end if

			try
			{
				initialize(s_fileName);
				break;
			} // end try
			catch (invalid_argument e)
			{
				cout << "An error occurred while parsing the ini file!" << endl;
				cout << "Error: " << e.what();
				cout << "Try different file?" << endl;
				char c = askUserYesNo();

				if (c == 'n')
				{
					return; // the object is in an invalid state
				} // end if
			} // end catch
		} // end forever
	} // end else

	b_invalid = false;
} // end Constructor 1


int Driver::run(void)
{
	char choice = 'q';

	if (b_invalid)
	{
		cout << "Parsing of the .ini file failed. Exiting ..." << endl;
		return EXIT_FAILURE; 
	} // end if

	Test* test = new Test(test_info);

	do
	{
		clearInput();
		choice = getChoice(); // get user input for which algorithm to run

		switch (choice)
		{
		case '1':
		{
			cout << "Starting tests for Particle Swarms ..." << endl;

			compute_start = highRes_Clock::now(); // start timer for whole run

			if (test != nullptr)
			{
				test->runTest<_PSO_>(PSO, PSO_Info(0.8, 1.2, 0.9));
			} // end if
			else
			{
				cout << "No test settings available!" << endl;
				break;
			} // end else

			compute_end = highRes_Clock::now();
			time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

			cout << "Finished running tests for Particle Swarms." << endl;
			cout << "Time elapsed: " << time_to_compute.count() << " seconds." << endl << endl;

			break;
		} // end case 1

		case '2':
		{
			cout << "Starting tests for Firefly Algorithm ..." << endl;

			compute_start = highRes_Clock::now(); // start timer for whole run

			assert(TODO);

			compute_end = highRes_Clock::now();
			time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

			cout << "Finished running tests for Firefly Algorithm." << endl;
			cout << "Time elapsed: " << time_to_compute.count() << " seconds." << endl << endl;

			break;
		} // end case 2
		case '3':
		{
			if (test != nullptr)
			{
				delete test;
			} // end if

			b_invalid = true;

			initialize(askUserForFileName()); // parse new settings

			if (b_invalid)
			{
				cout << "Parsing of the .ini file failed. Exiting ..." << endl;
				return EXIT_FAILURE;
			} // end if

			test = new Test(test_info);
		} // end case 3

		default:
			break;
		} // end switch
	} while (tolower(choice) != 'q' && !b_invalid);

	if (test != nullptr)
	{
		delete test;
	} // end if

	return EXIT_SUCCESS;
} // end method run


string Driver::askUserForFileName(void)
{
	// Variables:
	string s_name = "";

	b_stop = false;

	for(;;)
	{
		cout << "Please enter the name of the .ini file: ";
		clearInput();
		getline(cin, s_name);

		if (s_name.length() > 0)
		{
				ifstream file(s_name, ios::in);

				if (!file.bad() && file.is_open())
				{
					file.close();
					return s_name;
				} // end if 
				else
				{
					file.close();
					cout << "The file \"" << s_name << "\" could not be opened." << endl;
					cout << "Try different file?" << endl;
					clearInput();
					char c = askUserYesNo();

					if (c == 'n')
					{
						b_stop = true; // let instantiate know that user wants to quit
						return "";
					} // end if
				} // end else
		} // end if (s_name.length() > 0)
		else
		{
			cout << "Invalid input!" << endl;
			cout << "Try again?" << endl;
			clearInput();
			char c = askUserYesNo();

			if (c == 'n')
			{
				cout << "Exiting ..." << endl;
				b_stop = true; // let instantiate know that user wants to quit
				return "";
			} // end if
		} // end else
	} // end forever

	return s_name;
} // end method askUserForFileName


void Driver::clearInput()
{
	cin.clear();
	cin.ignore(std::cin.rdbuf()->in_avail());
} // end method clearInput