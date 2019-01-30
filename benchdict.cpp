/*
 * Names: Ramiz Alhaddad, Sanshit Sagar
 * Date: May 4th 2017
 * Description: This file benchmarks the bst, HT and Trie 
 * PA2
 */

#include "DictionaryHashtable.h" 
#include "DictionaryBST.h"
#include "DictionaryTrie.h"
#include "util.h"
#include <fstream> 
#include <iostream>

/*This is the main driver for the file. It 
 * takes the specified command line arguments, 
 * loads from a dictionary with a minimum step 
 * size. Prints the run time for each of the data 
 * structures with the initial diction size, as well 
 * as for the incremental sizes. 
 */

int main(int argc, char *argv[]){

	int min_size = std::atoi(argv[1]);
	int step_size =std::atoi(argv[2]);
	int num_iterations = std::atoi(argv[3]);
	std::string dictfile = std::string(argv[4]);
	std::cout << "benchmarking DictionaryTrie" << std::endl;
	double totalTimeTrie = 0;
	for(int i =0; i< num_iterations; i++){
                
		DictionaryTrie *dt = new DictionaryTrie(); 
		std::ifstream file;
		std::vector<std::string> vectTrie; 
		file.open(dictfile);
		if(file.fail()) { return -1; } 
		file.clear();
		file.seekg(0);
                Utils::load_dict(*dt,file, (min_size));
		Utils::load_vector(vectTrie, file, 100); 
		Timer timeTrie;
		double durationTrie = 0;
		timeTrie.begin_timer();
		for(size_t j =0 ; j< vectTrie.size(); j++){
			dt->find(vectTrie[j]);
		}
		durationTrie = timeTrie.end_timer();  
		durationTrie =  durationTrie;
		totalTimeTrie += durationTrie; 
                min_size = min_size +step_size;
                std::cout<< min_size<< "\t"<<totalTimeTrie << std::endl;
                file.close();
                delete dt; 
	}
        
	std::cout << "benchmarking DictionaryHashTable" << std::endl;
        double totalTimeHT = 0;
       // for(int i=0; i < 5; i++){
        for(int i =0; i< num_iterations; i++){

                DictionaryHashtable *ht = new DictionaryHashtable();
                std::ifstream file;
                std::vector<std::string> vectHT;
                file.open(dictfile);
                if(file.fail()) { return -1; } 
                file.clear();  
                file.seekg(0); 
                Utils::load_dict(*ht,file,min_size);
                Utils::load_vector(vectHT, file, 100);
                Timer timeHT;
                double durationHT = 0; 
                timeHT.begin_timer();
                for(size_t j =0 ; j< vectHT.size(); j++){
                        ht->find(vectHT[j]);
                }
                
                durationHT = timeHT.end_timer();  
                durationHT =  durationHT;
                totalTimeHT += durationHT; 
                min_size = min_size + step_size;  
	        std::cout <<min_size<<"\t"<<totalTimeHT<< std::endl; 
                file.close(); 
                delete ht;
        }
        
	std::cout << "benchmarking DictionaryBST" << std::endl;
        double totalTimeBST = 0;
        for(int i =0; i< num_iterations; i++){

                DictionaryBST *bst = new DictionaryBST();
                std::ifstream file;
                std::vector<std::string> vectBST;
                file.open(dictfile);
                if(file.fail()) { return -1; }
                file.clear();
                file.seekg(0);
                Utils::load_dict(*bst,file,min_size);
                Utils::load_vector(vectBST, file, 100);
                Timer timeBST;
                double durationBST = 0;
                timeBST.begin_timer();
                for(size_t j =0 ; j< vectBST.size(); j++){
                       bst->find(vectBST[j]);
                }
                durationBST = timeBST.end_timer();
                durationBST =  durationBST;
                totalTimeBST += durationBST;
                min_size = min_size + step_size;
                std::cout<<min_size<<"\t"<<totalTimeBST<< std::endl;	
                file.close();
                delete bst;
        }
	return 0; 
}
