#include "workers/WorkerSignalGenerator.h"

WorkerSignalGenerator::WorkerSignalGenerator()
{
	m_bIsWorkerInitialized = false;
}

WorkerSignalGenerator::~WorkerSignalGenerator()
{

}

void WorkerSignalGenerator::doWork()
{

}

bool WorkerSignalGenerator::init()
{

	return m_bIsWorkerInitialized;
}


