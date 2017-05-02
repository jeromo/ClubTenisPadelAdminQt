#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "initdb.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QMYSQL"))
        QMessageBox::critical(this, "Unable to load database", "This demo needs the MYSQL driver");

    // initialize the database
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }

    // Create the data model
    model = new QSqlRelationalTableModel(ui->playersTable);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable("player");
    model->setRelation(1, QSqlRelation("fos_user", "id", "username"));

    // Remember the indexes of the columns
    playerIdx = model->fieldIndex("player");
    genreIdx = model->fieldIndex("genre");

    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    ui->playersTable->setModel(model);
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
//    mapper->setItemDelegate(new BookDelegate(this));
    mapper->addMapping(ui->nameEdit, model->fieldIndex("id_fos_user"));
    mapper->addMapping(ui->descriptionEdit, model->fieldIndex("description"));
    mapper->addMapping(ui->genreEdit,  model->fieldIndex("genre"));
    mapper->addMapping(ui->activeEdit,  model->fieldIndex("active"));

    connect(ui->playersTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    ui->playersTable->setCurrentIndex(model->index(0, 0));
}

void AdminWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                "Error initializing database: " + err.text());
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
