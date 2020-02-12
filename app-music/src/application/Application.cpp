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
}


Application::~Application()
{
	if (nullptr != m_pWorkerSignalGenerator)
	{
		delete m_pWorkerSignalGenerator;
		m_pWorkerSignalGenerator = nullptr;
	}
	
	if (nullptr != m_pWorkerMusicPlayer)
	{
		delete m_pWorkerMusicPlayer;
		m_pWorkerMusicPlayer = nullptr;
	}

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
		m_pWorkerMusicPlayer = new WorkerMusicPlayer();
	}
}

void Application::registerMetaTypes()
{
	// register opencv data types
	qRegisterMetaType< std::vector<float> >("std::vector<float>");
	qRegisterMetaType< std::vector< std::deque<float> > >("std::vector<std::deque<float>>");
}

void Application::setWorkerConnections()
{
	QObject::connect(m_window, SIGNAL(selectedInstrumentAndNote(int, int)), this, SLOT(setSelectedInstrumentAndNote(int, int)));


	QObject::connect(this, SIGNAL(selectedInstrumentAndNote(int, int)), m_pWorkerSignalGenerator, SLOT(setSelectedInstrumentAndNote(int, int)));
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
}

void Application::stopWorkerThreads()
{
	m_TWorkerSignalGenerator.quit();
	m_TWorkerSignalGenerator.wait();

	m_TWorkerMusicPlayer.quit();
	m_TWorkerMusicPlayer.wait();
}

void Application::deleteWorkers()
{
	if (nullptr != m_pWorkerSignalGenerator)
	{
		delete m_pWorkerSignalGenerator;
		m_pWorkerSignalGenerator = nullptr;
	}

	if (nullptr != m_pWorkerMusicPlayer)
	{
		delete m_pWorkerMusicPlayer;
		m_pWorkerMusicPlayer = nullptr;
	}
		
}

void Application::setSelectedInstrumentAndNote(int instrument, int note)
{
	// TODO get harmonics weight values depending on the instrument

	switch (note)
	{
	case Notes::DO :

	case Notes::RE :

	case Notes::MI :

	case Notes::FA :

	case Notes::SOL :
	
	case Notes::LA :
	
	case Notes::SI :

	}
}