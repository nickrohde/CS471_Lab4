#include "Population.hpp" // class header

#pragma message("POP")

#pragma region Public:
	#pragma region Constructors:
		Population::Population(const std::size_t ui_SIZE, const std::size_t ui_DIM, const Bounds& BOUNDS)
		{
			b_isSorted = false;
			bounds = BOUNDS;

			initializePopulation(ui_SIZE, ui_DIM);
		} // end Constructor 4


		Population::Population(const Population & OTHER)
		{
			(*this) = OTHER;
		} // end Copy Constructor


		Population::Population(Population && other) noexcept
		{
			// copy primitives
			ui_size = other.ui_size;
			ui_length = other.ui_length;
			ui_bestIndex = other.ui_bestIndex;
			ui_worstIndex = other.ui_worstIndex;
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


		void Population::evaluateAll(const FitnessFunction& F)
		{
			for (std::size_t i = 0; i < ui_size; i++)
			{
				evaluate(F, i);
			} // end for
		} // end method evaluateAll 


		inline void Population::evaluate(const FitnessFunction& F, const std::size_t i)
		{
			setFitness(i, F(dp_pop[i], ui_length));
		} // end method evaluate

	#pragma endregion

	#pragma region Operators:
		Population & Population::operator=(const Population & OTHER)
		{
			ui_size = OTHER.ui_size;
			ui_length = OTHER.ui_length;
			b_isSorted = OTHER.b_isSorted;
			ui_bestIndex = OTHER.ui_bestIndex;
			ui_worstIndex = OTHER.ui_worstIndex;
			bounds = OTHER.bounds;

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

			memcpy(fitnesses, OTHER.fitnesses, sizeof(Fitness)*ui_length);

			for (std::size_t i = 0; i < ui_size; i++)
			{
				memcpy(dp_pop[i], OTHER.dp_pop[i], sizeof(double)*ui_length);
			} // end for
		} // end Copy Assignement


		Population & Population::operator=(Population&& other) noexcept
		{
			// copy primitives
			ui_size = other.ui_size;
			ui_length = other.ui_length;
			ui_bestIndex = other.ui_bestIndex;
			ui_worstIndex = other.ui_worstIndex;
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
		} // end Move Assignment

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
				fitnesses[j].d_bestFitness = d_fitness; // update best fitness

				if (d_fitness < bestFitness())
				{
					ui_bestIndex = j; // update global best
				} // end if
			} // end if
			else if (d_fitness > worstFitness())
			{
				ui_worstIndex = j; // update global worst
			} // end else

			b_fitnessValid = true;
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
		ui_size = ui_SIZE;  
		ui_length = ui_DIM;  
		ui_worstIndex = ui_bestIndex = 0;
		b_fitnessValid = false;

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