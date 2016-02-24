/*
 * MainWindow.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#include "EditorMainWindow.hpp"
#include "TilesetScene.hpp"
#include "LevelScene.hpp"

MainWindow::MainWindow()
{
	setupUi(this);
	connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{

}

void MainWindow::connectSignalsAndSlots()
{
	QObject::connect(this->pushButtonLoadLevel, SIGNAL(pressed()), this, SLOT(openLevel()));
	QObject::connect(this->pushButtonErase, SIGNAL(pressed()), this, SLOT(buttonErasePressed()));
	QObject::connect(this->pushButtonSaveLevel, SIGNAL(pressed()), this, SLOT(buttonSavePressed()));
}

void MainWindow::buttonErasePressed()
{
	TilesetScene* s = static_cast<TilesetScene*>(graphicsViewTiles->scene());
	s->m_selectedItem = 0;
}

void MainWindow::buttonSavePressed()
{
	LevelScene* s = static_cast<LevelScene*>(graphicsViewLevel->scene());

	QString fileName = QFileDialog::getSaveFileName(this,
	    tr("Save Level"), "./", tr("Levels (*.lvl)"));

	s->save(fileName.toStdString());
}

void MainWindow::openLevel()
{
	QString fileName = QFileDialog::getOpenFileName(this,
	    tr("Open Level"), "./", tr("Levels (*.lvl)"));

	TilesetScene* scene = new TilesetScene(fileName, this);
	LevelScene* levelScene = new LevelScene(fileName, this);

	this->graphicsViewTiles->setScene(scene);
	this->graphicsViewLevel->setScene(levelScene);
}

