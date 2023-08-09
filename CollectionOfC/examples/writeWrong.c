#include <string.h>
#include <unistd.h>
#include <stdint.h>
typedef struct {
	char name[13];
	uint16_t age;
} person_t;

int main(void) {
	person_t ivan;
	strncpy(ivan.name, "Ivan", sizeof(ivan.name));
	ivan.age = 42;
	// strlen(ivan.name) --> 4
	// sizeof(ivan.name) --> 13
	
	write(1, &ivan, sizeof(ivan));
}
