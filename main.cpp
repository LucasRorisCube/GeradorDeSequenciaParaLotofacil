#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> allSolution;


bool isOdd(int num){
  return (num%2 != 0);
}

bool isEven(int num){
  return (num%2 == 0);
}

bool isPrime(int num){

  if(num == 1 || num == 2) return true;
  
  for(int i = 2 ; i*i <= num ; i++) if(num%i == 0) return false;
  
  return true;
}

bool isFibonacciNumber(int num){

  int fibonacciNumber = 1;
  int prevFibonacciNumber = 1;

  while(fibonacciNumber < num){
    int aux = prevFibonacciNumber;
    prevFibonacciNumber = fibonacciNumber;
    fibonacciNumber += aux;
  }
  return (num == fibonacciNumber);
}

bool isMultiple(int num, int multiple){
  return(num%multiple == 0);
}

bool isInVector(int num, vector<int>& prevNumbers){

  for(int prevNum : prevNumbers){
    if(num == prevNum) return true;
  }
  return false;
}

void printSequences(vector<int>& sequence, vector<int>& prevNumbers){

  int odd = 0;
  int even = 0;
  int prime = 0;
  int prev = 0;
  int fibonacci = 0;
  int threeMultiple = 0;
  
  for(int num : sequence){
    if(isOdd(num)) {cout << "O número " << num << " é par" << endl; odd++;}
    else{ cout << "O número " << num << " é ímpar" << endl; even++;}

    if(isPrime(num)) {cout << "O número " << num << " é primo" << endl; prime++;}

    if(isFibonacciNumber(num)) {cout << "O número " << num << " é um número da sequência fibonacci" << endl; fibonacci++;}

    if(isMultiple(num, 3)) {cout << "O número " << num << " é multiplo de 3" << endl; threeMultiple++;}

    if(isInVector(num, prevNumbers)) {cout << "O número " << num << " apareceu no concurso anterior" << endl; prev++;}

    cout << endl;
  }

  cout << "Possui " << odd << " pares, " << even << " impares, " << prime << " primos, " << fibonacci << " fibonacci, " << prev << " anteriores e " << threeMultiple << " multiplos de 3\n";
}

void printSolution(vector<int> solution){
  for(int num : solution) cout << num << ",";
  cout << endl;
}

bool isAPrevSolution(vector<int>& sequence){

  for(vector<int> solution : allSolution){

    int flag = 0;
    for(int i = 0 ; i < (int)solution.size() ; i++){
      if(!isInVector(solution[i], sequence)){
        flag = 1;
        break;
      }    
    }
    if(flag == 0) return 1;
  }
  return 0;
}
int evaluate(vector<int>& currentSequence, vector<int>& prevNumbers){

  int odd = 0;
  int even = 0;
  int prime = 0;
  int prev = 0;
  int fibonacci = 0;
  int threeMultiple = 0;
  
  for(int num : currentSequence){
    if(isOdd(num)) odd++;
    else even++;

    if(isPrime(num)) prime++;

    if(isFibonacciNumber(num)) fibonacci++;

    if(isMultiple(num, 3)) threeMultiple++;

    if(isInVector(num, prevNumbers)) prev++;
    
  }

  if(odd > 8) return 0;
  if(even > 7) return 0;
  if(prev > 9) return 0;
  if(fibonacci > 5) return 0;
  if(prime > 5) return 0;
  if(threeMultiple > 5) return 0;

  if(odd == 8 && even == 7 && prev == 9 && fibonacci == 5 && prime == 5 && threeMultiple == 5){
    //if(!isAPrevSolution(currentSequence)){
      allSolution.push_back(currentSequence);
      printSolution(currentSequence);
    //}
    
    //printSequences(currentSequence, prevNumbers);
    return 1;
    }
  
  return 2;
}



int createSequence(vector<int>& currentSequence, vector<int>& prevNumbers){

  if((int)currentSequence.size() >= 16) return 2;
  
  for(int i = 1 ; i <= 25 ; i++){
    if(isInVector(i, currentSequence)) continue;
    
    vector<int> aux = currentSequence;
    aux.push_back(i);
    int ret = evaluate(aux, prevNumbers);
    if(ret == 1) return 1;
    if(ret == 2){
      int ret2 = createSequence(aux, prevNumbers);
      if(ret2 == 1) return 1;
      if(ret2 == 2) return 0;
    }
  }
  return 0;
}

int main() {

  vector<int> possibleNumbers {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
  vector<int> prevNumbers {1,2,6,7,9,10,12,13,17,18,20,21,23,24,25};

  vector<int> sequence;
  createSequence(sequence, prevNumbers);

  //vector<int> sequence {1,2,3,4,5,6,9,10,20,25,21,22,15,16,17};

  printSequences(allSolution[0], prevNumbers);
  
  
}
/*
1,2,3,4,5,6,9,10,20,25,21,19,22,15,16,
1,2,3,4,5,6,9,10,20,25,21,19,22,16,15,
1,2,3,4,5,6,9,10,20,25,21,22,15,16,17,
1,2,3,4,5,6,9,10,20,25,21,22,15,16,19,
1,2,3,4,5,6,9,10,20,25,21,22,15,16,23,
1,2,3,4,5,6,9,10,20,25,21,22,15,17,16,
1,2,3,4,5,6,9,10,20,25,21,22,15,19,16,
1,2,3,4,5,6,9,10,20,25,21,22,15,23,16,
1,2,3,4,5,6,9,10,20,25,21,22,16,15,17,
1,2,3,4,5,6,9,10,20,25,21,22,16,15,19,
1,2,3,4,5,6,9,10,20,25,21,22,16,15,23,
*/