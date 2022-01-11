/*
#############################################################################
# COMP.CS.110 Programming 2, Autumn 2021                                    #
# Project3: Directory structure                                             #
# File: cli.cpp                                                             #
# Description: Commandline interface for the program.                       #
# Notes: * This is a part of an exercise program                            #
#        * Student's don't touch this file.                                 #
# Check the cli.hh for more info.                                           #
#############################################################################
*/
#include <iostream>
#include <algorithm>

#include "cli.hh"

Cli::Cli(std::shared_ptr<DirectoryHierarchy> db):
    database_(db),recognized_(nullptr)
{
}

bool Cli::exec_prompt()
{
    // Always clear the command at first.
    args_.clear();
    recognized_ = nullptr;

    // Query for the command
    std::string line;
    std::cout << PROMPT;
    std::getline(std::cin, line);

    // Get the args from input
    parseCommand(line);

    /* Recognize and execute the command.
     * Interesting notion: You have to change shared_ptr to raw pointer
     * in order to execute the class-method through the function pointer.
     */
    switch (checkCommandType()) {
    case Commandtypes::WRONG_PARAMETERS:
        std::cout << "Wrong amount of parameters." << std::endl;
        return true;
    case Commandtypes::QUIT:
        return false;
    case Commandtypes::NO_PARAMETERS:
        // Compare to a usual function call:
        // database->printPersons(std::cout);
        ((database_.get())->*(recognized_->func0_))(std::cout);
        break;
    case Commandtypes::ONE_PARAMETER:
        if(recognized_->func1_ != nullptr) // const function
        {
            ((database_.get())->*(recognized_->func1_))(args_.at(1),std::cout);
        }
        else // if(recognized_->func1_nc_ != nullptr) // non-const function
        {
            ((database_.get())->*(recognized_->func1_nc_))(args_.at(1),std::cout);
        }
        break;
    case Commandtypes::TWO_PARAMETER:
        ((database_.get())->*(recognized_->func2_))(args_.at(1),
                                                    std::stoi(args_.at(2)),
                                                    std::cout);
        break;
    case Commandtypes::EMPTY:
        return true;
    default:
        std::cout << "Unknown command." << std::endl;
    }
    return true;
}

bool Cli::isEmpty(const std::string& str)
{
    for(char ch : str)
    {
        if(ch != ' ')
        {
            return false;
        }
    }
    return true;
}

void Cli::parseCommand(const std::string &line)
{
    if(line.empty())
    {
        return;
    }

    std::string current_arg = "";

    // Separate each word to a different argument
    for(unsigned int i = 0; i < line.size() - 1; ++i)
    {
        if(line.at(i) == '\\' and line.at(i + 1) == ' ') // found "\ "
        {
            ++i; // Dangerous operation
            current_arg += ' ';
        }
        else if(line.at(i) == ' ')                      // found " "
        {
            if(not isEmpty(current_arg))
            {
                args_.push_back(current_arg);
            }
            current_arg = "";
        }
        else                                            // otherwise
        {
            current_arg += line.at(i);
        }
    }
    // The last character left unread in the previous for
    current_arg += line.back();
    // The last argument left without push_back in the previous for
    if(not isEmpty(current_arg))
    {
        args_.push_back(current_arg);
    }
}

int Cli::checkCommandType()
{
    if(args_.empty())
    {
        return EMPTY;
    }

    // Remove the case sensitivity.
    std::string base = args_[0];
    std::transform(base.begin(), base.end(),base.begin(), ::toupper);

    // Loop through the commands and find the correct one.
    for(auto &i : COMMANDS)
    {
        for(auto &j : i.lines_)
        {
            if(j == base)
            {
                recognized_ = &i;

                /* Here we us goto to break out of both loops. Normally
                 * you should avoid using goto in C++ and it is considered
                 * totally unacceptable by some people.
                 * Personal opinion: this is one of the few cases where it is
                 * acceptable.
                 */
                goto cctlout;
            }
        }
    }
    // label, where the loop-breaking goto jumps.
cctlout:;

    /* Check for the special cases:
     * 1: Command not recognized
     * 2: Command is exit-command
     * 3: Command doesn't have correct amount of parameters.
     */
    if( recognized_ == nullptr)
    {
        return UNKNOWN;
    }
    if( recognized_ == &COMMANDS[0] )
    {
        return QUIT;
    }
    if((args_.size() == 1 and recognized_->func0_ == nullptr) or
       (args_.size() == 2 and recognized_->func1_ == nullptr and recognized_->func1_nc_ == nullptr) or
       (args_.size() == 3 and recognized_->func2_ == nullptr) or
       (args_.size() > 3))
    {
        return WRONG_PARAMETERS;
    }

    // Normally we just return the amount of arguments.
    return args_.size();
}

