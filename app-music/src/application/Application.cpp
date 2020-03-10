/**
* \file Application.cpp
* \brief Defines Application
* \author Guillaume Gibert
* \date 27/01/2020
*/

#include "application/Application.h"

Application::Application()
{
	m_pWorkerSignalGenerator = nullptr;
	m_pWorkerMusicPlayer = nullptr;
	m_pWorkerFFT = nullptr;
}


Application::~Application()
{
	// stops the threads
	stopWorkerThreads();

	// deletes the workers
	deleteWorkers();
}

void Application::init(MainWindow* window)
{
	m_window = window;

	initWorkers();
	registerMetaTypes();
	setWorkerConnections();
	moveWorkersToThread();

}

void Application::initWorkers()
{
	if (nullptr == m_pWorkerSignalGenerator)
	{
		m_pWorkerSignalGenerator = new WorkerSignalGenerator();
	}

	if (nullptr == m_pWorkerMusicPlayer)
	{
		m_pWorkerMusicPlayer = new WorkerMusicPlayer(8000.0, 1.0);
	}

	if (nullptr == m_pWorkerFFT)
	{
		m_pWorkerFFT = new WorkerFFT();
	}
}

void Application::registerMetaTypes()
{
	// register opencv data types
	qRegisterMetaType< std::vector<std::vector<float>> >("std::vector<std::vector<float>>");
}

void Application::setWorkerConnections()
{
	// Selection on the interface generates new signals
	QObject::connect(m_window, SIGNAL(sigBroadcastInstrumentAndNote(int, int)), this, SLOT(setSelectedInstrumentAndNote(int, int)));
	QObject::connect(this, SIGNAL(sigBroadcastSignalFeatures(float, float, float, int, std::vector<float>, std::vector<float>)), m_pWorkerSignalGenerator, SLOT(setSignalFeatures(float, float, float, int, std::vector<float>, std::vector<float>)));
	
	// Generated signals are then transmitted to the interface for display
	QObject::connect(m_pWorkerSignalGenerator, SIGNAL(sigBroadcastHarmonicSignals(std::vector<std::vector<float>>)), m_window, SLOT(setHarmonicSignals(std::vector<std::vector<float>>)));
	QObject::connect(m_pWorkerSignalGenerator, SIGNAL(sigBroadcastFullSignals(std::vector<std::vector<float>>)), m_window, SLOT(setFullSignals(std::vector<std::vector<float>>)));
	// and to the music player
	QObject::connect(m_pWorkerSignalGenerator, SIGNAL(sigBroadcastFullSignal(std::vector<float>)), m_pWorkerMusicPlayer, SLOT(setSignalValues(std::vector<float>)));
	// and to the FFT
	QObject::connect(m_pWorkerSignalGenerator, SIGNAL(sigBroadcastFullSignals(std::vector<std::vector<float>>)), m_pWorkerFFT, SLOT(setSignalValues(std::vector<std::vector<float>>)));
	QObject::connect(m_pWorkerFFT, SIGNAL(sigBroadcastPowerSpectrumValues(std::vector<std::vector<float>>)), m_window, SLOT(setPowerSpectrum(std::vector<std::vector<float>>)));
	

	
}

void Application::moveWorkersToThread()
{
	// WorkerSignalGenerator
	if (nullptr != m_pWorkerSignalGenerator)
	{
		m_pWorkerSignalGenerator->moveToThread(&m_TWorkerSignalGenerator);
		m_TWorkerSignalGenerator.start();
	}

	// WorkerSignalGenerator
	if (nullptr != m_pWorkerMusicPlayer)
	{
		m_pWorkerMusicPlayer->moveToThread(&m_TWorkerMusicPlayer);
		m_TWorkerMusicPlayer.start();
	}

	// WorkerFFT
	if (nullptr != m_pWorkerFFT)
	{
		m_pWorkerFFT->moveToThread(&m_TWorkerFFT);
		m_TWorkerFFT.start();
	}
}

void Application::stopWorkerThreads()
{
	m_TWorkerSignalGenerator.quit();
	m_TWorkerSignalGenerator.wait();

	m_TWorkerMusicPlayer.quit();
	m_TWorkerMusicPlayer.wait();

	m_TWorkerFFT.quit();
	m_TWorkerFFT.wait();
}

void Application::deleteWorkers()
{
    auto deleteAndNullify = [](auto pointer) -> void
    {
        if (nullptr != pointer)
        {
            delete pointer;
            pointer = nullptr;
        }
    };

    deleteAndNullify(m_pWorkerSignalGenerator);
    deleteAndNullify(m_pWorkerMusicPlayer);
    deleteAndNullify(m_pWorkerFFT);

 }

void Application::setSelectedInstrumentAndNote(int instrument, int note)
{
	// TODO get harmonics weight values depending on the instrument

	float fFps = 8000.0;
	float fDuration = 1.0;
	int nbHarmonics = 5;
	std::vector<float> vAmplitude = { 0.8, 0.5, 0.3, 0.2, 0.1 };
	std::vector<float> vPhase = { 0.0, 0.0, 0.0, 0.0 , 0.0};

	float fFrequency = 0.0;
	
	switch (note)
	{
	case Notes::DO :
		fFrequency = DO_FREQ;
		break;
	case Notes::RE :
		fFrequency = RE_FREQ;
		break;
	case Notes::MI :
		fFrequency = MI_FREQ;
		break;
	case Notes::FA :
		fFrequency = FA_FREQ;
		break;
	case Notes::SOL :
		fFrequency = SOL_FREQ;
		break;
	case Notes::LA :
		fFrequency = LA_FREQ;
		break;
	case Notes::SI :
		fFrequency = SI_FREQ;
		break;
	}

	
	emit sigBroadcastSignalFeatures(fFps, fDuration, fFrequency, nbHarmonics, vAmplitude, vPhase);
}
