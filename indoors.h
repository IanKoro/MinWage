#ifndef INDOORS_H
#define INDOORS_H

class IndoorHandler
{
		public:
			IndoorHandler();
			~IndoorHandler();
			void drawRoomView();
			
			bool isInside() {return isIndoors;}
			void goInside(int roomNumber);
			void goOutside();			
			
		private:
			bool isIndoors;
};

#endif
