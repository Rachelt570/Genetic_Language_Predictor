#ifndef HELPER_H
#define HELPER_H
#include <cmath>
#include <cstdlib>
#include <ctime>

	class helper
	{
		public:


			helper();
			static double relu(double value);
			static int random_int(int min, int max);
			static double random_double(double min, double max);
			static int letter_to_int(char letter);
			static char int_to_letter(int number);
		private:
			unsigned long seed;
	};

#endif