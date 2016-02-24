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
    ui->VertOptions->addItem(filename);
    ui->VertOptions->addItem(frame);
    ui->VertOptions->addItem(position);
    ui->VertOptions->addItem(weapon);
}
ItemSettingsGui::ItemSettingsGui(Bot *bot,QWidget *parent) : ItemSettingsGui(parent)
{
    /*
    class NPC{
        public:
            std::string type;
            std::string move_function;
            signed int move_value;
            unsigned int fireRate;
            signed int speed;
            std::string weapon_type;
            unsigned int weapon_level;
    };
    Bot();
    std::string filename;
    int frameWidth;
    int frameHeight;
    int tileID;
    int positionX;
    int positionY;
    NPC npc;
    std::string color;*/
    this->bot=bot;
    QHBoxLayout *filename=new QHBoxLayout();
    QHBoxLayout *frame=new QHBoxLayout();
    QHBoxLayout *tile=new QHBoxLayout();
    QHBoxLayout *position=new QHBoxLayout();
    QHBoxLayout *color=new QHBoxLayout();
    QHBoxLayout *npc_type=new QHBoxLayout();
    QHBoxLayout *npc_move_function=new QHBoxLayout();
    QHBoxLayout *npc_move_value=new QHBoxLayout();
    QHBoxLayout *npc_fireRate=new QHBoxLayout();
    QHBoxLayout *npc_speed=new QHBoxLayout();
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
    x=new QLabel(QString::number(item->positionX));
    position->addWidget(x);
    x=new QLabel(" x ");
    frame->addWidget(x);
    x=new QLabel(QString::number(item->positionY));
    frame->addWidget(x);
    x=new QLabel("Color:");
    color->addWidget(x);
    x=new QLabel(QString::fromUtf8(bot->color.c_str()));
    color->addWidget(x);
    ui->VertOptions->addItem(filename);
    ui->VertOptions->addItem(frame);
    ui->VertOptions->addItem(tile);
    ui->VertOptions->addItem(position);
    ui->VertOptions->addItem(color);
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
    frame->addWidget(x);
    x=new QLabel(QString::number(item->positionY));
    frame->addWidget(x);
    x=new QLabel("Type:");
    type->addWidget(x);
    QComboBox *types=new QComboBox();
    types->addItem(QString::fromUtf8(player->stdWeapon.c_str()));
    types->addItem("Waffe 1");
    types->addItem("Waffe 2");
    types->addItem("Waffe 3");
    type->addWidget(types);
    ui->VertOptions->addItem(filename);
    ui->VertOptions->addItem(frame);
    ui->VertOptions->addItem(position);
    ui->VertOptions->addItem(type);
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
