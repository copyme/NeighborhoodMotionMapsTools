#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <istream>
#include <QFileDialog>
#include "CSVExtractor.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    model = nullptr;
    /*The order matters!*/
    /*N1*/
    mapleDict.push_back("[1, 0, 0]");
    mapleDict.push_back("[0, 1, 0]");
    mapleDict.push_back("[0, 0, 1]");
    mapleDict.push_back("[-1, 0, 0]");
    mapleDict.push_back("[0, -1, 0]");
    mapleDict.push_back("[0, 0, -1]");
    mapleDict.push_back("[0, 0, 0]");
    /*N2*/
    mapleDict.push_back("[1, 1, 0]");
    mapleDict.push_back("[1, 0, 1]");
    mapleDict.push_back("[0, 1, 1]");
    mapleDict.push_back("[-1, -1, 0]");
    mapleDict.push_back("[-1, 0, -1]");
    mapleDict.push_back("[0, -1, -1]");
    mapleDict.push_back("[-1, 1, 0]");
    mapleDict.push_back("[-1, 0, 1]");
    mapleDict.push_back("[1, -1, 0]");
    mapleDict.push_back("[1, 0, -1]");
    mapleDict.push_back("[0, -1, 1]");
    mapleDict.push_back("[0, 1, -1]");
    /*N3*/
    mapleDict.push_back("[1, 1, 1]");
    mapleDict.push_back("[-1, 1, 1]");
    mapleDict.push_back("[1, -1, 1]");
    mapleDict.push_back("[1, 1, -1]");
    mapleDict.push_back("[-1, -1, 1]");
    mapleDict.push_back("[-1, 1, -1]");
    mapleDict.push_back("[-1, -1, -1]");
    mapleDict.push_back("[1, -1, -1]");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDB()
{
    db_name = QFileDialog::getOpenFileName ( this,
         tr ( "Open database" ), QDir::homePath(), tr( "DB Files (*.db)" ) );

    db.setDatabaseName ( db_name );

    if( !db.open() )
    {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
    }
    delete model;
    model = new QSqlTableModel(this);
    model->setTable("NMM");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::sendSelection ( )
{
    std::map<QString, QString> data;
    int id = ui->tableView->selectionModel()->currentIndex().row();
    QString NMM = model->record( id ).value( "NMM" ).toString();
    NMM.replace("], [", "]\t[");
    NMM = NMM.mid(1, NMM.length() - 2);
    CSVExtractor tokens;
    tokens.setSeparator("\t");
    tokens.input(NMM.toStdString());
    for(int i = 0; i < tokens.getSize(); i++)
    {
       data[mapleDict[i]] = QString( tokens.getValue( i ).c_str() );
    }

    ui->widget->draw3DNMM ( data.cbegin(), data.cend() );
}
