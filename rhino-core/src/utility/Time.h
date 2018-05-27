#pragma once


namespace rhino {

	class Time {
		friend class Window;

		private:

			static double frameStart;
			static double gameScale;
			static double scaledGameTime;
			static double timeScale;
			static double deltaTime;

		
			static void startGame();
			static void startNewFrame();

		public:
			static double getTime();
			static double getUnscaledTime();

			static double getDeltaTime();
			static double getUnscaledDeltaTime();

			static void setTimeScale(double timeScale);

	};

}