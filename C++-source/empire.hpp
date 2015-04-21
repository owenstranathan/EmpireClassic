#ifndef SRC_EMPIRE_HPP
#define SRC_EMPIRE_HPP

#include <cstdlib>
#include <vector>
#include <string>

// No need to redefine NULL
// #infdef NULL
// #define NULL 0
// #endif

typedef unsigned char uchar;
typedef long locT;	// Represents a board location in 4-digit form
typedef long countT;	// For iterating over or counting board locations

// Don't need these
//#define ASSERT(x) if (!(x)) assert ("x", __FILE__, __LINE__);
//#define ABORT assert ("aborting", __FILE__, __LINE__)

// The following enum replaces:
/*
#define NORTH 0
#define NORTHEAST 1
#define EAST 2
#define SOUTHEAST 3
#define SOUTH 4
#define SOUTHWEST 5
#define WEST 6
#define NORTHWEST 7
 */

enum Direction {
	NORTH = 0,
	NORTHEAST = 1,
	EAST = 2,
	SOUTHEAST = 3,
	SOUTH = 4,
	SOUTHWEST = 5,
	WEST = 6,
	NORTHWEST = 7
};

const int NUM_TOPS = 3;	// Number of lines at the top of the screen for messages
const int NUM_SIDES = 6; // Number of lines at side of the screen
const int LIST_SIZE = 5000;	// Max number of pieces on board

// Don't really need to define a max string size
//#define STRSIZE 400 /* number of characters in a string */

/*
 * The following enum replaces:
#define UNOWNED 0
#define USER 1
#define COMP 2
 */
enum Owner {
	UNOWNED = 0,
	USER = 1,
	COMP = 2
};

enum PieceType {
	ARMY = 0,
	FIGHTER = 1,
	PATROL = 2,
	DESTROYER = 3,
	SUBMARINE = 4,
	TRANSPORT = 5,
	CARRIER = 6,
	BATTLESHIP = 7,
	SATELLITE = 8,
	NUM_OBJECTS = 9,
	NO_PIECE = 255 // (A 'null' piece)
};

// Adapted from struct city_info
class CityInfo {
	private:
		locT mLocation;	// Location of city
		Owner mOwner;	// Owner of the city
		long * mFunctions;	// Array of functions for each object
		long mWork;	// Units of work performed
		char mBeingProduced;	// Item being produced

	public:
		CityInfo(locT loc, Owner owner, long * func, long work, char beingProd);
		locT getLocation();
		Owner getOwner();
		long * getFunctions();
		long getWork();
		char getItemBeingProduced();
};

/*
Types of programmed movement.  Use negative numbers for special
functions, use positive numbers to move toward a specific location.
*/
enum Movement {
	NO_FUNC = -1,
	RANDOM = -2,
	SENTRY = -3,
	FILL = -4,
	LAND = -5,
	EXPLORE = -6,
	ARMY_LOAD = -7,
	ARMY_ATTACK = -8,
	TT_LOAD = -9,
	REPAIR = -10,
	WF_TRANSPORT = -11,
	MOVE_N = -12,
	MOVE_NE = -13,
	MOVE_E = -14,
	MOVE_SE = -15,
	MOVE_S = -16,
	MOVE_SW = -17,
	MOVE_W = -18,
	MOVE_NW = -19
};

// Index to list of function names
// #define FUNCI(x) (-(x)-1)

/*
Macro to convert a movement function into a direction.
*/
// #define MOVE_DIR(a) (-(a)+MOVE_N)
static inline int moveFuncToMoveDir(Movement movement) {
	return (int)(-movement) + (int)(MOVE_N);
}

// Replaces struct piece_info
class PieceInfo {
	private:
		std::vector<PieceInfo *> mPieceLink;
		std::vector<PieceInfo *> mLocLink;
		std::vector<PieceInfo *> mCargoLink;
		Owner mOwner;
		int mType;
		locT mLocation;
		Movement mFunc;
		short mHitsLeft;
		int mNumMoves;
		PieceInfo * mShip;
		PieceInfo * mCargo;
		short mCount;
		short mRange;

	public:
		PieceInfo(std::vector<PieceInfo *> pl, std::vector<PieceInfo *> locLink, std::vector<PieceInfo *> cargoLink,
				Owner owner, int type, locT loc, Movement func, short hitsLeft, int numMoves,
				PieceInfo * ship, PieceInfo * cargo, short count, short range);
		std::vector<PieceInfo *> * getPieceLink();
		std::vector<PieceInfo *> * getLocLink();
		std::vector<PieceInfo *> * getCargoLink();
		Owner getOwner();
		int getType();
		locT getLocation();
		Movement getFunction();
		short getNumHitsLeft();
		int getMovesMade();
		PieceInfo * getShip();
		PieceInfo * getCargo();
		short getCount();
		short getRange();
};

// Vector replaces struct link_t

// Replaces typedef struct piece_attr
class PieceAttributes {
	private:
		char mAbbrevName;
		std::string mName;
		std::string mNickname;
		std::string mArticle;
		std::string mPlural;
		std::string mTerrain;
		uchar mBuildTime;
		uchar mStrength;
		uchar mMaxHits;
		uchar mSpeed;
		uchar mCapacity;
		long mRange;

	public:
		PieceAttributes(char abbrev, std::string name, std::string nickname,
				std::string article, std::string plural, std::string terrain,
				uchar buildTime, uchar strength, uchar maxHits, uchar speed,
				uchar capacity, long range);
		char getAbbreviatedName();
		std::string getName();
		std::string getNickname();
		std::string getArticle();
		std::string getPlural();
		std::string getTerrain();
		uchar getBuildTime();
		uchar getStrength();
		uchar getMaxHits();
		uchar getSpeed();
		uchar getCapacity();
		long getRange();
};

/* macros to set map and list of an object */
#define MAP(owner) ((owner) == USER ? user_map : comp_map)
#define LIST(owner) ((owner) == USER ? user_obj : comp_obj)

// These are the constants defined in empire.h as defines
static const long long INFINITY = 1000000000;
static const int MAP_WIDTH = 100;
static const int MAP_HEIGHT = 60;
static const int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT;
static const int SECTOR_ROWS = 5;
static const int SECTOR_COLS = 2;
static const int NUM_SECTORS = SECTOR_ROWS * SECTOR_COLS;
static const int ROWS_PER_SECTOR = ((MAP_HEIGHT + SECTOR_ROWS - 1) / SECTOR_ROWS);
static const int COLS_PER_SECTOR = ((MAP_WIDTH + SECTOR_COLS - 1) / SECTOR_COLS);
static const int W_TT_BUILD = -1;

static const char MAP_LAND = '+';
static const char MAP_SEA = '.';
static const char MAP_CITY = '*';

enum Terrain {
	T_UNKNOWN = 0,
	T_PATH = 1,
	T_LAND = 2,
	T_WATER = 4,
	T_AIR = (T_LAND | T_WATER)
};


// Replaces enum win_t
enum Win {
	NO_WIN = 0,
	WIPEOUT_WIN = 1,
	RATIO_WIN = 2
};

class RealMap {
	private:
		char mContents;
		bool mOnBoard;
		CityInfo * mCityInfo;
		PieceInfo * mPieceInfo;

	public:
		RealMap(char contents, bool onBoard, CityInfo * cityInfo, PieceInfo * pieceInfo);
		char getContents();
		bool isOnBoard();
		CityInfo * getCityInfo();
		PieceInfo * getPieceInfo();
};

class ViewMap {
	private:
		char mContents;
		long mSeen;

	public:
		ViewMap(char contents, long seen);
		char getContents();
		long getLastUpdated();
};

class PathMap {
	private:
		int mCost;
		int mIncrementalCost;
		Terrain mTerrain;

	public:
		PathMap(int cost, int incCost, Terrain terrain);
		int getCost();
		int getIncrementalCost();
		Terrain getTerrain();
};

class ScanCounts {
	private:
		int mUserCities;
		int * mUserObjects;
		int mCompCities;
		int * mCompObjects;
		int mSize;
		int mUnownedCities;
		int mUnexplored;

	public:
		ScanCounts(int userCities, int * userObj, int compCities, int * compObj, int size, int unownedCities, int unexplored);
		int getNumUserCities();
		int * getUserObjects();
		int getCompCities();
		int * getCompCityObjects();
		int getSize();
		int getNumUnownedCities();
		int getUnexplored();
};

class MoveInfo {
	private:
		char mCityOwner;
		char * mObjectives;
		int * mWeights;

	public:
		MoveInfo(char owner, char * obj, int * weights);
		char getCityOwner();
		char * getObjectives();
		int * getWeights();
};

class Perimeter {
	private:
		long mLength;
		long * mList;

	public:
		Perimeter(long length, long * list);
		long getLength();
		long * getList();
};

#endif /* SRC_EMPIRE_HPP_ */
