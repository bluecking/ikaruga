#include "MainWindow.hpp"



MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent){
	setupUi(this);
}

void MainWindow::on_action_oeffnen_triggered()
{
	QString filter = "Level Datei (*.lvl)";
	QString sFile=QFileDialog::getOpenFileName(this, "Select a levelfile to open...", QDir::currentPath(),filter);
	QFile fFile(sFile);
	int last=(fFile.fileName().lastIndexOf("/"))+1;
	this->bitmap_path->setText(fFile.fileName().mid(last));
	scene=new LevelScene(fFile.fileName(),this);
}

