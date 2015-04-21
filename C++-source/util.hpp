#ifndef SRC_UTIL_HPP
#define SRC_UTIL_HPP

class Util {
	private:
		const int mMaxListSize = 5000;	// Replaces #define LIST_SIZE 5000 /* max number of pieces on board */
		bool mInFree[mMaxListSize];
		bool mInObj[mMaxListSize];
		bool mInLoc[mMaxListSize];
		bool mInCargo[mMaxListSize];

	public:
		// Removed custom assert. Should use the assert provided
		// in <cassert> instead\

		// Function to end the game - originally void empend()
		//static void endGame();

};

#endif /* SRC_UTIL_HPP_ */
