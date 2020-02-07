#include "workers/WorkerSignalGenerator.h"

WorkerSignalGenerator::WorkerSignalGenerator()
{
	m_pSineGenerator = nullptr;

	m_fFps = 0.0;
	m_fDuration = 0.0;
	m_fFrequency = 0.0;
	m_i32NbHarmonics = 0.0;

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

void WorkerSignalGenerator::setSignalFeatures(float fFps, float fDuration, float fFrequency, int i32NbHarmonics, std::vector<float> vAmplitude, std::vector<float> vPhase)
{
	m_oWorkerMutex.lockForWrite();
		m_fFps = fFps;
		m_fDuration = fDuration;
		m_fFrequency = fFrequency;
		m_i32NbHarmonics = i32NbHarmonics;
		m_vAmplitude = vAmplitude;
		m_vPhase = vPhase;
	m_oWorkerMutex.unlock();
}


void WorkerSignalGenerator::generate()
{
	// checks if sample rate was correctly set
	if (m_fFps == 0.0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Sample rate was not correctly set.";
		return;
	}

	// checks if duration was correctly set
	if (m_fDuration == 0.0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Duration was not correctly set.";
		return;
	}

	// checks if frequency was correctly set
	if (m_fFrequency == 0.0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Frequency was not correctly set.";
		return;
	}

	// checks if number of harmonics was correctly set
	if (m_i32NbHarmonics == 0.0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Number of harmonics was not correctly set.";
		return;
	}

	// checks if vector of amplitude was correctly set
	if (m_vAmplitude.size() == 0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Vector of amplitude was not correctly set.";
		return;
	}

	// checks if vector of phase was correctly set
	if (m_vPhase.size() == 0)
	{
		qWarning() << "(WorkerSignalGenerator::generate) Vector of phase was not correctly set.";
		return;
	}

	// creates a vector to store the generated signals
	std::vector<std::vector<float>> l_vHarmonicSignals;

	// sets the general features (fps and duration)
	m_pSineGenerator->setFps(m_fFps);
	m_pSineGenerator->setDuration(m_fDuration);

	for (auto l_harmonic = 0; l_harmonic < m_i32NbHarmonics; l_harmonic++)
	{
		// sets the harmonic-specific features
		m_pSineGenerator->setFrequency(m_fFrequency * (l_harmonic+1));
		m_pSineGenerator->setAmplitude(m_vAmplitude[l_harmonic]);
		m_pSineGenerator->setPhase(m_vPhase[l_harmonic]);

		// stores the generated signal
		l_vHarmonicSignals.push_back(m_pSineGenerator->generate());
	}

	// broadcasts the generated signals
	emit sigBroadcastHarmonicSignals(l_vHarmonicSignals);
}

