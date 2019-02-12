#ifndef NODE_H
#define NODE_H
#include "helper.h"

	class node
	{
		public:
			node();
			void clear_value();
			double get_value() const;
			void set_value(double new_value);
			double get_bias() const;
			void set_bias(double new_bias);
			void add_value(double new_value_component);
			void push_value();

		private:
			helper help;
			const double MINIMUM_STARTING_BIAS = -1;
			const double MAXIMUM_STARTING_BIAS = 1;
			double value;
			double value_component;
			double number_of_value_components;
			double bias;
	};

#endif