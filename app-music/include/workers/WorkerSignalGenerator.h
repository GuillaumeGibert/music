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

private:
	SineGenerator* m_pSineGenerator;

}

#endif