#include  <QMainWindow>
#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  <QMenuBar>
#include  <QMainWindow>
#include  "SaveCellDialog.h"
#include  "OpenCellDialog.h"
#include  "InstancesWidget.h"
#include  "CellsLib.h"
#include  "CellsModel.h"

#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"
#include  "CellViewer.h"


namespace Netlist{

    CellViewer :: CellViewer ( QWidget* parent )
    : QMainWindow     (parent)
    , cellWidget_     (NULL)
    , saveCellDialog_ (NULL)
    , openCellDialog_ (NULL)
    , instancesWidget_(NULL)
    , cellsLib_       (NULL)
    {
        cellWidget_     = new  CellWidget  ();
        saveCellDialog_ = new  SaveCellDialog ( this );
        openCellDialog_ = new  OpenCellDialog ( this );
        instancesWidget_= new  InstancesWidget();
        cellsLib_       = new  CellsLib();

        setCentralWidget( cellWidget_  );
        QMenu* fileMenu = menuBar()->addMenu( "&File" );

        /* SAVE */
        QAction* action = new  QAction( "&Save As", this );
        action ->setStatusTip( "Save to disk (rename) the Cell" );
        action ->setShortcut ( QKeySequence("CTRL+S") );
        action ->setVisible   ( true );
        fileMenu ->addAction( action  );
        connect( action , SIGNAL(triggered ()), this , SLOT(saveCell()) );

        /* OPEN */
        action = new  QAction( "&Open", this );
        action ->setStatusTip( "Open a cell" );
        action ->setShortcut ( QKeySequence("CTRL+O") );
        action ->setVisible   ( true );
        fileMenu ->addAction( action  );
        connect( action , SIGNAL(triggered ()), this , SLOT(openCell()) );   
        
        /* INSTANCEWIDGET */
        action = new  QAction( "&Show Instances", this );
        action ->setStatusTip( "Show the MasterCells with their instances" );
        action ->setShortcut ( QKeySequence("CTRL+I") );
        action ->setVisible   ( true );
        fileMenu ->addAction( action  );
        connect( action , SIGNAL(triggered ()), this , SLOT(showInstancesWidget() ));     

        /* CELLSLIB */
        action = new  QAction( "&Show loaded Cells", this );
        action ->setStatusTip( "Show the MasterCells already in memory" );
        action ->setShortcut ( QKeySequence("CTRL+C") );
        action ->setVisible   ( true );
        fileMenu ->addAction( action  );
        connect( action , SIGNAL(triggered ()), this , SLOT(showCellsLib() ));     
        //Signal pour updater la liste.
        connect( this ,  SIGNAL(cellLoaded()), cellsLib_->getBaseModel() , SLOT(updateDatas()));


        /* QUIT */
        action = new  QAction( "&Quit", this );
        action ->setStatusTip( "Exit the Netlist Viewer" );
        action ->setShortcut ( QKeySequence("CTRL+Q") );
        action ->setVisible   ( true );
        fileMenu ->addAction( action  );
        connect( action , SIGNAL(triggered ()), this , SLOT(close ()) );


    }

   // void updateDatas(){
   //         CellsModel::updateDatas();
    //}

    void   CellViewer :: saveCell  (){
        Cell* cell = getCell();
        if ( cell == NULL ) 
            return;
        QString  cellName = cell ->getName().c_str();
        if (saveCellDialog_->run(cellName)) {
            cell->setName(cellName.toStdString());
            cell->save(cellName.toStdString());
        }
    }
    
    //void cellLoaded(){}

    void   CellViewer :: openCell  (){
        std::string cellptr;
        Cell* cell;
        if(openCellDialog_->run(&cellptr)){
            cell = Cell::find(cellptr);
            if (cell == nullptr){
                if ((cell = Cell::load(cellptr)))
                    emit cellLoaded();
            }

        }
        setCell(cell);

    }



    void  CellViewer::showInstancesWidget (){
        instancesWidget_->setCellViewer(this);
        instancesWidget_->setCell(getCell());
        instancesWidget_->show();
    }  // TME9+.

    void  CellViewer::showCellsLib        (){
        cellsLib_->setCellViewer(this);
        cellsLib_->show();
    }  // TME9+.


    CellViewer::~CellViewer          (){}

    void CellViewer::setCell              ( Cell* c){
        cellWidget_->setCell(c);
    }



} // Fin namespace Netlist