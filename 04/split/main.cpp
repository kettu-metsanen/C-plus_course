#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string line, char separator, bool chois = false)
{
    std::string timeline = line;
    std::vector< std::string > result = {};
    if(chois == false){

        //std::cout << timeline.find(separator) << std::endl;
        int ind = timeline.find(separator);
        while (timeline.find(separator) != std::string::npos) {

            if(timeline.find(separator) == 0){
                result.push_back("");

                timeline.erase(0, ind+1);
                //std::cout << timeline << std::endl;
                ind = timeline.find(separator);
                //std::cout << timeline.find(separator) << std::endl;

            }
            else{
                //std::cout << timeline.substr(0, ind) << std::endl;
                result.push_back(timeline.substr(0, ind));

                timeline.erase(0, ind+1);
                //std::cout << timeline << std::endl;
                ind = timeline.find(separator);
                //std::cout << timeline.find(separator) << std::endl;
            }
        }
        result.push_back(timeline.substr(0, ind));
        return result;
    }
    if(chois == true){

        //std::cout << timeline.find(separator) << std::endl;
        int ind = timeline.find(separator);
        while (timeline.find(separator) != std::string::npos) {

            if(timeline.find(separator) == 0){

                timeline.erase(0, ind+1);
                //std::cout << timeline << std::endl;
                ind = timeline.find(separator);
                //std::cout << timeline.find(separator) << std::endl;

            }
            else{
                //std::cout << timeline.substr(0, ind) << std::endl;
                result.push_back(timeline.substr(0, ind));

                timeline.erase(0, ind+1);
                //std::cout << timeline << std::endl;
                ind = timeline.find(separator);
                //std::cout << timeline.find(separator) << std::endl;
            }
        }
        //std::cout << "I am here" << timeline[0] << std::endl;
        if(timeline[0] != ' '){
        result.push_back(timeline.substr(0, ind));
        }
        return result;
    }


return result;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
