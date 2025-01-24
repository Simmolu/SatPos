#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>



using namespace std;


struct latLong {
	string lati;
	string longi;
};
 //searches table of zips to find our user coordinates given user input
void createZipTable(unordered_map <string, latLong> &map);

struct tleData {
	string satID;
	string classification;
	string launchYear;
	string revPerDay;
};

struct geoData {
	string satID;
	string satName;
	string launchDate;
	string satLat;
	string satLong;
	string satAlt;

	geoData(string satId, string satNam, string launchDat, string satLatt, string satLongg, string satAltt) : 
		satID(satId), satName(satNam), launchDate(launchDat), satLat(satLatt), satLong(satLongg), satAlt(satAltt){}
};

//Make a super class just called Data, make sub classes for TLE, GEO, etc. We can push these data to a vector for long term storage.

class Manager
{
public:

	string latitude;
	string longitude;
	vector <string> returnStrings;
	unordered_map <string, latLong> zips;

	void inputData(string rawData); //modify our string vector to add data from the API


	Manager(string zip);

	tleData tleInfo(string rawData);
	vector <geoData> geoInfo(string rawData);




};




#endif
