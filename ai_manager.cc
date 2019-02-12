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
void ai_manager::sort_bots()
{
//	std::sort(bots.begin(), bots.end(), bots);
}