/*
 * Names: Ramiz Alhaddad, Sanshit Sagar
 * Date: May 4th 2017
 * Description: This file just calls the c++ implementation of the 
 * binary search tree, and encases it in a wrapper. 
 * PA2
 */

#include <iostream>
#include "DictionaryHashtable.h" 
#include "DictionaryBST.h"
#include "DictionaryTrie.h"
#include "util.h"
#include <fstream>
#include <istream>
/*
 * FIRST HASH FUNCTION
 * Parameters: The word to be hashed
 * and the table size
 * Returns: HashValue for the word
 */ 
int hash1(std::string word, int size){
	unsigned long sum;
	for(size_t i=0; i < word.length();i++){
		sum += (int) word[i];
	}
	return sum%size;
}

/*
 * SECOND HASH FUNCTION
 * Parameters: The word to be hashed
 * and the table size
 * Returns: HashVAlue for the word
 */ 
int hash2(std::string word, int size) {
	int seed = 131; 
	unsigned long hash = 0; 
	for(size_t i =0; i< word.length(); i++) 
	{
		hash = (hash*seed) + word[i]; 
	}
	return hash%size; 
} 
int iteration = 0; 

/*This is the main driver for this program. 
 * It takes in two arguments from the command line
 * The dictionary, and the table size. It then simulates 
 * a hashtable for both the hashfunctions and prints the
 * number of collisions and the number of slots that have 
 * those number of collisions. It then prints out some 
 * other statisitics. It will always return 0. 
 */ 

int main(int argc, char *argv[]){
	while(iteration<2) {
		/*
		 * TESTING THE TWO HASH FUNCTIONS
		 std::vector<int> hashtable1(5); 
		 int hashVal1 = hash2("Bob", 5); 
		 hashtable1[hashVal1]++; 
		 int hashVal2 = hash2("aaa", 5); 
		 hashtable1[hashVal2]++; 	
		 for(int a =0; a<hashtable1.size(); a++) 
		 { 
		 std::cout << a << " " << hashtable1[a] << std::endl; 
		 }  
		 */

		/*
		 * READING FROM COMMAND LINE
		 */ 
		std::string dictfile = std::string(argv[1]);
		int num_words =std::atoi(argv[2]);
		int size_table = 2*num_words;

		//Load words from the dictionary
		std::ifstream file;
		file.open(dictfile);
		if(file.fail()) { return -1; }
		file.clear();
		file.seekg(0);

		//Create the vector that holds the words
		std::vector<std::string> vector;
		//Create the simulated hashtable 
		std::vector<int> hashtable(size_table);  
		//Load words from the dictionary into the vector
		Utils::load_vector(vector,file, num_words);

		int slotsperhit = 0; 
		int mostCollisions = 0; 
		//Simulate the hashtable
		for(int i=0; i<num_words; i++) 
		{
			if(iteration==0) {
				int hashValue = hash1(vector[i], size_table);
				hashtable[hashValue]++; 
			}
			else {
				int hashValue = hash2(vector[i], size_table); 
				hashtable[hashValue]++; 
			}
		}
		//The max number of steps that would be needed to find a word 
		//in a hashtable
		for(size_t i=0; i<hashtable.size(); i++)
		{
			if(hashtable[i] > mostCollisions) {
				mostCollisions = hashtable[i]; 
			}	
		}

		std::cout << "Printing the statistics for hashFunction"
		<< iteration
		<< " with hash table size " << size_table << std::endl; 
		std::cout << "#hits" << "\t" <<   "#slots receiving the #hits" 
		<< std::endl; 
		double numerator = 0; 
		double totalHits = 0; 
		//The number of slots tgat recieved each number of hits
		for( int j=0; j<mostCollisions; j++) 
		{
			for(size_t k=0; k<hashtable.size(); k++) 
			{
				if(j==hashtable[k])
				{
					slotsperhit++; 
				}	
			}
			std::cout << j << "\t" << slotsperhit << std::endl; 
			totalHits += slotsperhit; 
			numerator += (slotsperhit * j); 
			slotsperhit = 0; 
		}

		std::cout << 
	"The average number of steps that would be needed to find a word is "
			<< (double) numerator/totalHits 
			<< std::endl; 

		std::cout << 
	"The worst case steps that would be needed to find a word is "
			<< (mostCollisions-1)
			<< std::endl; 

		iteration++; 
	}

	return 0; 
}


