#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char name[13];
	uint16_t age;
} person_t;

int main(void) {
	person_t ivan;
	strncpy(ivan.name, "Ivan", sizeof(ivan.name));
	ivan.age = 42;

	write(1, "Name: ", strlen("Name: "));
	write(1, ivan.name, strlen(ivan.name));
	write(1, "\n", 1);

	write(1, "Age: ", strlen("Age: "));
	char age_string[6];
	snprintf(age_string, sizeof(age_string), "%d", ivan.age);
	write(1, age_string, strlen(age_string));
	write(1, "\n", 1);
}
