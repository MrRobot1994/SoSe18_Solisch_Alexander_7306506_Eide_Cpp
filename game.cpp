#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "button.h"
#include <QGraphicsRectItem>
#include "enemies.h"
#include <windows.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QPalette>
#include <QBrush>
#include <QTextStream>



Game::Game(QWidget *parent){

    //Einstellung der Szene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

    //Einstellung der Fesntergröße
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //Spieler wird geschaffen und die Szene gesetzt
    player = new Player();
    player->setRect(0,0,80,40);
    player->setPos(350,550);

    //Farbe und Muster des Spielers
    QPen pen (Qt::black,2);
    player->setBrush(Qt::BDiagPattern);
    player->setPen(pen);

    //Kreierung liveIcon1
    liveIcon1 = new liveIcon();
    liveIcon1->setRect(0,0,15,15);
    liveIcon1->setPos(90,42);
    liveIcon1->setBrush(Qt::magenta);

    //Kreierung liveIcon2
    liveIcon2 = new liveIcon();
    liveIcon2->setRect(0,0,15,15);
    liveIcon2->setPos(110,42);
    liveIcon2->setBrush(Qt::magenta);

    //Kreierung liveIcon3
    liveIcon3 = new liveIcon();
    liveIcon3->setRect(0,0,15,15);
    liveIcon3->setPos(130,42);
    liveIcon3->setBrush(Qt::magenta);

    //Spieler für Tasteneingaben empfänglich machen
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();


    //Kreierung der Punkte
    punkte = new score();

    health1 = new health();
}

//  restart the game, delete the timers, score and health, and create them new again, if not they will still be going in the game over screen
void Game :: restart(){
    delete timer;
    delete timer1;
    delete timer2;
    delete timerHeal;
    delete Scoretimer;
    delete health1;
    health1 = new health();
    delete punkte;
    punkte = new score();
    liveIcon1->setBrush(Qt::magenta);
    liveIcon2->setBrush(Qt::magenta);
    liveIcon3->setBrush(Qt::magenta);
    player->setOpacity(1);
    player->setFocus();
}

void Game::prestart(){

    //Kreierung des Titels im Menü
    title = new QGraphicsTextItem(QString("SoSe18 Solisch Alexander"));
    QFont titleFont("comic sans",30);
    title->setFont(titleFont);
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    int tyPos = 100;
    title->setPos(txPos,tyPos);
    scene->addItem(title);

    //Kreierung des play buttons im Menü
    startbuttonmain = new button1(QString("Play"));
    int bx1Pos = this->width()/2 - startbuttonmain->boundingRect().width()/2;
    int by1Pos = 200;
    startbuttonmain->setPos(bx1Pos,by1Pos);
    connect(startbuttonmain,SIGNAL(clicked()),SLOT(start()));
    scene->addItem(startbuttonmain);

    //Kreierung des quit buttons im Menü
    quitbuttonmain = new button1(QString("Quit"));
    int q1xPos = this->width()/2 - quitbuttonmain->boundingRect().width()/2;
    int q1yPos = 350;
    quitbuttonmain->setPos(q1xPos,q1yPos);
    connect(quitbuttonmain,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitbuttonmain);

    //Kreierung des load buttons im Menü
    loadmain = new button1(QString("Load"));
    int lx1Pos = this->width()/2 - loadmain->boundingRect().width()/2;;
    int ly1Pos = 275;
    loadmain->setPos(lx1Pos,ly1Pos);
    connect(loadmain,SIGNAL(clicked()),this,SLOT(loadRestart()));
    scene->addItem(loadmain);

    //Kreierung des pause buttons
    stopbutton = new button(QString("Pause"));
    int pxPos = 10;
    int pyPos = 520;
    stopbutton->setPos(pxPos,pyPos);
    connect(stopbutton,SIGNAL(clicked()),SLOT(pause()));

    //Kreierung des quit buttons
    quit= new button(QString("Quit"));
    int qxPos = 10;
    int qyPos = 580;
    quit->setPos(qxPos,qyPos);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    //Kreierung des load buttons
    loadbutton = new button(QString("Load"));
    int lxPos = 10;
    int lyPos = 560;
    loadbutton->setPos(lxPos,lyPos);
    connect(loadbutton,SIGNAL(clicked()),this,SLOT(load()));

    //Kreierung des save buttons
    savebutton = new button(QString("Save"));
    int sxPos = 10;
    int syPos = 540;
    savebutton->setPos(sxPos,syPos);
    connect(savebutton,SIGNAL(clicked()),this,SLOT(save()));
}

// Initialises the game, deletes stuff from the main menu, calls restart if it's from the game over screen
void Game::start(){
    // Restarting game from game over menu
    if (health1->getHealth() == 0) {
        restart();
    } else {
        //Hinzufügen des player zur Szene
        scene->addItem(player);

        //Hinzufügen des liveIcon zur Szene
        scene->addItem(liveIcon1);
        scene->addItem(liveIcon2);
        scene->addItem(liveIcon3);

        //Hinzufügen der buttons
        scene->addItem(quit);
        scene->addItem(loadbutton);
        scene->addItem(savebutton);
        scene->addItem(stopbutton);
    }

    //Entfernen des title
    scene->removeItem(title);

    //Hinzufügen des healths zur Szene
    scene->addItem(health1);
    //Hinzufügen des scores zur Szene
    scene->addItem(punkte);

    //Entfernen der Main buttons
    scene->removeItem(startbuttonmain);
    scene->removeItem(quitbuttonmain);
    scene->removeItem(loadmain);

    //timer für spawn()

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn())); //spawn greift auf create enemy zu
    timer->start(750); // determines how fast they spawn

    timer1 = new QTimer();
    QObject::connect(timer1,SIGNAL(timeout()),player,SLOT(spawn1())); //spawn greift auf create enemy zu
    timer1->start(1000); // determines how fast they spawn

    timer2 = new QTimer();
    QObject::connect(timer2,SIGNAL(timeout()),player,SLOT(spawn2())); //spawn greift auf create enemy zu
    timer2->start(15000); // determines how fast they spawn

    timerHeal = new QTimer();
    QObject::connect(timerHeal,SIGNAL(timeout()),player,SLOT(spawnHeal())); //spawn greift auf create enemy zu
    timerHeal->start(7000); // determines how fast they spawn

    //Erhöht den Score im Sekundentakt
    Scoretimer = new QTimer();
    QObject::connect(Scoretimer,SIGNAL(timeout()),punkte,SLOT(increase()));
    Scoretimer->start(1000); // determines how fast they spawn

    player->show();
}


//Stops the game when pause button is clicked, and freezes the game if player get's hit
void Game::stop(bool freeze){

    //stop timer enemy "generator" aus start()
    timer->stop();
    timer1->stop();
    timer2->stop();
    timerHeal->stop();
    Scoretimer->stop();
    player->clearFocus();

    QList<QGraphicsItem*> sceneItems = this->scene->items();
    for(QGraphicsItem* item : sceneItems) {
        enemies* enemy = dynamic_cast<enemies*>(item);
        if (enemy == NULL) {
            continue;
        }
        enemy->stop();
    }

    // Freeze game for a second
    if (freeze) {
        Sleep(1000);
    }
}


//pause the game and switch the text on the button
void Game::pause(){

    if(timer->isActive()){
        stopbutton->setText(QString("Start"));
        this->stop(false);
    }
    else{
        stopbutton->setText(QString("Pause"));
        this->resume();
    }

}

//resume the game
void Game::resume(){

    //startet timer enemy  "generator" erneut
    timer->start();
    timer1->start();
    timer2->start();
    timerHeal->start();
    Scoretimer->start();
    player->setFocus();

    QList<QGraphicsItem*> sceneItems = this->scene->items();
    for(QGraphicsItem* item : sceneItems) {
        enemies* enemy = dynamic_cast<enemies*>(item);
        if (enemy == NULL) {
            continue;
        }
        enemy->resume();
    }
}

//Speicher funktion
void Game::save(){
//stops so that the game doesn't go on while you are saving it
    stopbutton->setText(QString("Start"));
    this->stop(false);
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,tr("Speichern als"),".",tr("Zeichnungen(*.myz)"));

    if(fileName.isNull()==false)
    {
        file.setFileName(fileName);

        QTextStream textStream(&file);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text ))
        {
            QMessageBox::warning(this,tr("Dateifehler"),tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        } else {
            // writing the text file, postion of the player, health and the score
            // make sure that there is only one value per line
            textStream << player->x()<<endl<<player->y()<<endl;
            textStream << punkte->getPunkte()<<endl;
            textStream << health1->getHealth()<<endl;
            // goes through all enemys in a list
            QList<QGraphicsItem*> sceneItems = this->scene->items();
            for(QGraphicsItem* item : sceneItems) {
                enemies* enemy = dynamic_cast<enemies*>(item);
                if (enemy == NULL) {
                    continue;
                }
                //stops the enemies and saves their position, type and rotation
                enemy->stop();
                textStream << enemy->x()<<endl<<enemy->y()<<endl<<enemy->getType()<<endl<<enemy->rotation()<<endl;
            }
        }

        file.close();
        return;
    }
}

//Lade funktion
void Game::load(){
// load the game in a paused state so that you have enought time to prepare yourself and hit the play button
    stopbutton->setText(QString("Start"));
    this->stop(false);
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this, tr("Öffnen"),".",tr("Zeichnungen(*.myz)"));

    //if data can't get loaded
    if(fileName.isNull()==false)
    {
        file.setFileName(fileName);

        QTextStream textStream(&file);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,tr("Dateifehler"),tr("Folgende Datei kann nicht geladen werden: ")+ fileName,QMessageBox::Ok);
        } else {
            //reads the data in the selected file
            //reads the whole line
            int playerX = textStream.readLine().toInt();
            int playerY = textStream.readLine().toInt();
            // sets the position, health and score with the data
            player->setPos(playerX,playerY);
            punkte->setPunkte(textStream.readLine().toInt());
            health1->setHealth(textStream.readLine().toInt());
            // goes through all enemys in a list
            QList<QGraphicsItem*> sceneItems = this->scene->items();
            for(QGraphicsItem* item : sceneItems) {
                enemies* enemy = dynamic_cast<enemies*>(item);
                if (enemy == NULL) {
                    continue;
                }
                // deletes the old enemys, because old enemys would be left, if you would load in the middle of a game
                scene->removeItem(enemy);
                delete enemy;
            }
            // reads the file until it hit the end, and creates new enemies based on the data in the file with their saved, position, type and rotation
            while(!textStream.atEnd()) {
                //reads three lines for the x,y values of the enemies and their type
                enemies * enemy = new enemies(textStream.readLine().toInt(), textStream.readLine().toInt(), textStream.readLine().toInt());
                enemy->setRotation(textStream.readLine().toInt());
                scene->addItem(enemy);
                enemy->stop();
            }
        }

        file.close();
        return;
    }
}
//for the load button in the main menu
void Game::loadRestart() {
    this->start();
    this->load();
}
