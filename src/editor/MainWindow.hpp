#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "ui_LevelView.h"
#include "QFileDialog"
#include "LevelScene.hpp"

class LevelScene;
class MainWindow : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT
	public:
		MainWindow (QMainWindow *parent = 0);
		virtual ~MainWindow(){};
	private slots:
        void on_action_oeffnen_triggered();
	private:
	LevelScene* scene;
};
#endif //MAINWINDOW_HPP
