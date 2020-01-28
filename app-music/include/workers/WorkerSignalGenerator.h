#ifndef _WORKER_SIGNAL_GENERATOR_H
#define _WORKER_SIGNAL_GENERATOR_H

#include "workers\Worker.h"
#include "SineGenerator.h"

class WorkerSignalGenerator : public Worker
{
	Q_OBJECT

public:
	WorkerSignalGenerator();
	~WorkerSignalGenerator();

protected:
	void doWork();
	bool init();

public slots:
	void setSignalFeatures(int nbHarmonics, float fFps, float fFrequency, float fAmplitude, float fPhase, float fDuration);

signals:
	void sigBoradcastHarmonicSignals(std::vector<std::vector<float>>);

private:
	SineGenerator* m_pSineGenerator;

};

#endif