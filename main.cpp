/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   main.cpp
 * Author: Jörn Roddelkopf
 * Version: 1.0 23.02.2017
 * Purpose: Read in a Bind9 Query Log File, filter and Group the Domains and Output as List
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>

/**
 * Stores required Information about a single Domain
 */
struct DomainInfo
{
    std::string domain;
    int         counter;
    std::string date;
    std::string time;
};

/**
 * Remove Spaces from the Strings Left-/Right- Side
 * @param input String to Trim
 */
inline void trim(std::string& input)
{   
    while(input.length() > 0 && isspace(input.at(0)))
    {
        input = input.substr(1);
    }
    
    while(input.length() > 0 && isspace(input.at(input.length() - 1)))
    {
        input = input.substr(0, input.length() - 1);
    }
}

/**
 * Split a given String with at the given Limiter and return a List of Strings
 * containing the splitted Parts.
 * @param str String to split
 * @param delim Delimiter to split at
 * @return List of Strings
 */
inline std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    
    if(str.size() > 0)
    {
        if(delim.size() > 0)
        {
            std::string::size_type currPos = 0;
            std::string::size_type prevPos = 0;
            
            while((currPos = str.find(delim, prevPos)) != std::string::npos)
            {
                std::string item = str.substr(prevPos, currPos - prevPos);
                
                if(item.size() > 0)
                {
                    tokens.push_back(item);
                }
                
                prevPos = currPos + 1;
            }
            
            tokens.push_back(str.substr(prevPos));
        }
        else
        {
            tokens.push_back(str);
        }
    }
    
    return tokens;
}

/**
 * Compare the Domains Counter. Used for Sorting
 * @param a First Domain
 * @param b Second Domain
 * @return True if First Domain has more Counts. False if not
 */
inline bool alphaCompare(DomainInfo a, DomainInfo b)
{
    return a.counter > b.counter;
}

/**
 * Compare the Domains Request Times. Used for Sorting
 * @param a First Domain
 * @param b Second Domain
 * @return True if First Domain was requested earlyer. False if not.
 */
inline bool betaCompare(DomainInfo a, DomainInfo b)
{
    return (a.date + a.time).compare(b.date + b.time) < 0;
}

/**
 * Read in the Highlight File containing the Search Strings that should be
 * marked in Console Output.
 * @param highlightFile Path to the Highlight File
 * @return List of Strings that should be highlighted
 */
std::vector<std::string> readHighlights(std::string highlightFile)
{
    char* s;
    char buff[2084];
    std::vector<std::string> highlightList;
    
    FILE* high_file = fopen(highlightFile.c_str(), "r");
        
    if(high_file == NULL)
    {
        std::cout << "Can not read Highlight File: \"" + highlightFile + "\" Skipping..." << std::endl;
        return highlightList;
    }
       
    while((s = fgets(buff, sizeof buff, high_file)) != NULL)
    {
        if(buff[0] == '\n' || buff[0] == '#')
            continue;
            
        std::string line = std::string(buff);
        trim(line);
            
        highlightList.push_back(line);
    }
        
    fclose(high_file);
    
    return highlightList;
}

/**
 * Check if a given Domain contains one of the Search Strings that should be
 * highlighted.
 * @param domain Domain Name to search in
 * @param highlightList List of Strings to search for
 * @return True if should be highlighted. False if not.
 */
inline bool isHighlighted(std::string domain, std::vector<std::string>& highlightList)
{
    for(unsigned int i = 0; i < highlightList.size(); i++)
    {
        if(domain.find(highlightList.at(i)) != std::string::npos)
            return true;
    }
    
    return false;
}

/**
 * Main Entry Point of this Application.
 * @param argc Number of Arguments
 * @param argv Array of Arguments
 * @return Execution Result
 */
int main(int argc, char** argv) 
{
    // Say Hello and parse the Command Line Arguments
    std::cout << "Bind Domain Lister\n\nUsage: BDLister <Log File> <IP Address | Search String> <Output File | -> <Sorting: time | count> [Highlight: Needle File]\n\n";
    
    if(argc < 5)
    {
        std::cout << "Not enough Arguments provided! Exiting..." << std::endl;
        return EXIT_FAILURE;
    }
    
    std::string input_file(argv[1]);
    std::string needle(argv[2]);
    std::string output_file(argv[3]);
    std::string sorting(argv[4]);
    std::string highlightFile = "";
    char* s;
    char buff[2084];
    
    if(argc > 5)
    {
        highlightFile = std::string(argv[5]);
    }
    
    // Read the Needles to Highlight (if requested)
    std::vector<std::string> highlightList;
    
    if(highlightFile.length() > 0)
    {
        highlightList = readHighlights(highlightFile);
    }

    // Read the Query Log
    std::vector<DomainInfo> result_list;
    
    FILE* log_file = fopen(input_file.c_str(), "r");
        
    if(log_file != NULL)
    {
        std::cout << "Reading Input File: " << input_file << std::endl;
        
        while((s = fgets(buff, sizeof buff, log_file)) != NULL)
        {
            if(buff[0] == '\n' || buff[0] == '#')
              continue;
            
            std::string line = std::string(buff);
            trim(line);
            
            // Check if the Entry is of interest
            if(line.find(needle) != std::string::npos)
            {
                // Parse the Line into a DomainInfo Struct
                std::vector<std::string> s_parts = split(line, " ");

                DomainInfo tmp_info;
                tmp_info.counter = 1;
                tmp_info.date = s_parts.at(0);
                tmp_info.time = s_parts.at(1);
                tmp_info.domain = s_parts.at(6).substr(1, s_parts.at(6).length() - 1);
                
                // Keep only the root Domain (google.com instead of api.google.com)
                std::vector<std::string> domain_parts = split(tmp_info.domain, ".");
                
                if(domain_parts.size() > 2)
                    tmp_info.domain = domain_parts.at(domain_parts.size() - 2) + "." + domain_parts.at(domain_parts.size() - 1);
                
                // Check if already in List. Increment it's counter if yes or add it if not
                bool found = false;
        
                for(long unsigned int x = 0; x < result_list.size(); x++)
                {
                    if(result_list.at(x).domain.compare(tmp_info.domain) == 0)
                    {
                        result_list.at(x).counter++;
                        result_list.at(x).date = tmp_info.date;
                        result_list.at(x).time = tmp_info.time;
                        found = true;
                    }
                }

                if(!found)
                    result_list.push_back(tmp_info);
            }
        }

        fclose(log_file);
    }
    else
    {
        std::cout  << "Can not access the Input file! Exiting..." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Sort the resulting Domain List
    if(sorting.compare("count") == 0)
        std::sort(result_list.begin(), result_list.end(), alphaCompare);
    else
        std::sort(result_list.begin(), result_list.end(), betaCompare);
    
    // Create the Console Output (if choosen)
    if(output_file.compare("-") == 0)
    {
        for(long unsigned int i = 0; i < result_list.size(); i++)
        {
            std::string text = result_list.at(i).date + " " + result_list.at(i).time + " " + result_list.at(i).domain + " (" + std::to_string(result_list.at(i).counter) + ")";
            
            if(isHighlighted(result_list.at(i).domain, highlightList))
            {
                text = "\033[1;31m" + text + "\033[0m";
            }
            
            text += "\r\n";
            
            std::cout << text;
        }
        
        std::cout << std::endl;
        
        return EXIT_SUCCESS;
    }
    
    // Create the File Output (if choosen)
    FILE* needled_file = fopen(output_file.c_str(), "a+");
        
    if(needled_file != NULL)
    {
        for(long unsigned int i = 0; i < result_list.size(); i++)
        {
            std::string text = result_list.at(i).date + " " + result_list.at(i).time + " " + result_list.at(i).domain + " (" + std::to_string(result_list.at(i).counter) + ")\r\n";
            fputs(text.c_str(), needled_file);
        }
        
        fclose (needled_file);
    }
    
    std::cout << "Output written to: " << output_file << std::endl;
    
    return EXIT_SUCCESS;
}
