#include "Engine/File.hpp"
#include "Engine/Exception.hpp"

#include <string>
#include <sstream>
#include <fstream>

namespace engine
{
    std::string File::ReadText(const char* file)
    {
        std::string ret;
        std::stringstream buf;
        std::ifstream fs;

        fs.open(file);

        if (fs.is_open())
        {
            buf << fs.rdbuf();
        }
        else
        {
            THROW_NOT_FOUND_EXCEPTION(file);
        }

        fs.close();

        ret = buf.str();
        return ret;
    }

    void File::WriteText(const char* file, const std::string& data)
    {
        std::ofstream fs;
        
        fs.open(file);
        if (fs.is_open())
            fs << data;
        fs.close();
    }
}
