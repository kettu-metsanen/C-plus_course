/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2021                                    #
# Project3: Directory structure                                             #
# File: directoryhierarchy.hh                                               #
# Description: Directory hierarchy -class datastructure                     #
#       Datastructure is populated with Directory-structs and provides some #
#       query functions.                                                    #
# Notes: * This is a part of an exercise program                            #
#        * Student's aren't allowed to alter public interface!              #
#        * All changes to private side are allowed.                         #
#############################################################################
# Ohjelman kirjoittaja: Anna Rumiantseva
# Opiskelijanumero: 50309159
# Käyttäjätunnus: rdanru
# E-mail: anna.rumiantseva@tuni.fi

# Additional comments: Unfortunately I didn't have enough time to get
# the code "nice" because of lack of time. During this project
# my husband and daughter got sick. Thank you.
*/
#ifndef DIRECTORYHIERARCHY_HH
#define DIRECTORYHIERARCHY_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <sstream>

// Named constants to improve readability in other modules
const std::string EMPTY = "";
const int NO_SIZE = -1.0;

// Struct for a directory
struct Directory
{
    std::string id_ = EMPTY;
    std::string timestamp_ = EMPTY;
    int size_ = NO_SIZE;
    Directory* parent_ = nullptr;
    std::vector<Directory*> subdirectories_;
};

// Set of strings
using IdSet = std::set<std::string>;

/*  Class: DirectoryHierarchy
 *  Description: Datastructure for Directory-structs
 */
class DirectoryHierarchy
{
public:
    DirectoryHierarchy();
    ~DirectoryHierarchy();

    /* Description: Adds a new directory to the datastructure.
     * Parameters:
     *  Param1: Director's ID (name) string
     *  Param2: Director's timestamp
     *  Param3: Director's size
     *  Param4: Output-stream for error-printing
     * Errormessages:
     *  If director's ID is already in datastructure:
     *      "Error. Directory already added."
     */
    void addNewDirectory(const std::string& id, const std::string& timestamp,
                         int size, std::ostream &output);

    /* Description: Adds a new directory-parentdirectory relation.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: ID of the directory's parent
     *  Param3: Output-stream for error-printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void addRelation(const std::string& directory,
                     const std::string& parent,
                     std::ostream& output);

    /* Methods implementing commands */

    /* Description: Prints the current working directory with its path.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandPrintWorkingDirectory(std::ostream& output) const;

    /* Description: Prints the subdirectories of the current working directory.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandList(std::ostream& output) const;

    /* Description: Prints the disk usage of the current working directory.
     * Disk usage is counted as the sum of the sizes of the current working
     * directory and all its subdirectories.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandDiskUsage(std::ostream& output) const;

    /* Description: Changes the working directory to the subdirectory ID,
     * or home, or to the parent of the current working directory.
     *  Param1: ID of the directory, or "~", or "..".
     *  Param2: Output-stream for printing
     * Errormessages:
     *  If ID is not a subdirectory of the current working directory,
     *  prints the error message:
     *      "Error. <ID> not found."
     *  If the current working directory is home and if ID is "..",
     *  prints the error message:
     *      "Error. Already at the root."
     */
    void commandChangeDirectory(const std::string& id, std::ostream& output);

    /* Description: Finds the subdirectory ID of the current working directory
     * and prints all its subdirectories with their paths down to level n.
     * Parameters:
     *  Param1: ID of the subdirectory
     *  Param2: Maximum distance from the current working directory
     *  (n-1 times "hierarchy").
     *  Param3: Output-stream for printing
     * Errormessages:
     *  If ID is not a subdirectory of the current working directory,
     *  prints the error message:
     *      "Error. <ID> not found."
     *  If Param2's value is less than 1, prints the error message:
     *      "Error. Level can't be less than 1.
     */
    void commandFind(const std::string& id, const int n, std::ostream& output) const;

    /* Description: Prints all directories sharing their timestamps with the
     * given one in the same hierarchy as the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void commandAsOldAs(const std::string& id, std::ostream& output) const; // VOLUNTARY

    /* Description: Prints the greatest directory in hierarchy starting
     * from the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void commandGreatest(const std::string& id, std::ostream& output) const; // VOLUNTARY

    /* Description: Prints the smallest directory in hierarchy starting
     * from the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void commandSmallest(const std::string& id, std::ostream& output) const; // VOLUNTARY
    //void myTestFunct();
private:
    /* The following methods are meant to make project easier.
     * You can implement them if you want and/or create your own.
     * Anyway it would be a good idea to implement more methods
     * to make things easier and to avoid "copy-paste-coding".
     */

    // Returns the pointer for ID.
    Directory* getPointer(const std::string& id) const;

    // Returns subdirectories of the working directory.
    IdSet getSubdirectors() const;

    // Prints errors.
    void printNotFound(const std::string& id, std::ostream& output) const;

    // Prints the the data in a container.
    void printContainer(const IdSet& container, std::ostream& output) const;

    // Prints the path of the directory.
    void printPath(Directory* dir, std::ostream& output) const;

    Directory home_; // root of the tree structure
    Directory* work_; // pointer to the current directory
    std::vector<Directory> all_struct; // this vector contains all the Directory objects

    // More private methods and attributes
};

#endif // DIRECTORYHIERARCHY_HH
