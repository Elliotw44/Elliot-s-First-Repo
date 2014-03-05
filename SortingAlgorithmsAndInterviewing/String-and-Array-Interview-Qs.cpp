/*
 * String and Array interview Questions
 *
 *
 *  Elliot Weil
 *   */

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <math.h>
#include <assert.h>
#include "Sort.cpp"
using namespace std;

string LongestPalindrome(string s1);
void findTuples(vector<int> array);
void LongestSum(vector<int> theArray);
long StringToLong(string s);
char findUnique(string input);
string reverse(string theString);
vector<int> LargestSubProduct(vector<int> in, int l);
void LongestIncreasingNumSet(vector<int> theArray);
string TicTacToeAnaly(vector< vectors<string>> board);

int main()
{
    int uns2[] = {5,8,7,2,10,1,3,4,6,9};
    vector<int> unsort (uns2, uns2 + sizeof(uns2) / sizeof(int)); 
    int testArr[] = {5,10,-8,-8,4,11};
    vector<int> testV (testArr, testArr + sizeof(testArr) / sizeof(int));
        
    cout <<"Longest sum array: 5 10 -8 -8 4 11"<<endl;
    LongestSum(testV);

      
    int testIn[] = {4,3,2,1,0};
    vector<int> IncrNumTest (testIn, testIn + sizeof(testIn) / sizeof(int));
    LongestIncreasingNumSet(IncrNumTest);

    cout <<"Original array: 5 8 7 2 10 1 3 4 6 9"<<endl;
    cout<<endl<<endl<<"The Tuples for the list above are below."<<endl;
    findTuples(unsort);
    cout<<endl;
    //test Binary Search
    vector<int> sorted = MergeSort(unsort);
    cout<<"binary Search returned: "<<binarySearch(sorted, 5)<<endl;

    //test find largest sub product
    int grpSize = 3;
    vector<int> subProd = LargestSubProduct(testV, grpSize);
    cout<<"The largest product of group size: "<< grpSize<<endl;
    for(int i =0; i < subProd.size(); i++)
        cout<<subProd[i]<<", ";
    cout<<endl;
    

    //test string reverse
    assert(reverse("abc") == "cba");
    assert(reverse("hola") == "aloh");
    assert(reverse("12") == "21");
    assert(reverse("1") == "1");
    assert(reverse("asdfghjk") == "kjhgfdsa");

    //test longest Palindrome
    string s1 = "ababba";
    string s2 = "racecar";
    string s3 = "abcvdfgew";
    s1 =  LongestPalindrome(s1);
    s2 = LongestPalindrome(s2);
    s3 = LongestPalindrome(s3);
    cout <<s1<<" "<<s2<<" "<<s3<<endl;
    assert(s1 == "abba");
    assert(s2 == "racecar");
    assert(s3 == "w");

    //test find unique
    assert(findUnique("SBSBEfefe") == 'E');
    assert(findUnique("SSSBBSAaaAERER") == '#');
    assert(findUnique("a") == 'a');
    assert(findUnique("12332aabbcc14") == '4');
        
    //Test stringToLong
    //normal case
    string test = "39156742790";
    //letters inbetween
    string test1 = "93814asd34";
    //letters before, inbetween, and after
    string test2 = "dklj;fjl:5300sdfsfrsa1208wqegdseqwqe6sad";
    //normal negative case
    string test3 = "-23424562";
    //testing to make sure the bool first gets set properly
    string test4 ="3-243234234";
    //testing negative with letters before, inbetween, and after
    string test5 ="-asdsadsadsa342asdasd43asdsad344sadsalkjl)(*";
    //testing negative symbol midway in the string but before any number
    string test6 ="asdlkjesl;dj;sk;ldjelalj-7834-asdsf32wqwe--324-ewqeq";
    //test overload prevention
    string test7 = "12345678901234567890213456785432456786543";
    //testing overload prevention for negative numbers
    string test8 = "-12345678901234567890123";
    //testing for floats
    string test9 = "21343.324";
    long itest = StringToLong(test);
    long itest1 = StringToLong(test1);
    long itest2 = StringToLong(test2);
    long itest3 = StringToLong(test3);
    long itest4 = StringToLong(test4);
    long itest5 = StringToLong(test5);
    long itest6 = StringToLong(test6);
    long itest7 = StringToLong(test7);
    long itest8 = StringToLong(test8);
    long itest9 = StringToLong(test9);
    assert(itest == 39156742790);
    assert(itest1 == 9381434);
    assert(itest2 == 530012086);
    assert(itest3 == -23424562);
    assert(itest4 == 3243234234);
    assert(itest5 == -34243344);
    assert(itest6 == -783432324);
    assert(itest7 == 1234567890123456789);
    assert(itest8 == -1234567890123456789);
    assert(itest9 == 21343324);
       
    cout<<"all asserts passed!"<<endl;
    return 0;
}
//Return the largest sub product group of size l
//I split the vector into two sub vectors one of negatives and one of positives
//Then compare the results and decide which is the greater number
vector<int> LargestSubProduct(vector<int> in, int l){
 
  if(in.size() < l) //if the array is smaller then the group size just return the orginal array
    return in;

  vector<int> neg; //vector to hold negative numbers
  for(int i = 0; i < in.size(); i++){
    if(in[i] < 0){
      neg.push_back(in[i] * -1);
      in.erase(in.begin()+i);
    }
  }
  //sort both arrays O(n * Log(n))
  in = MergeSort(in);
  neg = MergeSort(neg);
  vector<int> RV;
  //special case where there is no positive numbers so add the 3 smallest negative numbers
  if(in.size() == 0){
    for(int k = 0; k < l; k++)
        RV.push_back(neg[k] * -1);
  }

  int i = in.size()-1;
  int j = neg.size()-1;

  while(RV.size() < l){
    if(in[i] > neg[j]){ //if the pos number is greater then push it to the final vector(RV)
      RV.push_back(in[i]);
      in.erase(in.begin() + i--);
    }
    else{
      if(l - RV.size() > 1){ //make sure there is two spots left in the final vector(RV) to possibly push two negative numbers
        if(in.size() > 1){//if there is more then 1 number left in the in vector then computer both products and compare
          int PosProd =  in[i] * in[i-1];
          int NegProd = neg[j] * neg[j-1];
          if(PosProd >= NegProd){ //if the positive number product is higher add it to the final vector(RV)
            RV.push_back(in[i]);
            in.erase(in.begin() + i--);
            RV.push_back(in[i]);
            in.erase(in.begin() + i--);
          }
          else{ //the negative number product is higher so add it to the final vector(RV)
            RV.push_back(neg[j] * -1);
            neg.erase(neg.begin() + j--);
            RV.push_back(neg[j] * -1);
            neg.erase(neg.begin() + j--);
          }
        }
        else{ //There is only one item left in the positive vector so add both negative numbers to the final vector(RV)
          RV.push_back(neg[j] * -1);
          neg.erase(neg.begin() + j--);
          RV.push_back(neg[j] * -1);
          neg.erase(neg.begin() + j--);
        }
      }
      else{ //There is only one spot left in the final vector(RV) so add the postive number
        RV.push_back(in[i]);
        in.erase(in.begin() + i--);
      }
    }      
  }

  return RV; //returning the final vector with the great product
}
  

//Code to reverse a string in place pretty simple
//Time: O(n)
string reverse(string theString){
	int length = theString.length() - 1;
	char temp;
  int i = 0;
  while(i < (length - i)){
      temp = theString[length-i];
      theString[length-i] = theString[i];
      theString[i] = temp;
      i++;
  }
    
	return theString;
}
//Take  a string full of numbers and make it a  long
//O(n) Time
long StringToLong(string s){
	//bool for checking if you have found the first number in the string
	bool first = false;
	//bool that gets set if the long is negative
	bool negative = false;
	//check if string is too long for long
	bool overloaded = false;
    int i = 0;
    long numlong = 0;
    int digitcount = 0;
    //while condition is till end of string in this case checking for null terminating symbol. could also use the size of the string
    while (s[i] != '\0') {
        // checks if the ascii value of the character is between 48 and 57 which are the ascii values of 0 through 9
        if ((int)s[i] < 58 && (int)s[i] > 47) {
            //if the characters is then append the digit on to the long;
        	if(digitcount <= 18){
        		numlong = ((numlong * 10) + ((long)s[i] - 48));
        		first = true;
        		digitcount++;
        	}
        	//If number is too large
        	else if(digitcount > 18){
				overloaded = true;
        		break;
        	}
        }
        else if( (first == false && (int)s[i] == 45 )){
        	negative = true;
        }
        //move forward in the string
        i++;
    }
    //if the number is negative return the negative value
    if (negative == true){
    	return numlong * -1;
    }
    //else return the positive
    else{
        return numlong;
    }
}
//Finds the longest continous sum  in the array.
//O(n) Time
void LongestSum(vector<int> theArray){
    int max = 0;
    int maxLen = 0;
    int maxInd = 0;
    int len = 0;
    int sum = 0;
    for(int i = 0; i < theArray.size(); i++){
        sum += theArray[i];
        len++;
        //the sum is less then zero and it is better to restart the sum and length because 0 is a greater number.
        if(sum < 0){
            sum = 0;
            len = 0;
        }
        //new max so set the variables
        if(sum > max){
            max = sum;
            maxLen = len;
            maxInd = i;
		}
    }
    cout<<"The Longest continuous sum is: ";
    for(int i = (maxInd-(maxLen-1)); i <= maxInd; i++)
  	cout<<theArray[i]<< ", ";
    cout<< " with a value of: " <<max<<endl;
}
//Finds the longest continuous increasing numbers
//O(n) Time
void LongestIncreasingNumSet(vector<int> theArray){
    int len = 1;
    int maxLen = 1;
    int maxEndIndex = 0;
    for(int i = 0; i < theArray.size()-1; i++){
      if(theArray[i] < theArray[i+1]){
          len++;
      }
      else
          len = 1;
      //new Longest increasing continous set
      if(len > maxLen){
            maxLen = len;
            maxEndIndex = i+1;//plus one because we are checking the current value of i with i+1
		  }
    }
    cout<<"The Longest continuous increasing Num set is: ";
    for(int i = 0; i < maxLen; i++)
  	  cout<<theArray[(maxEndIndex-maxLen+1) + i]<< ", "; //plus one here because Len assumes first index is 1 and not 0
    cout<<endl;
}     

string TicTacToeAnaly(vector< vectors<string>> board){
     for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           if(board[i][j] == ":x" || board[i][j] == ":o"){
              if(i == 0 && j == 0){
                  if(board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2])
                      return board[i][j]
              }
              if(i == 0){
                  if(board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2])
                      return board[i][j]
              }
              if(j == 0){
                  if(board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j])
                      return board[i][j]
              }
              if(j == 2 && i == 2){
                  if(board[i][j] == board[i-1][j-1] && board[i][j] == board[i-2][j-2])
                      return board[i][j]
              }
          }
      }
    }
    return "nil"
}


//find all the a^2 + b^2 = c^2 combinations in a given array
//O(n^2) Time
void findTuples(vector<int> array){
    //sort the array
    vector<int> sorted = MergeSort(array); // O(n Log(n))
    vector<int> sortedSq(sorted.size(), 0);
    vector<int> valuesToSearch;
        //square every value you in the sorted array and store it in a new array
        int possibleA;
        for(int i = 0; i < sorted.size(); i++){    //O(n)
            sortedSq[i] = sorted[i] * sorted[i];
        }
        //set the first possible C to the last item then work down to the 3rd spot in the list
        for(int c = sorted.size() - 1; c > 1; c--){ //O(n) * O(n) = O(n^2)
            //for each C check
            for(int b = (c-1); b > 0; b--){ //O(n)
                possibleA = sortedSq[c] - sortedSq[b];
                valuesToSearch = sortedSq;
                valuesToSearch.resize(b);
                if(binarySearch(valuesToSearch, possibleA)){  //O(Log(n))
                    //check to see if the sqrt is positive or negative
                    if(binarySearch(sorted, sqrt(possibleA))){
                        cout<< sqrt(possibleA) << "^2 + "<< sorted[b]<< "^2 = "<<sorted[c]<<"^2"<< endl;
                    }
                    else
                    {
                        cout<< sqrt(possibleA)*-1<<"^2 + "<< sorted[b]<<"^2 = "<< sorted[c]<<"^2" << endl;
                    }
                    
            }
        }
    }
}
           
//Solution for returning the longest palindrome in a string.
//Worst case:O(n^2) Best Case:O(n) Time
string LongestPalindrome(string s1){
    int lower;
    int upper;
    int LongestStart = 0;
    int LongestEnd = 0;
    for(int i =0; i< s1.length(); i++){ //O(n)
        //for odd palimdromes
        lower = i;
        upper = i;
        while(s1[upper] == s1[lower] && lower >= 0 && upper <= s1.length()){ //Best case:O(1) Worst case:O(n)
            if((upper - lower) >= (LongestEnd - LongestStart)){
                LongestEnd = upper;
                LongestStart = lower;
            }
            upper++;
            lower--;
        }
                   
        //for even palindromes
        lower = i;
        upper = i+1;
        while(s1[upper] == s1[lower] && lower >= 0 && upper <= s1.length()){ //Best case:O(1) Worst case:O(n)
            if((upper - lower) >= (LongestEnd - LongestStart)){
                LongestEnd = upper;
                LongestStart = lower;
            }
            upper++;
            lower--;
        }
    }
    string LPalin = "";
    for(int i = LongestStart; i <= LongestEnd; i++){ //O(n)
        LPalin += s1[i];
    }
    return LPalin;
}
//finds the first unique char in a string then returns it. If not unique char exist returns '#'
char findUnique(string input){
    unordered_map<char, int> CharCount;
    for(int i = 0; i < input.length(); i++){
        if(CharCount.count(input[i]) >= 1){
            unordered_map<char,int>::iterator iter = CharCount.find(input[i]);
            CharCount[input[i]] = iter->second + 1;
        }
        else{
            CharCount[input[i]] = 1;
        }
    }
    for( auto iter2 = CharCount.begin(); iter2 != CharCount.end(); iter2++){
        if(iter2->second == 1) {
            return iter2->first;
        }
    }
    
    return '#';
}

