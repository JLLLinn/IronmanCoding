#include "OCRFuncs.h"
#include <iostream>
#include <fstream>
#include <time.h>
#pragma once


namespace OCRcpp {
	using namespace System;
	using namespace System::IO;
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
	private: System::Windows::Forms::Button^  loadFileBtn;
	protected: 

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
			 System::Drawing::Bitmap ^rawBitMap;
			 System::Drawing::Bitmap ^displayBitMap;
	
			 
	private: unsigned char **red_rows;
	private: unsigned char **green_rows;
	private: unsigned char **blue_rows;

	private: System::Windows::Forms::Button^  lineBoxBtn;
	private: OCRDecoder *OCRDecoder1;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  disValueBox;
	private: System::Windows::Forms::Button^  DrLineBoxBtn;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  saveBitmap;
	private: System::Windows::Forms::TextBox^  textBox2;



	private: System::Windows::Forms::Button^  loadTemplate;
	private: System::Windows::Forms::Button^  TotalBadPx;
	private: System::Windows::Forms::TextBox^  y;

	private: System::Windows::Forms::TextBox^  x;


	private: System::Windows::Forms::TextBox^  target;
	private: System::Windows::Forms::TextBox^  instruct;
	private: System::Windows::Forms::Button^  drwTemplate;
	private: System::Windows::Forms::TextBox^  xd;
	private: System::Windows::Forms::TextBox^  yd;
	private: System::Windows::Forms::TextBox^  targetd;



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  degree;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  show_scores;
	private: System::Windows::Forms::Button^  Otsu_Thre;
	private: System::Windows::Forms::Button^  blurbtn;



















	private: System::Windows::Forms::Button^  setDisValue;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->loadFileBtn = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->lineBoxBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->disValueBox = (gcnew System::Windows::Forms::TextBox());
			this->setDisValue = (gcnew System::Windows::Forms::Button());
			this->DrLineBoxBtn = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->saveBitmap = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->loadTemplate = (gcnew System::Windows::Forms::Button());
			this->TotalBadPx = (gcnew System::Windows::Forms::Button());
			this->y = (gcnew System::Windows::Forms::TextBox());
			this->x = (gcnew System::Windows::Forms::TextBox());
			this->target = (gcnew System::Windows::Forms::TextBox());
			this->instruct = (gcnew System::Windows::Forms::TextBox());
			this->drwTemplate = (gcnew System::Windows::Forms::Button());
			this->xd = (gcnew System::Windows::Forms::TextBox());
			this->yd = (gcnew System::Windows::Forms::TextBox());
			this->targetd = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->degree = (gcnew System::Windows::Forms::NumericUpDown());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->show_scores = (gcnew System::Windows::Forms::Button());
			this->Otsu_Thre = (gcnew System::Windows::Forms::Button());
			this->blurbtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->degree))->BeginInit();
			this->SuspendLayout();
			// 
			// loadFileBtn
			// 
			this->loadFileBtn->Location = System::Drawing::Point(12, 12);
			this->loadFileBtn->Name = L"loadFileBtn";
			this->loadFileBtn->Size = System::Drawing::Size(100, 50);
			this->loadFileBtn->TabIndex = 0;
			this->loadFileBtn->Text = L"Load File";
			this->loadFileBtn->UseVisualStyleBackColor = true;
			this->loadFileBtn->Click += gcnew System::EventHandler(this, &Form1::loadFileBtn_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(151, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1324, 522);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// lineBoxBtn
			// 
			this->lineBoxBtn->AutoSize = true;
			this->lineBoxBtn->Location = System::Drawing::Point(12, 151);
			this->lineBoxBtn->Name = L"lineBoxBtn";
			this->lineBoxBtn->Size = System::Drawing::Size(100, 50);
			this->lineBoxBtn->TabIndex = 3;
			this->lineBoxBtn->Text = L"Find Lines Box";
			this->lineBoxBtn->UseVisualStyleBackColor = true;
			this->lineBoxBtn->Visible = false;
			this->lineBoxBtn->Click += gcnew System::EventHandler(this, &Form1::LineBoxBtn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 593);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 15);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Distinguish Color Value:";
			// 
			// disValueBox
			// 
			this->disValueBox->Location = System::Drawing::Point(13, 609);
			this->disValueBox->Name = L"disValueBox";
			this->disValueBox->Size = System::Drawing::Size(100, 20);
			this->disValueBox->TabIndex = 7;
			this->disValueBox->Visible = false;
			// 
			// setDisValue
			// 
			this->setDisValue->Location = System::Drawing::Point(13, 540);
			this->setDisValue->Name = L"setDisValue";
			this->setDisValue->Size = System::Drawing::Size(100, 50);
			this->setDisValue->TabIndex = 8;
			this->setDisValue->Text = L"Set Dis Value";
			this->setDisValue->UseVisualStyleBackColor = true;
			this->setDisValue->Visible = false;
			this->setDisValue->Click += gcnew System::EventHandler(this, &Form1::setDisValue_Click);
			// 
			// DrLineBoxBtn
			// 
			this->DrLineBoxBtn->Location = System::Drawing::Point(13, 254);
			this->DrLineBoxBtn->Name = L"DrLineBoxBtn";
			this->DrLineBoxBtn->Size = System::Drawing::Size(100, 50);
			this->DrLineBoxBtn->TabIndex = 9;
			this->DrLineBoxBtn->Text = L"Draw Boxes";
			this->DrLineBoxBtn->UseVisualStyleBackColor = true;
			this->DrLineBoxBtn->Visible = false;
			this->DrLineBoxBtn->Click += gcnew System::EventHandler(this, &Form1::DrLineBoxBtn_Click);
			// 
			// saveBitmap
			// 
			this->saveBitmap->Location = System::Drawing::Point(13, 415);
			this->saveBitmap->Name = L"saveBitmap";
			this->saveBitmap->Size = System::Drawing::Size(100, 50);
			this->saveBitmap->TabIndex = 10;
			this->saveBitmap->Text = L"Save Cur Bitmap";
			this->saveBitmap->UseVisualStyleBackColor = true;
			this->saveBitmap->Visible = false;
			this->saveBitmap->Click += gcnew System::EventHandler(this, &Form1::saveBitmap_Click);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(151, 540);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(1324, 502);
			this->textBox2->TabIndex = 11;
			// 
			// loadTemplate
			// 
			this->loadTemplate->Location = System::Drawing::Point(13, 207);
			this->loadTemplate->Name = L"loadTemplate";
			this->loadTemplate->Size = System::Drawing::Size(100, 41);
			this->loadTemplate->TabIndex = 12;
			this->loadTemplate->Text = L"Recognize";
			this->loadTemplate->UseVisualStyleBackColor = true;
			this->loadTemplate->Click += gcnew System::EventHandler(this, &Form1::loadTemplate_Click);
			// 
			// TotalBadPx
			// 
			this->TotalBadPx->Location = System::Drawing::Point(13, 649);
			this->TotalBadPx->Name = L"TotalBadPx";
			this->TotalBadPx->Size = System::Drawing::Size(100, 44);
			this->TotalBadPx->TabIndex = 13;
			this->TotalBadPx->Text = L"TotalBadPx";
			this->TotalBadPx->UseVisualStyleBackColor = true;
			this->TotalBadPx->Click += gcnew System::EventHandler(this, &Form1::TotalBadPx_Click);
			// 
			// y
			// 
			this->y->Location = System::Drawing::Point(13, 700);
			this->y->Name = L"y";
			this->y->Size = System::Drawing::Size(28, 20);
			this->y->TabIndex = 14;
			// 
			// x
			// 
			this->x->Location = System::Drawing::Point(47, 700);
			this->x->Name = L"x";
			this->x->Size = System::Drawing::Size(28, 20);
			this->x->TabIndex = 15;
			// 
			// target
			// 
			this->target->Location = System::Drawing::Point(81, 699);
			this->target->Name = L"target";
			this->target->Size = System::Drawing::Size(29, 20);
			this->target->TabIndex = 16;
			// 
			// instruct
			// 
			this->instruct->Location = System::Drawing::Point(14, 727);
			this->instruct->Name = L"instruct";
			this->instruct->ReadOnly = true;
			this->instruct->Size = System::Drawing::Size(100, 20);
			this->instruct->TabIndex = 17;
			this->instruct->Text = L"   y        x       target";
			// 
			// drwTemplate
			// 
			this->drwTemplate->Location = System::Drawing::Point(14, 803);
			this->drwTemplate->Name = L"drwTemplate";
			this->drwTemplate->Size = System::Drawing::Size(100, 43);
			this->drwTemplate->TabIndex = 18;
			this->drwTemplate->Text = L"Draw template";
			this->drwTemplate->UseVisualStyleBackColor = true;
			this->drwTemplate->Click += gcnew System::EventHandler(this, &Form1::drwTemplate_Click);
			// 
			// xd
			// 
			this->xd->Location = System::Drawing::Point(13, 863);
			this->xd->Name = L"xd";
			this->xd->Size = System::Drawing::Size(28, 20);
			this->xd->TabIndex = 19;
			// 
			// yd
			// 
			this->yd->Location = System::Drawing::Point(48, 863);
			this->yd->Name = L"yd";
			this->yd->Size = System::Drawing::Size(27, 20);
			this->yd->TabIndex = 20;
			// 
			// targetd
			// 
			this->targetd->Location = System::Drawing::Point(81, 863);
			this->targetd->Name = L"targetd";
			this->targetd->Size = System::Drawing::Size(18, 20);
			this->targetd->TabIndex = 21;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 899);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 15);
			this->label2->TabIndex = 22;
			this->label2->Text = L"     x    y   target  deg";
			// 
			// degree
			// 
			this->degree->DecimalPlaces = 1;
			this->degree->Location = System::Drawing::Point(105, 863);
			this->degree->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {180, 0, 0, System::Int32::MinValue});
			this->degree->Name = L"degree";
			this->degree->Size = System::Drawing::Size(41, 20);
			this->degree->TabIndex = 23;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 68);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(99, 48);
			this->button1->TabIndex = 24;
			this->button1->Text = L"One Button Do All";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// show_scores
			// 
			this->show_scores->Location = System::Drawing::Point(13, 324);
			this->show_scores->Name = L"show_scores";
			this->show_scores->Size = System::Drawing::Size(98, 44);
			this->show_scores->TabIndex = 25;
			this->show_scores->Text = L"Show Scores";
			this->show_scores->UseVisualStyleBackColor = true;
			this->show_scores->Click += gcnew System::EventHandler(this, &Form1::show_scores_Click);
			// 
			// Otsu_Thre
			// 
			this->Otsu_Thre->Location = System::Drawing::Point(13, 491);
			this->Otsu_Thre->Name = L"Otsu_Thre";
			this->Otsu_Thre->Size = System::Drawing::Size(100, 43);
			this->Otsu_Thre->TabIndex = 26;
			this->Otsu_Thre->Text = L"Otsu Threshold";
			this->Otsu_Thre->UseVisualStyleBackColor = true;
			this->Otsu_Thre->Click += gcnew System::EventHandler(this, &Form1::Otsu_Thre_Click);
			// 
			// blurbtn
			// 
			this->blurbtn->Location = System::Drawing::Point(14, 943);
			this->blurbtn->Name = L"blurbtn";
			this->blurbtn->Size = System::Drawing::Size(96, 49);
			this->blurbtn->TabIndex = 27;
			this->blurbtn->Text = L"Blur";
			this->blurbtn->UseVisualStyleBackColor = true;
			this->blurbtn->Click += gcnew System::EventHandler(this, &Form1::blurbtn_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1491, 1054);
			this->Controls->Add(this->blurbtn);
			this->Controls->Add(this->Otsu_Thre);
			this->Controls->Add(this->show_scores);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->degree);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->targetd);
			this->Controls->Add(this->yd);
			this->Controls->Add(this->xd);
			this->Controls->Add(this->drwTemplate);
			this->Controls->Add(this->instruct);
			this->Controls->Add(this->target);
			this->Controls->Add(this->x);
			this->Controls->Add(this->y);
			this->Controls->Add(this->TotalBadPx);
			this->Controls->Add(this->loadTemplate);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->saveBitmap);
			this->Controls->Add(this->DrLineBoxBtn);
			this->Controls->Add(this->setDisValue);
			this->Controls->Add(this->disValueBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lineBoxBtn);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->loadFileBtn);
			this->Name = L"Form1";
			this->Text = L"OoooooCcccccRrrrrr";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->degree))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loadFileBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				
				openFileDialog1->Filter = "Image Files|*.bmp;*.jpg;*.jpeg;*.BMP;*.JPG;*.JPEG";
				openFileDialog1->Title = "Open a Bitmap File";
				openFileDialog1->RestoreDirectory = true;//directory need to be restored, or current directory would be changed
				
				if(openFileDialog1->ShowDialog()!=System::Windows::Forms::DialogResult::OK)return;
			
				rawBitMap = gcnew System::Drawing::Bitmap(openFileDialog1->FileName);
				
				displayBitMap = gcnew System::Drawing::Bitmap(rawBitMap);				
				pictureBox1->Visible=true;
				pictureBox1->Image=displayBitMap;
				int pixel_index;
				System::Drawing::Rectangle rect(0, 0, displayBitMap->Width, displayBitMap->Height);
				System::Drawing::Imaging::BitmapData^  myPixels1 = rawBitMap->LockBits(rect, 
						 System::Drawing::Imaging::ImageLockMode::ReadWrite, rawBitMap->PixelFormat
						 );
				IntPtr ptr = myPixels1->Scan0;
				unsigned char *im = (unsigned char *)ptr.ToPointer();
				red_rows =new unsigned char *[rawBitMap->Height];
				green_rows =new unsigned char *[rawBitMap->Height];
				blue_rows =new unsigned char *[rawBitMap->Height];
				int strideValue = Math::Abs(myPixels1->Stride);

				for (int i = 0; i < rawBitMap->Height; i++) {
					red_rows[i] = new unsigned char[rawBitMap->Width];
					green_rows[i] = new unsigned char[rawBitMap->Width];
					blue_rows[i] = new unsigned char[rawBitMap->Width];

					if (!red_rows[i])
						 break;
					for (int j = 0; j < rawBitMap->Width; j++) {
						pixel_index = i * strideValue + j*3;//is it 3 or 4?
						red_rows[i][j] = im[pixel_index];
						green_rows[i][j] = im[pixel_index+1];
						blue_rows[i][j] = im[pixel_index +2];
					}
				}
				rawBitMap->UnlockBits(myPixels1);
				OCRDecoder1=new OCRDecoder((rawBitMap->Height),(rawBitMap->Width),green_rows,displayBitMap,25);
				this->Refresh();
				this->lineBoxBtn->Visible=true; 
				this->setDisValue->Visible=true;
				this->disValueBox->Visible=true;
				this->saveBitmap->Visible=true;
				disValueBox->Text=Convert::ToString(OCRDecoder1->DivideColorValue());
				for(int i=0;i<rawBitMap->Height;i++){
					delete[] red_rows[i];
					delete[] blue_rows[i];
				}
				delete[] red_rows;
				delete[] blue_rows;
			 }

	/*
	 * find the line box around the texts
	 */
private: System::Void LineBoxBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			OCRDecoder1->LineBox_All();
			disValueBox->Text=Convert::ToString(OCRDecoder1->DivideColorValue());
			this->DrLineBoxBtn->Visible = true;
			this->textBox2->Text=OCRDecoder1->BoxDataToString();
		  }
private: System::Void setDisValue_Click(System::Object^  sender, System::EventArgs^  e) {
			OCRDecoder1->DivideColorValue(Convert::ToInt32(disValueBox->Text));
		 }
private: System::Void DrLineBoxBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			OCRDecoder1->DrawLineBoxes();
			this->Refresh();
		 }
private: System::Void saveBitmap_Click(System::Object^  sender, System::EventArgs^  e) {
			saveFileDialog1->Filter = "Bitmap Image|*.bmp";
			saveFileDialog1->Title = "Save a Bitmap File";
			saveFileDialog1->RestoreDirectory=true;
			if(saveFileDialog1->ShowDialog()!=::System::Windows::Forms::DialogResult::OK)return;
			displayBitMap->Save(saveFileDialog1->FileName,System::Drawing::Imaging::ImageFormat::Bmp);
		 }
private: System::Void loadTemplate_Click(System::Object^  sender, System::EventArgs^  e) {
			this->textBox2->Text="";
			OCRDecoder1->Recognize();
			this->textBox2->Text+=OCRDecoder1->ResultStringToString();
		 }
private: System::Void TotalBadPx_Click(System::Object^  sender, System::EventArgs^  e) {
			 int x = Convert::ToInt32(this->x->Text);
			 int y = Convert::ToInt32(this->y->Text);
			 this->textBox2->Text+="\r\n"+"Total Bad Px: "+OCRDecoder1->ComputeTotalBadPx(y,x,(char)Convert::ToChar(this->target->Text[0]),0)+"\r\n";
			 this->textBox2->Text+=OCRDecoder1->CreateAndCompare(y,x,(char)Convert::ToChar(this->target->Text[0]),0);
		 }
private: System::Void drwTemplate_Click(System::Object^  sender, System::EventArgs^  e) {
			 int width = Convert::ToInt32(this->xd->Text);
			 int height = Convert::ToInt32(this->yd->Text);
			 char** compareMatrix = OCRDecoder1->CreateCompareMatrix(width,height,(char)Convert::ToChar(this->targetd->Text[0]),0,(double)this->degree->Value);
			 this->textBox2->Text=OCRDecoder1->CharMatrixToString(compareMatrix,width,height);
			 for(int i=0;i<height;i++){
				 delete[] compareMatrix[i];
			 }
			 delete[] compareMatrix;
			 this->textBox2->Text+=Directory::GetCurrentDirectory();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			double tstart, tstop, ttime;
			tstart = (double)clock()/CLOCKS_PER_SEC;
			OCRDecoder1->LineBox_All();
			disValueBox->Text=Convert::ToString(OCRDecoder1->DivideColorValue());
			OCRDecoder1->Recognize();
			tstop = (double)clock()/CLOCKS_PER_SEC;
			ttime= tstop-tstart;
			this->textBox2->Text=OCRDecoder1->ResultStringToString();
			this->textBox2->Text+="\r\n\r\nRun Time is: "+ttime+" Secs";
		 }
private: System::Void show_scores_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox2->Text=OCRDecoder1->ResultScoreToString();
		 }
private: System::Void Otsu_Thre_Click(System::Object^  sender, System::EventArgs^  e) {
			 OCRDecoder1->OtsuThreshold();
			 disValueBox->Text=Convert::ToString(OCRDecoder1->DivideColorValue());
		 }
private: System::Void blurbtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 OCRDecoder1->Blur();
			 OCRDecoder1->LoadColorRowsIntoBitmap();
			 this->Refresh();
		 }
};
}