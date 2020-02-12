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
	m_pWHarmonicSignalDisplay(nullptr),
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

	deleteAndNullify(m_pWHarmonicSignalDisplay);
	deleteAndNullify(m_pWFullSignalDisplay);
	deleteAndNullify(m_pWFullPowerSpectrumDisplay);
	
}

void MainWindow::initWidgets()
{
	// 1st Harmonic Signal display
	if (nullptr == m_pWHarmonicSignalDisplay)
	{
		m_pWHarmonicSignalDisplay = new BufferedSignalDisplay();
		m_pWHarmonicSignalDisplay->setMinimumSize(600, 600);
		m_pWHarmonicSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("F0"); vSignalLabels.push_back("F1"); vSignalLabels.push_back("F2"); vSignalLabels.push_back("F3");
		vSignalLabels.push_back("F4"); vSignalLabels.push_back("F5"); vSignalLabels.push_back("F6"); vSignalLabels.push_back("F7");
		m_pWHarmonicSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWHarmonicSignalDisplay->setFps(30.0);
		m_pWHarmonicSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWHarmonicSignalDisplay->setLegends("Time (s)", "Signal amplitude (n.u.)");
		m_pWHarmonicSignalDisplay->setTicks(1, 50);
		m_pWHarmonicSignalDisplay->setDrawLine(true);

		ui->vlHarmonics->addWidget(m_pWHarmonicSignalDisplay);
		
	}

	// Full Signal display
	if (nullptr == m_pWFullSignalDisplay)
	{
		m_pWFullSignalDisplay = new BufferedSignalDisplay();
		m_pWFullSignalDisplay->setMinimumSize(600, 600);
		m_pWFullSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("Signal");
		m_pWFullSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWFullSignalDisplay->setFps(30.0);
		m_pWFullSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWFullSignalDisplay->setLegends("Time (s)", "Signal amplitude");
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

