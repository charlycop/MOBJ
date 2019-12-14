#include  <QLabel>
#include  <QLineEdit>
#include  <QPushButton>
#include  <QHBoxLayout>
#include  <QVBoxLayout>
#include  <QAbstractTableModel>
#include  <QTableView>
#include  <QHeaderView>
#include  "InstancesWidget.h"
#include  "Cell.h"
#include  <string>
#include "CellsModel.h"
#include "CellsLib.h"

namespace Netlist{

    CellsLib :: CellsLib ( QWidget* parent )
    : QWidget         (parent)
    , cellViewer_     (NULL)
    , baseModel_      (new  CellsModel(this))
    , view_           (new  QTableView(this))
    , load_           (new  QPushButton(this))
    {
        setWindowTitle( tr("Cells already loaded in memory") );
        setMinimumSize(450,300);
        setAttribute( Qt::WA_QuitOnClose   , false  );
        setAttribute( Qt::WA_DeleteOnClose , false );
        setContextMenuPolicy( Qt::ActionsContextMenu  );
        view_->setShowGrid               ( false  );
        view_->setAlternatingRowColors( true );
        view_->setSelectionBehavior    ( QAbstractItemView :: SelectRows  );
        view_->setSelectionMode         ( QAbstractItemView :: SingleSelection  );
        view_->setSortingEnabled       ( true );
        
        view_->setModel                  ( baseModel_  );
        QHeaderView* horizontalHeader = view_->horizontalHeader ();
        horizontalHeader->setDefaultAlignment( Qt::AlignHCenter  );
        horizontalHeader->setMinimumSectionSize( 300 );
        horizontalHeader->setStretchLastSection( true );

        QHeaderView* verticalHeader = view_->verticalHeader ();
        verticalHeader->setVisible( false  );
        load_ ->setText( "Load" );
        connect( load_ , SIGNAL(clicked ()), this , SLOT(load ()) );

        QVBoxLayout* miseEnPage = new QVBoxLayout;
        miseEnPage->addWidget(view_);
        miseEnPage->addWidget(load_);
        setLayout(miseEnPage);
    }

    int   CellsLib::getSelectedRow  ()  const{
        QModelIndexList  selecteds = view_ ->selectionModel ()->selection (). indexes ();
        if (selecteds.empty ())  return  -1;
        return  selecteds.first ().row ();
    }

    void   CellsLib::load (){
        int  selectedRow = getSelectedRow ();
                std::cout << "getSelectedRow : " << selectedRow << std::endl;

        if (selectedRow  < 0)  return;
        std::cout << "getBaseModel() " << getBaseModel() << std::endl;
        std::cout << "getBaseModel()->getModel(selectedRow) : " <<getBaseModel()->getModel(selectedRow) << std::endl;
        cellViewer_->setCell( getBaseModel()->getModel(selectedRow) );
    }



} // Fin namespace Netlist