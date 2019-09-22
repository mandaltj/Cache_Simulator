#include <iostream>	
#include <string>		//For stoi(), stoull()
#include <math.h>		//For  log2()
#include <fstream>		//For File I/O
#include <vector>
#include <iomanip>
#include <time.h>
#include <queue>
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

//This is a Binary Tree Node structre. The node contains a data value, way selection and two pointers.
//One pointer points to a Left Binary Tree Node and the other to a Right Binary Tree Node.
struct binary_tree_node{
	int node_val;
	int way_sel;
	struct binary_tree_node *left;
	struct binary_tree_node *right;
};


//Function to create a new Node
//This is a function of type "binary_tree_node". It returns a pointer to a newly created binary tree node.
//"binary_tree_node*" - This basically means that we are creating a pointer to a Binary Tree Node
binary_tree_node* binary_newNode(int data, int way_sel){
	//Declaring a pointer to a newly created "binary_tree_node"(<- data type structure binary_tree_node)
	binary_tree_node* node = new binary_tree_node();
	//Since "node" is a pointer, we have to use '->' notation.
	node->node_val = data;
	node->way_sel = way_sel;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

//Function to link a binary tree structure for a particular set
binary_tree_node* link_binary_tree_to_SET(binary_tree_node* root, int start, int end){
	
	int mid = (start+end+1)/2;
	
	if(start<end){	
		binary_tree_node* temp = binary_newNode(0, 0);
		root = temp;
		
		//insert left child
		root->left 	= link_binary_tree_to_SET(root->left, start, mid-1);
		//insert right child
		root->right = link_binary_tree_to_SET(root->right, mid, end);
	}
	else if (start==end)
	{
		binary_tree_node* temp = binary_newNode(0, 0);
		root = temp;
		
		//This is leaf node. Assign way index
		root->way_sel = start;	
	}	
	return root;
}

void binary_tree_update(binary_tree_node* root, int way_update_index, int start, int end){
	
	int mid = (start+end+1)/2;
	
	if(start<end){
		if(way_update_index>= mid){	
			//cout<<"going right\n";
			root->node_val=1;
			
			//traverse right
			binary_tree_update(root->right, way_update_index, mid, end);
		}
		else
		{
			//cout<<"going left\n";	
			root->node_val=0;	
			
			//traverse left
			binary_tree_update(root->left, way_update_index, start, mid-1);
		}		
	}
	return;
		
}

int TPLRU_replacement(binary_tree_node* root, int start, int end){
	
	int mid = (start+end+1)/2;
	
	if(start<end){
		if(root->node_val==0){
			//cout<<"Should Go right\n";
			int way_replacement_index = TPLRU_replacement(root->right, start, mid-1);		
			return way_replacement_index; 
		}
		else{
			//cout<<"Should Go left\n";
			int way_replacement_index = TPLRU_replacement(root->left, mid, end);
			return way_replacement_index;
		}
	}
	//This line will only execute on leaf node when start==end
	//For all other nodes the return call inside if-else will execute
	return root->way_sel;
}

//=================================================================================================================================
//===============================================****   Debug Functions   ****=====================================================
//=================================================================================================================================
//Simple function to print an array
void print_array(int arr[], int size){
	for (int i=0; i<size; i++){
		cout<<i<<": "<<arr[i]<<"\n";
	}
}

// Function to print tree nodes in InOrder fashion 
void printLevelOrder(binary_tree_node *root) 
{ 
    // Base Case 
    if (root == NULL)  return; 
  
    // Create an empty queue for level order tarversal 
    queue<binary_tree_node *> q; 
  
    // Enqueue Root and initialize height 
    q.push(root); 
  
    while (q.empty() == false) 
    { 
        // Print front of queue and remove it from queue 
        binary_tree_node *node = q.front(); 
        if (node->left==NULL && node->right==NULL){
			cout << node->way_sel << " ";
		}
		else{
			cout << node->node_val << " "; 
		}
        q.pop(); 
  
        /* Enqueue left child */
        if (node->left != NULL) 
            q.push(node->left); 
  
        /*Enqueue right child */
        if (node->right != NULL) 
            q.push(node->right); 
    } 
} 

//Debug function to print Cache to a Text file
void display_cache(vector<vector<block_struct>> &cache, int set_size, int assoc){
	ofstream outFile;
	outFile.open("Results/Cache_display.txt");
	
	for (int i=0; i<set_size; i++){
		outFile<<"Set"<<i<<": ";
		for (int j=0; j<assoc; j++){
			outFile<<"["<<cache[i][j].valid_bit<<", "<<cache[i][j].tag_bits<<"] ";
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

//Print Binary Tree
void print_binary_tree(binary_tree_node *root)
{
    if (root != NULL)
    {
        print_binary_tree(root->left);
        cout << root->node_val<<" ";
        print_binary_tree(root->right);
    }
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

void Tree_PLRU_replacement(vector<vector<block_struct>> &cache, vector<int> &set_full, int assoc, int set_size, address_in &input_address,
					cache_stats_struct &cache_struct, binary_tree_node* bt_ptr[]){
	
	//Initialize a parameter to track Hit/Miss
	int Cache_Hit = 0;
	
	//Cache Checking in case of Read/Write
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
				//Update the BT for tracking most recently used
				binary_tree_update(bt_ptr[input_address.addr_index], i, 0, assoc-1);
				break;
			}
		}	
		
		//Debug Prints
		//if(Cache_Hit==0){
		//	cout<<"Cache Miss"<<"\n";
		//}else{
		//	cout<<"Cache Hit"<<"\n";
		//}
		
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
						binary_tree_update(bt_ptr[input_address.addr_index], i, 0, assoc-1);
						//cout<<"Updating Index in Set: "<<i<<"\n";
						break;
					}
				}	
				set_full[input_address.addr_index]++;
			} 
			
			//======================================================
			//if set is full then replace with LRU policy
			//======================================================			
			else{
				int replacement_index = TPLRU_replacement(bt_ptr[input_address.addr_index], 0, assoc-1);
				//cout<<"Replaced Way Number: "<<replacement_index<<"\n";
				cache[input_address.addr_index][replacement_index].valid_bit 		= 1;
                cache[input_address.addr_index][replacement_index].tag_bits  		= input_address.addr_tag;
				binary_tree_update(bt_ptr[input_address.addr_index], replacement_index, 0, assoc-1);
			}
			
		}
		
	} 
	//Neither of Read or Write command
	else{
		cerr<<"Invalid command from File"<<"\n";
	}
	

	//printLevelOrder(bt_ptr[input_address.addr_index]);
	
}

int main(int argc, char *argv[]){
	int nk = stoi(argv[1],nullptr,10);			//Cache size in KB
	int assoc = stoi(argv[2],nullptr,10);		//Set associativity of Cache = Number of ways = Number of blocks in a Set
	int blocksize = stoi(argv[3],nullptr,10);	//Blocksize of Cache in Bytes
	char repl = *argv[4];						//Cache Replacement policy
	
	
	int set_size = ((nk*1024)/assoc)/blocksize;	//Number of blocks in a way = Index bits
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
	

	//================================================
	//Binary tree creation for Tree_PLRU			    
	//================================================
	binary_tree_node *bt_ptr [set_size];
	for (int i=0; i<set_size; i++){
		bt_ptr[i] = link_binary_tree_to_SET(bt_ptr[i], 0, assoc-1);
	}
	
	//===============================================================================================================================
	//**********************************    FIle Read and Cache Hit/Miss Processing    **********************************************
	//===============================================================================================================================
	
	//================================================
	//Define the input address structure 
	//================================================
	address_in input_address;
	
	
	while(cin>>input_address.repl_in>>input_address.address){
		
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
		Tree_PLRU_replacement(cache, set_full, assoc, set_size, input_address, cache_statistics, bt_ptr);
		
		//cout<<"\n\n";
	}
	
	//display_cache(cache, set_size, assoc);
	
	double total_miss_percent 		= ((cache_statistics.number_of_misses/cache_statistics.number_of_mem_access)*100);
	double total_read_miss_percent 	= ((cache_statistics.number_of_read_misses/cache_statistics.number_of_read_access)*100);
	double total_write_miss_percent = ((cache_statistics.number_of_write_misses/cache_statistics.number_of_write_access)*100);
	
	cout<<cache_statistics.number_of_misses<<" "<<fixed<<setprecision(6)<<total_miss_percent<<"% "<<setprecision(0);
	cout<<cache_statistics.number_of_read_misses<<" "<<fixed<<setprecision(6)<<total_read_miss_percent<<"% "<<setprecision(0);
	cout<<cache_statistics.number_of_write_misses<<" "<<fixed<<setprecision(6)<<total_write_miss_percent<<"%"<<setprecision(0)<<"\n";
	
	ofstream outFile;
	outFile.open("Results/SpecBenchmark_Tree_PLRU_cache_results.txt", ios::app);
	outFile<<cache_statistics.number_of_misses<<" "<<fixed<<setprecision(6)<<total_miss_percent<<"% "<<setprecision(0)<<cache_statistics.number_of_read_misses<<" "<<fixed<<setprecision(6)<<total_read_miss_percent<<"% "<<setprecision(0)<<cache_statistics.number_of_write_misses<<" "<<fixed<<setprecision(6)<<total_write_miss_percent<<"%"<<setprecision(0)<<"\n";
	outFile.close();
	
	return 0;
}