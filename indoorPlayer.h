#ifndef INDOORPLAYER_H
#define INDOORPLAYER_H

class IndoorPlayer
{
		public:
			IndoorPlayer();
			~IndoorPlayer();

			void setX(float xval) {indoorx = xval;}
			void setY(float yval) {indoory = yval;}
		
			float getX() {return indoorx;}
			float getY() {return indoory;}
			
			void changeX(float changex); 
			void changeY(float changey);
			
			void setRoom(int roomVal) {indoorLocation = roomVal;}
			int getRoom() {return indoorLocation;}

			void setDir(int dir) {direction = dir;}
			int getDir() {return direction;}

			void startWalk() {walking = true;}
			void stopWalk() {walking = false;}
		
			int getXvel() {return xvel;}
			int getYvel() {return yvel;}

			void setXvel(int xvval) {xvel = xvval;}
			void setYvel(int yvval) {yvel = yvval;}
				
			void throttleX(int xch) {xvel += xch;}
			void throttleY(int ych) {yvel += ych;}

		
			bool isWalk() {return walking;}

			SDL_Surface *indoorSprite;

			void setFrame(float frame) {p_frame = frame;}
			float getFrame() {return p_frame;}
			void changeFrame(float change) {p_frame += change;}
			
			void moveChar();
			void handleIndoorInput();

			int frame_dir;
			
		private:
			
				float indoorx;
				float indoory;
				
				int direction;
	
	
				int xvel = 0;
				int yvel = 0;
				
				float p_frame;

				bool walking;
				
				int indoorLocation;
};

#endif
