#include "itemsettingsgui.h"
#include "ui_itemsettingsgui.h"

ItemSettingsGui::ItemSettingsGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSettingsGui)
{
    ui->setupUi(this);
}

ItemSettingsGui::ItemSettingsGui(Player *player,QWidget *parent) : ItemSettingsGui(parent)
{

}
ItemSettingsGui::ItemSettingsGui(Bot *player,QWidget *parent) : ItemSettingsGui(parent)
{

}
ItemSettingsGui::ItemSettingsGui(Item *player,QWidget *parent) : ItemSettingsGui(parent)
{

}

ItemSettingsGui::~ItemSettingsGui()
{
    delete ui;
}

void ItemSettingsGui::on_ButtonOption_accepted()
{

}

void ItemSettingsGui::on_ButtonOption_rejected()
{

}
