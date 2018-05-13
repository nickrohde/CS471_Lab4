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


inline double shekelsFoxholesFunction(const double* dp_VECT, const size_t ui_SIZE, const double** da_A, const std::size_t ui_M)
{
	static double da_C[] = { 0.806,0.517,0.1,0.908,0.965,0.669,0.524,0.902,0.351,0.876,0.462,
							0.491,0.463,0.741,0.352,0.869,0.813,0.811,0.0828,0.964,0.789,
							0.360,0.369,0.992,0.332,0.817,0.632,0.883,0.608,0.326 };

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


const std::vector<fitnessFunction>& getAllCostFunctions(const double ** arg1, const std::size_t arg2)
{
	static std::vector<fitnessFunction> functions
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
		std::bind(shekelsFoxholesFunction,std::placeholders::_1, std::placeholders::_2, arg1, arg2),
	};

	return functions;
} // end method getAllCostFunctions

