#ifndef INDOORPLAYER_H
#define INDOORPLAYER_H

class IndoorPlayer
{
		public:
			IndoorPlayer();
			~IndoorPlayer();

			void setX(float xval) {x = xval;}
			void setY(float yval) {y = yval;}
		
			float getX() {return x;}
			float getY() {return y;}
			
			void changeX(float changex); 
			void changeY(float changey);
			
			void setRoom(int roomVal) {indoorLocation = roomVal;}
			int getRoom() {return indoorLocation;}

			void setDir(int dir) {direction = dir;}
			int getDir() {return direction;}

			void startWalk() {walking = true;}
			void stopWalk() {walking = false;}
		
			bool isWalk() {return walking;}

			SDL_Surface *indoorSprite;

			void setFrame(float frame) {p_frame = frame;}
			float getFrame() {return p_frame;}
			void changeFrame(float change) {p_frame += change;}

			int frame_dir;
			
		private:
			
				float x;
				float y;
				
				int direction;

				float p_frame;

				bool walking;
				
				int indoorLocation;
};

#endif
