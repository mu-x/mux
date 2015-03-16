#pragma once


namespace TetrisProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
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
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  gameMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  newGameBtn;


	private: System::Windows::Forms::ToolStripMenuItem^  pauseBtn;
	private: System::Windows::Forms::ToolStripTextBox^  scoreLine;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitBtn;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::PictureBox^  screen;
	private: System::Windows::Forms::Timer^  gameProc;
	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->gameMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newGameBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pauseBtn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scoreLine = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->screen = (gcnew System::Windows::Forms::PictureBox());
			this->gameProc = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->screen))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->gameMenu, this->pauseBtn, 
				this->scoreLine, this->toolStripMenuItem1});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(235, 25);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// gameMenu
			// 
			this->gameMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->newGameBtn, 
				this->toolStripSeparator1, this->exitBtn});
			this->gameMenu->Name = L"gameMenu";
			this->gameMenu->Size = System::Drawing::Size(43, 21);
			this->gameMenu->Text = L"Игра";
			// 
			// newGameBtn
			// 
			this->newGameBtn->Name = L"newGameBtn";
			this->newGameBtn->Size = System::Drawing::Size(118, 22);
			this->newGameBtn->Text = L"Новая";
			this->newGameBtn->Click += gcnew System::EventHandler(this, &Form1::newGameBtn_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(115, 6);
			// 
			// exitBtn
			// 
			this->exitBtn->Name = L"exitBtn";
			this->exitBtn->Size = System::Drawing::Size(118, 22);
			this->exitBtn->Text = L"Выход";
			this->exitBtn->Click += gcnew System::EventHandler(this, &Form1::exitBtn_Click);
			// 
			// pauseBtn
			// 
			this->pauseBtn->Enabled = false;
			this->pauseBtn->Name = L"pauseBtn";
			this->pauseBtn->Size = System::Drawing::Size(49, 21);
			this->pauseBtn->Text = L"Пауза";
			this->pauseBtn->Click += gcnew System::EventHandler(this, &Form1::pauseBtn_Click);
			// 
			// scoreLine
			// 
			this->scoreLine->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->scoreLine->Name = L"scoreLine";
			this->scoreLine->ReadOnly = true;
			this->scoreLine->Size = System::Drawing::Size(100, 21);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(12, 21);
			// 
			// screen
			// 
			this->screen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->screen->Location = System::Drawing::Point(13, 29);
			this->screen->Name = L"screen";
			this->screen->Size = System::Drawing::Size(210, 420);
			this->screen->TabIndex = 1;
			this->screen->TabStop = false;
			// 
			// gameProc
			// 
			this->gameProc->Interval = 500;
			this->gameProc->Tick += gcnew System::EventHandler(this, &Form1::gameProc_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(235, 460);
			this->Controls->Add(this->screen);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"Form1";
			this->Text = L"Тетрис";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::Form1_KeyPress);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->screen))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion

	private: array<Point>^				figure;
			 array<array<Boolean>^>^	field;
			 Int32						score;
			 array<Byte>^				stack;
			 Int32						counter;

			 // Генерация новой фигуры
	private: System::Void nextFigure()
			 {
				 figure = gcnew array<Point>(5);

				 switch (stack[counter] % 12)
				 {
				 case 0:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(7, 3);
					 figure[4] = Point(7, 4);
					 break;

				 case 1:
					figure[0] = Point(7, 0);
					figure[1] = Point(7, 1);
					figure[2] = Point(7, 2);
					figure[3] = Point(7, 3);
					figure[4] = Point(8, 3);
					break;

				 case 2:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(7, 3);
					 figure[4] = Point(6, 3);
					 break;

				 case 3:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(8, 1);
					 figure[4] = Point(6, 1);
					 break;

				 case 4:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(7, 3);
					 figure[4] = Point(8, 2);
					 break;

				 case 5:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(8, 0);
					 figure[4] = Point(8, 2);
					 break;

				 case 6:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(8, 1);
					 figure[4] = Point(9, 1);
					 break;

				 case 7:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(9, 2);
					 figure[4] = Point(8, 2);
					 break;

				 case 8:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(6, 0);
					 figure[4] = Point(8, 2);
					 break;

				 case 9:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(6, 2);
					 figure[4] = Point(8, 0);
					 break;

				 case 10:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(8, 1);
					 figure[4] = Point(8, 2);
					 break;

				 case 11:
					 figure[0] = Point(7, 0);
					 figure[1] = Point(7, 1);
					 figure[2] = Point(7, 2);
					 figure[3] = Point(6, 1);
					 figure[4] = Point(6, 2);
					 break;
				 }

				 if (++counter == stack->Length)
					 counter = 0;

				 if (moveFigure(0, 0))
					 return;

				 gameProc->Stop();
				 pauseBtn->Enabled = 0;
				 paintScreen();
			 }

			 // Смещение фигуры
	private: System::Boolean moveFigure(Int32 x, Int32 y)
			 {
				 for (Int32 i = 0; i < figure->Length; i++)
					 try {
						if (field[figure[i].X + x][figure[i].Y + y])
							return 0;
					 } catch (...) {
						return 0;
					 }

				 for (Int32 i = 0; i < figure->Length; i++)
				 {
					 figure[i].X += x;
					 figure[i].Y += y;
				 }
				 return 1;
			 }

			 // Установка фигуры на поле
	private: System::Void toField()
			 {
				 for (Int32 i = 0; i < figure->Length; i++)
					field[figure[i].X][figure[i].Y] = 1;

				 for (Int32 i = field[0]->Length - 1; i != 0; i--)
				 {
					 Boolean del = 1;
					 for (Int32 j = 0; j < field->Length; j++)
						 del = del && field[j][i];

					 if (del) {
						 for (Int32 k = i; k != 0; k--)
							 for (Int32 j = 0; j < field->Length; j++)
								 field[j][k] = field[j][k - 1];
						 for (Int32 j = 0; j < field->Length; j++)
							 field[j][1] = 0;
						 score++;
					 }
				 }
				 
				 nextFigure();
			 }

			 // отрисовка картинки
    private: System::Void paintScreen()
			 {
				 Bitmap^ bitmap = gcnew Bitmap(screen->Width, screen->Height);
				 Graphics^ paint = Graphics::FromImage(bitmap);

				 paint->FillRectangle(Brushes::White, 0, 0, screen->Width, screen->Height);
				 Int32 stepX = screen->Width / 14, stepY = screen->Height / 28;

				 for (Int32 i = 0; i < figure->Length; i++)
					 paint->DrawRectangle(Pens::Black, figure[i].X * stepX + 1, figure[i].Y * stepY + 1, stepX - 2, stepY - 2);

				 for (Int32 i = 0; i < field->Length; i++)
					 for (Int32 j = 0; j < field[i]->Length; j++)
						 if (field[i][j])
							 paint->FillRectangle(Brushes::Black, i * stepX + 1, j * stepY + 1, stepX - 2, stepY - 2);
				 
				 screen->Image = bitmap;
			 }

			 // поворот фигуры
	private: System::Void rotate()
			 {
				 Point angle = Point(14, 28);
				 for (Int32 i = 0; i < figure->Length; i++)
				 {
					 if (angle.X > figure[i].X)
						 angle.X = figure[i].X;
					 if (angle.Y > figure[i].Y)
						 angle.Y = figure[i].Y;
				 }

				 array<Point>^ old = (array<Point>^)figure->Clone();
				 for (Int32 i = 0; i < figure->Length; i++)
					 figure[i] = Point(angle.X + 3 - (old[i].Y - angle.Y), old[i].X - angle.X + angle.Y);

				 if (!moveFigure(0, 0))
					 figure = old;
			 }

			 // кнопка "Новая игра"
	private: System::Void newGameBtn_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 double time = DateTime::Now.ToOADate();
				 Random^ rand = gcnew Random((int &)time);
				 stack = gcnew array<Byte>(100);
				 rand->NextBytes(stack);

				 field = gcnew array<array<Boolean>^>(14);
				 for (Int32 i = 0; i < field->Length; i++)
				 {
					 field[i] = gcnew array<Boolean>(28);
					 for (Int32 j = 0; j < field[i]->Length; j++)
						 field[i][j] = 0;
				 }

				 nextFigure();
				 paintScreen();

				 score = 0;
				 pauseBtn->Enabled = 1;
				 gameProc->Start();
			 }

			 // кнопка "Выход"
	private: System::Void exitBtn_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 Close();
			 }

			 // кнопка "пауза"
	private: System::Void pauseBtn_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (gameProc->Enabled)
				 {
					 gameProc->Stop();
					 pauseBtn->Text = "Продолжить";
					 return;
				 }

				 gameProc->Start();
				 pauseBtn->Text = "Пауза";
			 }

			 // таймер игрового процесса
	private: System::Void gameProc_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (!moveFigure(0, 1))
					toField();

				 paintScreen();
				 scoreLine->Text = "Счёт: " + score.ToString();
			 }

			 // действие по нажатию клавиши
	private: System::Void Form1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
			 {
				 if (e->KeyChar == 'w')
					 rotate();
				 else if (e->KeyChar == 's')
					 moveFigure(0, 1);
				 else if (e->KeyChar == 'a')
					 moveFigure(-1, 0);
				 else if (e->KeyChar == 'd')
					 moveFigure(1, 0);

				 paintScreen();
			 }
};
}

