#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

class User;

char* duplicateText(const char* text) {
    if (!text) {
        throw std::invalid_argument("null text");
    }

    size_t length = std::strlen(text);
    char* copy = new char[length + 1];
    std::strcpy(copy, text);
    return copy;
}

class Book {
public:
    Book()
        : id(nextId++), title(nullptr), author(nullptr), available(true), borrowedBy(nullptr) {
        setTitle("Untitled");
        setAuthor("Unknown");
    }

    Book(const char* title, const char* author)
        : id(nextId++), title(nullptr), author(nullptr), available(true), borrowedBy(nullptr) {
        setTitle(title);
        setAuthor(author);
    }

    Book(const Book& other)
        : id(nextId++), title(nullptr), author(nullptr), available(other.available), borrowedBy(other.borrowedBy) {
        setTitle(other.title);
        setAuthor(other.author);
    }

    Book& operator=(const Book& other) {
        if (this != &other) {
            setTitle(other.title);
            setAuthor(other.author);
            available = other.available;
            borrowedBy = other.borrowedBy;
        }
        return *this;
    }

    ~Book() {
        delete[] title;
        delete[] author;
    }

    unsigned getId() const {
        return id;
    }

    const char* getTitle() const {
        return title;
    }

    const char* getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    User* getBorrowedBy() const {
        return borrowedBy;
    }

    void setTitle(const char* newTitle) {
        char* copy = duplicateText(newTitle);
        delete[] title;
        title = copy;
    }

    void setAuthor(const char* newAuthor) {
        char* copy = duplicateText(newAuthor);
        delete[] author;
        author = copy;
    }

    void borrow(const User& user);

    void returnBook() {
        if (available) {
            throw std::runtime_error("book already available");
        }

        available = true;
        borrowedBy = nullptr;
    }

    void printInfo() const {
        std::cout << id << " | " << title << " | " << author << " | ";
        std::cout << (available ? "available" : "borrowed");
        if (borrowedBy != nullptr) {
            std::cout << " | borrowed by user";
        }
        std::cout << '\n';
    }

private:
    static unsigned nextId;

    const unsigned id;
    char* title;
    char* author;
    bool available;
    User* borrowedBy;
};

class User {
public:
    User()
        : User("user", "0000000000") {
    }

    User(const char* username, const char* phone)
        : username(nullptr), phone(nullptr) {
        setUsername(username);
        setPhone(phone);
    }

    User(const User& other)
        : username(nullptr), phone(nullptr) {
        setUsername(other.username);
        setPhone(other.phone);
    }

    User& operator=(const User& other) {
        if (this != &other) {
            setUsername(other.username);
            setPhone(other.phone);
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] phone;
    }

    const char* getUsername() const {
        return username;
    }

    const char* getPhone() const {
        return phone;
    }

    void setUsername(const char* newUsername) {
        if (std::strlen(newUsername) > 8) {
            throw std::runtime_error("username too long");
        }

        char* copy = duplicateText(newUsername);
        delete[] username;
        username = copy;
    }

    void setPhone(const char* newPhone) {
        if (std::strlen(newPhone) > 10) {
            throw std::runtime_error("phone too long");
        }

        char* copy = duplicateText(newPhone);
        delete[] phone;
        phone = copy;
    }

private:
    char* username;
    char* phone;
};

unsigned Book::nextId = 0;

void Book::borrow(const User& user) {
    if (!available) {
        throw std::runtime_error("book already borrowed");
    }

    available = false;
    borrowedBy = (User*)(&user);
}

class Library {
public:
    Library()
        : count(0) {
        for (size_t index = 0; index < 50; ++index) {
            books[index] = nullptr;
        }
    }

    Library(const Library& other)
        : count(0) {
        for (size_t index = 0; index < 50; ++index) {
            books[index] = nullptr;
        }

        for (size_t index = 0; index < other.count; ++index) {
            books[index] = new Book(*other.books[index]);
        }
        count = other.count;
    }

    Library& operator=(Library other) {
        swap(other);
        return *this;
    }

    ~Library() {
        clear();
    }

    size_t getCount() const {
        return count;
    }

    void addBook(const char* title, const char* author) {
        if (count == 50) {
            throw std::runtime_error("library is full");
        }

        books[count++] = new Book(title, author);
    }

    void borrowBook(unsigned bookId, const User& user) {
        Book* book = findBook(bookId);
        if (book == nullptr) {
            throw std::runtime_error("book not found");
        }

        book->borrow(user);
    }

    void returnBook(unsigned bookId) {
        Book* book = findBook(bookId);
        if (book == nullptr) {
            throw std::runtime_error("book not found");
        }

        book->returnBook();
    }

    void printInfo() const {
        for (size_t index = 0; index < count; ++index) {
            books[index]->printInfo();
        }
    }

private:
    Book* findBook(unsigned bookId) const {
        for (size_t index = 0; index < count; ++index) {
            if (books[index]->getId() == bookId) {
                return books[index];
            }
        }
        return nullptr;
    }

    void clear() {
        for (size_t index = 0; index < count; ++index) {
            delete books[index];
            books[index] = nullptr;
        }
        count = 0;
    }

    void swap(Library& other) noexcept {
        for (size_t index = 0; index < 50; ++index) {
            std::swap(books[index], other.books[index]);
        }
        std::swap(count, other.count);
    }

    Book* books[50];
    size_t count;
};

int main() {
    try {
        Library library;
        User u1("ivo", "0888123456");
        User u2("maria", "0888000000");

        library.addBook("Clean Code", "Robert Martin");
        library.addBook("The Pragmatic Programmer", "Andrew Hunt");
        library.printInfo();

        library.borrowBook(0, u1);
        std::cout << "After borrowing book 0:\n";
        library.printInfo();

        try {
            library.borrowBook(0, u2);
        } catch (const std::exception& ex) {
            std::cout << "Expected error: " << ex.what() << '\n';
        }

        library.returnBook(0);
        std::cout << "After return:\n";
        library.printInfo();
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
