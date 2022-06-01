#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); //초기화
int freeArray(int *a); //배열 메모리 해제
void printArray(int *a); // 배열 출력

int selectionSort(int *a); //선택정렬
int insertionSort(int *a); //삽입정렬
int bubbleSort(int *a); //버블정렬
int shellSort(int *a); // 쉘정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); //퀵정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- [leeseonjue] [2021041042] -----]");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //배열초기화
			break;
		case 'q': case 'Q':
			freeArray(array); //배열 해제
			break;
		case 's': case 'S':
			selectionSort(array); // 배열을 선택정렬로
			break;
		case 'i': case 'I':
			insertionSort(array); // 삽입정렬로
			break;
		case 'b': case 'B':
			bubbleSort(array); // 버블정렬로
			break;
		case 'l': case 'L':
			shellSort(array); //쉘 정렬로 
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE); //퀵정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열 출력
			hashing(array, &hashtable); //해싱
			printArray(hashtable); // 배열출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);//해시테이블의 정렬 출력
			index = search(hashtable, key); // 인덱스에 탐색 결과 삽입
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array); //배열출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) //배열 초기화
{
	int *temp = NULL; //temp의 값을 null로 초기화

	
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //array가 NULL인 경우 메모리 할당
        *a = temp;  // 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else
		temp = *a; //NULL이 아닌경우 temp에 배열 대입

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) //배열 동적 해제
{
	if(a != NULL)//배열 a가 비어있지 않으면 
		free(a);
	return 0;
}

void printArray(int *a) //배열 출력
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//최대 배열 크기까지 반복문
		printf("a[%02d] ", i);//0: 채워질 문자. 2: 총 자리수
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) //선택정렬
{
	int min; //최소값을 넣을 변수
	int minindex; //최소값의 인덱스
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 처음 인덱스 부터 값을 하나씩 선택하므로 minIndex는 i로 지정해둔다
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //선택한 값 이후의 있는 원소들과 비교해야하므로 j는 i + 1부터 시작
		{
			if (min > a[j]) //최솟값 탐색
			{
				min = a[j]; //최솟값이 a[j]이므로 최솟값의 인덱스는 j
				minindex = j;
			}
		}
		a[minindex] = a[i];//배열의 minindex에 i값 대입
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//배열 출력
	return 0;
}

int insertionSort(int *a) //삽입정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //배열출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //변수 t에 배열의 값 삽입
		j = i; // 동일시
		while (a[j-1] > t && j > 0) //이전의 값이 정렬된 값보다 크면
		{
			a[j] = a[j-1];//정렬된 값 바꾸기
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])// temp에 이전 인덱스 값 저장
			{
				t = a[j-1]; // 현재 값 이전 인덱스로 스왑
				a[j-1] = a[j]; // 이전 값 현재 인덱스로 스왑
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //처음 간격을 배열크기의 반으로,  2씩 나누면서 그룹 생성(그룹내 데이터는 2배씩 커짐)
	{
		for (i = 0; i < h; i++) 
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // 그룹 내에서 전값과 비교 
			{
				v = a[j]; // 삽입할 값 저장
				k = j;
				while (k > h-1 && a[k-h] > v) // 그룹내의 삽입 할 값의 앞만 검사
				{
					a[k] = a[k-h]; // 그룹내에서 뒤로 한 칸씩 옮김
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //퀵정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];//피봇의 값 설정
		i = -1; //초기화
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); //이전에 증가된 값의 a배열이 피봇보다 작은동안
			while(a[--j] > v); // 이전에 증가된 값의 a배열이 피봇보다 큰동안

			if (i >= j) break;
			t = a[i]; //값을 swap
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i]; //값을 swap
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); //퀵정렬 호출
		quickSort(a+i+1, n-i-1); //왼쪽 부분집합, 오른쪽 부분집합 퀵정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //키값을 최대 해시테이블 크기로 나눈값 리턴
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //해시테이블 null로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//해시테이블 배열의 값을 -1로 설정

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //키값, 해시코드값, 인덱스 모두 -1로 설정
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //키 변수에 배열 a의 값 대입
		hashcode = hashCode(key); //hashCode 함수에 key값 넣은 결과값을 hashcode에 대입
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //hashtable[hashcode]의 값이 -1이면 key
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode; //-1이 아니면 인덱스는 hashcode

			while(hashtable[index] != -1) //-1이 아닌동안
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //증가된 index를 최대 해시테이블 크기로 나눠줌 
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //key 값 대입
		}
	}

	return 0;
}

int search(int *ht, int key) //탐색
{
	int index = hashCode(key); //index변수에 hashCode(key)값 대입

	if(ht[index] == key) //인덱스 배열과 키 값이 같으면
		return index; //인덱스 리턴

	while(ht[++index] != key) //key 값과 같지 않으면
	{
		index = index % MAX_HASH_TABLE_SIZE; //인덱스 값을 최대 해시테이블 크기로 나눈 값을 인덱스 배열에 대입
	}
	return index; //인덱스 값 리턴
}
