/*
# Ohjelman kirjoittaja: Anna Rumiantseva
# Opiskelijanumero: 50309159
# Käyttäjätunnus: rdanru
# E-mail: anna.rumiantseva@tuni.fi

# Additional comments: Unfortunately I didn't have enough time to get
# the code "nice" because of lack of time. During this project
# my husband and daughter got sick. Thank you.
*/
#include "directoryhierarchy.hh"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

DirectoryHierarchy::DirectoryHierarchy()
{
    /*
     * Constructor: creates "virtual" directory home, which is suppose to be the root
     * of the whole structure
     * */
    home_.id_ = "home";
    home_.timestamp_ = EMPTY;
    home_.size_ = NO_SIZE;
    home_.parent_ = nullptr;
    work_ = &home_;
}

DirectoryHierarchy::~DirectoryHierarchy()
{
    /*
     * Destructor. I didn't invent what to do here
     * */

}

void DirectoryHierarchy::addNewDirectory(const std::string &id, const std::string &timestamp, int size, std::ostream &output)
{
    Directory newDirectory; // Creating and filling a new Directory object
    newDirectory.id_=id;
    newDirectory.size_=size;
    newDirectory.timestamp_=timestamp;
    if(all_struct.size() == 0) // if vector with Directory objects is empyt
    {
        all_struct.push_back(newDirectory); // then just push the object there
    }
    else
    {
        for(unsigned int i = 0; i <= all_struct.size(); i++) // if not empty
        {
            if(all_struct[i].id_ == id) // check if this is already exists
            {
                output << "Error. Directory already added." << std::endl;
                return;
            }

        }
        all_struct.push_back(newDirectory); // if no duplicates then push

    }

}

void DirectoryHierarchy::addRelation(const std::string &directory, const std::string &parent, std::ostream &output)
{
    /*
     * This method takse as parameters id of a Directory object and id of parent Directory and std::cout object.
     * Method creates relations between directory and its parent
     * */
    Directory* dir=nullptr; // pointer for Directory object
    Directory* par = nullptr; // pointer for parent of a Directory object

    for(auto it=all_struct.begin(); it != all_struct.end(); ++it) // Find Directory object by its id from vector
    {
        if(it->id_ == directory)
        {
            dir = &*it;
            break;
        }
    }
    if(parent == EMPTY)
    {
        par = &home_; // if parent is empty, then the parent will be "home"
    }
    else // if parent is not empty
    {
        for(auto it=all_struct.begin(); it!=all_struct.end(); ++it) // find parent by id
        {
            if(it->id_ == parent)
            {
                par = &*it;
                break;
            }
        }
    }
    if(par == nullptr) // if still didn't found, then error
    {
        output << "Error. " << parent <<" not found." << std::endl;
        return;
    }
    if(dir != nullptr) // otherwise create relations
    {
        dir->parent_ = par;
        par->subdirectories_.push_back(dir);
    }

}

void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream &output) const
{
    /*
     * Method takes as parameter std::cout object.
     * This method collects subdirectories of the "work"-directory into a vector
     * and prints the vector.
     * */
    Directory* temp = work_; // get pointer to the work directory
    std::vector<std::string> pwd; // create vector of strings
    while(temp->parent_ != nullptr) // while temp on in the root
    {
      pwd.push_back(temp->id_); // collect subdirectories
      temp = temp->parent_; // go up in the tree
    }
    pwd.push_back(home_.id_); // get home id
    for(auto it=pwd.end()-1; it >= pwd.begin(); --it) // print the vector
    {
        output << "/" << *it;
    }
    output << std::endl;
}

void DirectoryHierarchy::commandList(std::ostream &output) const
{
    /*
     * This method takes as parameter std::cout object.
     * The mehtod lists working directory with additional information
     * */
    std::vector<Directory*> temp = work_->subdirectories_; // get subdirectories of the working directory
    std::set<std::string> dirs; // create vector for output
    for(unsigned int i=0; i<temp.size(); ++i) // insert subdirectories into the vector
    {
        dirs.insert(temp[i]->id_ );
    }
    for(auto it=dirs.begin(); it != dirs.end(); ++it) // go through the dirs vector
    {
        output << *it; // print each directory
        for(unsigned int i=0; i < all_struct.size(); i++) // find additional information about particular directory
        {
            if(*it == all_struct[i].id_)
            {
                output << ", " << all_struct[i].timestamp_ << ", " << all_struct[i].size_ << std::endl; // print
            }
        }
    }


}

int recursive_du(Directory* root)
{
    /*
     * Help function for commandDiskUsage. Takes as parameter pointer to the directory
     * */
    int cumulative=0; // create cumulative sum variable
    for(unsigned int i=0; i<root->subdirectories_.size(); ++i) // go through each subdirectory of each node
    {
        cumulative += recursive_du(root->subdirectories_[i]); // accumulate values
    }
    cumulative += root->size_;
    return cumulative;

}

void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const
{
    /*
     * Method implementing "du" command. Takes as parameter std::cout object.
     * Method collects values into a map.
     * */
    std::map<std::string,int> list; // create map
    for(unsigned int i=0; i<work_->subdirectories_.size(); i++) // go through each subdirectory in the node
    {
        list[work_->subdirectories_[i]->id_] = recursive_du(work_->subdirectories_[i]); // get values recursively
    }
    for(auto it=list.begin(); it != list.end(); ++it) // printing the map
    {
        output << it->second << " /" << it->first << std::endl;
    }
}

void DirectoryHierarchy::commandChangeDirectory(const std::string &id, std::ostream &output)
{
    /*
     * Mehtod for navigating in the structure. Takes as arguments id of directory to be entered and std::cout object
     * */
    Directory* temp = work_; // create temporary pointer
    if(id == "..") // implementing "go up" in the structure
    {
        if(work_ == &home_) // can't go beyond the home
        {
            output << "Error. Already at the root." << std::endl;
            return;
        }
        work_ = work_->parent_;
    }
    if(id == "~") // go directly to the home
    {
        work_ = &home_;
    }
    for(unsigned int i = 0; i<work_->subdirectories_.size(); i++) // if there are no other options
    {
        if(work_->subdirectories_[i]->id_ == id) // find the directory to be entered from subdirectories
        {
            work_ = work_->subdirectories_[i]; // set it to be work directory
        }
    }
    if(work_ == temp) // if the directory to be entered was not found in the previous loop, then it does not exist
    {
        output << "Error. "<< id << " not found." << std::endl;
        return;
    }

}


bool cmp(const Directory* a, const Directory* b)
{
    /*
     * Help function for sorting container with Directory objects.
     * Takes as parameters two pointers to Directory object and compares.
     * */
    return a->id_ < b->id_;
}

void traverse(Directory* root, std::string tpr, int level)
{
    /*
     * Recursive help-function for implementing commandFind-method. Takes as parameters start node (root),
     * string tpr for collecting directory id's, and level or depth (how deep to dive).
     * Got down along the tree collecting directory names and sorting them
     * */
    if(level == 0) // if level is achieved returning from all recursions
    {
        return;
    }
    tpr += root->id_ + "/"; // set/preset string tpr with directory paths
    std::vector<Directory*> test; // create vector for keeping subdirectories of each node
    for(unsigned int i =0 ; i < root->subdirectories_.size(); i++)
    {
        test.push_back(root->subdirectories_[i]);
    }
    std::sort(test.begin(), test.end(), &cmp); // sort subdirectories using function above
    for(unsigned int i=0; i < test.size(); i++) // go through each subdirectory
    {
        std::cout << tpr + test[i]->id_ << std::endl; // print string tpr and name of current node
        traverse(test[i], tpr, level-1); // recursive call
    }

}


void DirectoryHierarchy::commandFind(const std::string &id, const int n, std::ostream &output) const
{
    /*
     * Method for implementing command Find. This method prints subdirectories up to level N (2nd parameter) sorting directory id's.
     * Takes as parameters id of directory to start from and n - the deepest level to dive
     * */
    Directory *local_work = nullptr; // pointer to local "work" directory
    if(n < 1) // if depth is less than 1
    {
        output << "Error. Level can't be less than 1." << std::endl;
        return;
    }
    for(unsigned int i=0; i < work_->subdirectories_.size(); i++) // find given directory from structure by id
    {
        if(work_->subdirectories_[i]->id_ == id)
        {
            local_work = work_->subdirectories_[i];
        }
    }
    if(local_work != nullptr) // if found
    {
        //std::vector<Directory*> test = local_work->subdirectories_;
        traverse(local_work,"", n); // call recursive function
    }
    return;

}

std::set<std::string> recursive_asoldas(Directory* root, std::string originalts, std::set<std::string> &temp, std::string originalnm)
{
    /*
     * Help function for implementing method as_old_as. Takes as parameters:
     * root - node to start from
     * originalts - timestamp at start
     * temp - set for collecting directory names
     * originaltm - name of the start node
     * */
    if((root->timestamp_ == originalts) && (root->id_ != originalnm)) // if time stamp we are looking for
    {
        temp.insert(root->id_); // insert into the set
    }
    for(unsigned int i=0; i<root->subdirectories_.size(); i++) // recursive call for all subdirectories of the current node
    {
        recursive_asoldas(root->subdirectories_[i], originalts, temp, originalnm);
    }
    return temp; // return filled list
}

void DirectoryHierarchy::commandAsOldAs(const std::string &id, std::ostream &output) const
{
    /*
     * Method for implementing as_old_as command. takes as parameters id of the node to be compared and std::cout object
     * */

    Directory* asroot = nullptr; // create pointer for the node to be compared
    Directory tobe_found; // directory that will be found
    bool found = false; // flag signalizing if id was not found from the vector of Directories
    for(auto it=all_struct.begin(); it!=all_struct.end(); ++it) // find Directory by id
    {
        if(it->id_ == id)
        {
            tobe_found = *it;
            found = true;
            break;
        }

    }
    if(!found)
    {
        output << "Error. " << id << " not found." << std::endl;
        return;
    }
    asroot = &tobe_found; // get pointer of the found Directory
    std::set<std::string> temp; // prepare a set for filling
    recursive_asoldas(asroot, tobe_found.timestamp_, temp, tobe_found.id_); // recursive call: down along the tree
    asroot = &tobe_found; // reset asroot pointer
    while(true) // go up along the tree
    {

        for(unsigned int i=0; i<asroot->subdirectories_.size(); i++) // get one node up and enumerate subdirectories
        {
            // if timestamp we want & not the name of the start node
            if((asroot->subdirectories_[i]->timestamp_ == tobe_found.timestamp_ ) && (asroot->subdirectories_[i]->id_ != tobe_found.id_))
            {
                temp.insert(asroot->subdirectories_[i]->id_); // add this name to the existing set
            }
        }
        if(asroot->timestamp_ != tobe_found.timestamp_) // if timestamp of the parent is not the same as starting node
        {
            break; // break loop
        }
        asroot = asroot->parent_; // go up one level along the tree
        if(asroot->id_ == "home") // if current node is "home"
        {
            break;
        }

    }

    for(auto elem : temp) // print collected elements
    {
        output << elem << std::endl;
    }
}

std::map<std::string, int> recursive_greatest(Directory* root, std::map<std::string, int> &map)
{
    /*
     * Help method for implementing method greatest and smallest. Takes as parameters starting node root
     * and map to be filled with nodes and their sizes. Theis recursion simply goes down from starting
     * node and fills the map
     * */
    map[root->id_] = root->size_; // place the current node into the map
    for(unsigned int i=0; i<root->subdirectories_.size(); i++)
    {
        recursive_greatest(root->subdirectories_[i], map); // recursive call
    }
    return map;

}

void DirectoryHierarchy::commandGreatest(const std::string &id, std::ostream &output) const
{
    /*
     * Mehtod implements command greatest. Takes as parameters id of the starting node and std::cout object.
     * This method gets map from recursive function above and find the maximum value from this map
     *
     * */
    Directory root; // prepare variable for finding
    bool found=false; // flag if not found
    for(unsigned int i=0; i<all_struct.size(); i++) // find directory by id
    {
        if(all_struct[i].id_ == id)
        {
            root = all_struct[i];
            found = true;
            break;
        }
    }
    if(!found)
    {
        output << "Error. " << id << " not found." << std::endl;
    }
    std::map<std::string, int> hierarchy; // prepare map
    recursive_greatest(&root, hierarchy); // fill map
    int minval = root.size_; // set starting minimum value
    std::string minname = root.id_; // set starting name of the directory with the minimum value
    for(auto elem : hierarchy)
    {
        if(elem.second > minval) // find maximum
        {
            minval = elem.second;
            minname = elem.first;
        }
    }
    output << minname << " ( " << minval << " )  is the greatest subdirectory in " <<
              (minname == root.id_ ? "its" : root.id_+"'s") << " subdirectories." <<std::endl;

}

void DirectoryHierarchy::commandSmallest(const std::string &id, std::ostream &output) const
{
    /*
     * Mehtod implements command smallest. Takes as parameters id of the starting node and std::cout object.
     * This method gets map from recursive function above and find the minimum value from this map.
     * All the comments are the same as for the method "greatest".
     *
     * */
    Directory root;
    bool found = false;
    for(unsigned int i=0; i<all_struct.size(); i++)
    {
        if(all_struct[i].id_ == id)
        {
            root = all_struct[i];
            found = true;
            break;
        }
    }
    if(!found)
    {
        output << "Error. " << id << " not found." << std::endl;
    }
    std::map<std::string, int> hierarchy;
    recursive_greatest(&root, hierarchy);
    int minval = root.size_;
    std::string minname = root.id_;
    for(auto elem : hierarchy)
    {
        if(elem.second < minval)
        {
            minval = elem.second;
            minname = elem.first;
        }
    }

    output << minname << " ( " << minval << " )  is the smallest subdirectory in " <<
              (minname == root.id_ ? "its" : root.id_ + "'s")  << " subdirectories." <<std::endl;

}
