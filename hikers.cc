
#include <iostream>
#include <algorithm>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "hikers.h"

using namespace std;

void hikers::cross_bridge( const YAML::Node& bridge )
{
    int bridge_time = 0;
    int bridge_len = bridge.as<int>();
    int fast_hiker;

    if( hiking_times.size() ) {
        if( hiking_times.size() <= 2 )
            bridge_time = bridge_len / hiking_times[0];
        else {
            fast_hiker = hiking_times[hiking_times.size() - 1];

            for( vector<int>::iterator it = hiking_times.begin(); it < (hiking_times.end() - 1); it++ ) {
                bridge_time += (bridge_len / *it );

                if( (it + 2) != hiking_times.end() )
                    bridge_time += (bridge_len / fast_hiker);
            }
        }
    }

    crossing_times.push_back( bridge_time );
}

void hikers::calculate_crossing_time( void )
{
    int iter = 0;

    for( int i : crossing_times ) {
        total_time += i;
        cout << "Bridge: " << iter << " Time: " << i << " minutes" << endl;
        iter++;
    }

    cout << "Total Time: " << total_time << " minutes" << endl;
}

int main( int argc, char **argv )
{
    hikers h;

    YAML::Node config = YAML::LoadFile("config.yaml");
    h.add_hikers( config["initial_hikers_speed"] );
    h.sort_hiker_times();

    for( YAML::const_iterator it = config["bridges"].begin(); it != config["bridges"].end(); it++ ) {
        h.add_hikers( (*it)["additional_hiker_speed"] );
        h.sort_hiker_times();
        h.cross_bridge( (*it)["length"] );
    }

    h.calculate_crossing_time();

    return 0;
}
