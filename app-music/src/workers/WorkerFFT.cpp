#include "workers/WorkerFFT.h"

WorkerFFT::WorkerFFT(): 
	m_pFFT(nullptr),
	m_fFps(0.0)
{
	init();
}

WorkerFFT::~WorkerFFT()
{
	if (nullptr != m_pFFT)
	{
		delete m_pFFT;
		m_pFFT = nullptr;
	}
}

void WorkerFFT::doWork()
{

}

bool WorkerFFT::init()
{
	if (nullptr == m_pFFT)
	{
		m_pFFT = new FFT();
		QObject::connect(m_pFFT, SIGNAL(sigBroadcastPowerSpectrumValues(std::vector<std::vector<float>>)), this, SIGNAL(sigBroadcastPowerSpectrumValues(std::vector<std::vector<float>>)));

		m_bIsWorkerInitialized = true;
	}

	

	return m_bIsWorkerInitialized;
}

void WorkerFFT::setFps(float fFps)
{
	m_oWorkerMutex.lockForWrite();
		m_pFFT->setFps(fFps);
	m_oWorkerMutex.unlock();
}

void WorkerFFT::setNbSignals(int i32NbSignals)
{
	m_oWorkerMutex.lockForWrite();
		m_pFFT->setNbSignals(i32NbSignals);
	m_oWorkerMutex.unlock();
}

void WorkerFFT::setSignalValues(std::vector<std::vector<float>> vSignalValues)
{
	m_oWorkerMutex.lockForWrite();
		m_pFFT->setBufferedSignalValues(vSignalValues);
	m_oWorkerMutex.unlock();
}