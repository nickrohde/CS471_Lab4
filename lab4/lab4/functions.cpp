#include "functions.hpp" // class header
#include "utility.hpp"	 // math defines


inline double schwefelsFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n]
	for (size_t i = 0; i < ui_SIZE; i++)
	{
		total += (-1 * dp_VECT[i]) * sin(sqrt(abs(dp_VECT[i])));
	} // end for

	return total;
} // end method schwefelsFunction


inline double firstDeJongsFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n]
	for (size_t i = 0; i < ui_SIZE; i++)
	{
		total += dp_VECT[i] * dp_VECT[i]; // (x_i)^2
	} // end for

	return total;
} // end method firstDeJongsFunction


inline double rosenbrockFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	temp = 100 * pow((dp_VECT[i] * dp_VECT[i] - dp_VECT[i+1]),2); // 100(x_i^2 - x_i+1)^2

		total += temp + pow((1 - dp_VECT[i]), 2); // 100(x_i^2 - x_i+1)^2 + (1-x_i)^2
	} // end for

	return total;
} // end method rosenbrockFunction


inline double rastriginFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n]
	for (std::size_t i = 0; i < ui_SIZE; i++)
	{
		total += ((pow(dp_VECT[i], 2)) - (10 * (cos(2 * _PI * dp_VECT[i]))));	// x_i^2 - 10cos(2pi * x_i)
	} // end for

	total += (10 * ui_SIZE); 
	total -= (200 * ui_SIZE); // 10*n + SUM -- shift down by -200n to move optimal point from 0 to -200n

	return total;
} // end method rastriginFunction                                     


inline double griewangkFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double	total = 0.0,
			sum = 0.0,		// SUM[1->n]
			product = 1.0;	// PROD[1->n]

#pragma loop(hint_parallel(0))
	for (std::size_t i = 0; i < ui_SIZE; i++)
	{
		// SUM[1->n]
		{
			sum += ((dp_VECT[i] * dp_VECT[i])/ 4000);
		} // end SUM[1->n]

		// PROD[1->n]
		{
			product *= cos((dp_VECT[i] / sqrt(static_cast<double>(i + 1))));
		} // end PROD[1->n]
	} // end for

	total += 1 + sum - product; // 1 + SUM - PROD

	return total;
} // end method griewangkFunction


inline double sineEnvelopeSineWaveFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double	total = 0.5 * (ui_SIZE - 1), // 0.5(n-1) + SUM
			sum = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	sumOfSquares = 0;

		sumOfSquares = (dp_VECT[i] * dp_VECT[i]) + (dp_VECT[i+1] * dp_VECT[i+1]); // x_i^2 + (x_i+1)^2

		total += ((pow(sin(sumOfSquares - 0.5), 2)) / (pow(((sumOfSquares * 0.001) + 1), 2))); // sin( x_i^2 + (x_i+1)^2 - 0.5 )^2 / (0.001(x_i^2 + (x_i+1)^2) + 1)^2
	} // end for

	total *= -1; // - SUM

	return total;
} // end method sineEnvelopeSineWaveFunction


inline double stretchedVSineWaveFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	sumOfSquares = 0.0,
				temp = 0.0;

		sumOfSquares = (dp_VECT[i] * dp_VECT[i]) + (dp_VECT[i+1] * dp_VECT[i+1]); // x_i^2 + (x_i+1)^2

		temp = pow(sin(50.0 * pow(sumOfSquares, 0.1)),2) + 1; // sin^2( 50( root_10( x_i^2 + (x_i+1)^2 ))) + 1

		total += temp * pow(sumOfSquares, 0.25); // (sin^2( 50( root_10( x_i^2 + (x_i+1)^2 ))) + 1) * root_4(x_i^2 + (x_i+1)^2)
	} // end for

	return total;
} // end method stretchedVSineWaveFunction


inline double ackleysOneFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	const double oneOverE = 1 / pow(_E, 0.2); // 1 / e ^ 0.2

	double total = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	sumOfSquares = 0,
				temp = 0;

		sumOfSquares = oneOverE * sqrt((dp_VECT[i] * dp_VECT[i]) + (dp_VECT[i+1] * dp_VECT[i+1])); // 1/(e^0.2) * sqrt(x_i ^ 2 + (x_i + 1) ^ 2)

		temp = 3 * (cos(2 * dp_VECT[i]) + sin(2 * dp_VECT[i+1])); // 3(cos(2 * x_i) + sin(2 * x_i+1))

		total += temp + sumOfSquares;      // 1/(e^0.2) * sqrt(x_i ^ 2 + (x_i + 1) ^ 2) + 3(cos(2 * x_i) + sin(2 * x_i+1))
	} // end for

	return total;
} // end method ackleysOneFunction


inline double ackleysTwoFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 20.0 * (ui_SIZE - 1.0); // 20(n-1) + SUM

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	sumOfSquares = 0.0,
				temp		 = 0.0;

		temp = 0.5 * (cos(2 * _PI * dp_VECT[i]) + cos(2 * _PI * dp_VECT[i+1])); // (cos(2pi * x_i) + cos(2pi * x_i+1))/2

		sumOfSquares = 0.2 * sqrt(((dp_VECT[i] * dp_VECT[i]) + (dp_VECT[i+1] * dp_VECT[i+1])) * 0.5); // (sqrt((x_i^2 + (x_i+1)^2)/2))/5

		total += _E - (20 / exp(sumOfSquares)) - exp(temp);                // e - e ^ (sqrt((x_i^2 + (x_i+1)^2)/2))/5 - e ^ ((cos(2pi * x_i) + cos(2pi * x_i+1))/2)
	} // end for

	return total;
} // end method ackleysTwoFunction


inline double eggHolderFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0,
		product = 0.0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	temp = 0,
				temp2 = 0;

		temp = dp_VECT[i] * sin(sqrt(abs(dp_VECT[i] - dp_VECT[i+1] - 47)));					// sin( sqrt(|(x_i - x_(i+1) - 47)|)) * x_i

		temp2 = (dp_VECT[i+1] + 47) * sin(sqrt(abs((dp_VECT[i] / 2) + dp_VECT[i+1] + 47)));	// sin( sqrt( |(x_i/2) + x_(i+1) + 47| )) * (x_(i+1) + 47)

		total += temp + temp2;							  // (sin( sqrt(|(x_i - x_(i+1) - 47)|)) * x_i) + (sin( sqrt( |(x_i/2) + x_(i+1) + 47| )) * (x_(i+1) + 47))
	} // end for

	total *= -1; // - SUM

	return total;
} // end method eggHolderFunction


inline double ranaFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double	total = static_cast<double>(20 * (ui_SIZE - 1));

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	sum = 0,
				sumPlusXi = 0,
				sumMinXi = 0,
				temp = 0,
				temp2 = 0;

		sum = dp_VECT[i+1] + 1;			// x_(i+1) + 1

		sumPlusXi = abs(sum + dp_VECT[i]); // |(x_(i+1) + 1) + x_i|

		sumMinXi = abs(sum - dp_VECT[i]);  // |(x_(i+1) + 1) - x_i|

		temp = dp_VECT[i] * sin(sumMinXi) * cos(sumPlusXi);			// x_i * sin(|(x_(i+1) + 1) - x_i|) * cos(|(x_(i+1) + 1) + x_i|)
		temp2 = (dp_VECT[i+1] + 1) * cos(sumMinXi) * sin(sumPlusXi); // (x_(i+1) + 1) * cos(|(x_(i+1) + 1) - x_i|) * sin(|(x_(i+1) + 1) + x_i|)

		total += temp + temp2; // [ x_i * sin(|(x_(i+1) + 1) - x_i|) * cos(|(x_(i+1) + 1) + x_i|)] + [ (x_(i+1) + 1) * cos(|(x_(i+1) + 1) - x_i|) * sin(|(x_(i+1) + 1) + x_i|)]
	} // end for

	return total;
} // end method ranaFunction


inline double pathologicalFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0.5 * (ui_SIZE - 1);

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	temp = pow(sin(sqrt(100 * dp_VECT[i] * dp_VECT[i] + dp_VECT[i+1] * dp_VECT[i+1])), 2) - 0.5, // sin^2(sqrt( 100(x_i)^2 + x_(i+1)^2)) - 0.5
				temp2 = (0.001 * pow((dp_VECT[i] * dp_VECT[i] - 2 * dp_VECT[i] * dp_VECT[i+1] + dp_VECT[i+1] * dp_VECT[i+1]), 2)) + 1; // 0.001((x_i)^2 - 2(x_i) * x_(i+1) + (x_(i+1))^2)^2 + 1

		total += temp / temp2; // [ sin^2(sqrt( 100(x_i)^2 + x_(i+1)^2))^2 - 0.5 ] / [ 0.001((x_i)^2 - 2(x_i) * x_(i+1) + (x_(i+1))^2)^2 + 1 ]
	} // end for

	return total;
} // end method pathologicalFunction


inline double michalewiczFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0;

#pragma loop(hint_parallel(0))
	// SUM[1->n]
	for (std::size_t i = 0; i < ui_SIZE; i++)
	{
		double	temp = 0;

		temp = pow(sin(((i + 1) * dp_VECT[i] * dp_VECT[i]) / _PI), 20);	// sin^20((i * (x_i)^2) / pi)

		total += sin(dp_VECT[i]) * temp;									// sin(x_i) * sin((i * (x_i)^2) / pi)^20
	} // end for

	total *= -1; // - SUM

	return total;
} // end method michalewiczFunction


inline double masterCosineWaveFunction(const double* dp_VECT, const size_t ui_SIZE)
{
	double total = 0;

#pragma loop(hint_parallel(0))
	// SUM[1->n-1]
	for (std::size_t i = 0; i < ui_SIZE - 1; i++)
	{
		double	temp = 0,
				temp2 = 0;

		// x_i^2 + 0.5(x_i)(x_i+1) + (x_i+1)^2
		temp2 = temp = (dp_VECT[i] * dp_VECT[i]) + (0.5 * dp_VECT[i] * dp_VECT[i+1]) + (dp_VECT[i+1] * dp_VECT[i+1]);

		temp *= -0.125;                  // (-1/8)(x_i^2 + 0.5(x_i)(x_i+1) + (x_i+1)^2)

		temp2 = 4 * sqrt(temp2);         // 4( x_i^2 + 0.5(x_i)(x_i+1) + (x_i+1)^2 )

		total += exp(temp) * cos(temp2); // e^((-1/8)(x_i^2 + 0.5(x_i)(x_i+1) + (x_i+1)^2)) * cos( 4( x_i^2 + 0.5(x_i)(x_i+1) + (x_i+1)^2 ))
	} // end for

	total *= -1; // - SUM

	return total;
} // end method masterCosineWaveFunction


inline double shekelsFoxholesFunction(const double* dp_VECT, const size_t ui_SIZE, const std::size_t ui_M)
{
	static double da_C[30] = { 0.806,0.517,0.1,0.908,0.965,0.669,0.524,0.902,0.351,0.876,0.462,
							   0.491,0.463,0.741,0.352,0.869,0.813,0.811,0.0828,0.964,0.789,
							   0.360,0.369,0.992,0.332,0.817,0.632,0.883,0.608,0.326 };
	static double da_A[30][10] = {	{ 9.681, 0.667, 4.783, 9.095, 3.517, 9.325, 6.544, 0.211, 5.122, 2.02 },  { 9.4, 2.041, 3.788, 7.931, 2.882, 2.672, 3.568, 1.284, 7.033, 7.374 },
									{ 8.025, 9.152, 5.114, 7.621, 4.564, 4.711, 2.996, 6.126, 0.734, 4.982 }, { 2.196, 0.415, 5.649, 6.979, 9.510, 9.166, 6.304, 6.054, 9.377, 1.426 },
									{ 8.074, 8.777, 3.467, 1.863, 6.708, 6.349, 4.534, 0.276, 7.633, 1.567 }, { 7.650, 5.658, 0.720, 2.764, 3.278, 5.283, 7.474, 6.274, 1.409, 8.208 },
									{ 1.256, 3.605, 8.623, 6.905, 4.584, 8.133, 6.071, 6.888, 4.187, 5.448 }, { 8.314, 2.261, 4.24, 1.781, 4.124, 0.932, 8.129, 8.658, 1.208, 5.762 },
									{ 0.226, 8.858, 1.42, 0.954, 1.622, 4.698, 6.228, 9.096, 0.972, 7.637 },  { 7.305, 2.228, 1.242, 5.928, 9.133, 1.826, 4.06, 5.204, 8.713, 8.247 },
									{ 0.652, 7.027, 0.508, 4.876, 8.807, 4.632, 5.808, 6.937, 3.291, 7.016 }, { 2.699, 3.516, 5.847, 4.119, 4.461, 7.496, 8.817, 0.69, 6.593, 9.789 },
									{ 8.327, 3.897, 2.017, 9.57, 9.825, 1.15, 1.395, 3.885, 6.354, 0.109 },   { 2.132, 7.006, 7.136, 2.641, 1.882, 5.943, 7.273, 7.691, 2.88, 0.564 },
									{ 4.707, 5.579, 4.08, 0.581, 9.698, 8.542, 8.077, 8.515, 9.231, 4.67 },   { 8.304, 7.559, 8.567, 0.322, 7.128, 8.392, 1.472, 8.524, 2.277, 7.826 },
									{ 8.632, 4.409, 4.832, 5.768, 7.05, 6.715, 1.711, 4.323, 4.405, 4.591 },  { 4.887, 9.112, 0.17, 8.967, 9.693, 9.867, 7.508, 7.77, 8.382, 6.74 },
									{ 2.44, 6.686, 4.299, 1.007, 7.008, 1.427, 9.398, 8.48, 9.95, 1.675 },    { 6.306, 8.583, 6.084, 1.138, 4.350, 3.134, 7.853, 6.061, 7.457, 2.258 },
									{ 0.652, 2.343, 1.37, 0.821, 1.31, 1.063, 0.689, 8.819, 8.833, 9.07 },    { 5.558, 1.272, 5.756, 9.857, 2.279, 2.764, 1.284, 1.677, 1.244, 1.234 },
									{ 3.352, 7.549, 9.817, 9.437, 8.687, 4.167, 2.57, 6.54, 0.228, 0.027 },   { 8.798, 0.88, 2.37, 0.168, 1.701, 3.68, 1.231, 2.39, 2.499, 0.064 },
									{ 1.46, 8.057, 1.337, 7.217, 7.914, 3.615, 9.981, 9.198, 5.292, 1.224 },  { 0.432, 8.645, 8.774, 0.249, 8.081, 7.461, 4.416, 0.652, 4.002, 4.644 },
									{ 0.679, 2.8, 5.523, 3.049, 2.968, 7.225, 6.73, 4.199, 9.614, 9.229 },    { 4.263, 1.074, 7.286, 5.599, 8.291, 5.2, 9.214, 8.272, 4.398, 4.506 },
									{ 9.496, 4.83, 3.15, 8.27, 5.079, 1.231, 5.731, 9.494, 1.883, 9.732 },    { 4.138, 2.562, 2.532, 9.661, 5.611, 5.5, 6.886, 2.341, 9.699, 6.5 } };


	double total = 0;

#pragma loop(hint_parallel(0))
	// SUM[1->m]
	for (std::size_t i = 0; i < ui_M; i++)
	{
		double temp = 0;

		// SUM[1->n]
		for (std::size_t j = 0; j < ui_SIZE; j++)
		{
			temp += pow((dp_VECT[j] - da_A[i][j]), 2); // (x_j - a_i,j)^2
		} // end for

		total += 1 / (temp + da_C[i]); // 1 / ( SUM[1->n](x_j - a_i,j)^2 + C_i )
	} // end for

	total *= -1;

	return total;
} // end method shekelsFoxholesFunction


const std::vector<FitnessFunction>& getAllCostFunctions(const std::size_t arg2)
{
	static std::vector<FitnessFunction> functions
	{
		schwefelsFunction ,
		firstDeJongsFunction ,
		rosenbrockFunction ,
		rastriginFunction ,
		griewangkFunction ,
		sineEnvelopeSineWaveFunction ,
		stretchedVSineWaveFunction ,
		ackleysOneFunction ,
		ackleysTwoFunction ,
		eggHolderFunction ,
		ranaFunction ,
		pathologicalFunction ,
		michalewiczFunction ,
		masterCosineWaveFunction ,
		std::bind(shekelsFoxholesFunction,std::placeholders::_1, std::placeholders::_2, arg2),
	};

	return functions;
} // end method getAllCostFunctions

