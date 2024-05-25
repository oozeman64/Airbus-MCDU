#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int AIRPORTSCAPACITY = 50; // Maximuim # of airports in database.
const double OEW = 42500.00; // Operating Empty Weight (in kg) of the A320neo.
const double MZFW = 64300.00; // Maximum Zero Fuel Weight (in kg) of the A320neo.
const double MTOW = 79000.00; // Maximum Takeoff Weight (in kg) of the A320neo.
const double MLW = 67400.00; // Maximum Landing Weight (in kg) of the A320neo.
const double PAXLOAD = 84.00; // Average weight (in kg) of one passenger (includes carry-on luggage).

struct Runway
{
    string name;
    int length; // length of runway in m.
};

struct Airport
{
    string ICAO;
    string name;
    double latitude;
    double longitude;
    int elevation; // (ASL) in ft.
    Runway runways[3]; // No airport in Pakistan has more than 2 runways.
    string frequencies[3]; // Air Traffic Control Radio frequencies - GND, TWR, CTR.
};


void PrintAirports(const Airport airports[], const int &airports_size)
{
    cout << endl;
    for(int i=0; i<airports_size; i++)
    {
        cout << "               ICAO: " << airports[i].ICAO << endl;
        cout << "               Name: " << airports[i].name << endl;
        cout << "               Latitude: " << abs(airports[i].latitude);
        if(airports[i].latitude > 0) cout << "N";
        else cout << "S"; cout << endl;
        cout << "               Longitude: " << abs(airports[i].longitude);
        if(airports[i].longitude > 0) cout << "E";
        else cout << "W"; cout << endl;
        cout << "               Elevation: " << airports[i].elevation << "ft" << endl;
        for(int j=0; j<3 && airports[i].runways[j].name != ""; j++)
        {
            cout << "               Runway " << j+1 <<": " << airports[i].runways[j].name <<"  Length: " << airports[i].runways[j].length << "m" << endl;
        }
        cout << "               GND: " << airports[i].frequencies[0] << endl;
        cout << "               TWR: " << airports[i].frequencies[1] << endl;
        cout << "               CTR: " << airports[i].frequencies[2] << endl;
        
        cout << endl;
    }
}

void RemoveAirport(Airport airports[], int &airports_size)
{
    string toberemoved; bool found = false;
    cout << "               --- Removing airport from database ---" << endl;
    cout << "Enter ICAO code: ";
    cin >> toberemoved;
    for(int i=0; i<airports_size; i++)
    {
        if(airports[i].ICAO == toberemoved)
        {
            found = true;
            for(int j=i; j<airports_size-1; j++)
            {
                airports[j] = airports[j+1];
            }
            airports_size--;
            cout << endl << "                        " << toberemoved << " has been removed." << endl;
            break;
        }
    }
    if (found == false) cout << "                       " << toberemoved << " is not in the database." << endl;
    cout << "               --------------------------------------" << endl;
}

void SortAirportsAfterAdding(Airport airports[], const int &airports_size)
{
    int newpos;
    Airport temp[1];
    for(int i=0; i<airports_size; i++)
    {
        if (!(airports[airports_size-1].ICAO > airports[i].ICAO))
        {
            newpos = i;
            break;
        }
    }
    temp[0] = airports[airports_size-1];
    for(int k=airports_size-1; k>newpos; k--) // Moves down all elements below newpos.
    {
        airports[k] = airports[k-1];
    }
    airports[newpos] = temp[0];
}

void AddAirport(Airport airports[], int &airports_size)
{
    int runwaycount;
    bool alreadyexists;
    cout << "               --- Adding airport to databse ---" << endl;
    do
    {
    alreadyexists = false;
    do
    {
    cout << "Enter ICAO code: ";
    cin >> airports[airports_size].ICAO;
    if(airports[airports_size].ICAO == "0") {
        airports[airports_size].ICAO = ""; return; }
    }
    while(airports[airports_size].ICAO.length() != 4);
    for(int i=0; i<airports_size; i++)
    {
        if(airports[i].ICAO == airports[airports_size].ICAO) 
        {
            cout << "               " << airports[airports_size].ICAO << " is already in the database!" << endl;
            alreadyexists = true; 
            break;
        }
    }
    }
    while(alreadyexists == true);
    cout << "Enter name: ";
    cin.ignore(); getline(cin, airports[airports_size].name);
    cout << "Enter latitude (negative for south): ";
    cin >> airports[airports_size].latitude;
    cout << "Enter longitude (negative for west): ";
    cin >> airports[airports_size].longitude;
    cout << "Enter elevation (in ft): ";
    cin >> airports[airports_size].elevation;
    cout << "Enter number of runways: ";
    cin >> runwaycount;
    for (int i=0; i<runwaycount; i++)
    {
        cout << "Enter the name of runway " << i+1 << ": ";
        cin >> airports[airports_size].runways[i].name;
        cout << "Enter the length of runway " << airports[airports_size].runways[i].name << " (in m): ";
        cin >> airports[airports_size].runways[i].length;
    }
    cout << "Enter GND frequency: ";
    cin >> airports[airports_size].frequencies[0];
    cout << "Enter TWR frequency: ";
    cin >> airports[airports_size].frequencies[1];
    cout << "Enter CTR freqeuency: ";
    cin >> airports[airports_size].frequencies[2];
    cout << endl;
    cout << "                      " << airports[airports_size].ICAO << " has been added." << endl;
    airports_size++;
    SortAirportsAfterAdding(airports, airports_size); 
    cout << "               ---------------------------------" << endl;
}

void EditRunways(Airport airports[], const int &airports_size, const int &tobeeditedindex)
{
    int runwayoption;
    int runwaydeleteoption;    
    cout << "            Current runways of " << airports[tobeeditedindex].ICAO << " are:" << endl;
    for(int j=0; j<3 && airports[tobeeditedindex].runways[j].name != ""; j++)
    {
        cout << "         Runway " << j+1 << ": " << airports[tobeeditedindex].runways[j].name << "\tEnter " << j+1 << " to edit" << endl;
    }
    cout << "               To delete a runway, enter 0." << endl;
    cout << "                 To add a runway, enter 4." << endl;
    cout << "Enter: ";
    do
    {
        cin >> runwayoption;
    }
    while(runwayoption < 0 || runwayoption > 4);
    if(runwayoption==0)
    {
        cout << "Enter runway number to delete: ";
        cin >> runwaydeleteoption;
        for(int i=runwaydeleteoption-1; i<2; i++)
        {
            airports[tobeeditedindex].runways[i] = airports[tobeeditedindex].runways[i+1];
        }
        cout << "                    Runway deleted." << endl;
    }
    else if(runwayoption == 1 || runwayoption == 2 || runwayoption == 3)
    {
        cout << endl << "Enter new name for " << airports[tobeeditedindex].runways[runwayoption-1].name << ": ";
        cin.ignore(); getline(cin, airports[tobeeditedindex].runways[runwayoption-1].name);
        cout << "Enter length of " << airports[tobeeditedindex].runways[runwayoption-1].name << ": ";
        cin >> airports[tobeeditedindex].runways[runwayoption-1].length;
        cout << "                    Runway updated." << endl;
    }
    if(runwayoption == 4)
    {
        if (airports[tobeeditedindex].runways[2].name != "")
        {
            cout << "               Cannot add more runways to " << airports[tobeeditedindex].ICAO << "." << endl;
        }
        else if (airports[tobeeditedindex].runways[1].name == "")
        {
            cout << "Enter the name of the new runway: ";
            cin >> airports[tobeeditedindex].runways[1].name;
            cout << "Enter the length of runway " << airports[tobeeditedindex].runways[1].name << " (in m): ";
            cin >> airports[tobeeditedindex].runways[1].length;
            cout << "                Runway added successfully." << endl;
        }
        else
        {
            cout << "Enter the name of the new runway: ";
            cin >> airports[tobeeditedindex].runways[2].name;
            cout << "Enter the length of runway " << airports[tobeeditedindex].runways[2].name << " (in m): ";
            cin >> airports[tobeeditedindex].runways[2].length;
            cout << "               Runway added successfully." << endl;
        }
        
    }

}

void EditFrequences(Airport airports[], const int &airports_size, const int &tobeeditedindex)
{
    cout << "               Current frequencies of " << airports[tobeeditedindex].ICAO << " are:" << endl;
    cout << "               GND: " << airports[tobeeditedindex].frequencies[0] << "\tEnter 1 to edit." << endl;
    cout << "               TWR: " << airports[tobeeditedindex].frequencies[1] << "\tEnter 2 to edit." << endl;
    cout << "               CTR: " << airports[tobeeditedindex].frequencies[2] << "\tEnter 3 to edit." << endl;
    cout << "Enter: ";
    int frequencyoption;
    do
    {
        cin >> frequencyoption;
    }
    while(frequencyoption < 1 || frequencyoption > 3);
    if(frequencyoption == 1)
    {
        cout << "Enter updated GND frequency: ";
        cin >> airports[tobeeditedindex].frequencies[0];
        cout << "                GND frequency updated." << endl << endl;
    }
    else if(frequencyoption == 2)
    {
        cout << "Enter updated TWR frequency: ";
        cin >> airports[tobeeditedindex].frequencies[1];
        cout << "                 TWR frequency updated." << endl << endl;
    }
    else if(frequencyoption == 3)
    {
        cout << "Enter updated CTR frequency: ";
        cin >> airports[tobeeditedindex].frequencies[2];
        cout << "                 CTR frequency updated." << endl << endl;
    }
}

void EditAirport(Airport airports[], const int &airports_size)
{
    string tobeedited;
    int tobeeditedindex = -1;
    cout << "Enter airport code to edit info: ";
    cin >> tobeedited;
    for(int i=0; i<airports_size; i++)
    {
        if (airports[i].ICAO == tobeedited)
        {
            tobeeditedindex = i;
            break;
        }
    }
    if (tobeeditedindex == -1)
    {
        cout << tobeedited << " is not in the database." << endl;
        return;
    }
    int editoption;
    cout << endl << "                  === Editing " << tobeedited << " ===" << endl;
    cout << "               To edit name, enter 1." << endl;
    cout << "               To edit latitude/longitude, enter 2." << endl;
    cout << "               To edit elevation, enter 3." << endl;
    cout << "               To edit runways, enter 4." << endl;
    cout << "               To edit frequencies, enter 5." << endl;
    cout << "Enter: ";
    do
    {
        cin >> editoption;
    }
    while(cin.fail() || editoption < 1 || editoption > 5);
    if (editoption == 1)
    {
        cout << "            Current name of " << tobeedited << " is " << airports[tobeeditedindex].name << endl;
        cout << "Enter updated name: ";
        cin.ignore(); getline(cin, airports[tobeeditedindex].name);
        cout << "                  Name updated." << endl << endl;
    }
    else if (editoption == 2)
    {
        cout << "               Current latitude/longitude of " << tobeedited << " is " << airports[tobeeditedindex].latitude << " " << airports[tobeeditedindex].longitude << endl;
        cout << "Enter updated latitude (negative for south): ";
        cin >> airports[tobeeditedindex].latitude;
        cout << "Enter updated longitude (negative for west): ";
        cin >> airports[tobeeditedindex].longitude;
        cout << "             Latitude/longitude updated." << endl << endl;
    }
    else if (editoption == 3)
    {
        cout << "               Current elevation of " << tobeedited << " 2is " << airports[tobeeditedindex].elevation << "ft" << endl;
        cout << "Enter updated elevation: ";
        cin >> airports[tobeeditedindex].elevation;
        cout << "               Elevation updated." << endl << endl;
    }
    else if (editoption == 4) EditRunways(airports, airports_size, tobeeditedindex);
    else if (editoption == 5) EditFrequences(airports, airports_size, tobeeditedindex);
    cout << "                  ==================="<< endl;
}


void TakeoffSpeeds(const double &tow, int &v1, int &vr, int &v2) // Uses linear approx. to calculate takeoff speeds.
{
    v1 = round((0.00117*tow) +56.08232);
    vr = round((0.00122*tow)+58.27716);
    v2 = vr + 3;
    cout << "               === TAKEOFF SPEEDS ===" << endl;
    cout << "               V1: " << v1 << endl;
    cout << "               Vr: " << vr << endl;
    cout << "               V2: " << v2 << endl;
    cout << "               ======================" << endl;
}

void LandingSpeeds(const double &tow, const double &trip_fuel, int &vref, int &vapp) // Uses linear approx. to calculate landing speeds.
{
    double LW = tow - trip_fuel;
    vref = round((0.00108*LW) + 64.76876);
    vapp = vref + 5;
    cout << "               === LANDING SPEEDS ===" << endl;
    cout << "               Vref: " << vref << endl;
    cout << "               Vapp: " << vapp << endl;
    cout << "               ======================" << endl;
}

double ConvertDegToRad(double deg)
{
    return deg * (M_PI/180);
}

double ConvertMetreToNauticalMile(double metre)
{
    return metre/1852.0;
}

double DistanceBetweenAirports(Airport airports[], const int &airport_1_index, const int &airport_2_index) // Calculates distance between two airports using the Haversine formula.
{
    double lat_1, lat_2, delta_lat, long_1, long_2, delta_long, haversine_a, haversine_c, distance;
    const int Re = 6378100;
    lat_1 = ConvertDegToRad(airports[airport_1_index].latitude);
    lat_2 = ConvertDegToRad(airports[airport_2_index].latitude);
    delta_lat = lat_2 - lat_1;
    long_1 = ConvertDegToRad(airports[airport_1_index].longitude);
    long_2 = ConvertDegToRad(airports[airport_2_index].longitude);
    delta_long = long_2 - long_1;
    haversine_a = (sin(delta_lat/2.0) * sin(delta_lat/2.0)) + (cos(lat_1) * cos(lat_2) * (sin(delta_long/2.0) * sin(delta_long/2.0)));
    haversine_c = 2.0 * atan2(sqrt(haversine_a), sqrt(1-haversine_a));
    distance = Re * haversine_c;
    return ConvertMetreToNauticalMile(distance);
}

double CalculateTripFuel(double distance) // Calculates fuel burn based on distance
{
    double trip_fuel = distance * 4.78;
    return trip_fuel;
}

double CalculateFlightTime(double distance) // Calculates flight time (in minutes) based on distance
{
    double flight_time = distance/6.791;
    return flight_time;
}

int CalculateCruiseAlt(double distance, Airport airports[], const int &dep_airport_index, const int &arr_airport_index) // Calculates cruise altitude based on flight distance and orientation (E/W) 
{
    int cruise_alt;
    if(distance <= 100) cruise_alt = (airports[arr_airport_index].longitude>airports[dep_airport_index].longitude) ? 11000 : 10000;
    else if(distance > 100 && distance <= 200) cruise_alt = (airports[arr_airport_index].longitude>airports[dep_airport_index].longitude) ? 17000 : 16000;
    else if(distance > 200 && distance <= 300) cruise_alt = (airports[arr_airport_index].longitude>airports[dep_airport_index].longitude) ? 23000 : 22000;
    else if(distance > 300 && distance <= 400) cruise_alt = (airports[arr_airport_index].longitude>airports[dep_airport_index].longitude) ? 29000 : 28000;
    else cruise_alt = (airports[arr_airport_index].longitude>airports[dep_airport_index].longitude) ? 35000 : 34000;
    return cruise_alt;
}

void FindAltnAirport(Airport airports[], const int &airports_size, int &dep_airport_index, int &arr_airport_index, int &altn_airport_index) // Assigns index of the closest alternate to arrival airport. 
{
    double distance_to_altn, previous_distance_to_altn = 0;
    for(int i=0; i<airports_size; i++)
    {
        if(i == dep_airport_index || i == arr_airport_index) continue;
        distance_to_altn = DistanceBetweenAirports(airports, arr_airport_index, i);
        if(distance_to_altn<previous_distance_to_altn) altn_airport_index = i;
        previous_distance_to_altn = distance_to_altn;
    }
}

void PrintFlightPlan(const string &flight_number, const int &dep_airport_index, const int &arr_airport_index, const int &altn_airport_index, Airport airports[], const int &airports_size, const int &paxnum, const double &pax_weight, const double &cargo_weight, const double &zfw, const double &taxi_fuel, const double &trip_fuel, const double &altn_fuel, const double &reserve_fuel, const double &block_fuel, const double &tow, const int &flight_time, const int &cruise_alt)
{
    cout << endl << "          -----------------------------------    "<< endl;
    cout <<"          |       Current Flight Plan       |    "<< endl;
    cout <<"          -----------------------------------    "<< endl;
    cout <<"                         " << flight_number << endl;
    cout <<"                       " << airports[dep_airport_index].ICAO << "-" << airports[arr_airport_index].ICAO << endl;
    cout <<"           Great Circle Distance: " << DistanceBetweenAirports(airports, dep_airport_index, arr_airport_index) << "nm" << endl;
    cout <<"               Cruise Altitude: " << cruise_alt << "ft" << endl;
    cout <<"                  En-route time: " << flight_time << " minutes" << endl;
    cout <<"                 Alternate Airport: " << airports[altn_airport_index].ICAO << endl;
    cout <<"          -----------------------------------    "<< endl;
    cout <<"                      =Planned Fuel=" << endl;
    cout <<"                 1. Taxi: " << taxi_fuel << "kg" << endl;
    cout <<"                 2. Trip: " << trip_fuel << "kg" << endl;
    cout <<"                 3. Alternate: " << altn_fuel << "kg" << endl;
    cout <<"                 4. Reserve: " << reserve_fuel << "kg" << endl;
    cout <<"                = Block Fuel:" << block_fuel << "kg" << endl;
    cout <<"          -----------------------------------    "<< endl;
    cout <<"                      =Loadsheet=" << endl;
    cout <<"                 1. Passengers (" << paxnum << "): " << pax_weight << "kg" << endl;
    cout <<"                 2. Cargo: " << cargo_weight << "kg" << endl;
    cout <<"                 3. Fuel:" << block_fuel << "kg" << endl;
    cout <<"                 - ZFW: " << zfw << "kg" << endl;
    cout <<"                 - TOW: " << tow << "kg" << endl;
    cout <<"                 - LW (expected): " << tow-trip_fuel << "kg" << endl;
    cout <<"          -----------------------------------" << endl;
    cout <<"                   Departure - " << airports[dep_airport_index].ICAO << endl;
    cout <<"               Name: " << airports[dep_airport_index].name << endl;
    cout <<"                   Latitude: " << airports[dep_airport_index].latitude;
    if(airports[dep_airport_index].latitude > 0) cout << "N";
    else cout << "S"; cout << endl;
    cout <<"                  Longitude: " << airports[dep_airport_index].longitude;
    if(airports[dep_airport_index].longitude > 0) cout << "E";
    else cout << "W"; cout << endl;
    cout <<"                   Elevation: " << airports[dep_airport_index].elevation << " ft" << endl;
    for(int j=0; j<3 && airports[dep_airport_index].runways[j].name != ""; j++)
    {
        cout << "            Runway " << j+1 <<": " << airports[dep_airport_index].runways[j].name <<"  Length: " << airports[dep_airport_index].runways[j].length << "m" << endl;
    }
    cout << "                      GND: " << airports[dep_airport_index].frequencies[0] << endl;
    cout << "                      TWR: " << airports[dep_airport_index].frequencies[1] << endl;
    cout << "                      CTR: " << airports[dep_airport_index].frequencies[2] << endl;
    cout <<"          -----------------------------------" << endl;
    cout <<"                   Arrival - " << airports[arr_airport_index].ICAO << endl;
    cout <<"               Name: " << airports[arr_airport_index].name << endl;
    cout <<"                   Latitude: " << airports[arr_airport_index].latitude;
    if(airports[arr_airport_index].latitude > 0) cout << "N";
    else cout << "S"; cout << endl;
    cout <<"                  Longitude: " << airports[arr_airport_index].longitude;
    if(airports[arr_airport_index].longitude > 0) cout << "E";
    else cout << "W"; cout << endl;
    cout <<"                   Elevation: " << airports[arr_airport_index].elevation << " ft" << endl;
    for(int j=0; j<3 && airports[arr_airport_index].runways[j].name != ""; j++)
    {
        cout << "           Runway " << j+1 <<": " << airports[arr_airport_index].runways[j].name <<"  Length: " << airports[arr_airport_index].runways[j].length << "m" << endl;
    }
    cout << "                      GND: " << airports[arr_airport_index].frequencies[0] << endl;
    cout << "                      TWR: " << airports[arr_airport_index].frequencies[1] << endl;
    cout << "                      CTR: " << airports[arr_airport_index].frequencies[2] << endl;
    cout <<"          ===================================" << endl << endl;
}

void CreateFlightPlan(string &flight_number, string &dep_airport, string &arr_airport, string &altn_airport, int &dep_airport_index, int &arr_airport_index, int &altn_airport_index, Airport airports[], const int &airports_size, int &paxnum, double &pax_weight, double &cargo_weight, double &zfw, double &taxi_fuel, double &trip_fuel, double &altn_fuel, double &reserve_fuel, double &block_fuel, double &tow, int &flight_time, int &cruise_alt)
{
    bool foundindatabase = false;
    bool depequalsarrival = false;
    cout << endl << "          -----------------------------------    "<< endl;
    cout <<"          |         New Flight Plan         |    "<< endl;
    cout <<"          -----------------------------------    "<< endl;
    do
    {
        cout << "Enter Flight Number: ";
        cin >> flight_number;
    }
    while(cin.fail());
    do
    {
        foundindatabase = false;
        cout <<"Enter Departure ICAO: ";
        cin >> dep_airport;
        for(int i=0; i<airports_size; i++)
        {
            if(airports[i].ICAO == dep_airport) 
            {
                foundindatabase = true;
                dep_airport_index = i;
            }
        }
        if(!foundindatabase) cout << "          " << dep_airport << " not found in the databse." << endl;
    }
    while(dep_airport.length() != 4 || cin.fail() || !foundindatabase);
    do
    {
        foundindatabase = false;
        depequalsarrival = false;
        cout <<"Enter Arrival ICAO: ";
        cin >> arr_airport;
        if(arr_airport == dep_airport)
        {
            depequalsarrival = true;
            cout << "       " << "Departure and arrival airports must be distinct." << endl;
        }
        for(int j=0; j<airports_size; j++)
        {
            if(airports[j].ICAO == arr_airport) 
            {
                foundindatabase = true;
                arr_airport_index = j;
            }
        }
        if(!foundindatabase) cout << "          " << arr_airport << " not found in the databse." << endl;
    }
    while(arr_airport.length() != 4 || cin.fail() || !foundindatabase || depequalsarrival);
    FindAltnAirport(airports, airports_size, dep_airport_index, arr_airport_index, altn_airport_index);
    altn_airport = airports[altn_airport_index].ICAO;
    cout << "              Ready to initialise weights." << endl;
    do
    {
        do
        {
            do
            {
                cout << "Enter number of passengers: ";
                cin >> paxnum;
                if(paxnum>180) cout << "          Passenger capacity is 180." << endl;
            }
            while(cin.fail() || paxnum < 0 || paxnum > 180);
            do
            {
                cout << "Enter cargo (in kg): ";
                cin >> cargo_weight;
                if(cargo_weight > 12000) cout << "          Cargo capacity is 12000kg." << endl;
            }
            while(cin.fail() || cargo_weight < 0 || cargo_weight > 120000);
            pax_weight = paxnum * PAXLOAD;
            zfw = OEW + pax_weight + cargo_weight;
            if(zfw>MZFW)
            {
                cout << "         ZFW cannot be greater than MZFW." << endl;
            }
        }
        while(zfw>MZFW);
        trip_fuel = CalculateTripFuel(DistanceBetweenAirports(airports, dep_airport_index, arr_airport_index));
        taxi_fuel = 200; // This is just an average.
        altn_fuel = CalculateTripFuel(DistanceBetweenAirports(airports, arr_airport_index, altn_airport_index));
        reserve_fuel = 1500;
        block_fuel = trip_fuel+taxi_fuel+altn_fuel+reserve_fuel;
        tow = zfw+block_fuel-taxi_fuel;
        if(tow>MTOW) cout << "  Maximum Takeoff Weight Exceeded. Reenter values." << endl;  
        else if(tow-trip_fuel>MLW) cout << "  Maximum Landing Weight Exceeded. Reenter values." << endl;  
    }
    while(tow>MTOW || tow-trip_fuel>MLW);
    flight_time = CalculateFlightTime(DistanceBetweenAirports(airports, dep_airport_index, arr_airport_index));
    cruise_alt = CalculateCruiseAlt(DistanceBetweenAirports(airports, dep_airport_index, arr_airport_index), airports, dep_airport_index, arr_airport_index);
    cout << endl <<  "                All values validated." << endl;

    PrintFlightPlan(flight_number, dep_airport_index, arr_airport_index, altn_airport_index, airports, airports_size, paxnum, pax_weight, cargo_weight, zfw, taxi_fuel, trip_fuel, altn_fuel, reserve_fuel, block_fuel, tow, flight_time, cruise_alt);
}

void DeleteFlightPlan(string &dep_airport, string &arr_airport, string &altn_airport, int &paxnum, double &pax_weight, double &cargo_weight, double &zfw, double &taxi_fuel, double &trip_fuel, double &altn_fuel, double &reserve_fuel, double &block_fuel, double &tow, int &flight_time, int &cruise_alt)
{
    int areyousure;
    cout << "                   Are you sure?" << endl;
    cout << "                 To delete, enter 1." << endl;
    cout << "               Enter 0 to return to home."<< endl;
    do
    {
        cout << "Enter: ";
        cin >> areyousure;
    }
    while(cin.fail() || areyousure < 0 || areyousure > 1);
    if(areyousure == 0) return;
    dep_airport = "NULL";
    arr_airport = "NULL";
    altn_airport = "NULL";
    paxnum = 0;
    pax_weight = 0.0;
    cargo_weight = 0.0;
    zfw = OEW;
    taxi_fuel = 0.0;
    trip_fuel = 0.0;
    altn_fuel = 0.0;
    reserve_fuel = 0.0;
    block_fuel = 0.0;
    tow = zfw;
    flight_time = 0.0;
    cruise_alt = 0;
    cout << "               Flight Plan Deleted!" << endl << endl;
}

void PrintMainMenu()
{
    cout << endl <<"          ===================================    "<< endl;
    cout <<"          |               HOME              |    "<< endl;
    cout <<"          ===================================    "<< endl << endl;
    cout <<"                |======================|         "<< endl;
    cout <<"         [1] .  |    FLIGHT PLANNING   |         "<< endl;
    cout <<"                |======================|         "<< endl;
    cout <<"         [2] .  |     CALCULATIONS     |         "<< endl;
    cout <<"                |======================|         "<< endl;
    cout <<"         [3] .  |  DATABASE MANAGEMENT |         "<< endl;
    cout <<"                |======================|         "<< endl;
    cout <<"         [4] .  |      INFORMATION     |         "<< endl;
    cout <<"                |======================|         "<< endl;
    cout <<"         [5] .  |       TERMINATE      |         "<< endl;
    cout <<"                |======================|         "<< endl << endl;
}

void FlightPlanningPage(string &flight_number, string &dep_airport, string &arr_airport, string &altn_airport, int &dep_airport_index, int &arr_airport_index, int &altn_airport_index, Airport airports[], int &airports_size, int &paxnum, double &pax_weight, double &cargo_weight, double &zfw, double &taxi_fuel, double &trip_fuel, double &altn_fuel, double &reserve_fuel, double &block_fuel, double &tow, int &flight_time, int &cruise_alt)
{
    int submenu_option;
    cout << endl << "          -----------------------------------    "<< endl;
    cout <<"          |         FLIGHT PLANNING         |    "<< endl;
    cout <<"          -----------------------------------    "<< endl;  
    if(dep_airport == "NULL")
    {
        cout <<"                 No Current Flight Plan           "<< endl;
        cout <<"               |------------------------|         "<< endl;
        cout <<"        [1] .  |   Create Flight Plan   |         "<< endl;
        cout <<"               |------------------------|         "<< endl;
        cout <<"               Enter 0 to return to home.         "<< endl << endl;
        do
        {
            cout << "Enter: ";
            cin >> submenu_option;
        }
        while(cin.fail() || submenu_option < 0 || submenu_option > 1);
        if(submenu_option == 1) CreateFlightPlan(flight_number, dep_airport, arr_airport, altn_airport, dep_airport_index, arr_airport_index, altn_airport_index, airports, airports_size, paxnum, pax_weight, cargo_weight, zfw, taxi_fuel, trip_fuel, altn_fuel, reserve_fuel, block_fuel, tow, flight_time, cruise_alt);
        else return;
    }
    else
    {
        cout <<"               |------------------------|         "<< endl;
        cout <<"        [1] .  |    View Flight Plan    |         "<< endl;
        cout <<"               |------------------------|         "<< endl;
        cout <<"        [2] .  |   Delete Flight Plan   |         "<< endl;
        cout <<"               |------------------------|         "<< endl;
        cout <<"               Enter 0 to return to home.         "<< endl << endl;
        do
        {
            cout << "Enter: ";
            cin >> submenu_option;
        }
        while(cin.fail() || submenu_option < 0 || submenu_option > 2);
        switch(submenu_option)
        {
            case 0: return; break;
            case 1: PrintFlightPlan(flight_number, dep_airport_index, arr_airport_index, altn_airport_index, airports, airports_size, paxnum, pax_weight, cargo_weight, zfw, taxi_fuel, trip_fuel, altn_fuel, reserve_fuel, block_fuel, tow, flight_time, cruise_alt); break;
            case 2: DeleteFlightPlan(dep_airport, arr_airport, altn_airport, paxnum, pax_weight, cargo_weight, zfw, taxi_fuel, trip_fuel, altn_fuel, reserve_fuel, block_fuel, tow, flight_time, cruise_alt); break;
            default: break;
        }
    }
    do
    {
        cout << "Enter 0 to return to home: ";
        cin >> submenu_option;
    }
    while(submenu_option!=0);
}

void CalculationsPage(double &tow, int &v1, int &vr, int &v2, double &trip_fuel, int &vref, int &vapp)
{
    int submenu_option;

    if(tow==OEW)
    {
        cout <<"          -----------------------------------"                 << endl;
        cout <<"          |           CALCULATIONS          |"                 << endl;
        cout <<"          -----------------------------------"                 << endl; 
        cout << "        Weights have not yet been initalialised."               << endl;
        cout << " To perform calculations using user inputs, enter values." << endl;
        cout << "             To return to menu, enter 0."                      << endl << endl;
        cout << "Enter takeoff weight (in kg): ";
        cin >> tow;
        if(tow == 0)
        {
            tow = OEW;
            return;
        }
        cout << "Enter trip fuel (in kg): ";
        cin >> trip_fuel;
        if(trip_fuel == 0) return;
    }
    cout <<"          -----------------------------------    "<< endl;
    cout <<"          |           CALCULATIONS          |    "<< endl;
    cout <<"          -----------------------------------    "<< endl; 
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [1] .  |    Takeoff Speeds    |         "<< endl;
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [2] .  |    Landing Speeds    |         "<< endl;
    cout <<"                |----------------------|         "<< endl;  
    cout <<"               Enter 0 to return to home." << endl << endl;
    do
    {
        cout << "Enter: ";
        cin >> submenu_option;
    }
    while(cin.fail() || submenu_option < 0 || submenu_option > 2);
    switch(submenu_option)
    {
        case 0: return; break;
        case 1: TakeoffSpeeds(tow, v1, vr, v2); break;
        case 2: LandingSpeeds(tow, trip_fuel, vref, vapp); break;
    }
    do
    {
        cout << "Enter 0 to return to home: ";
        cin >> submenu_option;
    }
    while(submenu_option!=0);
}

void DatabaseManagentPage(Airport airports[], int &airports_size)
{
    int submenu_option;
    cout <<"          -----------------------------------    "<< endl;
    cout <<"          |        DATABASE MANAGEMENT      |    "<< endl;
    cout <<"          -----------------------------------    "<< endl; 
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [1] .  |    Display Database  |         "<< endl;
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [2] .  |      Add Airport     |         "<< endl;
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [3] .  |    Remove Airport    |         "<< endl;
    cout <<"                |----------------------|         "<< endl;
    cout <<"         [4] .  |     Edit Airport     |         "<< endl;
    cout <<"                |----------------------|         "<< endl;
    cout <<"               Enter 0 to return to home." << endl << endl;
    do
    {
        cout << "Enter: ";
        cin >> submenu_option;
    }
    while(cin.fail() || submenu_option < 0 || submenu_option > 4);
    switch(submenu_option)
    {
        case 0: return; break;
        case 1: PrintAirports(airports, airports_size); break;
        case 2: AddAirport(airports, airports_size); break;
        case 3: RemoveAirport(airports, airports_size); break;
        case 4: EditAirport(airports, airports_size); break;
        default : break;
    }
    do
    {
        cout << "Enter 0 to return to home: ";
        cin >> submenu_option;
    }
    while(submenu_option!=0);
}

void InformationPage()
{
    int submenu_option;
    cout << endl <<"          -----------------------------------    "<< endl;
    cout <<"          |           Information           |    "<< endl;
    cout <<"          -----------------------------------    "<< endl; 
    cout <<"          Aircraft Type: A320neo (ICAO: A32N)" << endl;
    cout <<"                Passenger Capacity: 180" << endl;
    cout <<"            Maximum Take Off Weight: " << MTOW << "kg" << endl;
    cout <<"            Maximum Landing Weight: " << MLW << "kg" << endl;
    cout <<"   EFB Software developed by Bismah Shoaib & Muhammad Usman" << endl << endl;
    do
    {
        cout << "Enter 0 to return to home: ";
        cin >> submenu_option;
    }
    while(submenu_option!=0);
}

int main()
{
    int paxnum = 0; // Number of passengers
    double pax_weight = 0; // Weight of passengers (in kg)
    double cargo_weight = 0; // Weight of cargo (in kg)
    double zfw = OEW; // "Zero Fuel Weight" = OEW + paxweight + cargo (in kg)
    double taxi_fuel = 0.0; // Weight of taxi fuel (in kg)
    double trip_fuel = 0.0;
    double altn_fuel = 0.0;
    double reserve_fuel = 0.0;
    double block_fuel = 0.0; // Weight of block (total) fuel 
    double tow = zfw; // tow = weight - taxi 
    int flight_time = 0; // Estimated flight time (in minutes)
    int cruise_alt = 0; // Estimated cruise altitude (in ft)
    int v1, vr, v2, vapp, vref; // Takeoff & landing speeds (knots)
    string flight_number;
    int dep_airport_index, arr_airport_index, altn_airport_index;
    string dep_airport = "NULL";
    string arr_airport = "NULL";
    string altn_airport = "NULL";
    Airport airports[AIRPORTSCAPACITY] = 
    {
        {"OPFA", "Faisalabad Intl.", 31.366, 72.995, 591, { {"03L-21R", 2743}, {"03R-21L", 2826} }, {"121.8","118.625","121.5"} },
        {"OPGD", "Gwadar Intl.", 25.233, 62.328, 32, { {"06-24", 1982} }, {"121.8","122.5","123.7"} },
        {"OPGT", "Giglit", 35.918, 74.332, 4796, { {"07-25", 1646} }, {"119.1","122.8","120.75"} },
        {"OPIS", "Islamabad Intl.", 33.551, 72.827, 1761, { {"10L-28R", 3658}, {"10R-28L", 3658} }, {"130.6","122.15","120.75"} },
        {"OPKC", "Jinnah Intl.", 24.906, 67.163, 100, { {"07L-25R", 3200}, {"07R-25L", 3400} }, {"121.6","118.3","123.7"} },
        {"OPLA", "Allama Iqbal Intl.", 31.521, 74.404, 712, { {"18L-36R", 2743}, {"18R-36L", 3360} }, {"118.4","118.1","121.5"} },
        {"OPMT", "Multan Intl.", 30.200, 71.419, 403, { {"18-36", 3204} }, {"121.8","119.1","121.5"} },
        {"OPPS", "Bacha Khan Intl.", 33.989, 71.516, 1211,{ {"17-35", 2743} }, {"118.3","121.5","120.75"} },
        {"OPSD", "Skardu Intl.", 35.339, 75.540, 7316,{ {"14L-32R", 3641}, {"14R-32L", 3641} }, {"121.8","119.7","120.75"} }
    };
    int airports_size = 9;

    int menu_option;
    do
    {
        PrintMainMenu();
        do
        {
            cout << "Enter: ";
            cin >> menu_option;
        }
        while(cin.fail() || menu_option < 1 || menu_option > 5);
        switch(menu_option)
        {
            case 1: FlightPlanningPage(flight_number, dep_airport, arr_airport, altn_airport, dep_airport_index, arr_airport_index, altn_airport_index, airports, airports_size, paxnum, pax_weight, cargo_weight, zfw, taxi_fuel, trip_fuel, altn_fuel, reserve_fuel, block_fuel, tow, flight_time, cruise_alt); break;
            case 2: CalculationsPage(tow, v1, vr, v2, trip_fuel, vref, vapp); break;
            case 3: DatabaseManagentPage(airports, airports_size); break;
            case 4: InformationPage(); break;
            default : break;
        }
    }
    while(menu_option!=5);
    cout << endl << "              See you next time, Captain!" << endl << endl;
    return 0;
}