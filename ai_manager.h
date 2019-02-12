#ifndef AI_MANAGER_H
#define AI_MANAGER_H
#include "ai.h"
#include "helper.h"
#include <algorithm>
#include <vector>
	class ai_manager

	{
		public:

			void set_number_of_bots(unsigned int new_number_of_bots); //Creates new random bots, or deletes from back of vector
			void set_number_of_bots(std::vector<ai*> new_bots); //Sets bots = new_bots

			unsigned int get_number_of_bots() const; // Returns ai.size();

			ai* get_bot(unsigned int bot_number) const; // Returns the bot in position bot_number
			void set_bot(unsigned int bot_number, ai * bot); // Sets the bot in position bot_number to be equal to the passed bot

			void push_back(ai * bot); //Adds to back of the vector.
			void pop_back(); //Delete from back of the vector.


			void sort_bots(); //Uses std::sort to sort the bots
			void kill_bots(); //Kills the weakest performing bots

		private:
			std::vector<ai*> bots;
			
			ai breed(ai &father, ai &mother); //Returns a bot with an average of the the weights and biases of it's parents.
			void add_number_of_bots(unsigned int bot_number);
			void delete_number_of_bots(unsigned int bot_number);
		};
#endif