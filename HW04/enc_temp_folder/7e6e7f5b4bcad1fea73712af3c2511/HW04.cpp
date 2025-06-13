#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
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

    // 책 제목 검색
    void searchByTitle(const string& title) {
        bool isFind = false;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].title == title) {
                cout << "찾은 책 : " << books[i].title << " by " << books[i].author << endl;
                isFind = true;
            }
        }
        if (!isFind) cout << "검색한 책이 존재하지 않습니다." << endl;
    }

    // 작가 검색
    void searchByAuthor(const string& author) {
        bool isFind = false;
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].author == author) {
                cout << "찾은 책 : " << books[i].title << " by " << books[i].author << endl;
                isFind = true;
            }
        }
        if(!isFind) cout << "검색한 작가가 존재하지 않습니다." << endl;
    }


    const vector<Book>& getBooks() const {
        return books;
    }

    // 마지막에 들어온 책 == 방금 들어온 책 반환
    const Book& getLastBooks() const {

        return books.back();
    }

};


class BorrowManager {
private:
    unordered_map<string, int> stock; // 책 제목 -> 재고 수량

public:
    // 초기화 (Book 목록 받아서 재고 3으로 설정)
    void initializeStock(const Book& book, int quantity = 3) {
        stock[book.title] = quantity;
    }

    // 제목으로 대여
    void borrowBookByTitle(const vector<Book>& books, const string& title) {
        for (const auto& book : books) {
            if (book.title == title) {
                if (stock[title] > 0) {
                    stock[title]--;
                    cout << "[" << title << "] 책을 대여했습니다. 남은 재고: " << stock[title] << endl;
                }
                else {
                    cout << "[" << title << "] 책은 현재 모두 대여 중입니다." << endl;
                }
                return;
            }
        }
        cout << title << "' 에 해당하는 책이 없습니다." << endl;
    }

    // 작가로 대여
    void borrowBookByAuthor(const vector<Book>& books, const string& author) {
        for (const auto& book : books) {
            if (book.author == author) {
                if (stock[book.title] > 0) {
                    stock[book.title]--;
                    cout << "[" << book.title << "] 책을 대여했습니다. 남은 재고: " << stock[book.title] << endl;
                }
                else {
                    cout << "[" << book.title << "] 책은 현재 모두 대여 중입니다." << endl;
                }
                return;
            }
        }
        cout << author << " 작가의 책이 없습니다." << endl;
    }

    // 반납 처리
    void returnBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << "'" << title << "' 책을 반납했습니다. 현재 재고: " << stock[title] << endl;
        }
        else {
            cout << "'" << title << "' 책은 존재하지 않아 반납할 수 없습니다." << endl;
        }
    }

    // 모든 책 재고 출력
    void dispalyStock() {
        if (stock.empty()) {
            cout << "등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 재고 목록:" << endl;
        for (const auto& entry : stock) {
            cout << "- " << entry.first << " : " << entry.second << "권 남음" << endl;
        }
    }
};

int main() {
    BookManager manager;

    BorrowManager borrowManager;



    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목 검색" << endl; // 현재 책 목록에 있는 책 제목 검색
        cout << "4. 작가 검색" << endl; // 현재 책 목록에 있는 책 작가 검색
        cout << "5. 책 제목으로 대여" << endl;
        cout << "6. 작가로 대여" << endl;
        cout << "7. 책 반납" << endl;
        cout << "8. 전체 재고 확인" << endl;
        cout << "9. 종료" << endl; // 프로그램 종료
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
            borrowManager.initializeStock(manager.getLastBooks());
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 제목 검색
            // 현재 책 목록에 있는 책 제목을 검색합니다.
            cout << "검색 할 책 제목: ";
            string title;
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title);

            manager.searchByTitle(title);
        }
        else if (choice == 4) {
            // 3번 선택: 작가 검색
            // 현재 책 목록에 있는 책 작가를 검색합니다.
            cout << "검색 할 작가: ";
            string author;
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author);
            
            manager.searchByAuthor(author);
        }
        else if (choice == 5) {
            string title;
            cin.ignore();
            cout << "대여할 책 제목: ";
            getline(cin, title);
            borrowManager.borrowBookByTitle(manager.getBooks(), title);
        }
        else if (choice == 6) {
            string author;
            cin.ignore();
            cout << "대여할 작가 이름: ";
            getline(cin, author);
            borrowManager.borrowBookByAuthor(manager.getBooks(), author);
        }
        else if (choice == 7) {
            string title;
            cin.ignore();
            cout << "반납할 책 제목: ";
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 8) {
            borrowManager.dispalyStock();
        }
        else if (choice == 9) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}