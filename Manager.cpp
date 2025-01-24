#include "Manager.h"

void createZipTable(unordered_map <string, latLong> &zipData)
{

	ifstream file("Zips.csv");
	string line;

	if (!file.is_open()) {
		cerr << "cannot open file!\n"; 
		return;
	}

	getline(file, line); // read thru first line of file (header)

	while (getline(file, line)) {
		stringstream ss(line);
		string zip, latitude, longitude;

		//parse each line, store each pair into zip, lat, long
		getline(ss, zip, ','); 
		getline(ss, latitude, ',');
		getline(ss, longitude, ',');

		//store into our map
		zipData[zip] = { latitude, longitude };
	}
	return;
}

Manager::Manager(string zip)
{
	createZipTable(zips);
	latLong coords = zips[zip];
	latitude = coords.lati;
	longitude = coords.longi;
	std::cout << "Your latitude is: " << coords.lati << " and your longitude is: " << coords.longi << endl;

}

tleData Manager::tleInfo(string rawData)
{
	tleData dat;
	string tleLines;

	for (int i = 0; i < rawData.length(); i++) {
		if (rawData[i] == 't' && rawData[i + 1] == 'l' && rawData[i + 2] == 'e') {
			// TLE plus 8
			tleLines = rawData.substr(i + 6, rawData.length() - 1);
			break;
		}
	}

	dat.classification = tleLines[7];
	dat.launchYear = tleLines.substr(9, 2);
	dat.satID = "NULL";
	dat.revPerDay = "NULL";

	cout << "Satellite classification (U: Unclassified, C: Classified, S: Secret): " << dat.classification << "\n";
	cout << "Satellite Launch Year (last two digits): " << dat.launchYear << "\n";


	return dat;
}

vector <geoData> Manager::geoInfo(string rawData)
{
	vector <geoData> foundSats;
	string geoLines;
	string search = "above";
	vector <string> results;
	string newSat;
	//can just parse through from this point looking for open and closed curly braces
	geoLines = rawData.substr(rawData.find(search) + 8, rawData.length() - 1);

	for (int i = 0; i < geoLines.length() - 1; i++) {
		if (geoLines[i] == '{') {
			while (geoLines[i] != '}') {
				newSat += geoLines[i];
				i++;
			}
			results.push_back(newSat);
			newSat = "";
		}
	}
	cout << results.size() << " Satellites Found!\n";

	vector <string> satDatArray;
	string segment;

	for (string sats : results) {
		for (char ch : sats) {
			if (ch == ',') {
				satDatArray.push_back(segment);
				segment.clear();
				continue;
			}
			segment += ch;
		}
		satDatArray.push_back(segment);
		segment.clear();
	}

	//populate geoDatas
	int k = 0;
	for (int j = 0; j < results.size(); j++) {
		string satID = satDatArray[k].substr(9);
		string satName = satDatArray[k+1].substr(10);
		string satLaunch = satDatArray[k+3].substr(13);
		string satLatt = satDatArray[k+4].substr(9);
		string satLongg = satDatArray[k+5].substr(9);
		string satAltt = satDatArray[k+6].substr(9);
		foundSats.emplace_back(satID, satName, satLaunch, satLatt, satLongg, satAltt);
		k += 7;
	}
	// since we don't have visual yet, just use cout to confirm we're parsing data correctly.
	int i = 1;
	for (geoData satellites : foundSats) {
		cout << "Satellite " << i << "\n";
		cout << "Satellite ID: " << satellites.satID << "\n";
		cout << "Satellite name: " << satellites.satName << "\n";
		cout << "Satellite launch date: " << satellites.launchDate << "\n";
		cout << "Satellite latitude: " << satellites.satLat << "\n";
		cout << "Satellite longtude: " << satellites.satLong << "\n";
		cout << "Satellite altitude: " << satellites.satAlt << " km\n";
		cout << "\n";
		i++;
	}
	//generate a vector full of geoData, return to manager. It would be the renderers job to pull the geodata and draw to screen
	return foundSats;
}






void Manager::inputData(string rawData)
{
	returnStrings.push_back(rawData);
}









