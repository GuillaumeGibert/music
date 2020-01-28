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
	m_pWBufferedSignalDisplay(nullptr), m_pWPowerSpectrumDisplay(nullptr)
{
	ui->setupUi(this);
	//this->setWindowTitle(QString("PPG"));
	
	initWidgets();
	
}

MainWindow::~MainWindow()
{
	if (nullptr != m_pWBufferedSignalDisplay)
	{
		delete m_pWBufferedSignalDisplay;
		m_pWBufferedSignalDisplay = nullptr;
	}

	if (nullptr != m_pWPowerSpectrumDisplay)
	{
		delete m_pWPowerSpectrumDisplay;
		m_pWPowerSpectrumDisplay = nullptr;
	}
}

void MainWindow::initWidgets()
{
	// Buffered Signal display
	if (nullptr == m_pWBufferedSignalDisplay)
	{
		m_pWBufferedSignalDisplay = new BufferedSignalDisplay();
		m_pWBufferedSignalDisplay->setMinimumSize(600, 600);
		m_pWBufferedSignalDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWBufferedSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWBufferedSignalDisplay->setFps(30.0);
		m_pWBufferedSignalDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWBufferedSignalDisplay->setLegends("Time (s)", "Color amplitude");
		m_pWBufferedSignalDisplay->setTicks(1, 50);
		m_pWBufferedSignalDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWBufferedSignalDisplay);
	}

	// Power Spectrum display
	if (nullptr == m_pWPowerSpectrumDisplay)
	{
		m_pWPowerSpectrumDisplay = new BufferedSignalDisplay();
		m_pWPowerSpectrumDisplay->setMinimumSize(600, 600);
		m_pWPowerSpectrumDisplay->setWidgetSize(QSize(640, 480));
		std::vector<std::string> vSignalLabels;
		vSignalLabels.push_back("R"); vSignalLabels.push_back("G"); vSignalLabels.push_back("B");
		m_pWPowerSpectrumDisplay->setSignalLabels(vSignalLabels);
		m_pWPowerSpectrumDisplay->setFps(30.0);
		m_pWPowerSpectrumDisplay->setXYRange(QSize(0, 15), QSize(0, 250));
		m_pWPowerSpectrumDisplay->setLegends("Frequency (Hz)", "Power spectrum");
		m_pWPowerSpectrumDisplay->setTicks(5, 50);
		m_pWPowerSpectrumDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWPowerSpectrumDisplay);
	}
}

