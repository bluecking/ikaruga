/*
 * MainWindow.hpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#ifndef SRC_EDITOR_APP_EDITORMAINWINDOW_HPP_
#define SRC_EDITOR_APP_EDITORMAINWINDOW_HPP_

#include <QtGui>

#include "MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();

public Q_SLOTS:
	void openLevel();
	void buttonErasePressed();
	void buttonSavePressed();

private:
	void connectSignalsAndSlots();

};


#endif /* SRC_EDITOR_APP_EDITORMAINWINDOW_HPP_ */
