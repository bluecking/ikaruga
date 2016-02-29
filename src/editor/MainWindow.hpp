#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "ui_LevelView.h"
#include "QFileDialog"
#include "LevelScene.hpp"
#include <QList>
#include <QMap>
#include <QInputDialog>
#include <QMessageBox>

class LevelScene;
class MainWindow : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT
	public:
		MainWindow (QMainWindow *parent = 0);
        virtual ~MainWindow();
		Ui::MainWindow *ui;
	private slots:
        void on_action_oeffnen_triggered();
        void on_actionSpeichern_triggered();
        void on_actionSpeichern_unter_triggered();
        void on_actionNeu_triggered();
        void openLast(QAction *action);
        void on_pushButton_released();

private:
	LevelScene* scene;
    QString openedFile;
    QMap<QString,QString> lastOpenedFiles;
    void openFile(QString sFile);
    void saveFile(QString sFile);
};
#endif //MAINWINDOW_HPP
