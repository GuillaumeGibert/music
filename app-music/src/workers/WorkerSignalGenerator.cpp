#include "workers/WorkerSignalGenerator.h"

WorkerSignalGenerator::WorkerSignalGenerator()
{
	m_pSineGenerator = nullptr;
	m_bIsWorkerInitialized = false;

	init();
}

WorkerSignalGenerator::~WorkerSignalGenerator()
{
	if (nullptr != m_pSineGenerator)
	{
		delete m_pSineGenerator;
		m_pSineGenerator = nullptr;
	}
}

void WorkerSignalGenerator::doWork()
{

}

bool WorkerSignalGenerator::init()
{
	if (nullptr == m_pSineGenerator)
	{
		m_pSineGenerator = new SineGenerator();
		
		m_bIsWorkerInitialized = true;
	}


	return m_bIsWorkerInitialized;
}

void WorkerSignalGenerator::setSignalFeatures(int nbHarmonics, float fFps, float fFrequency, float fAmplitude, float fPhase, float fDuration)
{

}


