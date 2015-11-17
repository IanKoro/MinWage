#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

class InventoryItem
{
	public:
	private:
		int id_num;
		std::string name;
};

class PlayerInventory
{
		public:
			PlayerInventory() {}
			~PlayerInventory() {}	
			
			void gameStart();
			
			int getMoney() {return money;}
		private:
			int money;
};


#endif
