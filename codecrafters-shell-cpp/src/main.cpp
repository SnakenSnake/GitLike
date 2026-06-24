#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#ifdef _WIN32 // Identifies if os is Windows
    #include <io.h>
#else // If not Windows then os is Linux
    #include <unistd.h>
#endif
int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  std::vector<std::string> builtin;
  builtin.push_back("exit");
  builtin.push_back("echo");
  builtin.push_back("type");
  do
  {
  std::cout << "$ ";
  std::string user_input;
  std::getline(std::cin,user_input);
  if(user_input=="exit")
  {
    break;
  }
  else if(user_input.substr(0,5)=="echo ")
  {
    std::cout<<user_input.substr(5)<<'\n';
  }
  else if(user_input.substr(0,5)=="type ")
  {
    bool type_found=std::find(builtin.begin(),builtin.end(),user_input.substr(5))!=builtin.end();
    if(type_found)
        std::cout<<user_input.substr(5)<<" "<<"is a shell builtin"<<'\n';
    else 
    {
      std::string path=getenv("PATH");
      std::istringstream ss(path);
      std::string dir;
      #ifdef _WIN32
      while(getline(ss,dir,';'))
      {
        std::string full_path=dir+"/"+user_input.substr(5);
        if(!_access(full_path.c_str(),0))
        {
          std::cout<<user_input.substr(5)<<" "<<"is "<<full_path<<'\n';
          type_found=true;
          break;
        }
      }
      #else
      while(getline(ss,dir,':'))
      {
        std::string full_path=dir+"/"+user_input.substr(5);
        if(!access(full_path.c_str(),X_OK))
        {
          std::cout<<user_input.substr(5)<<" "<<"is "<<full_path<<'\n';
          type_found=true;
          break;
        }
      }
      #endif
    }
    if(!type_found)
      std::cout<<user_input.substr(5)<<": not found"<<"\n";
  }
  else
  std::cout<<user_input<<": command not found"<<"\n";
  }
  while(true);
}
