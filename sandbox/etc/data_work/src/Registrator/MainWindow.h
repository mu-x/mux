#pragma once
#include "Sensor.h"
#include <math.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::Odbc;


namespace Registrator {

	/// <summary>
	/// Сводка для MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DateTimePicker^  DateNow;
	private: System::Windows::Forms::TextBox^  TextOperator;
	private: System::Windows::Forms::TextBox^  TextComment;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ListBox^  OutList;
	private: System::Windows::Forms::Button^  BtnStart;
	private: System::Windows::Forms::Timer^  TimeNow;
	private: System::Windows::Forms::Timer^  TimeFrame;
	private: System::Windows::Forms::NumericUpDown^  TextFrames;
	private: System::ComponentModel::IContainer^  components;

		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->DateNow = (gcnew System::Windows::Forms::DateTimePicker());
			this->TextOperator = (gcnew System::Windows::Forms::TextBox());
			this->TextComment = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->OutList = (gcnew System::Windows::Forms::ListBox());
			this->BtnStart = (gcnew System::Windows::Forms::Button());
			this->TimeNow = (gcnew System::Windows::Forms::Timer(this->components));
			this->TimeFrame = (gcnew System::Windows::Forms::Timer(this->components));
			this->TextFrames = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TextFrames))->BeginInit();
			this->SuspendLayout();
			// 
			// DateNow
			// 
			this->DateNow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->DateNow->CustomFormat = L"dd.MM.yyyy |  hh.mm.ss";
			this->DateNow->Enabled = false;
			this->DateNow->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->DateNow->Location = System::Drawing::Point(96, 9);
			this->DateNow->Name = L"DateNow";
			this->DateNow->Size = System::Drawing::Size(233, 20);
			this->DateNow->TabIndex = 0;
			// 
			// TextOperator
			// 
			this->TextOperator->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->TextOperator->Location = System::Drawing::Point(96, 35);
			this->TextOperator->Name = L"TextOperator";
			this->TextOperator->Size = System::Drawing::Size(233, 20);
			this->TextOperator->TabIndex = 1;
			// 
			// TextComment
			// 
			this->TextComment->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->TextComment->Location = System::Drawing::Point(16, 116);
			this->TextComment->Multiline = true;
			this->TextComment->Name = L"TextComment";
			this->TextComment->Size = System::Drawing::Size(313, 79);
			this->TextComment->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Дата и время";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 38);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Оператор";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 95);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(69, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Коментарий";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(13, 64);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Кадры";
			// 
			// OutList
			// 
			this->OutList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->OutList->FormattingEnabled = true;
			this->OutList->Location = System::Drawing::Point(16, 201);
			this->OutList->Name = L"OutList";
			this->OutList->Size = System::Drawing::Size(313, 251);
			this->OutList->TabIndex = 8;
			// 
			// BtnStart
			// 
			this->BtnStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->BtnStart->Location = System::Drawing::Point(96, 87);
			this->BtnStart->Name = L"BtnStart";
			this->BtnStart->Size = System::Drawing::Size(233, 23);
			this->BtnStart->TabIndex = 9;
			this->BtnStart->Text = L"Снять данные";
			this->BtnStart->UseVisualStyleBackColor = true;
			this->BtnStart->Click += gcnew System::EventHandler(this, &MainWindow::BtnStart_Click);
			// 
			// TimeNow
			// 
			this->TimeNow->Enabled = true;
			this->TimeNow->Interval = 1000;
			this->TimeNow->Tick += gcnew System::EventHandler(this, &MainWindow::TimeNow_Tick);
			// 
			// TimeFrame
			// 
			this->TimeFrame->Tick += gcnew System::EventHandler(this, &MainWindow::TimeFrame_Tick);
			// 
			// TextFrames
			// 
			this->TextFrames->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->TextFrames->Location = System::Drawing::Point(96, 64);
			this->TextFrames->Name = L"TextFrames";
			this->TextFrames->Size = System::Drawing::Size(233, 20);
			this->TextFrames->TabIndex = 10;
			this->TextFrames->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(342, 467);
			this->Controls->Add(this->TextFrames);
			this->Controls->Add(this->BtnStart);
			this->Controls->Add(this->OutList);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TextComment);
			this->Controls->Add(this->TextOperator);
			this->Controls->Add(this->DateNow);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(252, 370);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Регистрация данных на объекте";
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TextFrames))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: OdbcConnection^	dataBase;
			 unsigned int		session;
			 unsigned int		frameCount;

			 // Подключение базы
	private: System::Void MainWindow_Load(System::Object^  sender, System::EventArgs^  e)
			 {
				 dataBase = gcnew OdbcConnection(
					 "Driver={Microsoft Access Driver (*.mdb)};Dbq=" +
					 Application::StartupPath +
					 "\\Archive.mdb;Uid=admin;Pwd=");
				 dataBase->Open();
			 }

			 // Запуск съёма
	private: System::Void BtnStart_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 try
				 {
					 frameCount = Convert::ToUInt32(TextFrames->Value);
					 if (frameCount <= 0)
						 throw gcnew Exception("Число кадров должно быть больше 0.");
					 if (TextOperator->Text == String::Empty)
						 throw gcnew Exception("Необходимо ввссти име оператора.");
				 }
				 catch (Exception^ e)
				 {
					 MessageBox::Show(e->Message, "Ошибка");
					 return;
				 }

				 OdbcDataAdapter^ adapter = gcnew OdbcDataAdapter(
					 "SELECT max(Номер) FROM Сессии", dataBase);
				 OdbcDataReader^ read = adapter->SelectCommand->ExecuteReader();
				 
				 if (read->Read() && (!read->IsDBNull(0)))
					 session = read->GetInt32(0) + 1;
				 else
					 session = 1;

				 String^ query = gcnew String("INSERT INTO Сессии VALUES (") +
					 DoString(session) + ", "
					 "'" + DateNow->Value.ToString("dd.MM.yyyy") + "', " +
					 "'" + TextOperator->Text +"', " +
					 "'" + TextComment->Text + "')";

				 OdbcCommand^ cmd = gcnew OdbcCommand(query, dataBase);
				 cmd->ExecuteNonQuery();

				 TextComment->Enabled = false;
				 TextFrames->Enabled = false;
				 TextOperator->Enabled = false;
				 UseWaitCursor = true;

				 OutList->Items->Clear();
				 TimeFrame->Start();
			 }

			 // Обновление даты
	private: System::Void TimeNow_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 DateNow->Value = DateTime::Now;
			 }

	private: System::Void OutList_Report(String^ text)
			 {
				 OutList->Items->Add(DateNow->Value.ToString() + " " + text);
			 }

			 // Съём кадра
	private: System::Void TimeFrame_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (!frameCount)
				 {
					 OutList_Report("Завершение съёма!");
					 TimeFrame->Stop();

					 TextComment->Enabled = true;
					 TextFrames->Enabled = true;
					 TextOperator->Enabled = true;
					 UseWaitCursor = false;
					 return;
				 }

				 array<String^>^ frame = gcnew array<String^>(12);
				 float buffer[5], mid = 0, disp = 0;

				 frame[0] = DoString(buffer[0] = opros(1));
				 if ((buffer[0] < -25) || (buffer[0] > 20))
					 OutList_Report("Канал 1 вышел за границы [-25, 20]");
				 frame[1] = DoString(opros(2));
				 frame[2] = DoString(opros(3));
				 frame[3] = DoString(buffer[0] = opros(4));
				 if ((buffer[0] < 0) || (buffer[0] > 1))
					 OutList_Report("Канал 4 вышел за границы [0, 1]");
				 frame[4] = DoString((opros(5) - 2.2) / 1.5);
				
				 for (int i = 0; i < 5; ++i)
					 mid += (buffer[i] = opros(6));
				 frame[5] = DoString(mid = mid / 5);
				 for (int i = 0; i < 5; ++i)
					 disp += pow(mid - buffer[i], 2);
				 frame[6] = DoString(disp = disp / 4);

				 for (int i = 0; i < 4; ++i)
					 buffer[i] = opros(9);
				 if ((buffer[0] != buffer[1]) || (buffer[0] != buffer[2]) ||
					 (buffer[0] != buffer[3]))
				 {
					OutList_Report("Канал 9 не стабилен, отмена кадра!");
					return;
				 }
				 frame[7] = DoString(buffer[0]);

				 frame[8] = DoString(opros(16));
				 frame[9] = DoString(opros(46));
				 buffer[0] = opros(66);
				 frame[10] = DoString((buffer[0] + 86) / (buffer[0] - 210));

				 for (int i = 0; i < 3; ++i)
					 buffer[i] = opros(76);
				 if ((buffer[0] != buffer[1]) || (buffer[0] != buffer[2]))
				 {
					 OutList_Report("Канал 76 не стабилен, отмена кадра!");
					 return;
				 }
				 frame[11] = DoString(buffer[0]);

				 // Запись в базу
				 String^ query = gcnew String("INSERT INTO Кадры ") +
					 "(Сессия, К01, К02, К03, К04, К05, К06C, " +
					 "К06Д, К09, К16, К46, К66, К76) VALUES (" +
					 Convert::ToString(session);
				 for (int i = 0; i < 12; ++i)
					 query += ", '" + frame[i] + "'";
				 OdbcCommand^ cmd = gcnew OdbcCommand(query + ")", dataBase);
				 cmd->ExecuteNonQuery();
				 frameCount--;
			 }

	private: String^ DoString(double val)
			 {
				 return Convert::ToString(Math::Round(val, 3));
			 }
	};
}
