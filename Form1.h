#pragma once
#include <queue>
#include <list>
#include <vector>
#include <climits>
#include <algorithm>
#include <iterator>

struct Person {
	std::string name;
	Person(std::string person_name)
		: name(person_name)
	{
	};
	Person() {};
};

struct Book {
	std::string title;
	std::string author;
	std::string isbn;
	Person borrower;
	std::queue<Person> waitlist;
	Book(std::string title_in, std::string author_in, std::string isbn_in)
		: title(title_in), author(author_in), isbn(isbn_in)
	{
	};
	Book() {};
	bool operator==(const Book& other)
	{
		if ((this->title == other.title) && (this->author == other.author) && (this->isbn == other.isbn))
			return true;
		return false;
	}
};

//Array of Vectors & Associated Parts
std::vector<Book*> authors[2503];
std::vector<Book*> titles[2503];
std::vector<Book*> isbns[2503];

std::vector<Book*> searchResults1;
std::vector<Book*> searchResults2;
std::vector<Book*> searchResults3;

int hashFunc(std::string in) {
	//Just a standard hash function
	int out = 0;

	for (char a : in) {
		out += a;
	}
	return out % 2503;
}

void insert(Book* in) {
	//Takes a pointer to a book.
	//Gets indicies for the Author, Title, and ISBN. Then inserts the pointer at the correct indicies.
	int aIndex = hashFunc(in->author);
	int tIndex = hashFunc(in->title);
	int iIndex = hashFunc(in->isbn);

	authors[aIndex].push_back(in);
	titles[tIndex].push_back(in);
	isbns[iIndex].push_back(in);
}

int remove(Book* in) {
	//Takes a pointer to a book.
	//Gets the appropriate indicies for the arrays. Also gets the initial sizes for the vectors.
	//Then, delete the book if it's in the vectors
	//If it's deleted, return 0, if it's not, return 1.
	//If something goes wrong and it's only found in some of them, return 2.
	int aIndex = hashFunc(in->author);
	int tIndex = hashFunc(in->title);
	int iIndex = hashFunc(in->isbn);

	int sizeA = authors[aIndex].size();
	int sizeT = titles[tIndex].size();
	int sizeI = isbns[iIndex].size();

	bool workeda = false;
	bool workedt = false;
	bool workedi = false;
	
	authors[aIndex].erase(find(authors[aIndex].begin(), authors[aIndex].end(), in));
	titles[tIndex].erase(find(titles[tIndex].begin(), titles[tIndex].end(), in));
	isbns[iIndex].erase(find(isbns[iIndex].begin(), isbns[iIndex].end(), in));

	if (sizeA != authors[aIndex].size()) {
		workeda = true;
	}
	if (sizeT != titles[tIndex].size()) {
		workedt = true;
	}
	if (sizeI != isbns[iIndex].size()) {
		workedi = true;
	}

	if (workeda && workedt && workedi) {
		return 0;
	}
	else if (workeda || workedt || workedi) {
		return 2;
	}
	else {
		return 1;
	}

}

// Default Book Initialization

void initializeBooks(std::list<Book>& L) {
	//Takes a list of books. Adds 5 books, use as a starting point.
	//To add more, use the format:
	// 
	//	B = *(new Book("title","author","isbn"));
	//	L.push_back(B);
	// 
	//	insert(&B);
	//

	Book B = *(new Book("Data Structures & Algorithm Analysis in C++ 4th Edition", "Mark Allen Weiss", "978-0-13-284737-7"));
	B.borrower = Person("Bob Smith");

	L.push_back(B);

	insert(&B);

	B = *(new Book("The Merriam-Webster Dictionary (2022)", "N/A", "978-0-87779-095-2"));

	L.push_back(B);

	insert(&B);

	B = *(new Book("Harry Potter and The Sorcerer's Stone", "J.K. Rowling", "978-0590353427"));

	L.push_back(B);

	insert(&B);

	B = *(new Book("C++ for Dummies 6th Edition", "Stephen R. Davis", "978-0470317266"));

	L.push_back(B);

	insert(&B);

	B = *(new Book("Introduction to Analog & Digital Circuits 2nd Edition", "Brian K. Dean & Daniel Llamocca", "978-1-7924-1609-5"));

	L.push_back(B);

	insert(&B);
}


//Checking out & Returning book functions

void queueToList(std::queue<Person> Q, std::list<std::string>& L) {
	//Puts a queue of People into an list, the list is passed by reference, the queue is not.
	//The list is front-to-back. (eg. the first element in the list is the front of the queue)
	while (!Q.empty()) {
		L.push_back(Q.front().name);
		Q.pop();
	}
}

int checkoutBook(Book& B,Person P) {
	//If there isn't currently a borrower, P is the new borrower.
	//Else, add P to the waitlist
	if (B.borrower.name == "") {
		B.borrower = P;
		return 0; // 0 = Borrower Updated
	}
	else {
		B.waitlist.push(P);
		return 1; // 1 = Waitlist Updated
	}
}

int returnBook(Book& B) {
	//If the book is currently in stock, return 0. (Only happens if there isn't a borrower.)
	//Else, if the waitlist is not empty, set the person at the front of the queue
		//as the current borrower. Then, pop the front of the queue. return 1.
	//Else, reset the current borrower. return 1.
	Person none;

	if (B.borrower.name == "") {
		return 0;
	}
	else if(!B.waitlist.empty()){
		B.borrower = B.waitlist.front();
		B.waitlist.pop();

		return 1;
	}
	else {
		B.borrower = none;

		return 1;
	}
}


std::list<Book> currentbooks;

// .NET has a special string type that we need to convert back to standard c++ strings
void MarshalString(String^ s, std::string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ tabControl;
	protected:
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;


	private: System::Windows::Forms::ListBox^ lbBookList1;
	private: System::Windows::Forms::TextBox^ txtISBN;

	private: System::Windows::Forms::TextBox^ txtAuthor;

	private: System::Windows::Forms::TextBox^ txtTitle;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnBookRegister;
	private: System::Windows::Forms::Button^ btnDeleteBook;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ txtISBNLook;
	private: System::Windows::Forms::TextBox^ txtAuthorLook;
	private: System::Windows::Forms::TextBox^ txtTitleLook;
	private: System::Windows::Forms::TextBox^ txtBorrowerLook;
	private: System::Windows::Forms::Label^ label7;






	private: System::Windows::Forms::TextBox^ txtUpNextLook;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ txtISBNSearch1;

	private: System::Windows::Forms::TextBox^ txtAuthorSearch1;

	private: System::Windows::Forms::TextBox^ txtTitleSearch1;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::ListBox^ lbSearchResult1;
	private: System::Windows::Forms::Button^ btnSearch1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ txtPersonName;
	private: System::Windows::Forms::Button^ btnReturnBook;
	private: System::Windows::Forms::Button^ btnBorrowBook;
	private: System::Windows::Forms::TextBox^ txtWaitlistFirst;

	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ txtBorrower;


	private: System::Windows::Forms::Label^ label14;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->txtUpNextLook = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->txtBorrowerLook = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->btnDeleteBook = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txtISBNLook = (gcnew System::Windows::Forms::TextBox());
			this->txtAuthorLook = (gcnew System::Windows::Forms::TextBox());
			this->txtTitleLook = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnBookRegister = (gcnew System::Windows::Forms::Button());
			this->txtISBN = (gcnew System::Windows::Forms::TextBox());
			this->txtAuthor = (gcnew System::Windows::Forms::TextBox());
			this->txtTitle = (gcnew System::Windows::Forms::TextBox());
			this->lbBookList1 = (gcnew System::Windows::Forms::ListBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->txtWaitlistFirst = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->txtBorrower = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->txtPersonName = (gcnew System::Windows::Forms::TextBox());
			this->btnReturnBook = (gcnew System::Windows::Forms::Button());
			this->btnBorrowBook = (gcnew System::Windows::Forms::Button());
			this->lbSearchResult1 = (gcnew System::Windows::Forms::ListBox());
			this->btnSearch1 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->txtISBNSearch1 = (gcnew System::Windows::Forms::TextBox());
			this->txtAuthorSearch1 = (gcnew System::Windows::Forms::TextBox());
			this->txtTitleSearch1 = (gcnew System::Windows::Forms::TextBox());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Location = System::Drawing::Point(12, 12);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(790, 463);
			this->tabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->txtUpNextLook);
			this->tabPage1->Controls->Add(this->label9);
			this->tabPage1->Controls->Add(this->txtBorrowerLook);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->btnDeleteBook);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->txtISBNLook);
			this->tabPage1->Controls->Add(this->txtAuthorLook);
			this->tabPage1->Controls->Add(this->txtTitleLook);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->btnBookRegister);
			this->tabPage1->Controls->Add(this->txtISBN);
			this->tabPage1->Controls->Add(this->txtAuthor);
			this->tabPage1->Controls->Add(this->txtTitle);
			this->tabPage1->Controls->Add(this->lbBookList1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(782, 434);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Book Management";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// txtUpNextLook
			// 
			this->txtUpNextLook->Location = System::Drawing::Point(631, 371);
			this->txtUpNextLook->Name = L"txtUpNextLook";
			this->txtUpNextLook->ReadOnly = true;
			this->txtUpNextLook->Size = System::Drawing::Size(145, 22);
			this->txtUpNextLook->TabIndex = 23;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(550, 374);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(55, 16);
			this->label9->TabIndex = 22;
			this->label9->Text = L"Up Next";
			// 
			// txtBorrowerLook
			// 
			this->txtBorrowerLook->Location = System::Drawing::Point(631, 343);
			this->txtBorrowerLook->Name = L"txtBorrowerLook";
			this->txtBorrowerLook->ReadOnly = true;
			this->txtBorrowerLook->Size = System::Drawing::Size(145, 22);
			this->txtBorrowerLook->TabIndex = 17;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(550, 346);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(61, 16);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Borrower";
			// 
			// btnDeleteBook
			// 
			this->btnDeleteBook->Location = System::Drawing::Point(553, 399);
			this->btnDeleteBook->Name = L"btnDeleteBook";
			this->btnDeleteBook->Size = System::Drawing::Size(223, 28);
			this->btnDeleteBook->TabIndex = 14;
			this->btnDeleteBook->Text = L"Delete Book";
			this->btnDeleteBook->UseVisualStyleBackColor = true;
			this->btnDeleteBook->Click += gcnew System::EventHandler(this, &Form1::btnDeleteBook_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(550, 318);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 16);
			this->label4->TabIndex = 13;
			this->label4->Text = L"ISBN";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(550, 290);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(45, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Author";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(550, 262);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 16);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Title";
			// 
			// txtISBNLook
			// 
			this->txtISBNLook->Location = System::Drawing::Point(631, 315);
			this->txtISBNLook->Name = L"txtISBNLook";
			this->txtISBNLook->ReadOnly = true;
			this->txtISBNLook->Size = System::Drawing::Size(145, 22);
			this->txtISBNLook->TabIndex = 10;
			// 
			// txtAuthorLook
			// 
			this->txtAuthorLook->Location = System::Drawing::Point(631, 287);
			this->txtAuthorLook->Name = L"txtAuthorLook";
			this->txtAuthorLook->ReadOnly = true;
			this->txtAuthorLook->Size = System::Drawing::Size(145, 22);
			this->txtAuthorLook->TabIndex = 9;
			// 
			// txtTitleLook
			// 
			this->txtTitleLook->Location = System::Drawing::Point(631, 259);
			this->txtTitleLook->Name = L"txtTitleLook";
			this->txtTitleLook->ReadOnly = true;
			this->txtTitleLook->Size = System::Drawing::Size(145, 22);
			this->txtTitleLook->TabIndex = 8;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(550, 143);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(38, 16);
			this->label3->TabIndex = 7;
			this->label3->Text = L"ISBN";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(550, 115);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(45, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Author";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(550, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 16);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Title";
			// 
			// btnBookRegister
			// 
			this->btnBookRegister->Location = System::Drawing::Point(550, 168);
			this->btnBookRegister->Name = L"btnBookRegister";
			this->btnBookRegister->Size = System::Drawing::Size(226, 30);
			this->btnBookRegister->TabIndex = 4;
			this->btnBookRegister->Text = L"Register Book";
			this->btnBookRegister->UseVisualStyleBackColor = true;
			this->btnBookRegister->Click += gcnew System::EventHandler(this, &Form1::btnBookRegister_Click);
			// 
			// txtISBN
			// 
			this->txtISBN->Location = System::Drawing::Point(631, 140);
			this->txtISBN->Name = L"txtISBN";
			this->txtISBN->Size = System::Drawing::Size(145, 22);
			this->txtISBN->TabIndex = 3;
			// 
			// txtAuthor
			// 
			this->txtAuthor->Location = System::Drawing::Point(631, 112);
			this->txtAuthor->Name = L"txtAuthor";
			this->txtAuthor->Size = System::Drawing::Size(145, 22);
			this->txtAuthor->TabIndex = 2;
			// 
			// txtTitle
			// 
			this->txtTitle->Location = System::Drawing::Point(631, 84);
			this->txtTitle->Name = L"txtTitle";
			this->txtTitle->Size = System::Drawing::Size(145, 22);
			this->txtTitle->TabIndex = 1;
			// 
			// lbBookList1
			// 
			this->lbBookList1->FormattingEnabled = true;
			this->lbBookList1->ItemHeight = 16;
			this->lbBookList1->Location = System::Drawing::Point(7, 7);
			this->lbBookList1->Name = L"lbBookList1";
			this->lbBookList1->Size = System::Drawing::Size(232, 420);
			this->lbBookList1->TabIndex = 0;
			this->lbBookList1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lbBookList1_SelectedIndexChanged);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->txtWaitlistFirst);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->txtBorrower);
			this->tabPage2->Controls->Add(this->label14);
			this->tabPage2->Controls->Add(this->label8);
			this->tabPage2->Controls->Add(this->txtPersonName);
			this->tabPage2->Controls->Add(this->btnReturnBook);
			this->tabPage2->Controls->Add(this->btnBorrowBook);
			this->tabPage2->Controls->Add(this->lbSearchResult1);
			this->tabPage2->Controls->Add(this->btnSearch1);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Controls->Add(this->label11);
			this->tabPage2->Controls->Add(this->label10);
			this->tabPage2->Controls->Add(this->txtISBNSearch1);
			this->tabPage2->Controls->Add(this->txtAuthorSearch1);
			this->tabPage2->Controls->Add(this->txtTitleSearch1);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(782, 434);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Borrow & Return";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// txtWaitlistFirst
			// 
			this->txtWaitlistFirst->Location = System::Drawing::Point(631, 304);
			this->txtWaitlistFirst->Name = L"txtWaitlistFirst";
			this->txtWaitlistFirst->ReadOnly = true;
			this->txtWaitlistFirst->Size = System::Drawing::Size(145, 22);
			this->txtWaitlistFirst->TabIndex = 35;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(550, 307);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(55, 16);
			this->label13->TabIndex = 34;
			this->label13->Text = L"Up Next";
			// 
			// txtBorrower
			// 
			this->txtBorrower->Location = System::Drawing::Point(631, 276);
			this->txtBorrower->Name = L"txtBorrower";
			this->txtBorrower->ReadOnly = true;
			this->txtBorrower->Size = System::Drawing::Size(145, 22);
			this->txtBorrower->TabIndex = 33;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(550, 279);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(61, 16);
			this->label14->TabIndex = 32;
			this->label14->Text = L"Borrower";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(550, 338);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(50, 16);
			this->label8->TabIndex = 25;
			this->label8->Text = L"Person";
			// 
			// txtPersonName
			// 
			this->txtPersonName->Location = System::Drawing::Point(606, 335);
			this->txtPersonName->Name = L"txtPersonName";
			this->txtPersonName->Size = System::Drawing::Size(170, 22);
			this->txtPersonName->TabIndex = 24;
			// 
			// btnReturnBook
			// 
			this->btnReturnBook->Location = System::Drawing::Point(553, 397);
			this->btnReturnBook->Name = L"btnReturnBook";
			this->btnReturnBook->Size = System::Drawing::Size(223, 28);
			this->btnReturnBook->TabIndex = 23;
			this->btnReturnBook->Text = L"Return Book";
			this->btnReturnBook->UseVisualStyleBackColor = true;
			// 
			// btnBorrowBook
			// 
			this->btnBorrowBook->Location = System::Drawing::Point(553, 363);
			this->btnBorrowBook->Name = L"btnBorrowBook";
			this->btnBorrowBook->Size = System::Drawing::Size(223, 28);
			this->btnBorrowBook->TabIndex = 22;
			this->btnBorrowBook->Text = L"Borrow Book";
			this->btnBorrowBook->UseVisualStyleBackColor = true;
			this->btnBorrowBook->Click += gcnew System::EventHandler(this, &Form1::btnBorrowBook_Click);
			// 
			// lbSearchResult1
			// 
			this->lbSearchResult1->FormattingEnabled = true;
			this->lbSearchResult1->ItemHeight = 16;
			this->lbSearchResult1->Location = System::Drawing::Point(10, 40);
			this->lbSearchResult1->Name = L"lbSearchResult1";
			this->lbSearchResult1->Size = System::Drawing::Size(283, 388);
			this->lbSearchResult1->TabIndex = 7;
			this->lbSearchResult1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lbSearchResult1_SelectedIndexChanged);
			// 
			// btnSearch1
			// 
			this->btnSearch1->Location = System::Drawing::Point(634, 7);
			this->btnSearch1->Name = L"btnSearch1";
			this->btnSearch1->Size = System::Drawing::Size(142, 23);
			this->btnSearch1->TabIndex = 6;
			this->btnSearch1->Text = L"Search";
			this->btnSearch1->UseVisualStyleBackColor = true;
			this->btnSearch1->Click += gcnew System::EventHandler(this, &Form1::btnSearch1_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(437, 10);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(38, 16);
			this->label12->TabIndex = 5;
			this->label12->Text = L"ISBN";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(219, 10);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(45, 16);
			this->label11->TabIndex = 4;
			this->label11->Text = L"Author";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(7, 7);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(33, 16);
			this->label10->TabIndex = 3;
			this->label10->Text = L"Title";
			// 
			// txtISBNSearch1
			// 
			this->txtISBNSearch1->Location = System::Drawing::Point(494, 7);
			this->txtISBNSearch1->Name = L"txtISBNSearch1";
			this->txtISBNSearch1->Size = System::Drawing::Size(125, 22);
			this->txtISBNSearch1->TabIndex = 2;
			// 
			// txtAuthorSearch1
			// 
			this->txtAuthorSearch1->Location = System::Drawing::Point(293, 7);
			this->txtAuthorSearch1->Name = L"txtAuthorSearch1";
			this->txtAuthorSearch1->Size = System::Drawing::Size(125, 22);
			this->txtAuthorSearch1->TabIndex = 1;
			// 
			// txtTitleSearch1
			// 
			this->txtTitleSearch1->Location = System::Drawing::Point(65, 7);
			this->txtTitleSearch1->Name = L"txtTitleSearch1";
			this->txtTitleSearch1->Size = System::Drawing::Size(125, 22);
			this->txtTitleSearch1->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(814, 487);
			this->Controls->Add(this->tabControl);
			this->Name = L"Form1";
			this->Text = L"Library Management System";
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		int selectedBookIndex = -1;
		int selectedSearchIndex = -1;
	private: System::Void lbBookList1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// Our index represents how far we need to go into the linked list to access the book.
		int index = 0;
		selectedBookIndex = this->lbBookList1->SelectedIndex; // Useful to quickly delete books
		for (Book book : currentbooks) { // Go through the books until we find our book
			if (index == this->lbBookList1->SelectedIndex) {
				this->txtTitleLook->Text = gcnew String(book.title.c_str());
				this->txtAuthorLook->Text = gcnew String(book.author.c_str());
				this->txtISBNLook->Text = gcnew String(book.isbn.c_str());
				this->txtBorrowerLook->Text = gcnew String(book.borrower.name.c_str());
				if (!book.waitlist.empty()) {
					this->txtUpNextLook->Text = gcnew String(book.waitlist.front().name.c_str());
				}
				else {
					this->txtUpNextLook->Text = "";
				}
				break;
			}	
			index++;
		}
	}
	private: System::Void btnBookRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		// Define our Book
		std::string title, author, isbn; 
		MarshalString(this->txtTitle->Text, title); // Convert System::String to std::string
		MarshalString(this->txtAuthor->Text, author);
		MarshalString(this->txtISBN->Text, isbn);
		Book* newBook = new Book; // Intentionally carve out some memory for this book, otherwise the values get all messed up later!
		newBook->title = title;
		newBook->author = author;
		newBook->isbn = isbn;
		currentbooks.push_front(*newBook);
		insert(newBook);
		// Refresh the Book list
		this->lbBookList1->Items->Clear();
		for (Book book : currentbooks) {
			System::String^ name = gcnew String(book.title.c_str()); // And then we go back
			this->lbBookList1->Items->Add(name);
		}
	}
	private: System::Void btnDeleteBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!currentbooks.empty() && selectedBookIndex >= 0) {
			std::list<Book>::iterator it;
			it = currentbooks.begin();
			advance(it, selectedBookIndex);
			// This looks weird, let me explain....
			// This is the pointer, to the dereferenced iterator which gives us the book, 
			// which gives us the pointer to the book
			remove(&(*it));
			currentbooks.erase(it);
			// Refresh the Book list
			this->lbBookList1->Items->Clear();
			for (Book book : currentbooks) {
				System::String^ name = gcnew String(book.title.c_str()); // And then we go back
				this->lbBookList1->Items->Add(name);
			}
			this->txtTitleLook->Text = "";
			this->txtAuthorLook->Text = "";
			this->txtISBNLook->Text = "";
			this->txtBorrowerLook->Text = "";
			this->txtUpNextLook->Text = "";
			selectedBookIndex = -1; // Set our book index to -1 so we know that we have to click again
		}
	}
	private: System::Void btnBorrowBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!searchResults1.empty() && selectedSearchIndex >= 0 && this->txtPersonName->Text != "") {
			// Get to our specific book
			Book* book = searchResults1[selectedSearchIndex];
			std::string name;
			MarshalString(this->txtPersonName->Text, name);
			Person person(name);
			if (checkoutBook(*book, person)) { // Is the waitlist updated?
				Person upnext = book->waitlist.front();
				System::String^ person_name = gcnew String(upnext.name.c_str());
				this->txtWaitlistFirst->Text = person_name;
			}
			else {
				System::String^ person_name = gcnew String(book->borrower.name.c_str());
				this->txtBorrower->Text = person_name;
			}
		}
	}
	private: System::Void btnReturnBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!searchResults1.empty() && selectedBookIndex >= 0) {
			// Get to our specific book
			Book* book = searchResults1[selectedSearchIndex];
			if (returnBook(*book)) { // Did anything change when we tried to return the book?
				if (!book->waitlist.empty()) {
					System::String^ person_name = gcnew String(book->waitlist.front().name.c_str());
					this->txtUpNextLook->Text = person_name;
				}
				else {
					this->txtUpNextLook->Text = "";
				}
				this->txtBorrowerLook->Text = gcnew String(book->borrower.name.c_str());
			}
		}
	}
	private: System::Void btnSearch1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->lbSearchResult1->Items->Clear();
		this->txtBorrower->Text = "";
		this->txtWaitlistFirst->Text = "";
		searchResults1.clear();
		std::string title, author, isbn;
		MarshalString(this->txtTitleSearch1->Text, title); // Convert System::String to std::string
		MarshalString(this->txtAuthorSearch1->Text, author);
		MarshalString(this->txtISBNSearch1->Text, isbn);
		int aIndex = -1, tIndex = -1, iIndex = -1;
		// If all three entries are empty, just return
		if (title == "" && author == "" && isbn == "")
			return;
		// Find our hash indices
		if (author != "")
			aIndex = hashFunc(author);
		if (title != "")
			tIndex = hashFunc(title);
		if (isbn != "")
			iIndex = hashFunc(isbn);
		// Determine the length of the results, and use that as our comparison table
		int smallestTable = -1; // 1 = author, 2 = title, 3 = isbn
		std::vector<Book*> *smallTable;
		int aSize = INT_MAX, tSize = INT_MAX, iSize = INT_MAX;
		if (aIndex != -1)
			aSize = authors[aIndex].size();
		if (tIndex != -1)
			tSize = titles[tIndex].size();
		if (iIndex != -1)
			iSize = isbns[iIndex].size();
		// If we find that all of our sizes are not updated, just return
		if (aSize == INT_MAX && tSize == INT_MAX && iSize == INT_MAX)
			return;
		int smallestSize = std::min({ aSize, tSize, iSize });
		if (aSize == smallestSize) {
			smallestTable = 1;
			smallTable = &authors[aIndex];
		}
		if (tSize == smallestSize) {
			smallestTable = 2;
			smallTable = &titles[tIndex];
		}
		if (iSize == smallestSize) {
			smallestTable = 3;
			smallTable = &isbns[iIndex];
		}
		// Now, we begin to add results
		std::vector<Book*> temp1;
		std::vector<Book*> temp2;
		if (smallestTable == 1) { // We start with the authors
			if (tIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : titles[tIndex]) {
						if (*bookA == *bookB)
							temp1.push_back(bookA);
					}
				}
			}
			if (iIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : isbns[iIndex]) {
						if (*bookA == *bookB)
							temp2.push_back(bookA);
					}
				}
			}
			if (temp1.size() != 0 && temp2.size() != 0) {
				for (Book* bookA : temp1) {
					for (Book* bookB : temp2) {
						if (*bookA == *bookB)
							searchResults1.push_back(bookA);
					}
				}
			}
			else if (temp1.size() != 0) {
				for (Book* book : temp1) {
					searchResults1.push_back(book);
				}
			}
			else if (temp2.size() != 0) {
				for (Book* book : temp2) {
					searchResults1.push_back(book);
				}
			}
			else { // It looks like we only filled out an author
				for (Book* book : *smallTable) {
					searchResults1.push_back(book);
				}
			}
		}
		else if (smallestTable == 2) { // We start with the title
			if (aIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : authors[aIndex]) {
						if (*bookA == *bookB)
							temp1.push_back(bookA);
					}
				}
			}
			if (iIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : isbns[iIndex]) {
						if (*bookA == *bookB)
							temp2.push_back(bookA);
					}
				}
			}
			if (temp1.size() != 0 && temp2.size() != 0) {
				for (Book* bookA : temp1) {
					for (Book* bookB : temp2) {
						if (*bookA == *bookB)
							searchResults1.push_back(bookA);
					}
				}
			}
			else if (temp1.size() != 0) {
				for (Book* book : temp1) {
					searchResults1.push_back(book);
				}
			}
			else if (temp2.size() != 0) {
				for (Book* book : temp2) {
					searchResults1.push_back(book);
				}
			}
			else { // It looks like we only filled out a title
				for (Book* book : *smallTable) {
					searchResults1.push_back(book);
				}
			}
		}
		else if (smallestTable == 3) { // We start with the ISBN
			if (aIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : authors[aIndex]) {
						if (*bookA == *bookB)
							temp1.push_back(bookA);
					}
				}
			}
			if (tIndex != -1) {
				for (Book* bookA : *smallTable) {
					for (Book* bookB : titles[tIndex]) {
						if (*bookA == *bookB)
							temp2.push_back(bookA);
					}
				}
			}
			if (temp1.size() != 0 && temp2.size() != 0) {
				for (Book* bookA : temp1) {
					for (Book* bookB : temp2) {
						if (*bookA == *bookB)
							searchResults1.push_back(bookA);
					}
				}
			}
			else if (temp1.size() != 0) {
				for (Book* book : temp1) {
					searchResults1.push_back(book);
				}
			}
			else if (temp2.size() != 0) {
				for (Book* book : temp2) {
					searchResults1.push_back(book);
				}
			}
			else { // It looks like we only filled out an isbn
				for (Book* book : *smallTable) {
					searchResults1.push_back(book);
				}
			}
		}
		// At last, we place the results into our list box
		for (Book* book : searchResults1) {
			std::string cname = book->title.c_str();
			System::String^ name = gcnew String(book->title.c_str()); // And then we go back
			this->lbSearchResult1->Items->Add(name);
		}
	}
	private: System::Void lbSearchResult1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// Our index represents how far we need to go into the list to access the book.
		int index = 0;
		selectedSearchIndex = this->lbSearchResult1->SelectedIndex; // Useful to quickly delete books
		for (Book* book : searchResults1) { // Go through the books until we find our book
			if (index == selectedSearchIndex) {
				this->txtBorrower->Text = gcnew String(book->borrower.name.c_str());
				if (!book->waitlist.empty()) {
					this->txtWaitlistFirst->Text = gcnew String(book->waitlist.front().name.c_str());
				}
				else {
					this->txtWaitlistFirst->Text = "";
				}
				break;
			}
			index++;
		}
	}
};
}
