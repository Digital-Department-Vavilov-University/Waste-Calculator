#pragma once
#include <fstream>
#using <System.dll>
#include <tuple>
#include <vector>

namespace WasteCalculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	//Список отходов
	///(Формула: 1) - Обозначает формулу по которой расчитывается отход
	///4 06 110 01 31 3 Отходы минеральных масел моторных
	///4 06 120 01 31 3 Отходы минеральных масел гидравлических, не содержащих галогены
	///4 06 130 01 31 3 Отходы минеральных масел индустриальных
	///4 06 150 01 31 3 Отходы минеральных масел трансмиссионных
	///(Формула: 2)
	///4 06 166 01 31 3 Отходы минеральных масел компрессорных 
	///(Формула: 3) 
	///4 38 111 01 51 3 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание 5 % и более)

	//База данных отходов
	public ref class WasteData
	{
	private:
		List<String^>^ columnHeader;
		List<String^>^ columnToolTipText;
		List<String^>^ columnName;

	public:
		float resultCalculate = 0.00f;
		int formula;
		List<Tuple<String^, float>^>^ listResult = gcnew List<Tuple<String^, float>^>();
		String^ name;
		String^ code;
		String^ klass;

		WasteData()
		{
			columnHeader = gcnew List<String^>();
			columnToolTipText = gcnew List<String^>();
			columnName = gcnew List<String^>();
		}

		void Select40611001313()
		{
			name = "Отходы минеральных масел моторных";
			code = "4 06 110 01 31 3";
			klass = "3";
			formula = 1;

			columnHeader->Add("Эксплуатируемая техника");
			columnHeader->Add("Коэффициент слива масла");
			columnHeader->Add("Коэффициент, учитывающий содержание воды");
			columnHeader->Add("Средняя плотность сливаемых масел, кг/л");
			columnHeader->Add("Объем заливки масла в двигатель, л");
			columnHeader->Add("Годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас)");
			columnHeader->Add("Нормативный пробег (тыс.км) или наработка (моточас)");
			columnHeader->Add("Коэффициент, учитывающий наличие механических примесей");
			columnHeader->Add("Количество двигателей");

			columnToolTipText->Add("Название техники");
			columnToolTipText->Add("коэффициент слива масла, доли от 1 (0,70..0,90)");
			columnToolTipText->Add("коэффициент, учитывающий содержание воды, доли от 1 (1,005..1,030)");
			columnToolTipText->Add("средняя плотность сливаемых масел, кг/л (0,880..0,910)");
			columnToolTipText->Add("объем заливки масла в двигатель i - той модели, л");
			columnToolTipText->Add("годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас), с двигателем i – той модели");
			columnToolTipText->Add("нормативный пробег (тыс.км) или наработка (моточас)");
			columnToolTipText->Add("коэффициент, учитывающий наличие механических примесей, доли от 1 (1,003..1,02)");
			columnToolTipText->Add("количество двигателей i - той модели");

			columnName->Add("Technics");
			columnName->Add("KofSM");
			columnName->Add("KofW");
			columnName->Add("PSM");
			columnName->Add("VZM");
			columnName->Add("L");
			columnName->Add("H");
			columnName->Add("KofMP");
			columnName->Add("N");
		}

		void Select40612001313()
		{
			name = "Отходы минеральных масел гидравлических, не содержащих галогены";
			code = "4 06 120 01 31 3";
			klass = "3";
			formula = 1;

			columnHeader->Add("Эксплуатируемая техника");
			columnHeader->Add("Коэффициент слива масла");
			columnHeader->Add("Коэффициент, учитывающий содержание воды");
			columnHeader->Add("Средняя плотность сливаемых масел, кг/л");
			columnHeader->Add("Объем заливки масла в двигатель, л");
			columnHeader->Add("Годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас)");
			columnHeader->Add("Нормативный пробег (тыс.км) или наработка (моточас)");
			columnHeader->Add("Коэффициент, учитывающий наличие механических примесей");
			columnHeader->Add("Количество двигателей");

			columnToolTipText->Add("Название техники");
			columnToolTipText->Add("коэффициент слива масла, доли от 1 (0,80..0,90)");
			columnToolTipText->Add("коэффициент, учитывающий содержание воды, доли от 1 (1,005..1,030)");
			columnToolTipText->Add("средняя плотность сливаемых масел, кг/л (0,880..0,910)");
			columnToolTipText->Add("объем заливки масла в двигатель i - той модели, л");
			columnToolTipText->Add("годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас), с двигателем i – той модели");
			columnToolTipText->Add("нормативный пробег (тыс.км) или наработка (моточас)");
			columnToolTipText->Add("коэффициент, учитывающий наличие механических примесей, доли от 1 (1,003..1,02)");
			columnToolTipText->Add("количество двигателей i - той модели");

			columnName->Add("Technics");
			columnName->Add("KofSM");
			columnName->Add("KofW");
			columnName->Add("PSM");
			columnName->Add("VZM");
			columnName->Add("L");
			columnName->Add("H");
			columnName->Add("KofMP");
			columnName->Add("N");
		}

		void Select40613001313()
		{
			name = "Отходы минеральных масел индустриальных";
			code = "4 06 130 01 31 3";
			klass = "3";
			formula = 1;

			//Видимое название
			columnHeader->Add("Эксплуатируемая техника");
			columnHeader->Add("Коэффициент слива масла");
			columnHeader->Add("Коэффициент, учитывающий содержание воды");
			columnHeader->Add("Средняя плотность сливаемых масел, кг/л");
			columnHeader->Add("Объем заливки масла в двигатель, л");
			columnHeader->Add("Годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас)");
			columnHeader->Add("Нормативный пробег (тыс.км) или наработка (моточас)");
			columnHeader->Add("Коэффициент, учитывающий наличие механических примесей");
			columnHeader->Add("Количество двигателей на единице технике");

			//Описание
			columnToolTipText->Add("Название техники");
			columnToolTipText->Add("коэффициент слива масла, доли от 1 (0,70..0,90)");
			columnToolTipText->Add("коэффициент, учитывающий содержание воды, доли от 1 (1,005..1,030)");
			columnToolTipText->Add("средняя плотность сливаемых масел, кг/л (0,880..0,910)");
			columnToolTipText->Add("объем заливки масла в двигатель i - той модели, л");
			columnToolTipText->Add("годовой пробег автотранспортной единицы (тыс.км.) или наработка механизма (моточас), с двигателем i – той модели");
			columnToolTipText->Add("нормативный пробег (тыс.км) или наработка (моточас)");
			columnToolTipText->Add("коэффициент, учитывающий наличие механических примесей, доли от 1 (1,003..1,02)");
			columnToolTipText->Add("количество двигателей i - той модели");

			//Техническое название
			columnName->Add("Technics");
			columnName->Add("KofSM");
			columnName->Add("KofW");
			columnName->Add("PSM");
			columnName->Add("VZM");
			columnName->Add("L");
			columnName->Add("H");
			columnName->Add("KofMP");
			columnName->Add("N");
		}

		void Select40615001313()
		{
			name = "Отходы минеральных масел трансмиссионных";
			code = "4 06 150 01 31 3";
			klass = "3";
			formula = 1;

			//Видимое название
			columnHeader->Add("Эксплуатируемая техника");
			columnHeader->Add("Коэффициент слива масла");
			columnHeader->Add("Коэффициент, учитывающий содержание воды");
			columnHeader->Add("Средняя плотность сливаемых масел, кг/л");
			columnHeader->Add("Сбъем заливки трансмиссионного масла в систему, л");
			columnHeader->Add("Пробег (наработка) трансмиссионной системы, тыс. км (моточас)");
			columnHeader->Add("Нормативный пробег (наработка) трансмиссионной системы, тыс. км (моточас)");
			columnHeader->Add("Коэффициент, учитывающий наличие механических примесей");
			columnHeader->Add("Количество трансмиссионных систем");

			//Описание
			columnToolTipText->Add("Название техники");
			columnToolTipText->Add("коэффициент слива масла, доли от 1 (0,8..0,9)");
			columnToolTipText->Add("коэффициент, учитывающий содержание воды, доли от 1 (1,005..1,03)");
			columnToolTipText->Add("средняя плотность сливаемых масел, кг/л");
			columnToolTipText->Add("объем заливки трансмиссионного масла в систему i - той модели, л");
			columnToolTipText->Add("пробег (наработка) трансмиссионной системы  i – той модели, тыс. км (моточас)");
			columnToolTipText->Add("нормативный пробег (наработка) трансмиссионной системы  i – той модели, тыс. км (моточас)");
			columnToolTipText->Add("коэффициент, учитывающий наличие механических примесей, доли от 1 (1,01..1,03)");
			columnToolTipText->Add("количество трансмиссионных систем i - той модели");

			//Техническое название
			columnName->Add("Technics");
			columnName->Add("KofSM");
			columnName->Add("KofW");
			columnName->Add("PSM");
			columnName->Add("VZM");
			columnName->Add("L");
			columnName->Add("H");
			columnName->Add("KofMP");
			columnName->Add("N");
		}

		void Select40616601313()
		{
			name = "Отходы минеральных масел компрессорных";
			code = "4 06 166 01 31 3";
			klass = "3";
			formula = 2;

			//Видимое название
			columnHeader->Add("Эксплуатируемая техника");
			columnHeader->Add("Годовой расход масла компрессорного, кг");
			columnHeader->Add("Удельный расход масла компрессорного, %");

			//Описание
			columnToolTipText->Add("Название техники");
			columnToolTipText->Add("годовой расход масла компрессорного, кг");
			columnToolTipText->Add("удельный расход масла компрессорного, %");

			//Техническое название
			columnName->Add("Technics");
			columnName->Add("M");
			columnName->Add("H");
		}

		void Select43811101513()
		{
			name = "Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание 5 % и более)";
			code = "4 38 111 01 51 3";
			klass = "3";
			formula = 3;

			//Видимое название
			columnHeader->Add("Название ЛКМ");
			columnHeader->Add("Расход лакокрасочных материалов, кг");
			columnHeader->Add("Вес лакокрасочных материалов в одной упаковке, кг");
			columnHeader->Add("Вес пустой упаковки из под лакокрасочных материалов, кг");

			//Описание
			columnToolTipText->Add("Название ЛКМ");
			columnToolTipText->Add("расход лакокрасочных материалов i-го вида, кг");
			columnToolTipText->Add("вес лакокрасочных материалов i-го вида в одной упаковке, кг");
			columnToolTipText->Add("вес пустой упаковки из под лакокрасочных материалов i-го вида, кг.");

			//Техническое название
			columnName->Add("NameLKM");
			columnName->Add("Q");
			columnName->Add("M");
			columnName->Add("m");
		}

		//Шаблон для отхода 
		void SelectExample()
		{
			name = "";
			code = "";
			klass = "";
			formula = 1;

			//Видимое название
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");
			columnHeader->Add("");

			//Описание
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");
			columnToolTipText->Add("");

			//Техническое название
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
			columnName->Add("");
		}

		void SelectWaste(String^ typeWaste)
		{
			columnHeader->Clear();
			columnToolTipText->Clear();
			columnName->Clear();

			//MessageBox::Show(typeWaste);

			if (typeWaste == "40611001313 Отходы минеральных масел моторных") Select40611001313();
			else if (typeWaste == "40612001313 Отходы минеральных масел гидравлических, не содержащих галогены") Select40612001313();
			else if (typeWaste == "40613001313 Отходы минеральных масел индустриальных") Select40613001313();
			else if (typeWaste == "40615001313 Отходы минеральных масел трансмиссионных") Select40615001313();
			else if (typeWaste == "40616601313 Отходы минеральных масел компрессорных") Select40616601313();
			else if (typeWaste == "43811101513 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание 5 % и более)") Select43811101513();
		}

		String^ GetName()
		{
			return name;
		}

		String^ GetCode()
		{
			return code;
		}

		String^ GetKlass()
		{
			return klass;
		}

		String^ GetItem(int type,int index)
		{
			if (type == 1 && index >= 0 && index < columnHeader->Count)
			{
				return columnHeader[index];
			}
			else if (type == 2 && index >= 0 && index < columnToolTipText->Count)
			{
				return columnToolTipText[index];
			}
			else if (type == 3 && index >= 0 && index < columnName->Count)
			{
				return columnName[index];
			}
			else
			{
				throw gcnew IndexOutOfRangeException("Индекс находится вне диапазона списка.");
			}
		}

		int GetItemCount()
		{
			return columnHeader->Count;
		}

		float Formula(List<float>^ floatList)
		{
			switch (formula)
			{
			case 1:
				//kofSM * kofW * pSM * vZM * kofMP * n * l / h * 0.001;
				return floatList[0] * floatList[1] * floatList[2] * floatList[3] *
					floatList[4] * floatList[5] * floatList[6] / floatList[7] * 0.001f;
			case 2:
				//M * H * 0,00001
				return floatList[0] * floatList[1] * 0.00001f;
			case 3:
				//Q / M * m * 0.001f
				return floatList[0] / floatList[1] * floatList[2] * 0.001f;
			default:
				return 0;
			}
		}

		void CalculateResults(DataGridView^ tablePropertyWaste, String^ selectedWaste)
		{
			SelectWaste(selectedWaste);

			// Переменные для хранения результатов вычислений
			float totalResult = 0.00f;

			// Проходим по каждой строке таблицы
			for (int rowIndex = 0; rowIndex < tablePropertyWaste->Rows->Count - 1; ++rowIndex)
			{
				List<Object^>^ listData = gcnew List<Object^>();
				List<float>^ floatList = gcnew List<float>();
				String^ Name;

				if (tablePropertyWaste->Rows[rowIndex]->Cells->Count == columnName->Count)
				{
					for each (String ^ columnName in columnName)
					{
						// Делайте что-то с каждым значением headerText
						listData->Add(tablePropertyWaste->Rows[rowIndex]->Cells[columnName]->Value);
					}

					bool allNonEmpty = true;

					if (listData[0] != nullptr) Name = listData[0]->ToString();
					else
					{
						Name = "";
					}

					// Используем цикл foreach для проверки всех элементов кроме первого
					for (int i = 1; i < listData->Count; i++)
					{
						if (listData[i] == nullptr || listData[i]->ToString()->Trim() == "")
						{
							allNonEmpty = false;
							break;
						}
					}

					if (allNonEmpty)
					{
						//MessageBox::Show(allNonEmpty.ToString());
						for each (Object ^ obj in listData->GetRange(1, listData->Count - 1))
						{
							if (obj != nullptr && obj->ToString()->Trim() != "")
							{
								float value;
								if (Single::TryParse(obj->ToString(), value))
								{
									floatList->Add(value);
								}
								else
								{
									// Обработка ошибки, если не удалось преобразовать значение в float
								}
							}
						}

						float result = Formula(floatList);
						totalResult += result;
						listResult->Add(gcnew Tuple<String^, float>(Name, Math::Round(result, 3)));
					}
					else
					{
						// Не все элементы, кроме первого, не являются пустыми
						continue;
					}
				}
			}

			resultCalculate = Math::Round(totalResult, 3);

		}

	};

	
	//Основной код
	public ref class Company : public System::Windows::Forms::Form
	{

	private: 
		String^ INN;
		String^ COMPANY_NAME;
		String^ selectedWaste = "NULL";
		String^ organizationFolderPath;
		bool detectEdit;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ labelCompany;
	private: System::Windows::Forms::Button^ buttonHide;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem40612001313;
	private: System::Windows::Forms::ToolStripMenuItem^ actionMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exportMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ deleteMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::DataGridView^ tableResult;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textResult;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ NameParameter;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Result;
	private: System::Windows::Forms::TextBox^ labelResultKlassWaste;
	private: System::Windows::Forms::TextBox^ labelResultCodeWaste;
	private: System::Windows::Forms::TextBox^ labelResultNameWaste;
	private: System::Windows::Forms::ToolStripMenuItem^ calculateMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem40613001313;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem40615001313;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem40616601313;



	private: System::Windows::Forms::Button^ buttonClose;

	public:
		Company(String^ inn, bool FirstRun, String^ company_name)
		{
			INN = inn;
			COMPANY_NAME = company_name;

			// Определяем путь до данных организации
			// Получение пути к папке с исполняемым файлом
			String^ executablePath = Application::ExecutablePath;
			String^ folderPath = System::IO::Path::GetDirectoryName(executablePath);

			// Проверка наличия папки с указанным ИНН
			organizationFolderPath = folderPath + "\\Company\\" + INN + "\\";

			InitializeComponent();
			if (!FirstRun) LoadSavedWaste();
			ClearTableProperties();

			labelCompany->Text = COMPANY_NAME + "(ИНН: " + INN + ")";
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Company()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menu;
	private: System::Windows::Forms::ToolStripMenuItem^ addWasteMenuItem;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ Menu40600000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem40611001313;
	private: System::Windows::Forms::ListBox^ listWaste;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::TabControl^ tabPropertyWaste;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::DataGridView^ tablePropertyWaste;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;

	protected:
	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Company::typeid));
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->addWasteMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu40600000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem40611001313 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem40612001313 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem40613001313 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem40615001313 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem40616601313 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->actionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calculateMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listWaste = (gcnew System::Windows::Forms::ListBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->tabPropertyWaste = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tablePropertyWaste = (gcnew System::Windows::Forms::DataGridView());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->labelResultKlassWaste = (gcnew System::Windows::Forms::TextBox());
			this->labelResultCodeWaste = (gcnew System::Windows::Forms::TextBox());
			this->labelResultNameWaste = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textResult = (gcnew System::Windows::Forms::TextBox());
			this->tableResult = (gcnew System::Windows::Forms::DataGridView());
			this->NameParameter = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Result = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->buttonHide = (gcnew System::Windows::Forms::Button());
			this->buttonClose = (gcnew System::Windows::Forms::Button());
			this->labelCompany = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menu->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->tabPropertyWaste->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablePropertyWaste))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableResult))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// menu
			// 
			this->menu->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->menu->Dock = System::Windows::Forms::DockStyle::None;
			this->menu->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->addWasteMenuItem, this->actionMenuItem });
			this->menu->Location = System::Drawing::Point(12, 2);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(198, 24);
			this->menu->TabIndex = 0;
			this->menu->Text = L"menuStrip1";
			// 
			// addWasteMenuItem
			// 
			this->addWasteMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->Menu40600000000 });
			this->addWasteMenuItem->Name = L"addWasteMenuItem";
			this->addWasteMenuItem->Size = System::Drawing::Size(117, 20);
			this->addWasteMenuItem->Text = L"Добавить отходы";
			// 
			// Menu40600000000
			// 
			this->Menu40600000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->MenuItem40611001313,
					this->MenuItem40612001313, this->MenuItem40613001313, this->MenuItem40615001313, this->MenuItem40616601313
			});
			this->Menu40600000000->Name = L"Menu40600000000";
			this->Menu40600000000->Size = System::Drawing::Size(353, 22);
			this->Menu40600000000->Text = L"4 06 000 00 00 0 ОТХОДЫ НЕФТЕПРОДУКТОВ";
			// 
			// MenuItem40611001313
			// 
			this->MenuItem40611001313->Name = L"MenuItem40611001313";
			this->MenuItem40611001313->Size = System::Drawing::Size(561, 22);
			this->MenuItem40611001313->Text = L"40611001313 Отходы минеральных масел моторных";
			this->MenuItem40611001313->Click += gcnew System::EventHandler(this, &Company::MenuItem40611001313_Click);
			// 
			// MenuItem40612001313
			// 
			this->MenuItem40612001313->Name = L"MenuItem40612001313";
			this->MenuItem40612001313->Size = System::Drawing::Size(561, 22);
			this->MenuItem40612001313->Text = L"40612001313 Отходы минеральных масел гидравлических, не содержащих галогены";
			this->MenuItem40612001313->Click += gcnew System::EventHandler(this, &Company::MenuItem40612001313_Click);
			// 
			// MenuItem40613001313
			// 
			this->MenuItem40613001313->Name = L"MenuItem40613001313";
			this->MenuItem40613001313->Size = System::Drawing::Size(561, 22);
			this->MenuItem40613001313->Text = L"40613001313 Отходы минеральных масел индустриальных";
			this->MenuItem40613001313->Click += gcnew System::EventHandler(this, &Company::MenuItem40613001313_Click);
			// 
			// MenuItem40615001313
			// 
			this->MenuItem40615001313->Name = L"MenuItem40615001313";
			this->MenuItem40615001313->Size = System::Drawing::Size(561, 22);
			this->MenuItem40615001313->Text = L"40615001313 Отходы минеральных масел трансмиссионных";
			this->MenuItem40615001313->Click += gcnew System::EventHandler(this, &Company::MenuItem40615001313_Click);
			// 
			// MenuItem40616601313
			// 
			this->MenuItem40616601313->Name = L"MenuItem40616601313";
			this->MenuItem40616601313->Size = System::Drawing::Size(561, 22);
			this->MenuItem40616601313->Text = L"40616601313 Отходы минеральных масел компрессорных";
			this->MenuItem40616601313->Click += gcnew System::EventHandler(this, &Company::MenuItem40616601313_Click);
			// 
			// actionMenuItem
			// 
			this->actionMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->calculateMenuItem,
					this->exportMenuItem, this->deleteMenuItem
			});
			this->actionMenuItem->Name = L"actionMenuItem";
			this->actionMenuItem->Size = System::Drawing::Size(73, 20);
			this->actionMenuItem->Text = L"Действие";
			// 
			// calculateMenuItem
			// 
			this->calculateMenuItem->Name = L"calculateMenuItem";
			this->calculateMenuItem->Size = System::Drawing::Size(180, 22);
			this->calculateMenuItem->Text = L"Расчет";
			this->calculateMenuItem->Click += gcnew System::EventHandler(this, &Company::calculateMenuItem_Click);
			// 
			// exportMenuItem
			// 
			this->exportMenuItem->Name = L"exportMenuItem";
			this->exportMenuItem->Size = System::Drawing::Size(180, 22);
			this->exportMenuItem->Text = L"Экспорт";
			// 
			// deleteMenuItem
			// 
			this->deleteMenuItem->Name = L"deleteMenuItem";
			this->deleteMenuItem->Size = System::Drawing::Size(180, 22);
			this->deleteMenuItem->Text = L"Удалить";
			this->deleteMenuItem->Click += gcnew System::EventHandler(this, &Company::deleteMenuItem_Click);
			// 
			// listWaste
			// 
			this->listWaste->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listWaste->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listWaste->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->listWaste->FormattingEnabled = true;
			this->listWaste->HorizontalScrollbar = true;
			this->listWaste->ItemHeight = 15;
			this->listWaste->Location = System::Drawing::Point(12, 29);
			this->listWaste->Name = L"listWaste";
			this->listWaste->Size = System::Drawing::Size(318, 499);
			this->listWaste->TabIndex = 1;
			this->listWaste->SelectedIndexChanged += gcnew System::EventHandler(this, &Company::listWaste_SelectedIndexChanged);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 57);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->listWaste);
			this->splitContainer1->Panel1->Controls->Add(this->menu);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->tabPropertyWaste);
			this->splitContainer1->Size = System::Drawing::Size(900, 550);
			this->splitContainer1->SplitterDistance = 333;
			this->splitContainer1->TabIndex = 2;
			// 
			// tabPropertyWaste
			// 
			this->tabPropertyWaste->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabPropertyWaste->Controls->Add(this->tabPage1);
			this->tabPropertyWaste->Controls->Add(this->tabPage2);
			this->tabPropertyWaste->Location = System::Drawing::Point(0, 0);
			this->tabPropertyWaste->Margin = System::Windows::Forms::Padding(0);
			this->tabPropertyWaste->Name = L"tabPropertyWaste";
			this->tabPropertyWaste->SelectedIndex = 0;
			this->tabPropertyWaste->Size = System::Drawing::Size(548, 528);
			this->tabPropertyWaste->TabIndex = 0;
			this->tabPropertyWaste->Visible = false;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->tablePropertyWaste);
			this->tabPage1->Location = System::Drawing::Point(4, 23);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(540, 501);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Свойства";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tablePropertyWaste
			// 
			this->tablePropertyWaste->AllowUserToResizeColumns = false;
			this->tablePropertyWaste->AllowUserToResizeRows = false;
			this->tablePropertyWaste->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tablePropertyWaste->BackgroundColor = System::Drawing::Color::White;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->tablePropertyWaste->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->tablePropertyWaste->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::WindowFrame;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->tablePropertyWaste->DefaultCellStyle = dataGridViewCellStyle2;
			this->tablePropertyWaste->Location = System::Drawing::Point(8, 6);
			this->tablePropertyWaste->Name = L"tablePropertyWaste";
			this->tablePropertyWaste->Size = System::Drawing::Size(526, 492);
			this->tablePropertyWaste->TabIndex = 1;
			this->tablePropertyWaste->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Company::tablePropertyWaste_CellValueChanged);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->labelResultKlassWaste);
			this->tabPage2->Controls->Add(this->labelResultCodeWaste);
			this->tabPage2->Controls->Add(this->labelResultNameWaste);
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Controls->Add(this->textResult);
			this->tabPage2->Controls->Add(this->tableResult);
			this->tabPage2->Controls->Add(this->pictureBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(540, 502);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Результат";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// labelResultKlassWaste
			// 
			this->labelResultKlassWaste->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->labelResultKlassWaste->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->labelResultKlassWaste->Cursor = System::Windows::Forms::Cursors::Default;
			this->labelResultKlassWaste->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelResultKlassWaste->ForeColor = System::Drawing::Color::White;
			this->labelResultKlassWaste->Location = System::Drawing::Point(192, 156);
			this->labelResultKlassWaste->Name = L"labelResultKlassWaste";
			this->labelResultKlassWaste->ReadOnly = true;
			this->labelResultKlassWaste->Size = System::Drawing::Size(320, 22);
			this->labelResultKlassWaste->TabIndex = 22;
			this->labelResultKlassWaste->Text = L"Класс опасности";
			this->labelResultKlassWaste->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// labelResultCodeWaste
			// 
			this->labelResultCodeWaste->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->labelResultCodeWaste->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->labelResultCodeWaste->Cursor = System::Windows::Forms::Cursors::Default;
			this->labelResultCodeWaste->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelResultCodeWaste->ForeColor = System::Drawing::Color::White;
			this->labelResultCodeWaste->Location = System::Drawing::Point(192, 125);
			this->labelResultCodeWaste->Name = L"labelResultCodeWaste";
			this->labelResultCodeWaste->ReadOnly = true;
			this->labelResultCodeWaste->Size = System::Drawing::Size(320, 25);
			this->labelResultCodeWaste->TabIndex = 21;
			this->labelResultCodeWaste->Text = L"Код:";
			this->labelResultCodeWaste->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// labelResultNameWaste
			// 
			this->labelResultNameWaste->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->labelResultNameWaste->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->labelResultNameWaste->Cursor = System::Windows::Forms::Cursors::Default;
			this->labelResultNameWaste->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelResultNameWaste->ForeColor = System::Drawing::Color::White;
			this->labelResultNameWaste->Location = System::Drawing::Point(192, 28);
			this->labelResultNameWaste->Multiline = true;
			this->labelResultNameWaste->Name = L"labelResultNameWaste";
			this->labelResultNameWaste->ReadOnly = true;
			this->labelResultNameWaste->Size = System::Drawing::Size(320, 91);
			this->labelResultNameWaste->TabIndex = 20;
			this->labelResultNameWaste->Text = L"Результат";
			this->labelResultNameWaste->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(462, 423);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 21);
			this->label1->TabIndex = 19;
			this->label1->Text = L"т/год";
			// 
			// textResult
			// 
			this->textResult->BackColor = System::Drawing::Color::White;
			this->textResult->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textResult->Cursor = System::Windows::Forms::Cursors::Default;
			this->textResult->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textResult->Location = System::Drawing::Point(327, 423);
			this->textResult->Name = L"textResult";
			this->textResult->ReadOnly = true;
			this->textResult->Size = System::Drawing::Size(129, 22);
			this->textResult->TabIndex = 18;
			this->textResult->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tableResult
			// 
			this->tableResult->AllowUserToAddRows = false;
			this->tableResult->AllowUserToDeleteRows = false;
			this->tableResult->AllowUserToResizeColumns = false;
			this->tableResult->AllowUserToResizeRows = false;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->tableResult->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->tableResult->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->tableResult->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->NameParameter,
					this->Result
			});
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::WindowFrame;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->tableResult->DefaultCellStyle = dataGridViewCellStyle4;
			this->tableResult->Location = System::Drawing::Point(26, 201);
			this->tableResult->Name = L"tableResult";
			this->tableResult->Size = System::Drawing::Size(486, 200);
			this->tableResult->TabIndex = 17;
			// 
			// NameParameter
			// 
			this->NameParameter->Frozen = true;
			this->NameParameter->HeaderText = L"Название";
			this->NameParameter->Name = L"NameParameter";
			this->NameParameter->ReadOnly = true;
			this->NameParameter->Width = 220;
			// 
			// Result
			// 
			this->Result->Frozen = true;
			this->Result->HeaderText = L"Результат";
			this->Result->Name = L"Result";
			this->Result->ReadOnly = true;
			this->Result->Width = 220;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(26, 28);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(150, 150);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 13;
			this->pictureBox2->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->AllowDrop = true;
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(158)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)));
			this->panel1->Controls->Add(this->buttonHide);
			this->panel1->Controls->Add(this->buttonClose);
			this->panel1->Controls->Add(this->labelCompany);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->ForeColor = System::Drawing::Color::White;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(900, 45);
			this->panel1->TabIndex = 3;
			// 
			// buttonHide
			// 
			this->buttonHide->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->buttonHide->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->buttonHide->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonHide->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonHide->Location = System::Drawing::Point(823, 7);
			this->buttonHide->Margin = System::Windows::Forms::Padding(0);
			this->buttonHide->Name = L"buttonHide";
			this->buttonHide->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->buttonHide->Size = System::Drawing::Size(30, 30);
			this->buttonHide->TabIndex = 12;
			this->buttonHide->Text = L"_";
			this->buttonHide->UseVisualStyleBackColor = false;
			this->buttonHide->Click += gcnew System::EventHandler(this, &Company::buttonHide_Click);
			// 
			// buttonClose
			// 
			this->buttonClose->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->buttonClose->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->buttonClose->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->buttonClose->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonClose->Location = System::Drawing::Point(863, 7);
			this->buttonClose->Margin = System::Windows::Forms::Padding(0);
			this->buttonClose->Name = L"buttonClose";
			this->buttonClose->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->buttonClose->Size = System::Drawing::Size(30, 30);
			this->buttonClose->TabIndex = 11;
			this->buttonClose->Text = L"✖";
			this->buttonClose->UseVisualStyleBackColor = false;
			this->buttonClose->Click += gcnew System::EventHandler(this, &Company::buttonClose_Click);
			// 
			// labelCompany
			// 
			this->labelCompany->AutoSize = true;
			this->labelCompany->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->labelCompany->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelCompany->Location = System::Drawing::Point(62, 15);
			this->labelCompany->Name = L"labelCompany";
			this->labelCompany->Size = System::Drawing::Size(126, 22);
			this->labelCompany->TabIndex = 2;
			this->labelCompany->Text = L"Организация";
			this->labelCompany->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 7);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(35, 35);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// Company
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)));
			this->ClientSize = System::Drawing::Size(900, 600);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->splitContainer1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menu;
			this->Name = L"Company";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->tabPropertyWaste->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablePropertyWaste))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tableResult))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}


#pragma endregion

	void MenuItem40611001313_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		NewWasteInList(MenuItem40611001313->Text);
	}

	void MenuItem40612001313_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		NewWasteInList(MenuItem40612001313->Text);
	}

	void MenuItem40613001313_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		NewWasteInList(MenuItem40613001313->Text);
	}

	void MenuItem40615001313_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		NewWasteInList(MenuItem40615001313->Text);
	}

	void MenuItem40616601313_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		NewWasteInList(MenuItem40616601313->Text);
	}

	//Добавление нового отхода в список - Не изменять
	void NewWasteInList(String^ value)
	{
		if (!tabPropertyWaste->Visible)
			tabPropertyWaste->Visible = true;

		bool have = false;

		for (int i = 0; i < listWaste->Items->Count; i++)
		{
			if (String::Equals(listWaste->Items[i]->ToString(), value))
			{
				have = true;
				listWaste->SelectedIndex = i; // Выбираем элемент, если уже существует
				break;
			}
		}

		if (!have)
		{
			listWaste->Items->Add(value);
			listWaste->SelectedIndex = listWaste->Items->Count - 1; // Выбираем новый элемент
			SaveListWaste();
		}
		else
		{
			MessageBox::Show("Значение уже существует в списке.", "Повторное значение");
		}
	}

	//Сохранение списка отходов - Не изменять
	void SaveListWaste()
	{
		//if (listWaste->Items->Count < 1)
		//{
		//	return;
		//}

		System::IO::StreamWriter^ sw;

		sw = gcnew System::IO::StreamWriter(organizationFolderPath + "Waste.txt");

		// Создаем или открываем файл для записи

		// Записываем каждый тип отходов в файл
		for each (String ^ wasteType  in listWaste->Items)
		{
			sw->WriteLine(wasteType);
		}

		// Закрываем файл
		sw->Close();
	}

	//Загрузка списка отходов - Не изменять
	void LoadSavedWaste()
	{
		try
		{
			// Формирование пути к файлу отходов
			String^ wasteFilePath = organizationFolderPath + "Waste.txt";

			// Проверяем существование файла
			if (System::IO::File::Exists(wasteFilePath))
			{
				// Читаем строки из файла
				array<String^>^ lines = System::IO::File::ReadAllLines(wasteFilePath);

				// Добавляем отходы в listWaste
				listWaste->Items->AddRange(lines);
			}

		}
		catch (Exception^ e)
		{
			MessageBox::Show("Ошибка при чтении файла: " + e->Message, "Ошибка");
		}
	}

	//Сохранение параметров отхода  - Не изменять
	void SaveWasteProperties(String^ wasteType)
	{
		// Название файла для свойств будет таким же, как и название отхода,
		// но с измененным расширением на ".properties" (например, "Отход1.properties")
		String^ propertiesFileName = organizationFolderPath + wasteType + ".txt";

		// Создаем или открываем файл для записи свойств
		System::IO::StreamWriter^ propertiesWriter = gcnew System::IO::StreamWriter(propertiesFileName);

		int columnCount = 0;
		WasteData^ list = gcnew WasteData();

		list->SelectWaste(wasteType);

		columnCount = list->GetItemCount();


		// Проходим по каждой строке таблицы
		for (int rowIndex = 0; rowIndex < tablePropertyWaste->Rows->Count - 1; ++rowIndex)
		{
			// Записываем значения свойств в файл

			for (int i = 0; i < columnCount; i++)
			{
				propertiesWriter->WriteLine(tablePropertyWaste->Rows[rowIndex]->Cells[i]->Value);
			}

			propertiesWriter->WriteLine(); // Пустая строка для разделения записей
		}

		// Закрываем файл со свойствами
		propertiesWriter->Close();
	}

	//Загрузка параметров отхода  - Не изменять
	void LoadWasteProperties(String^ wasteType)
	{
		// Название файла для свойств
		String^ propertiesFileName = organizationFolderPath + wasteType + ".txt";

		try
		{
			// Создаем или открываем файл для чтения свойств
			System::IO::StreamReader^ propertiesReader = gcnew System::IO::StreamReader(propertiesFileName);
			
			int columnCount = 0;
			WasteData^ list = gcnew WasteData();

			list->SelectWaste(wasteType);

			columnCount = list->GetItemCount();

			List<String^>^ rowData = gcnew List<String^>();

			// Проходим по каждой строке в файле свойств
			while (!propertiesReader->EndOfStream)
			{
				// Читаем значения свойств из файла


				for (int i = 0; i < columnCount; i++)
				{
					rowData->Add(propertiesReader->ReadLine());
				}

				// Добавляем новую строку в таблицу
				array<String^>^ rowArray = rowData->ToArray();
				tablePropertyWaste->Rows->Add(rowArray);
				rowData->Clear();

				// Читаем пустую строку для разделения записей
				propertiesReader->ReadLine();
			}
				

			// Закрываем файл со свойствами
			propertiesReader->Close();
		}
		catch (Exception^ ex)
		{
		}
	}

	//Расчеты
	//Нажатие на действие "Расчет"
	void calculateMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		CalculateWaste(selectedWaste);
	}

	// Главный
	void CalculateWaste(String^ typeWaste)
	{
		WasteData^ WD = gcnew WasteData();
		WD->resultCalculate = 0.00f;
		WD->listResult->Clear();

		/*resultCalculate = 0.00f;
		listResult->Clear();*/
		ClearTableResult();

		WD->CalculateResults(tablePropertyWaste, typeWaste);

		for each (Tuple<String^, float> ^ pair in WD->listResult)
		{
			// Извлечь первое и второе значение из пары
			String^ firstValue = pair->Item1;
			float secondValue = pair->Item2;

			// Создать массив объектов, содержащий значения для добавления в таблицу
			array<Object^>^ rowValues = { firstValue, secondValue };

			// Добавить значения в таблицу в новую строку
			tableResult->Rows->Add(rowValues);

		}

		textResult->Text = WD->resultCalculate.ToString();
	}

	//Очистка таблицы с параметрами  - Не изменять
	void ClearTableProperties()
	{
		// Удаление каждого столбца по очереди, начиная с последнего
		while (tablePropertyWaste->Columns->Count > 0)
		{
			tablePropertyWaste->Columns->RemoveAt(tablePropertyWaste->Columns->Count - 1);
		}
	}

	//Очистка таблицы с результатами  - Не изменять
	void ClearTableResult()
	{
		for (int i = tableResult->Rows->Count - 1; i >= 0; i--)
		{
			// Удаляем строку по индексу
			tableResult->Rows->RemoveAt(i);
		}
		
		textResult->Text = "";
	}

	//Выбор отхода в списке  - Не изменять
	void SelectWesteInList(String^ wasteType)
	{
		if (detectEdit)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show("Хотите сохранить измененные данные?", "Подтверждение сохранения", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			// Проверяем результат диалогового окна
			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				// Пользователь выбрал "Да", обработайте сохранение данных здесь
				// Например, вызовите функцию для сохранения данных
				SaveWasteProperties(selectedWaste);
			}
			else
			{
				// Пользователь выбрал "Нет" или закрыл диалоговое окно, можно выполнить какие-то дополнительные действия или просто продолжить выполнение программы
			}
		}

		ClearTableProperties();
		
		
		detectEdit = false;
		selectedWaste = wasteType;

		int columnCount = 0;
		WasteData^ list = gcnew WasteData();

		tabPropertyWaste->SelectTab(0);

		list->SelectWaste(wasteType);
		columnCount = list->GetItemCount();

		// Добавляем новые столбцы в таблицу
		for (int i = 0; i < columnCount; i++)
		{
			String^ headerText = list->GetItem(1, i); // Получаем элемент из списка по индексу i
			String^ ToolTipText = list->GetItem(2, i); // Получаем подсказку из списка по индексу i
			String^ name = list->GetItem(3, i); // Получаем имя из списка по индексу i

			// Добавляем новый столбец в таблицу
			tablePropertyWaste->Columns->Add(name, headerText);
			tablePropertyWaste->Columns[name]->ToolTipText = ToolTipText;
			//MessageBox::Show("Таблица обновлена");

			labelResultNameWaste->Text = list->GetName();
			labelResultCodeWaste->Text = "Код : " + list->GetCode();
			labelResultKlassWaste->Text = "Класс опасности: " + list->GetKlass();
		}

		
	}

	// Обработка события нажатия на элемент в списке отходов  - Не изменять
	void listWaste_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (listWaste->SelectedIndex >= 0)
		{
			tabPropertyWaste->Visible = true;
			if (listWaste->SelectedItem->ToString() != selectedWaste)
			{
				//MessageBox::Show(listWaste->SelectedItem->ToString());
				SelectWesteInList(listWaste->SelectedItem->ToString());
				LoadWasteProperties(listWaste->SelectedItem->ToString());
				CalculateWaste(listWaste->SelectedItem->ToString());
			}
		}
		else
		{
			tabPropertyWaste->Visible = false;
		}
	}

	//Закрытие программы  - Не изменять
	void buttonClose_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (detectEdit)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show("Хотите сохранить измененные данные?", "Подтверждение сохранения", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			// Проверяем результат диалогового окна
			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				// Пользователь выбрал "Да", обработайте сохранение данных здесь
				// Например, вызовите функцию для сохранения данных
				SaveWasteProperties(selectedWaste);
			}
			else
			{
				// Пользователь выбрал "Нет" или закрыл диалоговое окно, можно выполнить какие-то дополнительные действия или просто продолжить выполнение программы
			}
		}

		this->Close();
	}

	//Свернуть программу - Не изменять
	void buttonHide_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->WindowState = FormWindowState::Minimized;
	}

	//Обработка изменеией в таблице параметров отходов  - Не изменять
	void tablePropertyWaste_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) 
	{
		detectEdit = true;
		CalculateWaste(selectedWaste);
	}

	// Удаления отхода их списка
	void DeleteWasteAndFile(String^ wasteType)
	{
		try
		{
			// Получаем путь к файлу отхода
			String^ wasteFilePath = organizationFolderPath + wasteType + ".txt";

			// Проверяем существует ли файл
			if (System::IO::File::Exists(wasteFilePath))
			{
				// Удаляем файл
				System::IO::File::Delete(wasteFilePath);
			}

			// Удаляем отход из списка
			for (int i = 0; i < listWaste->Items->Count; i++)
			{
				if (String::Equals(listWaste->Items[i]->ToString(), wasteType))
				{
					listWaste->Items->RemoveAt(i);
					break;
				}
			}

			// Если после удаления список стал пустым, скрываем tabPropertyWaste
			if (listWaste->Items->Count == 0)
				tabPropertyWaste->Visible = false;
		}
		catch (Exception^ ex)
		{
		}
	}
	void deleteMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		DeleteWasteAndFile(selectedWaste);
		MessageBox::Show("Отход успешно удален.", "Успешное удаление");
		SaveListWaste();
	}



};
}

