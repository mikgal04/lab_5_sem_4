#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Book {
    std::string id, author, title;
    int pages;

    friend std::istream& operator>>(std::istream& is, Book& book) {
        is >> book.id >> book.author >> book.title >> book.pages;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << book.id << " " << book.author << " " << book.title << " " << book.pages;
        return os;
    }
};

struct Matrix {
    std::vector<std::vector<int>> data;
};

// Функции для работы с книгами
void addBook(std::vector<Book>& books, const Book& newBook) {
    std::string filename = "Book.txt";
    std::ofstream outBook;
    // Открываем файл в режиме добавления, чтобы не стирать существующие записи
    outBook.open(filename, std::ios::app);
    if (!outBook.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
        return;
    }
    books.push_back(newBook);
    outBook << newBook << std::endl;
    outBook.close();
}

void viewBooks() {
    std::string filename = "Book.txt";
    std::vector<Book> books;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Book book;
        while (inFile >> book) {
            books.push_back(book);
        }
        inFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    for (const auto& book : books) {
        std::cout << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }
}

void deleteBook(const std::string& id) {
    std::string filename = "Book.txt";
    std::vector<Book> books;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Book book;
        while (inFile >> book) {
            books.push_back(book);
        }
        inFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    // Удаление книги из списка
    books.erase(std::remove_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; }), books.end());

    // Запись обновленного списка книг обратно в файл
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& book : books) {
            outFile << book << std::endl;
        }
        outFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
    }
}

void searchBook(const std::string& title) {
    std::string filename = "Book.txt";
    std::vector<Book> books;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Book book;
        while (inFile >> book) {
            books.push_back(book);
        }
        inFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) { return book.title == title; });
    if (it != books.end()) {
        std::cout << it->id << " " << it->author << " " << it->title << " " << it->pages << std::endl;
    }
    else {
        std::cout << "Книга не найдена." << std::endl;
    }
}

void editBook(const std::string& id, const Book& updatedBook) {
    std::string filename = "Book.txt";
    std::vector<Book> books;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Book book;
        while (inFile >> book) {
            books.push_back(book);
        }
        inFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return;
    }

    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        *it = updatedBook;
    }
    else {
        std::cout << "Книга с таким ID не найдена." << std::endl;
        return;
    }

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& book : books) {
            outFile << book << std::endl;
        }
        outFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << " для записи" << std::endl;
    }
}

// Функции для работы с матрицами
void writeMatrixToFile(const std::string& filename, const Matrix& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return;
    }

    for (const auto& row : matrix.data) {
        for (int value : row) {
            file << value << ' ';
        }
        file << '\n';
    }

    file.close();
}

Matrix readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return Matrix{};
    }

    Matrix matrix;
    int value;
    while (file >> value) {
        std::vector<int> row;
        row.push_back(value);
        while (file.peek() != '\n' && file >> value) {
            row.push_back(value);
        }
        matrix.data.push_back(row);
    }

    file.close();
    return matrix;
}

// Функция для подсчета количества появлений заданного слова в текстовом файле
int countWordOccurrences(const std::string& filename, const std::string& word) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return -1;
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(word, pos)) != std::string::npos) {
            ++count;
            pos += word.length();
        }
    }

    file.close();
    return count;
}

int main() {
    std::vector<Book> books;
    std::string filename = "books.txt";
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string id, author, title;
        int pages;
        while (file >> id >> author >> title >> pages) {
            books.push_back({ id, author, title, pages });
        }
        file.close();
    }

    int choice;
    std::string input;

    do {
        std::cout << "Select action:\n"
            << "1. Add a book\n"
            << "2. View all books\n"
            << "3. Delete a book\n"
            << "4. Book search\n"
            << "5. Edit a book\n"
            << "6. Count the number of words in the file\n"
            << "7. Exit\n"
            << "Select: ";
        std::cin >> input;

        std::istringstream iss(input);
        if (!(iss >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            return 1; // Завершаем программу с кодом ошибки
        }

        choice = std::stoi(input);

        switch (choice) {
        case 1: {
            Book newBook;
            std::cout << "Enter ID, author, title and number of pages: ";
            std::cin >> newBook.id >> newBook.author >> newBook.title >> newBook.pages;
            addBook(books, newBook);
            break;
        }
        case 2:
            viewBooks();
            break;
        case 3: {
            std::string id;
            std::cout << "Enter the book ID to delete: ";
            std::cin >> id;
            deleteBook(id);
            break;
        }
        case 4: {
            std::string title;
            std::cout << "Enter the title of the book to search: ";
            std::cin >> title;
            searchBook(title);
            break;
        }
        case 5: {
            std::string id;
            Book updatedBook;
            std::cout << "Enter the book ID to edit: ";
            std::cin >> id;
            std::cout << "Enter new data: ";
            std::cin >> updatedBook.id >> updatedBook.author >> updatedBook.title >> updatedBook.pages;
            editBook(id, updatedBook);
            break;
        }
        case 6: {
            std::string filename, word;
            std::cout << "Enter the file name and search word: ";
            std::cin >> filename >> word;
            int occurrences = countWordOccurrences(filename, word);
            std::cout << "Word '" << word << " meets " << occurrences << " number of times." << std::endl;
            break;
        }
        case 7:
            std::cout << "Exit the program." << std::endl;
            break;
        default:
            std::cout << "Wrong choice. Try again." << std::endl;
            break;
        }
    } while (choice != 7);

    return 0;
}