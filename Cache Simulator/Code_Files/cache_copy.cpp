#include <iostream>	
#include <string>		//For stoi(), stoull()
#include <math.h>		//For  log2()
#include <fstream>		//For File I/O
#include <vector>
#include <iomanip>
using namespace std;

void print_array(int arr[], int size){
	for (int i=0; i<size; i++){
		cout<<i<<": "<<arr[i]<<"\n";
	}
}

struct block_struct
{
	//Valid bit to determine if the block has a valid content or not
	int valid_bit;
	//Tag for the corresponding address whose data is stored
	unsigned long long int tag_bits;
	//Increment this everytime a block is accessed
	unsigned long long int LRU_tracking;
};

void display_cache(vector<vector<block_struct>> &cache, int set_size, int assoc){
	ofstream outFile;
	outFile.open("Cache_copy.txt");
	
	for (int i=0; i<set_size; i++){
		outFile<<"Set"<<i<<": ";
		for (int j=0; j<assoc; j++){
			outFile<<"["<<cache[i][j].valid_bit<<", "<<cache[i][j].LRU_tracking<<", "<<cache[i][j].tag_bits<<"] ";
		}
		outFile<<"\n";
	}
	
	outFile.close();
}


void extract_cache_param(unsigned long long int *addr_tag, int *addr_index, unsigned long long int address_hex, int index_bit_size, int block_offset_bit_size){
	//Right shift address_hex by block offset bits and get rid of them
	//We don't need to look at block offset bits
	address_hex = address_hex >> block_offset_bit_size;
	//cout << "address_hex>>block_offset: "<<address_hex<<"\n";
	
	//If index_bit_size=5; 'AND' address_hex with '11111'
	unsigned long long int index_mask = pow(2, index_bit_size)-1;
	//cout<<"Index_mask: "<<index_mask<<"\n";
	*addr_index = address_hex & index_mask;
	
	//Shift the address further by index bits to get the residual tag_bits
	*addr_tag = address_hex >> index_bit_size;
}

void display_cache_info(int nk, int assoc, int blocksize, int set_size, int repl, int tag_bit_size, int index_bit_size, int block_offset_bit_size){
	cout<<"========================================"<<"\n";
	cout<<"Cache Size: "<<nk<<"KB\n";
	cout<<assoc <<"-way Set Associative"<<"\n";
	cout<<"Block Size: "<<blocksize<<"B\n";
	cout<<"Number of blocks in a way: "<<set_size<<"\n";
	cout<<"Cache Replacement Policy: "<<repl<<"\n";
	cout<<"Tag bits: "<<tag_bit_size<<" Index bits: "<<index_bit_size<<" Offset bits: "<<block_offset_bit_size<<"\n\n";
	
	cout<<"========================================"<<"\n";
}


int main(int argc, char *argv[]){
	int nk = stoi(argv[2],nullptr,10);			//Cache size in KB
	int assoc = stoi(argv[3],nullptr,10);		//Set associativity of Cache = Number of ways = Number of blocks in a Set
	int blocksize = stoi(argv[4],nullptr,10);	//Blocksize of Cache in Bytes
	char repl = *argv[5];						//Cache Replacement policy
	
	
	int set_size = ((nk/assoc)*1024)/blocksize;	//Number of blocks in a way = Index bits
	int index_bit_size = log2(set_size); 
	int block_offset_bit_size = log2(blocksize);
	int tag_bit_size = (64-index_bit_size-block_offset_bit_size); 
	
	double number_of_misses 		= 0;
	double number_of_mem_access		= 0;
	double number_of_read_misses 	= 0;
	double number_of_read_access	= 0;
	double number_of_write_misses 	= 0;
	double number_of_write_access	= 0;
	
	//display_cache_info(nk, assoc, blocksize, set_size, repl, tag_bit_size, index_bit_size, block_offset_bit_size);
	
	//Cache creating using std::vector. Thank God!!!
	vector<vector<block_struct>> cache(set_size, vector<block_struct>(assoc));
	//display_cache(cache, set_size, assoc);
	
		
	//This is an array where each element corresponds to a set in cache
	//Each element tracks if the set is full of elements or not
	int set_full[set_size] = {0};
	
	//===============================================================================================================================
	//**********************************    FIle Read and Cache Hit/Miss Processing    **********************************************
	//===============================================================================================================================
	
	ifstream inFile;					
	inFile.open(argv[1]);
	//Check for error
	if(inFile.fail()){
		cerr<<"Error Opening file"<<"\n";
		exit(1);
	}
	
	//File input variables
	char repl_in;
	string address;
	
	while(inFile>>repl_in>>address){
		
		unsigned long long address_hex = stoull(address, nullptr, 16);	//Convert the input address character in hex to integer		
		unsigned long long int addr_tag; 
		int addr_index;
		
		extract_cache_param(&addr_tag, &addr_index, address_hex, index_bit_size, block_offset_bit_size);
		//cout<<"Address Index: "<<addr_index<<"\n";
		//cout<<"Address Tag: "<<addr_tag<<"\n";
		//===============================================================================================================================
		//===============================================================================================================================
		
		//Update the LRU_tracking by +1 for all the elements that are valid in a set
		//This way, for every access in a set, the elements which are not accessed keep getting old
		//and then they will be replaced based in LRU policy
		//cout<<"Set "<<addr_index<<": \n";
		for (int i=0; i<assoc; i++){
			if (cache[addr_index][i].valid_bit == 1){
				cache[addr_index][i].LRU_tracking += 1;
			}
			//cout<<"["<<cache[addr_index][i].valid_bit<<", "<<cache[addr_index][i].LRU_tracking<<", "<<cache[addr_index][i].tag_bits<<"]\n";
		}
		
		
		
		int Cache_Hit = 0;
		//Cache Checking in case of Read
		if(repl_in=='r' || repl_in == 'w'){
			number_of_mem_access++;
			if(repl_in =='r'){
				number_of_read_access++;	
			} else if (repl_in == 'w'){
				number_of_write_access++;
			}
			
			//Check for a Cache Hit in a Set
			for (int i=0; i<assoc; i++){
				if (cache[addr_index][i].valid_bit == 1 && cache[addr_index][i].tag_bits == addr_tag){
					//cout<<"Cache Hit Way Number: "<< i <<"\n";
					Cache_Hit = 1;	
					cache[addr_index][i].LRU_tracking = 0;
					break;
				}
			}	
			
			if (Cache_Hit==0){
				number_of_misses++;
				if(repl_in =='r'){
					number_of_read_misses++;	
				} else if (repl_in == 'w'){
					number_of_write_misses++;
				}
				 
				//if set is not full, find an empty location and fill it
				if (set_full[addr_index] < assoc){
					for (int i=0; i<assoc; i++){
						if (cache[addr_index][i].valid_bit == 0){
							cache[addr_index][i].valid_bit 		= 1;
							cache[addr_index][i].tag_bits  		= addr_tag;
							cache[addr_index][i].LRU_tracking   = 0;
							//cout<<"Addition location in set: "<<i<<"\n";
							break;
						}
					}	
					set_full[addr_index]++;
				} 
				//if set is full then replace the LRU
				else{
					unsigned long long int temp = cache[addr_index][0].LRU_tracking;
					int temp_index = 0;
					for (int i=1; i<assoc; i++){
						if(cache[addr_index][i].LRU_tracking>temp){
							temp 		= cache[addr_index][i].LRU_tracking; 	
							temp_index 	= i; 	
						}
					}
					cache[addr_index][temp_index].valid_bit 		= 1;
                    cache[addr_index][temp_index].tag_bits  		= addr_tag;
                    cache[addr_index][temp_index].LRU_tracking      = 0;
				}
			}
			
		} 
		//Neither of Read or Write command
		else{
			cerr<<"Invalid command from File"<<"\n";
		}
	}
	display_cache(cache, set_size, assoc);
	
	double total_miss_percent 		= ((number_of_misses/number_of_mem_access)*100);
	double total_read_miss_percent 	= ((number_of_read_misses/number_of_read_access)*100);
	double total_write_miss_percent = ((number_of_write_misses/number_of_write_access)*100);
	
	cout<<number_of_misses<<" "<<fixed<<setprecision(6)<<total_miss_percent<<"% "<<setprecision(0);
	cout<<number_of_read_misses<<" "<<fixed<<setprecision(6)<<total_read_miss_percent<<"% "<<setprecision(0);
	cout<<number_of_write_misses<<" "<<fixed<<setprecision(6)<<total_write_miss_percent<<"%"<<setprecision(0)<<"\n";
	
	//print_array(set_full, set_size);
	
	ofstream outFile;
	outFile.open("SpecBenchmark_cachetest.txt");
	outFile<<argv[1]<<"			"<<number_of_misses<<" "<<total_miss_percent<<"% "<<number_of_read_misses<<" "<<total_read_miss_percent<<" "<<number_of_write_misses<<" "<<total_write_miss_percent<<"\n";	
	outFile.close();
	
	return 0;
}

