#include "empire.hpp"

///// CityInfo class /////
CityInfo::CityInfo(locT loc, Owner owner, long * func, long work, char beingProd) :
	mLocation(loc),
	mOwner(owner),
	mFunctions(func),
	mWork(work),
	mBeingProduced(beingProd) {}

locT CityInfo::getLocation() {
	return this->mLocation;
}

Owner CityInfo::getOwner() {
	return this->mOwner;
}

long * CityInfo::getFunctions() {
	return this->mFunctions;
}

long CityInfo::getWork() {
	return this->mWork;
}

char CityInfo::getItemBeingProduced() {
	return this->mBeingProduced;
}
//////////

///// PieceInfo class /////
PieceInfo::PieceInfo(std::vector<PieceInfo *> pl, std::vector<PieceInfo *> locLink, std::vector<PieceInfo *> cargoLink,
				Owner owner, int type, locT loc, Movement func, short hitsLeft, int numMoves,
				PieceInfo * ship, PieceInfo * cargo, short count, short range) :
	mPieceLink(pl),
	mLocLink(locLink),
	mCargoLink(cargoLink),
	mOwner(owner),
	mType(type),
	mLocation(loc),
	mFunc(func),
	mHitsLeft(hitsLeft),
	mNumMoves(numMoves),
	mShip(ship),
	mCargo(cargo),
	mCount(count),
	mRange(range)
	{}

std::vector<PieceInfo *> * PieceInfo::getPieceLink() {
	return &this->mPieceLink;
}

std::vector<PieceInfo *> * PieceInfo::getLocLink() {
	return &this->mLocLink;
}

std::vector<PieceInfo *> * PieceInfo::getCargoLink() {
	return &this->mCargoLink;
}

Owner PieceInfo::getOwner() {
	return this->mOwner;
}

int PieceInfo::getType() {
	return this->mType;
}

locT PieceInfo::getLocation() {
	return this->mLocation;
}

Movement PieceInfo::getFunction() {
	return this->mFunc;
}

short PieceInfo::getNumHitsLeft() {
	return this->mHitsLeft;
}

int PieceInfo::getMovesMade() {
	return this->mNumMoves;
}

PieceInfo * PieceInfo::getShip() {
	return this->mShip;
}

PieceInfo * PieceInfo::getCargo() {
	return this->mCargo;
}

short PieceInfo::getCount() {
	return this->mCount;
}

short PieceInfo::getRange() {
	return this->mRange;
}
//////////

///// PieceAttributes class /////
PieceAttributes::PieceAttributes(char abbrev, std::string name, std::string nickname,
		std::string article, std::string plural, std::string terrain,
		uchar buildTime, uchar strength, uchar maxHits, uchar speed,
		uchar capacity, long range) :
	mAbbrevName(abbrev),
	mName(name),
	mNickname(nickname),
	mArticle(article),
	mPlural(plural),
	mTerrain(terrain),
	mBuildTime(buildTime),
	mStrength(strength),
	mMaxHits(maxHits),
	mSpeed(speed),
	mCapacity(capacity),
	mRange(range) {}

char PieceAttributes::getAbbreviatedName() {
	return this->mAbbrevName;
}

std::string PieceAttributes::getName() {
	return this->mName;
}

std::string PieceAttributes::getNickname() {
	return this->mNickname;
}

std::string PieceAttributes::getArticle() {
	return this->mArticle;
}

std::string PieceAttributes::getPlural() {
	return this->mPlural;
}

std::string PieceAttributes::getTerrain() {
	return this->mTerrain;
}

uchar PieceAttributes::getBuildTime() {
	return this->mBuildTime;
}

uchar PieceAttributes::getStrength() {
	return this->mStrength;
}

uchar PieceAttributes::getMaxHits() {
	return this->mMaxHits;
}

uchar PieceAttributes::getSpeed() {
	return this->mSpeed;
}

uchar PieceAttributes::getCapacity() {
	return this->mCapacity;
}

long PieceAttributes::getRange() {
	return this->mRange;
}
//////////

///// RealMap class /////
RealMap::RealMap(char contents, bool onBoard, CityInfo * cityInfo, PieceInfo * pieceInfo) :
	mContents(contents),
	mOnBoard(onBoard),
	mCityInfo(cityInfo),
	mPieceInfo(pieceInfo) {}

char RealMap::getContents() {
	return this->mContents;
}

bool RealMap::isOnBoard() {
	return this->mOnBoard;
}

CityInfo * RealMap::getCityInfo() {
	return this->mCityInfo;
}

PieceInfo * RealMap::getPieceInfo() {
	return this->mPieceInfo;
}
//////////

///// ViewMap class /////
ViewMap::ViewMap(char contents, long seen) : mContents(contents), mSeen(seen) {}

char ViewMap::getContents() {
	return this->mContents;
}

long ViewMap::getLastUpdated() {
	return this->mSeen;
}
//////////

///// PathMap class /////
PathMap::PathMap(int cost, int incCost, Terrain terrain) :
	mCost(cost),
	mIncrementalCost(cost),
	mTerrain(terrain) {}

int PathMap::getCost() {
	return this->mCost;
}

int PathMap::getIncrementalCost() {
	return this->mIncrementalCost;
}

Terrain PathMap::getTerrain() {
	return this->mTerrain;
}
//////////

///// ScanCounts class /////
ScanCounts::ScanCounts(int userCities, int * userObj, int compCities, int * compObj, int size, int unownedCities, int unexplored) :
	mUserCities(userCities),
	mUserObjects(userObj),
	mCompCities(compCities),
	mCompObjects(compObj),
	mSize(size),
	mUnownedCities(unownedCities),
	mUnexplored(unexplored) {}

int ScanCounts::getNumUserCities() {
	return this->mUserCities;
}

int * ScanCounts::getUserObjects() {
	return this->mUserObjects;
}

int ScanCounts::getCompCities() {
	return this->mCompCities;
}

int * ScanCounts::getCompCityObjects() {
	return this->mCompObjects;
}

int ScanCounts::getSize() {
	return this->mSize;
}

int ScanCounts::getNumUnownedCities() {
	return this->mUnownedCities;
}

int ScanCounts::getUnexplored() {
	return this->mUnexplored;
}
//////////

///// MoveInfo class /////
MoveInfo::MoveInfo(char owner, char * obj, int * weights) : mCityOwner(owner), mObjectives(obj), mWeights(weights) {}

char MoveInfo::getCityOwner() {
	return this->mCityOwner;
}

char * MoveInfo::getObjectives() {
	return this->mObjectives;
}

int * MoveInfo::getWeights() {
	return this->mWeights;
}
//////////

///// Perimeter class /////
Perimeter::Perimeter(long length, long * list) : mLength(length), mList(list) {}

long Perimeter::getLength() {
	return this->mLength;
}

long * Perimeter::getList() {
	return this->mList;
}
//////////
