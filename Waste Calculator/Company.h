#pragma once
#include <fstream>
#using <System.dll>
#include <tuple>
#include <vector>
#include <windows.h>


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
	///4 38 111 02 51 4 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание менее 5 %)
	///(Формула: 4)
	///4 61 200 01 51 5 Лом и отходы стальных изделий незагрязненные
	///4 62 110 01 51 3 Лом и отходы медных изделий без покрытий незагрязненные
	///4 62 200 02 51 5 Лом электротехнических изделий из алюминия (провод, голые жилы кабелей и шнуров, шины распределительных устройств, трансформаторов, выпрямители)
	///(Формула: 5)
	///4 71 101 01 52 1 Лампы ртутные, ртутно-кварцевые, люминесцентные, утратившие потребительские свойства
	///4 82 411 00 52 5 Лампы накаливания, утратившие потребительские свойства
	///(Формула: 6)
	///4 81 203 01 52 3 Картриджи печатающих устройств с содержанием тонера 7 % и более отработанные
	///(Формула: 7)
	///7 33 100 01 72 4 Мусор от офисных и бытовых помещений организаций несортированный (исключая крупногабаритный)
	///(Формула: 8)
	///7 36 100 01 30 5 Пищевые отходы кухонь и организаций общественного питания несортированные
	///(Формула: 9)
	///9 20 110 01 53 2 Аккумуляторы свинцовые отработанные неповрежденные, с электролитом
	///(Формула: 10)
	///9 20 210 01 10 2 Кислота аккумуляторная серная отработанная
	///(Формула: 11)
	///9 20 310 01 52 5 Тормозные колодки отработанные без накладок асбестовых
	///(Формула: 12)
	///9 21 302 01 52 3 Фильтры очистки масла автотранспортных средств отработанные
	///(Формула: 13)
	///9 19 201 01 39 3 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)
	///9 19 201 02 39 4 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)
	///(Формула: 14)
	///9 19 100 02 20 4 Шлак сварочный
	///(Формула: 15)
	///9 19 100 01 20 5 Остатки и огарки стальных сварочных электродов
	///(Формула: 16)
	///9 19 204 01 60 3 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)
	///9 19 204 02 60 4 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)

	////База данных отходов
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
		void Select43811102514()
		{
			name = "Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание менее 5 %)";
			code = "4 38 111 02 51 4";
			klass = "4";
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
			columnToolTipText->Add("вес пустой упаковки из под лакокрасочных материалов i-го вида, кг");

			//Техническое название
			columnName->Add("NameLKM");
			columnName->Add("Q");
			columnName->Add("M");
			columnName->Add("m");
		}

		//Шаблон для отхода 
		void Select46120001515()
		{
			name = "Лом и отходы стальных изделий незагрязненные";
			code = "4 61 200 01 51 5";
			klass = "5";
			formula = 4;

			//Видимое название
			columnHeader->Add("Марка кабеля");
			columnHeader->Add("Длина отработанной проводки, м");
			columnHeader->Add("Масса одного погонного метра проводки, кг");

			//Описание
			columnToolTipText->Add("Марка кабеля");
			columnToolTipText->Add("Длина отработанной проводки, м");
			columnToolTipText->Add("Масса одного погонного метра проводки, кг");

			//Техническое название
			columnName->Add("CableBrand");
			columnName->Add("L");
			columnName->Add("m");
		}

		//Шаблон для отхода 
		void Select46211001513()
		{
			name = "Лом и отходы медных изделий без покрытий незагрязненные";
			code = "4 62 110 01 51 3";
			klass = "3";
			formula = 4;

			//Видимое название
			columnHeader->Add("Марка кабеля");
			columnHeader->Add("Длина отработанной проводки, м");
			columnHeader->Add("Масса одного погонного метра проводки, кг");

			//Описание
			columnToolTipText->Add("Марка кабеля");
			columnToolTipText->Add("Длина отработанной проводки, м");
			columnToolTipText->Add("Масса одного погонного метра проводки, кг");

			//Техническое название
			columnName->Add("CableBrand");
			columnName->Add("L");
			columnName->Add("m");
		}

		//Шаблон для отхода 
		void Select46220002515()
		{
			name = "Лом электротехнических изделий из алюминия (провод, голые жилы кабелей и шнуров, шины распределительных устройств, трансформаторов, выпрямители)";
			code = "4 62 200 02 51 5";
			klass = "5";
			formula = 4;

			//Видимое название
			columnHeader->Add("Марка кабеля");
			columnHeader->Add("Длина отработанной проводки, м");
			columnHeader->Add("Масса одного погонного метра проводки, кг");

			//Описание
			columnToolTipText->Add("Марка кабеля");
			columnToolTipText->Add("Длина отработанной проводки, м");
			columnToolTipText->Add("Масса одного погонного метра проводки, кг");

			//Техническое название
			columnName->Add("CableBrand");
			columnName->Add("L");
			columnName->Add("m");
		}

		//Шаблон для отхода 
		void Select47110101521()
		{
			name = "Лампы ртутные, ртутно-кварцевые, люминесцентные, утратившие потребительские свойства";
			code = "4 71 101 01 52 1";
			klass = "1";
			formula = 5;

			//Видимое название
			columnHeader->Add("Тип лампы");
			columnHeader->Add("Количество установленных источников света, шт");
			columnHeader->Add("Нормативный срок горения одного источника света, час");
			columnHeader->Add("Масса источников света, грамм");
			columnHeader->Add("Число дней в году для освещения");
			columnHeader->Add("Время работы источника света, час/смена или час/сутки");

			//Описание
			columnToolTipText->Add("Тип лампы");
			columnToolTipText->Add("Количество установленных источников света, i - того типа, шт");
			columnToolTipText->Add("Нормативный срок горения одного источника света i - того типа, час");
			columnToolTipText->Add("Масса источников света i - того типа, грамм");
			columnToolTipText->Add("Число дней в году для освещения");
			columnToolTipText->Add("Время работы источника света, час/смена или час/сутки (4.57 ч при односменной работе, 12.57 при двусменной работе, 20.57 при трехсменной работе, 10,3 ч для наружного освещения)");

			//Техническое название
			columnName->Add("LampType");
			columnName->Add("K");
			columnName->Add("H");
			columnName->Add("m");
			columnName->Add("C");
			columnName->Add("Ч");
		}

		//Шаблон для отхода 
		void Select48241100525()
		{
			name = "Лампы накаливания, утратившие потребительские свойства";
			code = "4 82 411 00 52 5";
			klass = "5";
			formula = 5;

			//Видимое название
			columnHeader->Add("Тип лампы");
			columnHeader->Add("Количество установленных источников света, шт");
			columnHeader->Add("Нормативный срок горения одного источника света, час");
			columnHeader->Add("Масса источников света, грамм");
			columnHeader->Add("Число дней в году для освещения");
			columnHeader->Add("Время работы источника света, час/смена или час/сутки");

			//Описание
			columnToolTipText->Add("Тип лампы");
			columnToolTipText->Add("Количество установленных источников света, i - того типа, шт");
			columnToolTipText->Add("Нормативный срок горения одного источника света i - того типа, час");
			columnToolTipText->Add("Масса источников света i - того типа, грамм");
			columnToolTipText->Add("Число дней в году для освещения");
			columnToolTipText->Add("Время работы источника света, час/смена или час/сутки (4.57 ч при односменной работе, 12.57 при двусменной работе, 20.57 при трехсменной работе, 10,3 ч для наружного освещения)");

			//Техническое название
			columnName->Add("LampType");
			columnName->Add("K");
			columnName->Add("H");
			columnName->Add("m");
			columnName->Add("C");
			columnName->Add("Ч");
		}

		//Шаблон для отхода 
		void Select48120301523()
		{
			name = "Картриджи печатающих устройств с содержанием тонера 7 % и более отработанные";
			code = "4 81 203 01 52 3";
			klass = "3";
			formula = 6;

			//Видимое название
			columnHeader->Add("Марка картриджа");
			columnHeader->Add("Вес использованного картриджа, г");
			columnHeader->Add("Количество листов в пачке бумаги");
			columnHeader->Add("Количество использованных пачек бумаги, шт");
			columnHeader->Add("Ресурс картриджа, листов на одну заправку");

			//Описание
			columnToolTipText->Add("Марка картриджа");
			columnToolTipText->Add("Вес использованного картриджа, г");
			columnToolTipText->Add("Количество листов в пачке бумаги");
			columnToolTipText->Add("Количество использованных пачек бумаги, шт");
			columnToolTipText->Add("Ресурс картриджа, листов на одну заправку");

			//Техническое название
			columnName->Add("CartridgeBrand");
			columnName->Add("m");
			columnName->Add("k");
			columnName->Add("n");
			columnName->Add("r");
		}

		//Шаблон для отхода 
		void Select73310001724()
		{
			name = "Мусор от офисных и бытовых помещений организаций несортированный (исключая крупногабаритный)";
			code = "7 33 100 01 72 4";
			klass = "4";
			formula = 7;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Удельный норматив образования отхода, кг/расчетную единицу в год");
			columnHeader->Add("Количество расчетных единиц");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Удельный норматив образования отхода, кг/расчетную единицу в год");
			columnToolTipText->Add("Количество расчетных единиц");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("m");
			columnName->Add("Q");
		}

		//Шаблон для отхода 
		void Select73610001305()
		{
			name = "Пищевые отходы кухонь и организаций общественного питания несортированные";
			code = "7 36 100 01 30 5";
			klass = "5";
			formula = 8;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Среднесуточное количество блюд, шт");
			columnHeader->Add("Удельный норматив образования отхода, кг/блюдо");
			columnHeader->Add("Количество дней работы столовой, дней");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Среднесуточное количество блюд, шт");
			columnToolTipText->Add("Удельный норматив образования отхода, кг/блюдо");
			columnToolTipText->Add("Количество дней работы столовой, дней");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("q");
			columnName->Add("m");
			columnName->Add("N");
		}

		//Шаблон для отхода 
		void Select92011001532()
		{
			name = "Аккумуляторы свинцовые отработанные неповрежденные, с электролитом";
			code = "9 20 110 01 53 2";
			klass = "2";
			formula = 9;

			//Видимое название
			columnHeader->Add("Марка АКБ");
			columnHeader->Add("Масса  свинцовых АКБ с электролитом, кг");
			columnHeader->Add("Количество АКБ, находящихся в эксплуатации, шт");
			columnHeader->Add("Средний срок службы  АКБ, лет");
			columnHeader->Add("Коэффициент, учитывающий частичное испарение электролита в процессе работы АКБ");

			//Описание
			columnToolTipText->Add("Марка АКБ");
			columnToolTipText->Add("Масса  свинцовых АКБ  i-той марки с электролитом, кг");
			columnToolTipText->Add("Количество АКБ  i – той марки, находящихся в эксплуатации, шт");
			columnToolTipText->Add("Средний срок службы  АКБ i – той марки, лет");
			columnToolTipText->Add("Коэффициент, учитывающий частичное испарение электролита в процессе работы АКБ i - той марки (0.75..0.95)");

			//Техническое название
			columnName->Add("AKBBrand");
			columnName->Add("m");
			columnName->Add("K");
			columnName->Add("H");
			columnName->Add("K");
		}

		//Шаблон для отхода 
		void Select92021001102()
		{
			name = "Кислота аккумуляторная серная отработанная";
			code = "9 20 210 01 10 2";
			klass = "2";
			formula = 10;

			//Видимое название
			columnHeader->Add("Марка АКБ");
			columnHeader->Add("Коэффициент слива электролита из АКБ, доли от 1");
			columnHeader->Add("Объем заливаемого в АКБ электролита, л");
			columnHeader->Add("Количество АКБ, находящихся в эксплуатации");
			columnHeader->Add("Плотность отработанного электролита, сливаемого из АКБ, кг/л");
			columnHeader->Add("Средний срок службы АКБ i - той марки, лет");

			//Описание
			columnToolTipText->Add("Марка АКБ");
			columnToolTipText->Add("Коэффициент слива электролита из АКБ, доли от 1 (0.75..0.95 с учетом испарения электролита)");
			columnToolTipText->Add("Объем заливаемого в АКБ электролита, л");
			columnToolTipText->Add("Количество АКБ i – той марки, находящихся в эксплуатации");
			columnToolTipText->Add("Плотность отработанного электролита, сливаемого из АКБ i - той марки, кг/л");
			columnToolTipText->Add("Средний срок службы АКБ i - той марки, лет");

			//Техническое название
			columnName->Add("AKBBrand");
			columnName->Add("K");
			columnName->Add("O");
			columnName->Add("K");
			columnName->Add("p");
			columnName->Add("H");
		}

		//Шаблон для отхода 
		void Select92031001525()
		{
			name = "Тормозные колодки отработанные без накладок асбестовых";
			code = "9 20 310 01 52 5";
			klass = "5";
			formula = 11;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Количество тормозных колодок на один автомобиль, шт");
			columnHeader->Add("Масса одной колодки, кг");
			columnHeader->Add("Коэффициент, учитывающий истирание колодок в процессе эксплуатации транспорта, доли от 1");
			columnHeader->Add("Годовой пробег автомобилей с тормозными колодками, тыс.км");
			columnHeader->Add("Нормативный пробег для замены колодок i-той марки, тыс.км ");


			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Количество тормозных колодок i-той марки на один автомобиль, шт");
			columnToolTipText->Add("Масса одной колодки i-той марки, кг");
			columnToolTipText->Add("Коэффициент, учитывающий истирание колодок в процессе эксплуатации транспорта, доли от 1 (для расчета норматива образования колодок равен 1)");
			columnToolTipText->Add("Годовой пробег автомобилей с тормозными колодками i-той марки, тыс.км");
			columnToolTipText->Add("Нормативный пробег для замены колодок i-той марки, тыс.км (16.00..20.00 - для легковых автомобилей; 12.00..16.00 - для грузовых автомобилей; 12.00..14.00 - для автобусов)");


			//Техническое название
			columnName->Add("Object");
			columnName->Add("N");
			columnName->Add("m");
			columnName->Add("L");
			columnName->Add("H");
			columnName->Add("K");
		}

		//Шаблон для отхода 
		void Select92130201523()
		{
			name = "Фильтры очистки масла автотранспортных средств отработанные";
			code = "9 21 302 01 52 3";
			klass = "3";
			formula = 12;

			//Видимое название
			columnHeader->Add("Марка техники");
			columnHeader->Add("Масса фильтра, кг");
			columnHeader->Add("Количество фильтров, установленных на единице техники, шт");
			columnHeader->Add("Коэффициент, учитывающий наличие механических примесей и остатков масел в отработанном фильтре");
			columnHeader->Add("Пробег техники или наработка (тыс.км или моточас)");
			columnHeader->Add("Нормативный пробег или наработка (тыс.км или моточас) до замены");

			//Описание
			columnToolTipText->Add("Марка техники");
			columnToolTipText->Add("Масса фильтра, кг");
			columnToolTipText->Add("Количество фильтров, установленных на единице техники, шт");
			columnToolTipText->Add("Коэффициент, учитывающий наличие механических примесей и остатков масел в отработанном фильтре (1,10..1,50)");
			columnToolTipText->Add("Пробег техники или наработка (тыс.км или моточас)");
			columnToolTipText->Add("Нормативный пробег или наработка (тыс.км или моточас) до замены (по характеристикам фильтров, либо принять для расчетов 15..20 тыс. км или 1680..1920 моточас)");

			//Техническое название
			columnName->Add("Technics");
			columnName->Add("m");
			columnName->Add("N");
			columnName->Add("K");
			columnName->Add("L");
			columnName->Add("H");
		}

		//Шаблон для отхода 
		void Select91920101393()
		{
			name = "Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)";
			code = "9 19 201 01 39 3";
			klass = "3";
			formula = 13;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Объем песка, израсходованного за год на засыпку нефтепродуктов, м3");
			columnHeader->Add("Плотность используемого песка, т/м3");
			columnHeader->Add("Коэффициент, учитывающий количество нефтепродуктов и механических примесей, впитанных при засыпке проливов, доли от 1");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Объем песка, израсходованного за год на засыпку нефтепродуктов, м3");
			columnToolTipText->Add("Плотность используемого песка, т/м3");
			columnToolTipText->Add("Коэффициент, учитывающий количество нефтепродуктов и механических примесей, впитанных при засыпке проливов, доли от 1 (1.15..1.30)");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("Q");
			columnName->Add("p");
			columnName->Add("K");
		}

		//Шаблон для отхода 
		void Select91920102394()
		{
			name = "Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)";
			code = "9 19 201 02 39 4";
			klass = "4";
			formula = 13;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Объем песка, израсходованного за год на засыпку нефтепродуктов, м3");
			columnHeader->Add("Плотность используемого песка, т/м3");
			columnHeader->Add("Коэффициент, учитывающий количество нефтепродуктов и механических примесей, впитанных при засыпке проливов, доли от 1");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Объем песка, израсходованного за год на засыпку нефтепродуктов, м3");
			columnToolTipText->Add("Плотность используемого песка, т/м3");
			columnToolTipText->Add("Коэффициент, учитывающий количество нефтепродуктов и механических примесей, впитанных при засыпке проливов, доли от 1 (1.15..1.30)");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("Q");
			columnName->Add("p");
			columnName->Add("K");
		}

		//Шаблон для отхода 
		void Select91910002204()
		{
			name = "Шлак сварочный";
			code = "9 19 100 02 20 4";
			klass = "4";
			formula = 14;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Удельный норматив образования отхода, доли от единицы");
			columnHeader->Add("Масса израсходованных сварочных электродов, т/год");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Удельный норматив образования отхода, доли от единицы");
			columnToolTipText->Add("Масса израсходованных сварочных электродов, т/год");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("C");
			columnName->Add("P");
		}

		//Шаблон для отхода 
		void Select91910001205()
		{
			name = "Остатки и огарки стальных сварочных электродов";
			code = "9 19 100 01 20 5";
			klass = "5";
			formula = 15;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Коэффициент, учитывающий неравномерность образования огарков ");
			columnHeader->Add("Масса израсходованных сварочных электродов, кг/год");
			columnHeader->Add("Норматив образования огарков, доли от массы израсходованных электродов");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Коэффициент, учитывающий неравномерность образования огарков (образование огарков разной длины при работе на объектах, Kн= 1.10..1.40)");
			columnToolTipText->Add("Масса израсходованных сварочных электродов, кг/год");
			columnToolTipText->Add("Норматив образования огарков, доли от массы израсходованных электродов (0.08 - для электродов с диаметром стержня 2-3 мм; 0.05 - для электродов с диаметром стержня более 3 мм)");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("K");
			columnName->Add("P");
			columnName->Add("C");
		}

		//Шаблон для отхода 
		void Select91920401603()
		{
			name = "Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)";
			code = "9 19 204 01 60 3";
			klass = "3";
			formula = 16;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Масса ветоши, израсходованной за год, кг");
			columnHeader->Add("Содержание в отходе масла, %");
			columnHeader->Add("Содержание в отходе влаги, %");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Масса ветоши, израсходованной за год, кг");
			columnToolTipText->Add("Содержание в отходе масла, %");
			columnToolTipText->Add("Содержание в отходе влаги, %");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("M");
			columnName->Add("M");
			columnName->Add("W");
		}

		//Шаблон для отхода 
		void Select91920402604()
		{
			name = "Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)";
			code = "9 19 204 02 60 4";
			klass = "4";
			formula = 16;

			//Видимое название
			columnHeader->Add("Объект образования отхода");
			columnHeader->Add("Масса ветоши, израсходованной за год, кг");
			columnHeader->Add("Содержание в отходе масла, %");
			columnHeader->Add("Содержание в отходе влаги, %");

			//Описание
			columnToolTipText->Add("Объект образования отхода");
			columnToolTipText->Add("Масса ветоши, израсходованной за год, кг");
			columnToolTipText->Add("Содержание в отходе масла, %");
			columnToolTipText->Add("Содержание в отходе влаги, %");

			//Техническое название
			columnName->Add("Object");
			columnName->Add("M");
			columnName->Add("M");
			columnName->Add("W");
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
			else if (typeWaste == "43811102514 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержание мекее 5 %)") Select43811102514();
			else if (typeWaste == "46120001515 Лом и отходы стальных изделий незагрязненные") Select46120001515();
			else if (typeWaste == "46211001513 Лом и отходы медных изделий без покрытий незагрязненные") Select46211001513();
			else if (typeWaste == "46220002515 Лом электротехнических изделий из алюминия (провод, голые жилы кабелей и шнуров, шины распределительных устройств, трансформаторов, выпрямители)") Select46220002515();
			else if (typeWaste == "47110101521 Лампы ртутные, ртутно-кварцевые, люминесцентные, утратившие потребительские свойства") Select47110101521();
			else if (typeWaste == "48241100525 Лампы накаливания, утратившие потребительские свойства") Select48241100525();
			else if (typeWaste == "48120301523 Картриджи печатающих устройств с содержанием тонера 7 % и более отработанные") Select48120301523();
			else if (typeWaste == "73310001724 Мусор от офисных и бытовых помещений организаций несортированный (исключая крупногабаритный)") Select73310001724();
			else if (typeWaste == "73610001305 Пищевые отходы кухонь и организаций общественного питания несортированные") Select73610001305();
			else if (typeWaste == "92011001532 Аккумуляторы свинцовые отработанные неповрежденные, с электролитом") Select92011001532();
			else if (typeWaste == "92021001102 Кислота аккумуляторная серная отработанная") Select92021001102();
			else if (typeWaste == "92031001525 Тормозные колодки отработанные без накладок асбестовых") Select92031001525();
			else if (typeWaste == "92130201523 Фильтры очистки масла автотранспортных средств отработанные") Select92130201523();
			else if (typeWaste == "91920101393 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)") Select91920101393();
			else if (typeWaste == "91920102394 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)") Select91920102394();
			else if (typeWaste == "91910002204 Шлак сварочный") Select91910002204();
			else if (typeWaste == "91910001205 Остатки и огарки стальных сварочных электродов") Select91910001205();
			else if (typeWaste == "91920401603 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов 15 % и более)") Select91920401603();
			else if (typeWaste == "91920402604 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержание нефти или нефтепродуктов менее 15 %)") Select91920402604();
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

		String^ GetItem(int type, int index)
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
				return floatList[0] * floatList[1] * floatList[2] * floatList[3] * floatList[4] * floatList[5] * floatList[6] / floatList[7] * 0.001f;
			case 2:
				//M * H * 0,00001
				return floatList[0] * floatList[1] * 0.00001f;
			case 3:
				//Q / M * m * 0.001f
				return floatList[0] / floatList[1] * floatList[2] * 0.001f;
			case 4:
				//L * m * 0.001f
				return floatList[0] * floatList[1] * 0.001f;
			case 5:
				//K * Ч * C * m / H * 0,000001f
				return floatList[0] * floatList[4] * floatList[3] * floatList[2] / floatList[1] * 0.000001f;
			case 6:
				//m * k * n / r * 0.000001f
				return floatList[0] * floatList[1] * floatList[2] / floatList[3] * 0.000001f;
			case 7:
				//Q * m * 0.001f
				return floatList[0] * floatList[1] * 0.001f;
			case 8:
				//q * N * m * 0.001f
				return floatList[0] * floatList[1] * floatList[2] * 0.001f;
			case 9:
				//K * K * m / H * 0.001f
				return floatList[0] * floatList[1] * floatList[3] / floatList[2] * 0.001f;
			case 10:
				//K * O * K * p / H * 0.001f
				return floatList[0] * floatList[1] * floatList[2] * floatList[3] / floatList[4] * 0.001f;
			case 11:
				//N * m * K * L / H * 0.001f
				return  floatList[0] * floatList[1] * floatList[4] * floatList[2] / floatList[3] * 0.001f;
			case 12:
				//N * m * K * L / H * 0.000001f
				return floatList[1] * floatList[0] * floatList[2] * floatList[3] / floatList[4] * 0.000001f;
			case 13:
				//Q * p * K
				return floatList[0] * floatList[1] * floatList[2];
			case 14:
				//C * P
				return floatList[0] * floatList[1];
			case 15:
				//K * P * C * 0.001f
				return floatList[0] * floatList[1] * floatList[2] * 0.001f;
			case 16:
				//M * (1 + M / 100 + W / 100) * 0.001
				return floatList[0] * (1 + floatList[1] / 100 + floatList[2] / 100) * 0.001;
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
	private: System::Windows::Forms::ToolStripMenuItem^ Menu43000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem43811101513;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem43811102514;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu46000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem46120001515;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem46211001513;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem46220002515;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu47000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem47110101521;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu48000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem48241100525;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem48120301523;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu73000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem73310001724;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem73610001305;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu92000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem92011001532;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem92021001102;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem92031001525;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem92130201523;
	private: System::Windows::Forms::ToolStripMenuItem^ Menu91000000000;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91910001205;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91910002204;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91920101394;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91920102394;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91920401603;
	private: System::Windows::Forms::ToolStripMenuItem^ MenuItem91920402604;
	private: System::Windows::Forms::ToolStripMenuItem^ deleteMenuItem;




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
			this->Menu43000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem43811101513 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem43811102514 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu46000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem46120001515 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem46211001513 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem46220002515 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu47000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem47110101521 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu48000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem48241100525 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem48120301523 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu73000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem73310001724 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem73610001305 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu91000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91910001205 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91910002204 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91920101394 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91920102394 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91920401603 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem91920402604 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu92000000000 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem92011001532 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem92021001102 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem92031001525 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->MenuItem92130201523 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->actionMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calculateMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->deleteMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->addWasteMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->Menu40600000000,
					this->Menu43000000000, this->Menu46000000000, this->Menu47000000000, this->Menu48000000000, this->Menu73000000000, this->Menu91000000000,
					this->Menu92000000000
			});
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
			this->Menu40600000000->Size = System::Drawing::Size(979, 22);
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
			// Menu43000000000
			// 
			this->Menu43000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->MenuItem43811101513,
					this->MenuItem43811102514
			});
			this->Menu43000000000->Name = L"Menu43000000000";
			this->Menu43000000000->Size = System::Drawing::Size(979, 22);
			this->Menu43000000000->Text = L"4 30 000 00 00 0 РЕЗИНОВЫЕ И ПЛАСТМАССОВЫЕ ИЗДЕЛИЯ, УТРАТИВШИЕ ПОТРЕБИТЕЛЬСКИЕ СВ"
				L"ОЙСТВА";
			// 
			// MenuItem43811101513
			// 
			this->MenuItem43811101513->Name = L"MenuItem43811101513";
			this->MenuItem43811101513->Size = System::Drawing::Size(682, 22);
			this->MenuItem43811101513->Text = L"43811101513 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержа"
				L"ние 5 % и более)";
			this->MenuItem43811101513->Click += gcnew System::EventHandler(this, &Company::MenuItem43811101513_Click);
			// 
			// MenuItem43811102514
			// 
			this->MenuItem43811102514->Name = L"MenuItem43811102514";
			this->MenuItem43811102514->Size = System::Drawing::Size(682, 22);
			this->MenuItem43811102514->Text = L"43811102514 Тара полиэтиленовая, загрязненная лакокрасочными материалами (содержа"
				L"ние менее 5 %)";
			this->MenuItem43811102514->Click += gcnew System::EventHandler(this, &Company::MenuItem43811102514_Click);
			// 
			// Menu46000000000
			// 
			this->Menu46000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->MenuItem46120001515,
					this->MenuItem46211001513, this->MenuItem46220002515
			});
			this->Menu46000000000->Name = L"Menu46000000000";
			this->Menu46000000000->Size = System::Drawing::Size(979, 22);
			this->Menu46000000000->Text = L"4 60 000 00 00 0 ЛОМ И ОТХОДЫ ЧЕРНЫХ И ЦВЕТНЫХ МЕТАЛЛОВ";
			// 
			// MenuItem46120001515
			// 
			this->MenuItem46120001515->Name = L"MenuItem46120001515";
			this->MenuItem46120001515->Size = System::Drawing::Size(1059, 22);
			this->MenuItem46120001515->Text = L"46120001515 Лом и отходы стальных изделий незагрязненные";
			this->MenuItem46120001515->Click += gcnew System::EventHandler(this, &Company::MenuItem46120001515_Click);
			// 
			// MenuItem46211001513
			// 
			this->MenuItem46211001513->Name = L"MenuItem46211001513";
			this->MenuItem46211001513->Size = System::Drawing::Size(1059, 22);
			this->MenuItem46211001513->Text = L"46211001513 Лом и отходы медных изделий без покрытий незагрязненные";
			this->MenuItem46211001513->Click += gcnew System::EventHandler(this, &Company::MenuItem46211001513_Click);
			// 
			// MenuItem46220002515
			// 
			this->MenuItem46220002515->Name = L"MenuItem46220002515";
			this->MenuItem46220002515->Size = System::Drawing::Size(1059, 22);
			this->MenuItem46220002515->Text = L"46220002515 Лом электротехнических изделий из алюминия (провод, голые жилы кабеле"
				L"й и шнуров, шины распределительных устройств, трансформаторов, выпрямители)";
			this->MenuItem46220002515->Click += gcnew System::EventHandler(this, &Company::MenuItem46220002515_Click);
			// 
			// Menu47000000000
			// 
			this->Menu47000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->MenuItem47110101521 });
			this->Menu47000000000->Name = L"Menu47000000000";
			this->Menu47000000000->Size = System::Drawing::Size(979, 22);
			this->Menu47000000000->Text = L"4 70 000 00 00 0 ОТХОДЫ ОБОРУДОВАНИЯ И ПРОЧЕЙ ПРОДУКЦИИ, ПОДЛЕЖАЩЕЙ ОСОБОМУ КОНТР"
				L"ОЛЮ";
			// 
			// MenuItem47110101521
			// 
			this->MenuItem47110101521->Name = L"MenuItem47110101521";
			this->MenuItem47110101521->Size = System::Drawing::Size(687, 22);
			this->MenuItem47110101521->Text = L"47110101521 Лампы ртутные, ртутно-кварцевые, люминесцентные, утратившие потребите"
				L"льские свойства";
			this->MenuItem47110101521->Click += gcnew System::EventHandler(this, &Company::MenuItem47110101521_Click);
			// 
			// Menu48000000000
			// 
			this->Menu48000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->MenuItem48241100525,
					this->MenuItem48120301523
			});
			this->Menu48000000000->Name = L"Menu48000000000";
			this->Menu48000000000->Size = System::Drawing::Size(979, 22);
			this->Menu48000000000->Text = L"4 80 000 00 00 0 ОТХОДЫ МАШИН И ПРОЧЕГО ОБОРУДОВАНИЯ";
			// 
			// MenuItem48241100525
			// 
			this->MenuItem48241100525->Name = L"MenuItem48241100525";
			this->MenuItem48241100525->Size = System::Drawing::Size(632, 22);
			this->MenuItem48241100525->Text = L"48241100525 Лампы накаливания, утратившие потребительские свойства";
			this->MenuItem48241100525->Click += gcnew System::EventHandler(this, &Company::MenuItem48241100525_Click);
			// 
			// MenuItem48120301523
			// 
			this->MenuItem48120301523->Name = L"MenuItem48120301523";
			this->MenuItem48120301523->Size = System::Drawing::Size(632, 22);
			this->MenuItem48120301523->Text = L"48120301523 Картриджи печатающих устройств с содержанием тонера 7 % и более отраб"
				L"отанные";
			this->MenuItem48120301523->Click += gcnew System::EventHandler(this, &Company::MenuItem48120301523_Click);
			// 
			// Menu73000000000
			// 
			this->Menu73000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->MenuItem73310001724,
					this->MenuItem73610001305
			});
			this->Menu73000000000->Name = L"Menu73000000000";
			this->Menu73000000000->Size = System::Drawing::Size(979, 22);
			this->Menu73000000000->Text = L"7 30 000 00 00 0 ОТХОДЫ КОММУНАЛЬНЫЕ, ПОДОБНЫЕ КОММУНАЛЬНЫМ НА ПРОИЗВОДСТВЕ И ПРИ"
				L" ПРЕДОСТАВЛЕНИИ УСЛУГ НАСЕЛЕНИЮ";
			// 
			// MenuItem73310001724
			// 
			this->MenuItem73310001724->Name = L"MenuItem73310001724";
			this->MenuItem73310001724->Size = System::Drawing::Size(743, 22);
			this->MenuItem73310001724->Text = L"73310001724 Мусор от офисных и бытовых помещений организаций несортированный (иск"
				L"лючая крупногабаритный)";
			this->MenuItem73310001724->Click += gcnew System::EventHandler(this, &Company::MenuItem73310001724_Click);
			// 
			// MenuItem73610001305
			// 
			this->MenuItem73610001305->Name = L"MenuItem73610001305";
			this->MenuItem73610001305->Size = System::Drawing::Size(743, 22);
			this->MenuItem73610001305->Text = L"73610001305 Пищевые отходы кухонь и организаций общественного питания несортирова"
				L"нные";
			this->MenuItem73610001305->Click += gcnew System::EventHandler(this, &Company::MenuItem73610001305_Click);
			// 
			// Menu91000000000
			// 
			this->Menu91000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->MenuItem91910001205,
					this->MenuItem91910002204, this->MenuItem91920101394, this->MenuItem91920102394, this->MenuItem91920401603, this->MenuItem91920402604
			});
			this->Menu91000000000->Name = L"Menu91000000000";
			this->Menu91000000000->Size = System::Drawing::Size(979, 22);
			this->Menu91000000000->Text = L"9 10 000 00 00 0 ОТХОДЫ ОБСЛУЖИВАНИЯ И РЕМОНТА МАШИН И ОБОРУДОВАНИЯ";
			// 
			// MenuItem91910001205
			// 
			this->MenuItem91910001205->Name = L"MenuItem91910001205";
			this->MenuItem91910001205->Size = System::Drawing::Size(857, 22);
			this->MenuItem91910001205->Text = L"91910001205 Остатки и огарки стальных сварочных электродов";
			this->MenuItem91910001205->Click += gcnew System::EventHandler(this, &Company::MenuItem91910001205_Click);
			// 
			// MenuItem91910002204
			// 
			this->MenuItem91910002204->Name = L"MenuItem91910002204";
			this->MenuItem91910002204->Size = System::Drawing::Size(857, 22);
			this->MenuItem91910002204->Text = L"91910002204 Шлак сварочный";
			this->MenuItem91910002204->Click += gcnew System::EventHandler(this, &Company::MenuItem91910002204_Click);
			// 
			// MenuItem91920101394
			// 
			this->MenuItem91920101394->Name = L"MenuItem91920101394";
			this->MenuItem91920101394->Size = System::Drawing::Size(857, 22);
			this->MenuItem91920101394->Text = L"91920101393 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или "
				L"нефтепродуктов 15 % и более)";
			this->MenuItem91920101394->Click += gcnew System::EventHandler(this, &Company::MenuItem91920101394_Click);
			// 
			// MenuItem91920102394
			// 
			this->MenuItem91920102394->Name = L"MenuItem91920102394";
			this->MenuItem91920102394->Size = System::Drawing::Size(857, 22);
			this->MenuItem91920102394->Text = L"91920102394 Песок, загрязненный нефтью или нефтепродуктами (содержание нефти или "
				L"нефтепродуктов менее 15 %)";
			this->MenuItem91920102394->Click += gcnew System::EventHandler(this, &Company::MenuItem91920102394_Click);
			// 
			// MenuItem91920401603
			// 
			this->MenuItem91920401603->Name = L"MenuItem91920401603";
			this->MenuItem91920401603->Size = System::Drawing::Size(857, 22);
			this->MenuItem91920401603->Text = L"91920401603 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержа"
				L"ние нефти или нефтепродуктов 15 % и более)";
			this->MenuItem91920401603->Click += gcnew System::EventHandler(this, &Company::MenuItem91920401603_Click);
			// 
			// MenuItem91920402604
			// 
			this->MenuItem91920402604->Name = L"MenuItem91920402604";
			this->MenuItem91920402604->Size = System::Drawing::Size(857, 22);
			this->MenuItem91920402604->Text = L"91920402604 Обтирочный материал, загрязненный нефтью или нефтепродуктами (содержа"
				L"ние нефти или нефтепродуктов менее 15 %)";
			this->MenuItem91920402604->Click += gcnew System::EventHandler(this, &Company::MenuItem91920402604_Click);
			// 
			// Menu92000000000
			// 
			this->Menu92000000000->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->MenuItem92011001532,
					this->MenuItem92021001102, this->MenuItem92031001525, this->MenuItem92130201523
			});
			this->Menu92000000000->Name = L"Menu92000000000";
			this->Menu92000000000->Size = System::Drawing::Size(979, 22);
			this->Menu92000000000->Text = L"9 20 000 00 00 0 ОТХОДЫ ОБСЛУЖИВАНИЯ, РЕМОНТА И ДЕМОНТАЖА ТРАНСПОРТНЫХ СРЕДСТВ ПР"
				L"ОЧИЕ";
			// 
			// MenuItem92011001532
			// 
			this->MenuItem92011001532->Name = L"MenuItem92011001532";
			this->MenuItem92011001532->Size = System::Drawing::Size(581, 22);
			this->MenuItem92011001532->Text = L"92011001532 Аккумуляторы свинцовые отработанные неповрежденные, с электролитом";
			this->MenuItem92011001532->Click += gcnew System::EventHandler(this, &Company::MenuItem92011001532_Click);
			// 
			// MenuItem92021001102
			// 
			this->MenuItem92021001102->Name = L"MenuItem92021001102";
			this->MenuItem92021001102->Size = System::Drawing::Size(581, 22);
			this->MenuItem92021001102->Text = L"92021001102 Кислота аккумуляторная серная отработанная";
			this->MenuItem92021001102->Click += gcnew System::EventHandler(this, &Company::MenuItem92021001102_Click);
			// 
			// MenuItem92031001525
			// 
			this->MenuItem92031001525->Name = L"MenuItem92031001525";
			this->MenuItem92031001525->Size = System::Drawing::Size(581, 22);
			this->MenuItem92031001525->Text = L"92031001525 Тормозные колодки отработанные без накладок асбестовых";
			this->MenuItem92031001525->Click += gcnew System::EventHandler(this, &Company::MenuItem92031001525_Click);
			// 
			// MenuItem92130201523
			// 
			this->MenuItem92130201523->Name = L"MenuItem92130201523";
			this->MenuItem92130201523->Size = System::Drawing::Size(581, 22);
			this->MenuItem92130201523->Text = L"92130201523 Фильтры очистки масла автотранспортных средств отработанные";
			this->MenuItem92130201523->Click += gcnew System::EventHandler(this, &Company::MenuItem92130201523_Click);
			// 
			// actionMenuItem
			// 
			this->actionMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->calculateMenuItem,
					this->deleteMenuItem
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
			// deleteMenuItem
			// 
			this->deleteMenuItem->Name = L"deleteMenuItem";
			this->deleteMenuItem->Size = System::Drawing::Size(180, 22);
			this->deleteMenuItem->Text = L"Удалить";
			this->deleteMenuItem->Click += gcnew System::EventHandler(this, &Company::deleteMenuItem_Click);
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

		void MenuItem43811101513_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem43811101513->Text);
		}

		void MenuItem43811102514_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem43811102514->Text);
		}

		void MenuItem46120001515_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem46120001515->Text);
		}

		void MenuItem46211001513_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem46211001513->Text);
		}

		void MenuItem46220002515_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem46220002515->Text);
		}

		void MenuItem47110101521_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem47110101521->Text);
		}

		void MenuItem48241100525_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem48241100525->Text);
		}

		void MenuItem48120301523_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem48120301523->Text);
		}

		void MenuItem73310001724_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem73310001724->Text);
		}

		void MenuItem73610001305_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem73610001305->Text);
		}

		void MenuItem92011001532_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem92011001532->Text);
		}

		void MenuItem92021001102_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem92021001102->Text);
		}

		void MenuItem92031001525_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem92031001525->Text);
		}

		void MenuItem92130201523_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem92130201523->Text);
		}

		private: System::Void MenuItem91910001205_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91910001205->Text);
		}

		private: System::Void MenuItem91910002204_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91910002204->Text);
		}

		private: System::Void MenuItem91920101394_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91920101394->Text);
		}

		private: System::Void MenuItem91920102394_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91920102394->Text);
		}

		private: System::Void MenuItem91920401603_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91920401603->Text);
		}

		private: System::Void MenuItem91920402604_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			NewWasteInList(MenuItem91920402604->Text);
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

		void exportMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
		{
		}

};
}

