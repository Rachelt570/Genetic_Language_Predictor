#include "ai.h"
#include <iostream>
void display_main_menu();
void display_view_node_menu();
void display_set_node_menu();
int main()
{
	srand(time(NULL));
	ai testBot;
	int user_input;
	while(1) {
		do
		{
			display_main_menu();
			std::cin >> user_input;
		} while(user_input < 1 || user_input > 3);

		switch(user_input)
		{
			case 1:
			{
				do
				{
					display_view_node_menu();
					std::cin >> user_input;
				} while(user_input < 1 || user_input > 4);
				switch(user_input)
				{
					case 1:
						std::cout << "Number of Input Nodes: " << testBot.get_number_of_input_nodes() << std::endl;
						break;
					case 2:
						std::cout << "Number of Hidden Layers: " << testBot.get_number_of_hidden_layers() << std::endl;
						break;
					case 3:
						int hidden_layer_number;
						std::cout << "Enter the hidden layer number" << std::endl;
						std::cin >> hidden_layer_number;
						if(hidden_layer_number < 0 || hidden_layer_number >= (signed int)testBot.get_number_of_hidden_layers())
						{
							break;
						}
						else
						{
							std::cout << "NUmber of Hidden Nodes: " << testBot.get_number_of_hidden_nodes(hidden_layer_number) << std::endl;
							break;
						}
					case 4:
						std::cout << "Number of Output Nodes: " << testBot.get_number_of_output_nodes() << std::endl;
						break;
				}
				break;
			}

			case 2:
			{
				do
				{
					display_set_node_menu();
					std::cin >> user_input;	
				} while(user_input < 1 || user_input > 4);
				switch(user_input)
				{
					case 1:
						std::cout << "Enter the desired number of input nodes" << std::endl;
						unsigned int desired_number_of_input_nodes;
						std::cin >> desired_number_of_input_nodes;
						testBot.set_number_of_input_nodes(desired_number_of_input_nodes);
						break;

					case 2:
						std::cout << "Enter the desired number of hidden layers" << std::endl;
						unsigned int desired_number_of_hidden_layers;
						std::cin >> desired_number_of_hidden_layers;
						testBot.set_number_of_hidden_layers(desired_number_of_hidden_layers);
						break;

					case 3:
						std::cout << "Enter the hidden layer number" << std::endl;
						unsigned int hidden_layer_number;
						std::cin >> hidden_layer_number;
						if(hidden_layer_number >= testBot.get_number_of_hidden_layers())
						{
							break;
						}
						else
						{
							std::cout << "Enter the desired number of Hidden Nodes" << std::endl;
							unsigned int desired_number_of_hidden_nodes;
							std::cin >> desired_number_of_hidden_nodes;
							testBot.set_number_of_hidden_nodes(hidden_layer_number, desired_number_of_hidden_nodes);
							break;
						}
					case 4:
						std::cout << "Enter the desired number of output nodes" << std::endl;
						unsigned int desired_number_of_output_nodes;
						std::cin >> desired_number_of_output_nodes;
						testBot.set_number_of_output_nodes(desired_number_of_output_nodes);
						break;
				}
				break;
			}
			case 3:
				testBot.clear_error_margin();
				testBot.get_input();
				testBot.push_input();
				testBot.check_output();
				break;
		}
	}
	return 0;
}
void display_main_menu() 
{
	std::cout << "1. View Node Count" << std::endl;
	std::cout << "2. Set Node Count" << std::endl;
	std::cout << "3. Get Input" << std::endl;
	return;
}
void display_view_node_menu()
{
	std::cout << "1. View number of Input Nodes" << std::endl;
	std::cout << "2. View number of Hidden Layers" << std::endl;
	std::cout << "3. View number of Hidden Nodes" << std::endl;
	std::cout << "4. View number of Output Nodes" << std::endl;
	return;
}
void display_set_node_menu()
{
	std::cout << "1. Set number of Input Nodes" << std::endl;
	std::cout << "2. Set number of Hidden Layers" << std::endl;
	std::cout << "3. Set Number of Hidden Nodes" << std::endl;
	std::cout << "4. Set Number of Output Nodes" << std::endl;
}