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
			(*this) = other;
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
				setFitness(i, F(&(dp_pop[i])));
			} // end for
		} // end method evaluateAll 

	#pragma endregion

	#pragma region Operators:
		Population & Population::operator=(const Population & OTHER)
		{
			ui_size = OTHER.ui_size;
			ui_length = OTHER.ui_length;
			b_isSorted = OTHER.b_isSorted;
			b_fitnessValid = OTHER.b_fitnessValid;
			ui_bestIndex = OTHER.ui_bestIndex;
			ui_worstIndex = OTHER.ui_worstIndex;
			bounds = OTHER.bounds;

			fitnesses = std::vector<Fitness>(OTHER.ui_size);
			instantiate(dp_pop, ui_size, ui_length);


			for (std::size_t i = 0; i < ui_length; i++)
			{
				fitnesses[i] = OTHER.fitnesses[i];
			} // end for
			
			for (std::size_t i = 0; i < ui_size; i++)
			{
				dp_pop[i] = OTHER.dp_pop[i];
			} // end for

			return (*this);
		} // end Copy Assignement


		Population & Population::operator=(Population&& other) noexcept
		{
			// copy primitives
			ui_size = other.ui_size;
			ui_length = other.ui_length;
			ui_bestIndex = other.ui_bestIndex;
			ui_worstIndex = other.ui_worstIndex;
			b_isSorted = other.b_isSorted;
			b_fitnessValid = other.b_fitnessValid;
			bounds = other.bounds;

			other.ui_size = 0;
			other.ui_length = 0;

			// move dynamic data over
			dp_pop = other.dp_pop;
			fitnesses = other.fitnesses;

			return (*this);
		} // end Move Assignment

	#pragma endregion

#pragma endregion

#pragma region Protected
	void Population::setFitness(const std::size_t j, const double d_fitness)
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
	} // end method setFitness


	void Population::instantiate(std::vector<std::vector<double>>& p_arr, const std::size_t ui_HEIGHT, const std::size_t ui_WIDTH)
	{
		p_arr = std::vector<std::vector<double>>(ui_HEIGHT);

		for (std::size_t i = 0; i < ui_HEIGHT; i++)
		{
			p_arr[i] = std::vector<double>(ui_WIDTH);
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
		fitnesses = std::vector<Fitness>(ui_SIZE);

		instantiate(dp_pop, ui_SIZE, ui_DIM);

		// initialize all members
		for (std::size_t i = 0; i < ui_SIZE; i++)
		{
			for (std::size_t j = 0; j < ui_DIM; j++)
			{
				dp_pop[i][j] = getRandomRealInRange<double>(bounds.d_min, bounds.d_max);
			} // end for
		} // end for	
	} // end method initializePopulation


#pragma endregion