#include "ai.h"

ai::ai()
{
	this->error_margin = 0;
	this->weights_initted = false;
	this->dictionary_selected = 0;
}

unsigned int ai::get_number_of_input_nodes() const
{

	return this->input_nodes.size();
}

unsigned int ai::get_number_of_hidden_layers() const
{
	return hidden_nodes.size();
}

unsigned int ai::get_number_of_hidden_nodes(unsigned int hidden_layer_number) const
{
	return hidden_nodes.at(hidden_layer_number)->size();
}

unsigned int ai::get_number_of_output_nodes() const
{
	return output_nodes.size();
}

unsigned int ai::get_number_of_weight_layers() const
{
	return weights.size();
}
unsigned int ai::get_number_of_weight_nodes(unsigned int weight_layer_number) const
{
	return weights.at(weight_layer_number).size();	
}
double ai::get_input_bias(unsigned int input_node_number) const
{
	return (input_nodes.at(input_node_number)->get_bias());
}
double ai::get_hidden_bias(unsigned int hidden_layer_number, unsigned int hidden_node_number) const
{
	return (hidden_nodes.at(hidden_layer_number)->at(hidden_node_number)->get_bias());
}
double ai::get_output_bias(unsigned int output_node_number) const
{
	return (output_nodes.at(output_node_number)->get_bias());
}
double ai::get_output_value(unsigned int output_index) const
{
	return output_nodes.at(output_index)->get_value();
}

unsigned int ai::get_number_of_letters() const
{
	return NUMBER_OF_LETTERS;
}

void ai::set_input_bias(unsigned int input_node_number, double new_bias)
{
	input_nodes.at(input_node_number)->set_bias(new_bias);
	return;
}
void ai::set_hidden_bias(unsigned int hidden_layer_number, unsigned int hidden_node_number, double new_bias)
{
	hidden_nodes.at(hidden_layer_number)->at(hidden_node_number)->set_bias(new_bias);
}
void ai::set_output_bias(unsigned int output_node_number, double new_bias)
{
	output_nodes.at(output_node_number)->set_bias(new_bias);
}

double ai::get_weight(unsigned int weight_layer_number, unsigned int weight_node_number) const
{
	return *weights.at(weight_layer_number).at(weight_node_number);
}

void ai::set_weight(unsigned int weight_layer_number, unsigned int weight_node_number, double new_weight)
{
	*this->weights.at(weight_layer_number).at(weight_node_number) = new_weight;
	return;
}
void ai::delete_nodes(std::vector<node*> &layer, unsigned int number_of_nodes)
{
	this->weights_initted = false;
	for(unsigned int counter = 0; counter < number_of_nodes; counter++)
	{
		layer.pop_back();
	}
	return;
}

void ai::add_nodes(std::vector<node*> &layer, unsigned int number_of_nodes)
{
	this->weights_initted = false;
	for(unsigned int counter = 0; counter < number_of_nodes; counter++)
	{
		node * tmp;
		tmp = new node;
		layer.push_back(tmp);
	}
	return;
}

void ai::set_number_of_hidden_layers(unsigned int new_number_of_hidden_layers)
{
	if(this->get_number_of_hidden_layers() == new_number_of_hidden_layers)
	{
		return;
	}

	this->weights_initted = false;

	unsigned int number_of_hidden_layers = this->get_number_of_hidden_layers();

	if(number_of_hidden_layers > new_number_of_hidden_layers)
	{
		for(unsigned int counter = number_of_hidden_layers; counter > new_number_of_hidden_layers; counter--)
		{
			hidden_nodes.pop_back();
		}
		return;
	}
	else
	{
		for(unsigned int counter = number_of_hidden_layers; counter < new_number_of_hidden_layers; counter++)
		{
			std::vector<node*> * tmp;
			tmp = new std::vector<node*>;
			hidden_nodes.push_back(tmp);
		}
		return;
	}
}


void ai::set_number_of_input_nodes(unsigned int new_number_of_input_nodes)
{
	unsigned int desired_number_of_nodes = (new_number_of_input_nodes * this->NUMBER_OF_LETTERS);
	if(this->get_number_of_input_nodes() == desired_number_of_nodes)
	{
		return;
	}
	if(this->get_number_of_input_nodes() > desired_number_of_nodes)
	{
		unsigned int number_of_nodes = (this->get_number_of_input_nodes() - desired_number_of_nodes);
		this->delete_nodes(input_nodes, number_of_nodes);
		return;
	}
	else
	{
		unsigned int number_of_nodes = (desired_number_of_nodes - this->get_number_of_input_nodes());
		this->add_nodes(input_nodes, number_of_nodes);
	}
}

void ai::set_number_of_hidden_nodes(unsigned int hidden_layer_number, unsigned int new_number_of_hidden_nodes)
{
	if(this->get_number_of_hidden_nodes(hidden_layer_number) == new_number_of_hidden_nodes)
	{
		return;
	}
	if(this->get_number_of_hidden_nodes(hidden_layer_number) > new_number_of_hidden_nodes)
	{
		unsigned int number_of_nodes = (this->get_number_of_hidden_nodes(hidden_layer_number) - new_number_of_hidden_nodes);
		this->delete_nodes(*hidden_nodes.at(hidden_layer_number), number_of_nodes);
		return;		
	}
	else
	{
		unsigned int number_of_nodes = (new_number_of_hidden_nodes - this->get_number_of_hidden_nodes(hidden_layer_number));
		this->add_nodes(*hidden_nodes.at(hidden_layer_number), number_of_nodes);
		return;
	}
}
void ai::set_number_of_output_nodes(unsigned int new_number_of_output_nodes)
{
	if(this->get_number_of_output_nodes() == new_number_of_output_nodes)
	{
		return;
	}
	if(this->get_number_of_output_nodes() > new_number_of_output_nodes)
	{
		unsigned int number_of_nodes = (this->get_number_of_output_nodes() - new_number_of_output_nodes);
		this->delete_nodes(output_nodes, number_of_nodes);
		return;
	}
	else
	{
		unsigned int number_of_nodes = (new_number_of_output_nodes - this->get_number_of_output_nodes());
		this->add_nodes(output_nodes, number_of_nodes);
		return;
	}
}

unsigned int ai::get_total_number_of_layers() const
{
	return this->get_number_of_hidden_layers() + 2;
}
void ai::init_weight_layers()
{
	for(unsigned int counter = 0; counter < (this->get_number_of_hidden_layers()+1); counter++)
	{
		std::vector<double*> * tmp;
		tmp = new std::vector<double*>;
		weights.push_back(*tmp);
	}
}
void ai::init_weight_nodes()
{
	for(unsigned int weight_layer_counter = 0; weight_layer_counter < weights.size(); weight_layer_counter++)
	{
		unsigned int needed_weights = 0; //The number of weights to be added to this layer

		if(weight_layer_counter == 0) //If first layer of weights
		{
			needed_weights = ((this->get_number_of_input_nodes()) * (this->get_number_of_hidden_nodes(0)));
		}
		else 
		{
			if(weight_layer_counter == (weights.size() - 1)) //If last layer of weights
			{
				needed_weights = ((this->get_number_of_output_nodes()) * (this->get_number_of_hidden_nodes(weight_layer_counter-1)));
			}
			else
			{
				needed_weights = ((this->get_number_of_hidden_nodes(weight_layer_counter) * this->get_number_of_hidden_nodes(weight_layer_counter -1)));
			}
		}
		for(unsigned int counter = 0; counter < needed_weights-1; counter++)
		{
			double * tmp;
			tmp = new double;
			*tmp = help.random_double(MINIMUM_STARTING_WEIGHT, MAXIMUM_STARTING_WEIGHT);
			weights.at(weight_layer_counter).push_back(tmp);
		}
	}

}
void ai::init_weights()
{
	if(!this->verify_structure()) // If the network does not have input nodes, hidden nodes, and output nodes abort.
	{
		return;
	}
	this->init_weight_layers();
	this->init_weight_nodes();
	weights_initted = true;
}

//void set_weight(unsigned int layer_number, unsigned int weight_number, double newWeight); 
//double get_weight(unsigned int layer_number, unsigned int weight_number) const;


bool ai::verify_structure()
{
	if(!weights_initted)
	{
		weights_initted = true;
		if(this->verify_network())
		{
			weights_initted = false;
			return true;
		}
		else
		{
			weights_initted = false;
			return false;
		}
	}
	else
	{
		return this->verify_network();
	}
}
bool ai::verify_network()
{
	if(!weights_initted)
	{
		return false;
	}
	if(this->get_number_of_input_nodes() == 0)
	{
		return false;
	}
	if(this->get_number_of_hidden_layers() == 0)
	{
		return false;
	}
	for(unsigned int counter = 0; counter < this->get_number_of_hidden_layers(); counter++)
	{
		if(this->get_number_of_hidden_nodes(counter) == 0)
		{
			return false;
		}
	}
	if(this->get_number_of_output_nodes() == 0)
	{
		return false;
	}
	return true;
}

void ai::open_input_streams() //Should make drier 
{
	for(unsigned int counter = 0; counter < this->NUMBER_OF_INPUT_STREAMS; counter++)
	{
		std::ifstream * tmp;
		tmp = new std::ifstream;
		input_streams.push_back(tmp);
	}
	input_streams.at(0)->open("English.txt");
	input_streams.at(1)->open("French.txt");
}

void ai::close_input_streams()
{
	for(unsigned int counter = 0; counter < this->NUMBER_OF_INPUT_STREAMS; counter++)
	{
		input_streams.at(counter)->close();
	}
}

void ai::get_input()
{	
	if(!this->verify_structure())
	{
		return;
	}
	if(!weights_initted) 
	{
		this->init_weights();
	}
	for(unsigned int input_counter = 0; input_counter < this->get_number_of_input_nodes(); input_counter++)
	{
		input_nodes.at(input_counter)->clear_value();
	}
	this->open_input_streams();
	this->dictionary_selected = help.random_int(0, 1);
	std::string word_selected;
	unsigned int word_number; 
	word_number = help.random_int(0, this->MAX_WORD_NUMBER);
	word_selected = this->get_word(this->input_streams.at(this->dictionary_selected), word_number);

	for(unsigned int letter_counter = 0; letter_counter < word_selected.length(); letter_counter++)
	{
		char letter;
		unsigned int letter_index;
		letter = word_selected[letter_counter];
		letter_index = help.letter_to_int(letter); //which component is firing
		for(unsigned int component_counter = 0; component_counter < this->NUMBER_OF_LETTERS; component_counter++)
		{
			if(this->get_number_of_input_nodes()-1 < ((this->NUMBER_OF_LETTERS * letter_counter) + component_counter))
			{
					break;
			}
			if(letter_index == component_counter)
			{
				double value_to_add = (this->VALUE_OF_POSITIVE_INPUT);
				input_nodes.at((this->NUMBER_OF_LETTERS * letter_counter) + component_counter)->add_value(value_to_add);
			}
			else
			{
				input_nodes.at((this->NUMBER_OF_LETTERS * letter_counter) + component_counter)->add_value(0);
			}
		}
	}
	this->close_input_streams();

	for(unsigned int counter = 0; counter < this->get_number_of_input_nodes(); counter++)
	{
		input_nodes.at(counter)->push_value();
		
	}

}

std::string ai::get_word(std::ifstream * dictionary, unsigned int word_number)
{
	std::string word_selected;
	for(unsigned int counter = 0; counter < word_number; counter++)
	{
		if(dictionary->eof())
		{
			dictionary->clear();
			dictionary->seekg(0, std::ios::beg);
		}
		
		std::getline((*dictionary), word_selected);
	}
	return word_selected;
}



void ai::push_input()
{
	this->push_input_to_hidden();
	for(unsigned int hidden_layer_counter = 0; hidden_layer_counter < this->get_number_of_hidden_layers() - 1; hidden_layer_counter++)
	{
		this->push_hidden_to_hidden(hidden_layer_counter);
	}
	this->push_hidden_to_output();

}

void ai::push_input_to_hidden()
{

	for(unsigned int counter = 0; counter < this->get_number_of_hidden_nodes(0); counter++)
	{
		hidden_nodes.at(0)->at(counter)->clear_value();
	}
	for(unsigned int counter = 0; counter < this->get_number_of_input_nodes(); counter++)
	{
		double value_to_push = input_nodes.at(counter)->get_value();
		value_to_push = help.relu(value_to_push); //Activation function f(x) = max(0, x);
		if(value_to_push != 0)
		{
			for(unsigned int hidden_node_counter = 0; hidden_node_counter < this->get_number_of_hidden_nodes(0); hidden_node_counter++)
				{
					hidden_nodes.at(0)->at(hidden_node_counter)->add_value(value_to_push);
				}
		}
	}
		for(unsigned int hidden_node_counter = 0; hidden_node_counter < this->get_number_of_hidden_nodes(0); hidden_node_counter++)
		{
			hidden_nodes.at(0)->at(hidden_node_counter)->push_value();
		}
}

void ai::push_hidden_to_hidden(unsigned int hidden_layer_number)
{
	for(unsigned int counter = 0; counter < this->get_number_of_hidden_nodes(hidden_layer_number+1); counter++)
	{
		hidden_nodes.at(hidden_layer_number+1)->at(counter)->clear_value();
	}
	for(unsigned int counter = 0; counter < this->get_number_of_hidden_nodes(hidden_layer_number); counter++)
	{
		double value_to_push = hidden_nodes.at(hidden_layer_number)->at(counter)->get_value();
		value_to_push = help.relu(value_to_push);
		if(value_to_push != 0)
		{
			for(unsigned int next_layer_counter = 0; next_layer_counter < this->get_number_of_hidden_nodes(hidden_layer_number+1); next_layer_counter++)
			{
				hidden_nodes.at(hidden_layer_number)->at(hidden_layer_number+1)->add_value(value_to_push);
			}
		}
	}
		for(unsigned int next_layer_counter = 0; next_layer_counter < this->get_number_of_hidden_nodes(hidden_layer_number+1); next_layer_counter++)
			{
				hidden_nodes.at(hidden_layer_number)->at(hidden_layer_number+1)->push_value();
			}
}

void ai::push_hidden_to_output() 
{
	for(unsigned int counter = 0; counter < this->get_number_of_output_nodes(); counter++)
	{
		output_nodes.at(counter)->clear_value();
	}
	for(unsigned int counter = 0; counter < this->get_number_of_hidden_nodes(this->get_number_of_hidden_layers()-1); counter++)
	{
		double value_to_push = hidden_nodes.at(this->get_number_of_hidden_layers()-1)->at(counter)->get_value();
		value_to_push = help.relu(value_to_push);
		if(value_to_push != 0)
		{
			for(unsigned int output_node_counter = 0; output_node_counter < this->get_number_of_output_nodes(); output_node_counter++)
			{
				output_nodes.at(output_node_counter)->add_value(value_to_push);
			}
		}
	}
	for(unsigned int output_node_counter = 0; output_node_counter < this->get_number_of_output_nodes(); output_node_counter++)
	{
		output_nodes.at(output_node_counter)->push_value();		
		output_nodes.at(output_node_counter)->set_value(tanh(output_nodes.at(output_node_counter)->get_value()));
	}	
}
unsigned int ai::get_selected() const
{
	unsigned int largest_index = 0;
	double largest_value =  output_nodes.at(0)->get_value();
	for(unsigned int counter = 0; counter < this->get_number_of_output_nodes(); counter++)
	{
		if(output_nodes.at(counter)->get_value() > largest_value)
		{
			largest_value = output_nodes.at(counter)->get_value();
			largest_index = counter;
		}
	}
	return largest_index;
}
void ai::check_output()
{
	unsigned int selected = this->get_selected();
	for(unsigned int output_counter = 0; output_counter < this->get_number_of_output_nodes(); output_counter++)
	{
		if(output_counter == selected)
		{
			double error_margin_comp;
			error_margin_comp = (1 - output_nodes.at(output_counter)->get_value());
			error_margin += error_margin_comp;
		}
		else 
		{
			double error_margin_comp;
			error_margin_comp = ((output_nodes.at(output_counter)->get_value()));
			error_margin += error_margin_comp;
		}
	}
}

double ai::get_error_margin() const
{
	return this->error_margin;
}
void ai::clear_error_margin()
{
	this->error_margin = 0;
}
