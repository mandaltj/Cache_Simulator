#include <iostream>	
#include <string>		//For stoi(), stoull()
#include <math.h>		//For  log2()
#include <fstream>		//For File I/O
#include <vector>
#include <iomanip>
using namespace std;


//=================================================================================================================================
//==================================****   Important Structures for Cache functionality   ****=====================================
//=================================================================================================================================
struct block_struct
{
	//Valid bit to determine if the block has a valid content or not
	int valid_bit;
	//Tag for the corresponding address whose data is stored
	unsigned long long int tag_bits;
	//Increment this everytime a block is accessed
	unsigned long long int LRU_tracking;
};

struct cache_stats_struct{
	double number_of_misses 		;
	double number_of_mem_access		;
	double number_of_read_misses 	;
	double number_of_read_access	;
	double number_of_write_misses 	;
	double number_of_write_access	;
};

struct address_in{
	char repl_in;
	string address;
	
	unsigned long long address_hex;
	unsigned long long int addr_tag; 
	int addr_index;
	
};

//=================================================================================================================================
//===============================================****   Debug Functions   ****=====================================================
//=================================================================================================================================
//Simple function to print an array
void print_array(int arr[], int size){
	for (int i=0; i<size; i++){
		cout<<i<<": "<<arr[i]<<"\n";
	}
}

//Debug function to print Cache to a Text file
void display_cache(vector<vector<block_struct>> &cache, int set_size, int assoc){
	ofstream outFile;
	outFile.open("Cache_display.txt");
	
	for (int i=0; i<set_size; i++){
		outFile<<"Set"<<i<<": ";
		for (int j=0; j<assoc; j++){
			outFile<<"["<<cache[i][j].valid_bit<<", "<<cache[i][j].LRU_tracking<<", "<<cache[i][j].tag_bits<<"] ";
		}
		outFile<<"\n";
	}
	outFile.close();
}

//Function to display information regarding the Cache
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

//=================================================================================================================================
//=====****   Func to extract Address parameters from SPEC trace file(Single Line -> Single Addr Param)   ****=====================
//=================================================================================================================================

void extract_cache_param(address_in &input_address, int index_bit_size, int block_offset_bit_size){
	//Right shift address_hex by block offset bits and get rid of them
	//We don't need to look at block offset bits
	input_address.address_hex = input_address.address_hex >> block_offset_bit_size;
	//cout << "address_hex>>block_offset: "<<address_hex<<"\n";
	
	//If index_bit_size=5; 'AND' address_hex with '11111'
	unsigned long long int index_mask = pow(2, index_bit_size)-1;
	//cout<<"Index_mask: "<<index_mask<<"\n";
	input_address.addr_index = input_address.address_hex & index_mask;
	
	//Shift the address further by index bits to get the residual tag_bits
	input_address.addr_tag = input_address.address_hex >> index_bit_size;
}

//=================================================================================================================================
//======================================****  LRU Replacement Policy Function   ****===============================================
//=================================================================================================================================

void LRU_replacement(vector<vector<block_struct>> &cache, vector<int> &set_full, int assoc, int set_size, address_in &input_address,
					cache_stats_struct &cache_struct){
	
	//Update the LRU_tracking by +1 for all the elements that are valid in a set
	//This way, for every access in a set, the elements which are not accessed keep getting old
	//and then they will be replaced based in LRU policy
	for (int i=0; i<assoc; i++){
		if (cache[input_address.addr_index][i].valid_bit == 1){
			cache[input_address.addr_index][i].LRU_tracking += 1;
		}
	}
	
	
	
	int Cache_Hit = 0;
	//Cache Checking in case of Read
	if(input_address.repl_in=='r' || input_address.repl_in == 'w'){
		cache_struct.number_of_mem_access++;
		if(input_address.repl_in =='r'){
			cache_struct.number_of_read_access++;	
		} else if (input_address.repl_in == 'w'){
			cache_struct.number_of_write_access++;
		}
		
		//======================================================
		//Check for a Cache Hit in a Set
		//======================================================
		for (int i=0; i<assoc; i++){
			if (cache[input_address.addr_index][i].valid_bit == 1 && cache[input_address.addr_index][i].tag_bits == input_address.addr_tag){
				//cout<<"Cache Hit Way Number: "<< i <<"\n";
				Cache_Hit = 1;	
				cache[input_address.addr_index][i].LRU_tracking = 0;
				break;
			}
		}	
		
		//======================================================
		//Functionality for Cache Miss
		//======================================================
		if (Cache_Hit==0){
			
			cache_struct.number_of_misses++;
			if(input_address.repl_in =='r'){
				cache_struct.number_of_read_misses++;	
			} else if (input_address.repl_in == 'w'){
				cache_struct.number_of_write_misses++;
			}
			
			//======================================================
			//if set is not full, find an empty location and fill it
			//======================================================
			if (set_full[input_address.addr_index] < assoc){
				for (int i=0; i<assoc; i++){
					if (cache[input_address.addr_index][i].valid_bit == 0){
						cache[input_address.addr_index][i].valid_bit 	= 1;
						cache[input_address.addr_index][i].tag_bits  	= input_address.addr_tag;
						cache[input_address.addr_index][i].LRU_tracking = 0;
						break;
					}
				}	
				set_full[input_address.addr_index]++;
			} 
			
			//======================================================
			//if set is full then replace with LRU policy
			//======================================================			
			else{
				unsigned long long int temp = cache[input_address.addr_index][0].LRU_tracking;
				int temp_index = 0;
				for (int i=1; i<assoc; i++){
					if(cache[input_address.addr_index][i].LRU_tracking>temp){
						temp 		= cache[input_address.addr_index][i].LRU_tracking; 	
						temp_index 	= i; 	
					}
				}
				cache[input_address.addr_index][temp_index].valid_bit 		= 1;
                cache[input_address.addr_index][temp_index].tag_bits  		= input_address.addr_tag;
                cache[input_address.addr_index][temp_index].LRU_tracking	= 0;
			}
			
		}
		
	} 
	//Neither of Read or Write command
	else{
		cerr<<"Invalid command from File"<<"\n";
	}
	
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
	
	
	//display_cache_info(nk, assoc, blocksize, set_size, repl, tag_bit_size, index_bit_size, block_offset_bit_size);
	
	
	//==================================================================
	//Cache generated using std::vector. Thank God for STL!!!
	//==================================================================
	vector<vector<block_struct>> cache(set_size, vector<block_struct>(assoc));
	//display_cache(cache, set_size, assoc);
	
	//==================================================================
	//Cache Statistics Structure generation
	//==================================================================
	cache_stats_struct cache_statistics = {0};
	
	
	//==================================================================
	//This is a vector where each element corresponds to a set in cache. Each element tracks if the set is full of elements or not 
	//This needs to be initialized outside the function that updates Cache(Ex: LRU_replacement)
	//Then pass it to the function so that it can be updated along with the cache
	//==================================================================
	vector<int> set_full(set_size);	
	
	
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
	
	//================================================
	//Define the input address structure 
	//================================================
	address_in input_address;
	
	
	while(inFile>>input_address.repl_in>>input_address.address){
		
		input_address.address_hex = stoull(input_address.address, nullptr, 16);	//Convert the input address character in hex to integer		
		
		//============================================================================
		//Extract Address Tag, Index from the Address Input
		//============================================================================
		extract_cache_param(input_address, index_bit_size, block_offset_bit_size);
		//cout<<"Address Index: "<<input_address.addr_index<<"\n";
		//cout<<"Address Tag: "<<input_address.addr_tag<<"\n";

		//============================================================================
        //Call Cache Update/Replacement Function for each Address Input
        //============================================================================
		LRU_replacement(cache, set_full, assoc, set_size, input_address, cache_statistics);
		
	}
	
	//display_cache(cache, set_size, assoc);
	
	double total_miss_percent 		= ((cache_statistics.number_of_misses/cache_statistics.number_of_mem_access)*100);
	double total_read_miss_percent 	= ((cache_statistics.number_of_read_misses/cache_statistics.number_of_read_access)*100);
	double total_write_miss_percent = ((cache_statistics.number_of_write_misses/cache_statistics.number_of_write_access)*100);
	
	cout<<cache_statistics.number_of_misses<<" "<<fixed<<setprecision(6)<<total_miss_percent<<"% "<<setprecision(0);
	cout<<cache_statistics.number_of_read_misses<<" "<<fixed<<setprecision(6)<<total_read_miss_percent<<"% "<<setprecision(0);
	cout<<cache_statistics.number_of_write_misses<<" "<<fixed<<setprecision(6)<<total_write_miss_percent<<"%"<<setprecision(0)<<"\n";
	
	//ofstream outFile;
	//outFile.open("SpecBenchmark_cachetest.txt");
	//outFile<<argv[1]<<"			"<<number_of_misses<<" "<<total_miss_percent<<"% "<<number_of_read_misses<<" "<<total_read_miss_percent<<" "<<number_of_write_misses<<" "<<total_write_miss_percent<<"\n";	
	//outFile.close();
	
	return 0;
}