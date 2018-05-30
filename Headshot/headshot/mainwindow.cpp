#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h_limit=1270;                   //Asigna los valores leidos el archivo
    v_limit=500;
    dt = 0.06;                        //Asigna el lapso de tiempo

    timer=new QTimer(this);                 //crea el timer
    timerPower = new QTimer(this);          //Crea timer del progressBar
    scene=new QGraphicsScene(this);         //crea la scene
    scene->setSceneRect(0,0,h_limit,v_limit);     //asigna el rectangulo que encierra la scene, determinado por h_limit y v_limit

    ui->graphicsView->setScene(scene);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->viewport()->setMouseTracking(true);
            qDebug()<<ui->graphicsView->size();
    ui->centralWidget->adjustSize();
            qDebug()<<ui->centralWidget->size();
   //this->adjustSize();//

        qDebug()<<this->size();
    scene->addRect(scene->sceneRect());
    this->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Headshot UdeA")); //Título ventana
    timer->stop();                              //para el timer
    timerPower->stop();                         //para el timer del progressBar

    proyector.append(new proyectorGraf(55, 13));
    scene->addItem(proyector.last());
    scene->setBackgroundBrush(QPixmap(":/Img/fondo"));

    QFile file_2(RUTA_ARCHIVO_2);           //Objeto para manejar la lectura del archivo
    file_2.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    obs=file_2.readAll();
    obs.remove("\n");
    obs.remove("\r");
    file_2.close();
    loader(1);
    QFile file(RUTA_ARCHIVO);           //Objeto para manejar la lectura del archivo
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    obje=file.readAll();
    obje.remove("\n");
    obje.remove("\r");
    file.close();
    loader(0);


    QFont tipo("Times",12,QFont::StyleItalic);
    scene->addText("Score: ",tipo); //Añade un texto en la esena
    scene->addText("Snowballs: ",tipo)->setPos(140,0);
    texto=scene->addText("0",tipo);// Añade el cero.
    vida = scene->addText("0",tipo);
    texto->setFlag(QGraphicsItem::ItemIsMovable);
    texto->setPos(50,0);//Posicion
    vida->setPlainText(QString::number(cantidad));
    vida->setPos(220,0);
    mensaje = scene->addText(" ", tipo);
    mensaje->setPos(1120,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(timerPower,SIGNAL(timeout()),this,SLOT(power())); //conecta la señal del timerPower con el slot power para el progressBar
    timerPower->start(20);
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/principal"));

    scene->addItem(guias.at(0));

}



void MainWindow::actualizar()
{
    if(obstaculos.isEmpty()==false || objetivos.isEmpty()==false){
    for(int i=0;i<proyectiles.size();i++){
        proyectiles.at(i)->actualizar(dt,v_limit);
        bordercollision(proyectiles.at(i));
    }
  }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
    delete timerPower;
}



void MainWindow::power() //SLOT donde se corre el progressBar
{
    if(i<100){
        i += 5;
        vel = i+50;
        ui->progressBar->setValue(i);
        if(i==100){
            j=100;
        }
    }
    else if(j>20){
        j-=5;
        vel = j+50;
        ui->progressBar->setValue(j);
        if(j==20){
            i=20;
        }
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) //Método donde se dan las posiciones del mouse (Solución sacada de internet, no sé porqué ni cómo funciona)
{
    event->accept();
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        QPointF pos = ui->graphicsView->mapToScene(mouse->pos());

        delta = atan2(((v_limit-13) - pos.y()),(pos.x() - 55)) * 180/PI;
        if(delta < -17){ //Se definen los límites para el ángulo, siendo -17 el menor y 70 el mayor
            delta = -17;
        }
        else if(delta > 70){
            delta = 70;
        }
        proyector.last()->setRotation(-1*delta); //Rota el cañón
    }
    return false;
}


void MainWindow::mousePressEvent(QMouseEvent *event) //Método que capta cuándo se presiona el botón del mouse y agrega proyectil
{
    if(cantidad>0 && ui->pushButton_Individual->isEnabled() == false && ui->pushButton_multijugador->isEnabled() == false && objetivos.isEmpty()==false){

        timer->start(16);
        proyectiles.append(new proyectilGraf(proyector.last()->getProyector()->get_px()+(62.87*cos((14.74356284+delta)*PI/180)), proyector.last()->getProyector()->get_py()+(62.87*sin((14.74356284+delta)*PI/180)), vel, delta));
        scene->addItem(proyectiles.last());
        cantidad-=1;
        vida->setPlainText(QString::number(cantidad));
        event->accept();
    }
}

void MainWindow::bordercollision(proyectilGraf* b)  //Colision con los bordes
{
    for(int i=0; i<obstaculos.size();i++){
        if(b->collidesWithItem(obstaculos.at(i)) && (obstaculos.at(i)->getObstaculo()->getDir() != ":/Img/cadena") && (obstaculos.at(i)->getObstaculo()->getDir() != ":/Img/cadena2")){
            if(((obstaculos.at(i)->getObstaculo()->getY()-obstaculos.at(i)->getObstaculo()->getH()/2) < b->getProyectil()->getY()) && (b->getProyectil()->getY()<(obstaculos.at(i)->getObstaculo()->getY()+obstaculos.at(i)->getObstaculo()->getH()/2))){
                b->getProyectil()->setVel(-1*b->getProyectil()->getVx(), b->getProyectil()->getVy());
            }
            if(((obstaculos.at(i)->getObstaculo()->getX()-obstaculos.at(i)->getObstaculo()->getW()/2) < b->getProyectil()->getX()) && (b->getProyectil()->getX()<(obstaculos.at(i)->getObstaculo()->getX()+obstaculos.at(i)->getObstaculo()->getW()/2))){
                b->getProyectil()->setVel(b->getProyectil()->getVx(), -1*b->getProyectil()->getVy());
            }
        }
    }
    if(b->getProyectil()->getX()<b->getProyectil()->getR()){
        b->getProyectil()->setVel(b->getProyectil()->get_e()*b->getProyectil()->getVx(),b->getProyectil()->getVy());
        b->getProyectil()->setPoint(b->getProyectil()->getR(), b->getProyectil()->getY());
    }
    else if(b->getProyectil()->getX()>h_limit-b->getProyectil()->getR()){
        b->getProyectil()->setVel(b->getProyectil()->get_e()*b->getProyectil()->getVx(),b->getProyectil()->getVy());
        b->getProyectil()->setPoint(h_limit-b->getProyectil()->getR(), b->getProyectil()->getY());
    }
    if(b->getProyectil()->getY()<b->getProyectil()->getR()){
        b->getProyectil()->setVel(b->getProyectil()->getVx(),-0.5*b->getProyectil()->getVy());
        b->getProyectil()->setPoint(b->getProyectil()->getX(),b->getProyectil()->getR());
    }
    else if(b->getProyectil()->getY()>v_limit-(b->getProyectil()->getR())){
        b->getProyectil()->setVel(b->getProyectil()->getVx(),-1*b->getProyectil()->getVy());
        b->getProyectil()->setPoint(b->getProyectil()->getX(),v_limit-b->getProyectil()->getR());
    }
    for(int i=0; i<objetivos.size();i++){
        if(b->collidesWithItem(objetivos.at(i))){

            scene->removeItem(objetivos.at(i));
            scene->removeItem(b);
            objetivos.removeAt(i);
            proyectiles.removeOne(b);
            puntuacion += 100; //Suma puntuacion
            texto->setPlainText(QString::number(puntuacion));//Cambia la puntuacion.
        }
    }
}

void MainWindow::loader(int ban)  //cargador de archivos
{
    QString doc;
    if(ban == 0){
        doc = obje;
    }
    else if(ban ==1){
        doc = obs;
    }
    else if(ban==2){
        QFile file("proyectiles_save.txt");           //Objeto para manejar la lectura del archivo
        file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
        doc=file.readAll();
        doc.remove("\n");
        doc.remove("\r");
        file.close();
    }
    else if(ban==3){
        QFile file("datos_juego.txt");           //Objeto para manejar la lectura del archivo
        file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
        doc=file.readAll();
        doc.remove("\n");
        doc.remove("\r");
        file.close();
    }
    QList<QString> dats;
    int n=0;
    while(n>=0){      //Ciclo para guardar cada dato de la linea de texto en su posicion correspondiente en el arreglo vec
        n = doc.indexOf(" ");
        if(n>0 && doc.left(n) != "F"){
            dats.append(doc.left(n));
        }
        if(doc.left(n) == "F"){
            doc=doc.remove(0,n+1);
            break;
        }
        doc=doc.remove(0,n+1);
    }

    n=0;
    while(n<dats.size()){
        if(dats.at(n)=="E"){
            if(ban ==0){
                objetivos.append(new objetivoGraf(dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat(), dats.at(++n).toFloat(), dats.at(++n)));
                scene->addItem(objetivos.last());
            }
            else if(ban==1){
                obstaculos.append(new obstaculoGraf(dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat(), dats.at(++n).toFloat(), dats.at(++n)));
                scene->addItem(obstaculos.last());
            }
            else if(ban==2){
                proyectiles.append(new proyectilGraf(dats.at(++n).toFloat(), dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat(),dats.at(++n).toFloat()));
                scene->addItem(proyectiles.last());
            }
        }
        n++;
    }
    if(ban == 0){
        temp_objetivos = objetivos;
        cantidad = objetivos.size() + 2;
        obje = doc;
    }
    else if(ban ==1){
        obs = doc;
    }
    else if(ban ==3){
        acumulado = puntuacion = dats.at(0).toInt();
        cantidad = dats.at(1).toInt();
        texto->setPlainText(QString::number(puntuacion));
        vida->setPlainText(QString::number(cantidad));
    }
}


void MainWindow::on_pushButton_multijugador_clicked()
{

}

void MainWindow::on_pushButton_Individual_clicked()
{
    scene->removeItem(guias.at(0));

    ui->pushButton_Individual->setDisabled(true);
    ui->pushButton_multijugador->setDisabled(true);
}

void MainWindow::on_pushButton_guardar_partida_clicked()
{

}

void MainWindow::on_pushButton_cargar_partida_clicked()
{

}

void MainWindow::on_pushButton_reiniciar_nivel_clicked()
{

}

void MainWindow::on_pushButton_reiniciar_juego_clicked()
{
 }

void MainWindow::on_pushButton_sound_clicked()
{

}


