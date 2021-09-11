#include <stdio.h>
#include <stdlib.h>
#define size 5
#define INF 100000

struct Triangle {
	int index;
	int type;					//0 signifies l type triangle and 1 signifies r type
	int nodes[size][size];		//Stores connectivity of nodes within the triangle
};

//Setting up triangle as l type or r type
struct Triangle* setUp (int type, int index) {
	struct Triangle *temp = malloc (sizeof (*temp));	//Check if the syntax is correct 
	//Maintains links of nodes that are connected	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			temp->nodes[i][j] = INF;
	temp->nodes[1][2] = temp->nodes[2][1] = 1;
	temp->nodes[2][3] = temp->nodes[3][2] = 1;
	temp->nodes[2][4] = temp->nodes[4][2] = 1;
	temp->type = type;												//Assigns type to the triangle
	temp->index = index;
	return temp;
}

//Maintains links in l type to r type transition
struct triangleLink {
	int links[size][size];
	//linkType maintains the type of link, lID maintains the id of triangle towards the left
	//And rID maintains the ID of triangle towards the right
	//For linkType, 0 indicates l to r and 1 indicates r to l
	int linkType, lID, rID;		
};

struct triangleLink* setLink (struct Triangle *left, struct Triangle *right) {
	struct triangleLink *temp = malloc(sizeof(*temp));
	temp->linkType = left->type;
	temp->lID = left->index;
	temp->rID = right->index;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			temp->links[i][j] = INF;
	//Stores links based on which triangle being converted
	switch (temp->linkType) {
		case 1:
			temp->links[4][1] = 1;
			temp->links[3][3] = 1;
			break;
		case 2:
			temp->links[2][2] = 1;
			break;
	}
	return temp;
}

//Updates triangle if obstacle in encounterd
void updateTriangle (struct Triangle *update, int nodeL, int nodeR, int weight) {
	update->nodes[nodeL][nodeR] = weight;
}

//Updates link weights if obstacle is encountered
void updateLink (struct triangleLink* update, int nodeL, int nodeR,int weight) {
	update->links[nodeL][nodeR] = weight;
}

int main() {
	struct Triangle* map[6];
	for (int i = 0; i < 6; i++) {
		map[i] = setUp(i%2, i);
	}
	for (int i = 5; i < 6; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				printf("%d  ", map[i]->nodes[j][k]);
			}
			printf("\n");
		}
	}
	return 0;
}

#undef size
#undef INF