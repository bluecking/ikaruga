#include "MainWindow.hpp"
#include <iostream>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSpeichern->setEnabled(false);
    ui->actionSpeichern_unter->setEnabled(false);
    connect(ui->menuZuletzt_geoeffnet, SIGNAL(triggered(QAction*)), this, SLOT(openLast(QAction*)));
    QRect buttonSize=ui->pushButton->geometry();
    buttonSize.setWidth(buttonSize.height());
    ui->pushButton->setGeometry(buttonSize);
    buttonSize.setX(0);
    buttonSize.setY(0);
    ui->pushButton->setIconSize(buttonSize.size());
    ui->level_size->setMinimum(10);
    ui->level_size->setMaximum(10000);
    ui->level_size->setValue(300);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addBot(QString botName,QString description)
{
    ui->botList->addItem(botName);
    QListWidgetItem* x=ui->botList->item(ui->botList->count()-1);
    x->setToolTip(description);
}

void MainWindow::addPower(QString powerName,QString description)
{
    ui->powerList->addItem(powerName);
    QListWidgetItem* x=ui->powerList->item(ui->powerList->count()-1);
    x->setToolTip(description);
}

void MainWindow::resetBot()
{
    ui->botList->clear();
}

void MainWindow::resetPower()
{
    ui->powerList->clear();
}

void MainWindow::openLast(QAction *action){

   QString x=action->text();
   QString sFile=this->lastOpenedFiles.value(x,NULL);
   if(x!=NULL)
   {
       openFile(sFile);
   }
}

void MainWindow::openFile(QString sFile)
{
    //std::cout<<"Open: "<<sFile.toStdString()<<std::endl;

    QFile fFile(sFile);
    this->openedFile=sFile;
    QFileInfo fileInfo(fFile.fileName());
    QString filename(fileInfo.fileName());
    if(!this->lastOpenedFiles.contains(filename))
    {
        this->lastOpenedFiles.insert(filename,sFile);
        ui->menuZuletzt_geoeffnet->addAction(new QAction(filename,ui->menuZuletzt_geoeffnet));

    }
    else
    {
        QString tmp;
        QString fName=filename;
        int i=1;

        do
        {
            tmp = this->lastOpenedFiles.value(filename, NULL);

            if (tmp == NULL) {
                this->lastOpenedFiles.insert(fName, sFile);
                ui->menuZuletzt_geoeffnet->addAction(new QAction(fName, ui->menuZuletzt_geoeffnet));
                break;
            }
            else {
                if (tmp == sFile)break;
                else fName = filename + " (" + QString::number(i) + ")";
            }
        }while(true);
    }

    int last=(sFile.lastIndexOf("/"))+1;
    ui->bitmap_path->setText(sFile.mid(last));
    scene=new LevelScene(sFile,this);
    ui->actionSpeichern->setEnabled(true);
    ui->actionSpeichern_unter->setEnabled(true);
}

void MainWindow::saveFile(QString sFile)
{
    if(this->openedFile!="")
    {
        //std::cout<<"Save: "<<sFile.toStdString()<<std::endl;
        scene->saveXml(sFile);
    }
}

void MainWindow::on_action_oeffnen_triggered()
{
    QString filter = "Level Datei (*.xml)";
    QString sFile=QFileDialog::getOpenFileName(this, "Select a level to open...", QDir::currentPath(),filter);

    if(sFile!=NULL)
    {
        this->openFile(sFile);
    }
}


void MainWindow::on_actionSpeichern_triggered()
{
    this->saveFile(this->openedFile);
}

void MainWindow::on_actionSpeichern_unter_triggered()
{
    QString filter = "Level Datei (*.xml)";
    QString sFile=QFileDialog::getSaveFileName(this,"Select a level to save",QDir::currentPath(),filter);

    if(sFile!=NULL)
    {
        if(!sFile.endsWith(".xml",Qt::CaseInsensitive))
        {
            sFile+=".xml";
        }

        this->saveFile(sFile);
    }
}

void MainWindow::on_actionNeu_triggered()
{
    QInputDialog* dialog=new QInputDialog(this,Qt::Widget);
    QString result = dialog->getText(this, "New Level", "Levelname:", QLineEdit::Normal);

    if(result!=NULL)
    {
        if(result.length()<3)
        {
            QMessageBox messageBox;
            messageBox.critical(this,"Error","The Levelname needs to be longer than 2 Characters!");
            messageBox.setFixedSize(500,200);
        }
        if(!result.endsWith(".xml",Qt::CaseInsensitive))
        {
            result+=".xml";
        }

        this->openFile(QDir::currentPath()+"/../res/levels/"+result);
    }
}

void MainWindow::on_pushButton_released()
{
    scene->setSize(ui->level_size->value());
}

void MainWindow::on_save_id_released()
{
    scene->setId(ui->level_id->value());
}

void MainWindow::on_saveLevelName_released()
{
    scene->setLevelName(ui->level_name->text());
}

void MainWindow::on_botList_itemClicked(QListWidgetItem *item)
{
    scene->setBot(item->text());
}

void MainWindow::on_powerList_itemClicked(QListWidgetItem *item)
{
    scene->setPower(item->text());scene->setPower(item->text());
}
