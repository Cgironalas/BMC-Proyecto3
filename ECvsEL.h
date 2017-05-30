//v y w se manejan con [index]
struct lNode{
	int value;
	struct lNode* next;
	struct lNode* prev;
};
struct cNode{
	int value;
	bool arrow[3];
	struct cNode* next;
	struct cNode* prev;
	struct cNode* down;
	struct cNode* up;
};

int maxScoringL = 0;
int maxScoringC = 0;

int vSize;
int wSize;

int *joints;

char * v;
char * w;

int gap = -2;
int match = 1;
int mismatch = -1;

void printV(){
	printf("V list: ");
	for (int i = 0; i < vSize; i++) {
		printf("%c", v[i]);
	}
	printf("\n");
}
void printW(){
	printf("W list: ");
	for (int i = 0; i < wSize; i++) {
		printf("%c", w[i]);
	}
	printf("\n");
}

//Print functions=================================
	void printCList(struct cNode *pCHead) {
		struct cNode *ptr = pCHead;
		while(ptr != NULL) {
			printf("(%i,{", ptr->value);
			if (ptr->arrow[0] == true) { printf("d "); }
			if (ptr->arrow[1] == true) { printf("u "); }
			if (ptr->arrow[2] == true) { printf("l"); }
			printf("}) * ");
			ptr = ptr->next;
		}
		printf("\n");
		free(ptr);
	}
	void printCTable(struct cNode *pCTHead) {
		struct cNode *row = pCTHead;
		do {
			printCList(row);
			row = row->down;
		} while (row != NULL);
		free(row);
	}
	void printLList(struct lNode *pLHead) {
		struct lNode *ptr = pLHead;
		while (ptr != NULL) {
			printf("%i * ", ptr->value);
			ptr = ptr->next;
		}
		printf("\n");
		free(ptr);
	}
//================================================

//Min max functions===============================
	int min(int m1, int m2){
		if (m1 < m2){ return m1; }
		else { return m2; }
	}
	int max(int m1, int m2){
		if (m1 > m2){ return m1; }
		else { return m2; }
	}
	int max3(int m1, int m2, int m3){ return max(max(m1, m2), m3); }
//================================================

int checkChars(int i, int j) {
	//printf("%c - %c\n", v[i], w[j]);
	if (v[i] == w[j]) { return match; }
	else { return mismatch; }
}

struct lNode* BestScorePos(int v1, int v2, int w1, int w2){
	
	int pVal = 0;

	//Create scoring vectors and auxiliars============
		struct lNode *lHead = (struct lNode*) malloc(sizeof(struct lNode));
		struct lNode *lHead2 = (struct lNode*) malloc(sizeof(struct lNode));
		struct lNode *lCurrent = NULL;
		struct lNode *lCurrent2 = NULL;
	//================================================

	//Initialize scoring vectors======================
		lHead->value = pVal;
		lHead->next = NULL;
		lHead->prev = NULL;

		lHead2->value = pVal;
		lHead2->next = NULL;
		lHead2->prev = NULL;

		lCurrent = lHead;
		lCurrent2 = lHead2;
	//================================================

	//Fill lists======================================
		for (int i = v1 - 1; i >= v2; i--) {
			pVal += gap;

			struct lNode *aux = (struct lNode*) malloc(sizeof(struct lNode));
			aux->value = pVal;
			aux->next = NULL;
			aux->prev = lCurrent;

			lCurrent->next = aux;
			lCurrent = aux;

			struct lNode *aux2 = (struct lNode*) malloc(sizeof(struct lNode));
			aux2->value = pVal;
			aux2->next = NULL;
			aux2->prev = lCurrent2;

			lCurrent2->next = aux2;
			lCurrent2 = aux2;
		}
	//================================================

	//printf("\nLISTS:\n");
	//printLList(lHead);

	//Get best scoring================================
		for (int j = w1 - 1; j >= w2; j--) {
			lCurrent = lHead;
			lCurrent2 = lHead2;
			
			lCurrent2->value = lCurrent->value + gap;

			for (int i = v1 - 1; i >= v2; i--) {
				int val1 = lCurrent->value + checkChars(i, j);
				int val2 = lCurrent2->value + gap;
				int val3 = lCurrent->next->value + gap;
				
				lCurrent2 = lCurrent2->next;
				lCurrent = lCurrent->next;

				lCurrent2->value = max3(val1, val2, val3);
			}
			//printLList(lHead2);

			//Reset current pointers==========================
				lCurrent = lHead;
				lCurrent2 = lHead2;
			//================================================

			//Set values of second row to main row============
				lCurrent->value = lCurrent2->value;
				for (int i = v1 - 1; i >= v2; i--) {
					lCurrent = lCurrent->next;
					lCurrent2 = lCurrent2->next;
					lCurrent->value = lCurrent2->value;
				}
			//================================================
		}
	//================================================
	return lHead;
}

struct lNode* BestScorePre(int v1, int v2, int w1, int w2){

	int pVal = 0;

	//Create scoring vectors and auxiliars============
		struct lNode *lHead = (struct lNode*) malloc(sizeof(struct lNode));
		struct lNode *lHead2 = (struct lNode*) malloc(sizeof(struct lNode));
		struct lNode *lCurrent = NULL;
		struct lNode *lCurrent2 = NULL;
	//================================================

	//Initialize scoring vectors======================
		lHead->value = pVal;
		lHead->next = NULL;
		lHead->prev = NULL;

		lHead2->value = pVal;
		lHead2->next = NULL;
		lHead2->prev = NULL;

		lCurrent = lHead;
		lCurrent2 = lHead2;
	//================================================

	//Fill lists======================================
		for (int i = v1; i < v2; i++) {
			pVal += gap;

			struct lNode *aux = (struct lNode*) malloc(sizeof(struct lNode));
			aux->value = pVal;
			aux->next = NULL;
			aux->prev = lCurrent;

			lCurrent->next = aux;
			lCurrent = aux;

			struct lNode *aux2 = (struct lNode*) malloc(sizeof(struct lNode));
			aux2->value = pVal;
			aux2->next = NULL;
			aux2->prev = lCurrent2;

			lCurrent2->next = aux2;
			lCurrent2 = aux2;
		}
	//================================================

	//printf("\nLIST:\n");
	//printLList(lHead);

	//Get best scoring================================
		for (int j = w1; j < w2; j++) {
			lCurrent = lHead;
			lCurrent2 = lHead2;
			
			lCurrent2->value = lCurrent->value + gap;

			for (int i = v1; i < v2; i++) {
				int val1 = lCurrent->value + checkChars(i, j);
				int val2 = lCurrent2->value + gap;
				int val3 = lCurrent->next->value + gap;
				
				lCurrent2 = lCurrent2->next;
				lCurrent = lCurrent->next;

				lCurrent2->value = max3(val1, val2, val3);
			}
			//printLList(lHead2);

			//Reset current pointers==========================
				lCurrent = lHead;
				lCurrent2 = lHead2;
			//================================================

			//Set values of second row to main row============
				lCurrent->value = lCurrent2->value;
				for (int i = v1; i < v2; i++) {
					lCurrent = lCurrent->next;
					lCurrent2 = lCurrent2->next;
					lCurrent->value = lCurrent2->value;
				}
			//================================================
		}
	//================================================
	return lHead;
}

void nwLAux(int m, int m2, int n, int n2){
	int i;
	if ((m2 - m) % 2 == 0) { i = m + ((m2 - m) / 2) - 1; }
	else { i = m + ((m2 - m) / 2); }

	printf("I value: %i\n", i);

	struct lNode* pre = BestScorePre(m, i, n, n2);
	printf("PRE: ");
	printLList(pre);
	struct lNode* pos = BestScorePos(m2, i + 1, n2, n);
	printf("POS: ");
	printLList(pos);

	int curVal;
	int index = 0;
	int counter = 1;
	int counterPre = 0;
	int counterPos = 1;

	int maxVal = pre->value + pos->value + gap;

	pos = pos->next;

	while (pre != NULL && pos != NULL) {
		curVal = pre->value + pos->value;

		if (counterPre == counterPos) {
			curVal += gap;
			counterPos++;
			pos = pos->next;
		} else {
			curVal += checkChars(i, counterPos);
			counterPre++;
			pre = pre->next;
		}
		if (curVal > maxVal) {
			maxVal = curVal;
			index = counter;
		}
		counter++;
	}
	joints[i] = index;
	if (m2 - m != 0) {
		nwLAux(m, i, n, index);
		nwLAux(i + 1, m2, index / 2, n2);	
	}
}

void nwL(){
	joints = malloc(sizeof(int) * ((vSize * 2) + 1));;
	for (int i = 0; i < (vSize * 2) + 1; i++) {
		joints[i] = -1;
	}

	nwLAux(0, vSize, 0, wSize);
	
	printf("\n\nAlignment Joints: \n");
	for (int i = 0; i < (vSize * 2) + 1; i++) {
		printf("%i * ", joints[i]);
	}
	printf("\n");
}