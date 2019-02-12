#ifndef AI_H
#define AI_H
#include "node.h"
#include "helper.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream> //Should be removed (after debug is done)

	class ai
	{
		public:

			ai();

			unsigned int get_number_of_input_nodes() const;
			unsigned int get_number_of_hidden_layers() const;
			unsigned int get_number_of_hidden_nodes(unsigned int layer_number) const;
			unsigned int get_number_of_output_nodes() const;
			unsigned int get_number_of_weight_layers() const;
			unsigned int get_number_of_weight_nodes(unsigned int weight_layer_number) const;
			double get_output_value(unsigned int output_node) const;
			void set_number_of_input_nodes(unsigned int new_number_of_input_nodes);
			void set_number_of_hidden_layers(unsigned int new_number_of_hidden_layers);
			void set_number_of_hidden_nodes(unsigned int layer_number, unsigned int new_number_of_hidden_nodes);
			void set_number_of_output_nodes(unsigned int new_number_of_output_nodes);

			double get_input_bias(unsigned int input_node_number) const;
			double get_hidden_bias(unsigned int hidden_layer_number, unsigned int hidden_node_number) const;
			double get_output_bias(unsigned int output_node_number) const;

			void set_input_bias(unsigned int input_node_number, double new_bias);
			void set_hidden_bias(unsigned int hidden_layer_number, unsigned int hidden_node_number, double new_bias);
			void set_output_bias(unsigned int output_node_number, double new_bias);


			void init_weights(); //Initalizes network with new weights
			void set_weight(unsigned int layer_number, unsigned int weight_number, double newWeight); 
			double get_weight(unsigned int layer_number, unsigned int weight_number) const;

			bool verify_network(); // Ensures the network has input nodes, hidden nodes, inited weights, and output nodes
			void get_input(); //Loads values into input nodes
			void push_input(); //Pushes the values in input node through the network
			void check_output(); //Checks the accuracy of the network

			double get_error_margin() const; //Gets the overall error margin
			void clear_error_margin();

		 	unsigned int get_number_of_letters() const;
		private:

			helper help;

			bool verify_structure(); // Ensures the network has input nodes hidden nodes, and output nodes.
			void init_weight_layers(); //Pushes a number of layers, equal to the number of layers of synapses 
			void init_weight_nodes(); // Populates weight layers with weight nodes
			void open_input_streams();
			void close_input_streams();
			void push_input_to_hidden(); //Pushes the input layer to the hidden layer
			void push_hidden_to_hidden(unsigned int hidden_layer_number); //Pushes a hidden layer to the next hidden layer
			void push_hidden_to_output(); //Pushes the last hidden layer to the output layer
			std::string get_word(std::ifstream * dictionary, unsigned int word_number);
			void delete_nodes(std::vector<node*> &layer, unsigned int number_of_nodes_to_delete);
			void add_nodes(std::vector<node*> &layer, unsigned int number_of_nodes_to_add);


			unsigned int get_total_number_of_layers() const;
			unsigned int get_selected() const;

			double error_margin;
			bool weights_initted;
			const double MINIMUM_STARTING_WEIGHT = -2;
			const double MAXIMUM_STARTING_WEIGHT = 2;	
			unsigned int dictionary_selected;

			std::vector<std::ifstream*> input_streams;
			const unsigned int MAX_WORD_NUMBER = 1000000;
			const unsigned int NUMBER_OF_INPUT_STREAMS = 2;
			const unsigned int NUMBER_OF_LETTERS = 26;
			const unsigned int VALUE_OF_POSITIVE_INPUT = 1;
			const int VALUE_OF_POSITIVE_OUTPUT = 1;
			std::vector<node*> input_nodes;
			std::vector<std::vector<node*>*> hidden_nodes;
			std::vector<node*> output_nodes;

			std::vector<std::vector<double*>> weights;

		
	};

#endif