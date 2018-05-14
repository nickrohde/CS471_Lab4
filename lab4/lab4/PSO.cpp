#include "PSO.hpp"



void _PSO(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO, Results* res)
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

	res->d_bestValue = population->bestFitness();
	res->d_time = time_to_compute.count();

	delete population;
} // end method _PSO


Results* PSO(const std::size_t NUM_THREADS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const PSO_Info& PSO_INFO)
{
	std::thread* threads = new std::thread[NUM_THREADS];

	Results* results = new Results[NUM_THREADS];

	for (size_t i = 0; i < NUM_THREADS; i++)
	{
		threads[i] = std::thread(_PSO, f, POP_INFO, BOUNDS, PSO_INFO, &(results[i]));
	} // end for

	for (size_t i = 0; i < NUM_THREADS; i++)
	{
		threads[i].join();
	} // end for

	delete[] threads;

	return results;
} // end method PSO