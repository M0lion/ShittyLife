
#include <fstream>

char* get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    in.seekg(0, std::ios::beg);

    char *buffer = new char[size + 1];
    buffer[size] = 0;

    in.read(buffer, size);
    in.close();
    return(buffer);
  }
  throw("Couldn't open file: " + (std::string)filename);
}