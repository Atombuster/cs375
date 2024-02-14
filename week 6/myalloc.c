#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))

struct block {
	int size; //sive in bytes
	int in_use; //boolean
	struct block *next;
	
};
struct block* head;
int start = 0;

void *myalloc(int meme){
	
	 
	if(start == 0){
		void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
		head = heap;
		int data_size = 1024 - PADDED_SIZE(sizeof(struct block));
		head->size = data_size;
		head->in_use = 0;
		head->next = NULL;	
		start = 1;
	}
	struct block* curr = head;
	while(curr != NULL) {
		if(curr->in_use == 0){
			if(curr->size >= PADDED_SIZE(meme)){
				curr->in_use = 1;
				return PTR_OFFSET(curr, PADDED_SIZE(sizeof(struct block)));
			}
		}
		
		curr = curr->next;
		
	}
	
	return NULL;
}
void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int main(){

	void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}







