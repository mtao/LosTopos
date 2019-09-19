/*
 *  runstats.cpp
 *
 *  Created by tyson on 21/04/11.
 *
 */

#include "LosTopos/common/runstats.h"

#include "LosTopos/common/commonoptions.h"
#include <fstream>

namespace LosTopos {

LosTopos::RunStats g_stats;
    
// ------------------------------------------------------------------

void RunStats::set_int( const std::string& name, int64_t value )
{
    int_stats[name] = value;
}

void RunStats::add_to_int( const std::string& name, int64_t increment )
{
    std::optional<int64_t> value= get_int( name );
    if ( !value )
    {
        value = 0;
    }
    *value += increment;
    set_int( name, *value );
}

std::optional<int64_t> RunStats::get_int( const std::string& name )
{
    std::map<std::string, int64_t>::iterator iter = int_stats.find( name );
    if (  iter == int_stats.end() ) { return {}; }
    return iter->second;
}


void RunStats::update_min_int( const std::string& name, int64_t value )
{
    std::optional<int64_t> current_min = get_int( name );
    if ( !current_min) { current_min = value; }
    int_stats[name] = std::min( value, *current_min );
}

void RunStats::update_max_int( const std::string& name, int64_t value )
{
    std::optional<int64_t> current_max = get_int( name );
    if ( !current_max) { current_max = value; }
    int_stats[name] = std::max( value, *current_max );
}

// ------------------------------------------------------------------

void RunStats::set_double( const std::string& name, double value )
{
    double_stats[name] = value;
}

void RunStats::add_to_double( const std::string& name, double increment )
{
    std::optional<double> value = get_double( name);
    if(!value) {
        value = 0;
    }
    *value += increment;
    set_double( name, *value );
}

std::optional<double> RunStats::get_double( const std::string& name )
{
    std::map<std::string, double>::iterator iter = double_stats.find( name );
    if ( iter == double_stats.end() ) { return {}; }
    return iter->second;
}

void RunStats::update_min_double( const std::string& name, double value )
{
    std::optional<double> current_min = get_double( name);
    if ( !current_min ) { current_min = value; }
    double_stats[name] = std::min( value, *current_min );
}

void RunStats::update_max_double( const std::string& name, double value )
{
    std::optional<double> current_max = get_double( name);
    if ( !current_max ) { current_max = value; }
    double_stats[name] = std::max( value, *current_max );
}

// ------------------------------------------------------------------

void RunStats::add_per_frame_int( const std::string& name, int frame, int64_t value )
{
    std::vector<PerFrameInt>& sequence = per_frame_int_stats[name];
    sequence.push_back( PerFrameInt(frame,value) );
}

bool RunStats::get_per_frame_ints( const std::string& name, std::vector<PerFrameInt>& sequence )
{
    std::map<std::string, std::vector<PerFrameInt> >::iterator iter = per_frame_int_stats.find( name );
    if ( iter == per_frame_int_stats.end() )
    {
        return false;
    }
    sequence = iter->second;
    return true;  
}

// ------------------------------------------------------------------

void RunStats::add_per_frame_double( const std::string& name, int frame, double value )
{
    std::vector<PerFrameDouble>& sequence = per_frame_double_stats[name];
    sequence.push_back( PerFrameDouble(frame,value) );
}

bool RunStats::get_per_frame_doubles( const std::string& name, std::vector<PerFrameDouble>& sequence )
{
    std::map<std::string, std::vector<PerFrameDouble> >::iterator iter = per_frame_double_stats.find( name );
    if ( iter == per_frame_double_stats.end() )
    {
        return false;
    }
    sequence = iter->second;
    return true;  
}

// ------------------------------------------------------------------

void RunStats::write_to_file( const char* filename )
{
    std::ofstream file( filename );
    
    // ----------
    if ( !int_stats.empty() )
    {
        file << "int_stats: " << std::endl << "----------" << std::endl;
        std::map<std::string, int64_t>::iterator int_iterator = int_stats.begin();
        for ( ; int_iterator != int_stats.end(); ++int_iterator )
        {
            file << int_iterator->first << ": " << int_iterator->second << std::endl;
        }   
        file << std::endl;
    }
    
    // ----------
    
    if ( !double_stats.empty() )
    {
        file << "double_stats: " << std::endl << "----------" << std::endl;
        std::map<std::string, double>::iterator double_iterator = double_stats.begin();
        for ( ; double_iterator != double_stats.end(); ++double_iterator )
        {
            file << double_iterator->first << ": " << double_iterator->second << std::endl;
        }
        file << std::endl;
    }
    
    // ----------
    
    if ( !per_frame_int_stats.empty() )
    {
        file << "per_frame_int_stats: " << std::endl << "----------" << std::endl;
        std::map<std::string, std::vector<PerFrameInt> >::iterator pfi_iter = per_frame_int_stats.begin();
        for ( ; pfi_iter != per_frame_int_stats.end(); ++pfi_iter )
        {
            file << pfi_iter->first << ": " << std::endl;
            std::vector<PerFrameInt>& sequence = pfi_iter->second;
            for ( unsigned int i = 0; i < sequence.size(); ++i )
            {
                file << sequence[i].first << " " << sequence[i].second << std::endl;
            }
        }
        file << std::endl;
    }   
    
    // ----------
    
    if ( !per_frame_double_stats.empty() )
    {
        file << "per_frame_double_stats: " << std::endl << "----------" << std::endl;
        std::map<std::string, std::vector<PerFrameDouble> >::iterator pfd_iter = per_frame_double_stats.begin();
        for ( ; pfd_iter != per_frame_double_stats.end(); ++pfd_iter )
        {
            file << pfd_iter->first << ": " << std::endl;
            std::vector<PerFrameDouble>& sequence = pfd_iter->second;
            for ( unsigned int i = 0; i < sequence.size(); ++i )
            {
                file << sequence[i].first << " " << sequence[i].second << std::endl;
            }
        }
        file << std::endl;      
    }
    
}

// ------------------------------------------------------------------

void RunStats::clear()
{
    int_stats.clear();
    double_stats.clear();
    per_frame_int_stats.clear();
    per_frame_double_stats.clear();
}

}


