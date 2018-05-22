#include "PS_Population.hpp"

#pragma message("PS_POP")

#pragma region Public:
	#pragma region Constructors:
		PS_Population::PS_Population(const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO)
									: Population(POP_INFO.ui_size, POP_INFO.ui_dim, BOUNDS)
		{
			d_C1 = PSO_INFO.C1;
			d_C2 = PSO_INFO.C2;
			d_K  = PSO_INFO.K;

			instantiate(dp_velocity, POP_INFO.ui_size, POP_INFO.ui_dim);
			initializeVelocities();
		} // end Constructor


		PS_Population::PS_Population(const PS_Population & OTHER) : Population(OTHER)
		{
			d_C1 = OTHER.d_C1;
			d_C2 = OTHER.d_C2;
			d_K = OTHER.d_K;

			instantiate(dp_velocity, OTHER.ui_size, OTHER.ui_length);

			for (size_t i = 0; i < ui_size; i++)
			{
				dp_velocity[i] = OTHER.dp_velocity[i];
			} // end for
		} // end Copy Constructor


		PS_Population::PS_Population(PS_Population && other) noexcept : Population(other)
		{
			d_C1 = other.d_C1;
			d_C2 = other.d_C2;
			d_K = other.d_K;

			dp_velocity = other.dp_velocity;
			other.dp_velocity.clear();
		} // end Move Constructor

	#pragma endregion

	#pragma region Operations:
		void PS_Population::update(const std::size_t i)
		{
			// pointer to current particle for convenience
			std::vector<double>* dp_particle = &dp_pop[i];

			for (std::size_t j = 0; j < ui_length;j ++)
			{
				// update velocity
				dp_velocity[i][j] = d_K * dp_velocity[i][j] + d_C1 * getRandomRealInRange<double>(0.0, 1.0) * (fitnesses[i].d_bestFitness - (*dp_particle)[j])
													        + d_C2 * getRandomRealInRange<double>(0.0, 1.0) * (best(j) - (*dp_particle)[j]);
				// update particle
				(*dp_particle)[j] += dp_velocity[i][j];

				// make sure we didn't go out of bounds
				if ((*dp_particle)[j] > bounds.d_max)
				{
					(*dp_particle)[j] = getRandomRealInRange<double>(bounds.d_min, bounds.d_max);
				} // end if
				else if ((*dp_particle)[j] < bounds.d_min)
				{
					(*dp_particle)[j] = getRandomRealInRange<double>(bounds.d_min, bounds.d_max); // make sure min isn't zero
				} // end elif
			} // end for
		} // end method update

		void PS_Population::evaluate(const FitnessFunction & F, const std::size_t i)
		{
			setFitness(i, F(&(dp_pop[i])));
		} // end method evaluate


	#pragma endregion

#pragma endregion

#pragma region Private:
	void PS_Population::initializeVelocities(void)
	{
		for (std::size_t i = 0; i < ui_size; i++)
		{
			for (std::size_t j = 0; j < ui_length; j++)
			{
				dp_velocity[i][j] = getRandomRealInRange<double>(0.0, 0.5 * (bounds.d_max - bounds.d_min));
			} // end for j
		} // end for i
	} // end method initializeVelocities

#pragma endregion

