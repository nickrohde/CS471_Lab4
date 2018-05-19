#include "FFA.hpp"




Results* _FFA(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const FF_Info& FF_INFO)
{
	Results* res = new Results();

	FF_Population* current = new FF_Population(POP_INFO, BOUNDS, FF_INFO); // current population

	double	d_beta_0 = 1.0,
			d_beta = 0.0,
			d_dist = 0.0;

	for (std::size_t i = 0; i < POP_INFO.ui_generations; i++)
	{
		FF_Population* copy = new FF_Population(*current); // working population 

		for (std::size_t j = 0; j < POP_INFO.ui_size; j++)
		{
			for (std::size_t k = 0; k < POP_INFO.ui_size; k++)
			{
				d_dist = current->distance(j, k);

				if (current->intensity(j, d_dist) > current->intensity(k, d_dist))
				{
					d_beta = current->beta(d_dist);

					copy->shiftTowards(j, k, d_beta);
				} // end if
			} // end for k
		} // end for j
	} // end for i

	return res;
} // end method _FFA


void FFA(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const FF_Info& FF_INFO)
{
	for (size_t i = 0; i < ui_ITERATIONS; i++)
	{
		res[i] = *(_FFA(f, POP_INFO, BOUNDS, FF_INFO));
	} // end for
} // end method FFA
