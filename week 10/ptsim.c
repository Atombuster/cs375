#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256  // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8  // Shift page number this much

#define PTP_OFFSET 64 // How far offset in page 0 is the page table pointer table

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);

    int zpfree_addr = get_address(0, 0);
    mem[zpfree_addr] = 1;  // Mark zero page as allocated
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

int find_free_page(void){
	for(int i=0; i != 64; i++) {
		if (mem[i] == 0) {
			return i;
		}
	}
	return -1;
}

void mark_page(int page_num, int in_use) {
	mem[page_num] = in_use;
}

//
// Allocate pages for a new process
//
// This includes the new process page table and page_count data pages.
//
void new_process(int proc_num, int page_count)
{
	int pt_free_page = find_free_page();
	//printf("np: %d\n", pt_free_page);
	mark_page(pt_free_page, 1);
	assert(pt_free_page != -1);
	int temp = proc_num + 64;
	mem[temp] = pt_free_page;
	int i = 0;
	while(i < page_count && i < 256){
		int free_page = find_free_page();
		//printf("np2: %d\n", free_page);
		mark_page(free_page, 1);
		int address = get_address(pt_free_page, i);
		mem[address] = free_page;
		i++;
	}
	
	
	
	
    // TODO
}



/*find the page table then find pages that contain the process
then free them, at the end free the page table*/
void kill_process(int process){
	//printf("kp: %d\n", process);
	int table_pointer = get_page_table(process);
	//printf("kpGPT: %d\n", table_pointer);
	//found page_table
	//loop through free page map finding in us pages and freeing them
	for (int i = 0; i < PAGE_COUNT; i++){
		int addr = get_address(table_pointer, i);
		//mem[addr];
		//\\printf("KP%d: %d\n", i , mem[addr]);
		int page_to_free = mem[addr];
		if (page_to_free != 0) {
			mem[page_to_free] = 0;
			//printf("%d\n", i);
		}
	}
	mem[table_pointer] = 0;
	
}//////////////////////////////////////////////////////////////////////////////////


void store(int proc_num, int virtual_address, int value){
    int vpage = virtual_address >> PAGE_SHIFT;
    int offset = virtual_address & (PAGE_SIZE - 1);
    int pageT = get_page_table(proc_num);
    int phys_page = mem[get_address(pageT, vpage)];
    int phys_addr = get_address(phys_page, offset);
    mem[phys_addr] = value;
	printf("Store proc %d: %d => %d, value=%d\n", proc_num, virtual_address, phys_addr, value);
}

int THE_value(int proc_num, int virtual_address){
    int vpage = virtual_address >> PAGE_SHIFT;
    int offset = virtual_address & (PAGE_SIZE - 1);
    int pageT = get_page_table(proc_num);
    int phys_page = mem[get_address(pageT, vpage)];
    int phys_addr = get_address(phys_page, offset);
	int value = mem[phys_addr];
	printf("Load proc %d: %d => %d, value=%d\n", proc_num, virtual_address, phys_addr, value);
    
	return value;
}




//
// Print the free page map
//
// Don't modify this
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");

    for (int i = 0; i < 64; i++) {
        int addr = get_address(0, i);

        printf("%c", mem[addr] == 0? '.': '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
// Don't modify this
//
void print_page_table(int proc_num)
{
    printf("--- PROCESS %d PAGE TABLE ---\n", proc_num);

    // Get the page table for this process
    int page_table = get_page_table(proc_num);

    // Loop through, printing out used pointers
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{
    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }
    
    initialize_mem();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "pfm") == 0) {
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) {
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }
		else if (strcmp(argv[i], "np") == 0) {
			int proc_num = atoi(argv[++i]);
			int page_count = atoi(argv[++i]);
            new_process(proc_num, page_count);
        }
		else if (strcmp(argv[i], "kp") == 0) {
			int proc_kill = atoi(argv[++i]);
            kill_process(proc_kill);
        }
		else if (strcmp(argv[i], "sb") == 0) {
			int proc_num = atoi(argv[++i]);
			int virtual_address = atoi(argv[++i]);
			int value = atoi(argv[++i]);
            store(proc_num, virtual_address, value);
        }
		else if (strcmp(argv[i], "lb") == 0) {
			int proc_num = atoi(argv[++i]);
			int virtual_address = atoi(argv[++i]);
            THE_value(proc_num, virtual_address);
        }

        // TODO: more command line arguments
    }
}
