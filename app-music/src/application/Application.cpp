/**
* \file Application.cpp
* \brief Defines Application
* \author Guillaume Gibert
* \date 27/01/2020
*/

#include "application/Application.h"

Application::Application()
{

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

}

void Application::registerMetaTypes()
{
	// register opencv data types
	qRegisterMetaType< std::vector<float> >("std::vector<float>");
	qRegisterMetaType< std::vector< std::deque<float> > >("std::vector<std::deque<float>>");
}

void Application::setWorkerConnections()
{
	
}

void Application::moveWorkersToThread()
{
	
}

void Application::stopWorkerThreads()
{
	
}

void Application::deleteWorkers()
{
	
		
}
