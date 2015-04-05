#pragma once

#include <stdlib.h>
#include <msclr\marshal_cppstd.h>
#include <boost/date_time.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "logic.h"
#include "storage.h"

namespace DoooodleGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	private:
		Logic* logic;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox4;

			 Storage* storage;

	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			logic = new Logic;
			storage = new Storage;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:








	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(17, 418);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(756, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
			this->textBox1->Enter += gcnew System::EventHandler(this, &GUI::textBox1_TextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GUI::textBox1_KeyDown);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(560, 350);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(80, 62);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &GUI::pictureBox1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Gabriola", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(565, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(171, 65);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Floating Task";
			this->label1->Click += gcnew System::EventHandler(this, &GUI::label1_Click);
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(17, 12);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::BurlyWood;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(552, 80);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(226, 264);
			this->textBox2->TabIndex = 7;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::Moccasin;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(17, 80);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(502, 296);
			this->textBox3->TabIndex = 8;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Gabriola", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(8, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(140, 50);
			this->label3->TabIndex = 9;
			this->label3->Text = L" Welcome Jim!";
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Location = System::Drawing::Point(17, 392);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(502, 13);
			this->textBox4->TabIndex = 10;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(790, 450);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBox1);
			this->Name = L"GUI";
			this->Text = L"GUI";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
		System::String^ convertStdToManaged(std::string std_string){ //convert std string to String^
			return gcnew String(std_string.c_str());
		}


		void MarshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =	(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void MarshalString(String ^ s, std::wstring& os) {
			using namespace Runtime::InteropServices;
			const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void clearUserInput(){
			textBox1->Clear();
		}

		void clearGUI(){
			textBox2->Clear();
			textBox3->Clear();
		}

		void processIndividualTask() {

		}


#pragma endregion
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Enter) {
		clearGUI();
		String^ userInput = textBox1->Text;
		std::string input;
		std::string cat;
		std::vector<std::string> displayMessage;
		MarshalString(userInput, input);
		std::string message = logic->receiveCommand(input);
		storage = logic->getStorage();
		std::vector<std::string> floatingTask = storage->retrieveFloatingTask();
		std::vector<std::string> topTen = storage->retrieveTopTen();

		label1->Text = "Floating Tasks [" + Convert::ToUInt32(logic->getFloatingSize()) + "]:";
		if (floatingTask.size() > 0) {
			textBox2->Text = convertStdToManaged(floatingTask[0]);
			for (int i = 1; i<floatingTask.size(); i++) {
				textBox2->Text = textBox2->Text + "\r\n" + (convertStdToManaged(floatingTask[i]));
			}
		}

		if (logic->getCommandType(input) == "search") {
			displayMessage = logic->displaySearchResults(input);
			label3->Text = "Search Results [" + Convert::ToUInt32(displayMessage.size()) + "]:";
			if (displayMessage.size()>0) {
				textBox3->Text = convertStdToManaged(displayMessage[0]);
				for (int i = 1; i < displayMessage.size(); i++) {
					textBox3->Text = textBox3->Text + "\r\n" + (convertStdToManaged(displayMessage[i]));
				}
			}
		}
		else if (logic->getCommandType(input) == "display"){
			displayMessage = logic->displayCategoricalTask(input, cat);
			label3->Text = "Below is the list of " + convertStdToManaged(cat) + " tasks [" + Convert::ToUInt32(displayMessage.size()) + "]:";
			if (displayMessage.size()>0) {
				textBox3->Text = convertStdToManaged(displayMessage[0]);
				for (int i = 1; i < displayMessage.size(); i++) {
					textBox3->Text = textBox3->Text + "\r\n" + (convertStdToManaged(displayMessage[i]));
				}
			}
		}
		else {
			label3->Text = "Below is the list of upcoming events in your calendar [" + Convert::ToUInt32(logic->getDeadlineSize()) + "] [" + Convert::ToUInt32(logic->getNormalSize()) + "]:";
			if (topTen.size()>0) {
				textBox3->Text = convertStdToManaged(topTen[0]);
				for (int i = 1; i < topTen.size(); i++) {
					textBox3->Text = textBox3->Text + "\r\n" + (convertStdToManaged(topTen[i]));
				}

			}
		}
		textBox4->Text = convertStdToManaged(message);
		clearUserInput();
	}
}
};
}
