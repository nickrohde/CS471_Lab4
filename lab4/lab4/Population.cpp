#include "Population.hpp" // class header


#pragma region Public:
	#pragma region Constructors:
	Population::Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& BOUNDS)
	{
		b_isSorted = false;
		bounds = BOUNDS;

		initializePopulation(ui_SIZE, ui_DIM);
	} // end Constructor 4


	Population::Population(const Population & other)
	{
		ui_size = other.ui_size;
		ui_length = other.ui_length;
		b_isSorted = other.b_isSorted;
		bounds = other.bounds;

		try
		{
			instantiate(fitnesses, ui_length);
			instantiate(dp_pop, ui_size, ui_length);
		} // end try
		catch (std::runtime_error e)
		{
			deleteContents();
			return;
		} // end catch	

		memcpy(fitnesses, other.fitnesses, sizeof(Fitness)*ui_length);

		for (std::size_t i = 0; i < ui_size; i++)
		{
			memcpy(dp_pop[i], other.dp_pop[i], sizeof(double)*ui_length);
		} // end for
	} // end Copy Constructor


	Population::Population(Population && other) noexcept
	{
		// copy primitives
		ui_size = other.ui_size;
		ui_length = other.ui_length;
		b_isSorted = other.b_isSorted;
		bounds = other.bounds;

		other.ui_size = 0;
		other.ui_length = 0;

		// free memory owned by this object
		deleteContents();

		// move dynamic data over
		dp_pop = other.dp_pop;
		fitnesses = other.fitnesses;

		// set other object's pointers to null
		other.dp_pop = nullptr;
		other.fitnesses = nullptr;
	} // end Move Constructor

	#pragma endregion

	#pragma region Operations:
	void Population::sort(void) noexcept
	{
		if (!b_isSorted) // only sort if needed
		{
			b_isSorted = true;
		} // end if
	} // end method sort

	#pragma endregion

#pragma endregion

#pragma region Protected
void Population::setFitness(const std::size_t j, const double d_fitness)
{
	if (isValid())
	{
		fitnesses[j].d_currentfitness = d_fitness; // update current fitness

		if (d_fitness < fitnesses[j].d_bestFitness)
		{
			fitnesses[j].d_bestFitness = d_fitness; // update particle's best fitness

			if (d_fitness < bestFitness())
			{
				ui_bestIndex = j; // update global best
			} // end if
		} // end if
		return;
	} // end if

	throw std::runtime_error("Memory allocation failed.");
} // end method setFitness


void Population::instantiate(double **& p_arr, const std::size_t ui_HEIGHT, const std::size_t ui_WIDTH)
{
	// make sure outer array doesn't exist yet
	if (p_arr == nullptr)
	{
		p_arr = new double*[ui_HEIGHT];

		if (p_arr == nullptr)
		{
			throw std::runtime_error("Memory allocation failed.");
		} // end if
	} // end if

	for (std::size_t i = 0; i < ui_HEIGHT; i++)
	{
		p_arr[i] = new double[ui_WIDTH];

		if (p_arr[i] == nullptr)
		{
			throw std::runtime_error("Memory allocation failed.");
		} // end if
	} // end for
} // end method instantiate

#pragma endregion

#pragma region Private:
void Population::initializePopulation(const std::size_t ui_SIZE, const std::size_t ui_DIM)
{
	ui_size = ui_SIZE;    // the length of all genes
	ui_length = ui_DIM;  // index of the fitness value

	try
	{
		instantiate(dp_pop, ui_SIZE, ui_DIM);
		instantiate(fitnesses, ui_SIZE);
	} // end try
	catch (std::runtime_error e)
	{
		deleteContents();
		return;
	} // end catch

	  // initialize all members
	for (std::size_t i = 0; i < ui_SIZE; i++)
	{
		for (std::size_t j = 0; j < ui_DIM; j++)
		{
			dp_pop[i][j] = getRandomRealInRange<double>(bounds.d_min, bounds.d_max);
		} // end for
	} // end for	
} // end method initializePopulation


void Population::deleteContents(void) noexcept
{
	if (dp_pop != nullptr)
	{
		for (std::size_t i = 0; i < ui_size; i++)
		{
			if (dp_pop[i] != nullptr)
			{
				delete[] dp_pop[i];
			} // end if
		} // end for

		delete[] dp_pop;
	} // end if

	if (fitnesses != nullptr)
	{
		delete[] fitnesses;
	} // end if
} // end method deleteContents


void Population::instantiate(Fitness*& p_arr, const std::size_t ui_LENGTH)
{
	if (p_arr == nullptr)
	{
		p_arr = new Fitness[ui_LENGTH];

		if (p_arr == nullptr)
		{
			throw std::runtime_error("Memory allocation failed.");
		} // end if
	} // end if
} // end method instantiate

#pragma endregion