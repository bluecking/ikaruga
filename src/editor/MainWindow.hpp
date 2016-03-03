#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "LevelView.h"
#include "QFileDialog"
#include "LevelScene.hpp"
#include <QStyleFactory>
#include <QList>
#include <QMap>
#include <QInputDialog>
#include <QMessageBox>
#include <QToolTip>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <iostream>
#include <QRegExp>

class LevelScene;
class MainWindow : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT
	public:
		
        MainWindow (QMainWindow *parent = 0, std::string folderPath = "");
        virtual ~MainWindow();
        void addBot(QString botName,QString description);
        void addPower(QString powerName,QString description);
		void resetBot();
		void resetPower();
		Ui::MainWindow *ui;
    
	private Q_SLOTS:
    
        void on_action_oeffnen_triggered();
        void on_actionSpeichern_triggered();
        void on_actionSpeichern_unter_triggered();
        void on_actionNeu_triggered();
        void openLast(QAction *action);
        void on_pushButton_released();
        void on_save_id_released();
        void on_saveLevelName_released();
        void on_botList_itemClicked(QListWidgetItem *item);
        void on_powerList_itemClicked(QListWidgetItem *item);
	
	private:

	    std::string m_resPath;
		LevelScene* scene;
    	QString openedFile;
    	QMap<QString,QString> lastOpenedFiles;
    	void openFile(QString sFile);
    	void saveFile(QString sFile);
};
#endif //MAINWINDOW_HPP
