#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book		// 책 구조체
{
	char title[100];	// 제목
	char author[100];	// 저자
	char isbn[100];		// 번호
	int year;			// 출시년
	int quantity;		// 재고
}Book;

typedef struct TreeNode		// 트리구조체
{
	Book book;				// 책 정보
	struct TreeNode *left;	// 왼쪽 자식
	struct TreeNode *right;	// 오른쪽 자식
}TreeNode;

TreeNode *insertBook(TreeNode *root, Book book);		// 책 추가
TreeNode *searchBook(TreeNode *root, char *title);		// 책 검색
TreeNode *deleteBook(TreeNode *root, char *title);		// 책 삭제
TreeNode *findminNode(TreeNode *root);				// 오른쪽 트리에서 최솟값 찾기
void printBooks(TreeNode *root);						// 책 출력
int getUserChoice();									// 사용자 선택 받기
void addBook(TreeNode **root);							// 책 추가 함수
void searchBookByTitle(TreeNode *root);					// 책 검색 함수
void deleteBookByTitle(TreeNode **root);					// 책 삭제 함수

int main()
{
	TreeNode *Library = NULL;
	Book book1 = {"Hong Gill Dong", "misang", "432123", 1930, 3};
	Book book2 = {"Kongji Pacji", "misang", "632123", 1940, 5};

	// 초기 책 데이터 삽입
	Library = insertBook(Library , book1);
	Library = insertBook(Library , book2);
	printBooks(Library);

	while(1)
	{
		int choose = getUserChoice();

		switch(choose)
		{
			case 1:
				addBook(&Library);  // 책 추가
				break;
			case 2:
				searchBookByTitle(Library);  // 책 검색
				break;
			case 3:
				deleteBookByTitle(&Library);  // 책 삭제
				break;
			case 4:
				printBooks(Library);  // 책 출력
				break;
			default:
				fputs("잘못된 선택입니다.\n", stdout);
				break;
		}
	}
	return 0;
}

// 사용자로부터 메뉴 선택 받기
int getUserChoice()
{
	int choice = 0;
	fputs("\n\n1. 책 추가\n", stdout);
	fputs("2. 책 검색\n", stdout);
	fputs("3. 책 삭제\n", stdout);
	fputs("4. 책 재고 출력\n", stdout);
	fputs("선택: ", stdout);
	scanf("%d", &choice);
	getchar();
	return choice;
}

// 책 추가 함수
void addBook(TreeNode **root)
{
    Book newBook;
    fputs("책 제목: ", stdout);
    fgets(newBook.title, sizeof(newBook.title), stdin);  
    newBook.title[strcspn(newBook.title, "\n")] = 0;  

    fputs("책 저자: ", stdout);
    fgets(newBook.author, sizeof(newBook.author), stdin);  
    newBook.author[strcspn(newBook.author, "\n")] = 0;  

    fputs("책 ISBN: ", stdout);
    fgets(newBook.isbn, sizeof(newBook.isbn), stdin);  
    newBook.isbn[strcspn(newBook.isbn, "\n")] = 0;  // 개행 문자 제거

    fputs("책 출시 연도: ", stdout);
    scanf("%d", &newBook.year);
    getchar();  

    fputs("책 재고: ", stdout);
    scanf("%d", &newBook.quantity);
    getchar();  // 엔터키 제거

    *root = insertBook(*root, newBook);
}

// 책 검색 함수
void searchBookByTitle(TreeNode *root)
{
	char title[100];
	fputs("검색할 책 제목: ", stdout);
	fgets(title, sizeof(title), stdin); 
    title[strcspn(title, "\n")] = 0;  // 입력 받은 문자열 끝의 개행 문자 제거
									  
	TreeNode *foundBook = searchBook(root, title);
	if(foundBook != NULL)
	{
		printf("\n책 제목: %s\n저자: %s\nISBN: %s\n출시 연도: %d\n재고: %d\n", 
				foundBook->book.title, foundBook->book.author, foundBook->book.isbn, 
				foundBook->book.year, foundBook->book.quantity);
	}
	else
	{
		fputs("책을 찾을 수 없습니다.\n", stdout);
	}
}

// 책 삭제 함수
void deleteBookByTitle(TreeNode **root)
{
	char title[100];
	fputs("삭제할 책 제목: ", stdout);
	fgets(title, sizeof(title), stdin);  
    title[strcspn(title, "\n")] = 0;  // 입력 받은 문자열 끝의 개행 문자 제거

	*root = deleteBook(*root, title);
	fputs("책이 삭제되었습니다.\n", stdout);
}

TreeNode *insertBook(TreeNode *root, Book book)
{
	if(root == NULL)
	{
		TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
		newnode->book = book;
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;
	}

	if(strcmp(book.title, root->book.title) < 0)
	{
		root->left = insertBook(root->left, book);
	}
	else if(strcmp(book.title, root->book.title) > 0)
	{
		root->right = insertBook(root->right, book);
	}
	return root;
}

TreeNode *searchBook(TreeNode *root, char *title)
{
	if(root == NULL || strcmp(title, root->book.title) == 0)
		return root;
	if(strcmp(title, root->book.title) < 0)
		return searchBook(root->left, title);
	else
		return searchBook(root->right, title);
}

TreeNode *deleteBook(TreeNode *root, char *title)
{
	if(root == NULL)
		return NULL;
	if(strcmp(title, root->book.title) < 0)
	{
		root->left = deleteBook(root->left, title);
	}
	else if(strcmp(title, root->book.title) > 0)
	{
		root->right = deleteBook(root->right, title);
	}
	else // 현재노드가 삭제할 노드일 경우
	{
		if(root->left == NULL && root->right == NULL) // 자식 둘다 널일 경우
		{
			free(root);
			return NULL;		
		}

		else if(root->left == NULL) // 자식이 하나일 경우
		{
			TreeNode *temp = root->right;  
			free(root);
			return temp;
		}

		else if(root->right == NULL)
		{
			TreeNode *temp = root->left;  
			free(root);
			return temp;
		}
		
		else // 자식이 두개인 경우
		{
			TreeNode *temp = findminNode(root->right);
			root->book = temp->book;
			root->right = deleteBook(root->right, temp->book.title);
		}
	}
	return root;
}

TreeNode *findminNode(TreeNode *root) // 오른쪽 노드중에 최소값검색
{
	while(root && root->left != NULL)
	{
		root = root->left;
	}
	return root;
}

void printBooks(TreeNode *root)
{
	if(root != NULL)
	{
		printBooks(root->left);
		fputs("------------------------------\n",stdout);
		printf("Title : %s\nAuthor : %s\nISBN : %s\nYear : %d\nQuantity : %d\n", 
				root->book.title, root->book.author, root->book.isbn, 
				root->book.year, root->book.quantity);
		printBooks(root->right);
	}
}

