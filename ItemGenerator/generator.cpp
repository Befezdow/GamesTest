#include "generator.h"

Generator::Generator(QWidget *parent):
    QWidget(parent),
    nextID(0)
{
    pathLabel = new QLabel("Path to JSON:");
    pathLabel->setAlignment(Qt::AlignCenter);
    pathLine = new QLineEdit;
    browse = new QPushButton("...");

    costLabel = new QLabel("Cost of item:");
    titleLabel = new QLabel("Title of item:");
    descriptionLabel = new QLabel("Description:");
    maxCountLabel = new QLabel("Count in stack:");
    levelLabel = new QLabel("Necessary level:");
    rarityLabel = new QLabel("Rarity of item:");
    typeLabel = new QLabel("Type of Item:");
    attackDamageLabel = new QLabel("Attack Damage:");
    enduranceLabel = new QLabel("Endurance bonus:");
    wisdomLabel = new QLabel("Wisdom bonus:");
    charismaLabel = new QLabel("Charisma bonus:");
    intelligenceLabel = new QLabel("Intelligence bonus:");
    adaptabilityLabel = new QLabel("Adaptability bonus:");
    nameOfIconLabel = new QLabel("Name of icon:");

    costLine = new QLineEdit;
    titleLine = new QLineEdit;
    descriptionText = new QTextEdit;
    maxCountLine = new QLineEdit(QString::number(1));
    levelLine = new QLineEdit;
    rarityBox = new QComboBox;
    typeBox = new QComboBox;
    attackDamageLine = new QLineEdit(QString::number(0));
    enduranceLine = new QLineEdit(QString::number(0));
    wisdomLine = new QLineEdit(QString::number(0));
    charismaLine = new QLineEdit(QString::number(0));
    intelligenceLine = new QLineEdit(QString::number(0));
    adaptabilityLine = new QLineEdit(QString::number(0));
    nameOfIconLine = new QLineEdit;

    button = new QPushButton("Add into the file");
    button->setMinimumSize(100,50);

    QStringList rarityList({"Common","Uncommon","Rare","Epic","Artifact"});
    QStringList typeList({"Amulet","Helment","Ring","Gloves","Armor","Weapon","Belt","Boots","Trash","QuestItem","ComponentForCraft","UsefulItem"});

    rarityBox->addItems(rarityList);
    typeBox->addItems(typeList);

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(titleLabel,0,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(titleLine,0,1,1,1);
    gridLayout->addWidget(descriptionLabel,1,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(descriptionText,1,1,1,1);
    gridLayout->addWidget(typeLabel,2,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(typeBox,2,1,1,1);
    gridLayout->addWidget(rarityLabel,3,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(rarityBox,3,1,1,1);
    gridLayout->addWidget(levelLabel,4,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(levelLine,4,1,1,1);
    gridLayout->addWidget(costLabel,5,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(costLine,5,1,1,1);
    gridLayout->addWidget(nameOfIconLabel,6,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(nameOfIconLine,6,1,1,1);
    gridLayout->addWidget(maxCountLabel,7,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(maxCountLine,7,1,1,1);
    gridLayout->addWidget(attackDamageLabel,8,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(attackDamageLine,8,1,1,1);
    gridLayout->addWidget(enduranceLabel,9,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(enduranceLine,9,1,1,1);
    gridLayout->addWidget(wisdomLabel,10,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(wisdomLine,10,1,1,1);
    gridLayout->addWidget(charismaLabel,11,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(charismaLine,11,1,1,1);
    gridLayout->addWidget(intelligenceLabel,12,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(intelligenceLine,12,1,1,1);
    gridLayout->addWidget(adaptabilityLabel,13,0,1,1,Qt::AlignLeft);
    gridLayout->addWidget(adaptabilityLine,13,1,1,1);

    QLabel* separator = new QLabel("--------------------------------------------");
    separator->setAlignment(Qt::AlignCenter);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(pathLine);
    hLayout->addWidget(browse);

    QVBoxLayout* vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(pathLabel,Qt::AlignHCenter);
    vLayout1->addLayout(hLayout);
    vLayout1->addWidget(separator,Qt::AlignHCenter);

    QVBoxLayout* vLayout2 = new QVBoxLayout;
    vLayout2->addLayout(vLayout1);
    vLayout2->addLayout(gridLayout);
    vLayout2->addWidget(button);

    this->setLayout(vLayout2);

    connect(browse,SIGNAL(clicked(bool)),this,SLOT(ChooseFile()));
    connect(button,SIGNAL(clicked(bool)),this,SLOT(AppendItem()));
    connect(pathLine,SIGNAL(textChanged(QString)),this,SLOT(GetObjectsCount()));
}

void
Generator::GetObjectsCount()
{
    if (!QFile::exists(pathLine->text()))
    {
        nextID = 0;
        return;
    }

    QFile file(pathLine->text());

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    unsigned int objectsCount = 0;

    while (!file.atEnd())
    {
        char c;
        file.getChar(&c);
        if (c == '{')
        {
            objectsCount++;
        }
    }

    file.close();

    nextID = objectsCount;

}

void
Generator::AppendItem()
{
    QFile file(pathLine->text());
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(this,"File error","File can't be opened");
        return;
    }

    QTextStream stream(&file);

    if (nextID == 0)
    {
        stream<<"["<<endl;
        stream<<"\t{"<<endl;
    }
    else
    {
        stream.seek(file.size() - 2);
        stream<<','<<endl<<"\t{"<<endl;
    }

    stream<<"\t\t\"id\" : "             + QString::number(nextID)                                           + ","<<endl;
    stream<<"\t\t\"cost\" : "           + costLine->text().trimmed()                                        + ","<<endl;
    stream<<"\t\t\"title\" : "          + QString("\"") + titleLine->text().trimmed() + "\""                + ","<<endl;
    stream<<"\t\t\"description\" : "    + QString("\"") + descriptionText->toPlainText().trimmed() + "\""   + ","<<endl;
    stream<<"\t\t\"maxCount\" : "       + maxCountLine->text().trimmed()                                    + ","<<endl;
    stream<<"\t\t\"level\" : "          + levelLine->text().trimmed()                                       + ","<<endl;
    stream<<"\t\t\"rarity\" : "         + QString("\"") + rarityBox->currentText().trimmed() + "\""         + ","<<endl;
    stream<<"\t\t\"type\" : "           + QString("\"") + typeBox->currentText().trimmed() + "\""           + ","<<endl;
    stream<<"\t\t\"attackDamage\" : "   + attackDamageLine->text().trimmed()                                + ","<<endl;
    stream<<"\t\t\"endurance\" : "      + enduranceLine->text().trimmed()                                   + ","<<endl;
    stream<<"\t\t\"wisdom\" : "         + wisdomLine->text().trimmed()                                      + ","<<endl;
    stream<<"\t\t\"charisma\" : "       + charismaLine->text().trimmed()                                    + ","<<endl;
    stream<<"\t\t\"intelligence\" : "   + intelligenceLine->text().trimmed()                                + ","<<endl;
    stream<<"\t\t\"adaptability\" : "   + adaptabilityLine->text().trimmed()                                + ","<<endl;
    stream<<"\t\t\"nameOfIcon\" : "     + QString("\"") + nameOfIconLine->text().trimmed() + "\""           <<endl;

    stream<<"\t}"<<endl<<"]";

    file.close();

    nextID++;
}

void
Generator::ChooseFile()
{
    QString str = QFileDialog::getOpenFileName(this,"Open file",QDir::rootPath(),"*.json");

    if (!str.isNull())
    {
        pathLine->setText(str);
        this->GetObjectsCount();
    }
}
