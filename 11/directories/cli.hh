/*
#############################################################################
# COMP.CS.110 Programming 2, Autumn 2021                                    #
# Project3: Directory structure                                             #
# File: cli.hh                                                              #
# Description: Commandline interface for the program.                       #
# Notes: * This is a part of an exercise program                            #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#        * This is also an example how you can use function pointers to     #
#          a class' functions.                                              #
#        * This could be upgraded to have commandhistory with a relative    #
#          ease.                                                            #
#############################################################################
*/
#ifndef CLI_HH
#define CLI_HH

#include <string>
#include <vector>
#include <memory>

#include "directoryhierarchy.hh"

/* In order to define a function pointer to a class you have to add
 * class as the visibility range before the pointer declaring * and
 * after that comes the type-name for the pointer.
 * In this case we have named the types according to the amount of parameters
 * the function receives and whether the function is constant or not.
 */
typedef void (DirectoryHierarchy::*oneparam)(std::ostream&) const;
typedef void (DirectoryHierarchy::*twoparam)(const std::string&, std::ostream&) const;
typedef void (DirectoryHierarchy::*twoparam_non_const)(const std::string&, std::ostream&);
typedef void (DirectoryHierarchy::*threeparam)(const std::string&, const int, std::ostream&) const;

// CommandInfo contains the list of strings (command names and aliases) and
// function pointers to the function that is going to be called through it.
struct CommandInfo
{
    std::vector<std::string> lines_;
    oneparam func0_;
    twoparam func1_;
    twoparam_non_const func1_nc_;
    threeparam func2_;
};


class Cli
{
public:
    // The database that is going to be used is given as a parameter.
    Cli(std::shared_ptr<DirectoryHierarchy> db);

    /* Description: Runs the interface.
     * Return values:
     *  True    - Normal command
     *  False   - Exit command
     */
    bool exec_prompt();

private:
    std::shared_ptr<DirectoryHierarchy> database_;

    // Stores the arguments from current command.
    std::vector<std::string> args_;

    // Pointer to the recognized command.
    const CommandInfo* recognized_;

    // Printed for every query
    const std::string PROMPT = "> ";

    /* Description: Checks if the given string contains only empty spaces.
     * Return values:
     *  True    - str consists only of empty spaces
     *  False   - str contains also other characters than just spaces
     */
    bool isEmpty(const std::string& str);

    // Parses the given input to different arguments
    void parseCommand(const std::string& line);

    /* Description: Sets the recognized_ to point at the correct
     * CommandInfo.
     * Return values:
     *  Amount of arguments - Command can be executed
     *  -1                  - Exit command
     *  -2                  - Invalid amount of parameters
     *  -3                  - Command not recognized.
     */
    int checkCommandType();

    // To make code more readable. Could also be different constants but this
    // groups them better.
    enum Commandtypes {QUIT = -1, NO_PARAMETERS = 1, ONE_PARAMETER = 2,
                       TWO_PARAMETER = 3, EMPTY = 0, UNKNOWN = -3,
                       WRONG_PARAMETERS = -2};


    // Constant table that contains the different commands that the CLI can
    // recognize.
    CommandInfo const COMMANDS[10] = {
        {{"EXIT","QUIT","Q"},nullptr,nullptr,nullptr,nullptr},
        {{"AS_OLD_AS","AOA"},nullptr,&DirectoryHierarchy::commandAsOldAs,nullptr,nullptr},
        {{"GREATEST"},nullptr,&DirectoryHierarchy::commandGreatest,nullptr,nullptr},
        {{"SMALLEST"},nullptr, &DirectoryHierarchy::commandSmallest,nullptr,nullptr},
        {{"LIST","LS"},&DirectoryHierarchy::commandList,nullptr,nullptr,nullptr},
        {{"CHANGE_DIRECTORY","CD"},nullptr,nullptr,&DirectoryHierarchy::commandChangeDirectory,nullptr},
        {{"PRINT_WORKING_DIRECTORY","PWD"},&DirectoryHierarchy::commandPrintWorkingDirectory,nullptr,nullptr,nullptr},
        {{"DISC_USAGE","DU"},&DirectoryHierarchy::commandDiskUsage,nullptr,nullptr,nullptr},
        {{"FIND"},nullptr,nullptr,nullptr,&DirectoryHierarchy::commandFind},  
        {{},nullptr,nullptr,nullptr,nullptr}
    };
};

#endif // CLI_HH
