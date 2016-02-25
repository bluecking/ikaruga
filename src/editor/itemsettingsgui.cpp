#include "itemsettingsgui.h"
#include "ui_itemsettingsgui.h"

ItemSettingsGui::ItemSettingsGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemSettingsGui)
{
    ui->setupUi(this);
    this->player=NULL;
    this->bot=NULL;
    this->item=NULL;
}

ItemSettingsGui::ItemSettingsGui(Player *player,QWidget *parent) : ItemSettingsGui(parent)
{
    this->player=player;
    QHBoxLayout *filename=new QHBoxLayout();
    QHBoxLayout *frame=new QHBoxLayout();
    QHBoxLayout *position=new QHBoxLayout();
    QHBoxLayout *weapon=new QHBoxLayout();
    QLabel *x=new QLabel("Filename:");
    filename->addWidget(x);
    x=new QLabel(QString::fromUtf8(player->filename.c_str()));
    filename->addWidget(x);
    x=new QLabel("Frame:");
    frame->addWidget(x);
    QSpacerItem *s=new QSpacerItem(20,40,QSizePolicy::Maximum);
    frame->addSpacerItem(s);
    x=new QLabel(QString::number(player->frameWidth));
    frame->addWidget(x);
    x=new QLabel(" x ");
    frame->addWidget(x);
    x=new QLabel(QString::number(player->frameHeight));
    frame->addWidget(x);
    s=new QSpacerItem(20,40,QSizePolicy::Maximum);
    frame->addSpacerItem(s);
    x=new QLabel("Starthöhe:");
    position->addWidget(x);
    x=new QLabel(QString::number(player->positionY));
    position->addWidget(x);
    x=new QLabel("Weapon:");
    weapon->addWidget(x);
    QComboBox *weapons=new QComboBox();
    weapons->addItem(QString::fromUtf8(player->stdWeapon.c_str()));
    weapons->addItem("Waffe 1");
    weapons->addItem("Waffe 2");
    weapons->addItem("Waffe 3");
    weapon->addWidget(weapons);
    ui->VertOptions->addLayout(filename);
    ui->VertOptions->addLayout(frame);
    ui->VertOptions->addLayout(position);
    ui->VertOptions->addLayout(weapon);
}
ItemSettingsGui::ItemSettingsGui(Bot *bot,QWidget *parent) : ItemSettingsGui(parent)
{
    this->bot=bot;
    QHBoxLayout *filename=new QHBoxLayout();
    QHBoxLayout *frame=new QHBoxLayout();
    QHBoxLayout *tile=new QHBoxLayout();
    QHBoxLayout *position=new QHBoxLayout();
    QHBoxLayout *color=new QHBoxLayout();
    QHBoxLayout *npc_type=new QHBoxLayout(); //NORMAL,BOSS
    QHBoxLayout *npc_move_function=new QHBoxLayout(); //NO_MOVE,SIN,SIN_UP,SIN_DOWN
    QHBoxLayout *npc_move_value=new QHBoxLayout();//0-100 QSpinBox setMaximum/setMinimum/value
    QHBoxLayout *npc_fireRate=new QHBoxLayout();//?
    QHBoxLayout *npc_speed=new QHBoxLayout();//0=Mit Karte -x=entgegen 100=gleichschnell (max)
    QHBoxLayout *npc_weapon_type=new QHBoxLayout();
    QHBoxLayout *npc_weapon_level=new QHBoxLayout();
    QLabel *x=new QLabel("Filename:");
    filename->addWidget(x);
    x=new QLabel(QString::fromUtf8(bot->filename.c_str()));
    filename->addWidget(x);
    x=new QLabel("Frame:");
    frame->addWidget(x);
    QSpacerItem *s=new QSpacerItem(20,40,QSizePolicy::Maximum);
    frame->addSpacerItem(s);
    x=new QLabel(QString::number(bot->frameWidth));
    frame->addWidget(x);
    x=new QLabel(" x ");
    frame->addWidget(x);
    x=new QLabel(QString::number(bot->frameHeight));
    frame->addWidget(x);
    x=new QLabel("TileID:");
    tile->addWidget(x);
    x=new QLabel(QString::number(bot->tileID));
    tile->addWidget(x);
    x=new QLabel("Position:");
    position->addWidget(x);
    x=new QLabel(QString::number(bot->positionX));
    position->addWidget(x);
    x=new QLabel(" x ");
    position->addWidget(x);
    x=new QLabel(QString::number(bot->positionY));
    position->addWidget(x);
    x=new QLabel("Color:");
    color->addWidget(x);
    x=new QLabel(QString::fromUtf8(bot->color.c_str()));
    color->addWidget(x);
    x=new QLabel("BotType:");
    npc_type->addWidget(x);
    QComboBox *types=new QComboBox();
    types->addItem(QString::fromUtf8(bot->npc->type.c_str()));
    types->addItem("Normal");
    types->addItem("Boss");
    npc_type->addWidget(types);
    x=new QLabel("Move Function:");
    npc_move_function->addWidget(x);
    QComboBox *move_func=new QComboBox();
    move_func->addItem(QString::fromUtf8(bot->npc->type.c_str()));
    move_func->addItem("NO_MOVE");
    move_func->addItem("SIN");
    move_func->addItem("SIN_UP");
    move_func->addItem("SIN_DOWN");
    npc_move_function->addWidget(move_func);
    x=new QLabel("Move Value:");
    npc_move_value->addWidget(x);
    QSpinBox *move_value=new QSpinBox();
    move_value->setMinimum(0);
    move_value->setMaximum(100);
    move_value->setValue(bot->npc->move_value);
    npc_move_value->addWidget(move_value);
    x=new QLabel("Firerate:");
    npc_fireRate->addWidget(x);
    QSpinBox *firerate=new QSpinBox();
    firerate->setMinimum(0.2);
    firerate->setMaximum(10);
    firerate->setValue(bot->npc->fireRate);
    npc_fireRate->addWidget(firerate);
    x=new QLabel("Movespeed:");
    npc_speed->addWidget(x);
    QSpinBox *speed=new QSpinBox();
    speed->setMinimum(-100);
    speed->setMaximum(100);
    speed->setValue(bot->npc->speed);
    npc_speed->addWidget(speed);
    x=new QLabel("Weapon Type:");
    npc_weapon_type->addWidget(x);
    QComboBox *weapon_type=new QComboBox();
    weapon_type->addItem(QString::fromUtf8(bot->npc->weapon_type.c_str()));
    weapon_type->addItem("LaserWeapon");
    npc_weapon_type->addWidget(weapon_type);
    x=new QLabel("Weapon Level:");
    npc_weapon_level->addWidget(x);
    QSpinBox *level=new QSpinBox();
    level->setMinimum(1);
    level->setMaximum(1);
    level->setValue(bot->npc->weapon_level);
    npc_weapon_level->addWidget(level);
    ui->VertOptions->addLayout(filename);
    ui->VertOptions->addLayout(frame);
    ui->VertOptions->addLayout(tile);
    ui->VertOptions->addLayout(position);
    ui->VertOptions->addLayout(color);
    ui->VertOptions->addLayout(npc_fireRate);
    ui->VertOptions->addLayout(npc_move_function);
    ui->VertOptions->addLayout(npc_move_value);
    ui->VertOptions->addLayout(npc_speed);
    ui->VertOptions->addLayout(npc_type);
    ui->VertOptions->addLayout(npc_weapon_level);
    ui->VertOptions->addLayout(npc_weapon_type);
}
ItemSettingsGui::ItemSettingsGui(Item *item,QWidget *parent) : ItemSettingsGui(parent)
{
    this->item=item;
    QHBoxLayout *filename=new QHBoxLayout();
    QHBoxLayout *frame=new QHBoxLayout();
    QHBoxLayout *position=new QHBoxLayout();
    QHBoxLayout *type=new QHBoxLayout();
    QLabel *x=new QLabel("Filename:");
    filename->addWidget(x);
    x=new QLabel(QString::fromUtf8(item->filename.c_str()));
    filename->addWidget(x);
    x=new QLabel("Frame:");
    frame->addWidget(x);
    QSpacerItem *s=new QSpacerItem(20,40,QSizePolicy::Maximum);
    frame->addSpacerItem(s);
    x=new QLabel(QString::number(item->frameWidth));
    frame->addWidget(x);
    x=new QLabel(" x ");
    frame->addWidget(x);
    x=new QLabel(QString::number(item->frameHeight));
    frame->addWidget(x);
    x=new QLabel("Position:");
    position->addWidget(x);
    x=new QLabel(QString::number(item->positionX));
    position->addWidget(x);
    x=new QLabel(" x ");
    position->addWidget(x);
    x=new QLabel(QString::number(item->positionY));
    position->addWidget(x);
    x=new QLabel("Type:");
    type->addWidget(x);
    QComboBox *types=new QComboBox();
    types->addItem(QString::fromUtf8(item->type.c_str()));
    types->addItem("PowerUp");
    type->addWidget(types);
    ui->VertOptions->addLayout(filename);
    ui->VertOptions->addLayout(frame);
    ui->VertOptions->addLayout(position);
    ui->VertOptions->addLayout(type);
}

ItemSettingsGui::~ItemSettingsGui()
{
    delete ui;
}

void ItemSettingsGui::on_ButtonOption_accepted()
{
    if(this->player!=NULL){
        QHBoxLayout *hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(0));
        player->filename=((QLabel*)hbox->itemAt(1))->text().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(1));
        player->frameWidth=((QLabel*)hbox->itemAt(1))->text().toInt();
        player->frameHeight=((QLabel*)hbox->itemAt(3))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(2));
        player->positionY=((QLabel*)hbox->itemAt(1))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(3));
        player->stdWeapon=((QComboBox*)hbox->itemAt(1))->currentText().toStdString();
    }else if(this->bot!=NULL){
        QHBoxLayout *hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(0));
        bot->filename=((QLabel*)hbox->itemAt(1))->text().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(1));
        bot->frameWidth=((QLabel*)hbox->itemAt(1))->text().toInt();
        bot->frameHeight=((QLabel*)hbox->itemAt(3))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(2));
        bot->tileID=((QLabel*)hbox->itemAt(1))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(3));
        bot->positionX=((QLabel*)hbox->itemAt(1))->text().toInt();
        bot->positionY=((QLabel*)hbox->itemAt(3))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(4));
        bot->color=((QLabel*)hbox->itemAt(1))->text().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(5));
        bot->npc->fireRate=((QSpinBox*)hbox->itemAt(1))->value();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(6));
        bot->npc->move_function=((QComboBox*)hbox->itemAt(1))->currentText().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(7));
        bot->npc->move_value=((QSpinBox*)hbox->itemAt(1))->value();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(8));
        bot->npc->speed=((QSpinBox*)hbox->itemAt(1))->value();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(9));
        bot->npc->type=((QComboBox*)hbox->itemAt(1))->currentText().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(10));
        bot->npc->weapon_level=((QSpinBox*)hbox->itemAt(1))->value();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(11));
        bot->npc->weapon_type=((QComboBox*)hbox->itemAt(1))->currentText().toStdString();
    }else if(this->item!=NULL){
        QHBoxLayout *hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(0));
        item->filename=((QLabel*)hbox->itemAt(1))->text().toStdString();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(1));
        item->frameWidth=((QLabel*)hbox->itemAt(1))->text().toInt();
        item->frameHeight=((QLabel*)hbox->itemAt(3))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(2));
        item->positionX=((QLabel*)hbox->itemAt(1))->text().toInt();
        item->positionY=((QLabel*)hbox->itemAt(3))->text().toInt();
        hbox=(QHBoxLayout*)(ui->VertOptions->itemAt(3));
        item->type=((QComboBox*)hbox->itemAt(1))->currentText().toStdString();
    }
    this->~ItemSettingsGui();
}

void ItemSettingsGui::on_ButtonOption_rejected()
{
    this->~ItemSettingsGui();
}
