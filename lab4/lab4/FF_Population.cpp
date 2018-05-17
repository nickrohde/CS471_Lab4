#include "FF_Population.hpp"

FF_Population::FF_Population(const Population_Info & POP_INFO, const Bounds & BOUNDS, const FF_Info & FF_INFO) : Population(POP_INFO.ui_size, POP_INFO.ui_dim, BOUNDS)
{
	alpha = FF_INFO.alpha;
	beta = FF_INFO.beta;
	gamma = FF_INFO.gamma;
} // end Constructor
