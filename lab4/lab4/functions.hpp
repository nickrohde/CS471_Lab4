#pragma once

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "MasterInclude.hpp"


/// <summary>Typedef to make cost function type a bit more readable.</summary>
typedef std::function<double(const double*, const size_t)> fitnessFunction;

/// <summary>Index of shekel's foxholes function in the vector returned by getAllCostFunctions</summary>
const int i_SHEKEL_INDEX = 14;

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double schwefelsFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double firstDeJongsFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double rosenbrockFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double rastriginFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double griewangkFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double sineEnvelopeSineWaveFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double stretchedVSineWaveFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double ackleysOneFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double ackleysTwoFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double eggHolderFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double ranaFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double pathologicalFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double michalewiczFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double masterCosineWaveFunction(const double* dp_VECT, const size_t ui_SIZE);

/// <summary>Cost function for testing an optimization strategy</summary>
/// <param name="dp_VECT">The point at which the function is to be evaluated.</param>
/// <param name="ui_SIZE">Length of <paramref name="dp_VECT"/>.</param>
/// <param name="da_A">A matrix for the outer loop of this function.</param>
/// <param name="ui_M">The number of times to execute the outer loop of the function.</param>
/// <returns>The value of the function evaluated at <paramref name="dp_VECT"/></returns>
inline double shekelsFoxholesFunction(const double* dp_VECT, const size_t ui_SIZE, const double** da_A, const std::size_t ui_M = 10);

/// <summary>Gets a vector containg all 15 cost functions.</summary>
/// <param name="da_A">A matrix for the outer loop of shekel's foxholes function.</param>
/// <param name="ui_M">The number of times to execute the outer loop of shekel's foxholes function is to be run.</param>
/// <returns>A constant vector containing pointers to all 15 functions above.</returns>
const std::vector<fitnessFunction>& getAllCostFunctions(const double ** arg1, const std::size_t arg2);


#endif