#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

struct Password{
  std::string password;
  struct PasswordPolicy{
    char ch;
    int min_occurance;
    int max_occurance;
  } password_policy;
  
  bool IsValid(){
    int no_of_ch = 0;
    for(auto ch : password){
      if(ch == password_policy.ch){
        no_of_ch++;
      }
    }
    if((no_of_ch >= password_policy.min_occurance) && (no_of_ch <= password_policy.max_occurance)){
      return true;
    }else{
      return false;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Password& password){
    os<<"Password: "<<password.password<<", "
      <<"PasswordPolicy: "<<password.password_policy.ch<<" <"
      <<password.password_policy.min_occurance<<", "
      <<password.password_policy.max_occurance<<">";
  }
};

Password ParseLine(std::string line){
  Password password;

  std::stringstream line_stream(line);
  std::string range, ch, password_string;
  line_stream>>range;
  line_stream>>ch;
  line_stream>>password_string;

  password.password = password_string;
  password.password_policy.ch = ch[0];
  password.password_policy.min_occurance = std::stoi( range.substr(0, range.find("-")) );
  password.password_policy.max_occurance = std::stoi( range.substr(range.find("-") +1) );

  return password;
}

using Passwords = std::vector<Password>;
Passwords ParseInput(){
  Passwords passwords;
  std::ifstream input_f("input.txt", std::ios_base::in);
  std::string line;
  while(std::getline(input_f, line)){
    passwords.emplace_back( ParseLine(line) );
  }
  input_f.close();
  return passwords;
}

int main(){
  auto passwords = ParseInput();
  int no_of_valid_password = 0;
  for(auto password : passwords){
    if(password.IsValid()){
      no_of_valid_password++;
    }
  }
  std::cout<<"Number of Valid Password: "<< no_of_valid_password <<std::endl;
  return 0;
}
