/**
* \file MainWindow.cpp
* \brief Defines the main Qt window
* \author Guillaume Gibert
* \date 27/01/2020
*/

#include "interface/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	m_pWFirstHarmonicSignalDisplay(nullptr), m_pWSecondHarmonicSignalDisplay(nullptr), 
	m_pWThirdHarmonicSignalDisplay(nullptr), m_pWFourthHarmonicSignalDisplay(nullptr),
	m_pWFullSignalDisplay(nullptr), m_pWFullPowerSpectrumDisplay(nullptr)
{
	ui->setupUi(this);
	//this->setWindowTitle(QString("Music Note Synthesizer"));
	
	initWidgets();
	
}

MainWindow::~MainWindow()
{
	auto deleteAndNullify = [](auto pointer) -> void
	{
		if (nullptr != pointer)
		{
			delete pointer;
			pointer = nullptr;
		}
	};

	deleteAndNullify(m_pWFirstHarmonicSignalDisplay);
	deleteAndNullify(m_pWSecondHarmonicSignalDisplay);
	deleteAndNullify(m_pWThirdHarmonicSignalDisplay);
	deleteAndNullify(m_pWFourthHarmonicSignalDisplay);
	deleteAndNullify(m_pWFullSignalDisplay);
	deleteAndNullify(m_pWFullPowerSpectrumDisplay);
	
	/*
	if (nullptr != m_pWFirstHarmonicSignalDisplay)
	{
		delete m_pWFirstHarmonicSignalDisplay;
		m_pWFirstHarmonicSignalDisplay = nullptr;
	}

	if (nullptr != m_pWSecondHarmonicSignalDisplay)
	{
		delete m_pWSecondHarmonicSignalDisplay;
		m_pWSecondHarmonicSignalDisplay = nullptr;
	}

	if (nullptr != m_pWThirdHarmonicSignalDisplay)
	{
		delete m_pWThirdHarmonicSignalDisplay;
		m_pWThirdHarmonicSignalDisplay = nullptr;
	}

	if (nullptr != m_pWFourthHarmonicSignalDisplay)
	{
		delete m_pWFourthHarmonicSignalDisplay;
		m_pWFourthHarmonicSignalDisplay = nullptr;
	}

	if (nullptr != m_pWFullSignalDisplay)
	{
		delete m_pWFullSignalDisplay;
		m_pWFullSignalDisplay = nullptr;
	}

	if (nullptr != m_pWFullPowerSpectrumDisplay)
	{
		delete m_pWFullPowerSpectrumDisplay;
		m_pWFullPowerSpectrumDisplay = nullptr;
	}
	*/
}

void MainWindow::initWidgets()
{
	// 1st Harmonic Signal display
	if (nullptr == m_pWFirstHarmonicSignalDisplay)
	{
		m_pWFirstHarmonicSignalDisplay = new BufferedSignalDisplay();
		m_pWFirstHarmonicSignalDisplay->setMinimumSize(600, 600);
		m_pWFirstHarmonicSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWFirstHarmonicSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWFirstHarmonicSignalDisplay->setFps(30.0);
		m_pWFirstHarmonicSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWFirstHarmonicSignalDisplay->setLegends("Time (s)", "Color amplitude");
		m_pWFirstHarmonicSignalDisplay->setTicks(1, 50);
		m_pWFirstHarmonicSignalDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWFullSignalDisplay);
	}

	// Full Signal display
	if (nullptr == m_pWFullSignalDisplay)
	{
		m_pWFullSignalDisplay = new BufferedSignalDisplay();
		m_pWFullSignalDisplay->setMinimumSize(600, 600);
		m_pWFullSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWFullSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWFullSignalDisplay->setFps(30.0);
		m_pWFullSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWFullSignalDisplay->setLegends("Time (s)", "Color amplitude");
		m_pWFullSignalDisplay->setTicks(1, 50);
		m_pWFullSignalDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWFullSignalDisplay);
	}

	// Full Power Spectrum display
	if (nullptr == m_pWFullPowerSpectrumDisplay)
	{
		m_pWFullPowerSpectrumDisplay = new BufferedSignalDisplay();
		m_pWFullPowerSpectrumDisplay->setMinimumSize(600, 600);
		m_pWFullPowerSpectrumDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWFullPowerSpectrumDisplay->setSignalLabels(vSignalLabels);
		m_pWFullPowerSpectrumDisplay->setFps(30.0);
		m_pWFullPowerSpectrumDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWFullPowerSpectrumDisplay->setLegends("Frequency (Hz)", "Power spectrum");
		m_pWFullPowerSpectrumDisplay->setTicks(5, 50);
		m_pWFullPowerSpectrumDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWFullPowerSpectrumDisplay);
	}
}

