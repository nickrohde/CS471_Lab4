#pragma once

#ifndef _FFA_H
#define _FFA_H

#include "MasterInclude.hpp"
#include "Containers.hpp"
#include "FF_Population.hpp"

Results* _FFA(const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, const FF_Info& FF_INFO);


void FFA(const std::size_t ui_ITERATIONS, const FitnessFunction& f, const Population_Info& POP_INFO, const Bounds& BOUNDS, Results* res, const FF_Info& FF_INFO);


#endif // !_FFA_H
