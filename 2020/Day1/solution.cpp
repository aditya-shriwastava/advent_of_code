#include<iostream>
#include<fstream>
#include<string>
#include<vector>

void ReadInput(std::vector<int>& input){
  std::ifstream input_f("input.txt", std::ios_base::in);

  std::string line;
  while(input_f>>line){
    input.emplace_back(std::stoi(line));
  }

  input_f.close();
}

bool Sum2_2020(const std::vector<int>& input, int& i, int& j){
  for(i=0; i<input.size(); i++){
    for(j=i+1; j<input.size(); j++){
      if(input.at(i) + input.at(j) == 2020){
        return true; 
      }// if(input.at(i) + input.at(j) == 2020)
    }// for(j=i; j<input.size(); j++)
  } // for(i=0; i<input.size(); i++)
  return false;
}// bool Sum2_2020


bool Sum3_2020(const std::vector<int>& input, int& i, int& j, int& k){
  for(i=0; i<input.size(); i++){
    for(j=i+1; j<input.size(); j++){
      for(k=j+1; k<input.size(); k++){
        if(input.at(i) + input.at(j) + input.at(k) == 2020){
          return true; 
        }// if(input.at(i) + input.at(j) == 2020)
      }// for(k=j; k<input.size(); k++)
    }// for(j=i; j<input.size(); j++)
  } // for(i=0; i<input.size(); i++)
  return false;
}// bool Sum3_2020

int main(){
  std::vector<int> input;
  ReadInput(input);
  
  // Solution of Part 1
  int i, j;
  if(Sum2_2020(input, i, j)){
    std::cout<<"i: "<<i<<" | "<<"input[i]: "<<input.at(i)<<std::endl;
    std::cout<<"j: "<<j<<" | "<<"input[j]: "<<input.at(j)<<std::endl;
    std::cout<<"input[i] + input[j]: "<<input.at(i) + input.at(j)<<std::endl;
    std::cout<<"input[i] x input[j]: "<<input.at(i) * input.at(j)<<std::endl;
  }else{
    std::cout<<"No Answer Found!!"<<std::endl;
  }

  std::cout<<std::endl;

  // Solution of Part 2
  int k;
  if(Sum3_2020(input, i, j, k)){
    std::cout<<"i: "<<i<<" | "<<"input[i]: "<<input.at(i)<<std::endl;
    std::cout<<"j: "<<j<<" | "<<"input[j]: "<<input.at(j)<<std::endl;
    std::cout<<"k: "<<k<<" | "<<"input[k]: "<<input.at(k)<<std::endl;
    std::cout<<"input[i] + input[j] + input[k]: "<<input.at(i) + input.at(j) + input.at(k)<<std::endl;
    std::cout<<"input[i] x input[j] x input[k]: "<<input.at(i) * input.at(j) * input.at(k)<<std::endl;
  }else{
    std::cout<<"No Answer Found!!"<<std::endl;
  }

  return 0;
 }
