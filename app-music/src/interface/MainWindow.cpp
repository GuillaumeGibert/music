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
	m_pWFullSignalDisplay(nullptr), m_pWFullPowerSpectrumDisplay(nullptr),
	m_i32InstrumentIndex(0), m_i32NoteIndex(0),
	m_pNoteMapper(new QSignalMapper(this)), m_pInstrumentMapper(new QSignalMapper(this))
{
	ui->setupUi(this);
	//this->setWindowTitle(QString("Music Note Synthesizer"));
	
	initWidgets();
	setInterfaceConnections();
	
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


	deleteAndNullify(m_pNoteMapper);
	deleteAndNullify(m_pInstrumentMapper);
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
		vSignalLabels.push_back("F4");/* vSignalLabels.push_back("F5"); vSignalLabels.push_back("F6"); vSignalLabels.push_back("F7");*/
		m_pWHarmonicSignalDisplay->setSignalLabels(vSignalLabels);
		m_pWHarmonicSignalDisplay->setFps(8000.0);
		m_pWHarmonicSignalDisplay->setXYRange(QSize(0, 1), QSize(-1, 1));
		m_pWHarmonicSignalDisplay->setLegends("Time (s)", "Signal amplitude (n.u.)");
		m_pWHarmonicSignalDisplay->setTicks(1, 1);
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
		m_pWFullSignalDisplay->setFps(8000.0);
		m_pWFullSignalDisplay->setXYRange(QSize(0, 1), QSize(-1, 1));
		m_pWFullSignalDisplay->setLegends("Time (s)", "Signal amplitude");
		m_pWFullSignalDisplay->setTicks(1, 1);
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
		vSignalLabels.push_back("Signal"); 
		m_pWFullPowerSpectrumDisplay->setSignalLabels(vSignalLabels);
		m_pWFullPowerSpectrumDisplay->setFps(8000.0);
		m_pWFullPowerSpectrumDisplay->setXYRange(QSize(0, 4000), QSize(0, 10));
		m_pWFullPowerSpectrumDisplay->setLegends("Frequency (Hz)", "Power spectrum");
		m_pWFullPowerSpectrumDisplay->setTicks(5, 500);
		m_pWFullPowerSpectrumDisplay->setDrawLine(true);

		ui->vlSignal->addWidget(m_pWFullPowerSpectrumDisplay);
	}
}

void MainWindow::setInterfaceConnections()
{
	// Notes	
		// in
	QObject::connect(ui->pbNotesDo, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesRe, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesMi, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesFa, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesSol, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesLa, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
	QObject::connect(ui->pbNotesSi, SIGNAL(clicked()), m_pNoteMapper, SLOT(map()));
		// maping
	m_pNoteMapper->setMapping(ui->pbNotesDo, 0);
	m_pNoteMapper->setMapping(ui->pbNotesRe, 1);
	m_pNoteMapper->setMapping(ui->pbNotesMi, 2);
	m_pNoteMapper->setMapping(ui->pbNotesFa, 3);
	m_pNoteMapper->setMapping(ui->pbNotesSol, 4);
	m_pNoteMapper->setMapping(ui->pbNotesLa, 5);
	m_pNoteMapper->setMapping(ui->pbNotesSi, 6);
		// out
	QObject::connect(m_pNoteMapper, SIGNAL(mapped(int)), this, SLOT(setNoteIndex(int)));


	// Instruments	
		// in
	QObject::connect(ui->pbInstrumentFundamental, SIGNAL(clicked()), m_pInstrumentMapper, SLOT(map()));
	QObject::connect(ui->pbInstrumentInvFreq, SIGNAL(clicked()), m_pInstrumentMapper, SLOT(map()));
	QObject::connect(ui->pbInstrumentOboe, SIGNAL(clicked()), m_pInstrumentMapper, SLOT(map()));
		// maping
	m_pInstrumentMapper->setMapping(ui->pbInstrumentFundamental, 0);
	m_pInstrumentMapper->setMapping(ui->pbInstrumentInvFreq, 1);
	m_pInstrumentMapper->setMapping(ui->pbInstrumentOboe, 2);
		// out
	QObject::connect(m_pInstrumentMapper, SIGNAL(mapped(int)), this, SLOT(setInstrumentIndex(int)));

	
}

void MainWindow::setNoteIndex(int i32NoteIndex)
{
	m_i32NoteIndex = i32NoteIndex;

	emit sigBroadcastInstrumentAndNote(m_i32InstrumentIndex, m_i32NoteIndex);
}

void MainWindow::setInstrumentIndex(int i32InstrumentIndex)
{
	m_i32InstrumentIndex = i32InstrumentIndex;

	emit sigBroadcastInstrumentAndNote(m_i32InstrumentIndex, m_i32NoteIndex);
}

void MainWindow::setHarmonicSignals(std::vector<std::vector<float>> vHarmonicSignals)
{
	m_pWHarmonicSignalDisplay->setNewValues(vHarmonicSignals);
}

void MainWindow::setFullSignals(std::vector<std::vector<float>> vFullSignals)
{
	m_pWFullSignalDisplay->setNewValues(vFullSignals);
}

void MainWindow::setPowerSpectrum(std::vector<std::vector<float>> vPowerSpectrum)
{
	m_pWFullPowerSpectrumDisplay->setNewValues(vPowerSpectrum);
}