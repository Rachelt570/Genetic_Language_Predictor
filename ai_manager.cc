#include "ai_manager.h"

void ai_manager::set_number_of_bots(unsigned int new_number_of_bots)
{
	if(new_number_of_bots == bots.size())
	{
		return;
	}
	if(new_number_of_bots > bots.size())
	{
		this->add_number_of_bots(new_number_of_bots - bots.size());
	}
	else
	{
		this->delete_number_of_bots(bots.size() - new_number_of_bots);
	}
}

void ai_manager::set_number_of_bots(std::vector<ai*> new_bots)
{
	this->bots = new_bots;
}
void ai_manager::add_number_of_bots(unsigned int bot_number)
{
	for(unsigned int i = 0; i < bot_number; i++)
	{
		ai * tmp;
		tmp = new ai;
		bots.push_back(tmp);
	}
}
void ai_manager::delete_number_of_bots(unsigned int bot_number)
{
	for(unsigned int i = 0; i < bot_number; i++)
	{
		bots.pop_back();
	}
}
unsigned int ai_manager::get_number_of_bots() const
{
	return this->bots.size();
}
ai* ai_manager::get_bot(unsigned int bot_number) const
{
	return this->bots.at(bot_number);
}
void ai_manager::set_bot(unsigned int bot_number, ai * bot) 
{
	this->bots.at(bot_number) = bot;
}

void ai_manager::push_back(ai * bot)
{
	this->bots.push_back(bot);
}

void ai_manager::pop_back()
{
	this->bots.pop_back();
}
bool ai_manager::compare_ai_pointer(ai * one, ai * two)
{
	return ((one->get_error_margin()) < (two->get_error_margin()));
}
void ai_manager::sort_bots()
{
	std::sort(bots.begin(), bots.end(), this->compare_ai_pointer);
}

void ai_manager::pass_input_biases(ai * father, ai * mother, ai * baby)
{

	for(unsigned int input_node_counter = 0; input_node_counter < father->get_number_of_input_nodes(); input_node_counter++)
	{
		double father_bias = father->get_input_bias(input_node_counter);
		double mother_bias = mother->get_input_bias(input_node_counter);
		double baby_bias = (((father_bias * mother_bias) + (father_bias * mother_bias * MUTATION_RATE) / 2));
		baby->set_input_bias(input_node_counter, baby_bias);
	}
}
void ai_manager::pass_hidden_biases(unsigned int hidden_layer, ai * father, ai * mother, ai * baby)
{
	for(unsigned int hidden_node_counter = 0; hidden_node_counter < father->get_number_of_hidden_nodes(hidden_layer); hidden_node_counter++)
	{
		double father_bias = father->get_hidden_bias(hidden_layer, hidden_node_counter);
		double mother_bias = mother->get_hidden_bias(hidden_layer, hidden_node_counter);
		double baby_bias = (((father_bias * mother_bias) + (father_bias * mother_bias * MUTATION_RATE) / 2));
		baby->set_hidden_bias(hidden_layer, hidden_node_counter, baby_bias);
	}
}
void ai_manager::pass_output_bises(ai * father, ai * mother, ai * baby)
{
	for(unsigned int output_node_counter = 0; output_node_counter < father->get_number_of_output_nodes(); output_node_counter++)
	{
		double father_bias = father->get_output_bias(output_node_counter);
		double mother_bias = mother->get_output_bias(output_node_counter);
		double baby_bias = (((father_bias * mother_bias) + (father_bias * mother_bias * MUTATION_RATE) / 2));
		baby->set_output_bias(output_node_counter, baby_bias);
	}
}
void ai_manager::pass_biases(ai * father, ai * mother, ai * baby)
{
	this->pass_input_biases(father, mother, baby);
	for(unsigned int counter = 0; counter < father->get_number_of_hidden_layers(); counter++)
	{
		this->pass_hidden_biases(counter, father, mother, baby);
	}
	this->pass_output_bises(father, mother, baby);
}

void ai_manager::pass_weights(ai * father, ai * mother, ai * baby)
{
	for(unsigned int weight_layer_counter = 0; weight_layer_counter < father->get_number_of_weight_layers(); weight_layer_counter++)
	{
		for(unsigned int weight_node_counter = 0; weight_node_counter < father->get_number_of_weight_nodes(weight_layer_counter); weight_node_counter++)
		{
			double father_weight = father->get_weight(weight_layer_counter, weight_node_counter);
			double mother_weight = mother->get_weight(weight_layer_counter, weight_node_counter);
			double baby_weight = (((father_weight * mother_weight) + (father_weight * mother_weight * MUTATION_RATE) / 2));
			baby->set_weight(weight_layer_counter, weight_node_counter, baby_weight);
		}
	}
}
ai * ai_manager::make_baby(ai * father, ai * mother)
{
	ai * baby;
	baby = new ai;
	baby->set_number_of_input_nodes(father->get_number_of_input_nodes() / (father->get_number_of_letters()));
	baby->set_number_of_hidden_layers(father->get_number_of_hidden_layers());
	for(unsigned int counter = 0; counter < father->get_number_of_hidden_layers(); counter++)
	{
		baby->set_number_of_hidden_nodes(counter, father->get_number_of_hidden_nodes(counter));
	}
	baby->set_number_of_output_nodes(father->get_number_of_output_nodes());


	return baby;
}
ai * ai_manager::breed(ai * father, ai * mother)
{

	ai * baby = this->make_baby(father, mother);
	baby->init_weights();
	pass_biases(father, mother, baby);
	pass_weights(father, mother, baby);

	return baby;
}

void ai_manager::kill_bot(unsigned int bot_index)
{
	delete bots.at(bot_index);
	return;
}