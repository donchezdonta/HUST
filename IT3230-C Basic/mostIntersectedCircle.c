#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
	int id;
	double x;
	double y;
	double radius;
} Circle;

int checkIntersection(Circle c1, Circle c2) {
	double distance = sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));
	double radiusSum = c1.radius + c2.radius;
	
	if (distance < radiusSum && distance > fabs(c1.radius - c2.radius)) 
		return 1;
	return 0;
}

void drawCircle(Circle* c, int index) {
	c->id = index + 1;
	printf("Circle %d: \n", c->id);
	printf("Center coords (x y): ");
	scanf("%lf %lf", &c->x, &c->y);
	printf("Radius: ");
	scanf("%lf", &c->radius);
}

void randomCircle(Circle* c, int index) {
	c->id = index + 1;
	c->x = (rand() % 201) - 100;
	c->y = (rand() % 201) - 100;
	c->radius = (rand() % 50) + 1;
}

void showCircle(Circle c) {
	printf("Circle %d: Center (%.2f %.2f), Radius: %.2f\n", c.id, c.x, c.y, c.radius);
}

void findMostIntersects(Circle* circles, int n) {
	int* intersect_cnt = (int*)calloc(n, sizeof(int));
	int** intersect_with = (int**)malloc(n * sizeof(int*));
	
	for (int i = 0; i <n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (i != j && checkIntersection(circles[i], circles[j])) {
				intersect_with[i][count] = j;
				count++;
			}
		}
		intersect_cnt[i] = count;
	}
	
	int max_idx= 0;
	for (int i = 0; i < n; i++) {
		if (intersect_cnt[i] > intersect_cnt[max_idx]) 
			max_idx = 1;
	}
	
	printf("\n==MOST INTERSECTED CIRCLE==\n");
	showCircle(circles[max_idx]);
	printf("Number of intersected circles: %d\n", intersect_cnt[max_idx]);
	
	if (intersect_cnt[max_idx] > 0) {
		printf("Circles intersected: ");
		for (int i = 0 ; i < intersect_cnt[max_idx]; i++) {
			printf("%d", circles[intersect_with[max_idx][i]].id);
			if ( i < intersect_cnt[max_idx] - 1) 
				printf(", ");
		}
		printf("\n");
	}
	
	for (int i = 0; i < n; i++) 
		free(intersect_with[i]);
	free(intersect_with);
	free(intersect_cnt);
}

int main() {
	srand(time(NULL));
	int n, choice;
	Circle* circles;
	
	printf("==CIRCLE MANAGEMENT==\n");
	printf("Input circles: ");
	scanf("%d", &n);
	
	while (n <= 0) {
		printf("Must be larger than 0. Re-enter: ");
		scanf("%d", &n);
	}
	
	printf("Input modes: \n");
	printf("1. Manual input\n");
	printf("2. Randomized\n");
	printf("Choose mode: ");
	scanf("%d", &choice);
	
	if (choice == 1) {
		for (int i = 0; i < n; i++) drawCircle(&circles[i], i);
	} else {
		for (int i = 0; i < n; i++) randomCircle(&circles[i], i);
		printf("\nGenerated %d random circles.\n", n);
	}
	
	printf("\n==CIRCLE INFO==\n");
	int has_intersection = 0;
	for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (checkIntersection(circles[i], circles[j])) {
                printf("Circle %d intersects with circle %d\n", circles[i].id, circles[j].id);
                has_intersection = 1;
            }
        }
    }
    
    if (!has_intersection) printf("No intersecting circles.");
    
    findMostIntersects(circles, n);
    free(circles);
	
	return 0;
}


