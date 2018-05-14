#include "PSO.hpp"



Results* _PSO(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO)
{
	timePoint compute_end = highRes_Clock::now();
	timePoint compute_start = highRes_Clock::now();

	PS_Population* population = new PS_Population(POP_INFO, BOUNDS, PSO_INFO);

	compute_start = highRes_Clock::now();

	population->evaluateAll(f);

	for (size_t i = 0; i < POP_INFO.ui_generations; i++)
	{
		for (size_t j = 0; j < population->size(); j++)
		{
			population->updateVelocity(j);
			population->evaluate(f, j);
		} // end for j
	} // end for i

	compute_end = highRes_Clock::now();

	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	assert(time_to_compute.count() > 0);

	Results* res = new Results(population->bestFitness(), time_to_compute.count());

	delete population;

	return res;
} // end method _PSO


void PSO(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const PSO_Info& PSO_INFO)
{
	for (size_t i = 0; i < ui_ITERATIONS; i++)
	{
		res[i] = *(_PSO(f, POP_INFO, BOUNDS, PSO_INFO));
	} // end for
} // end method PSO