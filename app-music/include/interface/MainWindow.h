/**
* \file MainWindow.h
* \brief Defines Application
* \author Guillaume Gibert
* \date 27/01/2020
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QMessagebox.h>
#include <QFileDialog>

#include "BufferedSignalDisplay.h"

// Qt stuff
namespace Ui {
class MainWindow;
}


/**
* \class MainWindow
* \brief Represents the main window of the application.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	* \brief The constructor.
	* \param [in] parent: the widget parent
	*/
	explicit MainWindow(QWidget *parent = 0);

	
	/**
	* \brief The function to delete the object.
	*/
	~MainWindow();

	

public slots:
		

signals:
	
private:
	void initWidgets();
	
private:
	Ui::MainWindow *ui;									// Also Qt stuff
	
	BufferedSignalDisplay* m_pWBufferedSignalDisplay;

	BufferedSignalDisplay* m_pWPowerSpectrumDisplay;
};

#endif // MAINWINDOW_H
