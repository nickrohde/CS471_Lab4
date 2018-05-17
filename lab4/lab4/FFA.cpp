#include "FFA.hpp"








Results * _FFA(const FitnessFunction & f, const Population_Info & POP_INFO, const Bounds & BOUNDS, const FF_Info& FF_INFO)
{
	return nullptr;
} // end method _FFA


void FFA(const std::size_t ui_ITERATIONS, const FitnessFunction & f, const Population_Info & POP_INFO, const Bounds & BOUNDS, Results * res, const FF_Info& FF_INFO)
{
	for (size_t i = 0; i < ui_ITERATIONS; i++)
	{
		res[i] = *(_FFA(f, POP_INFO, BOUNDS, FF_INFO));
	} // end for
} // end method FFA
