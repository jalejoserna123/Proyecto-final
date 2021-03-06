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
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/ganador"));
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/ganador_m"));
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/desempate"));
    scene->addItem(guias.at(0));
    ui->pushButton_guardar_partida->setDisabled(true);
    ui->pushButton_cargar_partida->setDisabled(true);        //encender los botones
    ui->pushButton_reiniciar_nivel->setDisabled(true);
    ui->pushButton_reiniciar_juego->setDisabled(true);
    //ui->pushButton_Individual->setDisabled(true);
    //ui->pushButton_multijugador->setDisabled(true);

}



void MainWindow::actualizar()
{
    if(obstaculos.isEmpty()==false || objetivos.isEmpty()==false){       //movimiento
    for(int i=0;i<proyectiles.size();i++){
        proyectiles.at(i)->actualizar(dt,v_limit);
        bordercollision(proyectiles.at(i));
    }
    if(objetivos.isEmpty()){                    //cambio de mapas
        puntuacion += 50*cantidad;
        texto->setPlainText(QString::number(puntuacion));
        if(punt_jugadores.isEmpty()){
            this->changeMap();
        }
        else{
            if(cont<punt_jugadores.size()){
                punt_jugadores.replace(cont,QString::number(puntuacion));   //sumario de puntos
                cont++;
                if(cont!=punt_jugadores.size()){
                    mensaje->setPlainText("Player # " +QString::number(cont+1));
                    acumulado = punt_jugadores.at(cont).toInt();
                    this->multijugador();
                }
            }
            else{
                cont=0;
                mensaje->setPlainText("Player # " +QString::number(cont+1));
                puntuacion = punt_jugadores.at(cont).toInt();
                acumulado = puntuacion;
                texto->setPlainText(QString::number(puntuacion));
                this->changeMap();

            }
        }
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
    if(f==true && x.GetS() == true)
    {
        QMessageBox::warning(this,"Warning!","entró");
        ui->pushButton_Individual->setEnabled(true);
        ui->pushButton_multijugador->setEnabled(true);
        f = false;
    }
    if(i<100){
        i += 5;          //ciclos que controlan la potencia del disparo
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

bool MainWindow::eventFilter(QObject *object, QEvent *event) //Método donde se dan las posiciones del mouse
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
        if(sound==true){
            QMediaPlayer *sound_canon = new QMediaPlayer();
            sound_canon->setMedia(QUrl("qrc:/Sounds/sound_canon.mp3"));
            sound_canon->setVolume(40);
            sound_canon->play();
        }
        timer->start(16);
        proyectiles.append(new proyectilGraf(proyector.last()->getProyector()->get_px()+(62.87*cos((14.74356284+delta)*PI/180)), proyector.last()->getProyector()->get_py()+(62.87*sin((14.74356284+delta)*PI/180)), vel, delta));
        scene->addItem(proyectiles.last());
        cantidad-=1;
        vida->setPlainText(QString::number(cantidad));
        event->accept();
    }
}

void MainWindow::bordercollision(proyectilGraf* b)    //colision con los bordes del mapa
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
            if(sound==true){
                QMediaPlayer *sound_impacto = new QMediaPlayer();
                //sound_impacto->setMedia(QUrl::fromLocalFile("C:/Users/Jhonatan Sossa/Pictures/sound_impacto.mp3"));
                sound_impacto->setMedia(QUrl("qrc:/Sounds/sound_impacto.mp3"));
                sound_impacto->setVolume(50);
                sound_impacto->play();
            }
            scene->removeItem(objetivos.at(i));
            scene->removeItem(b);
            objetivos.removeAt(i);
            proyectiles.removeOne(b);
            puntuacion += 100; //Suma puntuacion
            texto->setPlainText(QString::number(puntuacion));//Cambia la puntuacion.
        }
    }
}

void MainWindow::loader(int ban)          //cargador de archivos
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

void MainWindow::changeMap()       //cambio de mapa
{

    if(punt_jugadores.isEmpty()){
        acumulado = puntuacion;
    }
    for(int i=0; i<objetivos.size();i++){      //condicionales y ciclos que determinan cuando se cambia de mapa
        scene->removeItem(objetivos.at(i));
    }
    objetivos.clear();
    for(int i=0; i<obstaculos.size();i++){
        scene->removeItem(obstaculos.at(i));
    }
    obstaculos.clear();
    for(int i=0; i<proyectiles.size();i++){
        scene->removeItem(proyectiles.at(i));
    }
    proyectiles.clear();
    if(obje.size() == 1 && obs.size() == 1 && punt_jugadores.isEmpty()){
        if(sound==true){
            QMediaPlayer *sound_final = new QMediaPlayer();

            sound_final->setMedia(QUrl("qrc:/Sounds/sound_final.mp3"));
            sound_final->setVolume(50);
            sound_final->play();
        }
        scene->addItem(guias.at(1));
        scene->addText(QString::number(acumulado), QFont("Times",30,QFont::Black))->setPos(790,273);
        ui->pushButton_cargar_partida->setDisabled(true);
        ui->pushButton_guardar_partida->setDisabled(true);
        ui->pushButton_reiniciar_nivel->setDisabled(true);
    }
    else if(obje.size() == 1 && obs.size() == 1 && punt_jugadores.isEmpty() == false){
        if(sound==true){
            QMediaPlayer *sound_final = new QMediaPlayer();

            sound_final->setMedia(QUrl("qrc:/Sounds/sound_final.mp3"));
            sound_final->setVolume(50);
            sound_final->play();
        }
        int mayor, jugador;    //para multijugador
        if(punt_jugadores.at(0).toInt() > punt_jugadores.at(1).toInt()){
            mayor = punt_jugadores.at(0).toInt();
            jugador = 1;
            scene->addItem(guias.at(2));
            scene->addText(QString::number(mayor), QFont("Times",30,QFont::Black))->setPos(790,273);
            scene->addText(QString::number(jugador), QFont("Times",70,QFont::Black))->setPos(1070,122);
        }
        else if (punt_jugadores.at(1).toInt() > punt_jugadores.at(0).toInt()){
            mayor = punt_jugadores.at(1).toInt();
            jugador = 2;
            scene->addItem(guias.at(2));
            scene->addText(QString::number(mayor), QFont("Times",30,QFont::Black))->setPos(790,273);
            scene->addText(QString::number(jugador), QFont("Times",70,QFont::Black))->setPos(1070,122);
        }
        else{
            mayor = punt_jugadores.at(0).toInt();
            scene->addItem(guias.at(3));
            scene->addText(QString::number(mayor), QFont("Times",30,QFont::Black))->setPos(790,273);
        }
        ui->pushButton_cargar_partida->setDisabled(true);
        ui->pushButton_guardar_partida->setDisabled(true);
        ui->pushButton_reiniciar_nivel->setDisabled(true);
    }
    else{
        loader(1);
        loader(0);
        vida->setPlainText(QString::number(cantidad));
    }
}

void MainWindow::multijugador()     //para manejar el multijugador
{
    objetivos = temp_objetivos;
    for(int i=0; i<objetivos.size();i++){
        scene->addItem(objetivos.at(i));
    }
    cantidad = objetivos.size()+2;
    for(int i=0;i<proyectiles.size();i++){
        scene->removeItem(proyectiles.at(i));
    }
    proyectiles.clear();
    vida->setPlainText(QString::number(cantidad));
    puntuacion = punt_jugadores.at(cont).toInt();
    texto->setPlainText(QString::number(puntuacion));
}

void MainWindow::on_pushButton_multijugador_clicked()  //requisitos para multijugador
{
    scene->removeItem(guias.at(0));
    ui->pushButton_Individual->setDisabled(true);
    ui->pushButton_multijugador->setDisabled(true);
    ui->pushButton_reiniciar_nivel->setEnabled(true);
    ui->pushButton_reiniciar_juego->setEnabled(true);
    mensaje->setPlainText("Player #1: " +QString::number(cont+1));
    mensaje->startTimer(1000);
    QString t = QString::number(0);
    punt_jugadores.append(t);
    punt_jugadores.append(t);
}

void MainWindow::on_pushButton_Individual_clicked()    //para modo de juego indivual
{
    scene->removeItem(guias.at(0));
    ui->pushButton_reiniciar_juego->setEnabled(true);
    ui->pushButton_cargar_partida->setEnabled(true);
    ui->pushButton_guardar_partida->setEnabled(true);
    ui->pushButton_reiniciar_nivel->setEnabled(true);
    ui->pushButton_Individual->setDisabled(true);
    ui->pushButton_multijugador->setDisabled(true);
}


void MainWindow::on_pushButton_guardar_partida_clicked()   //guardar partida
{
    ofstream fout;
    fout.open("objetivos_save.txt");
    for(int i=0; i<objetivos.size(); i++){    //ciclos que copian en los archivos para guardar partida
        if(i < (objetivos.size()-1)){
            fout<<"E "<<objetivos.at(i)->getObjetivo()->getX()<<" "<<objetivos.at(i)->getObjetivo()->getY()<<" "<<objetivos.at(i)->getObjetivo()->getH()<<" "<<objetivos.at(i)->getObjetivo()->getW()<<" "<< objetivos.at(i)->getObjetivo()->getDir().toStdString()<<" ";
        }
        else{
            fout<<"E "<<objetivos.at(i)->getObjetivo()->getX()<<" "<<objetivos.at(i)->getObjetivo()->getY()<<" "<<objetivos.at(i)->getObjetivo()->getH()<<" "<<objetivos.at(i)->getObjetivo()->getW()<<" "<< objetivos.at(i)->getObjetivo()->getDir().toStdString()<<" F "<< obje.toStdString();
        }
    }
    fout.close();

    fout.open("obstaculos_save.txt");
    for(int i=0; i<obstaculos.size(); i++){
        if(i < (obstaculos.size()-1)){
            fout<<"E "<<obstaculos.at(i)->getObstaculo()->getX()<<" "<< obstaculos.at(i)->getObstaculo()->getY()<<" "<<obstaculos.at(i)->getObstaculo()->getH()<<" "<<obstaculos.at(i)->getObstaculo()->getW()<<" "<<obstaculos.at(i)->getObstaculo()->getDir().toStdString()<<" ";
        }
        else{
            fout<<"E "<<obstaculos.at(i)->getObstaculo()->getX()<<" "<< obstaculos.at(i)->getObstaculo()->getY()<<" "<<obstaculos.at(i)->getObstaculo()->getH()<<" "<<obstaculos.at(i)->getObstaculo()->getW()<<" "<<obstaculos.at(i)->getObstaculo()->getDir().toStdString()<<" F "<< obs.toStdString();
        }
    }
    fout.close();

    fout.open("proyectiles_save.txt");    //ciclos que leen los archivos de guardar partida
    for(int i=0; i<proyectiles.size(); i++){
        if(i<(proyectiles.size()-1)){
            fout<<"E "<<proyectiles.at(i)->getProyectil()->getX()<<" "<<proyectiles.at(i)->getProyectil()->getY()<<" "<<proyectiles.at(i)->getProyectil()->getVx()<<" "<<proyectiles.at(i)->getProyectil()->getVy()<<" "<<proyectiles.at(i)->getProyectil()->getAx()<<" "<<proyectiles.at(i)->getProyectil()->getAy()<<" ";
        }
        else{
            fout<<"E "<<proyectiles.at(i)->getProyectil()->getX()<<" "<<proyectiles.at(i)->getProyectil()->getY()<<" "<<proyectiles.at(i)->getProyectil()->getVx()<<" "<<proyectiles.at(i)->getProyectil()->getVy()<<" "<<proyectiles.at(i)->getProyectil()->getAx()<<" "<<proyectiles.at(i)->getProyectil()->getAy()<<" F ";
        }
    }
    fout.close();
    fout.open("datos_juego.txt");
    fout << puntuacion <<" "<< cantidad<<" F ";
    fout.close();
}

void MainWindow::on_pushButton_cargar_partida_clicked()
{
    ui->pushButton_Individual->setDisabled(true);
    ui->pushButton_multijugador->setDisabled(true);
    for(int i=0; i<objetivos.size();i++){
        scene->removeItem(objetivos.at(i));
    }
    objetivos.clear();
    for(int i=0; i<obstaculos.size();i++){
        scene->removeItem(obstaculos.at(i));
    }
    obstaculos.clear();
    for(int i=0; i<proyectiles.size();i++){
        scene->removeItem(proyectiles.at(i));
    }
    proyectiles.clear();
    QFile file_2("obstaculos_save.txt");           //Objeto para manejar la lectura del archivo
    file_2.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    obs=file_2.readAll();
    obs.remove("\n");
    obs.remove("\r");
    file_2.close();
    loader(1);
    QFile file("objetivos_save.txt");           //Objeto para manejar la lectura del archivo
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    obje=file.readAll();
    obje.remove("\n");
    obje.remove("\r");
    file.close();
    loader(0);
    loader(2);
    loader(3);
}

void MainWindow::on_pushButton_reiniciar_nivel_clicked() //para el reinicio de nivel
{
    if(acumulado>0){
        acumulado -= 50;
    }
    for(int i=0; i<objetivos.size();i++){
        scene->removeItem(objetivos.at(i));
    }
    for(int i=0; i<proyectiles.size();i++){      //ciclos y condicionales que reinician el nivel
        scene->removeItem(proyectiles.at(i));
    }
    proyectiles.clear();
    objetivos = temp_objetivos;
    for(int i=0;i<objetivos.size();i++){
        scene->addItem(objetivos.at(i));
    }
    cantidad = objetivos.size() +2;
    vida->setPlainText(QString::number(cantidad));
    puntuacion = acumulado;
    texto->setPlainText(QString::number(puntuacion));
}

void MainWindow::on_pushButton_reiniciar_juego_clicked()   //para reiniciar el juego hasta el inicio
{
    ui->pushButton_guardar_partida->setDisabled(true);
    ui->pushButton_cargar_partida->setDisabled(true);
    ui->pushButton_reiniciar_nivel->setDisabled(true);
    ui->pushButton_reiniciar_juego->setDisabled(true);
    ui->pushButton_Individual->setEnabled(true);
    ui->pushButton_multijugador->setEnabled(true);
    punt_jugadores.clear();
    guias.clear();
    scene->clear();
    proyectiles.clear();
    obstaculos.clear();
    objetivos.clear();
    proyector.clear();
    cont = cantidad = puntuacion = acumulado = 0;
    proyector.append(new proyectorGraf(55, 13));
    scene->addItem(proyector.last());

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
    scene->addText("Disparos: ",tipo)->setPos(150,0);
    texto=scene->addText("0",tipo);// Añade el cero.
    vida = scene->addText("0",tipo);
    texto->setFlag(QGraphicsItem::ItemIsMovable);
    texto->setPos(50,0);//Posicion
    vida->setPlainText(QString::number(cantidad));
    vida->setPos(220,0);
    mensaje = scene->addText(" ", tipo);
    mensaje->setPos(1120,0);

    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/principal"));
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/ganador"));
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/ganador_m"));
    guias.append(new obstaculoGraf(635, 250, 500, 1270, ":/Img/desempate"));
    scene->addItem(guias.at(0));
}

void MainWindow::on_pushButton_sound_clicked()  //para manejar sonido del juego
{
    if(sound == true){
        ui->pushButton_sound->setText("Sound on");
        sound = false;
    }
    else{
        ui->pushButton_sound->setText("Sound off");
        sound = true;
    }
}



void MainWindow::on_actionRules_triggered()    //para las reglas que son otra ventana
{
    Rules *MyRules = new Rules(); MyRules->show();
}

void MainWindow::on_actionClose_Game_triggered()
{
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    Control *MyControl = new Control(); MyControl->show();
}
