#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

class BookRecord
{
public:
    int id;
    string title;
    string author;
    int borrowedCount;
    int copiesInStock;

    BookRecord(int i = 0, string t = "", string a = "", int copies = 0, int borrowedCnt = 0)
        : id(i), title(t), author(a), copiesInStock(copies), borrowedCount(borrowedCnt) {}
};

class MemberRecord
{
public:
    int memberId;
    string firstName;
    string lastName;
    int birthYear;
    vector<int> borrowedBookIds;

    MemberRecord(int id = 0, string fn = "", string ln = "", int by = 0)
        : memberId(id), firstName(fn), lastName(ln), birthYear(by) {}
};

class LibraryManager
{
private:
    vector<BookRecord> bookList;
    vector<MemberRecord> memberList;

public:
    void persistData()
    {
        ofstream booksOut("books.txt"), membersOut("members.txt");

        for (auto &memberItem : memberList)
        {
            membersOut << memberItem.memberId << "|" << memberItem.firstName << "|" << memberItem.lastName << "|" << memberItem.birthYear;
            for (auto &borrowedId : memberItem.borrowedBookIds)
                membersOut << "," << borrowedId;
            membersOut << "\n";
        }

        for (auto &bookItem : bookList)
            booksOut << bookItem.id << "|" << bookItem.title << "|" << bookItem.author << "|" << bookItem.copiesInStock << "|" << bookItem.borrowedCount << "\n";
    }

    void restoreData()
    {
        bookList.clear();
        memberList.clear();
        ifstream booksIn("books.txt"), membersIn("members.txt");
        string recordLine;

        while (getline(membersIn, recordLine))
        {
            int birthYearParsed;
            size_t sep1 = recordLine.find("|"), sep2 = recordLine.find("|", sep1 + 1), sep3 = recordLine.find("|", sep2 + 1);
            int memberIdParsed = stoi(recordLine.substr(0, sep1));
            string firstNameParsed = recordLine.substr(sep1 + 1, sep2 - sep1 - 1);
            string lastNameParsed = recordLine.substr(sep2 + 1, sep3 - sep2 - 1);
            size_t posComma = recordLine.find(",", sep3 + 1);
            if (posComma == string::npos)
            {
                birthYearParsed = stoi(recordLine.substr(sep3 + 1));
            }
            else
            {
                birthYearParsed = stoi(recordLine.substr(sep3 + 1, posComma - sep3 - 1));
            }

            MemberRecord memberParsed(memberIdParsed, firstNameParsed, lastNameParsed, birthYearParsed);

            while (posComma != string::npos)
            {
                size_t nextComma = recordLine.find(",", posComma + 1);
                memberParsed.borrowedBookIds.push_back(stoi(recordLine.substr(posComma + 1, nextComma - posComma - 1)));
                posComma = nextComma;
            }
            memberList.push_back(memberParsed);
        }

        while (getline(booksIn, recordLine))
        {
            size_t sep1 = recordLine.find("|"), sep2 = recordLine.find("|", sep1 + 1), sep3 = recordLine.find("|", sep2 + 1), sep4 = recordLine.find("|", sep3 + 1);
            int bookIdParsed = stoi(recordLine.substr(0, sep1));
            string bookTitleParsed = recordLine.substr(sep1 + 1, sep2 - sep1 - 1);
            string bookAuthorParsed = recordLine.substr(sep2 + 1, sep3 - sep2 - 1);
            int copiesInStockParsed = stoi(recordLine.substr(sep3 + 1, sep4 - sep3 - 1));
            int borrowedCountParsed = stoi(recordLine.substr(sep4 + 1));
            bookList.push_back(BookRecord(bookIdParsed, bookTitleParsed, bookAuthorParsed, copiesInStockParsed, borrowedCountParsed));
        }
    }

    int getCurrentYear()
    {
        time_t t = time(nullptr);
        tm *currentTime = localtime(&t);
        return currentTime->tm_year + 1900;
    }

    int findMemberIndex(int searchMemberId)
    {
        for (int idx = 0; idx < memberList.size(); idx++)
            if (memberList[idx].memberId == searchMemberId)
                return idx;
        return -1;
    }

    int findBookIndex(int searchBookId)
    {
        for (int idx = 0; idx < bookList.size(); idx++)
            if (bookList[idx].id == searchBookId)
                return idx;
        return -1;
    }

    void validateInput(const string &prompt, auto &input, const string &errorMsg)
    {
    start:
        cout << prompt;
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg << "\n";
            goto start;
        }
    }

    void registerMember()
    {
        int memberIdInput, birthYearInput;
        string firstNameInput, lastNameInput;

    enter_member_id:
        validateInput("Membership number: ", memberIdInput, "Invalid input! Please enter a valid membership number.");
        if (findMemberIndex(memberIdInput) != -1)
        {
            cout << "This membership number is already registered!\n";
            goto enter_member_id;
        }
        if (memberIdInput < 0)
        {
            cout << "Invalid membership number!\n";
            goto enter_member_id;
        }
        if (memberList.size() >= 100)
        {
            cout << "Member limit reached! Cannot register more members.\n";
            return;
        }
        if (memberIdInput == 0)
        {
            return;
        }

    enter_first_name:
        validateInput("First name: ", firstNameInput, "Invalid input! Please enter a valid first name.");
        if (firstNameInput.empty())
        {
            cout << "First name cannot be empty!\n";
            goto enter_first_name;
        }
        if (firstNameInput == "0")
        {
            return;
        }

    enter_last_name:
        validateInput("Last name: ", lastNameInput, "Invalid input! Please enter a valid last name.");
        if (lastNameInput.empty())
        {
            cout << "Last name cannot be empty!\n";
            goto enter_last_name;
        }
        if (lastNameInput == "0")
        {
            return;
        }

    enter_birth_year:
        validateInput("Year of birth: ", birthYearInput, "Invalid input! Please enter a valid birth year.");
        if (birthYearInput < 1900 || birthYearInput > getCurrentYear())
        {
            cout << "Invalid birth year!\n";
            goto enter_birth_year;
        }
        if (birthYearInput > getCurrentYear() - 18)
        {
            cout << "Member must be at least 18 years old!\n";
            goto enter_birth_year;
        }
        if (birthYearInput == 0)
        {
            return;
        }

        memberList.push_back(MemberRecord(memberIdInput, firstNameInput, lastNameInput, birthYearInput));
        persistData();
    }

    void registerBook()
    {
        int bookIdInput, copiesInput;
        string bookTitleInput, bookAuthorInput;

    enter_book_id:
        validateInput("Book ID: ", bookIdInput, "Invalid input! Please enter a valid book ID.");
        if (findBookIndex(bookIdInput) != -1)
        {
            cout << "This book ID is already registered!\n";
            goto enter_book_id;
        }
        if (bookIdInput < 0)
        {
            cout << "Invalid book ID!\n";
            goto enter_book_id;
        }
        if (bookIdInput == 0)
        {
            return;
        }

        validateInput("Book name: ", bookTitleInput, "Invalid input! Please enter a valid book name.");
        if (bookTitleInput == "0")
        {
            return;
        }

        validateInput("Author's name: ", bookAuthorInput, "Invalid input! Please enter a valid author's name.");
        if (bookAuthorInput == "0")
        {
            return;
        }

    enter_copies:
        validateInput("Number of copies: ", copiesInput, "Invalid input! Please enter a valid number of copies.");
        if (bookIdInput < 0)
        {
            cout << "Number of copies must be greater than zero!\n";
            goto enter_copies;
        }
        if (copiesInput == 0)
        {
            return;
        }

        bookList.push_back(BookRecord(bookIdInput, bookTitleInput, bookAuthorInput, 0, copiesInput));
        persistData();
    }

    void checkoutBook()
    {
        int memberIdInput, bookIdInput;
        cout << "Membership number: ";
        cin >> memberIdInput;
        int memberIndex = findMemberIndex(memberIdInput);
        if (memberIndex == -1)
        {
            cout << "Member not found!\n";
            return;
        }
        if (memberList[memberIndex].borrowedBookIds.size() >= 3)
        {
            cout << "You cannot borrow more than 3 books.!\n";
            return;
        }

        cout << "Book ID: ";
        cin >> bookIdInput;
        int bookIndex = findBookIndex(bookIdInput);
        if (bookIndex == -1)
        {
            cout << "Book not found!\n";
            return;
        }
        if (bookList[bookIndex].borrowedCount >= bookList[bookIndex].copiesInStock)
        {
            cout << "No copies available for this book!\n";
            return;
        }
        bookList[bookIndex].borrowedCount++;
        memberList[memberIndex].borrowedBookIds.push_back(bookIdInput);
        persistData();
        cout << "The book was loaned..\n";
    }

    void checkinBook()
    {
        int memberIdInput, bookIdInput;
        cout << "Membership number: ";
        cin >> memberIdInput;
        int memberIndex = findMemberIndex(memberIdInput);
        if (memberIndex == -1)
        {
            cout << "Member not found!\n";
            return;
        }

        cout << "Book ID: ";
        cin >> bookIdInput;
        int bookIndex = findBookIndex(bookIdInput);
        if (bookIndex == -1)
        {
            cout << "Book not found!\n";
            return;
        }
        auto &bookRecord = bookList[bookIndex];
        if (bookRecord.borrowedCount <= 0)
        {
            cout << "Error: No borrowed copies to return for this book!\n";
            return;
        }
        bookRecord.borrowedCount--;
        auto &borrowedVec = memberList[memberIndex].borrowedBookIds;
        borrowedVec.erase(remove(borrowedVec.begin(), borrowedVec.end(), bookIdInput), borrowedVec.end());
        persistData();
        cout << "The book was returned..\n";
    }

    void printMembers()
    {
        for (auto &memberItem : memberList)
        {
            cout << memberItem.memberId << " - " << memberItem.firstName << " " << memberItem.lastName << " | Books: ";
            for (auto &borrowedId : memberItem.borrowedBookIds)
                cout << borrowedId << ", ";
            cout << "\n";
        }
    }

    void printBooks()
    {
        for (auto &bookItem : bookList)
        {
            int availableCopies = bookItem.copiesInStock - bookItem.borrowedCount;
            cout << bookItem.id << " - " << bookItem.title << " | " << bookItem.author << " (" << availableCopies << " copies left)" << "\n";
        }
    }

    void findMemberByFirstName()
    {
        string searchFirstName;
        cin.ignore();
        cout << "First name: ";
        getline(cin, searchFirstName);
        bool found = false;
        for (auto &memberItem : memberList)
            if (memberItem.firstName == searchFirstName)
            {
                cout << memberItem.memberId << " - " << memberItem.firstName << " " << memberItem.lastName << "\n";
                found = true;
            }
        if (!found)
        {
            cout << "No member found with the first name '" << searchFirstName << "'.\n";
        }
    }

    void findBookByTitle()
    {
        string searchTitle;
        cin.ignore();
        cout << "Book name: ";
        getline(cin, searchTitle);
        bool found = false;
        for (auto &bookItem : bookList)
            if (bookItem.title == searchTitle)
            {
                int availableCopies = bookItem.copiesInStock - bookItem.borrowedCount;
                cout << bookItem.id << " - " << bookItem.title << " | " << bookItem.author << " (" << availableCopies << "copies left)" << "\n";
                found = true;
            }
        if (!found)
        {
            cout << "No book found with the title '" << searchTitle << "'.\n";
        }
    }

    void run()
    {
        restoreData();
        int menuChoice;
        while (true)
        {
            cout << "\n===== Main Menu =====\n";
            cout << "1. Register Member\n";
            cout << "2. Register Book\n";
            cout << "3. Checkout Book\n";
            cout << "4. Checkin Book\n";
            cout << "5. Print Members\n";
            cout << "6. Print Books\n";
            cout << "7. Find Member by First Name\n";
            cout << "8. Find Book by Title\n";
            cout << "0. Exit\n";
            cout << "Select an option: ";
            cin >> menuChoice;
            switch (menuChoice)
            {
            case 1:
                registerMember();
                break;
            case 2:
                registerBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                checkinBook();
                break;
            case 5:
                printMembers();
                break;
            case 6:
                printBooks();
                break;
            case 7:
                findMemberByFirstName();
                break;
            case 8:
                findBookByTitle();
                break;
            case 0:
                persistData();
                return;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        }
    }
};

int main()
{
    LibraryManager lib;
    lib.run();
}
