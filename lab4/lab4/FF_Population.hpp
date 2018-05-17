#pragma once

#ifndef _FF_POP_H
#define _FF_POP_H


#include "MasterInclude.hpp"
#include "Population.hpp"
#include "Containers.hpp"


class FF_Population : public Population
{
public:
	FF_Population(const Population_Info& POP_INFO, const Bounds& BOUNDS, const FF_Info& FF_INFO);



private:
	double	alpha,
			beta,
			gamma;


}; // end Class FF_Population
#endif // !_FF_POP_H

