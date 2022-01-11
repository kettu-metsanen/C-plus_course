/*
#############################################################################
# COMP.CS.110 Programming 2, Autumn 2021                                    #
# Project3: Directory structure                                             #
# Program description: Queries user for CSV-file and allows simple searches #
#       based on the data.                                                  #
# File: main.cpp                                                            #
# Description: Main-module performs the followin operations:                #
#       * Query for input file.                                             #
#       * Parse the CSV-data                                                #
#       * Pass the parsed data to Directory-module                          #
#       * Launch Cli-module                                                 #
# Notes: * This is an exercise program.                                     #
#        * Student's don't touch this file.                                 #
#############################################################################
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "directoryhierarchy.hh"
#include "cli.hh"

// Constants to make CSV-parsing more readable.
const char CSV_DELIMITER = ';';
const int CSV_VALUES = 4;
const int CSV_NAME = 0, CSV_TIMESTAMP = 1, CSV_TIME = 2, CSV_PARENT = 3;


// Struct to group-up directory-parent relations.
struct Relation
{
    std::string directory_;
    std::string parent_;
};

bool populateDatabase(std::ifstream &datafile,
                      std::shared_ptr<DirectoryHierarchy> database);
Directory parseDirectory(const std::string &line,
                         std::vector<Relation> &relations);

int main()
{
    std::string cmd_string;
    std::shared_ptr<DirectoryHierarchy> database(new DirectoryHierarchy);
    //DirectoryHierarchy testPeremen;
    // File query
    std::cout << "Input file: ";
    std::getline(std::cin, cmd_string);

    // Query result must be transformed from std::string to c_string so it can
    // be passed to ifstream's constructor.
    std::ifstream datafile(cmd_string.c_str());

    if(not datafile)
    {
        std::cout << "Could not open file: " << cmd_string << std::endl;
        return EXIT_FAILURE;
    }

    // populateDatabase returns false if there was some error in file.
    if(not populateDatabase(datafile, database))
    {
        return EXIT_FAILURE;
    }
    // Constructing the command line interpreter with the given main
    // datastructure.
    Cli commandline(database);

    // Empty loop that runs the CLI.
    // CLI returns false only on exit-command.
    while(commandline.exec_prompt()){

    }
    //database->myTestFunct();
    return EXIT_SUCCESS;
}


/* Description: Reads throught the datafile and populates the database with it.
 * Parameters:
 *  Param1: Datafile-object
 *  Param2: Pointer to the database
 * Return values:
 *  True    - No errors in file
 *  False   - Errors in file
 */
bool populateDatabase(std::ifstream& datafile,
                      std::shared_ptr<DirectoryHierarchy> database)
{
    std::string line = "";
    std::vector<Relation> relations;
    int line_number = 0;
    while(std::getline(datafile, line))
    {
        // Linenumbering for error-printing.
        ++line_number;

        // Skip empty and commented lines.
        if(line.empty() or line[0] == '#')
        {
            continue;
        }

        // Parse the line to a new directory and relation.
        Directory new_directory = parseDirectory(line, relations);
        if( new_directory.id_ == EMPTY or new_directory.size_ == NO_SIZE )
        {
            std::cout << "Error in datafile, line " << line_number
                      << std::endl;
            return false;
        }

        // Add the new directory to the database.
        database->addNewDirectory(new_directory.id_,
                                  new_directory.timestamp_,
                                  new_directory.size_,
                                  std::cout);

    }

    // After all the directories have been created, add the directory-parent
    // relations.
    for( auto it = relations.begin(); it != relations.end(); ++it)
    {
        database->addRelation(it->directory_, it->parent_, std::cout);
    }
    return true;
}

/* Description: Parse string to a new directory and directory-parent relation.
 * Parameters:
 *  Param1: String to parse
 *  Param2: Container for Relations
 * Return values:
 *  Directory-struct that was created.
 *      id_     - EMPTY if wrong amount of parameters
 *      size_   - NO_SIZE if wrong amount of parameters or string-to-int
 *                conversion failed.
 */

Directory parseDirectory(const std::string& line,
                         std::vector<Relation> &relations)
{
    std::string tmp = line;
    std::vector<std::string> parsed_data;
    size_t pos = 0;
    Directory new_directory;
    Relation new_relation;

    // Split the ';' separated fields to a vector.
    while (true)
    {
        pos = tmp.find(CSV_DELIMITER);
        parsed_data.push_back(tmp.substr(0, pos));
        if(pos == std::string::npos){break;}
        tmp = tmp.substr(pos+1);
    }

    // Check the that there was correct amount of fields in the line.
    if( parsed_data.size() == CSV_VALUES )
    {
        new_directory.id_ = parsed_data[CSV_NAME];
        new_directory.timestamp_ = parsed_data[CSV_TIMESTAMP];
        // Exception safety.
        // The NO_SIZE assignment isn't necessary, but makes things clearer.
        try{
            new_directory.size_ = std::stoi(parsed_data[CSV_TIME]);
        }
        catch(std::invalid_argument&)
        {
            std::cout << "Caught invalid_argument exception." << std::endl;
            new_directory.size_ = NO_SIZE;
        }
        catch(std::out_of_range&)
        {
            std::cout << "Caught out_of_range exception." << std::endl;
            new_directory.size_ = NO_SIZE;
        }
        new_relation.directory_ = parsed_data[CSV_NAME];
        new_relation.parent_ = parsed_data[CSV_PARENT];
        relations.push_back(new_relation);
    }

    return new_directory;
}
