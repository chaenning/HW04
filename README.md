# [4번 과제] C++ Summary

## 1️⃣ **Intro: 도서관 관리 시스템 구현**

우리는 짧은시간동안 C++에 대해 많은 것들을 배웠습니다. 
얼마나 배웠는지 한번 쭉 나열해볼까요?

- 프로그래밍 기본 요소(변수, 배열, 함수, 조건문, 반복문)
- 다형성 / 상속
- STL
- SOLID 원칙

이번 과제는  간단한 도서 관리 프로그램을 만들어볼 것입니다.
비록 콘솔로 동작하는 프로그램이지만, 충분히 그럴듯할정도 동작하는 프로그램이기 때문에 꽤 성취감도 있을 겁니다.
지금까지 학습한 C++의 기본 개념과 프로그래밍 기술을 활용하여 실용적인 프로그램을 설계하고 구현해보는 것이 이 과제의 목적입 니다.

자신의 실력을 최대한 발휘해서  요구사항에 맞는 기능구현은 물론이고 재사용성까지 고려해서 프로젝트를 완성해봅시다.

## 2️⃣ 개발 프로세스 가이드

실제 현업을 하다보면 처음부터 코드를 구현하는 상황보다는, 이미 누군가 구현한 코드를 파악하고 이를 수정하거나 기능을 추가해야 하는 경우가 많습니다.

아예 새로 코드를 구현하는 경우에는 본인의 스타일대로 구현하면 되므로  간단하지만, 기존의 코드를 분석하고 구조를 유지한 채로 기증을 수정하거나 추가하는 경우엔 고려할 게 많습니다.

이번 과제에서는 아래 3가지 정도는 항상 고려하면서 진행하는걸 권장 드립니다.

- 어떤 의도로 코드를 구현했는지
- 수정을 해야 한다면, 기존 코드의 수정을 최소화 하면서 수정할 수 있는 방안이 있는지
- 객체지향 프로그래밍 언어라면 SOLID 원칙을 잘 준수하고 있는지

이번에 해볼 과제는 다음과 같은 순서로 진행 됩니다.

- 제공된 간단한 도서관 관리 프로그램 코드를 분석
- 제공된 코드를 활용해서 간단한 검색 기능을 추가한다 (간단한 반복문 정도 구현 수준)
- 대여 기능(도전 기능)을 추가한다.(아예 새로운 기능을 구현하는 수준)

기본적으로 제공 되는 도서관리 프로그램 코드는 아래와 같습니다.

- [코드스니펫]간단한 도서 관리 프로그램
    
    ```cpp
    #include <iostream>
    #include <vector>
    #include <string>
    
    using namespace std; // namespace std 사용
    
    class Book {
    public:
        string title;
        string author;
    
        Book(const string& title, const string& author)
            : title(title), author(author) {}
    };
    
    class BookManager {
    private:
        vector<Book> books; // 책 목록 저장
    
    public:
        // 책 추가 메서드
        void addBook(const string& title, const string& author) {
            books.push_back(Book(title, author)); // push_back 사용
            cout << "책이 추가되었습니다: " << title << " by " << author << endl;
        }
    
        // 모든 책 출력 메서드
        void displayAllBooks() const {
            if (books.empty()) {
                cout << "현재 등록된 책이 없습니다." << endl;
                return;
            }
    
            cout << "현재 도서 목록:" << endl;
            for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
                cout << "- " << books[i].title << " by " << books[i].author << endl;
            }
        }
    };
    
    int main() {
        BookManager manager;
    
        // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
        // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
        while (true) {
            cout << "\n도서관 관리 프로그램" << endl;
            cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
            cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
            cout << "3. 종료" << endl; // 프로그램 종료
            cout << "선택: ";
    
            int choice; // 사용자의 메뉴 선택을 저장
            cin >> choice;
    
            if (choice == 1) {
                // 1번 선택: 책 추가
                // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
                string title, author;
                cout << "책 제목: ";
                cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
                getline(cin, title); // 제목 입력 (공백 포함)
                cout << "책 저자: ";
                getline(cin, author); // 저자명 입력 (공백 포함)
                manager.addBook(title, author); // 입력받은 책 정보를 추가
            } else if (choice == 2) {
                // 2번 선택: 모든 책 출력
                // 현재 BookManager에 저장된 책 목록을 출력합니다.
                manager.displayAllBooks();
            } else if (choice == 3) {
                // 3번 선택: 종료
                // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
                cout << "프로그램을 종료합니다." << endl;
                break; // while 루프 종료
            } else {
                // 잘못된 입력 처리
                // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
                cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            }
        }
    
        return 0; // 프로그램 정상 종료
    }
    
    ```
    

![image](https://github.com/user-attachments/assets/aa938d6e-790e-41a8-a07f-e4a14d6d5a91)


## 3️⃣ 필수 기능 가이드

기존 도서관 관리 프로그램에 검색 기능을 추가해주세요

- 책 제목으로 검색이 가능해야 합니다.
- 작가로 검색이 가능해야 합니다.
- 책 제목이 동일한 경우는 없다고 가정 합니다.

필수 기능 구현 완료 후 전체적인 구조를 그리면 아래와 같습니다.

어디까지나 참조일 뿐 꼭 이대로 구현할 필요는 없습니다.

![image](https://github.com/user-attachments/assets/5463a984-bdd7-48b1-a42c-cb600da5c44f)


## 4️⃣ 도전 기능 가이드

기존 도서관 관리 프로그램에 필수 기능을 추가한 상태에서 아래 대여 기능을 추가해주세요

- 특정 책의 대여 여부를 알 수 있어야 합니다.
- 책의 이름으로 대여 여부를 검색하고 대여가 아닌 경우 대여할 수 있어야 합니다.
- 책의 작가로 대여 여부를 검색하고 대여가 아닌 경우 대여할 수 있어야 합니다.
- 책을 반납할 수 있어야 합니다.
- 모든 책의 재고는 난이도를 낮추기 위해 3권으로 통일 합니다.

도전 기능 구현까지 완료한 후 전체적인 구조를 그리면 아래와 같습니다.

어디까지나 참조일 뿐 꼭 이대로 구현할 필요는 없습니다.
![image](https://github.com/user-attachments/assets/58c019b7-540b-4ece-ba21-91f19f69fc66)
