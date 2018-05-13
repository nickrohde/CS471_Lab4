#include "PS_Population.hpp"

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


		PS_Population::PS_Population(const PS_Population & other) : Population(other)
		{
			d_C1 = other.d_C1;
			d_C2 = other.d_C2;
			d_K = other.d_K;

			try
			{
				instantiate(dp_velocity, other.ui_size, other.ui_length);
			} // end try
			catch(std::runtime_error e)
			{
				deleteContents();
				return;
			} // end catch

			for (size_t i = 0; i < ui_size; i++)
			{
				memcpy(dp_velocity[i], other.dp_velocity[i], sizeof(double)*ui_length);
			} // end for
		} // end Copy Constructor


		PS_Population::PS_Population(PS_Population && other) noexcept : Population(other)
		{
			d_C1 = other.d_C1;
			d_C2 = other.d_C2;
			d_K = other.d_K;

			deleteContents();

			dp_velocity = other.dp_velocity;
			other.dp_velocity = nullptr;
		} // end Move Constructor

	#pragma endregion

	#pragma region Operations:
		void PS_Population::evaluateAll(const FitnessFunction& f)
		{
			for (std::size_t i = 0; i < ui_size; i++)
			{
				evaluate(f, i);
			} // end for
		} // end method evaluateAll 


		inline void PS_Population::evaluate(const FitnessFunction& f, const std::size_t i)
		{
			setFitness(i, f(dp_pop[i], ui_length));
		} // end method evaluate


		void PS_Population::updateVelocity(const std::size_t i)
		{
			double* dp_particle = (*this)[i];

			for (std::size_t j = 0; j < ui_length;j ++)
			{
				assert(TODO);
				dp_velocity[i][j] = dp_velocity[i][j] + d_C1 * getRandomRealInRange<double>(0.0, 1.0) * (fitnesses[i].d_bestFitness - dp_particle[j])
													  + d_C2 * getRandomRealInRange<double>(0.0, 1.0) * (best(j) - dp_particle[j]);

				dp_particle[j] += dp_velocity[i][j];
			} // end for
		} // end method updateVelocity

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


	void PS_Population::deleteContents(void) noexcept
	{
		if (dp_velocity != nullptr)
		{
			for (std::size_t i = 0; i < ui_size; i++)
			{
				if (dp_velocity[i] != nullptr)
				{
					delete[] dp_velocity[i];
				} // end if
			} // end for

			delete[] dp_velocity;
		} // end if
	}

#pragma endregion

