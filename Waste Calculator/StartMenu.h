#pragma once
#include <iostream>
#include <fstream>
#include "Company.h"
#include <msclr\marshal_cppstd.h>
#include <vector>
#include <Windows.h>

namespace WasteCalculator {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class StartMenu : public System::Windows::Forms::Form
    {
    public:
        StartMenu(void)
        {
            InitializeComponent();
            LoadSavedOrganizations(); // Загрузка списка организаций при инициализации формы
            buttonDelete->Visible = false;
            this->listBoxSavedOrganizations->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &StartMenu::listBoxSavedOrganizations_MouseDoubleClick);
        }

    protected:
    private: System::ComponentModel::IContainer^ components;

    private:
        System::Windows::Forms::Label^ labelCompanyName;
        System::Windows::Forms::TextBox^ textBoxCompanyName;
        System::Windows::Forms::Label^ labelCompanyINN;
        System::Windows::Forms::TextBox^ textBoxCompanyINN;
    private: System::Windows::Forms::Button^ buttonClose;

           System::Windows::Forms::ListBox^ listBoxSavedOrganizations;
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Button^ buttonHide;
    private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
    private: System::Windows::Forms::Button^ buttonDelete;

           System::Windows::Forms::Button^ buttonStart;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(StartMenu::typeid));
            this->labelCompanyName = (gcnew System::Windows::Forms::Label());
            this->textBoxCompanyName = (gcnew System::Windows::Forms::TextBox());
            this->labelCompanyINN = (gcnew System::Windows::Forms::Label());
            this->textBoxCompanyINN = (gcnew System::Windows::Forms::TextBox());
            this->buttonStart = (gcnew System::Windows::Forms::Button());
            this->listBoxSavedOrganizations = (gcnew System::Windows::Forms::ListBox());
            this->buttonClose = (gcnew System::Windows::Forms::Button());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->buttonHide = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
            this->buttonDelete = (gcnew System::Windows::Forms::Button());
            this->panel1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->SuspendLayout();
            // 
            // labelCompanyName
            // 
            this->labelCompanyName->AutoSize = true;
            this->labelCompanyName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelCompanyName->Location = System::Drawing::Point(74, 101);
            this->labelCompanyName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->labelCompanyName->Name = L"labelCompanyName";
            this->labelCompanyName->Size = System::Drawing::Size(215, 22);
            this->labelCompanyName->TabIndex = 0;
            this->labelCompanyName->Text = L"Название организации:";
            // 
            // textBoxCompanyName
            // 
            this->textBoxCompanyName->BackColor = System::Drawing::Color::White;
            this->textBoxCompanyName->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBoxCompanyName->Location = System::Drawing::Point(78, 140);
            this->textBoxCompanyName->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->textBoxCompanyName->Name = L"textBoxCompanyName";
            this->textBoxCompanyName->Size = System::Drawing::Size(211, 29);
            this->textBoxCompanyName->TabIndex = 1;
            // 
            // labelCompanyINN
            // 
            this->labelCompanyINN->AutoSize = true;
            this->labelCompanyINN->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelCompanyINN->Location = System::Drawing::Point(91, 192);
            this->labelCompanyINN->Margin = System::Windows::Forms::Padding(0);
            this->labelCompanyINN->Name = L"labelCompanyINN";
            this->labelCompanyINN->Size = System::Drawing::Size(174, 22);
            this->labelCompanyINN->TabIndex = 2;
            this->labelCompanyINN->Text = L"ИНН организации:";
            // 
            // textBoxCompanyINN
            // 
            this->textBoxCompanyINN->BackColor = System::Drawing::Color::White;
            this->textBoxCompanyINN->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBoxCompanyINN->Location = System::Drawing::Point(78, 233);
            this->textBoxCompanyINN->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->textBoxCompanyINN->Name = L"textBoxCompanyINN";
            this->textBoxCompanyINN->Size = System::Drawing::Size(211, 29);
            this->textBoxCompanyINN->TabIndex = 3;
            // 
            // buttonStart
            // 
            this->buttonStart->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(158)),
                static_cast<System::Int32>(static_cast<System::Byte>(135)));
            this->buttonStart->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
            this->buttonStart->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonStart->ForeColor = System::Drawing::Color::White;
            this->buttonStart->Location = System::Drawing::Point(125, 287);
            this->buttonStart->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->buttonStart->Name = L"buttonStart";
            this->buttonStart->Size = System::Drawing::Size(117, 30);
            this->buttonStart->TabIndex = 4;
            this->buttonStart->Text = L"Начать";
            this->buttonStart->UseVisualStyleBackColor = false;
            this->buttonStart->Click += gcnew System::EventHandler(this, &StartMenu::buttonStart_Click);
            // 
            // listBoxSavedOrganizations
            // 
            this->listBoxSavedOrganizations->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->listBoxSavedOrganizations->BackColor = System::Drawing::Color::White;
            this->listBoxSavedOrganizations->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->listBoxSavedOrganizations->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->listBoxSavedOrganizations->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
                static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(37)));
            this->listBoxSavedOrganizations->FormattingEnabled = true;
            this->listBoxSavedOrganizations->ItemHeight = 19;
            this->listBoxSavedOrganizations->Location = System::Drawing::Point(379, 58);
            this->listBoxSavedOrganizations->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->listBoxSavedOrganizations->Name = L"listBoxSavedOrganizations";
            this->listBoxSavedOrganizations->Size = System::Drawing::Size(454, 361);
            this->listBoxSavedOrganizations->TabIndex = 5;
            this->listBoxSavedOrganizations->SelectedIndexChanged += gcnew System::EventHandler(this, &StartMenu::listBoxSavedOrganizations_SelectedIndexChanged);
            // 
            // buttonClose
            // 
            this->buttonClose->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
                static_cast<System::Int32>(static_cast<System::Byte>(37)));
            this->buttonClose->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
            this->buttonClose->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
            this->buttonClose->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonClose->Location = System::Drawing::Point(816, 5);
            this->buttonClose->Margin = System::Windows::Forms::Padding(0);
            this->buttonClose->Name = L"buttonClose";
            this->buttonClose->RightToLeft = System::Windows::Forms::RightToLeft::No;
            this->buttonClose->Size = System::Drawing::Size(30, 30);
            this->buttonClose->TabIndex = 6;
            this->buttonClose->Text = L"✖";
            this->buttonClose->UseVisualStyleBackColor = false;
            this->buttonClose->Click += gcnew System::EventHandler(this, &StartMenu::button1_Click);
            // 
            // panel1
            // 
            this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(158)),
                static_cast<System::Int32>(static_cast<System::Byte>(135)));
            this->panel1->Controls->Add(this->buttonHide);
            this->panel1->Controls->Add(this->label1);
            this->panel1->Controls->Add(this->buttonClose);
            this->panel1->Controls->Add(this->pictureBox1);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(861, 41);
            this->panel1->TabIndex = 7;
            // 
            // buttonHide
            // 
            this->buttonHide->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
                static_cast<System::Int32>(static_cast<System::Byte>(37)));
            this->buttonHide->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
            this->buttonHide->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
            this->buttonHide->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonHide->Location = System::Drawing::Point(776, 5);
            this->buttonHide->Margin = System::Windows::Forms::Padding(0);
            this->buttonHide->Name = L"buttonHide";
            this->buttonHide->RightToLeft = System::Windows::Forms::RightToLeft::No;
            this->buttonHide->Size = System::Drawing::Size(30, 30);
            this->buttonHide->TabIndex = 10;
            this->buttonHide->Text = L"_";
            this->buttonHide->UseVisualStyleBackColor = false;
            this->buttonHide->Click += gcnew System::EventHandler(this, &StartMenu::button2_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
                static_cast<System::Int32>(static_cast<System::Byte>(37)));
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(74, 11);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(191, 19);
            this->label1->TabIndex = 9;
            this->label1->Text = L"ВЫБОР ОРГАНИЗАЦИИ";
            // 
            // pictureBox1
            // 
            this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
            this->pictureBox1->Location = System::Drawing::Point(4, 3);
            this->pictureBox1->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(62, 35);
            this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->pictureBox1->TabIndex = 8;
            this->pictureBox1->TabStop = false;
            // 
            // buttonDelete
            // 
            this->buttonDelete->BackColor = System::Drawing::Color::Firebrick;
            this->buttonDelete->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
            this->buttonDelete->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonDelete->ForeColor = System::Drawing::Color::White;
            this->buttonDelete->Location = System::Drawing::Point(125, 332);
            this->buttonDelete->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->buttonDelete->Name = L"buttonDelete";
            this->buttonDelete->Size = System::Drawing::Size(117, 30);
            this->buttonDelete->TabIndex = 8;
            this->buttonDelete->Text = L"Удалить";
            this->buttonDelete->UseVisualStyleBackColor = false;
            this->buttonDelete->Click += gcnew System::EventHandler(this, &StartMenu::buttonDelete_Click);
            // 
            // StartMenu
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
                static_cast<System::Int32>(static_cast<System::Byte>(37)));
            this->ClientSize = System::Drawing::Size(861, 452);
            this->Controls->Add(this->buttonDelete);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->listBoxSavedOrganizations);
            this->Controls->Add(this->buttonStart);
            this->Controls->Add(this->textBoxCompanyINN);
            this->Controls->Add(this->labelCompanyINN);
            this->Controls->Add(this->textBoxCompanyName);
            this->Controls->Add(this->labelCompanyName);
            this->DoubleBuffered = true;
            this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->ForeColor = System::Drawing::SystemColors::Control;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
            this->Name = L"StartMenu";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"StartMenu";
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

        void CreateOrganizationFolderAndFile(String^ companyName, String^ companyINN)
        {
            System::IO::StreamWriter^ sw;
            try
            {
                // Получение пути к папке с исполняемым файлом
                String^ executablePath = Application::ExecutablePath;
                String^ folderPath = System::IO::Path::GetDirectoryName(executablePath);

                // Проверка наличия папки с указанным ИНН
                System::IO::Directory::CreateDirectory(folderPath + "\\Company\\");

                // Получаем атрибуты текущей директории
                System::IO::FileAttributes attributes = System::IO::File::GetAttributes(folderPath + "\\Company\\");

                // Добавляем атрибут "скрытый"
                attributes = static_cast<System::IO::FileAttributes>(attributes | System::IO::FileAttributes::Hidden);

                // Устанавливаем новые атрибуты
                System::IO::File::SetAttributes(folderPath + "\\Company\\", attributes);

                String^ organizationFolderPath = folderPath + "\\Company\\" + companyINN;
                if (System::IO::Directory::Exists(organizationFolderPath))
                {
                    // Если папка существует, выводим сообщение об ошибке и завершаем функцию
                    MessageBox::Show("Организация с таким ИНН уже существует.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                // Создание папки с названием ИНН организации
                System::IO::Directory::CreateDirectory(organizationFolderPath);

                // Сохранение названия организации в текстовый файл General.txt
                sw = gcnew System::IO::StreamWriter(organizationFolderPath + "\\General.txt");
                sw->WriteLine("Название организации: " + companyName);
                sw->Close();

                MessageBox::Show("Организация успешно создана и сохранена.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

                Company^ mainForm = gcnew Company(companyINN, true, companyName);
                mainForm->Text = companyName + " (ИНН:" + companyINN + ")";

                // Закрыть текущее окно StartMenu
                this->Hide();

                // Показать основное окно модально (ShowDialog)
                mainForm->ShowDialog();

                // После закрытия основного окна, закрыть приложение
                this->Close();
            }
            catch (Exception^ e)
            {
                // Обработка исключения
                MessageBox::Show("Ошибка: " + e->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

                // Закрыть StreamWriter в случае исключения
                if (sw != nullptr)
                {
                    sw->Close();
                }
            }
        }

        System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e)
        {
            LoadOrgList();
            // Получите значения из textBoxCompanyName и textBoxCompanyINN
            String^ companyName = textBoxCompanyName->Text;
            String^ companyINN = textBoxCompanyINN->Text;

            // Проверка на пустые строки
            if (String::IsNullOrWhiteSpace(companyName) || String::IsNullOrWhiteSpace(companyINN))
            {
                MessageBox::Show("Пожалуйста, заполните все поля.", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Проверка на то, что в ИНН содержатся только цифры
            if (System::Text::RegularExpressions::Regex::IsMatch(companyINN, "\\D"))
            {
                MessageBox::Show("ИНН должен содержать только цифры.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;  // Прекратить выполнение, если ИНН содержит нецифровые символы
            }

            // Проверка существования папки с указанным ИНН
            CreateOrganizationFolderAndFile(companyName, companyINN);
        }

        void LoadOrgList()
        {
            // Проверка, что в списке есть выбранный элемент
            if (listBoxSavedOrganizations->SelectedItem != nullptr)
            {
                // Получение названия организации и ИНН из выбранного элемента
                String^ selectedItemText = listBoxSavedOrganizations->SelectedItem->ToString();

                // Используйте регулярные выражения или другие методы для извлечения названия и ИНН
                // В примере предполагается, что формат текста: "Название организации (ИНН: xxx)"
                String^ organizationName;
                String^ organizationINN;

                // Пример разделения текста (ваш код может отличаться в зависимости от формата)
                array<String^>^ parts = selectedItemText->Split(gcnew array<wchar_t>{'(', ')'}, StringSplitOptions::RemoveEmptyEntries);
                if (parts->Length == 2)
                {
                    organizationName = parts[0]->Trim();
                    organizationINN = parts[1]->Replace("ИНН:", "")->Trim();
                }
                else
                {
                    // Обработка ошибки или вывод сообщения об ошибке
                    MessageBox::Show("Ошибка при разборе текста элемента списка.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                // Создание экземпляра основного окна Company и передача данных
                Company^ mainForm = gcnew Company(organizationINN, false, organizationName);
                mainForm->Text = organizationName + " (ИНН:" + organizationINN + ")";


                // Закрыть текущее окно StartMenu
                this->Hide();

                // Показать основное окно модально (ShowDialog)
                mainForm->ShowDialog();

                // После закрытия основного окна, закрыть приложение
                this->Close();
            }
        }

        // Добавление обработчика события для двойного клика по списку сохраненных организаций
        System::Void listBoxSavedOrganizations_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            LoadOrgList();
        }

        void LoadSavedOrganizations()
        {
            try
            {
                // Получение пути к папке с исполняемым файлом
                String^ executablePath = Application::ExecutablePath;
                String^ folderPath = System::IO::Path::GetDirectoryName(executablePath);
                   
                System::IO::Directory::CreateDirectory(folderPath + "\\Company");

                // Получение списка подпапок (каждая подпапка - это организация)
                array<String^>^ organizationFolders = System::IO::Directory::GetDirectories(folderPath + "\\Company");

                // Очистка списка перед загрузкой новых данных
                listBoxSavedOrganizations->Items->Clear();

                // Добавление каждой организации в listBox
                for (int i = 0; i < organizationFolders->Length; i++)
                {
                    String^ organizationINN = System::IO::Path::GetFileName(organizationFolders[i]);

                    // Чтение названия организации из файла General.txt
                    String^ generalFilePath = organizationFolders[i] + "\\General.txt";
                    if (System::IO::File::Exists(generalFilePath))
                    {
                        array<String^>^ lines = System::IO::File::ReadAllLines(generalFilePath);
                        if (lines->Length > 0)
                        {
                            String^ organizationName = lines[0];

                            // Убираем текст "Название организации:" из начала строки
                            String^ prefixToRemove = "Название организации: ";
                            if (organizationName->StartsWith(prefixToRemove))
                            {
                                organizationName = organizationName->Substring(prefixToRemove->Length);
                            }

                            listBoxSavedOrganizations->Items->Add(organizationName + " (ИНН: " + organizationINN + ")");
                        }
                    }
                }
            }
            catch (Exception^ e)
            {
                MessageBox::Show("Ошибка при загрузке списка организаций: " + e->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

    
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->WindowState = FormWindowState::Minimized;
    }

    void DeleteOrganization(String^ organizationName)
    {
        try
            {
             // Получаем путь к папке с организациями
             String^ executablePath = Application::ExecutablePath;
             String^ folderPath = System::IO::Path::GetDirectoryName(executablePath);
             String^ organizationFolderPath = folderPath + "\\Company";

             // Путь к папке выбранной организации
             String^ selectedOrganizationFolderPath = organizationFolderPath + "\\" + organizationName;

             // Проверяем существует ли папка выбранной организации
             if (System::IO::Directory::Exists(selectedOrganizationFolderPath))
             {
                // Удаляем папку организации со всем её содержимым
                System::IO::Directory::Delete(selectedOrganizationFolderPath, true);

                // Удаляем организацию из списка
                listBoxSavedOrganizations->Items->Remove(listBoxSavedOrganizations->SelectedItem->ToString());

                MessageBox::Show("Организация успешно удалена.", "Успешное удаление");
            }
            else
            {
                MessageBox::Show("Выбранная организация не существует.", "Ошибка удаления");
            }
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("Ошибка при удалении организации: " + ex->Message, "Ошибка удаления");
        }
    }
          
    void listBoxSavedOrganizations_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
    {
        buttonDelete->Visible = true;
    }

    void buttonDelete_Click(System::Object^ sender, System::EventArgs^ e) 
    {
        // Получаем выбранную организацию
        String^ selectedOrganization = listBoxSavedOrganizations->SelectedItem != nullptr ? listBoxSavedOrganizations->SelectedItem->ToString() : nullptr;

        // Получение названия организации и ИНН из выбранного элемента
        String^ selectedItemText = listBoxSavedOrganizations->SelectedItem->ToString();

        // Используйте регулярные выражения или другие методы для извлечения названия и ИНН
        // В примере предполагается, что формат текста: "Название организации (ИНН: xxx)"
        String^ organizationINN;

        // Пример разделения текста (ваш код может отличаться в зависимости от формата)
        array<String^>^ parts = selectedItemText->Split(gcnew array<wchar_t>{'(', ')'}, StringSplitOptions::RemoveEmptyEntries);
        if (parts->Length == 2)
        {
            organizationINN = parts[1]->Replace("ИНН:", "")->Trim();
        }
        DeleteOrganization(organizationINN);
        buttonDelete->Visible = false;
    }
};
}
