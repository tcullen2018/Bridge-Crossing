
#ifndef INCLUDED_HIKERS_H
#define INCLUDED_HIKERS_H

using namespace std;

class hikers {
    vector<int> hiking_times;
    vector<int> crossing_times;
    int total_time;

public:
    hikers() { total_time = 0; }
    ~hikers() {}

    void add_hikers( const YAML::Node& hikers ) { for( YAML::const_iterator it = hikers.begin(); it != hikers.end(); it++ )
                                                       hiking_times.push_back( it->as<int>() );
                                                }
    void cross_bridge( const YAML::Node& );
    void calculate_crossing_time( void );
    void sort_hiker_times( void ) { sort( hiking_times.begin(),hiking_times.end() ); }
};

#endif
