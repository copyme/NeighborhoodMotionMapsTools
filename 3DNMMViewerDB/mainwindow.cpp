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
    std::vector<QString> data;
    int id = ui->tableView->selectionModel()->currentIndex().row();
    QString NMM = model->record( id ).value( "NMM" ).toString();
    NMM.replace("], [", "]\t[");
    NMM = NMM.mid(1, NMM.length() - 2);
    CSVExtractor tokens;
    tokens.setSeparator("\t");
    tokens.input(NMM.toStdString());
    for(int i = 0; i < tokens.getSize(); i++)
    {
       data.push_back( QString( tokens.getValue( i ).c_str() ) );
    }

    ui->widget->draw3DNMM ( data[0], data[1], data[2], data[3], data[4], data[5], data[6] );
}
