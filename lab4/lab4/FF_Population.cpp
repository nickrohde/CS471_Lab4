#include "FF_Population.hpp"


#pragma region Public:
	#pragma region Constructors:
		FF_Population::FF_Population(const Population_Info & POP_INFO, const Bounds & BOUNDS, const FF_Info & FF_INFO) : Population(POP_INFO.ui_size, POP_INFO.ui_dim, BOUNDS)
		{
			d_alpha = FF_INFO.alpha;
			d_beta = FF_INFO.beta;
			d_gamma = FF_INFO.gamma;
			d_intensity = FF_INFO.intensity;
		} // end Constructor


		FF_Population::FF_Population(const FF_Population & OTHER) : Population(OTHER)
		{
			(*this) = OTHER;
		} // end Copy Constructor


		FF_Population::FF_Population(FF_Population && other) noexcept : Population(other)
		{
			d_alpha = other.d_alpha;
			d_beta = other.d_beta;
			d_gamma = other.d_gamma;
			d_intensity = other.d_intensity;
		} // end Move Constructor

	#pragma endregion

	#pragma region Operations:
		void FF_Population::shiftTowards(const std::size_t j, const std::size_t k, const double d_BETA)
		{
			for (std::size_t i = 0; i < ui_length; i++)
			{
				dp_pop[k][i] = dp_pop[k][i] + (d_BETA * (dp_pop[j][i] - dp_pop[k][i])) + (getRandomRealInRange<double>(0.0, 1.0) * getRandomRealInRange<double>(0.0,1.0));

				while (dp_pop[k][i] < bounds.d_min)
				{
					dp_pop[k][i] = bounds.d_min + getRandomRealInRange<double>(0.0, 1.0)*(bounds.d_max - bounds.d_min);
				} // end while
				while (dp_pop[k][i] > bounds.d_max)
				{
					dp_pop[k][i] = bounds.d_max - getRandomRealInRange<double>(0.0, 1.0)*(bounds.d_max - bounds.d_min);
				} // end while
			} // end for
		} // end method shiftTowards


		double FF_Population::distance(const std::size_t j, const std::size_t k)
		{
			if (j < ui_size && k < ui_size)
			{
				double r = 0.0;

				for (std::size_t i = 0; i < ui_length; i++)
				{
					r = r + pow((*this)[j][i] - (*this)[k][i],2);
				} // end for

				return sqrt(r);
			} // end if

			throw std::out_of_range("Indices received out of bounds!");
		} // end method distance

	#pragma endregion

	#pragma region Operators:
		FF_Population& FF_Population::operator=(const FF_Population& OTHER)
		{
			Population::operator=(OTHER);

			d_alpha = OTHER.d_alpha;
			d_beta = OTHER.d_beta;
			d_gamma = OTHER.d_gamma;
			d_intensity = OTHER.d_intensity;

			return (*this);
		} // end Copy Assignment


		FF_Population & FF_Population::operator=(FF_Population && other) noexcept
		{
			Population::operator=(other);

			d_alpha = other.d_alpha;
			d_beta = other.d_beta;
			d_gamma = other.d_gamma;
			d_intensity = other.d_intensity;

			return (*this);
		} // end Move Assignment

	#pragma endregion

#pragma endregion
