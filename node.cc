#include "node.h"

node::node()
{
	this->value = 0;
	this->value_component = 0;
	this->number_of_value_components = 0;
	this->bias = help.random_double(MINIMUM_STARTING_BIAS, MAXIMUM_STARTING_BIAS);
}
void node::clear_value()
{
	this->value = 0;
	this->value_component = 0;
	this->number_of_value_components = 0;
}
double node::get_value() const
{
	return this->value;
}
void node::set_value(double new_value)
{
	this->value = new_value;
	return;
}
void node::set_bias(double new_bias)
{
	this->bias = new_bias;
}
double node::get_bias() const
{
	return this->bias;
}
void node::add_value(double new_value_component)
{
	this->value_component += new_value_component;
	this->number_of_value_components++;
	return;
}
void node::push_value()
{
	if(this->value_component == 0)
	{
		this->value = 0;
		return;
	}
	this->value_component += this->bias;
	this->value = (this->value_component / (double)this->number_of_value_components);
	this->number_of_value_components = 0;
	return;
}