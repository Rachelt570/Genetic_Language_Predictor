#include "helper.h"

helper::helper()
{
}
double helper::relu(double value)
{
	if(0 > value)
	{
		return 0;
	}
	else
	{
		return value;
	}
}

int helper::random_int(int min, int max) 
{
	return (min + (std::rand() % (max - min + 1)));
	
}
double helper::random_double(double min, double max)
{
	double tmp =  (double)rand() / RAND_MAX;
	return min + tmp * (max - min);	
}

int helper::letter_to_int(char letter)
{
	if(letter <= 'Z')
	{
		return (int)(letter - 65);
	}
		return (int)(letter - 97);
}
char helper::int_to_letter(int number)
{
	if(number <= 25)
	{
		return (char)(number + 65);
	}
		return (char)(number + 97);
}
