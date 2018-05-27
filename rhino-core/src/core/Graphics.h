#pragma once

namespace rhino{

	class Application;
	class Window;

	class Graphics {

		friend class rhino::Application;
		friend class rhino::Window;

		private:
			static unsigned int width, height;

		public:

			static unsigned int getWidth() { return width; }
			static unsigned int getHeight() { return height; }


	};

	

}