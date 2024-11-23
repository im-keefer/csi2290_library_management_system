#pragma once
#include <queue>
#include <list>

struct Person {
	std::string name;
};

struct Book {
	std::string title;
	std::string author;
	std::string isbn;
	Person borrower;
	std::queue<Person> waitlist;
	Book(std::string title_in, std::string author_in, std::string isbn_in) 
		: title(title_in), author(author_in), isbn(isbn_in)
	{}
	Book();
};


//Checking out & Returning book functions

void queueToList(std::queue<Person> Q, std::list<std::string>& L) {
	//Puts a queue of People into an list, the list is passed by reference, the queue is not.
	//The list is front-to-back. (eg. the first element in the list is the front of the queue)
	while (!Q.empty()) {
		L.push_back(Q.front().name);
		Q.pop();
	}
}

void checkoutBook(Book& B,Person P) {
	//If there isn't currently a borrower, P is the new borrower.
	//Else, add P to the waitlist
	if (B.borrower.name == "") {
		B.borrower = P;

	}
	else {
		B.waitlist.push(P);
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
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::TabPage^ tabPage4;
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
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Controls->Add(this->tabPage4);
			this->tabControl->Location = System::Drawing::Point(12, 12);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(790, 463);
			this->tabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
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
			// btnDeleteBook
			// 
			this->btnDeleteBook->Location = System::Drawing::Point(553, 322);
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
			this->label4->Location = System::Drawing::Point(550, 297);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(38, 16);
			this->label4->TabIndex = 13;
			this->label4->Text = L"ISBN";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(550, 269);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(45, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Author";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(550, 241);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 16);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Title";
			// 
			// txtISBNLook
			// 
			this->txtISBNLook->Location = System::Drawing::Point(631, 294);
			this->txtISBNLook->Name = L"txtISBNLook";
			this->txtISBNLook->ReadOnly = true;
			this->txtISBNLook->Size = System::Drawing::Size(145, 22);
			this->txtISBNLook->TabIndex = 10;
			// 
			// txtAuthorLook
			// 
			this->txtAuthorLook->Location = System::Drawing::Point(631, 266);
			this->txtAuthorLook->Name = L"txtAuthorLook";
			this->txtAuthorLook->ReadOnly = true;
			this->txtAuthorLook->Size = System::Drawing::Size(145, 22);
			this->txtAuthorLook->TabIndex = 9;
			// 
			// txtTitleLook
			// 
			this->txtTitleLook->Location = System::Drawing::Point(631, 238);
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
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(782, 434);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Borrow & Return";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(782, 434);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// tabPage4
			// 
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(782, 434);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"tabPage4";
			this->tabPage4->UseVisualStyleBackColor = true;
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
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		int selectedBookIndex = -1;
	private: System::Void lbBookList1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		// Our index represents how far we need to go into the linked list to access the book.
		int index = 0;
		selectedBookIndex = this->lbBookList1->SelectedIndex; // Useful to quickly delete books
		for (Book book : currentbooks) { // Go through the books until we find our book
			if (index == this->lbBookList1->SelectedIndex) {
				this->txtTitleLook->Text = gcnew String(book.title.c_str());
				this->txtAuthorLook->Text = gcnew String(book.author.c_str());
				this->txtISBNLook->Text = gcnew String(book.isbn.c_str());
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
		Book newBook(title, author, isbn);
		currentbooks.push_front(newBook);
		// Refresh the Book list
		this->lbBookList1->Items->Clear();
		for (Book book : currentbooks) {
			System::String^ name = gcnew String(book.title.c_str()); // And then we go back
			this->lbBookList1->Items->Add(name);
		}
	}
	private: System::Void btnDeleteBook_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!currentbooks.empty() && selectedBookIndex >= 0) {
			int index = 0;
			std::list<Book>::iterator it;
			it = currentbooks.begin();
			advance(it, selectedBookIndex);
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
			selectedBookIndex = -1; // Set our book index to -1 so we know that we have to click again
		}
	}
};
}
