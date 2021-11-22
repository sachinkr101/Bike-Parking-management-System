#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrBook = new Book(this);
    ptrCancel = new Cancel(this);

    connect(ptrBook, &Book::mysignal, this, &MainWindow::updateUI);
    connect(ptrCancel, &Cancel::mysignal1, this, &MainWindow::updateUI);

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    qDebug() << "===== in updateUI() ====";
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Slot, Available from  _bikeparking");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
    }

    int no = 1;
    while(query.next())
    {
        QString sLabel = "lblSlot" + query.value(0).toString();
        QLabel * ptr = this->findChild<QLabel*>(sLabel);
        if(ptr!=nullptr)
        {
            if(query.value(1).toString().compare("N") == 0)
            {
                //int no = (qrand() % ((6 + 1) - 1) + 1);
                QString sBike = "bike" + QString::number(no) + ".jpg";
                QPixmap pm(":/assets/images/"+sBike);
                ptr->setPixmap(pm);
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is booked";
            }
            else
            {
                ptr->clear();
                ptr->setText("Slot "+query.value(0).toString());
            }


        }
        qDebug()<<query.value(0).toString()<< query.value(1).toString();
        no>=6?no=1:no++;
    }

}

void MainWindow::on_btnCancel_clicked()
{
    ptrCancel->Show();
}

void MainWindow::on_btnBook_clicked()
{
    ptrBook->Show();
}

void MainWindow::Show()
{
    qDebug() << "in MainWindow::Show()";
}
