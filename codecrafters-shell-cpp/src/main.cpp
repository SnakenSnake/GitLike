#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
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
  else
  std::cout<<user_input<<": command not found"<<"\n";
  }
  while(true);
}
