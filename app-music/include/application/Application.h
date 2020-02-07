/**
* \file Application.h
* \brief Defines Application
* \author Guillaume Gibert
* \date 27/01/2020
*/

#ifndef _APPLICATION_H
#define _APPLICATION_H

// Window
#include "interface/MainWindow.h"

// Qt
#include <QThread>

#include "workers/WorkerSignalGenerator.h"
#include "workers/WorkerMusicPlayer.h"

/**
* \class Application
* \brief The object which represents the application and manages it.
*/
class Application: public QObject
{
	Q_OBJECT

public:
	/**
	* \brief The constructor of the object.
	*/
	Application();

	/**
	* \brief The delete of the object.
	*/
	~Application();

	/**
	* \brief The function that initialize the application.
	*/
	void init(MainWindow* window);



private:
	void registerMetaTypes();

	void initWorkers();
	void setWorkerConnections();
	void moveWorkersToThread();
	void stopWorkerThreads();
	void deleteWorkers();

signals:
	
	// -------------------- SIGNALS FOR THE WINDOW --------------------

	

public slots:

	// -------------------- WINDOW SLOTS --------------------	

	


public:
	
private:
	MainWindow* m_window = nullptr;						/**< The main window. */
	
	WorkerSignalGenerator* m_pWorkerSignalGenerator;
	QThread m_TWorkerSignalGenerator;

	WorkerMusicPlayer* m_pWorkerMusicPlayer;
	QThread m_TWorkerMusicPlayer;
};

#endif